#pragma once

#include "Matrix3x3.h"
#include "Vector4.h"

#define SELF (*this)

template <typename T = double>
struct Matrix4x4 {

private:

	static const uint DIMENTIONS = 4;

public:

	static_assert(std::is_arithmetic<T>::value,
		"typename T can only be instantiated with floating point types. (E.g: float, double, half)");

	std::array<std::array<T, DIMENTIONS>, DIMENTIONS> data{ };

	Matrix4x4(
		T m1_1, T m1_2, T m1_3, T m1_4,
		T m2_1, T m2_2, T m2_3, T m2_4,
		T m3_1, T m3_2, T m3_3, T m3_4, 
		T m4_1, T m4_2, T m4_3, T m4_4 
	);

	Matrix4x4();
	Matrix4x4(T[DIMENTIONS][DIMENTIONS]);
	Matrix4x4(Vector4<T> row_1, Vector4<T> row_2, Vector4<T> row_3, Vector4<T> row_4);

	Matrix4x4(Matrix3x3<T> matrix);

	~Matrix4x4();

	// Static operations

	static Matrix4x4 ScaleMatrix(Vector3<T> scale);
	static Matrix4x4 RotationMatrix(Vector3<T> axis, T radians);
	static Matrix4x4 TranslationMatrix(Vector3<T> translation);

	static Matrix4x4 CrossProductMatrix(Vector3<T> direction);

	// Setters

	void setElementAt(uint row, uint column, T value);

	void setRow(uint row_index, Vector4<T> elements);

	void setColumn(uint column_index, Vector4<T> elements);

	// Getters

	T getElementAt(uint row, uint column);

	Vector4<T> getRow(uint row_index);

	Vector4<T> getColumn(uint column_index);

	// Operators

	Matrix4x4& operator = (const Matrix4x4& other);

	Matrix4x4& operator *= (const Matrix4x4& other);
	Matrix4x4& operator *= (const T mult);


	Vector4<T> operator * (const Vector4<T>& mult) const;
	Vector3<T> operator * (const Vector3<T>& mult) const;

	Matrix4x4 operator * (const Matrix4x4& other) const;
	Matrix4x4 operator * (T mult) const;

	std::array<T, Matrix4x4<T>::DIMENTIONS>& operator [] (const uint idx);
	const std::array<T, Matrix4x4<T>::DIMENTIONS>& operator [] (const uint idx) const;

	// Constants

	static const Matrix4x4 identity;
	static const Matrix4x4 zero;

//protected:
//	T mElements[DIMENTIONS][DIMENTIONS];
};