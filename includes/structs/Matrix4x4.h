#pragma once

#include "Quaternion.h"
#include "Vector3.h"
#include "Vector4.h"

#define T _Ty
#define N_DIMS 4

template <typename T> requires (std::is_arithmetic<T>::value)
struct _Matrix4x4T {

	union {
		struct {
			struct { T m11, m12, m13, m14; };
			struct { T m21, m22, m23, m24; };
			struct { T m31, m32, m33, m34; };
			struct { T m41, m42, m43, m44; };
		};
		std::array<std::array<T, N_DIMS>, N_DIMS> data{ };
	};


	constexpr _Matrix4x4T(
		T m1_1, T m1_2, T m1_3, T m1_4,
		T m2_1, T m2_2, T m2_3, T m2_4,
		T m3_1, T m3_2, T m3_3, T m3_4,
		T m4_1, T m4_2, T m4_3, T m4_4

	) : data({ { m1_1, m1_2, m1_3, m1_4 },
			   { m2_1, m2_2, m2_3, m2_4 },
			   { m3_1, m3_2, m3_3, m3_4 },
			   { m4_1, m4_2, m4_3, m4_4 } }) {};

	constexpr _Matrix4x4T(const T values[N_DIMS][N_DIMS]) {
		for (size_t row = 0; row < N_DIMS; row++)
			for (size_t col = 0; col < N_DIMS; col++) {
				data[row][col] = values[row][col];
			}
	}

	constexpr _Matrix4x4T(const _Vector4T<T>& row_1, const _Vector4T<T>& row_2, const _Vector4T<T>& row_3, const _Vector4T<T>& row_4) {
		setRow(0, row_1);
		setRow(1, row_2);
		setRow(2, row_3);
		setRow(3, row_4);
	}

	constexpr ~_Matrix4x4T(void) {};

	constexpr _Matrix4x4T(void) : _Matrix4x4T(Identity) {};

	// Static operations

	constexpr static const _Matrix4x4T ScaleMatrix(const _Vector3T<T>& scale) {
		return _Matrix4x4T(
			scale.x, 0.0f, 0.0f, 0.0f,
			0.0f, scale.y, 0.0f, 0.0f,
			0.0f, 0.0f, scale.z, 0.0f,
			0.0f, 0.0f,  0.0f,   1.0f
		);
	};

