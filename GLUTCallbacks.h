#pragma once

#include "GL_entry_point.h"

class GL_entry_point;

namespace GLUTCallbacks {

	void Init(GL_entry_point* new_entry_point);

	void Display();
	void Keyboard(unsigned char, int, int);
	void KeyboardUp(unsigned char, int, int);

	void Special(int, int, int);
	void SpecialUp(int, int, int);
}