#include "Vector3.h"

template <class T>
Vector3<T> Vector3<T>::operator * (const Vector3<T>& other) const {
	return Vector3(x * other.x, y * other.y, z * other.z);
}


//template<class T, class Ty>
//Vector3<T> operator * (const Vector3<T>& vec3, const Ty& value)
//{
//	static_assert(std::is_arithmetic<Ty>::value,
//		"class Ty can only be an arithmetic type. (E.g: float, double, half)");
//
//	return Vector3(x * value, y * value, z * value);
//}

template <class T>
Vector3<T> Vector3<T>::operator / (const Vector3<T>& other) const {
	return Vector3(x / other.x, y / other.y, z / other.z);
}

//template<class T>
//template<class Ty>
//Vector3<T> Vector3<T>::operator / (const Ty& value)
//{
//	static_assert(std::is_arithmetic<Ty>::value,
//		"class Ty can only be an arithmetic type. (E.g: float, double, half)");
//
//	return Vector3(x / value, y / value, z / value);
//}

template <class T>
Vector3<T> Vector3<T>::operator + (const Vector3<T>& other) const {
	return Vector3(x + other.x, y + other.y, z + other.z);
}

template <class T>
Vector3<T> Vector3<T>::operator - (const Vector3<T>&other) const {
	return Vector3(x - other.x, y - other.y, z - other.z);
}

template <class T>
Vector3<T>::operator bool() const {
	return x || y || z;
}

template <class T>
bool Vector3<T>::operator == (Vector3 other) const {
	return x == other.x && y == other.y && z == other.z;
}

template <class T>
bool Vector3<T>::operator != (Vector3 other) const {
	return x != other.x || y != other.y || z != other.z;
}

template <class T>
Vector3<T>& Vector3<T>::operator=(const Vector3& value)
{
	x = value.x;
	y = value.y;
	z = value.z;

	return *this;
}

template <class T>
Vector3<T>& Vector3<T>::operator *= (const Vector3 &value) {
	x *= value.x;
	y *= value.y;
	z *= value.z;

	return *this;
}

//template <class T> 
//template <class Ty>
//Vector3<T>& Vector3<T>::operator *= (const Ty &value) {
//
//	static_assert(std::is_arithmetic<Ty>::value,
//		"class Ty can only be an arithmetic type. (E.g: float, double, half)");
//
//	x *= value;
//	y *= value;
//	z *= value;
//
//	return *this;
//}

template <class T>
Vector3<T>& Vector3<T>::operator /= (const Vector3 &value) {
	x /= value.x;
	y /= value.y;
	z /= value.z;

	return *this;
}

template<class T>
template<class Ty>
Vector3<T>& Vector3<T>::operator *= (const Ty& value)
{
	static_assert(std::is_arithmetic<Ty>::value,
		"class Ty can only be an arithmetic type. (E.g: float, double, half)");

	x *= value;
	y *= value;
	z *= value;

	return *this;
}

template <class T>
template <class Ty>
Vector3<T>& Vector3<T>::operator /= (const Ty &value) {

	static_assert(std::is_arithmetic<Ty>::value,
		"class Ty can only be an arithmetic type. (E.g: float, double, half)");

	x /= value;
	y /= value;
	z /= value;

	return *this;
}

template <class T>
Vector3<T>& Vector3<T>::operator += (const Vector3 &value) {
	x += value.x;
	y += value.y;
	z += value.z;	

	return *this;
}

template <class T>
Vector3<T>& Vector3<T>::operator -= (const Vector3 &value) {
	x -= value.x;
	y -= value.y;
	z -= value.z;

	return *this;
}

template <class T>
T& Vector3<T>::operator [] (std::size_t idx) {
	return data[idx];
}

template <class T>
const T& Vector3<T>::operator [] (const std::size_t idx) const {
	return data[idx];
}

template <class T> const Vector3<T> Vector3<T>::Up = Vector3(0, 1, 0);
template <class T> const Vector3<T> Vector3<T>::Down = Vector3(0, -1, 0);
template <class T> const Vector3<T> Vector3<T>::Right = Vector3(1, 0, 0);
template <class T> const Vector3<T> Vector3<T>::Left = Vector3(-1, 0, 0);
template <class T> const Vector3<T> Vector3<T>::Forward = Vector3(0, 0, 1);
template <class T> const Vector3<T> Vector3<T>::Back = Vector3(0, 0, -1);

template <class T> const Vector3<T> Vector3<T>::Zero = Vector3(0, 0, 0);
template <class T> const Vector3<T> Vector3<T>::One = Vector3(1, 1, 1);

template <class T>
T Vector3<T>::SquaredMagnitude() const {
	return (x * x) + (y * y) + (z * z);
}

template <class T>
T Vector3<T>::Magnitude() const {
	return sqrt(SquaredMagnitude());
}

template <class T>
float Vector3<T>::MagnitudeF() const {
	return sqrtf((float)SquaredMagnitude());
}

template <class T>
Vector3<T> Vector3<T>::Normalised(InvSqrtPrecision precision) const {
	return Vector3((*this)).Normalise(precision); /// Returns a copy of the current Vector3 multiplied by 1/sqrt(SquaredMagnitude())
}

template <class T>
Vector3<T>& Vector3<T>::Normalise(InvSqrtPrecision precision) {
	float invSqrtX = FastInvSqrt((float)Vector3::SquaredMagnitude(), precision);

	x *= invSqrtX;
	y *= invSqrtX;
	z *= invSqrtX;

	return *this;
}

template <class T>
Vector3<T> Vector3<T>::Abs() const {
	return Vector3(fabs(x), fabs(y), fabs(z));
}

template <class T>
T Vector3<T>::Dot(Vector3 lhs, Vector3 rhs) {
	return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
}

template <class T>
Vector3<T> Vector3<T>::Cross(Vector3 lhs, Vector3 rhs) {
	return Vector3(
		(lhs.y * rhs.z) - (lhs.z * rhs.y),
		(lhs.z * rhs.x) - (lhs.x * rhs.z),
		(lhs.x * rhs.y) - (lhs.y * rhs.x)
	);
}
