#include "pch.h"
#include "math.h"

#include <math.h>

// -- Vector 2 --
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

vec2 vec2_mul(vec2 left, vec2 right)
{
	vec2 result;
	result.x = left.x * right.x;
	result.y = left.y * right.y;
	return result;
}

vec2 vec2_div(vec2 left, vec2 right)
{
	vec2 result;
	result.x = left.x / right.x;
	result.y = left.y / right.y;
	return result;
}

vec2 vec2_divf(vec2 v, f32 f)
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
	return sqrtf(vec2_len_sq(v));
}

vec2 vec2_normalize(vec2 v)
{
	f32 len = vec2_len(v);
	return vec2_divf(v, len);
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
	return sqrtf(vec3_len_sq(v));
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

// -- Vector 4 --
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
	return sqrtf(vec4_len_sq(v));
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