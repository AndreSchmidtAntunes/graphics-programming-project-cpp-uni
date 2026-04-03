#pragma once

//#include "FastInvSqrt.h"
//#include <array>
//#include <math.h>
//#include <ostream>
//#include <stdexcept>
//
//#include "defines.h"
//
//template <typename T = double>
//struct Vector3 {
//public:
//
//	static_assert(std::is_arithmetic<T>::value,
//		"typename T can only be a floating point type. (E.g: float, double, half)");
//
//	union {
//		struct { T x, y, z; };
//		std::array<T, 3> data { };
//	};
//
//	Vector3(const T& x, const T& y, const T& z) : x(x), y(y), z(z) {};
//
//	template <typename Ty>
//	Vector3(const Vector3<Ty>& other) : x(other.x), y(other.y), z(other.z) {};
//
//	explicit Vector3(const T& value) : x(value), y(value), z(value) {};
//
//	Vector3(void) : Vector3<T>(0) {};
//
//	~Vector3(void) { };
//
//	Vector3<T>operator - () const { return Vector3<T>(-x, -y, -z); };
//
//	template <typename Ty>
//	Vector3<T>& operator *= (const Vector3<Ty>& rhs) {
//
//		x *= rhs.x;
//		y *= rhs.y;
//		z *= rhs.z;
//
//		return *this;
//	}
//
//	template <typename Ty>
//	Vector3<T>& operator /= (const Vector3<Ty>& rhs) {
//
//		x /= rhs.x;
//		y /= rhs.y;
//		z /= rhs.z;
//
//		return *this;
//	}
//
//	template <typename Ty>
//	Vector3<T>& operator += (const Vector3<Ty>& rhs) {
//
//		x += rhs.x;
//		y += rhs.y;
//		z += rhs.z;
//
//		return *this;
//	}
//
//	template <typename Ty>
//	Vector3<T>& operator -= (const Vector3<Ty>& rhs) {
//
//		x -= rhs.x;
//		y -= rhs.y;
//		z -= rhs.z;
//
//		return *this;
//	}
//
//
//	template<typename Ty>
//	Vector3<T>& operator *= (const Ty& rhs) {
//
//		static_assert(std::is_arithmetic<Ty>::value,
//			"typename Ty can only be a floating point type (E.g: float, double, half)");
//
//		x *= rhs;
//		y *= rhs;
//		z *= rhs;
//
//		return *this;
//	}
//
//	template<typename Ty>
//	Vector3<T>& operator /= (const Ty& rhs) {
//
//		static_assert(std::is_arithmetic<Ty>::value,
//			"typename Ty can only be a floating point type (E.g: float, double, half)");
//
//		x /= rhs;
//		y /= rhs;
//		z /= rhs;
//
//		return *this;
//	}
//
//	T& operator [] (const uint idx);
//	const T& operator [] (const uint idx) const;
//
//	operator bool() const;
//
//	const bool operator == (const Vector3<T>& other) const;
//	const bool operator != (const Vector3<T>& other) const;
//
//	friend std::ostream& operator << (std::ostream& ostream, const Vector3<T>& vec) {
//		ostream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
//		return ostream;
//	}
//
//	/// <summary>
//	/// Used to avoid Square rooting when possible.
//	/// </summary>
//	/// <returns>The magnitude(distance) of the given vector squared. <br/> <c>x^2 + y^2 + z^2</c></returns>
//	T SquaredMagnitude() const;
//
//	/// <returns>The magnitude(distance) of the given vector at T floating point precision.<br/> <c>sqrt(x^2 + y^2 + z^2)</c></returns>
//	T Magnitude() const;
//
//	/// <returns>The magnitude(distance) of the given vector at floating point precision. <br/> <c>sqrt(x^2 + y^2 + z^2)</c></returns>
//	float MagnitudeF() const;
//
//	/// <summary>
//	/// Uses the Quake fast inverse square root algorithm to normalise the vector.
//	/// </summary>
//	/// <returns>
//	/// A copy of the vector facing in the same direction, but where it's magnitude is equal to 1. <br/> 
//	/// <c>[this] / sqrt(x^2 + y^2 + z^2)</c>
//	/// </returns>
//	Vector3<T>Normalised(InvSqrtPrecision precision = InvSqrtPrecision::MEDIUM) const;
//
//	/// <summary>
//	/// Normalises the current vector and assigns it to the current vector. <br/>
//	/// <c>[this] / sqrt(x^2 + y^2 + z^2)</c>
//	/// </summary>
//	Vector3<T>& Normalise(InvSqrtPrecision precision = InvSqrtPrecision::MEDIUM);
//
//	/// <returns>A copy of the vector where x, y, and z are absolute values.</returns>
//	Vector3<T> Abs() const;
//
//	static T Dot(const Vector3<T>& lhs, const Vector3<T>& rhs);
//	static Vector3<T>Cross(const Vector3<T>& lhs, const Vector3<T>& rhs);
//
//	const static Vector3 Up;
//	const static Vector3 Down;
//	const static Vector3 Left;
//	const static Vector3 Right;
//	const static Vector3 Forward;
//	const static Vector3 Back;
//
//	const static Vector3 Zero;
//	const static Vector3 One;
//};
//
//template <typename T> const Vector3<T> Vector3<T>::Up	   ( 0,  1,  0);
//template <typename T> const Vector3<T> Vector3<T>::Down    ( 0, -1,  0);
//template <typename T> const Vector3<T> Vector3<T>::Right   ( 1,  0,  0);
//template <typename T> const Vector3<T> Vector3<T>::Left    (-1,  0,  0);
//template <typename T> const Vector3<T> Vector3<T>::Forward ( 0,  0,  1);
//template <typename T> const Vector3<T> Vector3<T>::Back	   ( 0,  0, -1);
//
//template <typename T> const Vector3<T> Vector3<T>::Zero	(0);
//template <typename T> const Vector3<T> Vector3<T>::One	(1);
//
//template<typename T, typename Ty>
//Vector3<T> operator * (const Vector3<T>& lhs, const Vector3<Ty>& rhs) {
//	return Vector3<T>(lhs) *= rhs;
//}
//
//template<typename T, typename Ty>
//Vector3<T> operator / (const Vector3<T>& lhs, const Vector3<Ty>& rhs) {
//	return Vector3<T>(lhs) /= rhs;
//}
//
//template<typename T, typename Ty>
//Vector3<T> operator + (const Vector3<T>& lhs, const Vector3<Ty>& rhs) {
//	return Vector3<T>(lhs) += rhs;
//}
//
//template<typename T, typename Ty>
//Vector3<T> operator - (const Vector3<T>& lhs, const Vector3<Ty>& rhs) {
//	return Vector3<T>(lhs) -= rhs;
//}
//
//template<typename T, typename Ty> 
//Vector3<T> operator * (const Vector3<T>& lhs, const Ty& rhs) {
//
//	static_assert(std::is_arithmetic<Ty>::value,
//		"typename Ty can only be a floating point type (E.g: float, double, half)");
//
//	return Vector3<T>(lhs) *= rhs;
//}
//
//template<typename T, typename Ty>
//Vector3<T> operator / (const Vector3<T>& lhs, const Ty& rhs) {
//
//	static_assert(std::is_arithmetic<Ty>::value,
//		"typename Ty can only be a floating point type (E.g: float, double, half)");
//
//	return Vector3<T>(lhs) /= rhs;
//}

