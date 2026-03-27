#pragma once

#include "FastInvSqrt.h"
#include "Vector3.h"
#include <array>
#include <math.h>
#include <ostream>
#include <stdexcept>

#define uint unsigned int

template <class T = double>
struct Vector4 {
public:

	union {
		struct { T x, y, z, w; };
		std::array<T, 4> data { };
	};

	Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {};

	Vector4(const Vector4& other) : x(other.x), y(other.y), z(other.z), w(other.w) {};

	Vector4(Vector3<T> vec3, T w = 0) : x(vec3.x), y(vec3.y), z(vec3.z), w(w) {};

	Vector4(T value = 0) : x(value), y(value), z(value), w(value) {};


	~Vector4() { }

	Vector4 operator * (const Vector4 &other) const;
	Vector4 operator / (const Vector4 &other) const;
	Vector4 operator + (const Vector4 &other) const;
	Vector4 operator - (const Vector4 &other) const;

	Vector4 operator * (const T& value) const;
	Vector4 operator / (const T& value) const;

	Vector4 operator * (const float& value) const;
	Vector4 operator / (const float& value) const;

	Vector4 operator - () const { return Vector4(-x, -y, -z, -w); };

	Vector4& operator *= (const Vector4& value);
	Vector4& operator /= (const Vector4& value);
	Vector4& operator += (const Vector4& value);
	Vector4& operator -= (const Vector4& value);

	Vector4& operator *= (const T& value);
	Vector4& operator /= (const T& value);

	Vector4& operator *= (const float& value);
	Vector4& operator /= (const float& value);

	T& operator [] (const uint idx);
	const T& operator [] (const uint idx) const;

	operator bool() const;

	operator Vector3<T>() const { return Vector3(x, y, z); }

	bool operator == (Vector4 other) const;
	bool operator != (Vector4 other) const;

	friend std::ostream& operator << (std::ostream& ostream, const Vector4 Vector4) {
		ostream << "(" << Vector4.x << ", " << Vector4.y << ", " << Vector4.z << "," << Vector4.w << ")";
		return ostream;
	}

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
};