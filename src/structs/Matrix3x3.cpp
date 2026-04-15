#include "Matrix3x3.h"

#define TYPE float
#define DIMENTIONS 3

constexpr Matrix3x3::Matrix3x3(
	TYPE m1_1, TYPE m1_2, TYPE m1_3,
	TYPE m2_1, TYPE m2_2, TYPE m2_3,
	TYPE m3_1, TYPE m3_2, TYPE m3_3) {

	(*this)[0][0] = m1_1; (*this)[0][1] = m1_2; (*this)[0][2] = m1_3;
	(*this)[1][0] = m2_1; (*this)[1][1] = m2_2; (*this)[1][2] = m2_3;
	(*this)[2][0] = m3_1; (*this)[2][1] = m3_2; (*this)[2][2] = m3_3;
}


constexpr Matrix3x3::Matrix3x3(const TYPE elements[DIMENTIONS][DIMENTIONS]) {
	for (size_t row = 0; row < DIMENTIONS; row++)
		for (size_t col = 0; col < DIMENTIONS; col++) {
			data[row][col] = elements[row][col];
		}
}

constexpr Matrix3x3::Matrix3x3(const Vector3& row_1, const Vector3& row_2, const Vector3& row_3) {
	setRow(0, row_1);
	setRow(1, row_2);
	setRow(2, row_3);
}


constexpr Matrix3x3 Matrix3x3::ScaleMatrix(const Vector3& scale) {

	return Matrix3x3(
		scale.x, 0, 0,
		0, scale.y, 0,
		0, 0, scale.z
	);
}

// Used the formula half way through this page: http://www.fastgraph.com/makegames/3drotation/

Matrix3x3 Matrix3x3::RotationMatrix(const Vector3& axis, TYPE radians) {

	TYPE c = cos(radians);
	TYPE s = sin(radians);
	TYPE t = 1 - c;

	return Matrix3x3(
		(t * axis.x * axis.x) + c, (t * axis.x * axis.y) - (s * axis.z), (t * axis.x * axis.z) + (s * axis.y),
		(t * axis.x * axis.y) + (s * axis.z), (t * axis.y * axis.y) + c, (t * axis.y * axis.z) - (s * axis.x),
		(t * axis.x * axis.z) - (s * axis.y), (t * axis.y * axis.z) + (s * axis.x), (t * axis.z * axis.z) + c
	);
}


constexpr Matrix3x3 Matrix3x3::CrossProductMatrix(const Vector3& direction) {

	return Matrix3x3(
		0, -direction.z, direction.y,
		direction.z, 0, -direction.x,
		-direction.y, direction.x, 0
	);
}

// Setters

constexpr void Matrix3x3::setElementAt(size_t row_index, size_t column_index, TYPE value) {
	(*this)[row_index][column_index] = value;
}


constexpr void Matrix3x3::setRow(size_t row_index, const Vector3& elements) {
	for (size_t i = 0; i < DIMENTIONS; i++)
		(*this)[row_index][i] = elements[i];
}


constexpr void Matrix3x3::setColumn(size_t column_index, const Vector3& elements) {
	for (size_t i = 0; i < DIMENTIONS; i++)
		(*this)[i][column_index] = elements[i];
}

// Getters


constexpr TYPE Matrix3x3::getElementAt(size_t row_index, size_t column_index) const {
	return data[row_index][column_index];
}

constexpr Vector3 Matrix3x3::getRow(size_t row_index) const {
	return Vector3((*this)[row_index][0], (*this)[row_index][1], (*this)[row_index][2]);
}


constexpr Vector3 Matrix3x3::getColumn(size_t column_index) const {
	return Vector3((*this)[0][column_index], (*this)[1][column_index], (*this)[2][column_index]);
}


constexpr std::array<TYPE, DIMENTIONS>& Matrix3x3::operator [] (const size_t idx) {
	return data[idx];
}


constexpr const std::array<TYPE, DIMENTIONS>& Matrix3x3::operator [] (const size_t idx) const {
	return data[idx];
}


constexpr Matrix3x3& Matrix3x3::operator = (const Matrix3x3& other) {
	for (size_t row = 0; row < DIMENTIONS; row++)
		for (size_t col = 0; col < DIMENTIONS; col++)
			(*this)[row][col] = other[row][col];

	return (*this);
}


constexpr Matrix3x3& Matrix3x3::operator *= (const Matrix3x3& other) {
	(*this) = (*this) * other;
	return (*this);
}


constexpr Vector3& operator *= (Vector3& lhs, const Matrix3x3& rhs)
{
	lhs = rhs * lhs;
	return lhs;
}


constexpr Matrix3x3& Matrix3x3::operator *= (const TYPE mult) {
	for (size_t row = 0; row < DIMENTIONS; row++)
		for (size_t col = 0; col < DIMENTIONS; col++) {
			data[row][col] *= mult;
		}
	return (*this);
}


constexpr Vector3 Matrix3x3::operator * (const Vector3& mult) const {
	Vector3 result = Vector3();

	for (size_t i = 0; i < DIMENTIONS; i++) {
		TYPE sum = 0;
		for (size_t j = 0; j < DIMENTIONS; j++) {
			sum += ((*this)[i][j] * mult[j]);
		}
		result[i] = sum;
	}
	return result;
}


constexpr Matrix3x3 Matrix3x3::operator * (const Matrix3x3& other) const {
	Matrix3x3 result = Matrix3x3::zero;

	int i, j, m;
	for (i = 0; i < DIMENTIONS; i++)
		for (j = 0; j < DIMENTIONS; j++)
			for (m = 0; m < DIMENTIONS; m++)
				result[i][j] += (*this)[i][m] * other[m][j];

	return result;
}


constexpr Matrix3x3 Matrix3x3::operator * (const TYPE mult) const {
	Matrix3x3 result = Matrix3x3();
	for (size_t row = 0; row < DIMENTIONS; row++)
		for (size_t col = 0; col < DIMENTIONS; col++) {
			result[row][col] *= mult;
		}
	return result;
}

#undef DIMENTIONS
#undef TYPE