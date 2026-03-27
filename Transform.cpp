#include "Transform.h"

void Transform::SetOnChangedFunc(void (*callback)(Vector3<T>, Vector3<T>, Vector3<T>)) {
	anyChangedFunc = callback;
}

void Transform::SetOnPositionChangedFunc(void (*callback)(Vector3<T>)) {
	posChangedFunc = callback;
}

void Transform::SetOnRotationChangedFunc(void (*callback)(Vector3<T>)) {
	rotChangedFunc = callback;
}

void Transform::SetOnScaleChangedFunc(void (*callback)(Vector3<T>)) {
	scaleChangedFunc = callback;
}

// Setters

inline void Transform::setPosition(Vector3<T> position) {
	anyChangedFunc(position, rotation, scale);
	posChangedFunc(position);
	this->position = position;
}

inline void Transform::setRotation(Vector3<T> position) {
	anyChangedFunc(position, rotation, scale);
	posChangedFunc(position);
	this->position = position;
}

inline void Transform::setScale(Vector3<T> position) {
	anyChangedFunc(position, rotation, scale);
	posChangedFunc(position);
	this->position = position;
}

void Transform::setParent(Transform* transform, int index, bool keep_transform = false) {

	// Remove transform from old parent's child array
	parent->child_count--;
	parent->children.erase(parent->children.begin() + child_index);

	if (keep_transform)
	
	parent = transform;

	// Insert transform into new parent's child array
	
	parent->child_count++;
	parent->children.insert(parent->children.begin(), this);

	/// TODO: Test if the insert section works!!!
}

// Getters

inline Vector3<T>& Transform::getPosition() {
	return position;
}

inline Vector3<T>& Transform::getRotation() {
	return rotation;
}

inline Vector3<T>& Transform::getScale() {
	return scale;
}

Vector3<T> Transform::getWorldScale() {
	if (parent->is_root)
		return this->scale;
	else
		return position * (parent->scale) + parent->getWorldPosition();
}

Vector3<T> Transform::getWorldRotation() {

	if (parent->is_root)
		return this->scale;
	else
		return position * (parent->scale) + parent->getWorldPosition();
}

Vector3<T> Transform::getWorldPosition() {
	if (parent->is_root)
		return this->position;
	else
		return position * (parent->scale) + parent->getWorldPosition();
}

inline int Transform::getChildIndex() {
	return child_index;
}

