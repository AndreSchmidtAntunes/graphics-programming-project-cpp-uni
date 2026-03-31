#include "Transform.h"

template <typename T>
void Transform<T>::SetOnChangedFunc(void (*callback)(Vector3<T>, Vector3<T>, Vector3<T>)) {
	anyChangedFunc = callback;
}

template <typename T>
void Transform<T>::SetOnPositionChangedFunc(void (*callback)(Vector3<T>)) {
	posChangedFunc = callback;
}

template <typename T>
void Transform<T>::SetOnRotationChangedFunc(void (*callback)(Vector3<T>)) {
	rotChangedFunc = callback;
}

template <typename T>
void Transform<T>::SetOnScaleChangedFunc(void (*callback)(Vector3<T>)) {
	scaleChangedFunc = callback;
}

// Setters

template <typename T>
inline void Transform<T>::setPosition(Vector3<T> position) {
	anyChangedFunc(position, rotation, scale);
	posChangedFunc(position);
	this->position = position;
}

template <typename T>
inline void Transform<T>::setRotation(Vector3<T> position) {
	anyChangedFunc(position, rotation, scale);
	posChangedFunc(position);
	this->position = position;
}

template <typename T>
inline void Transform<T>::setScale(Vector3<T> position) {
	anyChangedFunc(position, rotation, scale);
	posChangedFunc(position);
	this->position = position;
}

template <typename T>
void Transform<T>::setParent(Transform<T>* parent, int index, bool keep_transform) {

	// Remove transform from old parent's child array
	this->parent->child_count--;
	this->parentparent->children.erase(this->parent->children.begin() + child_index);

	if (keep_transform)
	
	this->parent = parent;

	// Insert transform into new parent's child array
	
	this->parent->child_count++;
	this->parent->children.insert(this->parent->children.begin(), this);

	/// TODO: Test if the insert section works!!!
}

// Getters

template <typename T>
inline Vector3<T>& Transform<T>::getPosition() {
	return position;
}

template <typename T>
inline Vector3<T>& Transform<T>::getRotation() {
	return rotation;
}

template <typename T>
inline Vector3<T>& Transform<T>::getScale() {
	return scale;
}

template <typename T>
Vector3<T> Transform<T>::getWorldScale() {
	if (parent->is_root)
		return this->scale;
	else
		return position * (parent->scale) + parent->getWorldPosition();
}

template <typename T>
Vector3<T> Transform<T>::getWorldRotation() {

	if (parent->is_root)
		return this->scale;
	else
		return position * (parent->scale) + parent->getWorldPosition();
}

template <typename T>
Vector3<T> Transform<T>::getWorldPosition() {
	if (parent->is_root)
		return this->position;
	else
		return position * (parent->scale) + parent->getWorldPosition();
}

template <typename T>
inline int Transform<T>::getChildIndex() {
	return child_index;
}

