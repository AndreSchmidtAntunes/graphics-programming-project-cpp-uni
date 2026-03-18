#include "GL_entry_point.h"

#include "common.h" 
#include "Camera.h"
#include "GLExtras.h"
#include "GLUTCallbacks.h" // Placed here so that GLUTCallbacks.h doesn't include itself.
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

GL_entry_point::GL_entry_point(int argc, char* argv[]) : camera(new Camera(1, 0, 0)) {

	rot = 0.0f;

	glutInitWindowSize(800, 800);

	glutInit(&argc, argv);
	glutCreateWindow("Graphics Programming App");
		
	glutDisplayFunc(GLUTCallbacks::Display);

	GLUTCallbacks::Init(this);

	UserInput::Init();

	// below block is to test new input callback system

		UserInput::AddKeyboardDownCallback('h', PrintHello);
		UserInput::AddKeyboardDownCallback('h', PrintWorld);
		UserInput::AddSpecialDownCallback(UserInput::UP, PrintUP);


	glutTimerFunc(REFRESH_RATE, GLUTCallbacks::Timer, REFRESH_RATE);

	glutInitDisplayMode(GLUT_DOUBLE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45, 1, 0, 1000);

	glMatrixMode(GL_MODELVIEW);

	glutMainLoop();
}

GL_entry_point::~GL_entry_point(void) {
	delete camera;
}

void GL_entry_point::Display() {
	glClear(GL_COLOR_BUFFER_BIT); // Clears out the last frame
	// Draw vertices: 
	DrawPolygons();

	glFlush(); // Passes the scene draw to the graphics card
	glutSwapBuffers();
}

static const Mesh teapot_mesh("teapot.obj");
static const Mesh rat_mesh("rat.obj");

void GL_entry_point::DrawPolygons() {

	//// middle
	//glPushMatrix();
	//	#define RATSCALE 0.025f
	//	glScalef(RATSCALE, RATSCALE, RATSCALE);
	//	glRotatef(rot* 4, 1, 0, 0); glRotatef(rot * 2, 0, 1, 0); glRotatef(rot * 1, 0, 0, 1);

	//	GLExtras::AddMesh(rat_mesh);
	//glPopMatrix();

	//// bott-right
	//glPushMatrix();
	//	#define POTSCALE 0.002f
	//	glScalef(POTSCALE, POTSCALE, POTSCALE);
	//	glTranslatef(200, -130, 0);
	//	glRotatef(rot * -2, 1, 0, 0); glRotatef(rot * 4, 0, 1, 0); glRotatef(rot * -5, 0, 0, 1);

	//	GLExtras::AddMesh(rat_mesh);
	//glPopMatrix();

	//// top-left
	//glPushMatrix();
	//	#define POTSCALE 0.002f
	//	glScalef(POTSCALE, POTSCALE, POTSCALE);
	//	glTranslatef(-200, 130, 0);
	//	glRotatef(rot * 2, 1, 0, 0); glRotatef(rot * -4, 0, 1, 0); glRotatef(rot * 5, 0, 0, 1);

	//	GLExtras::AddMesh(rat_mesh);
	//glPopMatrix();

	glPushMatrix();

		#define POTSCALE 0.025f
		glScalef(POTSCALE, POTSCALE, POTSCALE);

		glRotatef(rot, 4, 2, 1);

		glTranslatef(0.0f, 0.0f, -5.0f);

		GLExtras::AddMesh(rat_mesh);
	
	glPopMatrix();
}

void GL_entry_point::Update() {
	rot += 1.0f;
	if (rot >= 360.0f)
		rot = 0.0f;

	gluLookAt(
		camera->eye.x, camera->eye.y, camera->eye.z,  // eye
		camera->position.x, camera->position.y, camera->position.z, // position
		camera->up.x, camera->up.y, camera->up.z // up
	);
}