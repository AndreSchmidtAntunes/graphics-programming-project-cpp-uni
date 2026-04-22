#pragma once

#include "Colour.h"
#include "GLLibs.h"
#include "Vector3.h"
#include "Texture2D.h"
#include "Camera.h"

class Camera;

#define TYPE GLfloat

class Mesh {
public:

	GLfloat  *vertices;		size_t vertices_size;	 GLuint *vert_indices;		size_t vert_indices_size;
	GLfloat  *normals;		size_t normals_size;	 GLuint *normal_indices;	size_t normal_indices_size;
    TexCoord *tex_coords;	size_t tex_coords_size;  GLuint *tex_coord_indices;	size_t tex_coord_indices_size;

	GLfloat  *colours;		size_t colours_count;

	const Texture2D *texture;

	Mesh(const TYPE* vertices, const size_t vertices_count, const size_t* indices, const size_t indices_count);

	Mesh(const TYPE* vertices, const size_t vertices_count, const size_t* indices, const size_t indices_count, const TYPE* colours, const size_t colours_count);

	Mesh(const TYPE* vertices, const size_t vertices_count, const size_t* indices, const size_t indices_count, const TYPE* normals, const size_t normals_count, const TexCoord* tex_coords, const size_t tex_coord_count);

	Mesh(const TYPE* vertices, const size_t vertices_count, const size_t* indices, const size_t indices_count, const TYPE* normals, const size_t normals_count, const TexCoord* tex_coords, const size_t tex_coord_count, const TYPE* colours, const size_t colours_count);

	Mesh(void) : Mesh(nullptr, 0, nullptr, 0, nullptr, 0, nullptr, 0, nullptr, 0) {};

	~Mesh(void);

	void Render(const Vector3& position, const Camera*) const;
	void Render(const Vector3& position, const Vector3& rotation, const Camera*) const;
	void Render(const Vector3& position, const Vector3& rotation, const Vector3& scale, const Camera*) const;

	bool LoadFromFile(const std::string& filename, const Texture2D* texture = nullptr);

	Mesh(const std::string& filename, const Texture2D* texture = nullptr) { LoadFromFile(filename, texture); }

private:
	void DrawElements() const;
};

