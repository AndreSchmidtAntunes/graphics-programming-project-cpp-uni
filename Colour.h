#pragma once

#include "FastInvSqrt.h"
#include <math.h>
#include <ostream>

struct Colour {

	short r;
	short g;
	short b;
	short a;

	Colour(short r, short g, short b, short a) : r(r), g(g), b(b), a(a) {};

	Colour() : r(0), g(0), b(0), a(0) {};

	Colour(const Colour& colour) : r(colour.r), g(colour.g), b(colour.b), a(colour.a) {};

	Colour operator * (const Colour &other) const;

	Colour operator * (const short &value) const;

	Colour operator / (const Colour &other) const;

	Colour operator / (const short &value) const;

	Colour operator + (const Colour &other) const;

	Colour operator - (const Colour &other) const;

	Colour& operator *= (const Colour& value);
	Colour& operator *= (const short& value);
	Colour& operator /= (const Colour& value);
	Colour& operator /= (const short& value);
	Colour& operator += (const Colour& value);
	Colour& operator -= (const Colour& value);

	short& operator [] (int i);

	Colour operator - () { return Colour(-r, -g, -b, -a); };

	operator bool();

	bool operator == (Colour other);
	bool operator != (Colour other);

	friend std::ostream& operator << (std::ostream& ostream, const Colour colour) {
		ostream << "(" << colour.r << ", " << colour.g << ", " << colour.b << "," << colour.a << ")";
		return ostream;
	}

	static const Colour 
		RED, GREEN, BLUE, 
		BLACK, WHITE,
		EMPTY, NIL;

	/// <summary>
	/// Used to avoid Square rooting when possible.
	/// </summary>
	/// <returns>The magnitude(distance) of the given (r,g,b) vector squared. <br/> <c>r^2 + g^2 + b^2</c></returns>
	double SquaredMagnitudeRGB();

	/// <summary>
	/// Uses the Quake fast inverse square root algorithm to normalise the vector.
	/// </summary>
	/// <returns>
	/// A normalised copy of the current colour's red, green and blue components, keeping the same colour but maximising it's brightness. <br/> 
	/// <c>[this] / sqrt(r^2 + g^2 + b^2)</c>
	/// </returns>
	Colour NormalisedRGB(InvSqrtPrecision precision = InvSqrtPrecision::MEDIUM);

	/// <summary>
	/// Normalises the current colour's red, green and blue components and assigns it to the current colour. <br/>
	/// <c>[this] / sqrt(r^2 + g^2 + b^2)</c>
	/// </summary>
	/// 
	/// <returns>
	/// A referenced to the colour being normalised.
	/// </returns>
	Colour& NormaliseRGB(InvSqrtPrecision precision = InvSqrtPrecision::MEDIUM);

	/// <returns>A copy of the vector where r, g, and b are absolute values.</returns>
	Colour Abs();

	#define uint32 uint_fast32_t

	static Colour HexRGBAToColour(const uint32& hex);
	static Colour HexRGBToColour(const uint32& hex);
};