#include "GL_entry_point.h"

#include "common.h"
#include "GLUTCallbacks.h"
#include "imguiHelper.h"
#include "UserInput.h"
#include <Windows.h>

#define CAMERA (*GLUTCallbacks::GetEntryPoint().camera)
#define DELTATIME GLUTCallbacks::GetEntryPoint().deltaTime

#define ROTATION_SPEED 15.0f
void RotateRight() { CAMERA.RotateFirstPerson(Vector3::Right * ROTATION_SPEED * DELTATIME); }
void RotateDown()  { CAMERA.RotateFirstPerson(Vector3::Down * ROTATION_SPEED * DELTATIME);	}
void RotateLeft()  { CAMERA.RotateFirstPerson(Vector3::Left * ROTATION_SPEED * DELTATIME);	}
void RotateUp()	   { CAMERA.RotateFirstPerson(Vector3::Up * ROTATION_SPEED * DELTATIME);	}

void CameraDragRotate() {
	if (UserInput::IsMouseDown(UserInput::MouseInputs::RMB)) {
		CAMERA.RotateFirstPerson(Vector3(UserInput::getMouseDelta()) * ROTATION_SPEED * DELTATIME);
	}
}

#define MOVESPEED 4.0f
void MoveForward() { CAMERA.position -= CAMERA.forward * MOVESPEED * DELTATIME; }
void MoveBack()    { CAMERA.position += CAMERA.forward * MOVESPEED * DELTATIME; }
void MoveRight()   { CAMERA.position += CAMERA.right * MOVESPEED * DELTATIME;	}
void MoveLeft()	   { CAMERA.position -= CAMERA.right * MOVESPEED * DELTATIME;	}

static Colour clear_colour = Colour(0.565f, 0.617f, 0.725f, 1.000f);

static Scene* scene;
static Model* transform_A;
static Model* transform_B;
static Model* transform_C;
static Model* transform_D;
static Model* floor_model;
static Light* light_1;
static Light* light_2;

