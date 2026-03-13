#include "Colour.h"

const Colour Colour::RED = Colour(1, 0, 0, 1);
const Colour Colour::GREEN = Colour(0, 1, 0, 1);
const Colour Colour::BLUE = Colour(0, 0, 1, 1);
const Colour Colour::BLACK = Colour(0, 0, 0, 1);
const Colour Colour::WHITE = Colour(1, 1, 1, 1);
const Colour Colour::EMPTY = Colour(0, 0, 0, 0);
const Colour Colour::NIL = Colour(0, 0, 0, 0);

const Colour Colour::operator * (const Colour &other) const {
	return Colour(r * other.r, g * other.g, b * other.b, a * other.a);
}

const Colour Colour::operator * (const float &value) const {
	return Colour(r * value, g * value, b * value, a * value);
}

const Colour Colour::operator / (const Colour &other) const {
	return Colour(r / other.r, g / other.g, b / other.b, a / other.a);
}

const Colour Colour::operator / (const float &value) const {
	return Colour(r / value, g / value, b / value, a / value);
}
const Colour Colour::operator + (const Colour &other) const {
	return Colour(r + other.r, g + other.g, b + other.b, a + other.a);
}

const Colour Colour::operator - (const Colour &other) const {
	return Colour(r - other.r, g - other.g, b - other.b, a - other.a);
}

Colour& Colour::operator = (const Colour& other) {
	r = other.r;
	g = other.g;
	b = other.b;
	a = other.a;

	return *this;
}

Colour& Colour::operator *= (const Colour& value) {
	r *= value.r;
	g *= value.g;
	b *= value.b;
	a *= value.a;

	return *this;
}

Colour& Colour::operator *= (const float& value) {
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

Colour& Colour::operator /= (const float& value) {
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

Colour::operator bool() const {
	return r || g || b || a;
}

float& Colour::operator [] (std::size_t idx) {
	return cElements[idx];
}

bool Colour::operator == (Colour other) const {
	return (r == other.r) && (g == other.g) && (b == other.b) && (a == other.a);
}

bool Colour::operator != (Colour other) const {
	return (r != other.r) || (g != other.g) || (b != other.b) || (a != other.a);
}

float Colour::SquaredMagnitudeRGB() const {
	return ((float)r * (float)r) + ((float)g * (float)g) + ((float)b * (float)b);
}

Colour Colour::NormalisedRGB(InvSqrtPrecision precision) const {
	return Colour((*this)).NormaliseRGB(precision); /// Returns a copy of the current Colour multiplied by 1/sqrt(SquaredMagnitude())
}

Colour& Colour::NormaliseRGB(InvSqrtPrecision precision) {
	float invSqrtX = FastInvSqrt((float)Colour::SquaredMagnitudeRGB(), precision);

	r = float(invSqrtX * r);
	g = float(invSqrtX * g);
	b = float(invSqrtX * b);

	return *this;
}

Colour Colour::HexRGBAToColour(const uint& hex) {

	const double div255 = 1.0 / 255.0;

	Colour result;

	const uint r_mask	= 0xff000000;
	const uint g_mask = 0x00ff0000;
	const uint b_mask	= 0x0000ff00;
	const uint a_mask = 0x000000ff;

	uint masked_r = hex & r_mask;
	uint masked_g = hex & g_mask;
	uint masked_b = hex & b_mask;
	uint masked_a = hex & a_mask;

	result.r = float(double(masked_r >> 24) * div255);
	result.g = float(double(masked_g >> 16) * div255);
	result.b = float(double(masked_b >>  8) * div255);
	result.a = float(double(masked_a) *       div255);

	return result;
}	

Colour Colour::HexRGBToColour(const uint& hex) {

	const double div255 = 1.0 / 255.0;

	Colour result;

	const uint r_mask = 0xff0000;
	const uint g_mask = 0x00ff00;
	const uint b_mask = 0x0000ff;

	uint masked_r = hex & r_mask;
	uint masked_g = hex & g_mask;
	uint masked_b = hex & b_mask;

	result.r = float(double(masked_r >> 16) * div255);
	result.g = float(double(masked_g >>  8) * div255);
	result.b = float(double(masked_b) *		  div255);
	result.a = float(1);

	return result;
}