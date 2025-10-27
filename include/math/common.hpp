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
	constexpr T Min(T min, T max)
	{
		return (min < max) ? min : max;
	}

	template<std::totally_ordered T>
	constexpr T Max(T min, T max)
	{
		return (min > max) ? min : max;
	}
}

#endif //MATHLIB_COMMON_HPP