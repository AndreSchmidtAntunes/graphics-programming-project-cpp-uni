#include "GL_entry_point.h"

#include "AssetCache.h"
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

static Colour clear_colour = Colour(0.396f, 0.396f, 0.502f, 1.0f);

static Scene* scene;
static Transform* transform_A;
static Transform* transform_B;
static Transform* transform_C;
static Transform* transform_D;

GL_entry_point::GL_entry_point(int argc, char* argv[]) : camera(new Camera), deltaTime(0) {

	rot = 0.0f;

	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(1500, 1000);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
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
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	Texture2D* penguins_texture = new Texture2D("textures/penguins.raw", 512, 512);
	Material* shiny_blue_material = new Material(Colour::Blue, Colour(0.75, 0.75, 0.75, 1), Colour::White, 1);
	Material* matt_red_material = new Material(Colour::Red, Colour::Red, Colour::Red, 0.1);
	Material* bight_green_material = new Material(Colour::Green, Colour::Green, Colour::White, 1);
	Material* bight_magenta_material = new Material(Colour::Magenta, Colour::Magenta, Colour::White, 1);

	Mesh* suzanne_mesh = new Mesh("models/suzanne.obj");
	Mesh* cube_mesh = new Mesh("models/cube.obj");

	scene = new Scene;

	camera->setScene(scene);

	transform_A = new Transform("green suzanne", scene->root, Vector3(5, -1, -5));
	transform_A->local_scale = Vector3::One * 0.5;
	transform_A->setMesh(suzanne_mesh);
	transform_A->setMaterial(bight_green_material);

	transform_B = new Transform("cube", transform_A, Vector3(0, 0, -10));
	transform_B->local_scale = Vector3::One * 10;
	transform_B->setMesh(cube_mesh);
	transform_B->setMaterial(bight_magenta_material);

	transform_C = new Transform("red suzanne", scene->root, Vector3(-3, -3, -4));
	transform_C->setParent(transform_B); // changed C's parent from root to B.
	transform_C->local_scale = Vector3::One * 0.2;
	transform_C->setMaterial(matt_red_material);
	transform_C->setMesh(suzanne_mesh);

	transform_D = new Transform("blue suzanne", scene->root);
	transform_D->local_position = Vector3::Back * 5 + Vector3::Left * 2;
	transform_D->setMesh(suzanne_mesh);
	transform_D->setTexture(penguins_texture);
	transform_D->setMaterial(shiny_blue_material);

// hierarchy:
	//	root
	//	╟══	A
	//	║	╚══	B
	//	║		╚══ C
	//	╚══	D

	UserInput::Enable(); //allow user input after everything has been properly set up.
		
	glutMainLoop();
}

GL_entry_point::~GL_entry_point(void) {

	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplGLUT_Shutdown();
	ImGui::DestroyContext();

	delete camera;
}

////////////////////
/// TODO: make lights a transform derived class and add light support to the scene graph
////////////////////

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