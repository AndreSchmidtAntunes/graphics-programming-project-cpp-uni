#pragma once

#include "Vector3.h"

#define self (*this)
#define uint unsigned int

struct Matrix3x3 {
private:
	static const uint DIMENTIONS = 3;
public:

	std::array<std::array<double, DIMENTIONS>, DIMENTIONS> mElements{ };

	Matrix3x3(
		double m1_1, double m1_2, double m1_3,
		double m2_1, double m2_2, double m2_3,
		double m3_1, double m3_2, double m3_3
	);

	Matrix3x3();
	Matrix3x3(double[DIMENTIONS][DIMENTIONS]);
	Matrix3x3(Vector3 row_1, Vector3 row_2, Vector3 row_3);

	~Matrix3x3();

	// Static operations

	static Matrix3x3 ScaleMatrix(Vector3 scale);
	static Matrix3x3 RotationMatrix(Vector3 axis, double radians);

	static Matrix3x3 CrossProductMatrix(Vector3 direction);

	// Setters

	void setElementAt(uint row, uint column, double value);

	void setRow(uint row_index, Vector3 elements);

	void setColumn(uint column_index, Vector3 elements);

	// Getters

	double getElementAt(uint row, uint column);

	Vector3 getRow(uint row_index);

	Vector3 getColumn(uint column_index);

	// Operators
	

	Matrix3x3& operator = (Matrix3x3 other);

	Matrix3x3& operator *= (Matrix3x3 other);
	Matrix3x3& operator *= (double mult);
	Matrix3x3& operator += (Matrix3x3 other);
	Matrix3x3& operator -= (Matrix3x3 other);

	Vector3 operator * (Vector3 mult);

	Matrix3x3 operator * (Matrix3x3 other);
	Matrix3x3 operator * (double mult);
	Matrix3x3 operator + (Matrix3x3 other);
	Matrix3x3 operator - (Matrix3x3 other);

	std::array<double, DIMENTIONS>& operator [] (const std::size_t idx);
	const std::array<double, DIMENTIONS>& operator [] (const std::size_t idx) const;

	// Constants

	static const Matrix3x3 identity;
	static const Matrix3x3 zero;

//protected:
//	double mElements[DIMENTIONS][DIMENTIONS];

};