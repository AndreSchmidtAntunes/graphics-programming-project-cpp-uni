#pragma once

#include "Vector3.h"
#include "Vector4.h"

struct Matrix3x3;

#define TYPE float
#define DIMENTIONS 4

struct Matrix4x4 {

public:

	static_assert(std::is_arithmetic<TYPE>::value,
		"typename TYPE can only be instantiated with floating point types. (E.g: float, double, half)");

	std::array<std::array<TYPE, DIMENTIONS>, DIMENTIONS> data{ };

	constexpr Matrix4x4(
		TYPE m1_1, TYPE m1_2, TYPE m1_3, TYPE m1_4,
		TYPE m2_1, TYPE m2_2, TYPE m2_3, TYPE m2_4,
		TYPE m3_1, TYPE m3_2, TYPE m3_3, TYPE m3_4,
		TYPE m4_1, TYPE m4_2, TYPE m4_3, TYPE m4_4
	);

	constexpr Matrix4x4();
	constexpr Matrix4x4(TYPE[DIMENTIONS][DIMENTIONS]);
	constexpr Matrix4x4(Vector4 row_1, Vector4 row_2, Vector4 row_3, Vector4 row_4);

	constexpr Matrix4x4(Matrix3x3 matrix);

	constexpr ~Matrix4x4();

	// Static operations

	constexpr static Matrix4x4 ScaleMatrix(Vector3 scale);
	static Matrix4x4 RotationMatrix(Vector3 axis, TYPE radians);
	constexpr static Matrix4x4 TranslationMatrix(Vector3 translation);

	constexpr static Matrix4x4 CrossProductMatrix(Vector3 direction);

	// Setters

	constexpr void setElementAt(size_t row_index, size_t column_index, TYPE value);

	constexpr void setRow(size_t row_index, Vector4 elements);

	constexpr void setColumn(size_t column_index, Vector4 elements);

	// Getters

	constexpr TYPE getElementAt(size_t row_index, size_t column_index);

	constexpr Vector4 getRow(size_t row_index);

	constexpr Vector4 getColumn(size_t column_index);

	// Operators

	constexpr Matrix4x4& operator = (const Matrix4x4& other);

	constexpr Matrix4x4& operator *= (const Matrix4x4& other);
	constexpr Matrix4x4& operator *= (const TYPE mult);


	constexpr Vector4 operator * (const Vector4& mult) const;
	constexpr Vector3 operator * (const Vector3& mult) const;

	constexpr Matrix4x4 operator * (const Matrix4x4& other) const;
	constexpr Matrix4x4 operator * (TYPE mult) const;

	constexpr std::array<TYPE, DIMENTIONS>& operator [] (const size_t idx);
	constexpr const std::array<TYPE, DIMENTIONS>& operator [] (const size_t idx) const;

	// Constants

	static const Matrix4x4 identity;
	static const Matrix4x4 zero;
};

#undef DIMENTIONS
#undef TYPE