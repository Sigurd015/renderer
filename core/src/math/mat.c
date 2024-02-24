#include "pch.h"
#include "math.h"

#include <math.h>

// -- Matrix 4x4 --
mat4 mat4_mul(mat4 left, mat4 right)
{
	mat4 result;
	f32* dest = (f32*)result.elements;
	f32* l = (f32*)left.elements;
	f32* r = (f32*)right.elements;
	for (u32 i = 0; i < 4; i++)
	{
		for (u32 j = 0; j < 4; j++)
		{
			dest[0] =
				l[0] * r[0 + j] +
				l[1] * r[4 + j] +
				l[2] * r[8 + j] +
				l[3] * r[12 + j];
			dest++;
		}
		l += 4;
	}
}

mat4 mat4_ortographic(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far)
{
	mat4 result = mat4_identity;

	f32 lr = 1.0f / (left - right);
	f32 bt = 1.0f / (bottom - top);
	f32 nf = 1.0f / (near - far);

	result.elements[0] = -2.0f * lr;
	result.elements[5] = -2.0f * bt;
	result.elements[10] = 2.0f * nf;

	result.elements[12] = (left + right) * lr;
	result.elements[13] = (top + bottom) * bt;
	result.elements[14] = (far + near) * nf;

	return result;
}

mat4 mat4_perspective(f32 fov, f32 aspect_ratio, f32 near, f32 far)
{
	mat4 result = mat4_identity;

	f32 tan_half_fov = f32_tan(fov * 0.5);

	result.elements[0] = 1.0f / (aspect_ratio * tan_half_fov);
	result.elements[5] = 1.0f / tan_half_fov;
	result.elements[10] = -((far + near) / (far - near));
	result.elements[11] = -1.0f;
	result.elements[14] = -((2.0f * far * near) / (far - near));

	return result;
}

mat4 mat4_look_at(vec3 eye, vec3 center, vec3 up)
{
	mat4 result = mat4_identity;

	vec3 f = vec3_normalize(vec3_sub(center, eye));
	vec3 s = vec3_normalize(vec3_cross(f, up));
	vec3 u = vec3_cross(s, f);

	result.elements[0] = s.x;
	result.elements[1] = u.x;
	result.elements[2] = -f.x;

	result.elements[4] = s.y;
	result.elements[5] = u.y;
	result.elements[6] = -f.y;

	result.elements[8] = s.z;
	result.elements[9] = u.z;
	result.elements[10] = -f.z;

	result.elements[12] = -vec3_dot(s, eye);
	result.elements[13] = -vec3_dot(u, eye);
	result.elements[14] = vec3_dot(f, eye);

	return result;
}

