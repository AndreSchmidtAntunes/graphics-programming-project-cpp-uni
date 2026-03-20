#pragma once

#include "GL_entry_point.h"

class GL_entry_point;

namespace GLUTCallbacks {

	void Init(GL_entry_point* new_entry_point);

	GL_entry_point* GetEntryPoint();

	void Display();

	void Timer(int refreshRate);
}