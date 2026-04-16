#pragma once

#include "Vector3.h"

#define TYPE float
#define DIMENTIONS 3

struct Matrix3x3 {

public:

	static_assert(std::is_arithmetic<TYPE>::value,
		"Matrix3x3: TYPE must be arithmetic!");

	std::array<std::array<TYPE, DIMENTIONS>, DIMENTIONS> data{ };

	constexpr Matrix3x3(
		TYPE m1_1, TYPE m1_2, TYPE m1_3,
		TYPE m2_1, TYPE m2_2, TYPE m2_3,
		TYPE m3_1, TYPE m3_2, TYPE m3_3
	);


	constexpr Matrix3x3(const TYPE[DIMENTIONS][DIMENTIONS]);
	constexpr Matrix3x3(const Vector3& row_1, const Vector3& row_2, const Vector3& row_3);

	constexpr Matrix3x3() : Matrix3x3(identity) {};

	constexpr ~Matrix3x3(void) {};

	// Static operations

	constexpr static Matrix3x3 ScaleMatrix(const Vector3& scale);
	static Matrix3x3 RotationMatrix(const Vector3& axis, TYPE radians);

	constexpr static Matrix3x3 CrossProductMatrix(const Vector3& direction);

	// Setters

	constexpr void setElementAt(size_t row_index, size_t column_index, TYPE value);

	constexpr void setRow(size_t row_index, const Vector3& elements);

	constexpr void setColumn(size_t column_index, const Vector3& elements);

	// Getters

	constexpr TYPE getElementAt(size_t row_index, size_t column_index) const;

	constexpr Vector3 getRow(size_t row_index) const;

	constexpr Vector3 getColumn(size_t column_index) const;

	// Operators
	
	constexpr Matrix3x3& operator = (const Matrix3x3& other);

	constexpr Matrix3x3& operator *= (const Matrix3x3& other);
	constexpr Matrix3x3& operator *= (TYPE mult);


	constexpr friend Vector3& operator *= (Vector3& lhs, const Matrix3x3& rhs);

	constexpr Vector3 operator * (const Vector3& mult) const;

	constexpr Matrix3x3 operator * (const Matrix3x3& other) const;
	constexpr Matrix3x3 operator * (const TYPE mult) const;

	constexpr std::array<TYPE, DIMENTIONS>& operator [] (const size_t idx);
	constexpr const std::array<TYPE, DIMENTIONS>& operator [] (const size_t idx) const;

	// Constants

	static const Matrix3x3 identity;
	static const Matrix3x3 zero;
};

#undef DIMENTIONS
#undef TYPE