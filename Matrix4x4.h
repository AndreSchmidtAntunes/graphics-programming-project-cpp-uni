#pragma once

#include "Matrix3x3.h"
#include "Vector4.h"

#define self (*this)

struct Matrix4x4 {
private:
	static const uint DIMENTIONS = 4;
public:

	std::array<std::array<double, DIMENTIONS>, DIMENTIONS> mElements{ };

	Matrix4x4(
		double m1_1, double m1_2, double m1_3, double m1_4,
		double m2_1, double m2_2, double m2_3, double m2_4,
		double m3_1, double m3_2, double m3_3, double m3_4, 
		double m4_1, double m4_2, double m4_3, double m4_4 
	);

	Matrix4x4();
	Matrix4x4(double[DIMENTIONS][DIMENTIONS]);
	Matrix4x4(Vector4 row_1, Vector4 row_2, Vector4 row_3, Vector4 row_4);

	Matrix4x4(Matrix3x3 matrix);

	~Matrix4x4();

	// Static operations

	static Matrix4x4 ScaleMatrix(Vector3 scale);
	static Matrix4x4 RotationMatrix(Vector3 axis, double radians);
	static Matrix4x4 TranslationMatrix(Vector3 translation);

	static Matrix4x4 CrossProductMatrix(Vector3 direction);

	// Setters

	void setElementAt(uint row, uint column, double value);

	void setRow(uint row_index, Vector4 elements);

	void setColumn(uint column_index, Vector4 elements);

	// Getters

	double getElementAt(uint row, uint column);

	Vector4 getRow(uint row_index);

	Vector4 getColumn(uint column_index);

	// Operators

	Matrix4x4& operator = (const Matrix4x4& other);

	Matrix4x4& operator *= (const Matrix4x4& other);
	Matrix4x4& operator *= (const double mult);
	Matrix4x4& operator += (const Matrix4x4& other);
	Matrix4x4& operator -= (const Matrix4x4& other);

	Vector4 operator * (const Vector4& mult) const;
	Vector3 operator * (const Vector3& mult) const;

	Matrix4x4 operator * (const Matrix4x4& other) const;
	Matrix4x4 operator * (double mult) const;
	Matrix4x4 operator + (const Matrix4x4& other) const;
	Matrix4x4 operator - (const Matrix4x4& other) const;

	std::array<double, DIMENTIONS>& operator [] (const uint idx);
	const std::array<double, DIMENTIONS>& operator [] (const uint idx) const;

	// Constants

	static const Matrix4x4 identity;
	static const Matrix4x4 zero;

//protected:
//	double mElements[DIMENTIONS][DIMENTIONS];
};