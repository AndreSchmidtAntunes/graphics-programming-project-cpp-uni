#pragma once

#include "Vector3.h"
#include "UserInput.h"

class Camera {
public:

	Vector3 eye, position, up;
	Camera(Vector3 eye, Vector3 position, Vector3 up) : eye(eye), position(position), up(up) {}

	void Rotate(Vector3 rotation);

	void RotateRight();
	void RotateLeft();
	void RotateUp();
	void RotateDown();
};