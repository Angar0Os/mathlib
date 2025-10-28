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

		Matrix(std::initializer_list<T> list, bool rowMajor = true)
		{
			assert(list.size() == R * C);

			if (rowMajor) 
			{
				
				size_t index = 0;
				for (size_t i = 0; i < R; ++i) 
				{       
					for (size_t j = 0; j < C; ++j) 
					{   
						values[j * R + i] = *(list.begin() + index);
						++index;
					}
				}
			}
			else 
			{
				std::copy(list.begin(), list.end(), values.begin());
			}
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

		Vec<R, T> operator*(const Vec<C, T>& other) const
		{
			Vec<R, T> result{};

			for (size_t i = 0; i < R; ++i)
			{
				T sum = static_cast<T>(0);
				for (size_t j = 0; j < C; ++j)
				{
					sum += (*this)(i, j) * other[j];
				}
				result[i] = sum;
			}

			return result;
		}

		Matrix<R, C, T> operator*(T scalar) const
		{
			Matrix<R, C, T> result;

			for (size_t i = 0; i < R * C; ++i)
			{
				result.values[i] = values[i] * scalar;
			}

			return result;
		}

		Matrix<R, C, T> operator-(T scalar) const
		{
			Matrix<R, C, T> result;

			for (size_t i = 0; i < R * C; ++i)
			{
				result.values[i] = values[i] - scalar;
			}

			return result;
		}

		Matrix<R, C, T> operator+(T scalar) const
		{
			Matrix<R, C, T> result;

			for (size_t i = 0; i < R * C; ++i)
			{
				result.values[i] = values[i] + scalar;
			}

			return result;
		}

		template<typename M>
		friend constexpr M Zero();

		template<typename M>
		friend constexpr M Identity();

		template<typename M>
		friend constexpr M Transpose(const M& matrix);

		friend Matrix<R, C, T> operator*(T scalar, const Matrix<R, C, T>& mat)
		{
			return mat * scalar;
		}

		friend Matrix<R, C, T> operator+(T scalar, const Matrix<R, C, T>& mat)
		{
			return mat + scalar;
		}

		friend Matrix<R, C, T> operator-(T scalar, const Matrix<R, C, T>& mat)
		{
			Matrix<R, C, T> result;

			for (size_t i = 0; i < R * C; ++i)
			{
				result.values[i] = scalar - mat.values[i];
			}

			return result;
		}
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
		{
			v = static_cast<typename M::value_type>(0);
		}
		return result;
	}

	template<typename M>
	constexpr M Identity()
	{
		M result = Zero<M>();

		if (M::rows != M::cols)
		{
			return result;
		}

		for (size_t i = 0; i < M::rows; ++i)
		{
			result(i, i) = static_cast<typename M::value_type>(1);

		}
		return result;
	}

	template<typename M>
	constexpr M Transpose(const M& matrix)
	{
		Matrix<M::cols, M::rows, typename M::value_type> result = Zero<Matrix<M::cols, M::rows, typename M::value_type>>();

		for (size_t i = 0; i < M::rows; ++i)
		{
			for (size_t j = 0; j < M::cols; ++j)
			{
				result(j, i) = matrix(i, j);
			}
		}
		
		return result;
	}

	template<typename M>
	constexpr typename M::value_type Determinant(const M& matrix)
	{
		static_assert(M::rows == M::cols, "Matrix must be square");

		if constexpr (M::rows == 1)
		{
			return matrix(0, 0);
		}
		else if constexpr (M::rows == 2)
		{
			return matrix(0, 0) * matrix(1, 1) - matrix(0, 1) * matrix(1, 0);
		}
		else
		{
			typename M::value_type det = 0;
			for (size_t col = 0; col < M::cols; ++col)
			{
				auto minor = Minor(matrix, 0, col);
				auto sign = (col % 2 == 0) ? 1 : -1;
				det += sign * matrix(0, col) * Determinant(minor);
			}
			return det;
		}
	}

	template<typename M>
	constexpr auto Minor(const M& matrix, size_t rowToRemove, size_t colToRemove)
	{
		Matrix<M::rows - 1, M::cols - 1, typename M::value_type> result;

		size_t r = 0;
		for (size_t i = 0; i < M::rows; ++i)
		{
			if (i == rowToRemove) continue;

			size_t c = 0;
			for (size_t j = 0; j < M::cols; ++j)
			{
				if (j == colToRemove) continue;
				result(r, c) = matrix(i, j);
				++c;
			}
			++r;
		}

		return result;
	}

	template<typename M>
	constexpr auto Inverse(const M& matrix)
	{
		static_assert(M::rows == M::cols);

		using T = typename M::value_type;
		const size_t N = M::rows;

		T det = Determinant(matrix);
		assert(det != static_cast<T>(0));

		Matrix<N, N, T> cofactorMat;

		for (size_t i = 0; i < N; ++i)
		{
			for (size_t j = 0; j < N; ++j)
			{
				auto minor = Minor(matrix, i, j);
				T cofactor = Determinant(minor);
				if ((i + j) % 2 == 1) cofactor = -cofactor;
				cofactorMat(j, i) = cofactor;
			}
		}

		return cofactorMat * (static_cast<T>(1) / det);
	}
}

#endif // MATHLIB_MATRIX_HPP
