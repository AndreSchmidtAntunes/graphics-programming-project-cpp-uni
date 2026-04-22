#include "Camera.h"

#include "Matrix3x3.h"

#define DEG2RAD 0.017453292f
#define HALF_PI 1.570796327f

#include <iostream>

void Camera::Rotate(const Vector3& rotation)
{
	//this->rotation += rotation;

	Matrix3x3 yaw  =  Matrix3x3::RotationMatrix(Vector::Up, rotation.x * DEG2RAD);
	Matrix3x3 pitch = Matrix3x3::RotationMatrix(Vector::Left, rotation.y * DEG2RAD);
	Matrix3x3 roll =  Matrix3x3::RotationMatrix(Vector::Back, rotation.z * DEG2RAD);

	rotation_matrix *= yaw * pitch * roll;

	this->up = rotation_matrix * Vector3::Up;
	this->forward = rotation_matrix * Vector3::Forward;
	this->right = rotation_matrix * Vector3::Right;
}

/// <param name="rotation"> x = yaw z = pitch, y = roll </param>
void Camera::RotateFirstPerson(const Vector3& rotation) {

	Matrix3x3 yaw = Matrix3x3::RotationMatrix(Vector3::Down, rotation.x * DEG2RAD);
	Matrix3x3 pitch = Matrix3x3::RotationMatrix(Vector3::Left, rotation.y * DEG2RAD);
	Matrix3x3 roll = Matrix3x3::RotationMatrix(Vector3::Back, rotation.z * DEG2RAD);

	rotation_matrix *= yaw * pitch * roll;

	this->up = rotation_matrix * Vector3::Up;
	this->forward = rotation_matrix * Vector3::Forward;	
	this->right = rotation_matrix * Vector3::Right;	

	this->right = Matrix3x3::RotationMatrix(Vector3::Down, HALF_PI) * forward;
}