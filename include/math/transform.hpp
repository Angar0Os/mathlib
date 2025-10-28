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
		Vec3 right = Cross(forward, up.Normalize()).Normalize();
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
}

#endif //MATHLIB_TRANSFORM_HPP
