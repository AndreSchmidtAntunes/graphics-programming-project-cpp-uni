#include "Camera.h"

#include "GLExtras.h"
#include "Matrix3x3.h"
#include "Mesh.h"
#include "Quaternion.h"
#include "Scene.h"
#include "Transform.h"

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

void Camera::setScene(Scene* const scene) {
	if (_scene)
		_scene->setCamera(nullptr);
	scene->setCamera(this);
	_scene = scene;
}

void Camera::DrawScene() const {

	if (!_scene) {
		std::cerr << "[!] ERROR: No Scene has been set in the current camera. DrawScene() failed." << std::endl;
		return;
	}

	glPushMatrix();
	glLoadIdentity();

	Vector3 camera_target;

	if (isTargetSelected())
		camera_target = focused_transform->getWorldPosition();
	else
		camera_target = position - forward;

	GLExtras::LookAt(position, camera_target, up);

	for (auto child : _scene->root->getChildren()) {
		DrawFamilyHierarchy(child);
	}

	glPopMatrix();
}

const bool Camera::isTargetSelected() const {
	return (focused_transform != nullptr) && (focused_transform->getScene() == _scene) && (focused_transform != _scene->root);
}


void Camera::DrawFamilyHierarchy(const Basic_Transform* const parent) const {
	glPushMatrix();

	GLExtras::PerformTransformation(parent->local_position, parent->local_rotation, parent->local_scale);

	// switch case for drawing light transform and model transform
	
	parent->Draw();
	
	for (auto child : parent->getChildren()) {
		DrawFamilyHierarchy(child);
	}
	glPopMatrix();
}

void Camera::RotateFirstPerson(const Vector3& look_dir) {

	if (isTargetSelected()) return; // don't allow rotating the camera if it is locked on an object

	float x =  -look_dir.y * DEG2RAD;
	float y =  -look_dir.x * DEG2RAD;

	Quaternion world_rot_horr = Quaternion::Euler(0.0f, y, 0.0f);

	rotation = rotation * rotation.Inverse() * world_rot_horr * rotation;
	rotation = rotation * Quaternion::Euler(x, 0.0f, 0.0f);

	UpdateDirections();
}