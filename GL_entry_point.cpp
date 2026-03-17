#include "GL_entry_point.h"

#include "common.h" 
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

GL_entry_point::GL_entry_point(int argc, char* argv[]) {

	rot = 0.0f;

	glutInitWindowSize(800, 800);

	glutInit(&argc, argv);
	glutCreateWindow("Graphics Programming App");
		
	glutDisplayFunc(GLUTCallbacks::Display);

	GLUTCallbacks::Init(this);
	UserInput::Init();

	glutTimerFunc(REFRESH_RATE, GLUTCallbacks::Timer, REFRESH_RATE);

	glutInitDisplayMode(GLUT_DOUBLE);

	glutMainLoop();
}

GL_entry_point::~GL_entry_point(void) {

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

		GLExtras::AddMesh(rat_mesh);
	
	glPopMatrix();
}

void GL_entry_point::Update() {
	rot += 1.0f;
	if (rot >= 360.0f)
		rot = 0.0f;
}