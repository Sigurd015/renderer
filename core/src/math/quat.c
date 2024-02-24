#include "pch.h"
#include "math.h"

#include <math.h>

f32 quat_normal(quat q)
{
	return f32_sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
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
	result.x = left.x * right.w + left.y * right.z - left.z * right.y + left.w * right.x;
	result.y = -left.x * right.z + left.y * right.w + left.z * right.x + left.w * right.y;
	result.z = left.x * right.y - left.y * right.x + left.z * right.w + left.w * right.z;
	result.w = -left.x * right.x - left.y * right.y - left.z * right.z + left.w * right.w;
	return result;
}

f32 quat_dot(quat left, quat right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
}

quat quat_axis_angle(vec3 axis, f32 angle)
{
	quat result;

	f32 half_angle = angle * 0.5f;
	f32 s = f32_sin(half_angle);

	result.x = axis.x * s;
	result.y = axis.y * s;
	result.z = axis.z * s;
	result.w = f32_cos(half_angle);

	return result;
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

vec3 quat_rotate_vec3(quat q, vec3 v)
{
	vec3 u = vec3_create(q.x, q.y, q.z);
	f32 s = q.w;

	return vec3_add(
		vec3_add(
			vec3_mul_scalar(u, 2.0f * vec3_dot(u, v)),
			vec3_mul_scalar(v, (s * s - vec3_dot(u, u)))),
		vec3_mul_scalar(vec3_cross(u, v), 2.0f * s));
}