#pragma once

#include "Vector3.h"
#include "Colour.h"

struct Poly {
public:

	Vector3* verts;
	Colour* colours;
	int vert_count;

	Poly(Vector3* verts, int vert_count);

	Poly(Vector3* vert, Colour* colours, int vert_count);

	~Poly();

	inline Vector3& operator [] (int i);
};