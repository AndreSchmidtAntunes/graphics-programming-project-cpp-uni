#include "Transform.h"

#include "GLLibs.h"
#include "Matrix4x4.h"
#include "Scene.h"

inline void Transform::setLocalPosition(const Vector3& position) {
	local_position = position;
}

inline void Transform::setLocalRotation(const Quaternion& rotation) {
	local_rotation = rotation;
}

inline void Transform::setLocalScale(const Vector3& scale) {
	local_scale = scale;
}

inline void Transform::setParent(Transform* parent, int index) {

	if (parent == this->parent) return;

	// Remove transform from old parent's child array
	this->parent->children.erase(this->parent->children.begin() + child_index);
	
	this->parent = parent;

	// Insert transform into new parent's child array
	
	this->parent->children.insert(this->parent->children.begin() + index, this);

	/// TODO: Test if the insert section works!!!
}

inline void Transform::setParent(Transform* parent) {
	setParent(parent, this->parent->children.size());
}

inline void Transform::setScene(Scene* scene, int index) {
	scene->InsertChild(this, index);
}

inline void Transform::setScene(Scene* scene) {
	scene->InsertChild(this);
}

// Getters

inline const Vector3 Transform::getWorldPosition() const {
	if (is_root)
		return local_position;
	else
		return getTransformMatrix(parent) * local_position;
}

inline const Quaternion Transform::getWorldRotation() const {
	if (is_root)
		return local_rotation;
	else
		return parent->getWorldRotation() * local_rotation;
}

inline const Vector3& Transform::getLocalScale() const {
	return local_scale;
}

inline const Vector3& Transform::getLocalPosition() const
{
	return local_position;
}

inline const Quaternion& Transform::getLocalRotation() const
{
	return local_rotation;
}

inline Transform* Transform::getParent() const {
	return parent;
}

inline const int Transform::getChildIndex() const {
	return child_index;
}

inline Scene* Transform::getScene() const {
	return scene;
}

inline const std::vector<Transform*> Transform::getAllChildren() const {
	return children;
}

inline Transform* Transform::getChild(const size_t index) const {
	return children[index];
}

inline const Matrix4x4 getTransformMatrix(Transform* transform) {
	if (transform->getIsRoot())
		return getLocalTransformMatrix(transform);
	else
		return getTransformMatrix(transform->getParent()) * getLocalTransformMatrix(transform);
}

inline const Matrix4x4 getLocalTransformMatrix(Transform* transform) {
	return Matrix4x4::ScaleMatrix(transform->getLocalScale()) * Matrix4x4::RotationMatrix(transform->getLocalRotation()) * Matrix4x4::TranslationMatrix(transform->getLocalPosition());
}