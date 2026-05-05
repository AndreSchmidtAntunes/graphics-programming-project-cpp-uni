#pragma once

#include "Quaternion.h"
#include "Vector3.h"
#include <type_traits>
#include <vector>

#define TYPE float

struct Matrix4x4;
struct Scene;
class Mesh;
class Material;
class Texture2D;

class Transform {
	const char* name;
	Transform* _parent;
	size_t child_index;
	std::vector<Transform*> children;
	
	Mesh* mesh = nullptr;
	Texture2D* texture = nullptr;
	Material* material = nullptr;

	Scene* scene; // scene which this transform is inside of
	int scene_transform_id; // the unique id assigned to the transform when added to a scene
	const bool is_root = false;

	constexpr Transform(Scene* const scene) :
		scene(scene), 
		scene_transform_id(0),
		is_root(true), 
		_parent(nullptr),
		child_index(0),
		name("root")
	{} // used by the scene class to make a root transform 

	friend class Scene;

	constexpr ~Transform(void) { // destroy all children, as they would otherwise be orphans
		for (auto child : children) {
			child->~Transform();
		}
		_parent->children.erase(_parent->children.begin() + child_index);
	}

	const Matrix4x4 getLocalTransformMatrix() const;
	const Matrix4x4 getWorldTransformMatrix() const;


public:

	Vector3 local_position = Vector3::Zero;
	Quaternion local_rotation = Quaternion::Identity;
	Vector3 local_scale = Vector3::One;

	bool is_mesh_enabled = true;

	static_assert(std::is_arithmetic<TYPE>::value,
		"Transform: TYPE must be arithmetic!");

	inline void setName(const char* name) {
		delete[] this->name;
		this->name = name;
	}

	inline void setParent(Transform* const parent, const size_t index) {

		if (parent == this->_parent) return;

		// Remove transform from old parent's child array
		this->_parent->children.erase(this->_parent->children.begin() + child_index);

		if (index >= parent->childCount())
			parent->children.push_back(this);
		else
			parent->children.insert(parent->children.begin() + index, this);
		
		// Insert transform into new parent's child array
		this->_parent = parent;
	}

	inline void setParent(Transform* const parent) { setParent(parent, -1); }

	inline void setMesh(Mesh* const mesh) { this->mesh = mesh; }
	inline void setTexture(Texture2D* const texture) { this->texture = texture; }
	inline void setMaterial(Material* const material) { this->material = material; }

	inline const char* const getName() const { return name; }

	const Vector3 getWorldPosition() const;
	const Quaternion getWorldRotation() const;

	inline constexpr const Mesh* const getMesh() const { return mesh; }
	inline constexpr const Material* const getMaterial() const { return material; }
	inline constexpr const Texture2D* const getTexture() const { return texture; }

	inline constexpr Transform* const parent() const { return _parent; }
	inline constexpr Scene* const getScene() const { return scene; }

	inline constexpr const int& getSceneTransformID() const { return scene_transform_id; }
	inline constexpr Transform* const getChild(const size_t index) const { return children[index]; }
	inline constexpr const std::vector<Transform*>& getChildren() const { return children; }

	inline constexpr const size_t getChildIndex() const { return child_index; };
	inline constexpr const size_t childCount() const { return children.size(); }
	inline constexpr const size_t descendantCount() const { 
		size_t count = children.size();
		for (auto child : children) {
			count += child->descendantCount();
		}
		return count;
	}

	constexpr inline const bool isRoot() const { return is_root; }

	inline constexpr void DestroyChild(const size_t child_index) {
		children[child_index]->Destroy();
	}

	inline constexpr void Destroy() { this->~Transform(); }
	
	Transform(const char* name, Transform* const parent, const size_t child_index, const Vector3& local_position = Vector3::Zero, const Quaternion& local_rotation = Quaternion::Identity, const Vector3& local_scale = Vector3::One);
	Transform(const char* name, Transform* const parent, const Vector3& local_position = Vector3::Zero, const Quaternion& local_rotation = Quaternion::Identity, const Vector3& local_scale = Vector3::One);
};