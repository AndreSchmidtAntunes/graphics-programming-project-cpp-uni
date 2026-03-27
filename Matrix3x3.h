#pragma once

#include "Vector3.h"

#define self (*this)
#define uint unsigned int

template <typename T = double>
struct Matrix3x3 {

private:

	static const uint DIMENTIONS = 3;

public:

	static_assert(std::is_arithmetic<T>::value,
		"typename T can only be instantiated with floating point types. (E.g: float, double, half)");

	std::array<std::array<T, DIMENTIONS>, DIMENTIONS> data{ };

	Matrix3x3(
		T m1_1, T m1_2, T m1_3,
		T m2_1, T m2_2, T m2_3,
		T m3_1, T m3_2, T m3_3
	);

	Matrix3x3();
	Matrix3x3(const T[DIMENTIONS][DIMENTIONS]);
	Matrix3x3(const Vector3<T>& row_1, const Vector3<T>& row_2, const Vector3<T>& row_3);

	~Matrix3x3();

	// Static operations

	static Matrix3x3<T> ScaleMatrix(const Vector3<T>& scale);
	static Matrix3x3<T> RotationMatrix(const Vector3<T>& axis, T radians);

	static Matrix3x3<T> CrossProductMatrix(const Vector3<T>& direction);

	// Setters

	void setElementAt(uint row, uint column, T value);

	void setRow(uint row_index, const Vector3<T>& elements);

	void setColumn(uint column_index, const Vector3<T>& elements);

	// Getters

	T getElementAt(uint row, uint column) const;

	Vector3<T> getRow(uint row_index) const;

	Vector3<T> getColumn(uint column_index) const;

	// Operators
	
	Matrix3x3<T>& operator = (const Matrix3x3<T>& other);

	Matrix3x3<T>& operator *= (const Matrix3x3<T>& other);
	Matrix3x3<T>& operator *= (T mult);


	friend Vector3<T>& operator *= (Vector3<T>& lhs, const Matrix3x3<T>& rhs);

	Vector3<T> operator * (const Vector3<T>& mult) const;

	Matrix3x3<T> operator * (const Matrix3x3<T>& other) const;
	Matrix3x3<T> operator * (const T mult) const;

	std::array<T, Matrix3x3<T>::DIMENTIONS>& operator [] (const uint idx);
	const std::array<T, Matrix3x3<T>::DIMENTIONS>& operator [] (const uint idx) const;

	// Constants

	static const Matrix3x3<T> identity;
	static const Matrix3x3<T> zero;

};

