#include "pch.h"
#include "math.h"

#include <math.h>

// -- Vector 2 --
vec2 vec2_create_from_scalar(f32 f)
{
	return vec2_create(f, f);
}

vec2 vec2_create(f32 x, f32 y)
{
	vec2 result;
	result.x = x;
	result.y = y;
	return result;
}

vec2 vec2_add(vec2 left, vec2 right)
{
	vec2 result;
	result.x = left.x + right.x;
	result.y = left.y + right.y;
	return result;
}

vec2 vec2_sub(vec2 left, vec2 right)
{
	vec2 result;
	result.x = left.x - right.x;
	result.y = left.y - right.y;
	return result;
}

vec2 vec2_sub_scalar(vec2 v, f32 f)
{
	vec2 result;
	result.x = v.x - f;
	result.y = v.y - f;
	return result;
}

vec2 vec2_mul(vec2 left, vec2 right)
{
	vec2 result;
	result.x = left.x * right.x;
	result.y = left.y * right.y;
	return result;
}

vec2 vec2_mul_scalar(vec2 v, f32 f)
{
	vec2 result;
	result.x = v.x * f;
	result.y = v.y * f;
	return result;
}

vec2 vec2_div(vec2 v, f32 f)
{
	vec2 result;
	result.x = v.x / f;
	result.y = v.y / f;
	return result;
}

f32 vec2_len_sq(vec2 v)
{
	return v.x * v.x + v.y * v.y;
}

f32 vec2_len(vec2 v)
{
	return f32_sqrt(vec2_len_sq(v));
}

vec2 vec2_normalize(vec2 v)
{
	f32 len = vec2_len(v);
	return vec2_div(v, len);
}

f32 vec2_distance_sq(vec2 left, vec2 right)
{
	return vec2_len_sq(vec2_sub(left, right));
}

f32 vec2_distance(vec2 left, vec2 right)
{
	return vec2_len(vec2_sub(left, right));
}

b32 vec2_equal(vec2 left, vec2 right)
{
	return left.x == right.x && left.y == right.y;
}

// -- Vector 3 --
vec3 vec3_create(f32 x, f32 y, f32 z)
{
	vec3 result;
	result.x = x;
	result.y = y;
	result.z = z;
	return result;
}

vec3 vec3_add(vec3 left, vec3 right)
{
	vec3 result;
	result.x = left.x + right.x;
	result.y = left.y + right.y;
	result.z = left.z + right.z;
	return result;
}

vec3 vec3_sub(vec3 left, vec3 right)
{
	vec3 result;
	result.x = left.x - right.x;
	result.y = left.y - right.y;
	result.z = left.z - right.z;
	return result;
}

vec3 vec3_mul(vec3 left, vec3 right)
{
	vec3 result;
	result.x = left.x * right.x;
	result.y = left.y * right.y;
	result.z = left.z * right.z;
	return result;
}

vec3 vec3_mul_scalar(vec3 v, f32 f)
{
	vec3 result;
	result.x = v.x * f;
	result.y = v.y * f;
	result.z = v.z * f;
	return result;
}

vec3 vec3_div(vec3 v, f32 f)
{
	vec3 result;
	result.x = v.x / f;
	result.y = v.y / f;
	result.z = v.z / f;
	return result;
}

