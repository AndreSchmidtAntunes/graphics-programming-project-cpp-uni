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

	GLUTCallbacks::Init(this);

	glutInit(&argc, argv);
	glutCreateWindow("Graphics Programming App");
		
	glutDisplayFunc(GLUTCallbacks::Display);

	//glutKeyboardFunc(GLUTCallbacks::Keyboard);
	//glutKeyboardUpFunc(GLUTCallbacks::KeyboardUp);

	//glutSpecialFunc(GLUTCallbacks::Special);
	//glutSpecialUpFunc(GLUTCallbacks::SpecialUp);

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

const Vector3* ratVerts = new Vector3[62]{
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

const Poly* ratPolygons = new Poly[103]{
	Poly(new uint[3]{0, 1, 2}, 3),
	Poly(new uint[3]{1, 3, 2}, 3),
	Poly(new uint[3]{6, 7, 5}, 3),
	Poly(new uint[3]{4, 5, 7}, 3),
	Poly(new uint[3]{8, 12, 11}, 3),
	Poly(new uint[3]{11, 16, 8}, 3),
	Poly(new uint[3]{17, 8, 16}, 3),
	Poly(new uint[3]{12, 8, 17}, 3),
	Poly(new uint[3]{18, 19, 20}, 3),
	Poly(new uint[3]{22, 2, 25}, 3),
	Poly(new uint[3]{19, 23, 21}, 3),
	Poly(new uint[3]{19, 21, 22}, 3),
	Poly(new uint[3]{18, 23, 19}, 3),
	Poly(new uint[3]{26, 13, 14}, 3),
	Poly(new uint[3]{46, 44, 26}, 3),
	Poly(new uint[3]{44, 28, 26}, 3),
	Poly(new uint[3]{29, 19, 16}, 3),
	Poly(new uint[3]{27, 28, 44}, 3),
	Poly(new uint[3]{30, 6, 31}, 3),
	Poly(new uint[3]{6, 5, 31}, 3),
	Poly(new uint[3]{4, 7, 33}, 3),
	Poly(new uint[3]{26, 35, 34}, 3),
	Poly(new uint[3]{32, 5, 33}, 3),
	Poly(new uint[3]{13, 26, 23}, 3),
	Poly(new uint[3]{30, 31, 19}, 3),
	Poly(new uint[3]{20, 19, 31}, 3),
	Poly(new uint[3]{20, 31, 32}, 3),
	Poly(new uint[3]{20, 32, 29}, 3),
	Poly(new uint[3]{30, 19, 33}, 3),
	Poly(new uint[3]{29, 33, 19}, 3),
	Poly(new uint[3]{23, 26, 34}, 3),
	Poly(new uint[3]{29, 32, 33}, 3),
	Poly(new uint[3]{34, 35, 10}, 3),
	Poly(new uint[3]{20, 27, 36}, 3),
	Poly(new uint[3]{26, 28, 35}, 3),
	Poly(new uint[3]{27, 37, 36}, 3),
	Poly(new uint[3]{35, 39, 10}, 3),
	Poly(new uint[3]{38, 34, 10}, 3),
	Poly(new uint[3]{39, 35, 27}, 3),
	Poly(new uint[3]{23, 34, 38}, 3),
	Poly(new uint[3]{21, 0, 22}, 3),
	Poly(new uint[3]{12, 29, 11}, 3),
	Poly(new uint[3]{24, 1, 21}, 3),
	Poly(new uint[3]{29, 12, 10}, 3),
	Poly(new uint[3]{10, 39, 29}, 3),
	Poly(new uint[3]{21, 23, 24}, 3),
	Poly(new uint[3]{38, 24, 23}, 3),
	Poly(new uint[3]{19, 22, 25}, 3),
	Poly(new uint[3]{19, 25, 38}, 3),
	Poly(new uint[3]{39, 20, 29}, 3),
	Poly(new uint[3]{24, 38, 25}, 3),
	Poly(new uint[3]{17, 38, 12}, 3),
	Poly(new uint[3]{16, 38, 17}, 3),
	Poly(new uint[3]{11, 29, 16}, 3),
	Poly(new uint[3]{2, 22, 0}, 3),
	Poly(new uint[3]{38, 10, 12}, 3),
	Poly(new uint[3]{0, 21, 1}, 3),
	Poly(new uint[3]{24, 25, 1}, 3),
	Poly(new uint[3]{30, 7, 6}, 3),
	Poly(new uint[3]{38, 16, 19}, 3),
	Poly(new uint[3]{32, 31, 5}, 3),
	Poly(new uint[3]{25, 2, 3}, 3),
	Poly(new uint[3]{25, 3, 1}, 3),
	Poly(new uint[3]{30, 33, 7}, 3),
	Poly(new uint[3]{27, 35, 28}, 3),
	Poly(new uint[3]{4, 33, 5}, 3),
	Poly(new uint[3]{27, 20, 39}, 3),
	Poly(new uint[3]{13, 23, 18}, 3),
	Poly(new uint[3]{14, 13, 18}, 3),
	Poly(new uint[3]{9, 14, 18}, 3),
	Poly(new uint[3]{27, 44, 42}, 3),
	Poly(new uint[3]{44, 45, 42}, 3),
	Poly(new uint[3]{18, 20, 36}, 3),
	Poly(new uint[3]{36, 37, 18}, 3),
	Poly(new uint[3]{37, 9, 18}, 3),
	Poly(new uint[3]{26, 14, 46}, 3),
	Poly(new uint[3]{27, 42, 37}, 3),
	Poly(new uint[3]{46, 45, 44}, 3),
	Poly(new uint[3]{48, 47, 49}, 3),
	Poly(new uint[3]{48, 49, 40}, 3),
	Poly(new uint[3]{50, 51, 52}, 3),
	Poly(new uint[3]{52, 43, 50}, 3),
	Poly(new uint[3]{41, 51, 50}, 3),
	Poly(new uint[3]{41, 50, 43}, 3),
	Poly(new uint[3]{52, 51, 43}, 3),
	Poly(new uint[3]{43, 51, 41}, 3),
	Poly(new uint[3]{47, 48, 15}, 3),
	Poly(new uint[3]{15, 49, 47}, 3),
	Poly(new uint[3]{40, 15, 48}, 3),
	Poly(new uint[3]{40, 49, 15}, 3),
	Poly(new uint[3]{37, 45, 9}, 3),
	Poly(new uint[3]{45, 37, 42}, 3),
	Poly(new uint[3]{45, 14, 9}, 3),
	Poly(new uint[3]{45, 46, 14}, 3),
	Poly(new uint[3]{53, 54, 55}, 3),
	Poly(new uint[3]{56, 57, 58}, 3),
	Poly(new uint[3]{59, 60, 61}, 3),

	Poly(new uint[4]{2, 3, 6, 7 }, 4),
	Poly(new uint[4]{1, 3, 5, 7 }, 4),
	Poly(new uint[4]{0, 1, 4, 5 }, 4),
	Poly(new uint[4]{0, 2, 4, 6 }, 4),
	Poly(new uint[4]{0, 1, 2, 3 }, 4),
	Poly(new uint[4]{4, 5, 6, 7 }, 4),
};

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

	// pot
	glPushMatrix();
		#define POTSCALE 0.25f
		glScalef(POTSCALE, POTSCALE, POTSCALE);
		glRotatef(rot * 0, 1, 0, 0); glRotatef(rot * 2, 0, 1, 0); glRotatef(rot * 1, 0, 0, 1);

		GLExtras::AddMesh(teapot_mesh);
	glPopMatrix();
}

void GL_entry_point::Update() {
	rot += 1.0f;
	if (rot >= 360.0f)
		rot = 0.0f;
}