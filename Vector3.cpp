#include "Vector3.h"

//template <typename T>
//Vector3<T> Vector3<T>::operator * (const Vector3<T>& other) const {
//	return Vector3(x * other.x, y * other.y, z * other.z);
//}


//template<typename T, typename Ty>
//Vector3<T> operator * (const Vector3<T>& vec3, const Ty& value)
//{
//	static_assert(std::is_arithmetic<Ty>::value,
//		"typename Ty can only be an arithmetic type. (E.g: float, double, half)");
//
//	return Vector3(x * value, y * value, z * value);
//}

//template <typename T>
//Vector3<T> Vector3<T>::operator / (const Vector3<T>& other) const {
//	return Vector3(x / other.x, y / other.y, z / other.z);
//}

//template<typename T>
//template<typename Ty>
//Vector3<T> Vector3<T>::operator / (const Ty& value)
//{
//	static_assert(std::is_arithmetic<Ty>::value,
//		"typename Ty can only be an arithmetic type. (E.g: float, double, half)");
//
//	return Vector3(x / value, y / value, z / value);
//}

//template <typename T>
//Vector3<T> Vector3<T>::operator + (const Vector3<T>& other) const {
//	return Vector3(x + other.x, y + other.y, z + other.z);
//}
//
//template <typename T>
//Vector3<T> Vector3<T>::operator - (const Vector3<T>&other) const {
//	return Vector3(x - other.x, y - other.y, z - other.z);
//}
//
//template <typename T>
//Vector3<T>::operator bool() const {
//	return x || y || z;
//}
//
template <typename T>
const bool Vector3<T>::operator == (const Vector3<T>& other) const {
	return x == other.x && y == other.y && z == other.z;
}

template <typename T>
const bool Vector3<T>::operator != (const Vector3<T>& other) const {
	return x != other.x || y != other.y || z != other.z;
}
//
//template <typename T>
//Vector3<T>& Vector3<T>::operator = (const Vector3<T>& value)
//{
//	x = value.x;
//	y = value.y;
//	z = value.z;
//
//	return *this;
//}
//
//template <typename T>
//Vector3<T>& Vector3<T>::operator *= (const Vector3<T> &value) {
//	x *= value.x;
//	y *= value.y;
//	z *= value.z;
//
//	return *this;
//}

//template <typename T> 
//template <typename Ty>
//Vector3<T>& Vector3<T>::operator *= (const Ty &value) {
//
//	static_assert(std::is_arithmetic<Ty>::value,
//		"typename Ty can only be an arithmetic type. (E.g: float, double, half)");
//
//	x *= value;
//	y *= value;
//	z *= value;
//
//	return *this;
//}

//template <typename T>
//Vector3<T>& Vector3<T>::operator /= (const Vector3<T> &value) {
//	x /= value.x;
//	y /= value.y;
//	z /= value.z;
//
//	return *this;
//}
//
//template<typename T>
//template<typename Ty>
//Vector3<T>& Vector3<T>::operator *= (const Ty& value)
//{
//	static_assert(std::is_arithmetic<Ty>::value,
//		"typename Ty can only be an arithmetic type. (E.g: float, double, half)");
//
//	x *= value;
//	y *= value;
//	z *= value;
//
//	return *this;
//}
//
//template <typename T>
//template <typename Ty>
//Vector3<T>& Vector3<T>::operator /= (const Ty &value) {
//
//	static_assert(std::is_arithmetic<Ty>::value,
//		"typename Ty can only be an arithmetic type. (E.g: float, double, half)");
//
//	x /= value;
//	y /= value;
//	z /= value;
//
//	return *this;
//}
//
//template <typename T>
//Vector3<T>& Vector3<T>::operator += (const Vector3<T> &other) {
//	x += other.x;
//	y += other.y;
//	z += other.z;
//
//	return *this;
//}
//
//template <typename T>
//Vector3<T>& Vector3<T>::operator -= (const Vector3<T> &other) {
//	x -= other.x;
//	y -= other.y;
//	z -= other.z;
//
//	return *this;
//}

template <typename T>
T& Vector3<T>::operator [] (std::size_t idx) {
	return data[idx];
}

template <typename T>
const T& Vector3<T>::operator [] (const std::size_t idx) const {
	return data[idx];
}

template <typename T> Vector3<T> Vector3<T>::Up = Vector3<T>(0, 1, 0);
template <typename T> Vector3<T> Vector3<T>::Down = Vector3<T>(0, -1, 0);
template <typename T> Vector3<T> Vector3<T>::Right = Vector3<T>(1, 0, 0);
template <typename T> Vector3<T> Vector3<T>::Left = Vector3<T>(-1, 0, 0);
template <typename T> Vector3<T> Vector3<T>::Forward = Vector3<T>(0, 0, 1);
template <typename T> Vector3<T> Vector3<T>::Back = Vector3<T>(0, 0, -1);

template <typename T> Vector3<T> Vector3<T>::Zero = Vector3<T>(0, 0, 0);
template <typename T> Vector3<T> Vector3<T>::One = Vector3<T>(1, 1, 1);

template <typename T>
T Vector3<T>::SquaredMagnitude() const {
	return (x * x) + (y * y) + (z * z);
}

template <typename T>
T Vector3<T>::Magnitude() const {
	return sqrt(SquaredMagnitude());
}

template <typename T>
float Vector3<T>::MagnitudeF() const {
	return sqrtf((float)SquaredMagnitude());
}

template <typename T>
Vector3<T> Vector3<T>::Normalised(InvSqrtPrecision precision) const {
	return Vector3((*this)).Normalise(precision); /// Returns a copy of the current Vector3 multiplied by 1/sqrt(SquaredMagnitude())
}

template <typename T>
Vector3<T>& Vector3<T>::Normalise(InvSqrtPrecision precision) {
	float invSqrtX = FastInvSqrt((float)Vector3::SquaredMagnitude(), precision);

	x *= invSqrtX;
	y *= invSqrtX;
	z *= invSqrtX;

	return *this;
}

template <typename T>
Vector3<T> Vector3<T>::Abs() const {
	return Vector3(fabs(x), fabs(y), fabs(z));
}

template <typename T>
T Vector3<T>::Dot(const Vector3<T>& lhs, const Vector3<T>& rhs) {
	return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
}

template <typename T>
Vector3<T> Vector3<T>::Cross(const Vector3<T>& lhs, const Vector3<T>& rhs) {
	return Vector3<T>(
		(lhs.y * rhs.z) - (lhs.z * rhs.y),
		(lhs.z * rhs.x) - (lhs.x * rhs.z),
		(lhs.x * rhs.y) - (lhs.y * rhs.x)
	);
}
