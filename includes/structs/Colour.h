#pragma once

#include "Vector.h"

#define T _Ty

// --- Colour type --- //

#define N_DIMS 4

template<typename T>
struct _COLOUR4_MEM_STRUCT {
	union {
		struct { T r, g, b, a; };
		std::array<T, N_DIMS> data{ };
	};
};

#define BASE Vector::_Basic_Vector<float, N_DIMS, _COLOUR4_MEM_STRUCT<float>>

struct Colour : public BASE {

	using BASE::_Basic_Vector;

	template <typename T1, typename MEMORY_STRUCTURE1>
		Colour(Vector::_Basic_Vector<T1, N_DIMS, MEMORY_STRUCTURE1> other) {
		for (size_t i = 0; i < N_DIMS; i++) {
			(*this)[i] = other[i];
		}
	}

	template <typename T1, typename MEMORY_STRUCTURE1>
		constexpr const Colour& operator *= (const Vector::_Basic_Vector<T1, N_DIMS, MEMORY_STRUCTURE1>& other) {
		for (size_t i = 0; i < N_DIMS; i++)
			(*this)[i] *= other[i];
		return (*this);
	}

	template <typename T1, typename MEMORY_STRUCTURE1>
		friend const constexpr Colour operator * (const Colour& first, const Vector::_Basic_Vector<T1, N_DIMS, MEMORY_STRUCTURE1>& other) {
		return Colour(first) *= other;

	}

	static Colour Hex8(const size_t& hex) {

		const float div255 = 1.0f / 255.0f;

		Colour result;

		const size_t r_mask = 0xff000000;
		const size_t g_mask = 0x00ff0000;
		const size_t b_mask = 0x0000ff00;
		const size_t a_mask = 0x000000ff;

		size_t masked_r = hex & r_mask;
		size_t masked_g = hex & g_mask;
		size_t masked_b = hex & b_mask;
		size_t masked_a = hex & a_mask;

		result.r = float(masked_r >> 24) * div255;
		result.g = float(masked_g >> 16) * div255;
		result.b = float(masked_b >> 8) * div255;
		result.a = float(masked_a) * div255;

		return result;
		
	}

	static const Colour Red;
	static const Colour Green;
	static const Colour Blue;
	static const Colour Yellow;
	static const Colour Cyan;
	static const Colour Magenta;
	static const Colour White;
	static const Colour Black;
	static const Colour Null, Empty;
};

inline const Colour Colour::Red			( 1, 0, 0, 1 );
inline const Colour Colour::Green		( 0, 1, 0, 1 );
inline const Colour Colour::Blue		( 0, 0, 1, 1 );
inline const Colour Colour::Yellow		( 1, 1, 0, 1 );
inline const Colour Colour::Cyan		( 0, 1, 1, 1 );
inline const Colour Colour::Magenta		( 1, 0, 1, 1 );
inline const Colour Colour::White		( 1, 1, 1, 1 );
inline const Colour Colour::Black		( 0, 0, 0, 1 );
inline const Colour Colour::Null, Colour::Empty ( 0, 0, 0, 0 );

#undef BASE

#define BASE Vector::_Basic_Vector<uint8_t, N_DIMS, _COLOUR4_MEM_STRUCT<uint8_t>>

struct Colour255 : public BASE {

	using BASE::_Basic_Vector;

	template <typename T1, typename MEMORY_STRUCTURE1>
		Colour255(Vector::_Basic_Vector<T1, N_DIMS, MEMORY_STRUCTURE1> other) {
		for (size_t i = 0; i < N_DIMS; i++) {
			(*this)[i] = other[i];
		}
	}

	template <typename T1, typename MEMORY_STRUCTURE1>
		constexpr Colour255& operator *= (const Vector::_Basic_Vector<T1, N_DIMS, MEMORY_STRUCTURE1>& other) {
		for (size_t i = 0; i < N_DIMS; i++)
			(*this)[i] *= other[i];
		return (*this);
	}

