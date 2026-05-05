#pragma once

#include "Vector3.h"
#include "Quaternion.h"

class Scene;
class Transform;

class Camera {

	void DrawFamilyHierarchy(const Transform* const parent) const;

	Scene* _scene = nullptr;

public:

	Vector3 position, euler_rotation;

	union {
		Vector3 eye;
		Vector3 forward;
	};
	Vector3 up, right;

	Quaternion rotation;

	Transform* focused_transform = nullptr;

	Camera(Vector3 eye, Vector3 position, Vector3 up, Vector3 right, Scene* const scene = nullptr) 
		: eye(eye), position(position), up(up), right(right), _scene(scene) {}
	
	Camera(Scene* const scene = nullptr) 
		: Camera(Vector3::Forward, Vector3::Zero, Vector3::Up, Vector3::Right, scene) {
		
	}

	~Camera(void) { }

	void RotateFirstPerson(const Vector3& look_dir);
	void Rotate(const Quaternion& rotation);

	void UpdateDirections();

	void DrawScene() const;

	const bool isTargetSelected() const;

	// scene needs access to camera's private scene pointer, 
	// to keep parity between their pointers to each other.
	friend class Scene; 

	inline const Scene* const getScene() const { return _scene; }
	void setScene(Scene* const scene);

//private:
};	