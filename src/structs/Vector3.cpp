#include "Vector3.h"

template <typename T>
const bool Vector3<T>::operator == (const Vector3<T>& other) const {
	return x == other.x && y == other.y && z == other.z;
}

template <typename T>
const bool Vector3<T>::operator != (const Vector3<T>& other) const {
	return x != other.x || y != other.y || z != other.z;
}

template <typename T>
T& Vector3<T>::operator [] (std::size_t idx) {
	return data[idx];
}

template <typename T>
const T& Vector3<T>::operator [] (const std::size_t idx) const {
	return data[idx];
}

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
