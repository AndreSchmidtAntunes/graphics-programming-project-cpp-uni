#include "GL_entry_point.h"

#include "Camera.h"
#include "common.h" 
#include "GLExtras.h"
#include "GLUTCallbacks.h" // Placed here so that GLUTCallbacks.h doesn't include itself.
#include "Matrix4x4.h"
#include "Mesh.h"
#include "UserInput.h"
#include <Windows.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

#define REFRESH_RATE 16

// using these functions to test input callback system

	void PrintHello() {
		std::cout << "HELLO!!!" << std::endl;
	}

	void PrintWorld() {
		std::cout << "WOOORRLLDD!!!!!" << std::endl;
	}

	void PrintUP() {
		std::cout << "UP!!!" << std::endl;
	}

	void PRINTKEY(size_t key, size_t x, size_t y) {
		std::cout << ((key >= 100) ? key - 87 : key) << std::endl;
	}

#define ROTATION_SPEED 80.0f
#define CAMERA (*GLUTCallbacks::GetEntryPoint().camera)
#define DELTATIME GLUTCallbacks::GetEntryPoint().deltaTime

void RotateRight() { CAMERA.RotateFirstPerson(Vector3::Right * ROTATION_SPEED * DELTATIME); }
void RotateDown()  { CAMERA.RotateFirstPerson(Vector3::Down * ROTATION_SPEED * DELTATIME);	}
void RotateLeft()  { CAMERA.RotateFirstPerson(Vector3::Left * ROTATION_SPEED * DELTATIME);	}
void RotateUp()	   { CAMERA.RotateFirstPerson(Vector3::Up * ROTATION_SPEED * DELTATIME);	}

#define MOVESPEED 4.0f

void MoveForward() { CAMERA.position -= CAMERA.forward * MOVESPEED * DELTATIME; }
void MoveBack()    { CAMERA.position += CAMERA.forward * MOVESPEED * DELTATIME; }
void MoveRight()   { CAMERA.position += CAMERA.right * MOVESPEED * DELTATIME;	}
void MoveLeft()	   { CAMERA.position -= CAMERA.right * MOVESPEED * DELTATIME;	}
void MoveUp()	   { CAMERA.position += CAMERA.up * MOVESPEED * DELTATIME;		}
void MoveDown()	   { CAMERA.position -= CAMERA.up * MOVESPEED * DELTATIME;		}

static Texture2D* texture;
static Mesh* mesh;

GL_entry_point::GL_entry_point(int argc, char* argv[]) : camera(new Camera(Vector3::Forward, Vector3::Zero, Vector3::Up, Vector3::Right)), deltaTime(0) {

	rot = 0.0f;

	glutInitWindowSize(800, 800);

	glutInit(&argc, argv);
	glutCreateWindow("Graphics Programming App");
		
	glutDisplayFunc(GLUTCallbacks::Display);

	GLUTCallbacks::Init(this);

	UserInput::Init();

	// below block is to test new input callback system

		UserInput::AddKeyboardDownCallback('h', PrintHello);
		UserInput::AddKeyboardDownCallback('h', PrintHello);

		UserInput::RemoveKeyboardDownCallback('h', PrintHello);

		UserInput::AddKeyboardDownCallback('h', PrintWorld);

		UserInput::AddSpecialDownCallback(UserInput::SpecialKey::LEFT_SHIFT, PrintUP);

		UserInput::AddSpecialActiveCallback(UserInput::SpecialKey::LEFT, RotateLeft);
		UserInput::AddSpecialActiveCallback(UserInput::SpecialKey::UP, RotateUp);
		UserInput::AddSpecialActiveCallback(UserInput::SpecialKey::RIGHT, RotateRight);
		UserInput::AddSpecialActiveCallback(UserInput::SpecialKey::DOWN, RotateDown);

		UserInput::AddKeyboardActiveCallback('d', MoveRight);
		UserInput::AddKeyboardActiveCallback('a', MoveLeft);
		UserInput::AddKeyboardActiveCallback('w', MoveForward);
		UserInput::AddKeyboardActiveCallback('s', MoveBack);

	glutTimerFunc(REFRESH_RATE, GLUTCallbacks::Timer, REFRESH_RATE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(0, 0, 800, 800);
		gluPerspective(80, 1, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);

	/// TODO: the gnererated texture still isnt getting a unique id (always 0)
	texture = new Texture2D("textures/penguins.raw", 512, 512);
	mesh = new Mesh("models/suzanne.obj", texture);

	glutMainLoop();
}

#include <map>
#include <typeindex>

const static std::map<std::type_index, std::vector<void*>*> asset_cache_map {
	{ std::type_index(typeid(Texture2D)),	(new std::vector<void*>) }, // void* means Texture2D* here
	{ std::type_index(typeid(Mesh)),		(new std::vector<void*>) } // void* means Mesh* here
};

template <typename T> requires( 
	std::common_type<T, Texture2D>::value || 
	std::common_type<T, Mesh>::value
	)
static void RemoveFromAssetCache(const T* asset) {
	// cast cache pointer to cache vector pointer, to then get vector as reference
	std::vector<T>& asset_cache = *static_cast<std::vector<T>*>(&asset_cache_map[typeid(T)]);

	auto it = std::find(asset_cache.begin(), asset_cache.end(), texture);

	if (it != asset_cache.end()) {
		delete *it;
		asset_cache.erase(it);
	}
}

template <typename T> requires(
	std::common_type<T,Texture2D>::value || 
	std::common_type<T,Mesh>::value
	)
static void RemoveFromAssetCache(const size_t& asset_cache_index) {
	std::vector<T>& asset_cache = *static_cast<std::vector<T>*>(&asset_cache_map[typeid(T)]);

	delete asset_cache[asset_cache_index];
	asset_cache.erase(asset_cache.begin() + asset_cache_index);
}

template <typename T> requires( 
	std::common_type<T,Texture2D>::value || 
	std::common_type<T,Mesh>::value
	)
static void AppendToAssetCache(const T* asset) {
	// Cast cache pointer to cache vector pointer, to then get vector as reference
	std::vector<T>& asset_cache = *static_cast<std::vector<T>*>(&asset_cache_map[typeid(T)]);

	asset_cache.push_back(asset);
}

template <typename T> requires(
	std::common_type<T, Texture2D>::value ||
	std::common_type<T, Mesh>::value
	)
static void InsertIntoAssetCache(const size_t& asset_cache_index, const T* asset) {
	std::vector<T>& asset_cache = *static_cast<std::vector<T>*>(&asset_cache_map[typeid(T)]);
	
	asset_cache.insert(asset_cache.begin() + asset_cache_index, asset_cache_index);
}

GL_entry_point::~GL_entry_point(void) {
	delete camera;
}

void GL_entry_point::Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clears out the last frame

	Draw();	// Draw vertices: 
	glFlush(); // Passes the scene draw to the graphics card
	glutSwapBuffers();
}

void GL_entry_point::Draw() {
	mesh->Render(Vector3(0, 0, -5), Vector3::Zero, camera);
}

void GL_entry_point::Update() {
	rot += 1.0f;
	if (rot >= 360.0f)
		rot = 0.0f;

	//glLoadIdentity();

	//gluLookAt(
	//	camera->eye.x, camera->eye.y, camera->eye.z,  // eye
	//	camera->position.x, camera->position.y, camera->position.z, // position
	//	camera->up.x, camera->up.y, camera->up.z // up
	//);
}