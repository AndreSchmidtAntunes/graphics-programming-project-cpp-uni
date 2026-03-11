#pragma once

#include "FastInvSqrt.h"
#include <math.h>
#include <ostream>
#include <array>

struct Vector4 {
protected:

	//double* vElements = new double[4] { };

public:

	union {
		struct { double x, y, z, w; };
		std::array<double, 4> vElements = { };
	};


	//double& x = vElements[0];
	//double& y = vElements[1];
	//double& z = vElements[2];
	//double& w = vElements[3];

	//Vector4() : vElements(new double[4] {0, 0, 0, 0}), x(vElements[0]), y(vElements[1]), z(vElements[2]), w(vElements[3]) {};

	//Vector4(double x, double y, double z, double w) : vElements(new double[4] {x, y, z, w}), x(vElements[0]), y(vElements[1]), z(vElements[2]), w(vElements[3]) {};

	//Vector4(const Vector4& other) : vElements(new double[4] {other.x, other.y, other.z, other.w}), x(vElements[0]), y(vElements[1]), z(vElements[2]), w(vElements[3]) {};

	//Vector4(double value) : vElements(new double[4] {value, value, value, value}), x(vElements[0]), y(vElements[1]), z(vElements[2]), w(vElements[3]) {};

	Vector4(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {};

	Vector4(const Vector4& other) : x(other.x), y(other.y), z(other.z), w(other.w) {};

	Vector4(double value = 0) : x(value), y(value), z(value), w(value) {};

	~Vector4() {
		//delete[4] vElements;
	}

	Vector4 operator * (const Vector4 &other) const;
	Vector4 operator / (const Vector4 &other) const;
	Vector4 operator + (const Vector4 &other) const;
	Vector4 operator - (const Vector4 &other) const;

	Vector4 operator * (const double& value) const;
	Vector4 operator / (const double& value) const;

	Vector4 operator - () const { return Vector4(-x, -y, -z, -w); };

	Vector4& operator *= (const Vector4& value);
	Vector4& operator /= (const Vector4& value);
	Vector4& operator += (const Vector4& value);
	Vector4& operator -= (const Vector4& value);

	Vector4& operator *= (const double& value);
	Vector4& operator /= (const double& value);

	double& operator [] (std::size_t idx);

	operator bool() const;

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
	double SquaredMagnitude() const;

	/// <returns>The magnitude(distance) of the given vector at double floating point precision.<br/> <c>sqrt(x^2 + y^2 + z^2 + w^2)</c></returns>
	double Magnitude() const;

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

	static double Dot(Vector4 lhs, Vector4 rhs);
};