mat4 mat4_inverse(mat4 m)
{
	mat4 result = mat4_identity;

	f32* dest = (f32*)result.elements;
	f32* src = (f32*)m.elements;

	f32 t0 = src[10] * src[15];
	f32 t1 = src[14] * src[11];
	f32 t2 = src[6] * src[15];
	f32 t3 = src[14] * src[7];
	f32 t4 = src[6] * src[11];
	f32 t5 = src[10] * src[7];
	f32 t6 = src[2] * src[15];
	f32 t7 = src[14] * src[3];
	f32 t8 = src[2] * src[11];
	f32 t9 = src[10] * src[3];
	f32 t10 = src[2] * src[7];
	f32 t11 = src[6] * src[3];
	f32 t12 = src[8] * src[13];
	f32 t13 = src[12] * src[9];
	f32 t14 = src[4] * src[13];
	f32 t15 = src[12] * src[5];
	f32 t16 = src[4] * src[9];
	f32 t17 = src[8] * src[5];
	f32 t18 = src[0] * src[13];
	f32 t19 = src[12] * src[1];
	f32 t20 = src[0] * src[9];
	f32 t21 = src[8] * src[1];
	f32 t22 = src[0] * src[5];
	f32 t23 = src[4] * src[1];

	dest[0] = (t0 * src[5] + t3 * src[9] + t4 * src[13]) -
		(t1 * src[5] + t2 * src[9] + t5 * src[13]);
	dest[1] = (t1 * src[1] + t6 * src[9] + t9 * src[13]) -
		(t0 * src[1] + t7 * src[9] + t8 * src[13]);
	dest[2] = (t2 * src[1] + t7 * src[5] + t10 * src[13]) -
		(t3 * src[1] + t6 * src[5] + t11 * src[13]);
	dest[3] = (t5 * src[1] + t8 * src[5] + t11 * src[9]) -
		(t4 * src[1] + t9 * src[5] + t10 * src[9]);

	f32 d = 1.0f / (src[0] * dest[0] + src[4] * dest[1] + src[8] * dest[2] + src[12] * dest[3]);

	dest[0] = d * dest[0];
	dest[1] = d * dest[1];
	dest[2] = d * dest[2];
	dest[3] = d * dest[3];
	dest[4] = d * ((t1 * src[4] + t2 * src[8] + t5 * src[12]) -
		(t0 * src[4] + t3 * src[8] + t4 * src[12]));
	dest[5] = d * ((t0 * src[0] + t7 * src[8] + t8 * src[12]) -
		(t1 * src[0] + t6 * src[8] + t9 * src[12]));
	dest[6] = d * ((t3 * src[0] + t6 * src[4] + t11 * src[12]) -
		(t2 * src[0] + t7 * src[4] + t10 * src[12]));
	dest[7] = d * ((t4 * src[0] + t9 * src[4] + t10 * src[8]) -
		(t5 * src[0] + t8 * src[4] + t11 * src[8]));
	dest[8] = d * ((t12 * src[7] + t15 * src[11] + t16 * src[15]) -
		(t13 * src[7] + t14 * src[11] + t17 * src[15]));
	dest[9] = d * ((t13 * src[3] + t18 * src[11] + t21 * src[15]) -
		(t12 * src[3] + t19 * src[11] + t20 * src[15]));
	dest[10] = d * ((t14 * src[3] + t19 * src[7] + t22 * src[15]) -
		(t15 * src[3] + t18 * src[7] + t23 * src[15]));
	dest[11] = d * ((t17 * src[3] + t20 * src[7] + t23 * src[11]) -
		(t16 * src[3] + t21 * src[7] + t22 * src[11]));
	dest[12] = d * ((t14 * src[10] + t17 * src[14] + t13 * src[6]) -
		(t16 * src[14] + t12 * src[6] + t15 * src[10]));
	dest[13] = d * ((t20 * src[14] + t12 * src[2] + t19 * src[10]) -
		(t18 * src[10] + t21 * src[14] + t13 * src[2]));
	dest[14] = d * ((t18 * src[6] + t23 * src[14] + t15 * src[2]) -
		(t22 * src[14] + t14 * src[2] + t19 * src[6]));
	dest[15] = d * ((t22 * src[10] + t16 * src[2] + t21 * src[6]) -
		(t20 * src[6] + t23 * src[10] + t17 * src[2]));

	return result;
}

mat4 mat4_transpose(mat4 m)
{
	mat4 result = mat4_identity;

	f32* dest = (f32*)result.elements;
	f32* src = (f32*)m.elements;

	dest[0] = src[0];
	dest[1] = src[4];
	dest[2] = src[8];
	dest[3] = src[12];
	dest[4] = src[1];
	dest[5] = src[5];
	dest[6] = src[9];
	dest[7] = src[13];
	dest[8] = src[2];
	dest[9] = src[6];
	dest[10] = src[10];
	dest[11] = src[14];
	dest[12] = src[3];
	dest[13] = src[7];
	dest[14] = src[11];
	dest[15] = src[15];

	return result;
}

mat4 mat4_translation(vec3 position)
{
	mat4 result = mat4_identity;

	result.elements[12] = position.x;
	result.elements[13] = position.y;
	result.elements[14] = position.z;

	return result;
}

mat4 mat4_scale(vec3 scale)
{
	mat4 result = mat4_identity;

	result.elements[0] = scale.x;
	result.elements[5] = scale.y;
	result.elements[10] = scale.z;

	return result;
}

mat4 mat4_euler_x(f32 angle)
{
	mat4 result = mat4_identity;

	f32 c = f32_cos(angle);
	f32 s = f32_sin(angle);

	result.elements[5] = c;
	result.elements[6] = s;
	result.elements[9] = -s;
	result.elements[10] = c;

	return result;
}

mat4 mat4_euler_y(f32 angle)
{
	mat4 result = mat4_identity;

	f32 c = f32_cos(angle);
	f32 s = f32_sin(angle);

	result.elements[0] = c;
	result.elements[2] = -s;
	result.elements[8] = s;
	result.elements[10] = c;

	return result;
}

mat4 mat4_euler_z(f32 angle)
{
	mat4 result = mat4_identity;

	f32 c = f32_cos(angle);
	f32 s = f32_sin(angle);

	result.elements[0] = c;
	result.elements[1] = s;
	result.elements[4] = -s;
	result.elements[5] = c;

	return result;
}

mat4 mat4_euler_xyz(f32 x, f32 y, f32 z)
{
	mat4 rx = mat4_euler_x(x);
	mat4 ry = mat4_euler_y(y);
	mat4 rz = mat4_euler_z(z);

	mat4 result = mat4_mul(rx, ry);
	result = mat4_mul(result, rz);

	return result;
}