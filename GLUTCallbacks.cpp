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

		entry_point->Update();

		glutPostRedisplay();
		glutTimerFunc(GLExtras::REFRESHRATE, Timer, 0);
	}

	void Keyboard(unsigned char c, int mouse_x, int mouse_y) {
		std::cout << "down: " << c << ": x=" << mouse_x << " y=" << mouse_y << std::endl;
		switch (c) {
		case 'w': {

		}
		}
	}

	void KeyboardUp(unsigned char c, int mouse_x, int mouse_y) {
		std::cout << "up: " << c << ": x=" << mouse_x << " y=" << mouse_y << std::endl;

	}

	void Special(int key, int mouse_x, int mouse_y) {

	}

	void SpecialUp(int key, int mouse_x, int mouse_y) {

	}


}	