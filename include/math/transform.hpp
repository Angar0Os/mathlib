#ifndef MATHLIB_TRANSFORM_HPP
#define MATHLIB_TRANSFORM_HPP
#pragma once

#include <math/matrix.hpp>

namespace math
{
	// TRANSFORM MATRIX

	inline Mat4 Translate(const Vec3& t)
	{
		Mat4 result = Identity<Mat4>();
		result(0, 3) = t[0];
		result(1, 3) = t[1];
		result(2, 3) = t[2];
		return result;
	}

	inline Mat4 Scale(const Vec3& s)
	{
		Mat4 result = Identity<Mat4>();
		result(0, 0) = s[0];
		result(1, 1) = s[1];
		result(2, 2) = s[2];
		return result;
	}

	inline Mat4 RotateX(float32 angle)
	{
		Mat4 result = Identity<Mat4>();
		float32 c = std::cos(angle);
		float32 s = std::sin(angle);

		result(1, 1) = c;
		result(1, 2) = -s;
		result(2, 1) = s;
		result(2, 2) = c;

		return result;
	}

	inline Mat4 RotateY(float32 angle)
	{
		Mat4 result = Identity<Mat4>();
		float32 c = std::cos(angle);
		float32 s = std::sin(angle);

		result(0, 0) = c;
		result(0, 2) = s;
		result(2, 0) = -s;
		result(2, 2) = c;

		return result;
	}

	inline Mat4 RotateZ(float32 angle)
	{
		Mat4 result = Identity<Mat4>();
		float32 c = std::cos(angle);
		float32 s = std::sin(angle);

		result(0, 0) = c;
		result(0, 1) = -s;
		result(1, 0) = s;
		result(1, 1) = c;

		return result;
	}

	inline Mat4 Rotate(float32 pitch, float32 yaw, float32 roll)
	{
		return RotateZ(roll) * RotateY(yaw) * RotateX(pitch);
	}

	// CAMERA MATRIX

	inline Mat4 LookAt(const Vec3& eye, const Vec3& target, const Vec3& up)
	{
		Vec3 forward = (target - eye).Normalize();
		Vec3 right = Cross(up.Normalize(), forward).Normalize();
		Vec3 trueUp = Cross(right, forward);

		Mat4 result = Identity<Mat4>();

		result(0, 0) = right[0];
		result(1, 0) = right[1];
		result(2, 0) = right[2];

		result(0, 1) = trueUp[0];
		result(1, 1) = trueUp[1];
		result(2, 1) = trueUp[2];

		result(0, 2) = -forward[0];
		result(1, 2) = -forward[1];
		result(2, 2) = -forward[2];

		result(0, 3) = -Dot(right, eye);
		result(1, 3) = -Dot(trueUp, eye);
		result(2, 3) = Dot(forward, eye);

		return result;
	}

	// PROJECTION MATRIX

	inline Mat4 Perspective(float32 fovRadians, float32 aspect, float32 nearZ, float32 farZ)
	{
		assert(aspect != 0);
		assert(farZ != nearZ);

		float32 f = 1.0f / std::tan(fovRadians / 2.0f);

		Mat4 result = Zero<Mat4>();
		result(0, 0) = f / aspect;
		result(1, 1) = f;
		result(2, 2) = (farZ + nearZ) / (nearZ - farZ);
		result(2, 3) = (2.0f * farZ * nearZ) / (nearZ - farZ);
		result(3, 2) = -1.0f;

		return result;
	}

	inline Mat4 Ortho(float32 left, float32 right, float32 bottom, float32 top, float32 nearZ, float32 farZ)
	{
		Mat4 result = Identity<Mat4>();

		result(0, 0) = 2.0f / (right - left);
		result(1, 1) = 2.0f / (top - bottom);
		result(2, 2) = -2.0f / (farZ - nearZ);

		result(0, 3) = -(right + left) / (right - left);
		result(1, 3) = -(top + bottom) / (top - bottom);
		result(2, 3) = -(farZ + nearZ) / (farZ - nearZ);

		return result;
	}

	inline Mat4 TransformMatrix(const Vec3& position, const Vec3& rotationEuler, const Vec3& scale)
	{
		Mat4 T = Translate(position);
		Mat4 R = Rotate(rotationEuler[0], rotationEuler[1], rotationEuler[2]);
		Mat4 S = Scale(scale);
		return T * R * S;
	}