f32 vec3_len_sq(vec3 v)
{
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

f32 vec3_len(vec3 v)
{
	return f32_sqrt(vec3_len_sq(v));
}

vec3 vec3_normalize(vec3 v)
{
	f32 len = vec3_len(v);
	return vec3_div(v, len);
}

f32 vec3_distance_sq(vec3 left, vec3 right)
{
	return vec3_len_sq(vec3_sub(left, right));
}

f32 vec3_distance(vec3 left, vec3 right)
{
	return vec3_len(vec3_sub(left, right));
}

b32 vec3_equal(vec3 left, vec3 right)
{
	return left.x == right.x && left.y == right.y && left.z == right.z;
}

f32 vec3_dot(vec3 left, vec3 right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z;
}

vec3 vec3_cross(vec3 left, vec3 right)
{
	vec3 result;
	result.x = left.y * right.z - left.z * right.y;
	result.y = left.z * right.x - left.x * right.z;
	result.z = left.x * right.y - left.y * right.x;
	return result;
}

vec3 vec3_reflect(vec3 v, vec3 normal)
{
	f32 dot = vec3_dot(v, normal);
	vec3 result;
	result.x = v.x - 2.0f * dot * normal.x;
	result.y = v.y - 2.0f * dot * normal.y;
	result.z = v.z - 2.0f * dot * normal.z;
	return result;
}

vec3 vec3_random()
{
	vec3 result;
	result.x = f32_random();
	result.y = f32_random();
	result.z = f32_random();
	return result;
}

vec3 vec3_random_range(f32 min, f32 max)
{
	vec3 result;
	result.x = f32_random_range(min, max);
	result.y = f32_random_range(min, max);
	result.z = f32_random_range(min, max);
	return result;
}

// -- Vector 4 --
vec4 vec4_create_from_vec3(vec3 v, f32 w)
{
	vec4 result;
	result.x = v.x;
	result.y = v.y;
	result.z = v.z;
	result.w = w;
	return result;
}

vec4 vec4_create(f32 x, f32 y, f32 z, f32 w)
{
	vec4 result;
	result.x = x;
	result.y = y;
	result.z = z;
	result.w = w;
	return result;
}

vec4 vec4_add(vec4 left, vec4 right)
{
	vec4 result;
	result.x = left.x + right.x;
	result.y = left.y + right.y;
	result.z = left.z + right.z;
	result.w = left.w + right.w;
	return result;
}

vec4 vec4_sub(vec4 left, vec4 right)
{
	vec4 result;
	result.x = left.x - right.x;
	result.y = left.y - right.y;
	result.z = left.z - right.z;
	result.w = left.w - right.w;
	return result;
}

vec4 vec4_mul(vec4 left, vec4 right)
{
	vec4 result;
	result.x = left.x * right.x;
	result.y = left.y * right.y;
	result.z = left.z * right.z;
	result.w = left.w * right.w;
	return result;
}

vec4 vec4_mul_m4(vec4 v, mat4 m)
{
	vec4 result;
	result.x = v.x * m.m00 + v.y * m.m10 + v.z * m.m20 + v.w * m.m30;
	result.y = v.x * m.m01 + v.y * m.m11 + v.z * m.m21 + v.w * m.m31;
	result.z = v.x * m.m02 + v.y * m.m12 + v.z * m.m22 + v.w * m.m32;
	result.w = v.x * m.m03 + v.y * m.m13 + v.z * m.m23 + v.w * m.m33;
	return result;
}

vec4 vec4_div(vec4 v, f32 f)
{
	vec4 result;
	result.x = v.x / f;
	result.y = v.y / f;
	result.z = v.z / f;
	result.w = v.w / f;
	return result;
}

f32 vec4_len_sq(vec4 v)
{
	return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
}

f32 vec4_len(vec4 v)
{
	return f32_sqrt(vec4_len_sq(v));
}

vec4 vec4_normalize(vec4 v)
{
	f32 len = vec4_len(v);
	return vec4_div(v, len);
}

f32 vec4_distance_sq(vec4 left, vec4 right)
{
	return vec4_len_sq(vec4_sub(left, right));
}

f32 vec4_distance(vec4 left, vec4 right)
{
	return vec4_len(vec4_sub(left, right));
}

b32 vec4_equal(vec4 left, vec4 right)
{
	return left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
}

f32 vec4_dot(vec4 left, vec4 right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
}

vec3 vec4_to_vec3(vec4 v)
{
	vec3 result;
	result.x = v.x;
	result.y = v.y;
	result.z = v.z;
	return result;
}

vec4 vec4_clamp(vec4 v, vec4 min, vec4 max)
{
	vec4 result;
	result.x = f32_clamp(v.x, min.x, max.x);
	result.y = f32_clamp(v.y, min.y, max.y);
	result.z = f32_clamp(v.z, min.z, max.z);
	result.w = f32_clamp(v.w, min.w, max.w);
	return result;
}

u32 vec4_to_rgba_u32(vec4 color)
{
	u8 r = (u8)(color.r * 255.0f);
	u8 g = (u8)(color.g * 255.0f);
	u8 b = (u8)(color.b * 255.0f);
	u8 a = (u8)(color.a * 255.0f);
	return (r << 24) | (g << 16) | (b << 8) | a;
}

u32 vec4_to_argb_u32(vec4 color)
{
	u8 r = (u8)(color.r * 255.0f);
	u8 g = (u8)(color.g * 255.0f);
	u8 b = (u8)(color.b * 255.0f);
	u8 a = (u8)(color.a * 255.0f);
	return (a << 24) | (r << 16) | (g << 8) | b;
}

u32 vec4_to_abgr_u32(vec4 color)
{
	u8 r = (u8)(color.r * 255.0f);
	u8 g = (u8)(color.g * 255.0f);
	u8 b = (u8)(color.b * 255.0f);
	u8 a = (u8)(color.a * 255.0f);
	return (a << 24) | (b << 16) | (g << 8) | r;
}