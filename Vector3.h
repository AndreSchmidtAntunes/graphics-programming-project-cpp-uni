#pragma once

#include "FastInvSqrt.h"
#include <array>
#include <math.h>
#include <ostream>
#include <stdexcept>

#define uint unsigned int

struct Vector3 {
public:

	union {
		struct { double x, y, z; };
		std::array<double, 3> vElements { };
	};

	Vector3(double x, double y, double z) : x(x), y(y), z(z) {};

	Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z) {};

	explicit Vector3(double value) : x(value), y(value), z(value) {};

	Vector3() : Vector3(0) {};

	~Vector3() { };
	
	Vector3 operator * (const Vector3 &other) const;
	Vector3 operator / (const Vector3 &other) const;
	Vector3 operator + (const Vector3 &other) const;
	Vector3 operator - (const Vector3 &other) const;

	Vector3 operator * (const double& value) const;
	Vector3 operator / (const double& value) const;

	Vector3 operator * (const float& value) const;
	Vector3 operator / (const float& value) const;

	Vector3 operator - () const { return Vector3(-x, -y, -z); };

	Vector3& operator = (const Vector3& value);

	Vector3& operator *= (const Vector3& value);
	Vector3& operator /= (const Vector3& value);
	Vector3& operator += (const Vector3& value);
	Vector3& operator -= (const Vector3& value);

	Vector3& operator *= (const double& value);
	Vector3& operator /= (const double& value);

	Vector3& operator *= (const float& value);
	Vector3& operator /= (const float& value);

	double& operator [] (const uint idx);
	const double& operator [] (const uint idx) const;

	operator bool() const;

	bool operator == (Vector3 other) const;
	bool operator != (Vector3 other) const;

	friend std::ostream& operator << (std::ostream& ostream, const Vector3 vec) {
		ostream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
		return ostream;
	}

	static const Vector3 Up;
	static const Vector3 Down;
	static const Vector3 Left;
	static const Vector3 Right;
	static const Vector3 Forward;
	static const Vector3 Back;

	static const Vector3 Zero;
	static const Vector3 One;

	/// <summary>
	/// Used to avoid Square rooting when possible.
	/// </summary>
	/// <returns>The magnitude(distance) of the given vector squared. <br/> <c>x^2 + y^2 + z^2</c></returns>
	double SquaredMagnitude() const;

	/// <returns>The magnitude(distance) of the given vector at double floating point precision.<br/> <c>sqrt(x^2 + y^2 + z^2)</c></returns>
	double Magnitude() const;

	/// <returns>The magnitude(distance) of the given vector at floating point precision. <br/> <c>sqrt(x^2 + y^2 + z^2)</c></returns>
	float MagnitudeF() const;

	/// <summary>
	/// Uses the Quake fast inverse square root algorithm to normalise the vector.
	/// </summary>
	/// <returns>
	/// A copy of the vector facing in the same direction, but where it's magnitude is equal to 1. <br/> 
	/// <c>[this] / sqrt(x^2 + y^2 + z^2)</c>
	/// </returns>
	Vector3 Normalised(InvSqrtPrecision precision = InvSqrtPrecision::MEDIUM) const;

	/// <summary>
	/// Normalises the current vector and assigns it to the current vector. <br/>
	/// <c>[this] / sqrt(x^2 + y^2 + z^2)</c>
	/// </summary>
	Vector3& Normalise(InvSqrtPrecision precision = InvSqrtPrecision::MEDIUM);

	/// <returns>A copy of the vector where x, y, and z are absolute values.</returns>
	Vector3 Abs() const;


	static double Dot(Vector3 lhs, Vector3 rhs);

	static Vector3 Cross(Vector3 lhs, Vector3 rhs);

};