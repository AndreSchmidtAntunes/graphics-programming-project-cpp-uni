#include "Transform.h"

#include "Matrix4x4.h"
#include "Scene.h"

// Getters

const Matrix4x4 Transform::getLocalTransformMatrix() const {
	return Matrix4x4::TranslationMatrix(local_position) * Matrix4x4::RotationMatrix(local_rotation) * Matrix4x4::ScaleMatrix(local_scale);
}

const Matrix4x4 Transform::getWorldTransformMatrix() const {

	if (_parent->isRoot())
		return getLocalTransformMatrix();
	else if (isRoot())
		return Matrix4x4::identity;
	else 
		return _parent->getWorldTransformMatrix() * getLocalTransformMatrix();
}

const Vector3 Transform::getWorldPosition() const {

	if (is_root) return Vector3::Zero;

	else return getWorldTransformMatrix().ApplyTransform();
}

const Quaternion Transform::getWorldRotation() const {
	if (_parent->isRoot())
		return local_rotation;
	else
		return _parent->getWorldRotation() * local_rotation;
}

Transform::Transform(const char* name, Transform* const parent, const size_t child_index, const Vector3& local_position, const Quaternion& local_rotation, const Vector3& local_scale)
: name(name), local_position(local_position), local_rotation(local_rotation), local_scale(local_scale), is_root(false)
{
	scene_transform_id = parent->scene->GetNextAvailableObjectID();
	this->_parent = parent;

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
	this->_parent = parent;

	this->child_index = parent->childCount();
	parent->children.push_back(this);
	this->scene = parent->scene;
	children.clear();
};



