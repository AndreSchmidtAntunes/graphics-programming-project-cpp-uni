#pragma once

#include <array>
#include <type_traits>
#include "Vector3.h"
#include <math.h>
//class Matrix3x3;

template<typename T>
struct _QuaternionT {
public:

	static_assert(std::is_arithmetic<T>::value,
		"Quaternion: T must be arithmetic!");

	union {

		struct { T i, j, k, scaler; };
		struct { T x, y, z, w;		};

		std::array<T, 4> data { };
	};

	T NormSquared() const {
		return w * w + x * x + y * y + z * z;
	}

	T UnrealNormSquared() const {
		return x * x + y * y + z * z;
	}

	constexpr T& operator [] (const size_t idx) { return data[idx]; }
	constexpr const T& operator [] (const size_t idx) const { return data[idx]; }

	template<typename T1> requires(std::is_convertible<T1, T>::value)
	Quaternion& operator=(const Quaternion<T1>& other) {
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
		return *this;
	}

	template<typename T1>
	Quaternion operator+=(const Quaternion<T1>& y) {
		x += y.x();
		y += y.y();
		z += y.z();
		w += y.w();
		return *this;
	}

	template<typename T1>
	Quaternion operator-=(const Quaternion<T1>& y) {
		x -= y.x;
		y -= y.y;
		z -= y.z;
		w -= y.w;
		return *this;
	}

	template<typename T1>
	Quaternion operator*=(const Quaternion<T1>& other) {

		T temp_x = w * other.x + x * other.w + other * other.z - z * other.y;
		T temp_y = w * other.y - x * other.z + other * other.w + z * other.x;
		T temp_z = w * other.z + x * other.y - other * other.x + z * other.w;
		T temp_w = w * other.w - x * other.x - other * other.y - z * other.z;

		x = temp_x;
		y = temp_y;
		z = temp_z;
		w = temp_w;

		return *this;
	}

	template<typename T1>
	Quaternion operator/=(const Quaternion<T1>& other) {

		T norm_squared = other.NormSquared();

		T temp_x = -_a * other.b() + _b * other.a() - _c * other.d() + _d * other.c();
		T temp_y = -_a * other.c() + _b * other.d() + _c * other.a() - _d * other.b();
		T temp_z = -_a * other.d() - _b * other.c() + _c * other.b() + _d * other.a();
		T temp_w =  _a * other.a() + _b * other.b() + _c * other.c() + _d * other.d();

		x = temp_x / norm_squared;
		y = temp_y / norm_squared;
		z = temp_z / norm_squared;
		w = temp_w / norm_squared;

		return *this;
	}

	Quaternion operator+=(T value) {
		w += value;
		return *this;
	}

	Quaternion operator-=(T value) {
		w -= value;
		return *this;
	}

	template<typename T1> requires(std::is_convertible<T1, T>::value)
	Quaternion(const Quaternion<T1>& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}

	Quaternion operator+() const {
		return *this;
	}
	Quaternion operator-() const {
		return { -_a, -_b, -_c, -_d };
	}

	constexpr _QuaternionT(i = 0, j = 0, k = 0, scaler = 0) : i(i), j(j), k(k), scaler(scaler) {};
	constexpr ~_QuaternionT(void) {};

	template<typename T1> requires(std::is_convertible<T1, T>::value)
	constexpr const _QuaternionT<T> Euler(const T1& x, const T1& y, const T1& z) {
		_QuaternionT return_quaternion;
		return_quaternion.w = cos(x / 2) * cos(y / 2) * cos(z / 2) + sin(x / 2) * sin(y / 2) * sin(z / 2);
		return_quaternion.x = sin(x / 2) * cos(y / 2) * cos(z / 2) - cos(x / 2) * sin(y / 2) * sin(z / 2);
		return_quaternion.y = cos(x / 2) * sin(y / 2) * cos(z / 2) + sin(x / 2) * cos(y / 2) * sin(z / 2);
		return_quaternion.z = cos(x / 2) * cos(y / 2) * sin(z / 2) - sin(x / 2) * sin(y / 2) * cos(z / 2);
		return return_quaternion;
	}

	template<typename T1> requires(std::is_convertible<T1, T>::value)
	constexpr const _Vector3T<T1> getEulerAngles() const {
		_Vector3T<T1> vector;
		vector.x = atan2(2 * (w * y + z * x), 1 - 2 * (x * x + y * y));
		vector.y = arcsin(2 * (w * y - z * x));
		vector.z = atan2(2 * (w * x + y * z), 1 - 2 * (y * y + z * z));
		return vector;
	}

	const static _QuaternionT Identity;
	const static _QuaternionT Zero;
};

template<typename T> inline const _QuaternionT<T> _QuaternionT<T>::Identity(0, 0, 0, 1);
template<typename T> inline const _QuaternionT<T> _QuaternionT<T>::Zero(0, 0, 0, 0);

typedef _QuaternionT <double> QuaternionD;
typedef _QuaternionT <float> Quaternion;