#pragma once

#include "Vector3.h"
#include "Vector2.h"
#include "Matrix3x3.h"
#include "Quaternion.h"
#include "UserInput.h"
#include <type_traits>

class Camera {
public:
	Vector3 position, euler_rotation;

	Camera(Vector3 eye, Vector3 position, Vector3 up, Vector3 right) : eye(eye), position(position), up(up), right(right) {}
	
	Camera(void) : Camera(Vector3::Forward, Vector3::Zero, Vector3::Up, Vector3::Right) {}
	~Camera(void) {}

	void RotateFirstPerson(const Vector3& rotation);
	void Rotate(const Quaternion& rotation);

	void UpdateDirections();

//private:

	union {
		Vector3 eye;
		Vector3 forward;
	};
	Vector3 up, right;

	Quaternion rotation;
};	