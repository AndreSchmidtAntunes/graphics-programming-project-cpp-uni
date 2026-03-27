#include "Vector4.h"

template <class T>
Vector4<T> Vector4<T>::operator * (const Vector4<T>& other) const {
	return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
}

template <class T>
Vector4<T> Vector4<T>::operator * (const T& value) const {
	return Vector4(x * value, y * value, z * value, w * value);
}

template <class T>
Vector4<T> Vector4<T>::operator * (const float& value) const {
	return Vector4(x * value, y * value, z * value, w * value);
}

template <class T>
Vector4<T> Vector4<T>::operator / (const Vector4<T>& other) const {
	return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
}

template <class T>
Vector4<T> Vector4<T>::operator / (const T& value) const {
	return Vector4(x / value, y / value, z / value, w / value);
}

template <class T>
Vector4<T> Vector4<T>::operator / (const float& value) const {
	return Vector4(x / value, y / value, z / value, w / value);
}

template <class T>
Vector4<T> Vector4<T>::operator + (const Vector4<T>& other) const {
	return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}

template <class T>
Vector4<T> Vector4<T>::operator - (const Vector4<T>& other) const {
	return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}

template <class T>
Vector4<T>::operator bool() const {
	return x || y || z || w;
}

template <class T>
bool Vector4<T>::operator == (Vector4<T> other) const {
	return x == other.x && y == other.y && z == other.z && w == other.w;
}

template <class T>
bool Vector4<T>::operator != (Vector4<T> other) const {
	return x != other.x || y != other.y || z != other.z || w != other.w;
}

template <class T>
Vector4<T>& Vector4<T>::operator *= (const Vector4<T>& value) {
	x *= value.x;
	y *= value.y;
	z *= value.z;
	w *= value.w;

	return *this;
}
template <class T>
Vector4<T>& Vector4<T>::operator *= (const T& value) {
	x *= value;
	y *= value;
	z *= value;
	w *= value;

	return *this;
}

template <class T>
Vector4<T>& Vector4<T>::operator *= (const float& value) {
	x *= value;
	y *= value;
	z *= value;
	w *= value;

	return *this;
}

template <class T>
Vector4<T>& Vector4<T>::operator /= (const Vector4<T>& value) {
	x /= value.x;
	y /= value.y;
	z /= value.z;
	w /= value.w;

	return *this;
}

template <class T>
Vector4<T>& Vector4<T>::operator /= (const T& value) {
	x /= value;
	y /= value;
	z /= value;
	w /= value;

	return *this;
}

template <class T>
Vector4<T>& Vector4<T>::operator /= (const float& value) {
	x /= value;
	y /= value;
	z /= value;
	w /= value;

	return *this;
}

template <class T>
Vector4<T>& Vector4<T>::operator += (const Vector4& value) {
	x += value.x;
	y += value.y;
	z += value.z;
	w += value.w;

	return *this;
}

template <class T>
Vector4<T>& Vector4<T>::operator -= (const Vector4& value) {
	x -= value.x;
	y -= value.y;
	z -= value.z;
	w -= value.w;

	return *this;
}

template <class T>
T& Vector4<T>::operator [] (const std::size_t idx) {
	return data[idx];
}

template <class T>
const T& Vector4<T>::operator [] (const std::size_t idx) const {
	return data[idx];
}

template <class T> const Vector4<T> Vector4<T>::Up = Vector4(0, 1, 0, 0);
template <class T> const Vector4<T> Vector4<T>::Down = Vector4(0, -1, 0, 0);
template <class T> const Vector4<T> Vector4<T>::Right = Vector4(1, 0, 0, 0);
template <class T> const Vector4<T> Vector4<T>::Left = Vector4(-1, 0, 0, 0);
template <class T> const Vector4<T> Vector4<T>::Forward = Vector4(0, 0, 1, 0);
template <class T> const Vector4<T> Vector4<T>::Back = Vector4(0, 0, -1, 0);
template <class T> const Vector4<T> Vector4<T>::Ana = Vector4(0, 0, 0, 1);
template <class T> const Vector4<T> Vector4<T>::Kata = Vector4(0, 0, 0, -1);

template <class T> const Vector4<T> Vector4<T>::Zero = Vector4(0, 0, 0, 0);
template <class T> const Vector4<T> Vector4<T>::One = Vector4(1, 1, 1, 1);

template <class T>
T Vector4<T>::SquaredMagnitude() const {
	return (x * x) + (y * y) + (z * z) + (w * w);
}

template <class T>
T Vector4<T>::Magnitude() const {
	return sqrt(SquaredMagnitude());
}

template <class T>
float Vector4<T>::MagnitudeF() const {
	return sqrtf((float)SquaredMagnitude());
}

template <class T>
Vector4<T> Vector4<T>::Normalised(InvSqrtPrecision precision) const {
	return Vector4((*this)).Normalise(precision); /// Returns w copy of the current Vector4 multiplied by 1/sqrt(SquaredMagnitude())
}

template <class T>
Vector4<T>& Vector4<T>::Normalise(InvSqrtPrecision precision) {
	float invSqrtX = FastInvSqrt((float)Vector4<T>::SquaredMagnitude(), precision);

	x *= invSqrtX;
	y *= invSqrtX;
	z *= invSqrtX;
	w *= invSqrtX;

	return *this;
}

template <class T>
Vector4<T> Vector4<T>::Abs() const {
	return Vector4(fabs(x), fabs(y), fabs(z), fabs(w));
}

template <class T>
T Vector4<T>::Dot(Vector4 lhs, Vector4 rhs) {
	return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z) + (lhs.w * rhs.w);

}