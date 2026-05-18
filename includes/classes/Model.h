#pragma once
#include "Transform.h"

struct Material;
struct Texture2D;
class Mesh;

class Model : public Transform {

	using Transform::Transform;

	Mesh* _mesh = nullptr;
	Texture2D* _texture = nullptr;
	Material* _material = nullptr;

public:

	bool is_mesh_enabled = true;

	void Draw() const;

	inline constexpr const Mesh* const getMesh() const { return _mesh; }
	inline constexpr const Material* const getMaterial() const { return _material; }
	inline constexpr const Texture2D* const getTexture() const { return _texture; }

	inline void setMesh(Mesh* const mesh) { 
		this->_mesh = mesh; 
	}
	inline void setTexture(Texture2D* const texture) { 
		this->_texture = texture; 
	}
	inline void setMaterial(Material* const material) { 
		this->_material = material; 
	}
};