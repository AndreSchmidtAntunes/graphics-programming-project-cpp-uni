#include "Transform.h"
#include "Matrix3x3.h"

void Transform::SetOnChangedFunc(void (*callback)(Vector3, Vector3, Vector3)) {
	anyChangedFunc = callback;
}


void Transform::SetOnPositionChangedFunc(void (*callback)(Vector3)) {
	posChangedFunc = callback;
}


void Transform::SetOnRotationChangedFunc(void (*callback)(Vector3)) {
	rotChangedFunc = callback;
}

void Transform::SetOnScaleChangedFunc(void (*callback)(Vector3)) {
	scaleChangedFunc = callback;
}

// Setters

inline void Transform::setPosition(Vector3 position) {
	anyChangedFunc(position, rotation, scale);
	posChangedFunc(position);
	this->position = position;
}

inline void Transform::setRotation(Vector3 position) {
	anyChangedFunc(position, rotation, scale);
	posChangedFunc(position);
	this->position = position;
}

inline void Transform::setScale(Vector3 position) {
	anyChangedFunc(position, rotation, scale);
	posChangedFunc(position);
	this->position = position;
}

void Transform::setParent(Transform* parent, int index, bool keep_transform) {

	// Remove transform from old parent's child array
	this->parent->child_count--;
	this->parent->children.erase(this->parent->children.begin() + child_index);

	if (keep_transform)
	
	this->parent = parent;

	// Insert transform into new parent's child array
	
	this->parent->child_count++;
	this->parent->children.insert(this->parent->children.begin(), this);

	/// TODO: Test if the insert section works!!!
}

// Getters


inline Vector3& Transform::getPosition() {
	return position;
}


inline Vector3& Transform::getRotation() {
	return rotation;
}


inline Vector3& Transform::getScale() {
	return scale;
}


Vector3 Transform::getWorldScale() {
	if (is_root)
		return this->scale;
	else
		return Matrix3x3::ScaleMatrix(parent->getWorldScale()) * this->scale;
}


Vector3 Transform::getWorldRotation() {

	return Vector3::Zero; /// TODO: make this after finishing Quaternion implementation
}


Vector3 Transform::getWorldPosition() {
	if (parent->is_root)
		return this->position;
	else
		return (Matrix3x3::ScaleMatrix(parent->scale) * position) + parent->getWorldPosition();
}


inline int Transform::getChildIndex() {
	return child_index;
}

