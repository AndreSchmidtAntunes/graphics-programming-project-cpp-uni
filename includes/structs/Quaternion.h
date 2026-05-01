#pragma once

#include "Vector3.h"
#include <array>
#include <math.h>
#include <type_traits>

template<typename T>
struct _QuaternionT {

	static_assert(std::is_arithmetic<T>::value,
		"Quaternion: T must be arithmetic!");

	union {
		struct { T scaler,	i, j, k; };
		struct { T w,		x, y, z; };
		struct { T a,		b, c, d; };
		std::array<T, 4> data { };
	};

	inline constexpr const T NormSquared() const {
		return w * w + x * x + y * y + z * z;
	}

	inline constexpr const T Norm() const {
		return std::sqrt(NormSquared());
	}

	inline constexpr const T UnrealNormSquared() const {
		return x * x + y * y + z * z;
	}

	inline constexpr const _QuaternionT<T> Conjugate() const {
		return { w, -x, -y, -z };
	}

	inline constexpr const _QuaternionT<T> Inverse() {
		return Conjugate() / NormSquared();
	}

	inline constexpr T& operator [] (const size_t idx) { return data[idx]; }
	inline constexpr const T& operator [] (const size_t idx) const { return data[idx]; }

	template<typename T1> requires(std::is_convertible<T1, T>::value)
	constexpr _QuaternionT<T>& operator=(const _QuaternionT<T1>& other) {
		w = other.w;
		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}

	template<typename T1> requires(std::is_convertible<T1, T>::value)
	constexpr _QuaternionT<T>& operator += (const _QuaternionT<T1>& other) {
		w += other.w;
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}
	template<typename T1> requires(std::is_convertible<T1, T>::value)
	constexpr friend const _QuaternionT<T> operator + (const _QuaternionT<T>& lhs, const _QuaternionT<T1>& rhs) {
		return _QuaternionT(lhs) += rhs;
	}

