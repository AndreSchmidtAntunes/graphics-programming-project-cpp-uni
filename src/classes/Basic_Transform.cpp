#include "Basic_Transform.h"

#include "Matrix4x4.h"
#include "Scene.h"

// Getters

const Matrix4x4 Basic_Transform::getLocalTransformMatrix() const {
	return Matrix4x4::TranslationMatrix(local_position) * Matrix4x4::RotationMatrix(local_rotation) * Matrix4x4::ScaleMatrix(local_scale);
}

const Matrix4x4 Basic_Transform::getWorldTransformMatrix() const {
	if (_parent->isRoot())
		return getLocalTransformMatrix();
	else if (_is_root)
		return Matrix4x4::Identity;
	else
		return _parent->getWorldTransformMatrix() * getLocalTransformMatrix();
}

#include "imguiLibs.h"
#include "imguiHelper.h"

void Basic_Transform::DrawImGuiData(ImGuiIO& io) {
	if (ImGui::CollapsingHeader("Transforms", ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_DefaultOpen))
	{
		DrawImGuiVector3(transform->local_position, "Position");
		DrawImGuiVector3(transform->local_scale, "Scale   ");
		DrawImGuiQuaternion(transform->local_rotation, "Rotation");
	}

	if (transform->childCount() > 0)
		if (ImGui::CollapsingHeader("children", ImGuiTreeNodeFlags_Bullet)) {

			for (auto child : transform->getChildren()) {
				ImGui::Text("     ");
				ImGui::SameLine(0);
				ImGui::BeginGroup();

				DrawImGuiTransformFamily(child, camera_following_radio_value);
				ImGui::EndGroup();
			}
		}
}

const Vector3 Basic_Transform::getWorldPosition() const {

	if (_is_root) return Vector3::Zero;

	else return getWorldTransformMatrix().ApplyTransform();
}

const Quaternion Basic_Transform::getWorldRotation() const {
	if (_parent->isRoot())
		return local_rotation;
	else
		return _parent->getWorldRotation() * local_rotation;
}

Basic_Transform::Basic_Transform(const char* name, Basic_Transform* const parent, const size_t child_index, const Vector3& local_position, const Quaternion& local_rotation, const Vector3& local_scale)
	: _name(name), local_position(local_position), local_rotation(local_rotation), local_scale(local_scale), _is_root(false)
{
	_scene_transform_id = parent->_scene->GetNextAvailableObjectID();
	this->_parent = parent;

	if (child_index >= parent->childCount()) {
		this->_child_index = parent->childCount();
		parent->_children.push_back(this);
	}
	else {
		this->_child_index = child_index;
		parent->_children.insert(parent->_children.begin() + child_index, this);
	}

	this->_scene = parent->_scene;
	_children.clear();
}

Basic_Transform::Basic_Transform(const char* name, Basic_Transform* const parent, const Vector3& local_position, const Quaternion& local_rotation, const Vector3& local_scale)
	: _name(name), local_position(local_position), local_rotation(local_rotation), local_scale(local_scale), _is_root(false)
{
	_scene_transform_id = parent->_scene->GetNextAvailableObjectID();
	this->_parent = parent;

	this->_child_index = parent->childCount();
	parent->_children.push_back(this);
	this->_scene = parent->_scene;
	_children.clear();
};