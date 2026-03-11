#pragma once

#include "FastInvSqrt.h"
#include <math.h>
#include <ostream>
#include <array>

struct Colour {
protected:

	//std::array<short, 4> cElements = { };

public:

	union {
		struct { short r, g, b, a; };
		std::array<short, 4> cElements = { };
	};

	//short& r = cElements[0];
	//short& g = cElements[1];
	//short& b = cElements[2];
	//short& a = cElements[3];

	//Colour() : cElements(new short[4] {0, 0, 0, 0}), r(cElements[0]), g(cElements[1]), b(cElements[2]), a(cElements[3]) {};

	Colour(short r, short g, short b, short a) : r(r), g(g), b(b), a(a) {
		//cElements[0] = r;
		//cElements[1] = g;
		//cElements[2] = b;
		//cElements[3] = a;
	};

	Colour(const Colour& other) : r(other.r), g(other.g), b(other.b), a(other.a) {
		//cElements[0] = other.r;
		//cElements[1] = other.g;
		//cElements[2] = other.b;
		//cElements[3] = other.a;
	

	
	};

	Colour(short value = 0) : r(value), g(value), b(value), a(value) {
	
		//cElements[0] = value;
		//cElements[1] = value;
		//cElements[2] = value;
		//cElements[3] = value;

	
	};

	~Colour() {
		//delete[4] cElements;
	}

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
	/// 
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