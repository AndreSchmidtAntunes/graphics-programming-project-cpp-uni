#pragma once

//#include "defines.h"
//
//template <class T = double>
//struct Vector2 {
//public:
//
//	static_assert(std::is_arithmetic<T>::value,
//		"class T can only be instantiated with floating point types. (E.g: float, double, half)");
//
//	union {
//		struct { T x, y; };
//		std::array<T, 2> data;
//	};
//
//	Vector2(T x, T y) : x(x), y(y) { };
//
//	Vector2(const Vector2& other) : x(other.x), y(other.y) { };
//
//	Vector2(T value = 0) : x(value), y(value) { };
//
//	~Vector2() { };
//
//	T& operator[](const uint idx) {
//		return data[idx];
//	}
//
//	Vector2 operator + (const Vector2& other) const { return Vector2(x + other.x, y + other.y); }
//	Vector2 operator - (const Vector2& other) const { return Vector2(x - other.x, y - other.y); }
//	Vector2 operator * (const Vector2& other) const { return Vector2(x * other.x, y * other.y); }
//	Vector2 operator / (const Vector2& other) const { return Vector2(x / other.x, y / other.y); }
//
//	Vector2 operator * (const T& value) const { return Vector2(x * value, y * value); }
//	Vector2 operator / (const T& value) const { return Vector2(x / value, y / value); }
//
//	Vector2& operator += (const Vector2& other) { x += other.x; y += other.y; return SELF; }
//	Vector2& operator -= (const Vector2& other) { x -= other.x; y -= other.y; return SELF; }
//	Vector2& operator *= (const Vector2& other) { x *= other.x; y *= other.y; return SELF; }
//	Vector2& operator /= (const Vector2& other) { x /= other.x; y /= other.y; return SELF; }
//
//	Vector2& operator *= (const T& value) { x *= value; y *= value; return SELF; }
//	Vector2& operator /= (const T& value) { x /= value; y /= value; return SELF; }
//
//};
