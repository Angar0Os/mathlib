#ifndef MATHLIB_MATRIX_HPP
#define MATHLIB_MATRIX_HPP

#include <math/vector.hpp>

namespace math
{
	template<size_t R, size_t C, typename T>
	struct Matrix
	{
	protected:
		std::array<T, R * C> values{};
	public:
		Matrix() = default;

		Matrix(std::initializer_list<T> list)
		{
			assert(list.size() == R * C);
			std::copy(list.begin(), list.end(), values.begin());
		}

		T operator()(size_t row, size_t col) const
		{
			return values[col * R + row];
		}

		T& operator()(size_t row, size_t col)
		{
			return values[col * R + row];
		}
	};

	// UTILS TYPES FOR MATRIX 

	using Mat2 = Matrix<2, 2, float32>;
	using Mat3 = Matrix<3, 3, float32>;
	using Mat4 = Matrix<4, 4, float32>;

	using Mat2x3 = Matrix<2, 3, float32>; 
	using Mat3x2 = Matrix<3, 2, float32>; 
	using Mat2x4 = Matrix<2, 4, float32>;
	using Mat4x2 = Matrix<4, 2, float32>;
	using Mat3x4 = Matrix<3, 4, float32>;
	using Mat4x3 = Matrix<4, 3, float32>;
}

#endif //MATHLIB_MATRIX_HPP