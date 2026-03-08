#include "Vector3.h"

Vector3 Vector3::operator * (const Vector3 &other) const {
	return Vector3(x * other.x, y * other.y, z * other.z);
}

Vector3 Vector3::operator * (const double &value) const {
	return Vector3(x * value, y * value, z * value);
}

Vector3 Vector3::operator / (const Vector3 &other) const {
	return Vector3(x / other.x, y / other.y, z / other.z);
}

Vector3 Vector3::operator / (const double &value) const {
	return Vector3(x / value, y / value, z / value);
}

Vector3 Vector3::operator + (const Vector3 &other) const {
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator - (const Vector3 &other) const {
	return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3::operator bool() {
	return x || y || z;
}

bool Vector3::operator == (Vector3 other) {
	return x == other.x && y == other.y && z == other.z;
}

bool Vector3::operator != (Vector3 other) {
	return x != other.x || y != other.y || z != other.z;
}

Vector3& Vector3::operator *= (const Vector3 &value) {
	x *= value.x;
	y *= value.y;
	z *= value.z;

	return *this;
}

Vector3& Vector3::operator *= (const double &value) {
	x *= value;
	y *= value;
	z *= value;

	return *this;
}

Vector3& Vector3::operator /= (const Vector3 &value) {
	x /= value.x;
	y /= value.y;
	z /= value.z;

	return *this;
}

Vector3& Vector3::operator /= (const double &value) {
	x /= value;
	y /= value;
	z /= value;

	return *this;
}

Vector3& Vector3::operator += (const Vector3 &value) {
	x += value.x;
	y += value.y;
	z += value.z;	

	return *this;
}

Vector3& Vector3::operator -= (const Vector3 &value) {
	x -= value.x;
	y -= value.y;
	z -= value.z;

	return *this;
}

double& Vector3::operator [] (int i) {
	try {
		// Code that may throw an exception

		switch (i) {
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			throw 0;
		}
	}	

	catch (int) {
		// Attempted to index null value in a Vector3
		throw std::out_of_range("Index is out of range. Defaulted to 0");
		return x;
	}
}

const Vector3 Vector3::Up = Vector3(0, 1, 0);
const Vector3 Vector3::Down = Vector3(0, -1, 0);
const Vector3 Vector3::Right = Vector3(1, 0, 0);
const Vector3 Vector3::Left = Vector3(-1, 0, 0);
const Vector3 Vector3::Forward = Vector3(0, 0, 1);
const Vector3 Vector3::Back = Vector3(0, 0, -1);

const Vector3 Vector3::Zero = Vector3(0, 0, 0);
const Vector3 Vector3::One = Vector3(1, 1, 1);

double Vector3::SquaredMagnitude() {
	return (x * x) + (y * y) + (z * z);
}

double Vector3::Magnitude() {
	return sqrt(SquaredMagnitude());
}

float Vector3::MagnitudeF() {
	return sqrtf((float)SquaredMagnitude());
}

Vector3 Vector3::Normalised(InvSqrtPrecision precision) {
	return Vector3((*this)).Normalise(precision); /// Returns a copy of the current Vector3 multiplied by 1/sqrt(SquaredMagnitude())
}

Vector3& Vector3::Normalise(InvSqrtPrecision precision) {
	float invSqrtX = FastInvSqrt((float)Vector3::SquaredMagnitude(), precision);

	x *= invSqrtX;
	y *= invSqrtX;
	z *= invSqrtX;

	return *this;
}

Vector3 Vector3::Abs() {
	return Vector3(fabs(x), fabs(y), fabs(z));
}

double Vector3::Dot(Vector3 lhs, Vector3 rhs) {
	return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
}

Vector3 Vector3::Cross(Vector3 lhs, Vector3 rhs) {
	return Vector3(
		lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x
	);
}