#include "Vector.h"

template<typename T>
struct VECTOR3_MEMORY_LAYOUT {

	union {
		struct { T x, y, z; };
		std::array<T, 3> data { };
	};
};

template <typename T = double>
struct Vector3 : Vectors::Vector<T, 3, VECTOR3_MEMORY_LAYOUT<T>> {
	
	using type = Vectors::Vector<T, 3>;

	using type::Vector;
	using type::operator*;
	using type::operator/;
	using type::operator+;
	using type::operator-;

	template<typename T1, uint Dim> requires (std::is_arithmetic<T1>::value && Dim >= 3) // might not need arithmetic check!!!!!!!!!!!!!
	constexpr operator Vectors::Vector<T, Dim>() const {
		return Vectors::Vector<T, Dim>(x, y, z);
	}

	template<typename T1, uint Dim> requires (std::is_arithmetic<T1>::value && Dim < 3) // might not need arithmetic check!!!!!!!!!!!!!
	constexpr operator Vectors::Vector<T, Dim>() const {
		Vectors::Vector<T, Dim> return_vector;
		for (int i = 0; i < Dim; i++)
			return_vector[i] = SELF[i];

		return return_vector;
	}

private:

	#define THIS_TYPE Vectors::Vector<T, 3>
	
public:

	union {
		Vectors::Vector<T, 3> (*this);
		struct { T x, y, z; };
	};

	constexpr Vector(T value = T{}) : THIS_TYPE(value) {}
};

//template <typename T>
//using Vector3 = Vectors::Vector<T, 3>;
