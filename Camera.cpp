#include "Camera.h"

#include "Matrix3x3.h"

#define DEG2RAD 0.017453292f
#define HALF_PI 1.570796327f

template <typename T>
void Camera<T>::Rotate(const Vector3<T>& rotation)
{
	//this->rotation += rotation;

	Matrix3x3<T> yaw  =  Matrix3x3<T>::RotationMatrix(Vector3<T>::Up, rotation.x * DEG2RAD);
	Matrix3x3<T> pitch = Matrix3x3<T>::RotationMatrix(Vector3<T>::Left, rotation.y * DEG2RAD);
	Matrix3x3<T> roll =  Matrix3x3<T>::RotationMatrix(Vector3<T>::Back, rotation.z * DEG2RAD);

	rotation_matrix *= yaw * pitch * roll;

	this->up = rotation_matrix * Vector3<T>::Up;
	this->forward = rotation_matrix * Vector3<T>::Forward;
	this->right = rotation_matrix * Vector3<T>::Right;
}

/// <summary>
/// 
/// </summary>
/// <param name="rotation"> x = yaw z = pitch, y = roll </param>
template <typename T>
void Camera<T>::RotateFirstPerson(const Vector3<T>& rotation) {

	Matrix3x3<T> yaw = Matrix3x3<T>::RotationMatrix(Vector3<T>::Down, rotation.x * DEG2RAD);
	Matrix3x3<T> pitch = Matrix3x3<T>::RotationMatrix(Vector3<T>::Left, rotation.y * DEG2RAD);
	Matrix3x3<T> roll = Matrix3x3<T>::RotationMatrix(Vector3<T>::Back, rotation.z * DEG2RAD);
	
	Matrix3x3<T> fpsRotMatrix = pitch * roll;
	
	rotation_matrix *= yaw * pitch * roll;

	this->up = rotation_matrix * Vector3<T>::Up;
	this->forward = rotation_matrix * Vector3<T>::Forward;
	this->right = rotation_matrix * Vector3<T>::Right;

	//rotation_matrix *= (pitch * roll) * yaw;
	//rotation_matrix *= Matrix3x3<T>::RotationMatrix(Vector3<T>::Left, rotation.y * DEG2RAD);

	//this->up = rotation_matrix * Vector3<T>::Up;
	//this->forward = rotation_matrix * Vector3<T>::Forward;	
	//this->right = rotation_matrix * Vector3<T>::Right;	

	//this->right = Matrix3x3<T>::RotationMatrix(Vector3<T>::Down, HALF_PI) * forward;

}