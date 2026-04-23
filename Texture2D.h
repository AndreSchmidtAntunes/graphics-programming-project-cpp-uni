#pragma once

#include <array>
#include "Vector.h"
#include "GLLibs.h"

#define N_DIMS 2
#define SIZE_TYPE size_t
#define ID_TYPE GLuint

struct Texture2D {

	const ID_TYPE getID() const { return _ID; }
	const SIZE_TYPE getWidth() const { return width; }
	const SIZE_TYPE getHeight() const { return height; }

	static const Texture2D* Load(const char* path, const SIZE_TYPE width, const SIZE_TYPE height);

protected:
	union {
		std::array<SIZE_TYPE, N_DIMS> data;
		struct { SIZE_TYPE width, height; };
	};
	ID_TYPE _ID = -1;

	// internal constructor 
	constexpr Texture2D(void) : data({}) {}
	constexpr ~Texture2D(void) { }
};

#undef N_DIMS
#undef SIZE_TYPE
#undef ID_TYPE

#define N_DIMS 2
#define TYPE GLfloat

struct TEX_COORD_MEM_STRUCT {
	union {
		std::array<TYPE, N_DIMS> data;
		struct { TYPE u, v; };
	};
};

struct TexCoord : public Vector::_VectorT<TYPE, N_DIMS, TEX_COORD_MEM_STRUCT> {};

#undef N_DIMS
#undef TYPE