#ifndef MATHLIB_SIMD_HPP
#define MATHLIB_SIMD_HPP
#pragma once

#include <immintrin.h>

namespace math::simd
{
	// SIMD WIDTH is the amount of operations a processor can execute at the same time. 
#if defined(__AVX2__)
	#define MATHLIB_SIMD_WIDTH 8
	using VecFloat = __m256;
#elif defined(__SSE2__)
	#define MATHLIB_SIMD_WIDTH 4
	using VecFloat = __m128;
#else
	#define MATHLIB_SIMD_WIDTH 1
	using VecFloat = float;
#endif
}

#endif //MATHLIB_SIMD_HPP