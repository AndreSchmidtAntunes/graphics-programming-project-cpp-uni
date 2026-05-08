#pragma once

#include <array>
#include "Vector.h"
#include "GLLibs.h"
#include "GLExtras.h"

#define N_DIMS 2
#define ID_TYPE size_t

struct Texture2D {

	const ID_TYPE& getID() const	{ return _ID; }
	const size_t& getWidth() const	{ return data[0]; }
	const size_t& getHeight() const { return data[1]; }

	static Texture2D* FromFileRAW(const char* file_path, const size_t width, const size_t height);
	static Texture2D* FromFileBMP(const char* file_path);
	
	const bool LoadFileRAW(const char* file_path, const size_t width, const size_t height);
	const bool LoadFileBMP(const char* file_path);

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

	const bool LoadRawData(const char* data, const size_t width, const size_t height, const char* file_path);
};

#undef N_DIMS
#undef SIZE_TYPE
#undef ID_TYPE

#define N_DIMS 2
#define TYPE float

struct TEX_COORD_MEM_STRUCT {
	union {
		std::array<TYPE, N_DIMS> data;
		struct { TYPE u, v; };
	};
};

struct TexCoord : public Vector::_Basic_Vector<TYPE, N_DIMS, TEX_COORD_MEM_STRUCT> {};

#undef N_DIMS
#undef TYPE