#ifndef MATHLIB_COMMON_HPP
#define MATHLIB_COMMON_HPP
#pragma once

#include <cmath>
#include <cstdint>
#include <cstddef>
#include <limits>
#include <type_traits>

namespace math
{
	// TYPES

	using uint		= unsigned int;
	using uint32	= uint32_t;
	using uint64	= uint64_t;

	using float32	= float;
	using float64	= double;

	using int32		= int32_t;
	using int64		= int64_t;

	// CONST 
	
	constexpr float32 PI_f32		= 3.1415927f;
	constexpr float64 PI_f64		= 3.1415926535897932;
	constexpr float32 EPSILON_f32	= 1e-6f;
	constexpr float64 EPSILON_f64	= 1e-12;
	constexpr float32 TAU_f32		= 2.0f * PI_f32;
	constexpr float64 TAU_f64		= 2.0 * PI_f64;

	// UTIL FUNCTIONS

	template<std::floating_point T>
	constexpr T DegToRad(T angle)
	{
		return angle * static_cast<T>(PI_f64) / static_cast<T>(180);
	}

	template<std::floating_point T>
	constexpr T RadToDeg(T angle)
	{
		return angle * static_cast<T>(180) / static_cast<T>(PI_f64);
	}

	template<std::floating_point T>
	constexpr T Absolute(T value)
	{
		return (value >= 0) ? value : -value;
	}

	template<std::floating_point T>
	constexpr bool NearlyEquals(T a, T b, T eps = static_cast<T>(EPSILON_f64))
	{
		return Absolute(a - b) < eps;
	}

	template<std::floating_point T>
	constexpr T Clamp(T x, T min, T max)
	{
		return (x < min) ? min : (x > max ? max : x);
	}

	template<std::totally_ordered T>
	constexpr T Min(T a, T b)
	{
		return (a < b) ? a : b;
	}

	template<std::totally_ordered T>
	constexpr T Max(T a, T b)
	{
		return (a > b) ? a : b;
	}

	template<typename T>
	constexpr T Lerp(T a, T b, T t)
	{
		return a + t * (b - a);
	}

	template<typename T>
	constexpr T Smoothstep(T edge0, T edge1, T x)
	{
		T t = Clamp((x - edge0) / (edge1 - edge0), T(0), T(1));
		return t * t * (3 - 2 * t);
	}

	template<typename T>
	constexpr T Sign(T value)
	{
		return (value > T(0)) ? T(1) : (value < T(0)) ? T(-1) : T(0);
	}
	
	template<typename T>
	constexpr T Saturate(T x)
	{
		return Clamp(x, T(0), T(1));
	}

	template<typename T>
	constexpr T Pow(T base, int32 exponent)
	{
		if (exponent == 0) return T(1);
		if (exponent < 0) return T(1) / Pow(base, -exponent);

		T result = base;	
		for (int32 i = 1; i < exponent; ++i)
		{
			result *= base;
		}

		return result;
	}
}

#endif //MATHLIB_COMMON_HPP