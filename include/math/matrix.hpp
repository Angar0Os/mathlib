#ifndef MATHLIB_MATRIX_HPP
#define MATHLIB_MATRIX_HPP

#include <math/vector.hpp>

namespace math
{
	template<size_t R, size_t C, typename T>
	struct Matrix
	{
	protected:
		std::array<T, R* C> values{};

	public:
		using value_type = T;
		static constexpr size_t rows = R;
		static constexpr size_t cols = C;

		Matrix() = default;

		Matrix(std::initializer_list<T> list)
		{
			assert(list.size() == R * C);
			std::copy(list.begin(), list.end(), values.begin());
		}

		Matrix(std::initializer_list<Vec<R, T>> columns)
		{
			assert(columns.size() == C);

			size_t colIndex = 0;
			for (auto it = columns.begin(); it != columns.end(); ++it)
			{
				const Vec<R, T>& col = *it;
				for (size_t row = 0; row < R; ++row)
					values[colIndex * R + row] = col[row];
				++colIndex;
			}
		}

		T operator()(size_t row, size_t col) const
		{
			return values[col * R + row];
		}

		T& operator()(size_t row, size_t col)
		{
			return values[col * R + row];
		}

		template<size_t C2>
		Matrix<R, C2, T> operator*(const Matrix<C, C2, T>& other) const
		{
			Matrix<R, C2, T> result = Zero<Matrix<R, C2, T>>();

			for (size_t i = 0; i < R; ++i)
			{
				for (size_t j = 0; j < C2; ++j)
				{
					for (size_t k = 0; k < C; ++k)
					{
						result(i, j) += (*this)(i, k) * other(k, j);
					}
				}
			}

			return result;
		}

		template<typename M>
		friend constexpr M Zero();

		template<typename M>
		friend constexpr M Identity();
	};

	// UTILS TYPES 

	using Mat2 = Matrix<2, 2, float32>;
	using Mat3 = Matrix<3, 3, float32>;
	using Mat4 = Matrix<4, 4, float32>;

	using Mat2x3 = Matrix<2, 3, float32>;
	using Mat3x2 = Matrix<3, 2, float32>;
	using Mat2x4 = Matrix<2, 4, float32>;
	using Mat4x2 = Matrix<4, 2, float32>;
	using Mat3x4 = Matrix<3, 4, float32>;
	using Mat4x3 = Matrix<4, 3, float32>;

	// MATRIX RELATED FUNCTIONS

	template<typename M>
	constexpr M Zero()
	{
		M result;
		for (auto& v : result.values)
			v = static_cast<typename M::value_type>(0);
		return result;
	}

	template<typename M>
	constexpr M Identity()
	{
		M result = Zero<M>();

		if (M::rows != M::cols)
			return result;

		for (size_t i = 0; i < M::rows; ++i)
			result(i, i) = static_cast<typename M::value_type>(1);

		return result;
	}
}

#endif // MATHLIB_MATRIX_HPP
