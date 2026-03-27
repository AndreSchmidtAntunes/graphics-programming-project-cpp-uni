#pragma once

#include "Matrix3x3.h"

template<class T = double>
struct Quaternion {
public:

	static_assert(std::is_floating_point<T>::value,
		"class T can only be instantiated with floating point types. (E.g: float, double, half)");

	union {
		struct { T i, j, k, scaler; };
		struct { T x, y, z, w;		 };

		std::array<double, 4> data { };
	};

	T& operator [] (const uint idx) { return data[idx]; }
	const T& operator [] (const uint idx) const { return data[idx]; }




};