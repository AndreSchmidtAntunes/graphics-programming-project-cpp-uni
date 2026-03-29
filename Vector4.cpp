#include "Vector4.h"

template <typename T> 
template <typename Ty>
Vector4<T> Vector4<T>::operator * (const Vector4<Ty>& other) const {
	return Vector4<T>(*this) *= other;
}

template <typename T>
template <typename Ty>
Vector4<T> Vector4<T>::operator * (const Ty& other) const {
	return Vector4<T>(*this) *= value;
}

template <typename T>
Vector4<T>::operator bool() const {
	return x || y || z || w;
}

template<typename T>
bool Vector4<T>::operator == (const Vector4<T>& other) const {
	return x == other.x && y == other.y && z == other.z && w == other.w;
}

template<typename T>
bool Vector4<T>::operator != (const Vector4<T>& other) const {
	return x != other.x || y != other.y || z != other.z || w != other.w;
}

template <typename T>
T& Vector4<T>::operator [] (const std::size_t idx) {
	return data[idx];
}

template <typename T>
const T& Vector4<T>::operator [] (const std::size_t idx) const {
	return data[idx];
}

template <typename T>
T Vector4<T>::SquaredMagnitude() const {
	return (x * x) + (y * y) + (z * z) + (w * w);
}

template <typename T>
T Vector4<T>::Magnitude() const {
	return sqrt(SquaredMagnitude());
}

template <typename T>
float Vector4<T>::MagnitudeF() const {
	return sqrtf((float)SquaredMagnitude());
}

template <typename T>
Vector4<T> Vector4<T>::Normalised(InvSqrtPrecision precision) const {
	return Vector4((*this)).Normalise(precision); /// Returns w copy of the current Vector4 multiplied by 1/sqrt(SquaredMagnitude())
}

template <typename T>
Vector4<T>& Vector4<T>::Normalise(InvSqrtPrecision precision) {
	float invSqrtX = FastInvSqrt((float)Vector4<T>::SquaredMagnitude(), precision);

	x *= invSqrtX;
	y *= invSqrtX;
	z *= invSqrtX;
	w *= invSqrtX;

	return *this;
}

template <typename T>
Vector4<T> Vector4<T>::Abs() const {
	return Vector4(fabs(x), fabs(y), fabs(z), fabs(w));
}

template <typename T>
T Vector4<T>::Dot(Vector4 lhs, Vector4 rhs) {
	return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z) + (lhs.w * rhs.w);

}