#include "Colour.h"

Colour Colour::operator * (const Colour &other) const {
	return Colour(r * other.r, g * other.g, b * other.b, a * other.a);
}

Colour Colour::operator * (const short &value) const {
	return Colour(r * value, g * value, b * value, a * value);
}

Colour Colour::operator / (const Colour &other) const {
	return Colour(r / other.r, g / other.g, b / other.b, a / other.a);
}

Colour Colour::operator / (const short &value) const {
	return Colour(r / value, g / value, b / value, a / value);
}
Colour Colour::operator + (const Colour &other) const {
	return Colour(r + other.r, g + other.g, b + other.b, a + other.a);
}

Colour Colour::operator - (const Colour &other) const {
	return Colour(r - other.r, g - other.g, b - other.b, a - other.a);
}

Colour& Colour::operator *= (const Colour& value) {
	r *= value.r;
	g *= value.g;
	b *= value.b;
	a *= value.a;

	return *this;
}

Colour& Colour::operator *= (const short& value) {
	r *= value;
	g *= value;
	b *= value;
	a *= value;

	return *this;
}

Colour& Colour::operator /= (const Colour& value) {
	r /= value.r;
	g /= value.g;
	b /= value.b;
	a /= value.a;

	return *this;
}

Colour& Colour::operator /= (const short& value) {
	r /= value;
	g /= value;
	b /= value;
	a /= value;

	return *this;
}

Colour& Colour::operator += (const Colour& value) {
	r += value.r;
	g += value.g;
	b += value.b;
	a += value.a;

	return *this;
}

Colour& Colour::operator -= (const Colour& value) {
	r -= value.r;
	g -= value.g;
	b -= value.b;
	a -= value.a;

	return *this;
}

Colour::operator bool() {
	return r || g || b || a;
}

short& Colour::operator [] (int i) {
	try {
		// Code that may throw an exception

		switch (i) {
		case 0:
			return r;
		case 1:
			return g;
		case 2:
			return b;
		case 3:
			return a;
		default:
			throw 0;
		}
	}

	catch (int) {
		throw std::out_of_range("Index is out of range. Defaulted to 0");
		return r;
	}
}

bool Colour::operator == (Colour other) {
	return (r == other.r) && (g == other.g) && (b == other.b) && (a == other.a);
}

bool Colour::operator != (Colour other) {
	return (r != other.r) || (g != other.g) || (b != other.b) || (a != other.a);
}

const Colour Colour::RED =	 Colour(1, 0, 0, 1);
const Colour Colour::GREEN = Colour(0, 1, 0, 1);
const Colour Colour::BLUE =  Colour(0, 0, 1, 1);

const Colour Colour::BLACK = Colour(0, 0, 0, 1);
const Colour Colour::WHITE = Colour(1, 1, 1, 1);

const Colour Colour::EMPTY = Colour(0, 0, 0, 0); 
const Colour Colour::NIL   = Colour(0, 0, 0, 0);

double Colour::SquaredMagnitudeRGB() {
	return (r * r) + (g * g) + (b * b);
}

Colour Colour::NormalisedRGB(InvSqrtPrecision precision) {
	return Colour((*this)).NormaliseRGB(precision); /// Returns a copy of the current Colour multiplied by 1/sqrt(SquaredMagnitude())
}

Colour& Colour::NormaliseRGB(InvSqrtPrecision precision) {
	float invSqrtX = FastInvSqrt((float)Colour::SquaredMagnitudeRGB(), precision);

	r = short(invSqrtX * r);
	g = short(invSqrtX * g);
	b = short(invSqrtX * b);

	return *this;
}

Colour Colour::HexRGBAToColour(const uint32& hex) {

	const double div255 = 1.0 / 255.0;

	Colour result;

	const uint32 r_mask	= 0xff000000;
	const uint32 g_mask = 0x00ff0000;
	const uint32 b_mask	= 0x0000ff00;
	const uint32 a_mask = 0x000000ff;

	uint32 masked_r = hex & r_mask;
	uint32 masked_g = hex & g_mask;
	uint32 masked_b = hex & b_mask;
	uint32 masked_a = hex & a_mask;

	result.r = short(double(masked_r >> 24) * div255);
	result.g = short(double(masked_g >> 16) * div255);
	result.b = short(double(masked_b >>  8) * div255);
	result.a = short(double(masked_a) *       div255);

	return result;
}	

Colour Colour::HexRGBToColour(const uint32& hex) {

	const double div255 = 1.0 / 255.0;

	Colour result;

	const uint32 r_mask = 0xff0000;
	const uint32 g_mask = 0x00ff00;
	const uint32 b_mask = 0x0000ff;

	uint32 masked_r = hex & r_mask;
	uint32 masked_g = hex & g_mask;
	uint32 masked_b = hex & b_mask;

	result.r = short(double(masked_r >> 16) * div255);
	result.g = short(double(masked_g >>  8) * div255);
	result.b = short(double(masked_b) *		  div255);
	result.a = short(1);

	return result;
}