	template<typename T1> requires(std::is_convertible<T1, T>::value)
	constexpr _QuaternionT<T>& operator -= (const _QuaternionT<T1>& other) {
		w -= other.w;
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	template<typename T1> requires(std::is_convertible<T1, T>::value)
	constexpr friend const _QuaternionT<T> operator - (const _QuaternionT<T>& lhs, const _QuaternionT<T1>& rhs) {
		return _QuaternionT(lhs) -= rhs;
	}

	template<typename T1> requires(std::is_convertible<T1, T>::value)
	constexpr _QuaternionT<T>& operator *= (const _QuaternionT<T1>& other) {

		T temp_w = w * other.w - x * other.x - y * other.y - z * other.z;
		T temp_x = w * other.x + x * other.w + y * other.z - z * other.y;
		T temp_y = w * other.y - x * other.z + y * other.w + z * other.x;
		T temp_z = w * other.z + x * other.y - y * other.x + z * other.w;

		w = temp_w;
		x = temp_x;
		y = temp_y;
		z = temp_z;

		return *this;
	}
	template<typename T1> requires(std::is_convertible<T1, T>::value)
	constexpr friend const _QuaternionT<T> operator * (const _QuaternionT<T>& lhs, const _QuaternionT<T1>& rhs) {
		return _QuaternionT(lhs) *= rhs;
	}

	template<typename T1> requires(std::is_convertible<T1, T>::value)
	constexpr _QuaternionT<T> operator /= (const _QuaternionT<T1>& other) {

		T norm_squared = other.NormSquarez;

		T temp_w = w * other.w + x * other.x + y * other.y + z * other.z;
		T temp_x = -w * other.x + x * other.w - y * other.z + z * other.y;
		T temp_y = -w * other.y + x * other.z + y * other.w - z * other.x;
		T temp_z = -w * other.z - x * other.y + y * other.x + z * other.w;

		w = temp_w / norm_squared;
		x = temp_x / norm_squared;
		y = temp_y / norm_squared;
		z = temp_z / norm_squared;

		return *this;
	}
	template<typename T1> requires(std::is_convertible<T1, T>::value)
	constexpr friend const _QuaternionT<T> operator / (const _QuaternionT<T>& lhs, const _QuaternionT<T1>& rhs) {
		return _QuaternionT(lhs) /= rhs;
	}

	template<typename T1> requires(std::is_convertible<T1, T>::value)
	constexpr _QuaternionT<T> operator += (const T1& value) {
		w += value;
		return *this;
	}
	template<typename T1> requires(std::is_convertible<T1, T>::value)
	constexpr friend const _QuaternionT<T> operator + (const _QuaternionT<T>& lhs, const T1& value) {
		return _QuaternionT(lhs) += value;
	}

	template<typename T1> requires(std::is_convertible<T1, T>::value)
	constexpr _QuaternionT<T> operator -= (const T1& value) {
		w -= value;
		return *this;
	}
	template<typename T1> requires(std::is_convertible<T1, T>::value)
		constexpr friend const _QuaternionT<T> operator - (const _QuaternionT<T>& lhs, const T1& value) {
		return _QuaternionT(lhs) -= value;
	}

	template<typename T1> requires(std::is_convertible<T1, T>::value)
		constexpr _QuaternionT<T>& operator *= (const T1& value) {
		w *= value;
		x *= value;
		y *= value;
		z *= value;
		return *this;
	}
	template<typename T1> requires(std::is_convertible<T1, T>::value)
		constexpr friend const _QuaternionT<T> operator * (const _QuaternionT<T>& lhs, const T1& value) {
		return _QuaternionT(lhs) *= value;
	}

	template<typename T1> requires(std::is_convertible<T1, T>::value)
		constexpr _QuaternionT<T>& operator /= (const T1& value) {
		w /= value;
		x /= value;
		y /= value;
		z /= value;
		return *this;
	}
	template<typename T1> requires(std::is_convertible<T1, T>::value)
		constexpr friend const _QuaternionT<T> operator / (const _QuaternionT<T>& lhs, const T1& value) {
		return _QuaternionT(lhs) /= value;
	}

	template<typename T1> requires(std::is_convertible<T1, T>::value)
	inline constexpr _QuaternionT(const  _QuaternionT<T1>& other) : data(other.data) {}

	constexpr _QuaternionT operator+() const {
		return *this;
	}
	constexpr _QuaternionT operator-() const {
		return { -w, -x, -y, -z };
	}

	template<typename T1> requires(std::is_convertible<T1, T>::value)
		constexpr _QuaternionT(const T1& w = 0, const T1& x = 0, const T1& y = 0, const T1& z = 0) : w(w), x(x), y(y), z(z) {};
	constexpr _QuaternionT(void) : _QuaternionT(1,0,0,0) {};
	constexpr ~_QuaternionT(void) {};

	template<typename T1> requires(std::is_convertible<T1, T>::value)
	static constexpr const _QuaternionT Euler(const T1& x = 0, const T1& y = 0, const T1& z = 0) {
		T qw = cos(x / 2) * cos(y / 2) * cos(z / 2) + sin(x / 2) * sin(y / 2) * sin(z / 2);
		T qx = sin(x / 2) * cos(y / 2) * cos(z / 2) - cos(x / 2) * sin(y / 2) * sin(z / 2);
		T qy = cos(x / 2) * sin(y / 2) * cos(z / 2) + sin(x / 2) * cos(y / 2) * sin(z / 2);
		T qz = cos(x / 2) * cos(y / 2) * sin(z / 2) - sin(x / 2) * sin(y / 2) * cos(z / 2);

		return { qw, qx, qy, qz };
	}

	template<typename T1> requires(std::is_convertible<T1, T>::value)
	static constexpr const _QuaternionT Euler(const _Vector3T<T1>& euler_rotation) {
		return Euler(euler_rotation.x, euler_rotation.y, euler_rotation.z);
	}
	constexpr const _Vector3T<T> Euler() const {
		return _Vector3T<T> {
			atan2(2 * (w * y + z * x), 1 - 2 * (x * x + y * y)),
			std::asin (2 * (w * y - z * x)), 
			atan2(2 * (w * x + y * z), 1 - 2 * (y * y + z * z)) 
		};
	}

	static const _QuaternionT Identity;
	static const _QuaternionT Zero;
};

template<typename T> inline const _QuaternionT<T> _QuaternionT<T>::Identity	(1, 0, 0, 0);
template<typename T> inline const _QuaternionT<T> _QuaternionT<T>::Zero		(0, 0, 0, 0);

typedef _QuaternionT <double> QuaternionD;
typedef _QuaternionT <float> Quaternion;