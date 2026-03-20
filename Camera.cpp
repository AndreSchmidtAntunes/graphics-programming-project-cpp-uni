#include "Camera.h"

#include "Matrix4x4.h"

void Camera::Rotate(Vector3 rotation)
{
	up = Matrix4x4::RotationMatrix(Vector3::Down, rotation.x) *	  // rotate x
		Matrix4x4::RotationMatrix(Vector3::Right, rotation.y) *	  // rotate y
		Matrix4x4::RotationMatrix(Vector3::Forward, rotation.z) * // rotate z
		up;
}

