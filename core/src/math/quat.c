#include "pch.h"
#include "math.h"

#include <math.h>

f32 quat_normal(quat q)
{
	return sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
}

quat quat_normalize(quat q)
{
	quat result;
	f32 normal = quat_normal(q);
	result.x /= normal;
	result.y /= normal;
	result.z /= normal;
	result.w /= normal;
	return result;
}

quat quat_conjugate(quat q)
{
	quat result;
	result.x = -q.x;
	result.y = -q.y;
	result.z = -q.z;
	result.w = q.w;
	return result;
}

quat quat_inverse(quat q)
{
	return quat_normalize(quat_conjugate(q));
}

quat quat_mul(quat left, quat right)
{
	quat result;
	result.x = left.w * right.x + left.x * right.w + left.y * right.z - left.z * right.y;
	result.y = left.w * right.y + left.y * right.w + left.z * right.x - left.x * right.z;
	result.z = left.w * right.z + left.z * right.w + left.x * right.y - left.y * right.x;
	result.w = left.w * right.w - left.x * right.x - left.y * right.y - left.z * right.z;
	return result;
}

f32 quat_dot(quat left, quat right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
}

mat4 quat_to_mat4(quat q)
{
	mat4 result = mat4_identity;

	// https://stackoverflow.com/questions/1556260/convert-quaternion-rotation-to-rotation-matrix

	quat n = quat_normalize(q);

	result.elements[0] = 1.0f - 2.0f * n.y * n.y - 2.0f * n.z * n.z;
	result.elements[1] = 2.0f * n.x * n.y - 2.0f * n.z * n.w;
	result.elements[2] = 2.0f * n.x * n.z + 2.0f * n.y * n.w;

	result.elements[4] = 2.0f * n.x * n.y + 2.0f * n.z * n.w;
	result.elements[5] = 1.0f - 2.0f * n.x * n.x - 2.0f * n.z * n.z;
	result.elements[6] = 2.0f * n.y * n.z - 2.0f * n.x * n.w;

	result.elements[8] = 2.0f * n.x * n.z - 2.0f * n.y * n.w;
	result.elements[9] = 2.0f * n.y * n.z + 2.0f * n.x * n.w;
	result.elements[10] = 1.0f - 2.0f * n.x * n.x - 2.0f * n.y * n.y;

	return result;
}

quat quat_axis_angle(vec3 axis, f32 angle)
{
	quat result;

	f32 half_angle = angle * 0.5f;
	f32 s = sinf(half_angle);

	result.x = axis.x * s;
	result.y = axis.y * s;
	result.z = axis.z * s;
	result.w = cosf(half_angle);

	return result;
}