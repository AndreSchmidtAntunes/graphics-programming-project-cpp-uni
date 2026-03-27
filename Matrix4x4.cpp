#include "Matrix4x4.h"

template <class T>
Matrix4x4<T>::Matrix4x4(
	T m1_1, T m1_2, T m1_3, T m1_4,
	T m2_1, T m2_2, T m2_3, T m2_4,
	T m3_1, T m3_2, T m3_3, T m3_4,
	T m4_1, T m4_2, T m4_3, T m4_4) {

	self[0][0] = m1_1; self[0][1] = m1_2; self[0][2] = m1_3;self[0][3] = m1_4;               
	self[1][0] = m2_1; self[1][1] = m2_2; self[1][2] = m2_3;self[1][3] = m2_4;
	self[2][0] = m3_1; self[2][1] = m3_2; self[2][2] = m3_3;self[2][3] = m3_4;
	self[3][0] = m4_1; self[3][1] = m4_2; self[3][2] = m4_3;self[3][3] = m4_4;
}

template <class T>
Matrix4x4<T>::Matrix4x4() {
	self = identity;
}

template <class T>
Matrix4x4<T>::Matrix4x4(T elements[DIMENTIONS][DIMENTIONS]) {
	for (uint row = 0; row < DIMENTIONS; row++)
		for (uint col = 0; col < DIMENTIONS; col++) {
			data[row][col] = elements[row][col];
		}
}

template <class T>
Matrix4x4<T>::Matrix4x4(Vector4<T> row_1, Vector4<T> row_2, Vector4<T> row_3, Vector4<T> row) {
	setRow(0, row_1);
	setRow(1, row_2);
	setRow(2, row_3);
}

template <class T>
Matrix4x4<T>::Matrix4x4(Matrix3x3<T> matrix) {
	self = Matrix4x4(
		matrix[0][0], matrix[0][1], matrix[0][2], 0,
		matrix[1][0], matrix[1][1], matrix[1][2], 0,
		matrix[2][0], matrix[2][1], matrix[2][2], 0,
		0,			  0,			0,			  1
	);
}

template <class T>
Matrix4x4<T>::~Matrix4x4() { }

template <class T>
Matrix4x4<T> Matrix4x4<T>::ScaleMatrix(Vector3<T> scale) {

	return Matrix4x4(
		scale.x, 0, 0, 0,
		0, scale.y, 0, 0,
		0, 0, scale.z, 0,
		0, 0,		0, 1
	);
}

// Used the formula half way through this page: http://www.fastgraph.com/makegames/3drotation/
template <class T>
Matrix4x4<T> Matrix4x4<T>::RotationMatrix(Vector3<T> axis, T radians) {

	T c = cos(radians);
	T s = sin(radians);
	T t = 1 - c;

	return Matrix4x4(
		(t * axis.x * axis.x) + c, (t * axis.x * axis.y) - (s * axis.z), (t * axis.x * axis.z) + (s * axis.y), 0, 
		(t * axis.x * axis.y) + (s * axis.z), (t * axis.y * axis.y) + c, (t * axis.y * axis.z) - (s * axis.x), 0,
		(t * axis.x * axis.z) - (s * axis.y), (t * axis.y * axis.z) + (s * axis.x), (t * axis.z * axis.z) + c, 0,
		0,									  0,									0,						   1
	);
}

template <class T>
Matrix4x4<T> Matrix4x4<T>::TranslationMatrix(Vector3<T> translation) {

	return Matrix4x4(
		1, 0, 0, translation.x,
		0, 1, 0, translation.y,
		0, 0, 1, translation.z,
		0, 0, 0, 1
	);
}

// Setters

template <class T>
void Matrix4x4<T>::setElementAt(uint row_index, uint column_index, T value) {
	self[row_index][column_index] = value;
}

template <class T>
void Matrix4x4<T>::setRow(uint row_index, Vector4<T> elements) {
	for (uint i = 0; i < DIMENTIONS; i++)
		self[row_index][i] = elements[i];
}

template <class T>
void Matrix4x4<T>::setColumn(uint column_index, Vector4<T> elements) {
	for (uint i = 0; i < DIMENTIONS; i++)
		self[i][column_index] = elements[i];
}

// Getters

template <class T>
T Matrix4x4<T>::getElementAt(uint row_index, uint column_index) {
	return data[row_index][column_index];
}

template <class T>
Vector4<T> Matrix4x4<T>::getRow(uint row_index) {
	return Vector4(self[row_index][0], self[row_index][1], self[row_index][2], self[row_index][3]);
}

template <class T>
Vector4<T> Matrix4x4<T>::getColumn(uint column_index) {
	return Vector4(self[0][column_index], self[1][column_index], self[2][column_index], self[3][column_index]);
}

template <class T>
std::array<T, Matrix4x4<T>::DIMENTIONS>& Matrix4x4<T>::operator [] (const uint idx) {
	return data[idx];
}

template <class T>
const std::array<T, Matrix4x4<T>::DIMENTIONS>& Matrix4x4<T>::operator[](const uint idx) const {
	return data[idx];
}

template <class T>
Matrix4x4<T>& Matrix4x4<T>::operator = (const Matrix4x4& other) {
	for (uint row = 0; row < DIMENTIONS; row++)
		for (uint col = 0; col < DIMENTIONS; col++)
			self[row][col] = other[row][col];
	
	return self;
}

template <class T>
Matrix4x4<T>& Matrix4x4<T>::operator *= (const Matrix4x4& other) {
	self = self * other;
	return self;
}

template <class T>
Matrix4x4<T>& Matrix4x4<T>::operator *= (const T mult) {
	for (uint row = 0; row < DIMENTIONS; row++)
		for (uint col = 0; col < DIMENTIONS; col++) {
			data[row][col] *= mult;
		}
	return self;
}

template <class T>
Vector4<T> Matrix4x4<T>::operator * (const Vector4<T>& mult) const {
	Vector4 result = Vector4();

	for (uint i = 0; i < DIMENTIONS; i++) {

		T sum = 0;
		for (uint j = 0; j < DIMENTIONS; j++) {
			sum += (self[i][j] * mult[j]);
		}
		result[i] = sum;
	}
	return result;
}

template <class T>
Vector3<T> Matrix4x4<T>::operator * (const Vector3<T>& mult) const {
	Vector4 result = self * Vector4(mult);
	return (Vector3)result;
}

template <class T>
Matrix4x4<T> Matrix4x4<T>::operator * (const Matrix4x4& other) const {
	Matrix4x4 result = Matrix4x4();
	for (uint row = 0; row < DIMENTIONS; row++)
		for (uint col = 0; col < DIMENTIONS; col++) {
			result[row][col] *= other[row][col];
		}
	return result;
}

template <class T>
Matrix4x4<T> Matrix4x4<T>::operator * (const T mult) const {
	Matrix4x4 result = Matrix4x4();
	for (uint row = 0; row < DIMENTIONS; row++)
		for (uint col = 0; col < DIMENTIONS; col++) {
			result[row][col] *= mult;
		}
	return result;
}

template <class T>
const Matrix4x4<T> Matrix4x4<T>::identity = Matrix4x4(
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
);

template <class T>
const Matrix4x4<T> Matrix4x4<T>::zero = Matrix4x4(
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0
);

