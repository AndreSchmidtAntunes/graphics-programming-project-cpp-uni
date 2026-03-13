#include "GLUTCallbacks.h"

#include <iostream>
#include "GLExtras.h"

namespace GLUTCallbacks {

	namespace {
		static GL_entry_point* entry_point = nullptr;
	}

	void Init(GL_entry_point* new_entry_point) {
		entry_point = new_entry_point;
	}

	void Display() {
		if (entry_point != nullptr) {
			entry_point->Display();
		}
	}

	void Timer(int refreshRate) {

		int updateDuration = glutGet(GLUT_ELAPSED_TIME);

		entry_point->Update();

		updateDuration = glutGet(GLUT_ELAPSED_TIME) - updateDuration;
		
		glutTimerFunc(GLExtras::REFRESHRATE - updateDuration, Timer, GLExtras::REFRESHRATE);
		glutPostRedisplay();
	}
}	