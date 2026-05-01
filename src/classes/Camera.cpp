#include "Camera.h"

#include "Matrix3x3.h"
#include "Quaternion.h"

#define DEG2RAD 0.017453292f
#define HALF_PI 1.570796327f

#include <iostream>

void Camera::Rotate(const Quaternion& rotation)
{
	this->rotation *= rotation;
	UpdateDirections();
}

void Camera::UpdateDirections() {
	const Matrix3x3 rot_matrix = Matrix3x3::RotationMatrix(rotation);
	up		= rot_matrix * Vector3::Up;
	forward = rot_matrix * Vector3::Forward;
	right	= rot_matrix * Vector3::Right;
	euler_rotation = rotation.Euler();
}

void Camera::RotateFirstPerson(const Vector3& look_dir) {
	float x =  -look_dir.y * DEG2RAD;
	float y =  -look_dir.x * DEG2RAD;

	Quaternion world_rot_horr = Quaternion::Euler(0.0f, y, 0.0f);

	rotation = rotation * rotation.Inverse() * world_rot_horr * rotation;
	rotation = rotation * Quaternion::Euler(x, 0.0f, 0.0f);

	UpdateDirections();
}