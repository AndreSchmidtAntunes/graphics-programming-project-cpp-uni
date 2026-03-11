#include "Poly.h";

Poly::Poly(const uint* indices, const uint vert_count/*, Mesh* owner*/)/* : owner(owner)*/ {

	this->indices = new uint[vert_count];
	this->colours = NULL;
	this->vert_count = vert_count;

	for (uint i = 0; i < vert_count; i++) {
		this->indices[i] = indices[i];
	}
}

Poly::Poly(const uint* indices, const Colour* colours, const uint vert_count/*, Mesh* owner*/)/* : owner(owner)*/ {

	this->vert_count = vert_count;

	this->indices = new uint[vert_count];
	for (uint i = 0; i < vert_count; i++) {
		this->indices[i] = indices[i];
	}

	if (colours) {
		this->colours = new Colour[vert_count];
		for (uint i = 0; i < vert_count; i++) {
			this->colours[i] = colours[i];
		}
	}
	else
		this->colours = NULL;
}

Poly::~Poly() {
	delete[vert_count] indices;
	if (colours)
		delete[vert_count] colours;
}

//#include "Mesh.h"
//
//Vector3& Poly::operator[] (const uint idx) {
//	return owner->vertices[indices[idx]];
//}

