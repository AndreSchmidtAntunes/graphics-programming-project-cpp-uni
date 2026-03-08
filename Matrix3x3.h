#pragma once

#include "Vector3.h"

#define self (*this)

struct Matrix3x3 {
public:
	Matrix3x3(
		double m1_1, double m1_2, double m1_3,
		double m2_1, double m2_2, double m2_3,
		double m3_1, double m3_2, double m3_3
	);

	Matrix3x3();
	Matrix3x3(double[3][3]);
	Matrix3x3(Vector3 row_1, Vector3 row_2, Vector3 row_3);

	~Matrix3x3();

	// Static operations

	static Matrix3x3 ScaleMatrix(Vector3 scale);
	static Matrix3x3 RotationMatrix(Vector3 axis, double radians);

	static Matrix3x3 CrossProductMatrix(Vector3 direction);

	double Trace();

	void Transpose();

	// Setters

	void setElementAt(int row, int column, double value);

	void setRow(int row_index, Vector3 elements);

	void setColumn(int column_index, Vector3 elements);

	// Getters

	double getElementAt(int row, int column);

	Vector3 getRow(int row_index);

	Vector3 getColumn(int column_index);

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

	double* operator [] (int i);

	// Constants

	static const Matrix3x3 identity;
	static const Matrix3x3 zero;

	const int DIMENTIONS = 3;

protected:
	double mElements[3][3];

};

/// TODO: position matrix maker