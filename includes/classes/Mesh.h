#pragma once

#include "Colour.h"
#include "GLLibs.h"
#include "Vector3.h"
#include "Camera.h"

class Mesh {
public:

	GLfloat *vertices, *colours, *normals,  *uvs;

	GLuint *indices, *normal_indices, *uv_indices;

	GLuint vertices_count, colours_count, normals_count, uvs_count,
		indices_count;

	//Poly* polygons;
	//uint polygons_count;

	//Mesh() : vertices(nullptr), polygons(nullptr), vertices_count(0), polygons_count(0) { };


	//Mesh(const double* vertices, const uint vertices_length, const Poly* triangles, const uint triangles_length);
	
	Mesh(const double* vertices, const uint vertices_length, const uint* indices, const uint triangles_length);

	Mesh(const double* vertices, const uint vertices_count, const uint* indices, const uint indices_count, const double* colours, const uint colours_count);

	Mesh(const double* vertices, const uint vertices_count, const uint* indices, const uint indices_count, const double* normals, const uint normals_count, const double* uvs, const uint uvs_count);

	Mesh(const double* vertices, const uint vertices_count, const uint* indices, const uint indices_count, const double* normals, const uint normals_count, const double* uvs, const uint uvs_count, const double* colours, const uint colours_count);


	//Mesh(const double* vertices, const uint vertices_length, const uint** indices, const uint* per_indice_length, const uint triangles_length);

	//Mesh(const double* vertices, const uint vertices_length, const uint** indices, const Colour** indice_colours, const uint* per_indice_length, const uint indices_length);

	Mesh(void) : Mesh(nullptr, 0, nullptr, 0, nullptr, 0, nullptr, 0, nullptr, 0) {};

	~Mesh(void);

	//Vector3<>& getVertex(const Poly* polygon, uint edge_index) {
	//	return vertices[polygon->indices[edge_index]];
	//}

	void Render(const Vector3<>& position, const Camera<>*) const;
	void Render(const Vector3<>& position, const Vector3<>& rotation, const Camera<>*) const;
	void Render(const Vector3<>& position, const Vector3<>& rotation, const Vector3<>& scale, const Camera<>*) const;

	bool LoadFromFile(const std::string& filename);

	Mesh(const std::string& filename) { LoadFromFile(filename); }

protected:
	const Colour DefaultColour = Colour::RED;

private:
	void DrawElements() const;
};

