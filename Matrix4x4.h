#pragma once

#include "Matrix3x3.h"
#include "Vector4.h"

#define self (*this)

struct Matrix4x4 {
public:
	Matrix4x4(
		double m1_1, double m1_2, double m1_3, double m1_4,
		double m2_1, double m2_2, double m2_3, double m2_4,
		double m3_1, double m3_2, double m3_3, double m3_4, 
		double m4_1, double m4_2, double m4_3, double m4_4 
	);

	Matrix4x4();
	Matrix4x4(double[4][4]);
	Matrix4x4(Vector4 row_1, Vector4 row_2, Vector4 row_3, Vector4 row_4);

	Matrix4x4(Matrix3x3 matrix);

	~Matrix4x4();

	// Static operations

	static Matrix4x4 ScaleMatrix(Vector3 scale);
	static Matrix4x4 RotationMatrix(Vector3 axis, double radians);
	static Matrix4x4 TranslationMatrix(Vector3 translation);
	static Matrix4x4 CrossProductMatrix(Vector3 direction);

	double Trace();

	void Transpose();

	// Setters

	void setElementAt(int row, int column, double value);

	void setRow(int row_index, Vector4 elements);

	void setColumn(int column_index, Vector4 elements);

	// Getters

	double getElementAt(int row, int column);

	Vector4 getRow(int row_index);

	Vector4 getColumn(int column_index);

	// Operators

	Matrix4x4& operator = (Matrix4x4 other);

	Matrix4x4& operator *= (Matrix4x4 other);
	Matrix4x4& operator *= (double mult);
	Matrix4x4& operator += (Matrix4x4 other);
	Matrix4x4& operator -= (Matrix4x4 other);

	Vector4 operator * (Vector4 mult);
	Vector3 operator * (Vector3 mult);

	Matrix4x4 operator * (Matrix4x4 other);
	Matrix4x4 operator * (double mult);
	Matrix4x4 operator + (Matrix4x4 other);
	Matrix4x4 operator - (Matrix4x4 other);

	double* operator [] (int i);

	// Constants

	static const Matrix4x4 identity;
	static const Matrix4x4 zero;

	const int DIMENTIONS = 4;

protected:
	double mElements[4][4];
};