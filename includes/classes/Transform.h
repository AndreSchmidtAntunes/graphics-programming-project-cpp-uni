#pragma once

#include "Quaternion.h"
#include "Vector3.h"
#include <type_traits>
#include <vector>

#define TYPE float

struct Matrix4x4;
struct Scene;
class Mesh;

class Transform {

	Vector3 local_position = Vector3::Zero;
	Quaternion local_rotation = Quaternion::Identity;
	Vector3 local_scale = Vector3::One;

	Transform* parent;
	size_t child_index;
	std::vector<Transform*> children{ };

	
	Mesh* mesh = nullptr;

	Scene* scene; // scene which this transform is inside of
	const bool is_root = false;

	constexpr Transform(Scene* const scene) :
		scene(scene), 
		is_root(true), 
		parent(nullptr),
		child_index(0)
	{} // used by the scene class to make a root transform 

	friend class Scene;

	constexpr ~Transform(void) { // destroy all children, as they would otherwise be orphans
		for (auto child : children) {
			child->~Transform();
		}
		parent->children.erase(parent->children.begin() + child_index);
	}

public:

	bool is_mesh_enabled = true;

	static_assert(std::is_arithmetic<TYPE>::value,
		"Transform: TYPE must be arithmetic!");

	inline void setLocalPosition(const Vector3& position) { local_position = position; }
	inline void setLocalRotation(const Quaternion& rotation) { local_rotation = rotation; }
	inline void setLocalScale(const Vector3& scale) { local_scale = scale; }

	inline void setParent(Transform* const parent, const size_t index) {

		if (parent == this->parent) return;

		// Remove transform from old parent's child array
		this->parent->children.erase(this->parent->children.begin() + child_index);

		if (index >= parent->childCount())
			parent->children.push_back(this);
		else
			parent->children.insert(parent->children.begin() + index, this);
		
		this->parent = parent;

		// Insert transform into new parent's child array


		/// TODO: Test if the insert section works!!!
	}
	inline void setParent(Transform* const parent) { setParent(parent, -1); }

	inline void setMesh(Mesh* const mesh) { this->mesh = mesh; }

	inline const Vector3 getWorldPosition() const;
	inline const Quaternion getWorldRotation() const;

	inline constexpr const Vector3& getLocalScale() const { return local_scale; }
	inline constexpr const Vector3& getLocalPosition() const { return local_position; }
	inline constexpr const Quaternion& getLocalRotation() const { return local_rotation; }

	inline constexpr Transform* const getParent() const { return parent; }
	inline constexpr Scene* const getScene() const { return scene; }
	inline constexpr Transform* const getChild(const size_t index) const { return children[index]; }
	inline constexpr const std::vector<Transform*>& getChildren() const { return children; }

	inline constexpr const size_t getChildIndex() const { return child_index; };
	inline constexpr const size_t childCount() const { return children.size(); }

	constexpr inline const bool getIsRoot() const { return is_root; }

	inline constexpr void DestroyChild(const size_t child_index) {
		children[child_index]->Destroy();
	}

	inline constexpr void Destroy() { this->~Transform(); }
	
	constexpr Transform(Transform* const parent, const size_t child_index, const Vector3& local_position = Vector3::Zero, const Quaternion& local_rotation = Quaternion::Identity, const Vector3& local_scale = Vector3::One)
	:	parent(parent), local_position(local_position), local_rotation(local_rotation), local_scale(local_scale), is_root(false)
	{
		if (child_index >= parent->childCount()) {
			this->child_index = parent->childCount();
			parent->children.push_back(this);
		}
		else {
			this->child_index = child_index;
			parent->children.insert(parent->children.begin() + child_index, this);
		}

		this->scene = parent->scene;
	};
	constexpr Transform(Transform* const parent, const Vector3& local_position = Vector3::Zero, const Quaternion& local_rotation = Quaternion::Identity, const Vector3 & local_scale = Vector3::One)
	:	parent(parent), local_position(local_position), local_rotation(local_rotation), local_scale(local_scale), is_root(false)
	{
		this->child_index = parent->childCount();
		parent->children.push_back(this);
		this->scene = parent->scene;
	};
};