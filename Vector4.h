#pragma once

#include "FastInvSqrt.h"
#include "Vector3.h"
#include <array>
#include <math.h>
#include <ostream>
#include <stdexcept>

#define uint unsigned int

template <typename T = double>
struct Vector4 {
public:

	static_assert(std::is_arithmetic<T>::value,
		"typename T can only be a floating point type. (E.g: float, double, half)");

	union {
		struct { T x, y, z, w; };
		std::array<T, 4> data { };
	};

	Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {};

	Vector4(const Vector4& other) : x(other.x), y(other.y), z(other.z), w(other.w) {};

	Vector4(Vector3<T> vec3, T w = 0) : x(vec3.x), y(vec3.y), z(vec3.z), w(w) {};

	Vector4(T value = 0) : x(value), y(value), z(value), w(value) {};


	~Vector4() { }

	template <typename Ty> Vector4<T> operator * (const Vector4<Ty> &other) const;
	template <typename Ty> Vector4<T> operator / (const Vector4<Ty> &other) const;
	template <typename Ty> Vector4<T> operator + (const Vector4<Ty> &other) const;
	template <typename Ty> Vector4<T> operator - (const Vector4<Ty> &other) const;

	template <typename Ty> Vector4<T> operator * (const Ty& value) const;
	template <typename Ty> Vector4<T> operator / (const Ty& value) const;

	Vector4 operator - () const { return Vector4(-x, -y, -z, -w); };

	T& operator [] (const uint idx);
	const T& operator [] (const uint idx) const;

	operator bool() const;

	operator Vector3<T>() const { return Vector3(x, y, z); }

	bool operator == (const Vector4<T>& other) const;
	bool operator != (const Vector4<T>& other) const;

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

template <typename T> const Vector4<T> Vector4<T>::Up      ( 0,  1,  0,  0);
template <typename T> const Vector4<T> Vector4<T>::Down    ( 0, -1,  0,  0);
template <typename T> const Vector4<T> Vector4<T>::Right   ( 1,  0,  0,  0);
template <typename T> const Vector4<T> Vector4<T>::Left    (-1,  0,  0,  0);
template <typename T> const Vector4<T> Vector4<T>::Forward ( 0,  0,  1,  0);
template <typename T> const Vector4<T> Vector4<T>::Back    ( 0,  0, -1,  0);
template <typename T> const Vector4<T> Vector4<T>::Ana     ( 0,  0,  0,  1);
template <typename T> const Vector4<T> Vector4<T>::Kata    ( 0,  0,  0, -1);

template <typename T> const Vector4<T> Vector4<T>::Zero	(0);
template <typename T> const Vector4<T> Vector4<T>::One	(1);

template <typename T, typename Ty>
Vector4<T>& operator *= (Vector4<T>& lhs, const Vector4<Ty>& rhs) {
	lhs.x *= value.x;
	lhs.y *= value.y;
	lhs.z *= value.z;
	lhs.w *= value.w;

	return lhs;
}

template <typename T, typename Ty>
Vector4<T>& operator /= (Vector4<T>& lhs, const Vector4<Ty>& rhs) {
	lhs.x /= value.x;
	lhs.y /= value.y;
	lhs.z /= value.z;
	lhs.w /= value.w;

	return lhs;
}

template <typename T, typename Ty>
Vector4<T>& operator += (Vector4<T>& lhs, const Vector4<Ty>& rhs) {
	lhs.x += value.x;
	lhs.y += value.y;
	lhs.z += value.z;
	lhs.w += value.w;

	return lhs;
}

template <typename T, typename Ty>
Vector4<T>& operator -= (Vector4<T>& lhs, const Vector4<Ty>& rhs) {
	lhs.x -= value.x;
	lhs.y -= value.y;
	lhs.z -= value.z;
	lhs.w -= value.w;

	return lhs;
}

template <typename T, typename Ty>
Vector4<T>& operator *= (Vector4<T>& lhs, const Ty& rhs) {

	static_assert(std::is_arithmetic<Ty>::value,
		"typename Ty can only be a floating point type (E.g: float, double, half)");

	lhs.x *= value;
	lhs.y *= value;
	lhs.z *= value;
	lhs.w *= value;

	return lhs;
}

template <typename T, typename Ty>
Vector4<T>& operator /= (Vector4<T>& lhs, const Ty& rhs) {

	static_assert(std::is_arithmetic<Ty>::value,
		"typename Ty can only be a floating point type (E.g: float, double, half)");

	lhs.x /= value;
	lhs.y /= value;
	lhs.z /= value;
	lhs.w /= value;

	return lhs;
}