#include "Transform.h"

#include "Matrix4x4.h"
#include "Scene.h"

// Getters

inline const Matrix4x4 getLocalTransformMatrix(Transform* const transform) {
	return Matrix4x4::ScaleMatrix(transform->local_scale) * Matrix4x4::RotationMatrix(transform->local_rotation) * Matrix4x4::TranslationMatrix(transform->local_position);
}

inline const Matrix4x4 getTransformMatrix(Transform* const transform) {
	if (transform->getIsRoot())
		return getLocalTransformMatrix(transform);
	else
		return getTransformMatrix(transform->getParent()) * getLocalTransformMatrix(transform);
}

const Vector3 Transform::getWorldPosition() const {
	if (is_root)
		return local_position;
	else
		return getTransformMatrix(parent) * local_position;
}

const Quaternion Transform::getWorldRotation() const {
	if (is_root)
		return local_rotation;
	else
		return parent->getWorldRotation() * local_rotation;
}

Transform::Transform(const char* name, Transform* const parent, const size_t child_index, const Vector3& local_position, const Quaternion& local_rotation, const Vector3& local_scale)
: name(name), local_position(local_position), local_rotation(local_rotation), local_scale(local_scale), is_root(false)
{
	scene_transform_id = parent->scene->GetNextAvailableObjectID();
	this->parent = parent;

	if (child_index >= parent->childCount()) {
		this->child_index = parent->childCount();
		parent->children.push_back(this);
	}
	else {
		this->child_index = child_index;
		parent->children.insert(parent->children.begin() + child_index, this);
	}

	this->scene = parent->scene;
	children.clear();
}
Transform::Transform(const char* name, Transform* const parent, const Vector3& local_position, const Quaternion& local_rotation, const Vector3& local_scale)
: name(name), local_position(local_position), local_rotation(local_rotation), local_scale(local_scale), is_root(false)
{
	scene_transform_id = parent->scene->GetNextAvailableObjectID();
	this->parent = parent;

	this->child_index = parent->childCount();
	parent->children.push_back(this);
	this->scene = parent->scene;
	children.clear();
};



