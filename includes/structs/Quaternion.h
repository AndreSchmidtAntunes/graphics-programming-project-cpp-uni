#pragma once

#include <array>
#include <type_traits>
//class Matrix3x3;

template<typename T = double>
struct Quaternion {
public:

	static_assert(std::is_arithmetic<T>::value,
		"Quaternion: T must be arithmetic!");

	union {

		struct { T i, j, k, scaler; };
		struct { T x, y, z, w;		};

		std::array<T, 4> data { };
	};

	T& operator [] (const size_t idx) { return data[idx]; }
	const T& operator [] (const size_t idx) const { return data[idx]; }

	const static Quaternion 
		Identity,
		Zero;

	Quaternion() : i(0), j(0), k(0), scaler(1) {};
};