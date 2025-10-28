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

		template<typename... Args, typename = std::enable_if_t<sizeof...(Args) == N>>
		Vec(Args... args) : values{ static_cast<T>(args)... } {}

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

		Vec<N, T> operator-() const
		{
			Vec<N, T> result;
			for (size_t i = 0; i < N; ++i)
			{
				result[i] = -values[i];
			}
			return result;
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

		bool operator==(const Vec<N, T>& other) const
		{
			for (size_t i = 0; i < N; ++i)
			{
				if (values[i] != other[i])
				{
					return false;
				}
			}
			return true;
		}

		bool operator!=(const Vec<N, T>& other) const
		{
			return !(*this == other);
		}

		bool NearlyEquals(const Vec<N, T>& other, T epsilon = static_cast<T>(EPSILON_f32)) const
		{
			for (size_t i = 0; i < N; ++i)
			{
				if (Absolute(values[i] - other[i]) >= epsilon)
				{
					return false;
				}
			}
			return true;
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
			T len = Length();
			assert(len > 0);

			Vec<N, T> result;
			for (size_t i = 0; i < N; ++i)
			{
				result[i] = values[i] / len;
			}

			return result;
		}
	private:
	};

	// UTILS TYPES FOR VECTORS

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
	constexpr Vec<N, T> Reflect(const Vec<N, T>& I, const Vec<N, T>& Norm)
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

	template<size_t N, typename T>
	constexpr Vec<N, T> Lerp(const Vec<N, T>& a, const Vec<N, T>& b, T t)
	{
		return a + (b - a) * t;
	}

	template<size_t N, typename T>
	constexpr Vec<N, T> Project(const Vec<N, T> a, const Vec<N, T>& b)
	{
		T dotProduct = Dot(a, b);
		T lengthSquared = b.LengthSquared();

		if (lengthSquared == 0) return Vec<N, T>();

		return b * (dotProduct / lengthSquared);
	}

	template<size_t N, typename T>
	T Angle(const Vec<N, T>& a, const Vec<N, T>& b)
	{
		T lenA = a.Length();
		T lenB = b.Length();

		if (lenA == 0 || lenB == 0) return 0;

		T cosAngle = Dot(a, b) / (lenA * lenB);
		cosAngle = Clamp(cosAngle, T(-1), T(1)); 

		return std::acos(cosAngle); 
	}

	template<size_t N, typename T>
	constexpr T DistanceSquared(const Vec<N, T>& a, const Vec<N, T>& b)
	{
		T sum = 0;
		for (size_t i = 0; i < N; ++i)
		{
			T diff = b[i] - a[i];
			sum += diff * diff;
		}
		return sum;
	}

	template<size_t N, typename T>
	constexpr Vec<N, T> Min(const Vec<N, T>& a, const Vec<N, T>& b)
	{
		Vec<N, T> result;
		for (size_t i = 0; i < N; ++i)
			result[i] = Min(a[i], b[i]);
		return result;
	}

	template<size_t N, typename T>
	constexpr Vec<N, T> Max(const Vec<N, T>& a, const Vec<N, T>& b)
	{
		Vec<N, T> result;
		for (size_t i = 0; i < N; ++i)
		{
			result[i] = Max(a[i], b[i]);
		}
		return result;
	}

	template<size_t N, typename T>
	constexpr Vec<N, T> Clamp(const Vec<N, T>& v, const Vec<N, T>& min, const Vec<N, T>& max)
	{
		Vec<N, T> result;
		for (size_t i = 0; i < N; ++i)
		{
			result[i] = Clamp(v[i], min[i], max[i]);
		}
		return result;
	}

	template<size_t N, typename T>
	constexpr Vec<N, T> Abs(const Vec<N, T>& v)
	{
		Vec<N, T> result;
		for (size_t i = 0; i < N; ++i)
		{
			result[i] = Absolute(v[i]);
		}
		return result;
	}

	inline constexpr Vec3 Vec3Right()	{ return Vec3(1, 0, 0);	}
	inline constexpr Vec3 Vec3Left()	{ return Vec3(-1, 0, 0);}
	inline constexpr Vec3 Vec3Up()		{ return Vec3(0, 1, 0); }
	inline constexpr Vec3 Vec3Down()	{ return Vec3(0, -1, 0);}
	inline constexpr Vec3 Vec3Forward() { return Vec3(0, 0, 1); }
	inline constexpr Vec3 Vec3Back()	{ return Vec3(0, 0, -1);}
}

#endif //MATH_VECTOR_HPP