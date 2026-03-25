#include "Matrix3x3.h"

Matrix3x3::Matrix3x3(
	double m1_1, double m1_2, double m1_3,
	double m2_1, double m2_2, double m2_3,
	double m3_1, double m3_2, double m3_3) {

	self[0][0] = m1_1; self[0][1] = m1_2; self[0][2] = m1_3;
	self[1][0] = m2_1; self[1][1] = m2_2; self[1][2] = m2_3;
	self[2][0] = m3_1; self[2][1] = m3_2; self[2][2] = m3_3;
}

Matrix3x3::Matrix3x3() {
	self = identity;
}

Matrix3x3::Matrix3x3(const double elements[DIMENTIONS][DIMENTIONS]) {
	for (uint row = 0; row < DIMENTIONS; row++)
		for (uint col = 0; col < DIMENTIONS; col++) {
			mElements[row][col] = elements[row][col];
		}
}

Matrix3x3::Matrix3x3(const Vector3& row_1, const Vector3& row_2, const Vector3& row_3) {
	setRow(0, row_1);
	setRow(1, row_2);
	setRow(2, row_3);
}

Matrix3x3::~Matrix3x3() {

}

Matrix3x3 Matrix3x3::ScaleMatrix(const Vector3& scale) {
	
	return Matrix3x3(
		scale.x, 0, 0,
		0, scale.y, 0,
		0, 0, scale.z
	);
}

// Used the formula half way through this page: http://www.fastgraph.com/makegames/3drotation/
Matrix3x3 Matrix3x3::RotationMatrix(const Vector3& axis, double radians) {

	double c = cos(radians);
	double s = sin(radians);
	double t = 1 - c;

	return Matrix3x3(
		(t * axis.x * axis.x) + c, (t * axis.x * axis.y) - (s * axis.z), (t * axis.x * axis.z) + (s * axis.y),
		(t * axis.x * axis.y) + (s * axis.z), (t * axis.y * axis.y) + c, (t * axis.y * axis.z) - (s * axis.x),
		(t * axis.x * axis.z) - (s * axis.y), (t * axis.y * axis.z) + (s * axis.x), (t * axis.z * axis.z) + c
	);
}

Matrix3x3 Matrix3x3::CrossProductMatrix(const Vector3& direction) {
	
	return Matrix3x3(
		0, -direction.z, direction.y,
		direction.z, 0, -direction.x,
		-direction.y, direction.x, 0
	);
}

// Setters

void Matrix3x3::setElementAt(uint row_index, uint column_index, double value) {
	self[row_index][column_index] = value;
}

void Matrix3x3::setRow(uint row_index, const Vector3& elements) {
	for (uint i = 0; i < DIMENTIONS; i++)
		self[row_index][i] = elements[i];
}

void Matrix3x3::setColumn(uint column_index, const Vector3& elements) {
	for (uint i = 0; i < DIMENTIONS; i++)
		self[i][column_index] = elements[i];
}

// Getters

double Matrix3x3::getElementAt(uint row_index, uint column_index) const {
	return mElements[row_index][column_index];
}

Vector3 Matrix3x3::getRow(uint row_index) const {
	return Vector3(self[row_index][0], self[row_index][1], self[row_index][2]);
}

Vector3 Matrix3x3::getColumn(uint column_index) const {
	return Vector3(self[0][column_index], self[1][column_index], self[2][column_index]);
}

std::array<double, Matrix3x3::DIMENTIONS>& Matrix3x3::operator [] (const uint idx) {
	return mElements[idx];
}

const std::array<double, Matrix3x3::DIMENTIONS>& Matrix3x3::operator [] (const uint idx) const {
	return mElements[idx];
}

Matrix3x3& Matrix3x3::operator = (const Matrix3x3& other) {
	for (uint row = 0; row < DIMENTIONS; row++)
		for (uint col = 0; col < DIMENTIONS; col++)
			self[row][col] = other[row][col];

	return self;
}

Matrix3x3& Matrix3x3::operator *= (const Matrix3x3& other) {
	self = self * other;
	return self;
}

Vector3& operator *= (Vector3& lhs, const Matrix3x3& rhs)
{
	lhs = rhs * lhs;
	return lhs;
}

Matrix3x3& Matrix3x3::operator *= (const double mult) {
	for (uint row = 0; row < DIMENTIONS; row++)
		for (uint col = 0; col < DIMENTIONS; col++) {
			mElements[row][col] *= mult;
		}
	return self;
}

Vector3 Matrix3x3::operator * (const Vector3& mult) const {
	Vector3 result = Vector3();
	
	for (uint i = 0; i < DIMENTIONS; i++) {
		double sum = 0;
		for (uint j = 0; j < DIMENTIONS; j++) {
			sum += (self[i][j] * mult[j]);
		}
		result[i] = sum;
	}
	return result;
}

Matrix3x3 Matrix3x3::operator * (const Matrix3x3& other) const {
	Matrix3x3 result = Matrix3x3::zero;

	int i, j, m;
	for (i = 0; i < DIMENTIONS; i++)
		for (j = 0; j < DIMENTIONS; j++)
			for (m = 0; m < DIMENTIONS; m++)
				result[i][j] += self[i][m] * other[m][j];

	return result;
}

Matrix3x3 Matrix3x3::operator * (const double mult) const {
	Matrix3x3 result = Matrix3x3();
	for (uint row = 0; row < DIMENTIONS; row++)
		for (uint col = 0; col < DIMENTIONS; col++) {
			result[row][col] *= mult;
		}
	return result;
}

const Matrix3x3 Matrix3x3::identity = Matrix3x3 (
	1, 0, 0,
	0, 1, 0,
	0, 0, 1
);

const Matrix3x3 Matrix3x3::zero = Matrix3x3 (
	0, 0, 0,
	0, 0, 0,
	0, 0, 0
);

