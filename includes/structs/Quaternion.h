#pragma once

#include "Vector.h"
#include "Vector3.h"
#include <array>
#include <type_traits>
#include <iostream>

#define T _Ty
#define N_DIMS 4

template<typename T>
struct _QUATERNION_MEM_STRUCT {
	union {
		struct { T scaler, i, j, k; };
		struct { T		w, x, y, z; };
		struct { T		a, b, c, d; };
		std::array<T, N_DIMS> data{ };
	};
};

#define _w (*this)[0]
#define _x (*this)[1]
#define _y (*this)[2]
#define _z (*this)[3]

#define other_w other[0]
#define other_x other[1]
#define other_y other[2]
#define other_z other[3]

#define BASE Vector::_Basic_Vector<T, N_DIMS, _QUATERNION_MEM_STRUCT<T>>
#define OTHER_BASE Vector::_Basic_Vector<T1, N_DIMS, _QUATERNION_MEM_STRUCT<T>>

template<typename T>
struct _QuaternionT : public BASE {

	using BASE::_Basic_Vector;

	constexpr _QuaternionT(BASE other) {
		for (size_t i = 0; i < N_DIMS; i++) {
			(*this)[i] = other[i];
		}
	}

	template<typename T1> requires(std::is_arithmetic<T1>::value)
		constexpr const _QuaternionT<T>& operator *= (const OTHER_BASE& other) {

		T norm_squared = other.SquaredMagnitude();

		T temp_w =  (_w) * (other_w) + (_x) * (other_x) + (_y) * (other_y) + (_z) * (other_z);
		T temp_x = -(_w) * (other_x) + (_x) * (other_w) - (_y) * (other_z) + (_z) * (other_y);
		T temp_y = -(_w) * (other_y) + (_x) * (other_z) + (_y) * (other_w) - (_z) * (other_x);
		T temp_z = -(_w) * (other_z) - (_x) * (other_y) + (_y) * (other_x) + (_z) * (other_w);

		_w = temp_w / norm_squared;
		_x = temp_x / norm_squared;
		_y = temp_y / norm_squared;
		_z = temp_z / norm_squared;

		return *this;
	}

	template<typename T1> requires(std::is_arithmetic<T1>::value)
		friend constexpr const _QuaternionT<T> operator * (const _QuaternionT<T>& lhs, const _QuaternionT<T1>& rhs) {

		BASE return_quat;

		T norm_squared = rhs.SquaredMagnitude();

		T temp_w =  (lhs.w) * (rhs.w) + (lhs.x) * (rhs.x) + (lhs.y) * (rhs.y) + (lhs.z) * (rhs.z);
		T temp_x = -(lhs.w) * (rhs.x) + (lhs.x) * (rhs.w) - (lhs.y) * (rhs.z) + (lhs.z) * (rhs.y);
		T temp_y = -(lhs.w) * (rhs.y) + (lhs.x) * (rhs.z) + (lhs.y) * (rhs.w) - (lhs.z) * (rhs.x);
		T temp_z = -(lhs.w) * (rhs.z) - (lhs.x) * (rhs.y) + (lhs.y) * (rhs.x) + (lhs.z) * (rhs.w);

		return _QuaternionT<T>{
			temp_w / norm_squared,
			temp_x / norm_squared,
			temp_y / norm_squared,
			temp_z / norm_squared
		};
	}

	template<typename T1> requires(std::is_arithmetic<T1>::value)
		constexpr const _QuaternionT<T>& operator /= (const OTHER_BASE& other) {

		T norm_squared = other.SquaredMagnitude();

		T temp_w =  (_w) * (other_w) + (_x) * (other_x) + (_y) * (other_y) + (_z) * (other_z);
		T temp_x = -(_w) * (other_x) + (_x) * (other_w) - (_y) * (other_z) + (_z) * (other_y);
		T temp_y = -(_w) * (other_y) + (_x) * (other_z) + (_y) * (other_w) - (_z) * (other_x);
		T temp_z = -(_w) * (other_z) - (_x) * (other_y) + (_y) * (other_x) + (_z) * (other_w);

		_w = temp_w / norm_squared;
		_x = temp_x / norm_squared;
		_y = temp_y / norm_squared;
		_z = temp_z / norm_squared;

		return *this;
	}

