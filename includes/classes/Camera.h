#pragma once

#include "Matrix3x3.h"
#include "UserInput.h"

template <typename T = double>
class Camera {
public:

	static_assert(std::is_floating_point<T>::value,
		"class T can only be a floating point type, as it is the type used for 3D calculations. (E.g: float, double, half)");

	Vectors::Vector3<T> position, rotation;
	Camera(Vectors::Vector3<T> eye, Vectors::Vector3<T> position, Vectors::Vector3<T> up, Vectors::Vector3<T> right) : eye(eye), position(position), up(up), right(right) {}
	
	Camera(void) : Camera(Vectors::Vector3<T>::Forward, Vectors::Vector3<T>::Zero, Vectors::Vector3<T>::Up, Vectors::Vector3<T>::Right) {}
	~Camera(void) {}

	void Rotate(const Vectors::Vector3<T>& rotation);

	void RotateFirstPerson(const Vectors::Vector3<T>& rotation);

	//void setRotationFirstPerson(const float pitch, const float yaw, const float roll);

//private:
	union {
		Vectors::Vector3<T> eye;
		Vectors::Vector3<T> forward;
	};

	Vectors::Vector3<T> up;
	Vectors::Vector3<T> right;

private:
	Matrix3x3<T> rotation_matrix = Matrix3x3<T>::identity;
};	