	template <typename T1, typename MEMORY_STRUCTURE1>
		friend const constexpr Colour255 operator * (const Colour255& first, const Vector::_Basic_Vector<T1, N_DIMS, MEMORY_STRUCTURE1>& other) {
		return Colour255(first) *= other;

	}

	static Colour255 Hex8(const size_t& hex) {

		Colour255 result;

		const size_t r_mask = 0xff000000;
		const size_t g_mask = 0x00ff0000;
		const size_t b_mask = 0x0000ff00;
		const size_t a_mask = 0x000000ff;

		size_t masked_r = hex & r_mask;
		size_t masked_g = hex & g_mask;
		size_t masked_b = hex & b_mask;
		size_t masked_a = hex & a_mask;

		result.r = uint8_t(masked_r >> 24);
		result.g = uint8_t(masked_g >> 16);
		result.b = uint8_t(masked_b >> 8);
		result.a = uint8_t(masked_a);

		return result;
	}

	static const Colour255 Red;
	static const Colour255 Green;
	static const Colour255 Blue;
	static const Colour255 Yellow;
	static const Colour255 Cyan;
	static const Colour255 Magenta;
	static const Colour255 White;
	static const Colour255 Black;
	static const Colour255 Null, Empty;
};

inline const Colour255 Colour255::Red		( 255,   0,   0, 255 );
inline const Colour255 Colour255::Green		(   0, 255,   0, 255 );
inline const Colour255 Colour255::Blue		(   0,   0, 255, 255 );
inline const Colour255 Colour255::Yellow	( 255, 255,   0, 255 );
inline const Colour255 Colour255::Cyan		(   0, 255, 255, 255 );
inline const Colour255 Colour255::Magenta	( 255,   0, 255, 255 );
inline const Colour255 Colour255::White		( 255, 255, 255, 255 );
inline const Colour255 Colour255::Black		(   0,   0,   0, 255 );
inline const Colour255 Colour255::Null,Colour255::Empty ( 0, 0, 0, 0 );

#undef N_DIMS
#undef BASE

// --- ColourRGB type --- //

#define N_DIMS 3

template<typename T>
struct _COLOUR3_MEM_STRUCT {
	union {
		struct { T r, g, b; };
		std::array<T, N_DIMS> data{ };
	};
};

#define BASE Vector::_Basic_Vector<float, N_DIMS, _COLOUR3_MEM_STRUCT<float>>

struct ColourRGB : public BASE {

	using BASE::_Basic_Vector;

	template <typename T1, typename MEMORY_STRUCTURE1>
		ColourRGB(Vector::_Basic_Vector<T1, N_DIMS, MEMORY_STRUCTURE1> other) {
		for (size_t i = 0; i < N_DIMS; i++) {
			(*this)[i] = other[i];
		}
	}

	template <typename T1, typename MEMORY_STRUCTURE1>
		constexpr ColourRGB& operator *= (const Vector::_Basic_Vector<T1, N_DIMS, MEMORY_STRUCTURE1>& other) {
		for (size_t i = 0; i < N_DIMS; i++)
			(*this)[i] *= other[i];
		return (*this);
	}

	template <typename T1, typename MEMORY_STRUCTURE1>
		friend const constexpr ColourRGB operator * (const ColourRGB& first, const Vector::_Basic_Vector<T1, N_DIMS, MEMORY_STRUCTURE1>& other) {
		return ColourRGB(first) *= other;
	}

	static constexpr const ColourRGB Hex6(const size_t& hex) {

		const float div255 = 1.0f / 255.0f;

		ColourRGB result;

		const size_t r_mask = 0xff0000;
		const size_t g_mask = 0x00ff00;
		const size_t b_mask = 0x0000ff;

		size_t masked_r = hex & r_mask;
		size_t masked_g = hex & g_mask;
		size_t masked_b = hex & b_mask;

		result.r = float(masked_r >> 16) * div255;
		result.g = float(masked_g >> 8) * div255;
		result.b = float(masked_b) * div255;

		return result;

	}