	template<typename T1> requires(std::is_arithmetic<T1>::value)
		friend constexpr const _QuaternionT<T> operator / (const _QuaternionT<T>& lhs, const _QuaternionT<T1>& rhs) {
		std::cout << lhs << rhs << std::endl;

		BASE return_quat;

		T norm_squared = rhs.SquaredMagnitude();

		T temp_w =  lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2] + lhs[3] * rhs[3];
		T temp_x = -lhs[0] * rhs[1] + lhs[1] * rhs[0] - lhs[2] * rhs[3] + lhs[3] * rhs[2];
		T temp_y = -lhs[0] * rhs[2] + lhs[1] * rhs[3] + lhs[2] * rhs[0] - lhs[3] * rhs[1];
		T temp_z = -lhs[0] * rhs[3] - lhs[1] * rhs[2] + lhs[2] * rhs[1] + lhs[3] * rhs[0];

		return _QuaternionT<T> {
			temp_w / norm_squared,
			temp_x / norm_squared,
			temp_y / norm_squared,
			temp_z / norm_squared
		};
	}

	template<typename T1> requires(std::is_convertible<T1, T>::value)
		constexpr const _QuaternionT<T> operator += (const T1& value) {
		_w += value;
		return *this;
	}
	template<typename T1> requires(std::is_convertible<T1, T>::value)
		constexpr const _QuaternionT<T> operator + (const T1& value) {
		return (*this) += value;
	}

	template<typename T1> requires(std::is_convertible<T1, T>::value)
		constexpr const _QuaternionT<T> operator -= (const T1& value) {
		_w -= value;
		return *this;
	}
	template<typename T1> requires(std::is_convertible<T1, T>::value)
		constexpr const _QuaternionT<T> operator - (const T1& value) {
		return (*this) -= value;
	}

	using BASE::SquaredMagnitude;
	using BASE::Magnitude;

	inline constexpr const T NormSquared() const {
		return (_w) * (_w) + (_x) * (_x) + (_y) * (_y) + (_z) * (_z);
	}

	inline constexpr const T Norm() const {
		return sqrt(NormSquared());
	}

	inline constexpr const T UnrealNormSquared() const {
		return (_x) * (_x) + (_y) * (_y) + (_z) * (_z);
	}

	inline constexpr const _QuaternionT<T> Conjugate() const {
		return _QuaternionT{ (_w), -(_x), -(_y), -(_z) };
	}

	inline constexpr const _QuaternionT<T> Inverse() {
		return Conjugate() / NormSquared();
	}

	template<typename T1> requires(std::is_convertible<T1, T>::value)
	static constexpr const _QuaternionT<T> Euler(const T1& x = 0, const T1& y = 0, const T1& z = 0) {
		T qw = cos(x / 2) * cos(y / 2) * cos(z / 2) + sin(x / 2) * sin(y / 2) * sin(z / 2);
		T qx = sin(x / 2) * cos(y / 2) * cos(z / 2) - cos(x / 2) * sin(y / 2) * sin(z / 2);
		T qy = cos(x / 2) * sin(y / 2) * cos(z / 2) + sin(x / 2) * cos(y / 2) * sin(z / 2);
		T qz = cos(x / 2) * cos(y / 2) * sin(z / 2) - sin(x / 2) * sin(y / 2) * cos(z / 2);

		return _QuaternionT{ qw, qx, qy, qz };
	}

	template<typename T1> requires(std::is_convertible<T1, T>::value)
	static inline constexpr const _QuaternionT Euler(const _Vector3T<T1>& euler_rotation) {
		return Euler(euler_rotation.x, euler_rotation.y, euler_rotation.z);
	}
	constexpr const _Vector3T<T> ToEuler() const {
		return _Vector3T<T> {
			atan2(2 * ((_w) * (_y)+(_z) * (_x)), 1 - (2 * ((_x) * (_x)+(_y) * (_y)))),
			std::asin (2 * ((_w) * (_y) - (_z) * (_x))), 
			atan2(2 * ((_w) * (_x)+(_y) * (_z)), 1 - (2 * ((_y) * (_y)+(_z) * (_z))))
		};
	}

	static const _QuaternionT Identity;
	static const _QuaternionT Zero;
};

template<typename T> inline const _QuaternionT<T> _QuaternionT<T>::Identity	(1, 0, 0, 0);
template<typename T> inline const _QuaternionT<T> _QuaternionT<T>::Zero		(0, 0, 0, 0);

typedef _QuaternionT <double> QuaternionD;
typedef _QuaternionT <float> Quaternion;

#undef BASE;
#undef T;

#undef _w
#undef _x
#undef _y
#undef _z
#undef other_w
#undef other_x
#undef other_y
#undef other_z