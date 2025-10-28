#ifndef MATHLIB_QUATERNION_HPP
#define MATHLIB_QUATERNION_HPP
#pragma once 

#include <math/matrix.hpp>

namespace math
{
	struct Quaternion
	{
		float32 x, y, z, w;

		Quaternion() : x(0), y(0), z(0), w(1) {}
		Quaternion(float32 x, float32 y, float32 z, float32 w) : x(x), y(y), z(z), w(w) {}

		static Quaternion FromAxisAngle(const Vec3& axis, float32 angle)
		{
			Vec3 a = axis.Normalize();
			float32 halfAngle = angle * 0.5f;
			float32 s = std::sin(halfAngle);
			float32 c = std::cos(halfAngle);

			return Quaternion(a[0] * s, a[1] * s, a[2] * s, c);
		}

		static Quaternion FromEuler(float32 pitch, float32 yaw, float32 roll)
		{
			float32 cy = std::cos(yaw * 0.5f);
			float32 sy = std::sin(yaw * 0.5f);
			float32 cp = std::cos(pitch * 0.5f);
			float32 sp = std::sin(pitch * 0.5f);
			float32 cr = std::cos(roll * 0.5f);
			float32 sr = std::sin(roll * 0.5f);

			Quaternion q;
			q.w = cr * cp * cy + sr * sp * sy;
			q.x = sr * cp * cy - cr * sp * sy;
			q.y = cr * sp * cy + sr * cp * sy;
			q.z = cr * cp * sy - sr * sp * cy;

			return q;
		}

		static Quaternion FromRotationMatrix(const Mat3& m)
		{
			Quaternion q;
			float32 trace = m(0, 0) + m(1, 1) + m(2, 2);

			if (trace > 0.0f)
			{
				float32 s = std::sqrt(trace + 1.0f) * 2.0f;
				q.w = 0.25f * s;
				q.x = (m(2, 1) - m(1, 2)) / s;
				q.y = (m(0, 2) - m(2, 0)) / s;
				q.z = (m(1, 0) - m(0, 1)) / s;
			}
			else if ((m(0, 0) > m(1, 1)) && (m(0, 0) > m(2, 2)))
			{
				float32 s = std::sqrt(1.0f + m(0, 0) - m(1, 1) - m(2, 2)) * 2.0f;
				q.w = (m(2, 1) - m(1, 2)) / s;
				q.x = 0.25f * s;
				q.y = (m(0, 1) + m(1, 0)) / s;
				q.z = (m(0, 2) + m(2, 0)) / s;
			}
			else if (m(1, 1) > m(2, 2))
			{
				float32 s = std::sqrt(1.0f + m(1, 1) - m(0, 0) - m(2, 2)) * 2.0f;
				q.w = (m(0, 2) - m(2, 0)) / s;
				q.x = (m(0, 1) + m(1, 0)) / s;
				q.y = 0.25f * s;
				q.z = (m(1, 2) + m(2, 1)) / s;
			}
			else
			{
				float32 s = std::sqrt(1.0f + m(2, 2) - m(0, 0) - m(1, 1)) * 2.0f;
				q.w = (m(1, 0) - m(0, 1)) / s;
				q.x = (m(0, 2) + m(2, 0)) / s;
				q.y = (m(1, 2) + m(2, 1)) / s;
				q.z = 0.25f * s;
			}

			return q;
		}

		static Quaternion FromRotationMatrix(const Mat4& m)
		{
			Mat3 m3 = Zero<Mat3>();
			for (size_t i = 0; i < 3; ++i)
			{
				for (size_t j = 0; j < 3; ++j)
				{
					m3(i, j) = m(i, j);
				}
			}
			return FromRotationMatrix(m3);
		}

		Quaternion operator*(const Quaternion& other) const
		{
			return Quaternion(
				w * other.x + x * other.w + y * other.z - z * other.y,
				w * other.y - x * other.z + y * other.w + z * other.x,
				w * other.z + x * other.y - y * other.x + z * other.w,
				w * other.w - x * other.x - y * other.y - z * other.z
			);
		}

		Vec3 operator*(const Vec3& v) const
		{
			Vec3 qv(x, y, z);
			Vec3 t = Cross(qv, v) * 2.0f;
			return v + t * w + Cross(qv, t);
		}

		Quaternion operator+(const Quaternion& other) const
		{
			return Quaternion(x + other.x, y + other.y, z + other.z, w + other.w);
		}

		Quaternion operator*(float32 scalar) const
		{
			return Quaternion(x * scalar, y * scalar, z * scalar, w * scalar);
		}

		friend Quaternion operator*(float32 scalar, const Quaternion& q)
		{
			return q * scalar;
		}

		Quaternion Conjugate() const
		{
			return Quaternion(-x, -y, -z, w);
		}

		Quaternion Inverse() const
		{
			float32 lenSq = LengthSquared();
			assert(lenSq > 0);
			Quaternion conj = Conjugate();
			return conj * (1.0f / lenSq);
		}

		float32 Length() const
		{
			return std::sqrt(x * x + y * y + z * z + w * w);
		}

		float32 LengthSquared() const
		{
			return x * x + y * y + z * z + w * w;
		}

		Quaternion Normalize() const
		{
			float32 len = Length();
			assert(len > 0);
			return (*this) * (1.0f / len);
		}

