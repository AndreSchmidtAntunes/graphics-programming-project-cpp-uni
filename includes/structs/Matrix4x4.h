#pragma once

#include "Vector4.h"
#include "Vector3.h"

#include "Quaternion.h"
#include "Matrix3x3.h"

#define TYPE float
#define DIMENTIONS 4

struct Matrix4x4 {

public:

	static_assert(std::is_arithmetic<TYPE>::value,
		"typename TYPE can only be instantiated with floating point types. (E.g: float, double, half)");

	std::array<std::array<TYPE, DIMENTIONS>, DIMENTIONS> data{ };

	constexpr Matrix4x4() : Matrix4x4(identity) {};

	constexpr Matrix4x4(
		TYPE m1_1, TYPE m1_2, TYPE m1_3, TYPE m1_4,
		TYPE m2_1, TYPE m2_2, TYPE m2_3, TYPE m2_4,
		TYPE m3_1, TYPE m3_2, TYPE m3_3, TYPE m3_4,
		TYPE m4_1, TYPE m4_2, TYPE m4_3, TYPE m4_4

	) : data({ { m1_1, m1_2, m1_3, m1_4 },
			   { m2_1, m2_2, m2_3, m2_4 },
			   { m3_1, m3_2, m3_3, m3_4 },
			   { m4_1, m4_2, m4_3, m4_4 } }) {};

	constexpr Matrix4x4(const TYPE values[DIMENTIONS][DIMENTIONS]) {
		for (size_t row = 0; row < DIMENTIONS; row++)
			for (size_t col = 0; col < DIMENTIONS; col++) {
				data[row][col] = values[row][col];
			}
	}

	constexpr Matrix4x4(const _Vector4T<TYPE>& row_1, const _Vector4T<TYPE>& row_2, const _Vector4T<TYPE>& row_3, const _Vector4T<TYPE>& row_4) {
		setRow(0, row_1);
		setRow(1, row_2);
		setRow(2, row_3);
		setRow(3, row_4);
	}

	constexpr Matrix4x4(const Matrix3x3& matrix) : Matrix4x4 (
		matrix[0][0], matrix[0][1], matrix[0][2], 0,
		matrix[1][0], matrix[1][1], matrix[1][2], 0,
		matrix[2][0], matrix[2][1], matrix[2][2], 0,
		0, 0, 0, 1
	) {}

	constexpr ~Matrix4x4(void) {};

	// Static operations

	constexpr static const Matrix4x4 ScaleMatrix(const _Vector3T<TYPE>& scale) {
		return Matrix4x4(
			scale.x, 0.0f, 0.0f, 0.0f,
			0.0f, scale.y, 0.0f, 0.0f,
			0.0f, 0.0f, scale.z, 0.0f,
			0.0f, 0.0f,  0.0f,   1.0f
		);
	};

