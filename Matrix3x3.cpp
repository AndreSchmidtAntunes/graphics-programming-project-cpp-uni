#include "Matrix3x3.h"

template <typename T>
Matrix3x3<T>::Matrix3x3(
	T m1_1, T m1_2, T m1_3,
	T m2_1, T m2_2, T m2_3,
	T m3_1, T m3_2, T m3_3) {

	self[0][0] = m1_1; self[0][1] = m1_2; self[0][2] = m1_3;
	self[1][0] = m2_1; self[1][1] = m2_2; self[1][2] = m2_3;
	self[2][0] = m3_1; self[2][1] = m3_2; self[2][2] = m3_3;
}
template <typename T>
Matrix3x3<T>::Matrix3x3() {
	self = identity;
}
template <typename T>
Matrix3x3<T>::Matrix3x3(const T elements[DIMENTIONS][DIMENTIONS]) {
	for (uint row = 0; row < DIMENTIONS; row++)
		for (uint col = 0; col < DIMENTIONS; col++) {
			data[row][col] = elements[row][col];
		}
}
template <typename T>
Matrix3x3<T>::Matrix3x3(const Vector3<T>& row_1, const Vector3<T>& row_2, const Vector3<T>& row_3) {
	setRow(0, row_1);
	setRow(1, row_2);
	setRow(2, row_3);
}
template <typename T>
Matrix3x3<T>::~Matrix3x3() {
	delete data;
}

template <typename T>
Matrix3x3<T> Matrix3x3<T>::ScaleMatrix(const Vector3<T>& scale) {
	
	return Matrix3x3(
		scale.x, 0, 0,
		0, scale.y, 0,
		0, 0, scale.z
	);
}

// Used the formula half way through this page: http://www.fastgraph.com/makegames/3drotation/
template <typename T>
Matrix3x3<T> Matrix3x3<T>::RotationMatrix(const Vector3<T>& axis, T radians) {

	T c = cos(radians);
	T s = sin(radians);
	T t = 1 - c;

	return Matrix3x3(
		(t * axis.x * axis.x) + c, (t * axis.x * axis.y) - (s * axis.z), (t * axis.x * axis.z) + (s * axis.y),
		(t * axis.x * axis.y) + (s * axis.z), (t * axis.y * axis.y) + c, (t * axis.y * axis.z) - (s * axis.x),
		(t * axis.x * axis.z) - (s * axis.y), (t * axis.y * axis.z) + (s * axis.x), (t * axis.z * axis.z) + c
	);
}

template <typename T>
Matrix3x3<T> Matrix3x3<T>::CrossProductMatrix(const Vector3<T>& direction) {
	
	return Matrix3x3(
		0, -direction.z, direction.y,
		direction.z, 0, -direction.x,
		-direction.y, direction.x, 0
	);
}

// Setters
template <typename T>
void Matrix3x3<T>::setElementAt(uint row_index, uint column_index, T value) {
	self[row_index][column_index] = value;
}

template <typename T>
void Matrix3x3<T>::setRow(uint row_index, const Vector3<T>& elements) {
	for (uint i = 0; i < DIMENTIONS; i++)
		self[row_index][i] = elements[i];
}

template <typename T>
void Matrix3x3<T>::setColumn(uint column_index, const Vector3<T>& elements) {
	for (uint i = 0; i < DIMENTIONS; i++)
		self[i][column_index] = elements[i];
}

// Getters

template <typename T>
T Matrix3x3<T>::getElementAt(uint row_index, uint column_index) const {
	return data[row_index][column_index];
}

template <typename T>
Vector3<T> Matrix3x3<T>::getRow(uint row_index) const {
	return Vector3<T>(self[row_index][0], self[row_index][1], self[row_index][2]);
}

template <typename T>
Vector3<T> Matrix3x3<T>::getColumn(uint column_index) const {
	return Vector3<T>(self[0][column_index], self[1][column_index], self[2][column_index]);
}

template <typename T>
std::array<T, Matrix3x3<T>::DIMENTIONS>& Matrix3x3<T>::operator [] (const uint idx) {
	return data[idx];
}

template <typename T>
const std::array<T, Matrix3x3<T>::DIMENTIONS>& Matrix3x3<T>::operator [] (const uint idx) const {
	return data[idx];
}

template <typename T>
Matrix3x3<T>& Matrix3x3<T>::operator = (const Matrix3x3<T>& other) {
	for (uint row = 0; row < DIMENTIONS; row++)
		for (uint col = 0; col < DIMENTIONS; col++)
			self[row][col] = other[row][col];

	return self;
}

template <typename T>
Matrix3x3<T>& Matrix3x3<T>::operator *= (const Matrix3x3<T>& other) {
	self = self * other;
	return self;
}

template <typename T>
Vector3<T>& operator *= (Vector3<T>& lhs, const Matrix3x3<T>& rhs)
{
	lhs = rhs * lhs;
	return lhs;
}

template <typename T>
Matrix3x3<T>& Matrix3x3<T>::operator *= (const T mult) {
	for (uint row = 0; row < DIMENTIONS; row++)
		for (uint col = 0; col < DIMENTIONS; col++) {
			data[row][col] *= mult;
		}
	return self;
}

template <typename T>
Vector3<T> Matrix3x3<T>::operator * (const Vector3<T>& mult) const {
	Vector3<T> result = Vector3<T>();
	
	for (uint i = 0; i < DIMENTIONS; i++) {
		T sum = 0;
		for (uint j = 0; j < DIMENTIONS; j++) {
			sum += (self[i][j] * mult[j]);
		}
		result[i] = sum;
	}
	return result;
}

template <typename T>
Matrix3x3<T> Matrix3x3<T>::operator * (const Matrix3x3<T>& other) const {
	Matrix3x3<T> result = Matrix3x3<T>::zero;

	int i, j, m;
	for (i = 0; i < DIMENTIONS; i++)
		for (j = 0; j < DIMENTIONS; j++)
			for (m = 0; m < DIMENTIONS; m++)
				result[i][j] += self[i][m] * other[m][j];

	return result;
}

template <typename T>
Matrix3x3<T> Matrix3x3<T>::operator * (const T mult) const {
	Matrix3x3<T> result = Matrix3x3<T>();
	for (uint row = 0; row < DIMENTIONS; row++)
		for (uint col = 0; col < DIMENTIONS; col++) {
			result[row][col] *= mult;
		}
	return result;
}

template <typename T>
const Matrix3x3<T> Matrix3x3<T>::identity = Matrix3x3<T> (
	1, 0, 0,
	0, 1, 0,
	0, 0, 1
);

template <typename T>
const Matrix3x3<T> Matrix3x3<T>::zero = Matrix3x3<T>(
	0, 0, 0,
	0, 0, 0,
	0, 0, 0
);

