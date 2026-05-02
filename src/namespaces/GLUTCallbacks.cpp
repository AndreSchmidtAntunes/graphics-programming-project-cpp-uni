#include "GLUTCallbacks.h"

#include <iostream>
#include "GLExtras.h"
#include "UserInput.h"

namespace GLUTCallbacks {

	static GL_entry_point* entry_point = nullptr;

	GL_entry_point& GetEntryPoint() {
		return *entry_point;
	}

	void Init(GL_entry_point* new_entry_point) {
		if (entry_point == nullptr) {
			entry_point = new_entry_point;
		}
	}

	void UpdateLoop() {
		if (entry_point != nullptr) {
			entry_point->Render();
		}
	}

	int old_elapsed_time = 0;

	void Timer(int refreshRate) {

		int updateDuration = glutGet(GLUT_ELAPSED_TIME);

		entry_point->Update();

		UserInput::RunAllActiveCallbacks();

		updateDuration = glutGet(GLUT_ELAPSED_TIME) - updateDuration;
		
		glutTimerFunc(GLExtras::REFRESHRATE - updateDuration, Timer, GLExtras::REFRESHRATE);

		entry_point->deltaTime = (glutGet(GLUT_ELAPSED_TIME) - old_elapsed_time) * 0.001f;
		old_elapsed_time = glutGet(GLUT_ELAPSED_TIME);
	}
}	