	inline Mat4 InverseLookAt(const Vec3& eye, const Vec3& target, const Vec3& up)
	{
		Vec3 forward = (target - eye).Normalize();
		Vec3 right = Cross(up.Normalize(), forward).Normalize();
		Vec3 trueUp = Cross(forward, right);

		Mat4 result = Identity<Mat4>();

		result(0, 0) = right[0];
		result(1, 0) = right[1];
		result(2, 0) = right[2];

		result(0, 1) = trueUp[0];
		result(1, 1) = trueUp[1];
		result(2, 1) = trueUp[2];

		result(0, 2) = forward[0];
		result(1, 2) = forward[1];
		result(2, 2) = forward[2];

		result(0, 3) = eye[0];
		result(1, 3) = eye[1];
		result(2, 3) = eye[2];

		return result;
	}

	inline void DecomposeTransform(const Mat4& m, Vec3& position, Vec3& rotationEuler, Vec3& scale)
	{
		position = { m(0, 3), m(1, 3), m(2, 3) };

		scale[0] = Vec3(m(0, 0), m(1, 0), m(2, 0)).Length();
		scale[1] = Vec3(m(0, 1), m(1, 1), m(2, 1)).Length();
		scale[2] = Vec3(m(0, 2), m(1, 2), m(2, 2)).Length();

		Mat4 rot = m;
		rot(0, 0) /= scale[0]; rot(1, 0) /= scale[0]; rot(2, 0) /= scale[0];
		rot(0, 1) /= scale[1]; rot(1, 1) /= scale[1]; rot(2, 1) /= scale[1];
		rot(0, 2) /= scale[2]; rot(1, 2) /= scale[2]; rot(2, 2) /= scale[2];

		rotationEuler[1] = std::asin(-rot(0, 2));
		if (std::cos(rotationEuler[1]) != 0.0f)
		{
			rotationEuler[0] = std::atan2(rot(1, 2), rot(2, 2));
			rotationEuler[2] = std::atan2(rot(0, 1), rot(0, 0));
		}
		else
		{
			rotationEuler[0] = 0;
			rotationEuler[2] = std::atan2(-rot(1, 0), rot(1, 1));
		}
	}

	inline Mat4 RotateAxis(const Vec3& axis, float32 angle)
	{
		Vec3 a = axis.Normalize();
		float32 c = std::cos(angle);
		float32 s = std::sin(angle);
		float32 t = 1.0f - c;

		Mat4 result = Identity<Mat4>();

		result(0, 0) = t * a[0] * a[0] + c;
		result(0, 1) = t * a[0] * a[1] - s * a[2];
		result(0, 2) = t * a[0] * a[2] + s * a[1];

		result(1, 0) = t * a[0] * a[1] + s * a[2];
		result(1, 1) = t * a[1] * a[1] + c;
		result(1, 2) = t * a[1] * a[2] - s * a[0];

		result(2, 0) = t * a[0] * a[2] - s * a[1];
		result(2, 1) = t * a[1] * a[2] + s * a[0];
		result(2, 2) = t * a[2] * a[2] + c;

		return result;
	}

	inline Vec3 ExtractRight(const Mat4& m)
	{
		return Vec3(m(0, 0), m(1, 0), m(2, 0));
	}

	inline Vec3 ExtractUp(const Mat4& m)
	{
		return Vec3(m(0, 1), m(1, 1), m(2, 1));
	}

	inline Vec3 ExtractForward(const Mat4& m)
	{
		return Vec3(m(0, 2), m(1, 2), m(2, 2));
	}

	inline Vec3 ExtractPosition(const Mat4& m)
	{
		return Vec3(m(0, 3), m(1, 3), m(2, 3));
	}

	inline Vec3 ExtractScale(const Mat4& m)
	{
		Vec3 right = ExtractRight(m);
		Vec3 up = ExtractUp(m);
		Vec3 forward = ExtractForward(m);

		return Vec3(right.Length(), up.Length(), forward.Length());
	}

	inline Mat4 FromBasis(const Vec3& right, const Vec3& up, const Vec3& forward, const Vec3& position = Vec3(0, 0, 0))
	{
		Mat4 result = Identity<Mat4>();

		result(0, 0) = right[0];
		result(1, 0) = right[1];
		result(2, 0) = right[2];

		result(0, 1) = up[0];
		result(1, 1) = up[1];
		result(2, 1) = up[2];

		result(0, 2) = forward[0];
		result(1, 2) = forward[1];
		result(2, 2) = forward[2];

		result(0, 3) = position[0];
		result(1, 3) = position[1];
		result(2, 3) = position[2];

		return result;
	}
}

#endif //MATHLIB_TRANSFORM_HPP
