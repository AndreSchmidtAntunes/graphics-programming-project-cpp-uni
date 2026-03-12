#pragma once

#include "Vector3.h"
#include "Colour.h"

#define self (*this)

struct Mesh;

struct Poly {
public:

	uint* indices;
	Colour* colours;
	uint vert_count;

	/// <summary> Pointer to the mesh this polygon is holding indices for. </summary>
	//Mesh* owner;

	Poly() : indices(NULL), colours(NULL), vert_count(0) { };

	Poly(const uint* indices, const uint vert_count);

	Poly(const uint* indices, const Colour* colours, const uint vert_count);

	~Poly();
};