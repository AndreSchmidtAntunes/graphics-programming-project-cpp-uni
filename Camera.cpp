#include "Camera.h"
#include "Matrix3x3.h"

#define DEG2RAD (0.017453292f)

#include <iostream>

void Camera::Rotate(const Vector3& rotation)
{

	//this->rotation += rotation;

	Matrix3x3 yaw = Matrix3x3::RotationMatrix(Vector3::Up, -rotation.x * DEG2RAD);
	Matrix3x3 pitch = Matrix3x3::RotationMatrix(Vector3::Forward, -rotation.y * DEG2RAD);
	Matrix3x3 roll = Matrix3x3::RotationMatrix(Vector3::Right, -rotation.z * DEG2RAD);

	Matrix3x3 RotationMatrix = yaw * pitch * roll;

	this->up *= RotationMatrix; 	this->up.Normalise();
	this->forward *= RotationMatrix;	this->forward.Normalise();

	//if (this->rotation.x > 360)
	//	this->rotation.x -= 360;

	//else if (this->rotation.x < 0)
	//	this->rotation.x += 360;

	//if (this->rotation.y > 360)
	//	this->rotation.y -= 360;

	//else if (this->rotation.y < 0)
	//	this->rotation.y += 360;

	//if (this->rotation.z > 360)
	//	this->rotation.z -= 360;

	//else if (this->rotation.z < 0)
	//	this->rotation.z += 360;
}

/// <summary>
/// 
/// </summary>
/// <param name="rotation"> x = yaw z = pitch, y = roll </param>
void Camera::RotateFirstPerson(const Vector3& rotation) {

	Matrix3x3 yaw = Matrix3x3::RotationMatrix(Vector3::Up, -rotation.x * DEG2RAD);
	Matrix3x3 pitch = Matrix3x3::RotationMatrix((this->right), -rotation.y * DEG2RAD);
	Matrix3x3 roll = Matrix3x3::RotationMatrix((this->forward), -rotation.z * DEG2RAD);

	Matrix3x3 RotationMatrix =/* yaw * pitch * */roll * pitch * yaw;

	this->up *= RotationMatrix;
	//this->forward = Matrix3x3::RotationMatrix(Vector3::Right, 90 * DEG2RAD) * up;
	this->forward *= RotationMatrix;
	this->right = Matrix3x3::RotationMatrix(Vector3::Up, 90 * DEG2RAD) * forward;

	std::cout  << " up: " << up << " forward: " << forward << " right: " << right << std::endl;

	if (up.x > 1)
		up.x -= 1;
	else if (up.x < -1)
		up.x += 1;
	if (up.y > 1)
		up.y -= 1;
	else if(up.y < -1)
		up.y += 1;
	if (up.z > 1)
		up.z -= 1;
	else if(up.z < -1)
		up.z += 1;

	if (forward.x > 1)
		forward.x -= 1;
	else if (forward.x < -1)
		forward.x += 1;
	if (forward.y > 1)
		forward.y -= 1;
	else if (forward.y < -1)
		forward.y += 1;
	if (forward.z > 1)
		forward.z -= 1;
	else if (forward.z < -1)
		forward.z += 1;
}

