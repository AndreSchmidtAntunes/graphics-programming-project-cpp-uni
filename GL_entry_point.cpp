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

	glutPostRedisplay();
	glutTimerFunc(REFRESH_RATE, GLUTCallbacks::Timer, 0);

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

const Vector3 ratModel[63] = {
	Vector3(-6.723, -7.608, -5.98),//0
	Vector3(-7.597,-5.384,-5.98),
	Vector3(-4.646,-6.38,-5.98),
	Vector3(-4.531,-1.322,-5.98),
	Vector3(-0.884,-1.322,-5.98),
	Vector3(2.182,-5.384,-5.98),//5
	Vector3(1.308,-7.608,-5.98),
	Vector3(-0.769,-6.38,-5.98),
	Vector3(-2.708,36.239,-4.1),
	Vector3(-2.708,-21.273,-3.433),
	Vector3(-2.708,1.512,1.992),//10
	Vector3(-1.48,1.93,-3.995),
	Vector3(-2.708,1.93,-2.729),
	Vector3(-6.524,-16.875,-4.24),
	Vector3(-5.785,-20.535,-3.15),
	Vector3(-4.669,-17.696,-4.504),//15
	Vector3(-2.708,1.826,-5.104),
	Vector3(-3.935,1.93,-3.995),
	Vector3(-2.708,-16.039,-4.645),
	Vector3(-2.708,-8.249,-5.068),
	Vector3(3.585,-8.257,-3.921),//20
	Vector3(-6.1513,-5.923,-4.4678),
	Vector3(-6.0769,-5.8915,-4.4817),
	Vector3(-9,-8.257,-3.921),
	Vector3(-6.1739,-5.8587,-4.4645),
	Vector3(-6.0684,-5.6859,-4.4857),//25
	Vector3(-6.046,-22.518,1.4),
	Vector3(0.63,-22.518,1.4),
	Vector3(-2.708,-23.407,3.339),
	Vector3(3.095,-1.593,-4.089),
	Vector3(0.662,-5.8914,-4.4816),//30
	Vector3(0.7363,-5.923,-4.4677),
	Vector3(0.7588,-5.8587,-4.4644),
	Vector3(0.6535,-5.6862,-4.4856),
	Vector3(-8.479,-8.04,4.723),
	Vector3(-2.708,-8.04,8.022),//35
	Vector3(1.109,-16.875,-4.24),
	Vector3(0.37,-20.535,-3.15),
	Vector3(-8.51,-1.593,-4.089),
	Vector3(3.064,-8.04,4.723),
	Vector3(-3.691,-14.176,-5.849),//40
	Vector3(-1.724,-14.176,-5.849),
	Vector3(-2.102,-29.629,-2.812),
	Vector3(0.425,-17.525,-5.849),
	Vector3(-2.708,-30.218,-2.581),
	Vector3(-2.708,-29.073,-3.767),//45
	Vector3(-3.313,-29.629,-2.812),
	Vector3(-5.024,-19.21,-5.849),
	Vector3(-3.476,-18.13,-5.849),
	Vector3(-5.84,-17.525,-5.849),
	Vector3(-0.746,-17.696,-4.504),//50
	Vector3(-1.939,-18.13,-5.849),
	Vector3(-0.391,-19.21,-5.849),
	Vector3(-2,-23,3),
	Vector3(0,-23,2),
	Vector3(-1,-23,5),//55
	Vector3(-6,-23,2),
	Vector3(-4,-23,3),
	Vector3(-5,-23,5),
	Vector3(-3.8,-30,-2.5),
	Vector3(-1.8,-30,-2.5),//60
	Vector3(-2.8,-30,-3.5)
};

const Colour ratModel_col[63] = {};

void GL_entry_point::DrawPolygons() {
	glPushMatrix();

		glRotatef(rot* 4, 1, 0, 0);

		glRotatef(rot * 2, 0, 1, 0);
		glRotatef(rot * 1, 0, 0, 1);

		glScalef(0.5f, 0.5f, 0.5f);

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

		//Poly triangle = Poly(points, colours, 3);

		const int tri_count = 63 / 3;

		Poly rat_mesh[tri_count];

		int tri = 0;

		for (int i = 0; i < tri_count; i++) {
			rat_mesh[i] = Poly(ratModel + tri, 3);
			tri += 3;
		}

		GLExtras::AddPolygons(rat_mesh, tri_count);

		Poly triangle = Poly(points, colours ,3);
		GLExtras::AddPolygon(triangle);

		//glBegin(GL_POLYGON);
		//	glColor3f(1, 1, 1);

		//	GLExtras::AddVertex(Vector3(0, 0.5, 0));

		//	glColor4f(1, 0, 0, 1);
		//	glVertex3d(0, 0.5, 0);
		//	glColor3f(1,1,1);

		//	GLExtras::AddVertex(Vector3(0.5, -0.5, 0));
		//	glColor4f(0, 1, 0, 1);

		//	glVertex3d(0.5, -0.5, 0);

		//	glColor3f(1, 1, 1);

		//	GLExtras::AddVertex(Vector3(-0.5, -0.5, 0));
		//	glColor4f(0, 0, 1, 1);

		//	glVertex3d(-0.5, -0.5, 0);

		//glEnd();

	glPopMatrix();
}

void GL_entry_point::Update() {
	rot += 1.0f;
	if (rot >= 360.0f)
		rot = 0.0f;
}