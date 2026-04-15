#pragma once

#include "GLLibs.h"
#include "Vector3.h"

class Camera;

#define TYPE GLfloat
class Mesh {
public:

	GLfloat *vertices, *colours, *normals,  *uvs;

	GLuint *indices, *normal_indices, *uv_indices;

	GLuint vertices_count, colours_count, normals_count, uvs_count,
		indices_count;

	//Poly* polygons;
	//size_t polygons_count;

	//Mesh() : vertices(nullptr), polygons(nullptr), vertices_count(0), polygons_count(0) { };


	//Mesh(const TYPE* vertices, const size_t vertices_length, const Poly* triangles, const size_t triangles_length);
	
	Mesh(const TYPE* vertices, const size_t vertices_count, const size_t* indices, const size_t indices_count);

	Mesh(const TYPE* vertices, const size_t vertices_count, const size_t* indices, const size_t indices_count, const TYPE* colours, const size_t colours_count);

	Mesh(const TYPE* vertices, const size_t vertices_count, const size_t* indices, const size_t indices_count, const TYPE* normals, const size_t normals_count, const TYPE* uvs, const size_t uvs_count);

	Mesh(const TYPE* vertices, const size_t vertices_count, const size_t* indices, const size_t indices_count, const TYPE* normals, const size_t normals_count, const TYPE* uvs, const size_t uvs_count, const TYPE* colours, const size_t colours_count);


	//Mesh(const TYPE* vertices, const size_t vertices_length, const size_t** indices, const size_t* per_indice_length, const size_t triangles_length);

	//Mesh(const TYPE* vertices, const size_t vertices_length, const size_t** indices, const Colour** indice_colours, const size_t* per_indice_length, const size_t indices_length);

	Mesh(void) : Mesh(nullptr, 0, nullptr, 0, nullptr, 0, nullptr, 0, nullptr, 0) {};

	~Mesh(void);

	//Vector3& getVertex(const Poly* polygon, size_t edge_index) {
	//	return vertices[polygon->indices[edge_index]];
	//}

	void Render(const Vector3& position, const Camera*) const;
	void Render(const Vector3& position, const Vector3& rotation, const Camera*) const;
	void Render(const Vector3& position, const Vector3& rotation, const Vector3& scale, const Camera*) const;

	bool LoadFromFile(const std::string& filename);

	Mesh(const std::string& filename) { LoadFromFile(filename); }

private:
	void DrawElements() const;
};

