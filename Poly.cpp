#include "Poly.h";

Poly::Poly(const uint* indices, const uint vert_count) {
	this->vert_count = vert_count;

	this->indices = new uint[vert_count];

	for (uint i = 0; i < vert_count; i++) {
		this->indices[i] = indices[i];
	}
}

Poly::~Poly() {
	delete[vert_count] indices;
	if (colours)
		delete[vert_count] colours;
}

Colour*& Poly::Init(const Colour* colours) {
	if (colours) {
		this->colours = new Colour[vert_count];
		for (uint i = 0; i < vert_count; i++) {
			this->colours[i] = colours[i];
		}
	}
	return this->colours;
}

Vector2<>*& Poly::Init(const Vector2<>* uvs) {
	if (uvs) {
		this->texture_coordinates = new Vector2<>[vert_count];
		for (uint i = 0; i < vert_count; i++) {
			this->texture_coordinates[i] = uvs[i];
		}
	}
	return this->texture_coordinates;
}

Vector3<>*& Poly::Init(const Vector3<>* normals) {
	if (normals) {
		this->normals = new Vector3<>[vert_count];
		for (uint i = 0; i < vert_count; i++) {
			this->normals[i] = normals[i];
		}
	}
	return this->normals;
}

