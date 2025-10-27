#ifndef MATH_VECTOR_HPP
#define MATH_VECTOR_HPP

#include <math/common.hpp>

#include <array>
#include <assert.h>

namespace math
{

	template<size_t N, typename T>
	struct Vec
	{
	protected:
		std::array<T, N> values{};
	public:
		Vec() = default;

		Vec(std::initializer_list<T> list)
		{
			assert(list.size() == N);
			std::copy(list.begin(), list.end(), values.begin());
		}

		T operator[](size_t i) const { return values[i]; }
		T& operator[](size_t i) { return values[i]; }

		// OVERLOADED OPERATORS

		Vec<N, T> operator+(const Vec<N, T>& other) const
		{
			Vec<N, T> result;
			for (int32 i = 0; i < N; ++i)
			{
				result[i] = values[i] + other[i];
			}
			return result;
		}

		Vec<N, T> operator+=(const Vec<N, T>& other)
		{
			for (int32 i = 0; i < N; ++i)
			{
				values[i] += other[i];
			}
			return *this;
		}

		Vec<N, T> operator-(const Vec<N, T>& other) const
		{
			Vec<N, T> result;
			for (int32 i = 0; i < N; ++i)
			{
				result[i] = values[i] - other[i];
			}
			return result;
		}

		Vec<N, T> operator-=(const Vec<N, T>& other)
		{
			for (int32 i = 0; i < N; ++i)
			{
				values[i] -= other[i];
			}
			return *this;
		}

		Vec<N, T> operator*(const Vec<N, T>& other) const
		{
			Vec<N, T> result;
			for (int32 i = 0; i < N; ++i)
			{
				result[i] = values[i] * other[i];
			}
			return result;
		}

		Vec<N, T> operator*=(const Vec<N, T>& other)
		{
			for (int32 i = 0; i < N; ++i)
			{
				values[i] *= other[i];
			}
			return *this;
		}

		Vec<N, T> operator*(T scalar) const
		{
			Vec<N, T> result;
			for (size_t i = 0; i < N; ++i)
			{
				result[i] = values[i] * scalar;
			}
			return result;
		}

		friend Vec<N, T> operator*(T scalar, const Vec<N, T>& vec)
		{
			return vec * scalar;
		}

		Vec<N, T> operator/(const Vec<N, T>& other) const
		{
			Vec<N, T> result;
			for (int32 i = 0; i < N; ++i)
			{
				result[i] = values[i] / other[i];
			}
			return result;
		}

		Vec<N, T> operator/=(const Vec<N, T>& other)
		{
			for (int32 i = 0; i < N; ++i)
			{
				values[i] /= other[i];
			}
			return *this;
		}

		T Length() const
		{
			T sum = 0;
			for (size_t i = 0; i < N; ++i)
			{
				sum += values[i] * values[i];
			}
			return std::sqrt(sum);
		}

		T LengthSquared() const
		{
			T sum = 0;
			for (size_t i = 0; i < N; ++i)
			{
				sum += values[i] * values[i];
			}
			return sum;
		}

		Vec<N, T> Normalize() const
		{
			Vec<N, T> result;
			T len = Length();
			if (len == 0) return result;

			for (size_t i = 0; i < N; ++i)
			{
				result[i] = values[i] / len;
			}

			return result;
		}
	private:
	};

	// UTILS FOR VECTORS

	using Vec2 = Vec<2, float32>;
	using Vec3 = Vec<3, float32>;
	using Vec4 = Vec<4, float32>;

	// VECTORS RELATED FUNCTIONS

	template<size_t N, typename T>
	constexpr T Dot(const math::Vec<N, T> a, const math::Vec<N, T> b)
	{
		T sum = 0;
		for (size_t i = 0; i < N; ++i)
		{
			sum += a[i] * b[i];
		}
		return sum;
	}

	template<typename T>
	constexpr math::Vec<3, T> Cross(const math::Vec<3, T>& a, const math::Vec<3, T>& b)
	{
		math::Vec<3, T> result;

		result[0] = a[1] * b[2] - a[2] * b[1];
		result[1] = a[2] * b[0] - a[0] * b[2];
		result[2] = a[0] * b[1] - a[1] * b[0];

		return result;
	}

	template<size_t N, typename T>
	T Distance(const math::Vec<N, T>& a, const math::Vec<N, T>& b)
	{
		T sum = 0;
		for (size_t i = 0; i < N; ++i)
		{
			sum += (b[i] - a[i]) * (b[i] - a[i]);
		}
		return std::sqrt(sum);
	}

	template<size_t N, typename T>
	Vec<N, T> Reflect(const Vec<N, T>& I, const Vec<N, T>& Norm)
	{
		T dotIN = Dot(I, Norm);
		Vec<N, T> scaledN = Norm * (2 * dotIN);
		return I - scaledN;
	}

	template<size_t N, typename T>
	Vec<N, T> Refract(const Vec<N, T>& I, const Vec<N, T>& Norm, T Eta_In, T Eta_Out)
	{
		Vec<N, T> N_unit = Norm;           
		Vec<N, T> I_unit = I;              

		T eta = Eta_In / Eta_Out;
		T cosi = -Dot(N_unit, I_unit);     

		T k = 1 - eta * eta * (1 - cosi * cosi);

		Vec<N, T> result;

		if (k < 0)
		{
			result = Reflect(I_unit, N_unit);
		}
		else
		{
			T cos2 = std::sqrt(k);
			result = eta * I_unit + (eta * cosi - cos2) * N_unit;
		}

		return result;
	}
}



#endif //MATH_VECTOR_HPP