#include "Matrix4x4.h"

Matrix4x4::Matrix4x4(
	double m1_1, double m1_2, double m1_3, double m1_4,
	double m2_1, double m2_2, double m2_3, double m2_4,
	double m3_1, double m3_2, double m3_3, double m3_4,
	double m4_1, double m4_2, double m4_3, double m4_4) {

	self[0][0] = m1_1; self[0][1] = m1_2; self[0][2] = m1_3;self[0][3] = m1_4;               
	self[1][0] = m2_1; self[1][1] = m2_2; self[1][2] = m2_3;self[1][3] = m2_4;
	self[2][0] = m3_1; self[2][1] = m3_2; self[2][2] = m3_3;self[2][3] = m3_4;
	self[3][0] = m4_1; self[3][1] = m4_2; self[3][2] = m4_3;self[3][3] = m4_4;
}

Matrix4x4::Matrix4x4() {
	self = identity;
}

Matrix4x4::Matrix4x4(double elements[DIMENTIONS][DIMENTIONS]) {
	for (uint row = 0; row < DIMENTIONS; row++)
		for (uint col = 0; col < DIMENTIONS; col++) {
			data[row][col] = elements[row][col];
		}
}

Matrix4x4::Matrix4x4(Vector4 row_1, Vector4 row_2, Vector4 row_3, Vector4 row) {
	setRow(0, row_1);
	setRow(1, row_2);
	setRow(2, row_3);
}

Matrix4x4::Matrix4x4(Matrix3x3 matrix) {
	self = Matrix4x4(
		matrix[0][0], matrix[0][1], matrix[0][2], 0,
		matrix[1][0], matrix[1][1], matrix[1][2], 0,
		matrix[2][0], matrix[2][1], matrix[2][2], 0,
		0,			  0,			0,			  1
	);
}

Matrix4x4::~Matrix4x4() {

}

Matrix4x4 Matrix4x4::ScaleMatrix(Vector3 scale) {

	return Matrix4x4(
		scale.x, 0, 0, 0,
		0, scale.y, 0, 0,
		0, 0, scale.z, 0,
		0, 0,		0, 1
	);
}

// Used the formula half way through this page: http://www.fastgraph.com/makegames/3drotation/
Matrix4x4 Matrix4x4::RotationMatrix(Vector3 axis, double radians) {

	double c = cos(radians);
	double s = sin(radians);
	double t = 1 - c;

	return Matrix4x4(
		(t * axis.x * axis.x) + c, (t * axis.x * axis.y) - (s * axis.z), (t * axis.x * axis.z) + (s * axis.y), 0, 
		(t * axis.x * axis.y) + (s * axis.z), (t * axis.y * axis.y) + c, (t * axis.y * axis.z) - (s * axis.x), 0,
		(t * axis.x * axis.z) - (s * axis.y), (t * axis.y * axis.z) + (s * axis.x), (t * axis.z * axis.z) + c, 0,
		0,									  0,									0,						   1
	);
}

Matrix4x4 Matrix4x4::TranslationMatrix(Vector3 translation) {

	return Matrix4x4(
		1, 0, 0, translation.x,
		0, 1, 0, translation.y,
		0, 0, 1, translation.z,
		0, 0, 0, 1
	);
}

// Setters

void Matrix4x4::setElementAt(uint row_index, uint column_index, double value) {
	self[row_index][column_index] = value;
}

void Matrix4x4::setRow(uint row_index, Vector4 elements) {
	for (uint i = 0; i < DIMENTIONS; i++)
		self[row_index][i] = elements[i];
}

void Matrix4x4::setColumn(uint column_index, Vector4 elements) {
	for (uint i = 0; i < DIMENTIONS; i++)
		self[i][column_index] = elements[i];
}

// Getters

double Matrix4x4::getElementAt(uint row_index, uint column_index) {
	return data[row_index][column_index];
}

Vector4 Matrix4x4::getRow(uint row_index) {
	return Vector4(self[row_index][0], self[row_index][1], self[row_index][2], self[row_index][3]);
}

Vector4 Matrix4x4::getColumn(uint column_index) {
	return Vector4(self[0][column_index], self[1][column_index], self[2][column_index], self[3][column_index]);
}

std::array<double, Matrix4x4::DIMENTIONS>& Matrix4x4::operator [] (const uint idx) {
	return data[idx];
}

const std::array<double, Matrix4x4::DIMENTIONS>& Matrix4x4::operator[](const uint idx) const {
	return data[idx];
}

Matrix4x4& Matrix4x4::operator = (const Matrix4x4& other) {
	for (uint row = 0; row < DIMENTIONS; row++)
		for (uint col = 0; col < DIMENTIONS; col++)
			self[row][col] = other[row][col];
	
	return self;
}

Matrix4x4& Matrix4x4::operator *= (const Matrix4x4& other) {
	self = self * other;
	return self;
}

Matrix4x4& Matrix4x4::operator *= (const double mult) {
	for (uint row = 0; row < DIMENTIONS; row++)
		for (uint col = 0; col < DIMENTIONS; col++) {
			data[row][col] *= mult;
		}
	return self;
}

Matrix4x4& Matrix4x4::operator += (const Matrix4x4& other) {
	for (uint row = 0; row < DIMENTIONS; row++)
		for (uint col = 0; col < DIMENTIONS; col++) {
			data[row][col] += other[row][col];
		}
	return self;
}

Matrix4x4& Matrix4x4::operator -= (const Matrix4x4& other) {
	for (uint row = 0; row < DIMENTIONS; row++)
		for (uint col = 0; col < DIMENTIONS; col++) {
			data[row][col] -= other[row][col];
		}
	return self;
}

Vector4 Matrix4x4::operator * (const Vector4& mult) const {
	Vector4 result = Vector4();

	for (uint i = 0; i < DIMENTIONS; i++) {

		double sum = 0;
		for (uint j = 0; j < DIMENTIONS; j++) {
			sum += (self[i][j] * mult[j]);
		}
		result[i] = sum;
	}
	return result;
}

Vector3 Matrix4x4::operator * (const Vector3& mult) const {
	Vector4 result = self * Vector4(mult);
	return (Vector3)result;
}

Matrix4x4 Matrix4x4::operator * (const Matrix4x4& other) const {
	Matrix4x4 result = Matrix4x4();
	for (uint row = 0; row < DIMENTIONS; row++)
		for (uint col = 0; col < DIMENTIONS; col++) {
			result[row][col] *= other[row][col];
		}
	return result;
}

Matrix4x4 Matrix4x4::operator * (const double mult) const {
	Matrix4x4 result = Matrix4x4();
	for (uint row = 0; row < DIMENTIONS; row++)
		for (uint col = 0; col < DIMENTIONS; col++) {
			result[row][col] *= mult;
		}
	return result;
}

Matrix4x4 Matrix4x4::operator + (const Matrix4x4& other) const {
	Matrix4x4 result = Matrix4x4();
	for (uint row = 0; row < DIMENTIONS; row++)
		for (uint col = 0; col < DIMENTIONS; col++) {
			result[row][col] += other[row][col];
		}
	return result;
}

Matrix4x4 Matrix4x4::operator - (const Matrix4x4& other) const {
	Matrix4x4 result = Matrix4x4();
	for (uint row = 0; row < DIMENTIONS; row++)
		for (uint col = 0; col < DIMENTIONS; col++) {
			result[row][col] -= other[row][col];
		}
	return result;
}

const Matrix4x4 Matrix4x4::identity = Matrix4x4(
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
);

const Matrix4x4 Matrix4x4::zero = Matrix4x4(
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0
);

