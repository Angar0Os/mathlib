#ifndef MATHLIB_VECTOR
#define MATHLIB_VECTOR
#pragma once

#include <array>
#include <initializer_list>

template <typename T, std::size_t N>
class Vector
{
protected:
	std::array<T, N> values{};

public:
	Vector() = default;

	Vector(std::initializer_list<T> list)
	{
		std::copy(list.begin(), list.end(), values.begin());
	}

	T operator[](size_t i) const { return values[i]; }

	T& operator[](size_t i) { return values[i]; }
};

#endif //MATHLIB_VECTOR
