#pragma once

#include "Colour.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Texture2D.h"

class Camera;
struct Material;

struct vertex_data {

	Vector3 position;
	TexCoord tex_coord;
	Vector3 normal;
	Colour colour;

	vertex_data(const Vector3& position, const TexCoord& tex_coord, const Vector3& normal, const Colour& colour = Colour::White);
	vertex_data(void) : position(position), tex_coord(tex_coord), normal(normal) {}
	~vertex_data(void) { }
};

class Mesh {
public:

	vertex_data* vertices = nullptr; size_t vertices_size;
	size_t* vert_indices; size_t vert_indices_count;

	std::string name;
	bool shade_smooth = false;

	bool has_colours = false, has_normals = false, has_tex_coords = false;


	void DrawElements(const Material* const material = nullptr, const Texture2D* const texture = nullptr) const;

	void RenderWithoutMatrices(Camera* const camera, const Vector3& position = Vector3::Zero, const Quaternion& rotation = Quaternion::Identity, const Vector3& scale = Vector3::One) const;

	void Render(Camera* const camera, const Vector3& position = Vector3::Zero, const Quaternion& rotation = Quaternion::Identity, const Vector3& scale = Vector3::One) const;

	bool LoadFromFile(const char* file_name);

	Mesh(const char* file_name) { LoadFromFile(file_name); }

	Mesh(const Vector3* vertices, const size_t vertices_count, const size_t* indices, const size_t indices_count, const Vector3* normals = nullptr, const size_t normals_count = 0, const TexCoord* tex_coords = nullptr, const size_t tex_coords_count = 0, const Colour* colours = nullptr, const size_t colours_count = 0, const Texture2D* texture = nullptr);
	Mesh(void) : Mesh(nullptr, 0, nullptr, 0) {};
	~Mesh(void);
};

