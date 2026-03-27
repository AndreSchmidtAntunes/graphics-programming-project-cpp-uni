#pragma once

#include "FastInvSqrt.h"
#include <array>
#include <math.h>
#include <ostream>
#include <stdexcept>

#define uint unsigned int

template <class T = double>
struct Vector3 {
public:

	static_assert(std::is_arithmetic<T>::value,
		"class T can only be a floating point type. (E.g: float, double, half)");

	union {
		struct { T x, y, z; };
		std::array<T, 3> data { };
	};

	Vector3<T>(T x, T y, T z) : x(x), y(y), z(z) {};

	template <class Ty>
	Vector3<T>(const Vector3<Ty>& other) : x((T)other.x), y((T)other.y), z((T)other.z) {};

	explicit Vector3<T>(T value) : x(value), y(value), z(value) {};

	Vector3<T>(void) : Vector3<T>(0) {};

	~Vector3<T>(void) { };
	
	Vector3<T>operator * (const Vector3<T>&other) const;
	Vector3<T>operator / (const Vector3<T>&other) const;
	Vector3<T>operator + (const Vector3<T>&other) const;
	Vector3<T>operator - (const Vector3<T>&other) const;



	Vector3<T>operator - () const { return Vector3<T>(-x, -y, -z); };

	Vector3<T>& operator = (const Vector3<T>& value);

	Vector3<T>& operator *= (const Vector3<T>& value);
	Vector3<T>& operator /= (const Vector3<T>& value);
	Vector3<T>& operator += (const Vector3<T>& value);
	Vector3<T>& operator -= (const Vector3<T>& value);

	template <class Ty> Vector3<T>& operator *= (const Ty& value);
	template <class Ty> Vector3<T>& operator /= (const Ty& value);

	T& operator [] (const uint idx);
	const T& operator [] (const uint idx) const;

	operator bool() const;

	bool operator == (Vector3<T>other) const;
	bool operator != (Vector3<T>other) const;

	friend std::ostream& operator << (std::ostream& ostream, const Vector3<T>vec) {
		ostream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
		return ostream;
	}

	static const Vector3<T>Up;
	static const Vector3<T>Down;
	static const Vector3<T>Left;
	static const Vector3<T>Right;
	static const Vector3<T>Forward;
	static const Vector3<T>Back;

	static const Vector3<T>Zero;
	static const Vector3<T>One;

	/// <summary>
	/// Used to avoid Square rooting when possible.
	/// </summary>
	/// <returns>The magnitude(distance) of the given vector squared. <br/> <c>x^2 + y^2 + z^2</c></returns>
	T SquaredMagnitude() const;

	/// <returns>The magnitude(distance) of the given vector at T floating point precision.<br/> <c>sqrt(x^2 + y^2 + z^2)</c></returns>
	T Magnitude() const;

	/// <returns>The magnitude(distance) of the given vector at floating point precision. <br/> <c>sqrt(x^2 + y^2 + z^2)</c></returns>
	float MagnitudeF() const;

	/// <summary>
	/// Uses the Quake fast inverse square root algorithm to normalise the vector.
	/// </summary>
	/// <returns>
	/// A copy of the vector facing in the same direction, but where it's magnitude is equal to 1. <br/> 
	/// <c>[this] / sqrt(x^2 + y^2 + z^2)</c>
	/// </returns>
	Vector3<T>Normalised(InvSqrtPrecision precision = InvSqrtPrecision::MEDIUM) const;

	/// <summary>
	/// Normalises the current vector and assigns it to the current vector. <br/>
	/// <c>[this] / sqrt(x^2 + y^2 + z^2)</c>
	/// </summary>
	Vector3<T>& Normalise(InvSqrtPrecision precision = InvSqrtPrecision::MEDIUM);

	/// <returns>A copy of the vector where x, y, and z are absolute values.</returns>
	Vector3<T>Abs() const;


	static T Dot(Vector3<T>lhs, Vector3<T>rhs);

	static Vector3<T>Cross(Vector3<T>lhs, Vector3<T>rhs);

};

template<typename T, typename Ty>
Vector3<T> operator * (const Vector3<T>& lhs, const Vector3<Ty>& rhs) {

	static_assert(std::is_arithmetic<Ty>::value,
		"class Ty can only be a floating point type (E.g: float, double, half)");

	return Vector3<T>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

template<typename T, typename Ty>
Vector3<T> operator / (const Vector3<T>& lhs, const Vector3<Ty>& rhs) {

	static_assert(std::is_arithmetic<Ty>::value,
		"class Ty can only be a floating point type (E.g: float, double, half)");

	return Vector3<T>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
}

template<typename T, typename Ty>
Vector3<T> operator + (const Vector3<T>& lhs, const Vector3<Ty>& rhs) {

	static_assert(std::is_arithmetic<Ty>::value,
		"class Ty can only be a floating point type (E.g: float, double, half)");

	return Vector3<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

template<typename T, typename Ty>
Vector3<T> operator - (const Vector3<T>& lhs, const Vector3<Ty>& rhs) {

	static_assert(std::is_arithmetic<Ty>::value,
		"class Ty can only be a floating point type (E.g: float, double, half)");

	return Vector3<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

template<typename T, typename Ty>
Vector3<T> operator * (const Vector3<T>& lhs, const Ty& rhs) {

	static_assert(std::is_arithmetic<Ty>::value,
		"class Ty can only be a floating point type (E.g: float, double, half)");

	return Vector3<T>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

template<typename T, typename Ty>
Vector3<T> operator / (const Vector3<T>& lhs, const Ty& rhs) {

	static_assert(std::is_arithmetic<Ty>::value,
		"class Ty can only be a floating point type (E.g: float, double, half)");

	return Vector3<T>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}

template<typename T, typename Ty>
Vector3<T> operator + (const Vector3<T>& lhs, const Ty& rhs) {

	static_assert(std::is_arithmetic<Ty>::value,
		"class Ty can only be a floating point type (E.g: float, double, half)");

	return Vector3<T>(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
}

template<typename T, typename Ty>
Vector3<T> operator - (const Vector3<T>& lhs, const Ty& rhs) {

	static_assert(std::is_arithmetic<Ty>::value,
		"class Ty can only be a floating point type (E.g: float, double, half)");

	return Vector3<T>(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs);
}