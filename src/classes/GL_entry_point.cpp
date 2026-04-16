#include "GL_entry_point.h"

#include "Camera.h"
#include "common.h"
#include "GLExtras.h"
#include "GLUTCallbacks.h"
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

	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(0, 0, 800, 800);
		gluPerspective(80, 1, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);

	glutMainLoop();
}

GL_entry_point::~GL_entry_point(void) {
	delete camera;
}

void GL_entry_point::Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clears out the last frame

	DrawPolygons();	// Draw vertices: 

	glFlush(); // Passes the scene draw to the graphics card
	glutSwapBuffers();
}

//static const Mesh* teapot_mesh = new Mesh("teapot.obj");
static const Mesh* rat_mesh = new Mesh("rat.obj");

void GL_entry_point::DrawPolygons() {

	rat_mesh->Render(Vector3(0, 0, -5), Vector3(0, 0, 90), Vector3(0.025), camera);
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