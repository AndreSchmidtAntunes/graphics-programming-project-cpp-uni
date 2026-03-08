#include "GL_entry_point.h"

// Placed here so that GLUTCallbacks.h doesn't include itself, or any not needed libraries.
#include "common.h"
#include "customGLExtras.h"
#include "GLUTCallbacks.h"
#include <Windows.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

GL_entry_point::GL_entry_point(int argc, char* argv[]) {

	glutInitWindowSize(800, 800);

	GLUTCallbacks::Init(this);

	glutInit(&argc, argv);
	glutCreateWindow("Graphics Programming App");
	
	glutDisplayFunc(GLUTCallbacks::Display);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutKeyboardUpFunc(GLUTCallbacks::KeyboardUp);
	glutSpecialFunc(GLUTCallbacks::Special);
	glutSpecialUpFunc(GLUTCallbacks::SpecialUp);

	glutMainLoop();
}

GL_entry_point::~GL_entry_point(void) {

}

void GL_entry_point::Display() {
	glClear(GL_COLOR_BUFFER_BIT); // Clears out the last frame
	// Draw vertices: 
	DrawPolygons();

	glFlush(); // Passes the scene draw to the graphics card
}

void GL_entry_point::DrawPolygons() {
	glBegin(GL_POLYGON);
	{
		Vector3 offset = Vector3();

		glColor4f(1, 0, 0, 1);
		VertexWrapper::AddVertex((Vector3(0, 0.5, 0) + offset));

		glColor4f(0, 1, 0, 1);
		VertexWrapper::AddVertex(Vector3(0.5, -0.5, 0) + offset);

		glColor4f(0, 0, 1, 1);
		VertexWrapper::AddVertex(Vector3(-0.5, -0.5, 0) + offset);
	}	
	glEnd();
}