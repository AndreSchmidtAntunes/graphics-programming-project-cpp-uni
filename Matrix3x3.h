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
	Matrix3x3(const double[DIMENTIONS][DIMENTIONS]);
	Matrix3x3(const Vector3& row_1, const Vector3& row_2, const Vector3& row_3);

	~Matrix3x3();

	// Static operations

	static Matrix3x3 ScaleMatrix(const Vector3& scale);
	static Matrix3x3 RotationMatrix(const Vector3& axis, double radians);

	static Matrix3x3 CrossProductMatrix(const Vector3& direction);

	// Setters

	void setElementAt(uint row, uint column, double value);

	void setRow(uint row_index, const Vector3& elements);

	void setColumn(uint column_index, const Vector3& elements);

	// Getters

	double getElementAt(uint row, uint column) const;

	Vector3 getRow(uint row_index) const;

	Vector3 getColumn(uint column_index) const;

	// Operators
	

	Matrix3x3& operator = (const Matrix3x3& other);

	Matrix3x3& operator *= (const Matrix3x3& other);
	Matrix3x3& operator *= (double mult);
	Matrix3x3& operator += (const Matrix3x3& other);
	Matrix3x3& operator -= (const Matrix3x3& other);

	friend Vector3& operator *= (Vector3& lhs, const Matrix3x3& rhs);

	Vector3 operator * (const Vector3& mult) const;

	Matrix3x3 operator * (const Matrix3x3& other) const;
	Matrix3x3 operator * (const double mult) const;
	Matrix3x3 operator + (const Matrix3x3& other) const;
	Matrix3x3 operator - (const Matrix3x3& other) const;

	std::array<double, DIMENTIONS>& operator [] (const uint idx);
	const std::array<double, DIMENTIONS>& operator [] (const uint idx) const;

	// Constants

	static const Matrix3x3 identity;
	static const Matrix3x3 zero;

//protected:
//	double mElements[DIMENTIONS][DIMENTIONS];

};

