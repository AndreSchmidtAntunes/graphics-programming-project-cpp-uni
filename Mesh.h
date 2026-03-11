#pragma once

#include "Colour.h"
#include "GLLibs.h"
#include "Poly.h"

struct Mesh {
public:

	Vector3* vertices;
	uint vertices_count;

	Poly* polygons;
	uint polygons_count;

	Mesh() : vertices(nullptr), polygons(nullptr), vertices_count(0), polygons_count(0) {};

	Mesh(const Vector3* vertices, const uint vertices_length, const Poly* triangles, const uint triangles_length);

	Mesh(const Vector3* vertices, const uint vertices_length, const uint** indices, const uint* per_indice_length, const uint triangles_length);

	Mesh(const Vector3* vertices, const uint vertices_length, const uint** indices, const Colour** indice_colours, const uint* per_indice_length, const uint indices_length);

	~Mesh();

	Vector3& getVertex(const Poly* polygon, uint edge_index) {
		return vertices[polygon->indices[edge_index]];
	}

	bool LoadFromFile(const std::string& filename);

};