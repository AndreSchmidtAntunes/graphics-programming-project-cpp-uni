#pragma once

#include "Vector3.h"

#define TYPE float
#define DIMENTIONS 3

struct Matrix3x3 {

public:

	static_assert(std::is_arithmetic<TYPE>::value,
		"Matrix3x3: TYPE must be arithmetic!");

	std::array<std::array<TYPE, DIMENTIONS>, DIMENTIONS> data{ };

	constexpr Matrix3x3() : Matrix3x3(identity) {};

	constexpr Matrix3x3(
		TYPE m1_1, TYPE m1_2, TYPE m1_3,
		TYPE m2_1, TYPE m2_2, TYPE m2_3,
		TYPE m3_1, TYPE m3_2, TYPE m3_3

	) : data({ { m1_1, m1_2, m1_3 },
			   { m2_1, m2_2, m2_3 },
			   { m3_1, m3_2, m3_3 }  }) {
	};

	constexpr Matrix3x3(const TYPE values[DIMENTIONS][DIMENTIONS]) {
		for (size_t row = 0; row < DIMENTIONS; row++)
			for (size_t col = 0; col < DIMENTIONS; col++) {
				data[row][col] = values[row][col];
			}
	}

	constexpr Matrix3x3(const Vector3& row_1, const Vector3& row_2, const Vector3& row_3) {
		setRow(0, row_1);
		setRow(1, row_2);
		setRow(2, row_3);
	};

	constexpr ~Matrix3x3(void) {};

	// Static operations

	inline constexpr static const Matrix3x3 ScaleMatrix(const Vector3& scale) {
		return Matrix3x3(
			scale.x, 0.0f, 0.0f,
			0.0f, scale.y, 0.0f,
			0.0f, 0.0f, scale.z
		);
	};

	inline static const Matrix3x3 RotationMatrix(const Vector3& axis, const TYPE radians) {

		TYPE c = cos(radians);
		TYPE s = sin(radians);
		TYPE t = 1 - c;

		return Matrix3x3(
			(t * axis.x * axis.x) + c, (t * axis.x * axis.y) - (s * axis.z), (t * axis.x * axis.z) + (s * axis.y),
			(t * axis.x * axis.y) + (s * axis.z), (t * axis.y * axis.y) + c, (t * axis.y * axis.z) - (s * axis.x),
			(t * axis.x * axis.z) - (s * axis.y), (t * axis.y * axis.z) + (s * axis.x), (t * axis.z * axis.z) + c
		);
	};

	inline constexpr static const Matrix3x3 CrossProductMatrix(const Vector3& direction) {

		return Matrix3x3(
			0, -direction.z, direction.y,
			direction.z, 0, -direction.x,
			-direction.y, direction.x, 0
		);
	};

	// Setters

	constexpr void setElementAt(const size_t row_index, const size_t column_index, const TYPE value) {
		(*this)[row_index][column_index] = value;
	};

	constexpr void setRow(const size_t row_index, const Vector3& elements) {
		for (size_t i = 0; i < DIMENTIONS; i++)
			(*this)[row_index][i] = elements[i];
	};

	constexpr void setColumn(const size_t column_index, const Vector3& elements) {
		for (size_t i = 0; i < DIMENTIONS; i++)
			(*this)[i][column_index] = elements[i];
	};

	// Getters

	constexpr const TYPE getElementAt(const size_t row_index, const size_t column_index) const {
		return data[row_index][column_index];
	}

	constexpr const Vector3 getRow(const size_t row_index) const {
		return Vector3((*this)[row_index][0], (*this)[row_index][1], (*this)[row_index][2]);
	}

	constexpr const Vector3 getColumn(const size_t column_index) const {
		return Vector3((*this)[0][column_index], (*this)[1][column_index], (*this)[2][column_index]);
	}

	// Operators

	constexpr std::array<TYPE, DIMENTIONS>& operator [] (const size_t idx) {
		return data[idx];
	};

	constexpr const std::array<TYPE, DIMENTIONS>& operator [] (const size_t idx) const {
		return data[idx];
	};
	
	constexpr Matrix3x3& operator = (const Matrix3x3& other) {
		for (size_t row = 0; row < DIMENTIONS; row++)
			for (size_t col = 0; col < DIMENTIONS; col++)
				(*this)[row][col] = other[row][col];

		return (*this);
	};

	constexpr Matrix3x3& operator *= (const Matrix3x3& other) {
		int i, j, m;
		for (i = 0; i < DIMENTIONS; i++)
			for (j = 0; j < DIMENTIONS; j++)
				for (m = 0; m < DIMENTIONS; m++)
					(*this)[i][j] += (*this)[i][m] * other[m][j];
		return (*this);
	};

	constexpr Matrix3x3& operator *= (TYPE mult) {
		for (size_t row = 0; row < DIMENTIONS; row++)
			for (size_t col = 0; col < DIMENTIONS; col++) {
				data[row][col] *= mult;
			}
		return (*this);
	};

	constexpr Vector3 operator * (const Vector3& mult) const {
		Vector3 result;

		for (size_t i = 0; i < DIMENTIONS; i++) {

			TYPE sum = 0;
			for (size_t j = 0; j < DIMENTIONS; j++) {
				sum += ((*this)[i][j] * mult[j]);
			}
			result[i] = sum;
		}
		return result;
	};

	constexpr Matrix3x3 operator * (const Matrix3x3& other) const {
		return Matrix3x3(*this) *= other;
	};

	constexpr Matrix3x3 operator * (const TYPE mult) const {
		Matrix3x3 result = Matrix3x3();
		for (size_t row = 0; row < DIMENTIONS; row++)
			for (size_t col = 0; col < DIMENTIONS; col++) {
				result[row][col] *= mult;
			}
		return result;
	};

	// Constants

	static const Matrix3x3 identity;
	static const Matrix3x3 zero;
};

inline const Matrix3x3 Matrix3x3::identity (
	1, 0, 0,
	0, 1, 0,
	0, 0, 1
);

inline const Matrix3x3 Matrix3x3::zero (
	0, 0, 0,
	0, 0, 0,
	0, 0, 0
);

#undef DIMENTIONS
#undef TYPE