		Mat3 ToMatrix3() const
		{
			Mat3 result = Identity<Mat3>();

			float32 xx = x * x, yy = y * y, zz = z * z;
			float32 xy = x * y, xz = x * z, yz = y * z;
			float32 wx = w * x, wy = w * y, wz = w * z;

			result(0, 0) = 1.0f - 2.0f * (yy + zz);
			result(0, 1) = 2.0f * (xy - wz);
			result(0, 2) = 2.0f * (xz + wy);

			result(1, 0) = 2.0f * (xy + wz);
			result(1, 1) = 1.0f - 2.0f * (xx + zz);
			result(1, 2) = 2.0f * (yz - wx);

			result(2, 0) = 2.0f * (xz - wy);
			result(2, 1) = 2.0f * (yz + wx);
			result(2, 2) = 1.0f - 2.0f * (xx + yy);

			return result;
		}

		Mat4 ToMatrix4() const
		{
			Mat4 result = Identity<Mat4>();
			Mat3 rot = ToMatrix3();

			for (size_t i = 0; i < 3; ++i)
			{
				for (size_t j = 0; j < 3; ++j)
				{
					result(i, j) = rot(i, j);
				}
			}

			return result;
		}

		Vec3 ToEuler() const
		{
			Vec3 angles;

			float32 sinp = 2.0f * (w * x - z * y);
			if (Absolute(sinp) >= 1.0f)
			{
				angles[0] = std::copysign(PI_f32 / 2.0f, sinp);
			}
			else
			{
				angles[0] = std::asin(sinp);
			}

			float32 siny_cosp = 2.0f * (w * y + z * x);
			float32 cosy_cosp = 1.0f - 2.0f * (x * x + y * y);
			angles[1] = std::atan2(siny_cosp, cosy_cosp);

			float32 sinr_cosp = 2.0f * (w * z + x * y);
			float32 cosr_cosp = 1.0f - 2.0f * (z * z + x * x);
			angles[2] = std::atan2(sinr_cosp, cosr_cosp);

			return angles;
		}

		bool operator==(const Quaternion& other) const
		{
			return x == other.x && y == other.y && z == other.z && w == other.w;
		}

		bool NearlyEquals(const Quaternion& other, float32 epsilon = EPSILON_f32) const
		{
			return Absolute(x - other.x) < epsilon &&
				Absolute(y - other.y) < epsilon &&
				Absolute(z - other.z) < epsilon &&
				Absolute(w - other.w) < epsilon;
		}
	};

	inline float32 Dot(const Quaternion& a, const Quaternion& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	inline Quaternion Nlerp(const Quaternion& a, const Quaternion& b, float32 t)
	{
		Quaternion q0 = a;
		Quaternion q1 = b;

		float32 dot = Dot(q0, q1);

		if (dot < 0.0f)
		{
			q1 = q1 * -1.0f;
		}

		Quaternion result = q0 * (1.0f - t) + q1 * t;
		return result.Normalize();
	}

	inline Quaternion Slerp(const Quaternion& a, const Quaternion& b, float32 t)
	{
		Quaternion q0 = a.Normalize();
		Quaternion q1 = b.Normalize();

		float32 dot = Dot(q0, q1);

		if (dot < 0.0f)
		{
			q1 = q1 * -1.0f;
			dot = -dot;
		}

		if (dot > 0.9995f)
		{
			return Nlerp(q0, q1, t);
		}

		float32 theta = std::acos(dot);
		float32 sinTheta = std::sin(theta);

		float32 w0 = std::sin((1.0f - t) * theta) / sinTheta;
		float32 w1 = std::sin(t * theta) / sinTheta;

		return q0 * w0 + q1 * w1;
	}

	inline Quaternion RotationBetween(const Vec3& from, const Vec3& to)
	{
		Vec3 f = from.Normalize();
		Vec3 t = to.Normalize();

		float32 dot = Dot(f, t);

		if (dot >= 1.0f - EPSILON_f32)
		{
			return Quaternion(0, 0, 0, 1);
		}

		if (dot <= -1.0f + EPSILON_f32)
		{
			Vec3 axis = Cross(Vec3(1, 0, 0), f);
			if (axis.LengthSquared() < EPSILON_f32)
				axis = Cross(Vec3(0, 1, 0), f);
			axis = axis.Normalize();
			return Quaternion::FromAxisAngle(axis, PI_f32);
		}

		Vec3 axis = Cross(f, t);
		float32 s = std::sqrt((1.0f + dot) * 2.0f);
		float32 invS = 1.0f / s;

		return Quaternion(
			axis[0] * invS,
			axis[1] * invS,
			axis[2] * invS,
			s * 0.5f
		).Normalize();
	}

	inline Quaternion LookRotation(const Vec3& forward, const Vec3& up = Vec3(0, 1, 0))
	{
		Vec3 f = forward.Normalize();
		Vec3 r = Cross(up, f).Normalize();
		Vec3 u = Cross(f, r);

		Mat3 rotMat = Identity<Mat3>();
		rotMat(0, 0) = r[0]; rotMat(0, 1) = u[0]; rotMat(0, 2) = f[0];
		rotMat(1, 0) = r[1]; rotMat(1, 1) = u[1]; rotMat(1, 2) = f[1];
		rotMat(2, 0) = r[2]; rotMat(2, 1) = u[2]; rotMat(2, 2) = f[2];

		return Quaternion::FromRotationMatrix(rotMat);
	}

	inline float32 AngleBetween(const Quaternion& a, const Quaternion& b)
	{
		float32 dot = Dot(a.Normalize(), b.Normalize());
		dot = Clamp(dot, -1.0f, 1.0f);
		return std::acos(Absolute(dot)) * 2.0f;
	}
}

#endif // MATHLIB_QUATERNION_HPP