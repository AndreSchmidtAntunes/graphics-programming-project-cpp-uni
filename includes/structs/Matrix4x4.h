#pragma once

#include "Vector4.h"
#include "Vector3.h"

struct Matrix3x3;

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

	constexpr Matrix4x4(const Vector4& row_1, const Vector4& row_2, const Vector4& row_3, const Vector4& row_4) {
		setRow(0, row_1);
		setRow(1, row_2);
		setRow(2, row_3);
		setRow(3, row_4);
	}

	constexpr Matrix4x4(const Matrix3x3& matrix) : Matrix4x4(
		matrix[0][0], matrix[0][1], matrix[0][2], 0,
		matrix[1][0], matrix[1][1], matrix[1][2], 0,
		matrix[2][0], matrix[2][1], matrix[2][2], 0,
		0, 0, 0, 1
	) {}

	constexpr ~Matrix4x4(void) {};

	// Static operations

	constexpr static const Matrix4x4 ScaleMatrix(const Vector3& scale) {
		return Matrix4x4(
			scale.x, 0.0f, 0.0f, 0.0f,
			0.0f, scale.y, 0.0f, 0.0f,
			0.0f, 0.0f, scale.z, 0.0f,
			0.0f, 0.0f,  0.0f,   1.0f
		);
	};

	// Used the formula half way through this page: http://www.fastgraph.com/makegames/3drotation/
	static const Matrix4x4 RotationMatrix(const Vector3& axis, const TYPE radians) {

		TYPE c = cos(radians);
		TYPE s = sin(radians);
		TYPE t = 1 - c;

		return Matrix4x4(
			(t * axis.x * axis.x) + c, (t * axis.x * axis.y) - (s * axis.z), (t * axis.x * axis.z) + (s * axis.y), 0,
			(t * axis.x * axis.y) + (s * axis.z), (t * axis.y * axis.y) + c, (t * axis.y * axis.z) - (s * axis.x), 0,
			(t * axis.x * axis.z) - (s * axis.y), (t * axis.y * axis.z) + (s * axis.x), (t * axis.z * axis.z) + c, 0,
			0, 0, 0, 1
		);
	};

	constexpr static const Matrix4x4 TranslationMatrix(const Vector3& translation) {
		return Matrix4x4(
			1, 0, 0, translation.x,
			0, 1, 0, translation.y,
			0, 0, 1, translation.z,
			0, 0, 0, 1
		);
	};

	// Setters

	constexpr void setElementAt(const size_t row_index, const size_t column_index, const TYPE value) {
		(*this)[row_index][column_index] = value;
	}

	constexpr void setRow(const size_t row_index, const Vector4& elements) {
		for (size_t i = 0; i < DIMENTIONS; i++)
			(*this)[row_index][i] = elements[i];
	}


	constexpr void setColumn(const size_t column_index, const Vector4& elements) {
		for (size_t i = 0; i < DIMENTIONS; i++)
			(*this)[i][column_index] = elements[i];
	}

	// Getters

	constexpr const TYPE getElementAt(const size_t row_index, const size_t column_index) const {
		return data[row_index][column_index];
	}


	constexpr const Vector4 getRow(const size_t row_index) const {
		return Vector4((*this)[row_index][0], (*this)[row_index][1], (*this)[row_index][2], (*this)[row_index][3]);
	}


	constexpr const Vector4 getColumn(const size_t column_index) const {
		return Vector4((*this)[0][column_index], (*this)[1][column_index], (*this)[2][column_index], (*this)[3][column_index]);
	}


	constexpr std::array<TYPE, DIMENTIONS>& operator [] (const size_t idx) {
		return data[idx];
	}


	constexpr const std::array<TYPE, DIMENTIONS>& operator[](const size_t idx) const {
		return data[idx];
	}


	constexpr Matrix4x4& operator = (const Matrix4x4& other) {
		for (size_t row = 0; row < DIMENTIONS; row++)
			for (size_t col = 0; col < DIMENTIONS; col++)
				(*this)[row][col] = other[row][col];

		return (*this);
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


	constexpr const Vector4 operator * (const Vector4& mult) const {
		Vector4 result = Vector4();

		for (size_t i = 0; i < DIMENTIONS; i++) {

			TYPE sum = 0;
			for (size_t j = 0; j < DIMENTIONS; j++) {
				sum += ((*this)[i][j] * mult[j]);
			}
			result[i] = sum;
		}
		return result;
	}


	constexpr const Vector3 operator * (const Vector3& mult) const {
		Vector4 result = (*this) * Vector4(mult);
		return (Vector3)result;
	}


	constexpr const Matrix4x4 operator * (const Matrix4x4& other) const {
		Matrix4x4 result = Matrix4x4();
		for (size_t row = 0; row < DIMENTIONS; row++)
			for (size_t col = 0; col < DIMENTIONS; col++) {
				result[row][col] *= other[row][col];
			}
		return result;
	}


	constexpr const Matrix4x4 operator * (const TYPE mult) const {
		Matrix4x4 result = Matrix4x4();
		for (size_t row = 0; row < DIMENTIONS; row++)
			for (size_t col = 0; col < DIMENTIONS; col++) {
				result[row][col] *= mult;
			}
		return result;
	}

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