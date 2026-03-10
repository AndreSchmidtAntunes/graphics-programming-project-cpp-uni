#include "Vector4.h"

Vector4 Vector4::operator * (const Vector4& other) const {
	return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
}

Vector4 Vector4::operator * (const double& value) const {
	return Vector4(x * value, y * value, z * value, w * value);
}

Vector4 Vector4::operator / (const Vector4& other) const {
	return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
}

Vector4 Vector4::operator / (const double& value) const {
	return Vector4(x / value, y / value, z / value, w / value);
}

Vector4 Vector4::operator + (const Vector4& other) const {
	return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}

Vector4 Vector4::operator - (const Vector4& other) const {
	return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}

Vector4::operator bool() const {
	return x || y || z || w;
}

bool Vector4::operator == (Vector4 other) const {
	return x == other.x && y == other.y && z == other.z && w == other.w;
}

bool Vector4::operator != (Vector4 other) const {
	return x != other.x || y != other.y || z != other.z || w != other.w;
}

Vector4& Vector4::operator *= (const Vector4& value) {
	x *= value.x;
	y *= value.y;
	z *= value.z;
	w *= value.w;

	return *this;
}

Vector4& Vector4::operator *= (const double& value) {
	x *= value;
	y *= value;
	z *= value;
	w *= value;

	return *this;
}

Vector4& Vector4::operator /= (const Vector4& value) {
	x /= value.x;
	y /= value.y;
	z /= value.z;
	w /= value.w;

	return *this;
}

Vector4& Vector4::operator /= (const double& value) {
	x /= value;
	y /= value;
	z /= value;
	w /= value;

	return *this;
}

Vector4& Vector4::operator += (const Vector4& value) {
	x += value.x;
	y += value.y;
	z += value.z;
	w += value.w;

	return *this;
}

Vector4& Vector4::operator -= (const Vector4& value) {
	x -= value.x;
	y -= value.y;
	z -= value.z;
	w -= value.w;

	return *this;
}

double& Vector4::operator [] (std::size_t idx) {
	return vElements[idx];
}

const Vector4 Vector4::Up = Vector4(0, 1, 0, 0);
const Vector4 Vector4::Down = Vector4(0, -1, 0, 0);
const Vector4 Vector4::Right = Vector4(1, 0, 0, 0);
const Vector4 Vector4::Left = Vector4(-1, 0, 0, 0);
const Vector4 Vector4::Forward = Vector4(0, 0, 1, 0);
const Vector4 Vector4::Back = Vector4(0, 0, -1, 0);
const Vector4 Vector4::Ana = Vector4(0, 0, 0, 1);
const Vector4 Vector4::Kata = Vector4(0, 0, 0, -1);

const Vector4 Vector4::Zero = Vector4(0, 0, 0, 0);
const Vector4 Vector4::One = Vector4(1, 1, 1, 1);

double Vector4::SquaredMagnitude() const {
	return (x * x) + (y * y) + (z * z) + (w * w);
}

double Vector4::Magnitude() const {
	return sqrt(SquaredMagnitude());
}

float Vector4::MagnitudeF() const {
	return sqrtf((float)SquaredMagnitude());
}

Vector4 Vector4::Normalised(InvSqrtPrecision precision) const {
	return Vector4((*this)).Normalise(precision); /// Returns w copy of the current Vector4 multiplied by 1/sqrt(SquaredMagnitude())
}

Vector4& Vector4::Normalise(InvSqrtPrecision precision) {
	float invSqrtX = FastInvSqrt((float)Vector4::SquaredMagnitude(), precision);

	x *= invSqrtX;
	y *= invSqrtX;
	z *= invSqrtX;
	w *= invSqrtX;

	return *this;
}

Vector4 Vector4::Abs() const {
	return Vector4(fabs(x), fabs(y), fabs(z), fabs(w));
}

double Vector4::Dot(Vector4 lhs, Vector4 rhs) {
	return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z) + (lhs.w * rhs.w);

}