#pragma once

#include "GL_entry_point.h"

class GL_entry_point;

namespace GLUTCallbacks {

	void Init(GL_entry_point* new_entry_point);

	void Display();

	void Timer(int refreshRate);
}