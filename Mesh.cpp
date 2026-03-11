#include "Mesh.h"

Mesh::Mesh(const Vector3* vertices, const uint vertices_length, const Poly* polygons, const uint polygons_count) {
	
	this->vertices_count = vertices_length;
	this->polygons_count = polygons_count;

	this->vertices = new Vector3[vertices_count];
	for (uint i = 0; i < vertices_length; i++) {
		this->vertices[i] = vertices[i];
	}

	this->polygons = new Poly[polygons_count];
	for (uint i = 0; i < polygons_count; i++) {

		/*this->polygons[i].owner = this;*/

		this->polygons[i].vert_count = polygons[i].vert_count;
		this->polygons[i].indices = new uint[polygons[i].vert_count];
		for (uint indice = 0; indice < polygons[i].vert_count; indice++) {
			this->polygons[i].indices[indice] = polygons[i].indices[indice];
		}

		if (polygons[i].colours) {

			this->polygons[i].colours = new Colour[polygons[i].vert_count];
			for (uint vert = 0; vert < polygons[i].vert_count; vert++) {
				this->polygons[i].colours[vert] = polygons[i].colours[vert];
			}
		}
		else
			this->polygons[i].colours = NULL;

	}
}

Mesh::Mesh(const Vector3* vertices, const uint vertices_length, const uint** indices, const uint* per_indice_length, const uint indices_length) {

	this->vertices_count = vertices_length;
	this->polygons_count = indices_length;
	
	this->vertices = new Vector3[vertices_count];
	for (uint i = 0; i < vertices_length; i++) {
		this->vertices[i] = vertices[i];
	}

	this->polygons = new Poly[indices_length];
	for (uint i = 0; i < indices_length; i++) {

		/*this->polygons[i].owner = this;*/

		this->polygons[i].vert_count = per_indice_length[i];
		this->polygons[i].indices = new uint[per_indice_length[i]];
		for (uint indice = 0; indice < per_indice_length[i]; indice++) {
			this->polygons[i].indices[indice] = indices[i][indice];
		}

		this->polygons[i].colours = NULL;
	}
}

Mesh::Mesh(const Vector3* vertices, const uint vertices_length, const uint** indices, const Colour** indice_colours, const uint* per_indice_length, const uint indices_length) {

	this->vertices_count = vertices_length;
	this->polygons_count = indices_length;
	
	this->vertices = new Vector3[vertices_count];
	for (uint i = 0; i < vertices_length; i++) {
		this->vertices[i] = vertices[i];
	}

	this->polygons = new Poly[indices_length];
	for (uint i = 0; i < indices_length; i++) {
		this->polygons[i].indices = new uint[per_indice_length[i]];
		/*this->polygons[i].owner = this;*/

		this->polygons[i].vert_count = per_indice_length[i];
		for (uint indice = 0; indice < per_indice_length[i]; indice++) {
			this->polygons[i].indices[indice] = indices[i][indice];
		}

		if (polygons[i].colours) {

			this->polygons[i].colours = new Colour[per_indice_length[i]];
			for (uint indice = 0; indice < per_indice_length[i]; indice++) {
				this->polygons[i].colours[i] = indice_colours[i][indice];
			}
		}
		else
			this->polygons[i].colours = NULL;
	}
}

Mesh::~Mesh() {
	delete[this->vertices_count] vertices;
	delete[this->polygons_count] polygons;
}