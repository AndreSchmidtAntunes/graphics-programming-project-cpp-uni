#include "Transform.h"

#include "GLLibs.h"
#include "Matrix4x4.h"
#include "Scene.h"

// Getters

inline const Matrix4x4 getLocalTransformMatrix(Transform* const transform) {
	return Matrix4x4::ScaleMatrix(transform->getLocalScale()) * Matrix4x4::RotationMatrix(transform->getLocalRotation()) * Matrix4x4::TranslationMatrix(transform->getLocalPosition());
}

inline const Matrix4x4 getTransformMatrix(Transform* const transform) {
	if (transform->getIsRoot())
		return getLocalTransformMatrix(transform);
	else
		return getTransformMatrix(transform->getParent()) * getLocalTransformMatrix(transform);
}

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



