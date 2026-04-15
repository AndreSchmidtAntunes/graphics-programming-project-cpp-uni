#pragma once

#include "Matrix3x3.h"
#include "Vector3.h"
#include <type_traits>

#define THIS_TYPE float

class Camera {
public:

	static_assert(std::is_arithmetic<THIS_TYPE>::value,
		"class T can only be a floating point type, as it is the type used for 3D calculations. (E.g: float, double, half)");

	Vector3 position, rotation;

	Camera(Vector3 eye, Vector3 position, Vector3 up, Vector3 right) : eye(eye), position(position), up(up), right(right) {}
	
	Camera(void) : Camera(Vector3::Forward, Vector3::Zero, Vector3::Up, Vector3::Right) {}
	~Camera(void) {}

	void Rotate(const Vector3& rotation);

	void RotateFirstPerson(const Vector3& rotation);

//private:

	union {
		Vector3 eye;
		Vector3 forward;
	};

	Vector3 up;
	Vector3 right;

private:
	Matrix3x3 rotation_matrix = Matrix3x3::identity;
};	