#include "Poly.h"

Poly::Poly(const Vector3* verts, int vert_count) : verts(NULL), colours(NULL) {

	this->verts = new Vector3[vert_count];	
	this->colours = NULL;
	this->vert_count = vert_count;

	for (int i = 0; i < vert_count; i++) {
		this->verts[i] = verts[i];
	}
}

Poly::Poly(const Vector3* verts, const Colour* colours, int vert_count) : verts(NULL), colours(NULL) {

	this->vert_count = vert_count;

	this->verts = new Vector3[vert_count];
	for (int i = 0; i < vert_count; i++) {
		this->verts[i] = verts[i];
	}

	if (colours) {
		this->colours = new Colour[vert_count];
		for (int i = 0; i < vert_count; i++) {
			this->colours[i] = colours[i];
		}
	}
	else
		this->colours = NULL;
}

Poly::~Poly() {
	delete[vert_count] verts;

	if (colours)
		delete[vert_count] colours;
}

Vector3& Poly::operator[](std::size_t idx){
	return this->verts[idx];
}