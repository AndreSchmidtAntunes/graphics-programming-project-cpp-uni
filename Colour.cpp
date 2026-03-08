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

const Colour Colour::RED = Colour(1, 0, 0, 1);
const Colour Colour::GREEN = Colour(0, 1, 0, 1);
const Colour Colour::BLUE = Colour(0, 0, 1, 1);

const Colour Colour::BLACK = Colour(0, 0, 0, 1);
const Colour Colour::WHITE = Colour(1, 1, 1, 1);
const Colour Colour::EMPTY, Colour::NIL = Colour(0, 0, 0, 0);

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