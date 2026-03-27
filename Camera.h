#pragma once

#include "Matrix3x3.h"
#include "UserInput.h"

template <typename T = double>
class Camera {
public:

	static_assert(std::is_floating_point<T>::value,
		"class T can only be a floating point type, as it is the type used for 3D calculations. (E.g: float, double, half)");

	Vector3<T> position, rotation;
	Camera(Vector3<T> eye, Vector3<T> position, Vector3<T> up, Vector3<T> right) : eye(eye), position(position), up(up), right(right) {}
	
	Camera(void) : Camera(Vector3<T>::Forward, Vector3<T>::Zero, Vector3<T>::Up, Vector3<T>::Right) {}
	~Camera(void) {}

	void Rotate(const Vector3<T>& rotation);

	void RotateFirstPerson(const Vector3<T>& rotation);

	//void setRotationFirstPerson(const float pitch, const float yaw, const float roll);

//private:
	union {
		Vector3<T> eye;
		Vector3<T> forward;
	};

	Vector3<T> up;
	Vector3<T> right;

private:
	Matrix3x3<T> rotation_matrix = Matrix3x3<T>::identity;
};	