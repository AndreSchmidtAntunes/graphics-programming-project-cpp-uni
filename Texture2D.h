#pragma once

#include <array>
#include "Vector.h"
#include "GLLibs.h"

#define N_DIMS 2
#define ID_TYPE GLuint

struct Texture2D {

	const ID_TYPE& getID() const	{ return _ID; }
	const size_t& getWidth() const	{ return data[0]; }
	const size_t& getHeight() const { return data[1]; }

	static const Texture2D* FromFile(const char* file_path, const size_t width, const size_t height);
	const bool LoadFile(const char* file_path, const size_t width, const size_t height);

	Texture2D(const char* file_path, const size_t width, const size_t height) {
		LoadFile(file_path, width, height);
	}

	constexpr ~Texture2D(void) {
		if (_ID != 0)
			glDeleteTextures(1, &_ID);
	}

protected:
	union {
		std::array<size_t, N_DIMS> data;
		struct { size_t width, height; };
	};
	ID_TYPE _ID = 0;

	// internal constructor 
	constexpr Texture2D(void) : data({}) {}
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