#pragma once


#include "Quaternion.h"
#include "Vector3.h"
#include <type_traits>
#include <vector>

#define TYPE float

struct Matrix4x4;
struct Scene;

class Basic_Transform {
protected:
	const char* _name;
	Basic_Transform* _parent;

	size_t _child_index;
	std::vector<Basic_Transform*> _children;

	Scene* _scene; // scene which this transform is inside of
	int _scene_transform_id; // the unique id assigned to the transform when added to a scene
	const bool _is_root = false;

	constexpr Basic_Transform(Scene* const scene) :
		_scene(scene),
		_scene_transform_id(0),
		_is_root(true),
		_parent(nullptr),
		_child_index(0),
		_name("root")
	{
	} // used by the scene class to make a root transform 
	friend class Scene;

	const Matrix4x4 getLocalTransformMatrix() const;
	const Matrix4x4 getWorldTransformMatrix() const;

public:

	virtual void Draw() const {} // override this with how the transform type will be drawn

	constexpr ~Basic_Transform(void) { // destroy all children, as they would otherwise be orphans
		for (auto child : _children) {
			child->~Basic_Transform();
		}
		_parent->_children.erase(_parent->_children.begin() + _child_index);
	}

	Vector3	local_position = Vector3::Zero;
	Quaternion local_rotation = Quaternion::Identity;
	Vector3 local_scale = Vector3::One;

	static_assert(std::is_arithmetic<TYPE>::value,
		"Transform: TYPE must be arithmetic!");

	inline void setName(const char* name) {
		delete[] this->_name;
		this->_name = name;
	}

	inline void setParent(Basic_Transform* const parent, const size_t index) {

		if (parent == this->_parent) return;

		// Remove transform from old parent's child array
		this->_parent->_children.erase(this->_parent->_children.begin() + _child_index);

		if (index >= parent->childCount())
			parent->_children.push_back(this);
		else
			parent->_children.insert(parent->_children.begin() + index, this);

		// Insert transform into new parent's child array
		this->_parent = parent;
	}

	inline void setParent(Basic_Transform* const parent) { setParent(parent, -1); }

	inline const char* const getName() const { return _name; }

	const Vector3 getWorldPosition() const;
	const Quaternion getWorldRotation() const;

	inline constexpr Basic_Transform* const parent() const { return _parent; }
	inline constexpr Scene* const getScene() const { return _scene; }

	inline constexpr const int& getSceneTransformID() const { return _scene_transform_id; }
	inline constexpr Basic_Transform* const getChild(const size_t index) const { return _children[index]; }
	inline constexpr const std::vector<Basic_Transform*>& getChildren() const { return _children; }

	inline constexpr const size_t getChildIndex() const { return _child_index; };
	inline constexpr const size_t childCount() const { return _children.size(); }
	inline constexpr const size_t descendantCount() const {

		size_t count = _children.size();
		for (auto child : _children) {
			count += child->descendantCount();
		}
		return count;
	}

	constexpr inline const bool isRoot() const { return _is_root; }

	inline constexpr void DestroyChild(const size_t child_index) {
		_children[child_index]->Destroy();
	}

	inline constexpr void Destroy() { this->~Basic_Transform(); }

	Basic_Transform(const char* name, Basic_Transform* const parent, const size_t child_index, const Vector3& local_position = Vector3::Zero, const Quaternion& local_rotation = Quaternion::Identity, const Vector3& local_scale = Vector3::One);
	Basic_Transform(const char* name, Basic_Transform* const parent, const Vector3& local_position = Vector3::Zero, const Quaternion& local_rotation = Quaternion::Identity, const Vector3& local_scale = Vector3::One);
};