GL_entry_point::GL_entry_point(int argc, char* argv[]) : camera(new Camera), deltaTime(0) {

	rot = 0.0f;

	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(1500, 1000);
	glutInitDisplayMode(
		  GLUT_DOUBLE 
		| GLUT_DEPTH 
		| GLUT_RGBA 
		| GLUT_MULTISAMPLE
	);
	glutCreateWindow("Graphics Programming App");

	glutDisplayFunc(GLUTCallbacks::UpdateLoop);
	glutTimerFunc(16, GLUTCallbacks::Timer, 16);
	glutReshapeFunc(GLUTCallbacks::Reshape);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsDark();
	
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 3);
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 3);

	io.Fonts->AddFontDefault();

	static const ImWchar nerd_font_ranges[] = { 0xe000, 0xf8ff, 0 };

	//ImFontConfig config;
	//config.MergeMode = true;
	//config.PixelSnapH = true;
	//io.Fonts->AddFontFromFileTTF("fonts/HurmitNerdFont-Regular.otf", 16.0f, &config, nerd_font_ranges);

	ImGui_ImplGLUT_Init();
	ImGui_ImplOpenGL2_Init();

	GLUTCallbacks::Init(this);

	// --- User Input --- //

	UserInput::Init(false); // don't enable inputs while initialising the entry point.

	UserInput::AddSpecialActiveCallback(UserInput::SpecialInputs::LEFT, RotateLeft);
	UserInput::AddSpecialActiveCallback(UserInput::SpecialInputs::UP, RotateUp);
	UserInput::AddSpecialActiveCallback(UserInput::SpecialInputs::RIGHT, RotateRight);
	UserInput::AddSpecialActiveCallback(UserInput::SpecialInputs::DOWN, RotateDown);

	UserInput::AddKeyboardActiveCallback('d', MoveRight);
	UserInput::AddKeyboardActiveCallback('a', MoveLeft);
	UserInput::AddKeyboardActiveCallback('w', MoveForward);
	UserInput::AddKeyboardActiveCallback('s', MoveBack);

	UserInput::AddMouseDragCallback(CameraDragRotate);

	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, &(Colour(0.1f, 0.1f, 0.1f)[0]));

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_NORMALIZE);

	Material* shiny_blue_material = new Material(Colour::Blue, Colour(0.75, 0.75, 0.75, 1), Colour::White, 1);
	Material* matt_red_material = new Material(Colour::Red, Colour::Red, Colour::Red, 0.1);
	Material* bight_green_material = new Material(Colour::Green, Colour::Green, Colour::White, 1);
	Material* bight_magenta_material = new Material(Colour::Magenta, Colour::Magenta, Colour::White, 1);

	Mesh* suzanne_mesh = new Mesh("models/suzanne.obj");
	Mesh* cube_mesh = new Mesh("models/cube.obj");
	Mesh* teapot_mesh = new Mesh("models/teapot.obj");

	Texture2D* penguins_texture = Texture2D::FromFileRAW("textures/penguins.raw", 512, 512);
	Texture2D* snail_texture = Texture2D::FromFileBMP("textures/snail.bmp");

	scene = new Scene;

	camera->setScene(scene);

	Light* sun_light = new Light("Sun Lighting", scene->root, Vector3(-6, 10, -2.5));
	sun_light->light_type = Light_Type::Direction;
	sun_light->ambient = Colour::Hex8(0x8B8477FF);
	sun_light->diffuse = Colour::Hex8(0xDF691BFF);
	sun_light->ambient = Colour::Hex8(0x87692EFF);

	floor_model = new Model("floor", scene->root, Vector3(0, -5, 0), Quaternion::Identity, Vector3(100, 1, 100));
	floor_model->setMesh(cube_mesh);
	floor_model->setTexture(snail_texture);

	transform_A = new Model("green suzanne", scene->root, Vector3(5, -1, -5));
	transform_A->local_scale = Vector3::One * 0.5;
	transform_A->setMesh(suzanne_mesh);
	transform_A->setMaterial(bight_green_material);

	transform_B = new Model("cube", transform_A, Vector3(0, 0, -10));
	transform_B->local_scale = Vector3::One * 10;
	transform_B->setMesh(cube_mesh);
	transform_B->setMaterial(bight_magenta_material);
	transform_B->setTexture(penguins_texture);

	transform_C = new Model("red suzanne", scene->root, Vector3(-3, -3, -4));
	transform_C->setParent(transform_B); // changed C's parent from root to B.
	transform_C->local_scale = Vector3::One * 0.2;
	transform_C->setMaterial(matt_red_material);
	transform_C->setMesh(suzanne_mesh);

	transform_D = new Model("tea pot", scene->root);
	transform_D->local_position = Vector3::Back * 5 + Vector3::Left * 2 + Vector3::Down * 2;
	transform_D->setMesh(teapot_mesh);
	transform_D->setTexture(snail_texture);
	transform_D->setMaterial(shiny_blue_material);

	light_1 = new Light("green light", transform_D, Vector3(-2, 0, 0.5));
	light_1->light_type = Light_Type::Position;
	light_1->diffuse = Colour(0.026f, 0.210f, 0.026f, 1.000f);
	light_1->specular = Colour(0.022f, 1.000f, 0.271f, 1.000f);
	light_1->ambient = Colour(0.109f, 0.133f, 0.066f, 1.000f);
	light_1->falloff = 0.922;

	light_2 = new Light("pink light", scene->root, Vector3(-20, -10, 1));
	light_2->light_type = Light_Type::Position;
	light_2->specular = Colour(0.200f, 0.000f, 0.000f, 1.000f);
	light_2->diffuse = Colour(0.200f, 0.000f, 0.000f, 1.000f);
	light_2->ambient = Colour(1.000f, 0.210f, 0.210f, 1.000f);
	light_2->falloff = 0.889;

// hierarchy:
	//	root
	//	╟══ sun_light
	//	╟══ floor
	//	╟══	A
	//	║	╚══	B
	//	║		╚══ C
	//	╟══	teapot
	//	║	╚══ light1	
	//	╚══ light2

	UserInput::Enable(); //allow user input after everything has been properly set up.
	
	glutMainLoop();
}

GL_entry_point::~GL_entry_point(void) {

	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplGLUT_Shutdown();
	ImGui::DestroyContext();

	delete camera;
}

void GL_entry_point::Render() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ImGuiIO& io = ImGui::GetIO();
	glViewport(0, 0, io.DisplaySize.x, io.DisplaySize.y);
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplGLUT_NewFrame();
	ImGui::NewFrame();

	ImGuiHelper::FPS(io, deltaTime);
	ImGuiHelper::SceneTree(io, scene, &clear_colour);

	camera->DrawScene();

	ImGui::Render();

	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	glFlush(); // Passes the scene draw to the graphics card
	glutSwapBuffers();
	glutPostRedisplay();
}

void GL_entry_point::Update() {
	rot += 1.0f;
	if (rot >= 360.0f)
		rot = 0.0f;

	transform_A->local_rotation = Quaternion::Euler(0.0f, rot * DEG2RAD, 0.0f);
	transform_B->local_rotation = Quaternion::Euler(rot * DEG2RAD, 0.0f, 0.0f);
	transform_B->local_scale = Vector3::One * (sin(rot * DEG2RAD) + 1.5f);
	//transform_D->local_position = Vector3(sin(rot * DEG2RAD), 0.0f, -5.0f);
}