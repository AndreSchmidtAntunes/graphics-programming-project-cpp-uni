#pragma once

#include "Vector3.h"
#include "Colour.h"

struct Poly {
public:

	Vector3* verts;
	Colour* colours;
	int vert_count;

	Poly() : verts(NULL), colours(NULL), vert_count(0) {} ;

	Poly(const Vector3* verts, int vert_count);
	
	Poly(const Vector3* vert, const Colour* colours, int vert_count);

	~Poly();

	Vector3& operator [] (std::size_t idx);
};