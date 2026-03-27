#include "Camera.h"
#include "Matrix3x3.h"

#define DEG2RAD (0.017453292f)
#define HALF_PI 1.57079632679f

#include <iostream>

void Camera::Rotate(const Vector3& rotation)
{

	//this->rotation += rotation;

	Matrix3x3 yaw  =  Matrix3x3::RotationMatrix(Vector3::Up, rotation.x * DEG2RAD);
	Matrix3x3 pitch = Matrix3x3::RotationMatrix(Vector3::Left, rotation.y * DEG2RAD);
	Matrix3x3 roll =  Matrix3x3::RotationMatrix(Vector3::Back, rotation.z * DEG2RAD);

	rotation_matrix *= yaw * pitch * roll;

	this->up = rotation_matrix * Vector3::Up;
	this->forward = rotation_matrix * Vector3::Forward;
	this->right = rotation_matrix * Vector3::Right;

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

	Matrix3x3 yaw = Matrix3x3::RotationMatrix(Vector3::Down, rotation.x * DEG2RAD);
	Matrix3x3 pitch = Matrix3x3::RotationMatrix(Vector3::Left, rotation.y * DEG2RAD);
	Matrix3x3 roll = Matrix3x3::RotationMatrix(Vector3::Back, rotation.z * DEG2RAD);
	
	Matrix3x3 fpsRotMatrix = pitch * roll;
	

	//rotation_matrix *= (pitch * roll) * yaw;
	//rotation_matrix *= Matrix3x3::RotationMatrix(Vector3::Left, rotation.y * DEG2RAD);

	//this->up = rotation_matrix * Vector3::Up;
	//this->forward = rotation_matrix * Vector3::Forward;	
	//this->right = rotation_matrix * Vector3::Right;	

	//this->right = Matrix3x3::RotationMatrix(Vector3::Down, HALF_PI) * forward;

	std::cout  << " up: " << up << " forward: " << forward << " right: " << right << std::endl;

	//if (up.x > 1)
	//	up.x -= 1;
	//else if (up.x < -1)
	//	up.x += 1;
	//if (up.y > 1)
	//	up.y -= 1;
	//else if(up.y < -1)
	//	up.y += 1;
	//if (up.z > 1)
	//	up.z -= 1;
	//else if(up.z < -1)
	//	up.z += 1;
	//if (forward.x > 1)
	//	forward.x -= 1;
	//else if (forward.x < -1)
	//	forward.x += 1;
	//if (forward.y > 1)
	//	forward.y -= 1;
	//else if (forward.y < -1)
	//	forward.y += 1;
	//if (forward.z > 1)
	//	forward.z -= 1;
	//else if (forward.z < -1)
	//	forward.z += 1;
}