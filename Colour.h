#pragma once

#include "FastInvSqrt.h"
#include <math.h>
#include <ostream>

struct Colour {

	short& r = cElements[0];
	short& g = cElements[1];
	short& b = cElements[2];
	short& a = cElements[3];

	Colour() {};

	Colour(short r, short g, short b, short a) : r(r), g(g), b(b), a(a) {};

	Colour(const Colour& colour) : r(colour.r), g(colour.g), b(colour.b), a(colour.a) {};

	const Colour operator * (const Colour &other) const;

	const Colour operator * (const short &value) const;

	const Colour operator / (const Colour &other) const;

	const Colour operator / (const short &value) const;

	const Colour operator + (const Colour &other) const;

	const Colour operator - (const Colour &other) const;

	Colour& operator = (const Colour& value);
	Colour& operator *= (const Colour& value);
	Colour& operator *= (const short& value);
	Colour& operator /= (const Colour& value);
	Colour& operator /= (const short& value);
	Colour& operator += (const Colour& value);
	Colour& operator -= (const Colour& value);

	short& operator [] (std::size_t idx);

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
	double SquaredMagnitudeRGB() const;

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
	/// 
	/// <returns>
	/// A referenced to the colour being normalised.
	/// </returns>
	Colour& NormaliseRGB(InvSqrtPrecision precision = InvSqrtPrecision::MEDIUM);

	/// <returns>A copy of the vector where r, g, and b are absolute values.</returns>
	Colour Abs() const;

	#define uint32 uint_fast32_t

	static Colour HexRGBAToColour(const uint32& hex);
	static Colour HexRGBToColour(const uint32& hex);

protected:

	short cElements[4] = { };

};