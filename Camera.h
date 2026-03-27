#pragma once

#include "Vector3.h"
#include "Matrix3x3.h"
#include "UserInput.h"

class Camera {
public:

	Vector3 position, rotation;
	Camera(Vector3 eye, Vector3 position, Vector3 up, Vector3 right) : eye(eye), position(position), up(up), right(right) {}
	~Camera() {}

	void Rotate(const Vector3& rotation);

	void RotateFirstPerson(const Vector3& rotation);

	//void setRotationFirstPerson(const float pitch, const float yaw, const float roll);

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