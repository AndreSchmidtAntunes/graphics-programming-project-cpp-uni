#pragma once

#include "Transform.h"
#include "Camera.h"

class User {
	Transform* selected = nullptr;
	Transform* hovered = nullptr;

	bool lock_camera_to_selected = false;
};

