#pragma once

#include "Vector3.h"

class Camera {
public:

	Vector3 eye, position, up;
	Camera(Vector3 eye, Vector3 position, Vector3 up) : eye(eye), position(position), up(up) {}
};