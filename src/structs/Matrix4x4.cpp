#include "Matrix4x4.h"

#include "Matrix3x3.h"

#define TYPE float
#define DIMENTIONS 4

constexpr Matrix4x4::Matrix4x4(
	TYPE m1_1, TYPE m1_2, TYPE m1_3, TYPE m1_4,
	TYPE m2_1, TYPE m2_2, TYPE m2_3, TYPE m2_4,
	TYPE m3_1, TYPE m3_2, TYPE m3_3, TYPE m3_4,
	TYPE m4_1, TYPE m4_2, TYPE m4_3, TYPE m4_4) {

	(*this)[0][0] = m1_1; (*this)[0][1] = m1_2; (*this)[0][2] = m1_3; (*this)[0][3] = m1_4;
	(*this)[1][0] = m2_1; (*this)[1][1] = m2_2; (*this)[1][2] = m2_3; (*this)[1][3] = m2_4;
	(*this)[2][0] = m3_1; (*this)[2][1] = m3_2; (*this)[2][2] = m3_3; (*this)[2][3] = m3_4;
	(*this)[3][0] = m4_1; (*this)[3][1] = m4_2; (*this)[3][2] = m4_3; (*this)[3][3] = m4_4;
}


constexpr Matrix4x4::Matrix4x4() {
	(*this) = identity;
}


constexpr Matrix4x4::Matrix4x4(TYPE elements[DIMENTIONS][DIMENTIONS]) {
	for (size_t row = 0; row < DIMENTIONS; row++)
		for (size_t col = 0; col < DIMENTIONS; col++) {
			data[row][col] = elements[row][col];
		}
}


constexpr Matrix4x4::Matrix4x4(Vector4 row_1, Vector4 row_2, Vector4 row_3, Vector4 row) {
	setRow(0, row_1);
	setRow(1, row_2);
	setRow(2, row_3);
}


constexpr Matrix4x4::Matrix4x4(Matrix3x3 matrix) {
	(*this) = Matrix4x4(
		matrix[0][0], matrix[0][1], matrix[0][2], 0,
		matrix[1][0], matrix[1][1], matrix[1][2], 0,
		matrix[2][0], matrix[2][1], matrix[2][2], 0,
		0, 0, 0, 1
	);
}


constexpr Matrix4x4::~Matrix4x4() {}


constexpr Matrix4x4 Matrix4x4::ScaleMatrix(Vector3 scale) {

	return Matrix4x4(
		scale.x, 0, 0, 0,
		0, scale.y, 0, 0,
		0, 0, scale.z, 0,
		0, 0, 0, 1
	);
}

// Used the formula half way through this page: http://www.fastgraph.com/makegames/3drotation/

Matrix4x4 Matrix4x4::RotationMatrix(Vector3 axis, TYPE radians) {

	TYPE c = cos(radians);
	TYPE s = sin(radians);
	TYPE t = 1 - c;

	return Matrix4x4(
		(t * axis.x * axis.x) + c, (t * axis.x * axis.y) - (s * axis.z), (t * axis.x * axis.z) + (s * axis.y), 0,
		(t * axis.x * axis.y) + (s * axis.z), (t * axis.y * axis.y) + c, (t * axis.y * axis.z) - (s * axis.x), 0,
		(t * axis.x * axis.z) - (s * axis.y), (t * axis.y * axis.z) + (s * axis.x), (t * axis.z * axis.z) + c, 0,
		0, 0, 0, 1
	);
}


constexpr Matrix4x4 Matrix4x4::TranslationMatrix(Vector3 translation) {

	return Matrix4x4(
		1, 0, 0, translation.x,
		0, 1, 0, translation.y,
		0, 0, 1, translation.z,
		0, 0, 0, 1
	);
}

// Setters


constexpr void Matrix4x4::setElementAt(size_t row_index, size_t column_index, TYPE value) {
	(*this)[row_index][column_index] = value;
}


constexpr void Matrix4x4::setRow(size_t row_index, Vector4 elements) {
	for (size_t i = 0; i < DIMENTIONS; i++)
		(*this)[row_index][i] = elements[i];
}


constexpr void Matrix4x4::setColumn(size_t column_index, Vector4 elements) {
	for (size_t i = 0; i < DIMENTIONS; i++)
		(*this)[i][column_index] = elements[i];
}

// Getters


constexpr TYPE Matrix4x4::getElementAt(size_t row_index, size_t column_index) {
	return data[row_index][column_index];
}


constexpr Vector4 Matrix4x4::getRow(size_t row_index) {
	return Vector4((*this)[row_index][0], (*this)[row_index][1], (*this)[row_index][2], (*this)[row_index][3]);
}


constexpr Vector4 Matrix4x4::getColumn(size_t column_index) {
	return Vector4((*this)[0][column_index], (*this)[1][column_index], (*this)[2][column_index], (*this)[3][column_index]);
}


constexpr std::array<TYPE, DIMENTIONS>& Matrix4x4::operator [] (const size_t idx) {
	return data[idx];
}


constexpr const std::array<TYPE, DIMENTIONS>& Matrix4x4::operator[](const size_t idx) const {
	return data[idx];
}


constexpr Matrix4x4& Matrix4x4::operator = (const Matrix4x4& other) {
	for (size_t row = 0; row < DIMENTIONS; row++)
		for (size_t col = 0; col < DIMENTIONS; col++)
			(*this)[row][col] = other[row][col];

	return (*this);
}


constexpr Matrix4x4& Matrix4x4::operator *= (const Matrix4x4& other) {
	(*this) = (*this) * other;
	return (*this);
}


constexpr Matrix4x4& Matrix4x4::operator *= (const TYPE mult) {
	for (size_t row = 0; row < DIMENTIONS; row++)
		for (size_t col = 0; col < DIMENTIONS; col++) {
			data[row][col] *= mult;
		}
	return (*this);
}


constexpr Vector4 Matrix4x4::operator * (const Vector4& mult) const {
	Vector4 result = Vector4();

	for (size_t i = 0; i < DIMENTIONS; i++) {

		TYPE sum = 0;
		for (size_t j = 0; j < DIMENTIONS; j++) {
			sum += ((*this)[i][j] * mult[j]);
		}
		result[i] = sum;
	}
	return result;
}


constexpr Vector3 Matrix4x4::operator * (const Vector3& mult) const {
	Vector4 result = (*this) * Vector4(mult);
	return (Vector3)result;
}


constexpr Matrix4x4 Matrix4x4::operator * (const Matrix4x4& other) const {
	Matrix4x4 result = Matrix4x4();
	for (size_t row = 0; row < DIMENTIONS; row++)
		for (size_t col = 0; col < DIMENTIONS; col++) {
			result[row][col] *= other[row][col];
		}
	return result;
}


constexpr Matrix4x4 Matrix4x4::operator * (const TYPE mult) const {
	Matrix4x4 result = Matrix4x4();
	for (size_t row = 0; row < DIMENTIONS; row++)
		for (size_t col = 0; col < DIMENTIONS; col++) {
			result[row][col] *= mult;
		}
	return result;
}



#undef DIMENTIONS
#undef TYPE