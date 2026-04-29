#pragma once

#include "Vector3.h"
#include "Quaternion.h"
#include <vector>
#include <type_traits>

#define TYPE float
struct Matrix4x4;
struct Scene;

class Transform {
public:

	static_assert(std::is_arithmetic<TYPE>::value,
		"Transform: TYPE must be arithmetic!");

	inline void setLocalPosition(const Vector3& position);
	inline void setLocalRotation(const Quaternion& rotation);
	inline void setLocalScale(const Vector3& scale);

	inline void setParent(Transform* parent, int index);
	inline void setParent(Transform* parent);
	inline void setScene(Scene* scene, int index);
	inline void setScene(Scene* scene);

	inline const Vector3 getWorldPosition() const;
	inline const Quaternion getWorldRotation() const;

	inline const Vector3& getLocalPosition() const;
	inline const Quaternion& getLocalRotation() const;	
	inline const Vector3& getLocalScale() const;

	inline Transform* getParent() const;
	inline const int getChildIndex() const;

	inline const bool getIsRoot() const {
		return parent == this;
	}

	inline Scene* getScene() const;

	inline const std::vector<Transform*> getAllChildren() const;
	inline Transform* getChild(size_t index) const;

	inline void DestroyChild(size_t child_index) {
		Destroy(children[child_index]);
	}

	inline void Destroy() {
		Transform::Destroy(this);
	}

	static inline void Destroy(Transform* transform) {

		for (Transform* child : transform->children) {
			Destroy(child);
		}

		auto it = transform->parent->children.begin() + transform->child_index;
		transform->parent->children.erase(it);
		transform->~Transform();
	}
	
	Transform(Transform* parent, const size_t child_index, const Vector3& local_position = Vector3::Zero, const Vector3& local_scale = Vector3::One, const Quaternion& local_rotation = Quaternion::Identity)
	:	parent(parent), child_index(child_index), local_position(local_position), local_rotation(local_rotation), local_scale(local_scale), is_root(false)
	{
		parent->children.insert(parent->children.begin() + child_index, this);
		this->scene = parent->scene;
	};
	Transform(Transform* parent, const Vector3& local_position = Vector3::Zero, const Vector3& local_scale = Vector3::One, const Quaternion& local_rotation = Quaternion::Identity)
	:	parent(parent), local_position(local_position), local_rotation(local_rotation), local_scale(local_scale), is_root(false)
	{
		this->child_index = parent->children.size();
		parent->children.insert(parent->children.begin() + this->child_index, this);
		this->scene = parent->scene;
	};

	constexpr Transform(Scene* const scene) { // used by scene class to make a root transform 
		parent = nullptr;
		local_position = Vector3::Zero;
		local_rotation = Quaternion::Identity;
		local_scale = Vector3::One;

		is_root = true;
		this->scene = scene;
		this->scene->InsertChild(this);
	};

	constexpr inline const bool getIsRoot() const {
		return is_root;
	}

protected:
	Vector3 local_position = Vector3::Zero;
	Quaternion local_rotation = Quaternion::Identity;
	Vector3 local_scale = Vector3::One;

	Transform* parent;
	int child_index;
	std::vector<Transform*> children { };

	Scene* scene;
	bool is_root = false;
};