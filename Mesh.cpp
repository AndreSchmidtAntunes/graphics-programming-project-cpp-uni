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

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

bool Mesh::LoadFromFile(const std::string& filename) {

	std::vector<Vector3> vertices;
	std::vector<Poly*> polygons;

	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return false;
	}
	std::string line = "";

	uint _current_line = 0;
	while (std::getline(file, line)) {
		std::istringstream iss(line);

		_current_line++;

		char type;

		if (iss >> type)
			switch (type)
			{
				case 'v': { // If we are reading a vertex

					double x, y, z;

					if (iss >> x >> y >> z)
						vertices.emplace_back(Vector3(x, y, z));

					continue;
				}

				case 'f': { // If we are reading a face definition

					std::vector<uint> indices;

					// Loop through however many points are referenced in a face dynamically, as they can have 3 or 4 or 5 etc
					uint index;
					while (iss >> index) {
						indices.push_back(index);
					}
					if (indices.size())
						polygons.emplace_back(new Poly(indices.data(), indices.size()));

					continue;
				}
				case 'o': { // comment
					continue;
				}

				case '#': { // comment
					continue;
				} 


				default: { // erroneous first istring
					std::cerr << "Erroneous command at file: " << filename << ", line: " << _current_line << std::endl;
					continue;
				}

			}
	}
	
	this->vertices_count = vertices.size();
	this->polygons_count = polygons.size();

	delete[this->vertices_count] this->vertices;
	delete[this->polygons_count] this->polygons;

	this->vertices = new Vector3[vertices_count] { };
	this->polygons = new Poly[polygons_count] { };

	for (int i = 0; i < vertices_count; i++)
		this->vertices[i] = vertices[i];

	for (int i = 0; i < polygons_count; i++)
		this->polygons[i] = *polygons[i];

	//std::copy(vertices.begin(), vertices.end(), this->vertices);
	//std::copy(polygons.begin(), polygons.end(), this->polygons);
	
	return true;
}