	static const ColourRGB Red;
	static const ColourRGB Green;
	static const ColourRGB Blue;
	static const ColourRGB Yellow;
	static const ColourRGB Cyan;
	static const ColourRGB Magenta;
	static const ColourRGB White;
	static const ColourRGB Black, Null, Empty;
};

inline const ColourRGB ColourRGB::Red		( 1, 0, 0 );
inline const ColourRGB ColourRGB::Green		( 0, 1, 0 );
inline const ColourRGB ColourRGB::Blue		( 0, 0, 1 );
inline const ColourRGB ColourRGB::Yellow	( 1, 1, 0 );
inline const ColourRGB ColourRGB::Cyan		( 0, 1, 1 );
inline const ColourRGB ColourRGB::Magenta	( 1, 0, 1 );
inline const ColourRGB ColourRGB::White		( 1, 1, 1 );
inline const ColourRGB ColourRGB::Black,ColourRGB::Null,ColourRGB::Empty ( 0, 0, 0 );

#undef BASE

#define BASE Vector::_Basic_Vector<uint8_t, N_DIMS, _COLOUR3_MEM_STRUCT<uint8_t>>

struct ColourRGB255 : public BASE {

	using BASE::_Basic_Vector;

	template <typename T1, typename MEMORY_STRUCTURE1>
		ColourRGB255(Vector::_Basic_Vector<T1, N_DIMS, MEMORY_STRUCTURE1> other) {
		for (size_t i = 0; i < N_DIMS; i++) {
			(*this)[i] = other[i];
		}
	}

	template <typename T1, typename MEMORY_STRUCTURE1>
		constexpr ColourRGB255& operator *= (const Vector::_Basic_Vector<T1, N_DIMS, MEMORY_STRUCTURE1>& other) {
		for (size_t i = 0; i < N_DIMS; i++)
			(*this)[i] *= other[i];
		return (*this);
	}

	template <typename T1, typename MEMORY_STRUCTURE1>
		friend const constexpr ColourRGB255 operator * (const ColourRGB255& first, const Vector::_Basic_Vector<T1, N_DIMS, MEMORY_STRUCTURE1>& other) {
		return ColourRGB255(first) *= other;

	}

	static constexpr ColourRGB255 Hex6(const size_t& hex) {

		ColourRGB255 result;

		const size_t r_mask = 0xff0000;
		const size_t g_mask = 0x00ff00;
		const size_t b_mask = 0x0000ff;

		size_t masked_r = hex & r_mask;
		size_t masked_g = hex & g_mask;
		size_t masked_b = hex & b_mask;

		result.r = uint8_t(masked_r >> 16);
		result.g = uint8_t(masked_g >> 8);
		result.b = uint8_t(masked_b);

		return result;
	}

	static const ColourRGB255 Red;
	static const ColourRGB255 Green;
	static const ColourRGB255 Blue;
	static const ColourRGB255 Yellow;
	static const ColourRGB255 Cyan;
	static const ColourRGB255 Magenta;
	static const ColourRGB255 White;
	static const ColourRGB255 Black,Null,Empty;
};

inline const ColourRGB255 ColourRGB255::Red			( 255,   0,   0 );
inline const ColourRGB255 ColourRGB255::Green		(   0, 255,   0 );
inline const ColourRGB255 ColourRGB255::Blue		(   0,   0, 255 );
inline const ColourRGB255 ColourRGB255::Yellow		( 255, 255,   0 );
inline const ColourRGB255 ColourRGB255::Cyan		(   0, 255, 255 );
inline const ColourRGB255 ColourRGB255::Magenta		( 255,   0, 255 );
inline const ColourRGB255 ColourRGB255::White		( 255, 255, 255 );
inline const ColourRGB255 ColourRGB255::Black,ColourRGB255::Null,ColourRGB255::Empty ( 0, 0, 0 );

#undef N_DIMS
#undef BASE