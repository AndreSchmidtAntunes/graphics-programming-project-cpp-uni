#include "Camera.h"

#include "Matrix3x3.h"

#define DEG2RAD 0.017453292f
#define HALF_PI 1.570796327f

template <typename T>
void Camera<T>::Rotate(const Vectors::Vector3<T>& rotation)
{
	//this->rotation += rotation;

	Matrix3x3<T> yaw  =  Matrix3x3<T>::RotationMatrix(Vectors::Up, rotation.x * DEG2RAD);
	Matrix3x3<T> pitch = Matrix3x3<T>::RotationMatrix(Vectors::Left, rotation.y * DEG2RAD);
	Matrix3x3<T> roll =  Matrix3x3<T>::RotationMatrix(Vectors::Back, rotation.z * DEG2RAD);

	rotation_matrix *= yaw * pitch * roll;

	this->up = rotation_matrix * Vectors::Up;
	this->forward = rotation_matrix * Vectors::Forward;
	this->right = rotation_matrix * Vectors::Right;
}

/// <summary>
/// 
/// </summary>
/// <param name="rotation"> x = yaw z = pitch, y = roll </param>
template <typename T>
void Camera<T>::RotateFirstPerson(const Vectors::Vector3<T>& rotation) {

	Matrix3x3<T> yaw = Matrix3x3<T>::RotationMatrix(Vectors::Down, rotation.x * DEG2RAD);
	Matrix3x3<T> pitch = Matrix3x3<T>::RotationMatrix(Vectors::Left, rotation.y * DEG2RAD);
	Matrix3x3<T> roll = Matrix3x3<T>::RotationMatrix(Vectors::Back, rotation.z * DEG2RAD);
	
	Matrix3x3<T> fpsRotMatrix = pitch * roll;
	
	rotation_matrix *= yaw * pitch * roll;

	this->up = rotation_matrix * Vectors::Up;
	this->forward = rotation_matrix * Vectors::Forward;
	this->right = rotation_matrix * Vectors::Right;

	//rotation_matrix *= (pitch * roll) * yaw;
	//rotation_matrix *= Matrix3x3<T>::RotationMatrix(Vector3<T>::Left, rotation.y * DEG2RAD);

	//this->up = rotation_matrix * Vector3<T>::Up;
	//this->forward = rotation_matrix * Vector3<T>::Forward;	
	//this->right = rotation_matrix * Vector3<T>::Right;	

	//this->right = Matrix3x3<T>::RotationMatrix(Vector3<T>::Down, HALF_PI) * forward;

}