	// Used the formula half way through this page: http://www.fastgraph.com/makegames/3drotation/
	static const _Matrix4x4T RotationMatrix(const _Vector3T<T>& axis, const T radians) {

		T c = cos(radians);
		T s = sin(radians);
		T t = 1 - c;

		return _Matrix4x4T(
			(t * axis.x * axis.x) + c, (t * axis.x * axis.y) - (s * axis.z), (t * axis.x * axis.z) + (s * axis.y), 0.0f,
			(t * axis.x * axis.y) + (s * axis.z), (t * axis.y * axis.y) + c, (t * axis.y * axis.z) - (s * axis.x), 0.0f,
			(t * axis.x * axis.z) - (s * axis.y), (t * axis.y * axis.z) + (s * axis.x), (t * axis.z * axis.z) + c, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	};

	// thank you to the quaternions library by ferd36 for this rotation matrix conversion implementation below.
// The entire module can be found here: https://github.com/ferd36/quaternions/tree/master
	static const _Matrix4x4T RotationMatrix(const Quaternion& q) { /// WARNING: might be the cause of a circular include 

		T a2 = q.w * q.w, b2 = q.x * q.x, c2 = q.y * q.y, d2 = q.z * q.z;
		T wx = q.w * q.x, ac = q.w * q.y, ad = q.w * q.z;
		T xy = q.x * q.y, bd = q.x * q.z;
		T yz = q.y * q.z;

		return _Matrix4x4T(
			a2 + b2 - c2 - d2,	2 * (xy - ad),		2 * (bd + ac),		0.0f,
			2 * (xy + ad),		a2 - b2 + c2 - d2,	2 * (yz - wx),		0.0f,
			2 * (bd - ac),		2 * (yz + wx),		a2 - b2 - c2 + d2,	0.0f,
			0.0f,				0.0f,				0.0f,				1.0f);
	}

	constexpr static const _Matrix4x4T TranslationMatrix(const _Vector3T<T>& translation) {
		return _Matrix4x4T(
			1.0f, 0.0f, 0.0f, translation.x,
			0.0f, 1.0f, 0.0f, translation.y,
			0.0f, 0.0f, 1.0f, translation.z,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	};

	// Setters

	constexpr void setElementAt(const size_t row_index, const size_t column_index, const T value) {
		(*this)[row_index][column_index] = value;
	}

	constexpr void setRow(const size_t row_index, const _Vector4T<T>& elements) {
		for (size_t i = 0; i < N_DIMS; i++)
			(*this)[row_index][i] = elements[i];
	}


	constexpr void setColumn(const size_t column_index, const _Vector4T<T>& elements) {
		for (size_t i = 0; i < N_DIMS; i++)
			(*this)[i][column_index] = elements[i];
	}

	// Getters

	constexpr const T getElementAt(const size_t row_index, const size_t column_index) const {
		return data[row_index][column_index];
	}


	constexpr const _Vector4T<T> getRow(const size_t row_index) const {
		return _Vector4T<T>((*this)[row_index][0], (*this)[row_index][1], (*this)[row_index][2], (*this)[row_index][3]);
	}


	constexpr const _Vector4T<T> getColumn(const size_t column_index) const {
		return _Vector4T<T>((*this)[0][column_index], (*this)[1][column_index], (*this)[2][column_index], (*this)[3][column_index]);
	}


	constexpr std::array<T, N_DIMS>& operator [] (const size_t idx) {
		return data[idx];
	}


	constexpr const std::array<T, N_DIMS>& operator [] (const size_t idx) const {
		return data[idx];
	}

	constexpr void operator = (const _Matrix4x4T& other) {
		for (size_t row = 0; row < N_DIMS; row++)
			for (size_t col = 0; col < N_DIMS; col++)
				(*this)[row][col] = other[row][col];
	}

	// --- Vector 4 --- //

	constexpr const _Vector4T<T> operator * (const _Vector4T<T>& mult) const {
		return _Vector4T<T> {
			(*this)[0][0] * mult.x + (*this)[0][1] * mult.y + (*this)[0][2] * mult.z + (*this)[0][3] * mult.w,
			(*this)[1][0] * mult.x + (*this)[1][1] * mult.y + (*this)[1][2] * mult.z + (*this)[1][3] * mult.w,
			(*this)[2][0] * mult.x + (*this)[2][1] * mult.y + (*this)[2][2] * mult.z + (*this)[2][3] * mult.w,
			(*this)[3][0] * mult.x + (*this)[3][1] * mult.y + (*this)[3][2] * mult.z + (*this)[3][3] * mult.w
		};
	}

	constexpr _Vector4T<T>& operator *= (_Vector4T<T>& vec) {
		vec.x = (*this)[0][0] * vec.x + (*this)[0][1] * vec.y + (*this)[0][2] * vec.z + (*this)[0][3] * vec.w;
		vec.y = (*this)[1][0] * vec.x + (*this)[1][1] * vec.y + (*this)[1][2] * vec.z + (*this)[1][3] * vec.w;
		vec.z = (*this)[2][0] * vec.x + (*this)[2][1] * vec.y + (*this)[2][2] * vec.z + (*this)[2][3] * vec.w;
		vec.w = (*this)[3][0] * vec.x + (*this)[3][1] * vec.y + (*this)[3][2] * vec.z + (*this)[3][3] * vec.w;
		return vec;
	}

	constexpr const _Matrix4x4T operator * (const _Matrix4x4T& other) const {

		_Matrix4x4T result;
		for (size_t row = 0; row < N_DIMS; row++) {
			for (size_t col = 0; col < N_DIMS; col++) {
				T dot = getRow(row).Dot(other.getColumn(col));
				result[row][col] = dot;
			}
		}
		return result;
	}

	constexpr _Matrix4x4T& operator *= (const _Matrix4x4T& other) {
		(*this) = (*this) * other;
		return (*this);
	}

	constexpr _Matrix4x4T& operator *= (const T mult) {
		for (size_t row = 0; row < N_DIMS; row++)
			for (size_t col = 0; col < N_DIMS; col++) {
				data[row][col] *= mult;
			}
		return (*this);
	}

	constexpr const _Matrix4x4T operator * (const T mult) const {
		return _Matrix4x4T(*this) *= mult;
	}

	constexpr const _Vector3T<T> ApplyTransform(const _Vector3T<T>& point = _Vector3T<T>::Zero) const {
		return _Vector3T<T>((*this) * _Vector4T<T>(point + _Vector4T<T>::Ana));
	};

	// Constants

	static const _Matrix4x4T<T> Identity;

	static const _Matrix4x4T<T> Zero;
};

template <typename T> requires (std::is_arithmetic<T>::value)
inline const _Matrix4x4T<T> _Matrix4x4T<T>::Identity {
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

template <typename T> requires (std::is_arithmetic<T>::value)
inline const _Matrix4x4T<T> _Matrix4x4T<T>::Zero {
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0
};

#undef N_DIMS
#undef T

typedef _Matrix4x4T <double> Matrix4x4D;
typedef _Matrix4x4T <float> Matrix4x4;