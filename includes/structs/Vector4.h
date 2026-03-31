#pragma once

#include "FastInvSqrt.h"
#include <array>
#include <math.h>
#include <ostream>
#include <stdexcept>

#include "defines.h"

template <typename T>
class Vector3;

template <typename T = double>
struct Vector4 {
public:

	static_assert(std::is_arithmetic<T>::value,
		"typename T can only be a floating point type. (E.g: float, double, half)");

	union {
		struct { T x, y, z, w; };
		std::array<T, 4> data { };
	};

	Vector4(T x, T y, T z = T{}, T w = T{}) : x(x), y(y), z(z), w(w) {};

	template <typename Ty>
	Vector4(const Vector4<Ty>& other) : x(other.x), y(other.y), z(other.z), w(other.w) {};

	Vector4(Vector3<T> vec3, T w = T{}) : x(vec3.x), y(vec3.y), z(vec3.z), w(w) {};

	Vector4(T value = T{}) : x(value), y(value), z(value), w(value) {};

	~Vector4() { }

	template <typename Ty>
	Vector4<T>& Vector4<T>::operator *= (const Vector4<Ty>& rhs) {
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		w *= rhs.w;

		return SELF;
	}

	template <typename Ty>
	Vector4<T>& Vector4<T>::operator /= (const Vector4<Ty>& rhs) {
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		w /= rhs.w;

		return SELF;
	}

	template <typename Ty>
	Vector4<T>& Vector4<T>::operator += (const Vector4<Ty>& rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;

		return SELF;
	}

	template <typename Ty>
	Vector4<T>& Vector4<T>::operator -= (const Vector4<Ty>& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;

		return SELF;
	}

	template <typename Ty>
	Vector4<T>& Vector4<T>::operator *= (const Ty& rhs) {

		static_assert(std::is_arithmetic<Ty>::value,
			"typename Ty can only be a floating point type (E.g: float, double, half)");

		x *= rhs;
		y *= rhs;
		z *= rhs;
		w *= rhs;

		return SELF;
	}

	template <typename Ty>
	Vector4<T>& Vector4<T>::operator /= (const Ty& rhs) {

		static_assert(std::is_arithmetic<Ty>::value,
			"typename Ty can only be a floating point type (E.g: float, double, half)");

		x /= rhs;
		y /= rhs;
		z /= rhs;
		w /= rhs;

		return SELF;
	}

	template <typename Ty> Vector4<T> operator * (const Vector4<Ty> &other) const;
	template <typename Ty> Vector4<T> operator / (const Vector4<Ty> &other) const;
	template <typename Ty> Vector4<T> operator + (const Vector4<Ty> &other) const;
	template <typename Ty> Vector4<T> operator - (const Vector4<Ty> &other) const;

	template <typename Ty> Vector4<T> operator * (const Ty& value) const;
	template <typename Ty> Vector4<T> operator / (const Ty& value) const;

	Vector4<T> operator - () const { return Vector4<T>(-x, -y, -z, -w); };

	T& operator [] (const uint idx);
	const T& operator [] (const uint idx) const;

	operator bool() const;

	bool operator == (const Vector4<T>& other) const;
	bool operator != (const Vector4<T>& other) const;

	friend Vector3<T> operator Vector3<T>() const { return Vector3<T>(x, y, z); }

	friend std::ostream& operator << (std::ostream& ostream, const Vector4<T> Vector4) {
		ostream << "(" << Vector4.x << ", " << Vector4.y << ", " << Vector4.z << "," << Vector4.w << ")";
		return ostream;
	}

	/// <summary>
	/// Used to avoid Square rooting when possible.
	/// </summary>
	/// <returns>The magnitude(distance) of the given vector squared. <br/> <c>x^2 + y^2 + z^2 + w^2</c></returns>
	T SquaredMagnitude() const;

	/// <returns>The magnitude(distance) of the given vector at T floating point precision.<br/> <c>sqrt(x^2 + y^2 + z^2 + w^2)</c></returns>
	T Magnitude() const;

	/// <returns>The magnitude(distance) of the given vector at floating point precision. <br/> <c>sqrt(x^2 + y^2 + z^2 + w^2)</c></returns>
	float MagnitudeF() const;

	Vector4 Normalised(InvSqrtPrecision precision = InvSqrtPrecision::MEDIUM) const;

	/// <summary>
	/// Normalises the current vector and assigns it to the current vector. <br/>
	/// <c>[this] / sqrt(x^2 + y^2 + z^2 + w^2/c>
	/// </summary>
	Vector4& Normalise(InvSqrtPrecision precision = InvSqrtPrecision::MEDIUM);

	/// <returns>w copy of the vector where x, y, z, and w are absolute values.</returns>
	Vector4 Abs() const;

	static T Dot(Vector4 lhs, Vector4 rhs);

	static const Vector4 Up;
	static const Vector4 Down;
	static const Vector4 Left;
	static const Vector4 Right;
	static const Vector4 Forward;
	static const Vector4 Back;
	static const Vector4 Ana;
	static const Vector4 Kata;

	static const Vector4 Zero;
	static const Vector4 One;
};

static const Vector4<int> Up = Vector4<int>(0, 1, 0, 0);
static const Vector4<int> Down = Vector4<int>(0, -1, 0, 0);
static const Vector4<int> Right = Vector4<int>(1, 0, 0, 0);
static const Vector4<int> Left = Vector4<int>(-1, 0, 0, 0);
static const Vector4<int> Forward = Vector4<int>(0, 0, 1, 0);
static const Vector4<int> Back = Vector4<int>(0, 0, -1, 0);
static const Vector4<int> Ana = Vector4<int>(0, 0, 0, 1);
static const Vector4<int> Kata = Vector4<int>(0, 0, 0, -1);

static const Vector4<int> Zero = Vector4<int>(0);
static const Vector4<int> One = Vector4<int>(1);

template <typename T>
template <typename Ty>
Vector4<T> Vector4<T>::operator * (const Vector4<Ty>& other) const {
	return Vector4<T>(*this) *= other;
}

template <typename T>
template <typename Ty>
Vector4<T> Vector4<T>::operator / (const Vector4<Ty>& other) const {
	return Vector4<T>(*this) /= other;
}

template <typename T>
template <typename Ty>
Vector4<T> Vector4<T>::operator + (const Vector4<Ty>& other) const {
	return Vector4<T>(*this) += other;
}

template <typename T>
template <typename Ty>
Vector4<T> Vector4<T>::operator - (const Vector4<Ty>& other) const {
	return Vector4<T>(*this) -= other;
}

template <typename T>
template <typename Ty>
Vector4<T> Vector4<T>::operator * (const Ty& other) const {
	return Vector4<T>(*this) *= value;
}

template <typename T>
template <typename Ty>
Vector4<T> Vector4<T>::operator / (const Ty& other) const {
	return Vector4<T>(*this) /= value;
}


