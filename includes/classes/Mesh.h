#pragma once

#include "Camera.h"
#include "Colour.h"
#include "GLLibs.h"
#include "Texture2D.h"
#include "Vector3.h"
#include "Quaternion.h"

class Camera;

#define TYPE GLfloat

struct vertex_data {

	Vector3 position;
	TexCoord tex_coord;
	Vector3 normal;
	Colour colour;

	vertex_data(const Vector3& position, const TexCoord& tex_coord, const Vector3& normal, const Colour& colour = Colour::White) : position(position), tex_coord(tex_coord), normal(normal), colour(colour) {}
	vertex_data(void) : position(position), tex_coord(tex_coord), normal(normal) {}
	~vertex_data(void) { }
};

class Mesh {
public:

	vertex_data* vertices = nullptr; size_t vertices_size;
	GLuint* vert_indices; size_t vert_indices_count;

	std::string name;
	bool shade_smooth = false;

	bool has_colours, has_normals, has_tex_coords = false;

	const Texture2D *texture = nullptr;

	Mesh(const Vector3* vertices, const size_t vertices_count, const GLuint* indices, const size_t indices_count, const Vector3* normals = nullptr, const size_t normals_count = 0, const TexCoord* tex_coords = nullptr, const size_t tex_coords_count = 0, const Colour* colours = nullptr, const size_t colours_count = 0, const Texture2D* texture = nullptr);
	
	Mesh(void) : Mesh(nullptr, 0, nullptr, 0) {};
	~Mesh(void);

	void RenderWithoutMatrices(Camera* const camera, const Vector3& position = Vector3::Zero, const Quaternion& rotation = Quaternion::Identity, const Vector3& scale = Vector3::One) const;

	void Render(Camera* const camera, const Vector3& position = Vector3::Zero, const Quaternion& rotation = Quaternion::Identity, const Vector3& scale = Vector3::One) const;

	bool LoadFromFile(const char* file_name, const Texture2D* texture = nullptr);

	bool LoadFromFile(const char* file_name, const char* raw_texture_filename, const size_t texture_width, const size_t texture_height) { 
		return LoadFromFile(file_name, Texture2D::FromFile(raw_texture_filename, texture_width, texture_height)); 
	}
	Mesh(const char* file_name, const Texture2D* texture = nullptr) { LoadFromFile(file_name, texture); }

	void DrawElements() const;
};