	// Used the formula half way through this page: http://www.fastgraph.com/makegames/3drotation/
	static const Matrix4x4 RotationMatrix(const _Vector3T<TYPE>& axis, const TYPE radians) {

		TYPE c = cos(radians);
		TYPE s = sin(radians);
		TYPE t = 1 - c;

		return Matrix4x4(
			(t * axis.x * axis.x) + c, (t * axis.x * axis.y) - (s * axis.z), (t * axis.x * axis.z) + (s * axis.y), 0.0f,
			(t * axis.x * axis.y) + (s * axis.z), (t * axis.y * axis.y) + c, (t * axis.y * axis.z) - (s * axis.x), 0.0f,
			(t * axis.x * axis.z) - (s * axis.y), (t * axis.y * axis.z) + (s * axis.x), (t * axis.z * axis.z) + c, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	};

	// thank you to the quaternions library by ferd36 for this rotation matrix conversion implementation below.
// The entire module can be found here: https://github.com/ferd36/quaternions/tree/master
	static const Matrix4x4 RotationMatrix(const Quaternion& q) { /// WARNING: might be the cause of a circular include 

		TYPE a2 = q.w * q.w, b2 = q.x * q.x, c2 = q.y * q.y, d2 = q.z * q.z;
		TYPE wx = q.w * q.x, ac = q.w * q.y, ad = q.w * q.z;
		TYPE xy = q.x * q.y, bd = q.x * q.z;
		TYPE yz = q.y * q.z;

		return Matrix4x4(
			a2 + b2 - c2 - d2,	2 * (xy - ad),		2 * (bd + ac),		0.0f,
			2 * (xy + ad),		a2 - b2 + c2 - d2,	2 * (yz - wx),		0.0f,
			2 * (bd - ac),		2 * (yz + wx),		a2 - b2 - c2 + d2,	0.0f,
			0.0f,				0.0f,				0.0f,				1.0f);
	}

	constexpr static const Matrix4x4 TranslationMatrix(const _Vector3T<TYPE>& translation) {
		return Matrix4x4(
			1.0f, 0.0f, 0.0f, translation.x,
			0.0f, 1.0f, 0.0f, translation.y,
			0.0f, 0.0f, 1.0f, translation.z,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	};

	// Setters

	constexpr void setElementAt(const size_t row_index, const size_t column_index, const TYPE value) {
		(*this)[row_index][column_index] = value;
	}

	constexpr void setRow(const size_t row_index, const _Vector4T<TYPE>& elements) {
		for (size_t i = 0; i < DIMENTIONS; i++)
			(*this)[row_index][i] = elements[i];
	}


	constexpr void setColumn(const size_t column_index, const _Vector4T<TYPE>& elements) {
		for (size_t i = 0; i < DIMENTIONS; i++)
			(*this)[i][column_index] = elements[i];
	}

	// Getters

	constexpr const TYPE getElementAt(const size_t row_index, const size_t column_index) const {
		return data[row_index][column_index];
	}


	constexpr const _Vector4T<TYPE> getRow(const size_t row_index) const {
		return _Vector4T<TYPE>((*this)[row_index][0], (*this)[row_index][1], (*this)[row_index][2], (*this)[row_index][3]);
	}


	constexpr const _Vector4T<TYPE> getColumn(const size_t column_index) const {
		return _Vector4T<TYPE>((*this)[0][column_index], (*this)[1][column_index], (*this)[2][column_index], (*this)[3][column_index]);
	}


	constexpr std::array<TYPE, DIMENTIONS>& operator [] (const size_t idx) {
		return data[idx];
	}


	constexpr const std::array<TYPE, DIMENTIONS>& operator [] (const size_t idx) const {
		return data[idx];
	}

	constexpr void operator = (const Matrix4x4& other) {
		for (size_t row = 0; row < DIMENTIONS; row++)
			for (size_t col = 0; col < DIMENTIONS; col++)
				(*this)[row][col] = other[row][col];
	}

	constexpr const _Vector4T<TYPE> operator * (const _Vector4T<TYPE>& mult) const {
		return _Vector4T<TYPE> {
			(*this)[0][0] * mult.x + (*this)[0][1] * mult.y + (*this)[0][2] * mult.z + (*this)[0][3] * mult.w,
			(*this)[1][0] * mult.x + (*this)[1][1] * mult.y + (*this)[1][2] * mult.z + (*this)[1][3] * mult.w,
			(*this)[2][0] * mult.x + (*this)[2][1] * mult.y + (*this)[2][2] * mult.z + (*this)[2][3] * mult.w,
			(*this)[3][0] * mult.x + (*this)[3][1] * mult.y + (*this)[3][2] * mult.z + (*this)[3][3] * mult.w
		};
	}

	constexpr _Vector4T<TYPE>& operator *= (_Vector4T<TYPE>& vec) {
		vec.x = (*this)[0][0] * vec.x + (*this)[0][1] * vec.y + (*this)[0][2] * vec.z + (*this)[0][3] * vec.w;
		vec.y = (*this)[1][0] * vec.x + (*this)[1][1] * vec.y + (*this)[1][2] * vec.z + (*this)[1][3] * vec.w;
		vec.z = (*this)[2][0] * vec.x + (*this)[2][1] * vec.y + (*this)[2][2] * vec.z + (*this)[2][3] * vec.w;
		vec.w = (*this)[3][0] * vec.x + (*this)[3][1] * vec.y + (*this)[3][2] * vec.z + (*this)[3][3] * vec.w;
		return vec;
	}

	constexpr const Matrix4x4 operator * (const Matrix4x4& other) const {

		Matrix4x4 result;
		for (size_t row = 0; row < DIMENTIONS; row++) {
			for (size_t col = 0; col < DIMENTIONS; col++) {
				TYPE dot = getRow(row).Dot(other.getColumn(col));
				result[row][col] = dot;
			}
		}
		return result;
	}

	constexpr Matrix4x4& operator *= (const Matrix4x4& other) {
		(*this) = (*this) * other;
		return (*this);
	}

	constexpr Matrix4x4& operator *= (const TYPE mult) {
		for (size_t row = 0; row < DIMENTIONS; row++)
			for (size_t col = 0; col < DIMENTIONS; col++) {
				data[row][col] *= mult;
			}
		return (*this);
	}

	constexpr const Matrix4x4 operator * (const TYPE mult) const {
		return Matrix4x4(*this) *= mult;
	}

	constexpr const _Vector3T<TYPE> ApplyTransform(const _Vector3T<TYPE>& point = _Vector3T<TYPE>::Zero) const {
		return _Vector3T<TYPE>((*this) * _Vector4T<TYPE>(point + _Vector4T<TYPE>::Ana));
	};

	// Constants

	static const Matrix4x4 identity;
	static const Matrix4x4 zero;
};

inline const Matrix4x4 Matrix4x4::identity = Matrix4x4(
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
);

inline const Matrix4x4 Matrix4x4::zero = Matrix4x4(
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0
);

#undef DIMENTIONS
#undef TYPE