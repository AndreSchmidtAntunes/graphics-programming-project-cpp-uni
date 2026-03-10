#include "Poly.h"

Poly::Poly(Vector3* verts, int vert_count) {

	this->verts = new Vector3[vert_count];	
	this->colours = new Colour[vert_count];
	this->vert_count = vert_count;

	for (int i = 0; i < vert_count; i++) {
		this->verts[i] = verts[i];
		this->colours[i] = Colour::WHITE;
	}
}

Poly::Poly(Vector3* verts, Colour* colours, int vert_count) {

	this->verts = new Vector3[vert_count];
	this->colours = new Colour[vert_count];
	this->vert_count = vert_count;

	for (int i = 0; i < vert_count; i++) {
		this->verts[i] = verts[i];
		this->colours[i] = colours[i];
	}
}

Poly::~Poly() {
	delete[vert_count] verts;
	delete[vert_count] colours;
}

Vector3& Poly::operator[](std::size_t idx){
	return this->verts[idx];
}