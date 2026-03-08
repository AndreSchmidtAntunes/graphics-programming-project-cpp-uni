#pragma once

#include "FastInvSqrt.h"
#include <math.h>
#include <ostream>

struct Vector4 {

	double x, y, z, w;

	Vector4() : x(0), y(0), z(0), w(0) {};

	Vector4(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {};

	Vector4(const Vector4& other) : x(other.x), y(other.y), z(other.z), w(other.w) {};

	Vector4(double value) : x(value), y(value), z(value), w(value) {};

	Vector4 operator * (const Vector4 &other) const;

	Vector4 operator * (const double &value) const;

	Vector4 operator / (const Vector4 &other) const;

	Vector4 operator / (const double &value) const;

	Vector4 operator + (const Vector4 &other) const;

	Vector4 operator - (const Vector4 &other) const;

	Vector4 operator - () const { return Vector4(-x, -y, -z, -w); };

	Vector4& operator *= (const Vector4& value);
	Vector4& operator *= (const double& value);
	Vector4& operator /= (const Vector4& value);
	Vector4& operator /= (const double& value);
	Vector4& operator += (const Vector4& value);
	Vector4& operator -= (const Vector4& value);

	double& operator [] (int i);

	operator bool();

	bool operator == (Vector4 other);
	bool operator != (Vector4 other);

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
	double SquaredMagnitude();

	/// <returns>The magnitude(distance) of the given vector at double floating point precision.<br/> <c>sqrt(x^2 + y^2 + z^2 + w^2)</c></returns>
	double Magnitude();

	/// <returns>The magnitude(distance) of the given vector at floating point precision. <br/> <c>sqrt(x^2 + y^2 + z^2 + w^2)</c></returns>
	float MagnitudeF();

	Vector4 Normalised(InvSqrtPrecision precision = InvSqrtPrecision::MEDIUM);

	/// <summary>
	/// Normalises the current vector and assigns it to the current vector. <br/>
	/// <c>[this] / sqrt(x^2 + y^2 + z^2 + w^2/c>
	/// </summary>
	Vector4& Normalise(InvSqrtPrecision precision = InvSqrtPrecision::MEDIUM);

	/// <returns>w copy of the vector where x, y, z, and w are absolute values.</returns>
	Vector4 Abs();

	static double Dot(Vector4 lhs, Vector4 rhs);

};