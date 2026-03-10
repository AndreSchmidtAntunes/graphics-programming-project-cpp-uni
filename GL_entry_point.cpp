#include "GL_entry_point.h"

// Placed here so that GLUTCallbacks.h doesn't include itself, or any not needed libraries.
#include "common.h"
#include "GLExtras.h"
#include "GLUTCallbacks.h"
#include <Windows.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

#define REFRESH_RATE 16

GL_entry_point::GL_entry_point(int argc, char* argv[]) {

	rot = 0.0f;

	glutInitWindowSize(800, 800);

	GLUTCallbacks::Init(this);

	glutInit(&argc, argv);
	glutCreateWindow("Graphics Programming App");
		
	glutDisplayFunc(GLUTCallbacks::Display);

	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutKeyboardUpFunc(GLUTCallbacks::KeyboardUp);

	glutSpecialFunc(GLUTCallbacks::Special);
	glutSpecialUpFunc(GLUTCallbacks::SpecialUp);

	glutTimerFunc(REFRESH_RATE, GLUTCallbacks::Timer, REFRESH_RATE);

	glutMainLoop();
}

GL_entry_point::~GL_entry_point(void) {
	std::cout << "GL_END";
}

void GL_entry_point::Display() {
	glClear(GL_COLOR_BUFFER_BIT); // Clears out the last frame
	// Draw vertices: 
	DrawPolygons();

	glFlush(); // Passes the scene draw to the graphics card
}

void GL_entry_point::DrawPolygons() {
	glPushMatrix();

		//glRotatef(rot, 0.0f, 0.0f, -1.0f);

		Vector3 points[3] = { 
			Vector3(0, 0.5, 0), 
			Vector3(0.5, -0.5, 0), 
			Vector3(-0.5, -0.5, 0) 
		};
		Colour colours[3] = { 
			Colour::RED, 
			Colour::GREEN, 
			Colour::BLUE 
		};

		Poly triangle = Poly(points, colours, 3);

		//GLExtras::AddPolygon(triangle);

		glBegin(GL_POLYGON);
			glColor4f(1, 0, 0, 1);
			GLExtras::AddVertex(Vector3(0, 0.5, 0));
			glColor4f(0, 1, 0, 1);
			GLExtras::AddVertex(Vector3(0.5, -0.5, 0));
			glColor4f(0, 0, 1, 1);
			GLExtras::AddVertex(Vector3(-0.5, -0.5, 0));
		glEnd();

	glPopMatrix();

}

void GL_entry_point::Update() {

	glutPostRedisplay();
		
	std::cout << "udt!" << std::endl;
	rot += 0.5f;
	if (rot >= 360.0f)
		rot = 0.0f;
}