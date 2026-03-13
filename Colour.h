#pragma once

#include "FastInvSqrt.h"
#include <array>
#include <math.h>
#include <ostream>
#include <stdexcept>

struct Colour {
public:
	
	union {
		struct { float r, g, b, a; };
		std::array<float, 4> cElements = { };
	};

	Colour(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {};

	Colour(const Colour& other) : r(other.r), g(other.g), b(other.b), a(other.a) {};

	Colour(float value = 0) : r(value), g(value), b(value), a(value) {};

	~Colour() { }

	const Colour operator * (const Colour& other) const;

	const Colour operator * (const float& value) const;

	const Colour operator / (const Colour& other) const;

	const Colour operator / (const float& value) const;
	
	const Colour operator + (const Colour& other) const;

	const Colour operator - (const Colour& other) const;

	Colour& operator = (const Colour& value);
	Colour& operator *= (const Colour& value);
	Colour& operator *= (const float& value);
	Colour& operator /= (const Colour& value);
	Colour& operator /= (const float& value);
	Colour& operator += (const Colour& value);
	Colour& operator -= (const Colour& value);

	float& operator [] (std::size_t idx);

	Colour operator - () const { return Colour(-r, -g, -b, -a); };

	operator bool() const;

	bool operator == (Colour other) const;
	bool operator != (Colour other) const;

	friend std::ostream& operator << (std::ostream& ostream, const Colour colour) {
		ostream << "(" << colour.r << ", " << colour.g << ", " << colour.b << "," << colour.a << ")";
		return ostream;
	}

	static const Colour RED;
	static const Colour GREEN;
	static const Colour BLUE;
	static const Colour BLACK;
	static const Colour WHITE;
	static const Colour EMPTY;
	static const Colour NIL;

	/// <summary>
	/// Used to avoid Square rooting when possible.
	/// </summary>
	/// <returns>The magnitude(distance) of the given (r,g,b) vector squared. <br/> <c>r^2 + g^2 + b^2</c></returns>
	float SquaredMagnitudeRGB() const;

	/// <summary>
	/// Uses the Quake fast inverse square root algorithm to normalise the vector.
	/// </summary>
	/// <returns>
	/// A normalised copy of the current colour's red, green and blue components, keeping the same colour but maximising it's brightness. <br/> 
	/// <c>[this] / sqrt(r^2 + g^2 + b^2)</c>
	/// </returns>
	Colour NormalisedRGB(InvSqrtPrecision precision = InvSqrtPrecision::MEDIUM) const;

	/// <summary>
	/// Normalises the current colour's red, green and blue components and assigns it to the current colour. <br/>
	/// <c>[this] / sqrt(r^2 + g^2 + b^2)</c>
	/// </summary>
	/// <returns>
	/// A referenced to the colour being normalised.
	/// </returns>
	Colour& NormaliseRGB(InvSqrtPrecision precision = InvSqrtPrecision::MEDIUM);

	/// <returns>A copy of the vector where r, g, and b are absolute values.</returns>
	Colour Abs() const;

	#define uint unsigned int

	static Colour HexRGBAToColour(const uint& hex);
	static Colour HexRGBToColour(const uint& hex);

};