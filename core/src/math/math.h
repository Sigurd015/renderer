#pragma once
#include "defines.h"

// Right Handed Coordinate System
// Column Major Matrix

#define PI 3.14159265358979323846f
#define PI_2 2.0f * PI
#define RAD_TO_DEG(rad) (180.0f / PI) * rad
#define DEG_TO_RAD(deg) (PI / 180.0f) * deg
#define F32_MAX 3.402823466e+38f

// -- Scalar types --
i32 i32_random();
i32 i32_random_range(i32 min, i32 max);
i32 i32_abs(i32 i);
void i32_swap(i32* a, i32* b);

f32 f32_abs(f32 f);
f32 f32_sqrt(f32 f);
f32 f32_clamp(f32 f, f32 min, f32 max);
f32 f32_sin(f32 f);
f32 f32_cos(f32 f);
f32 f32_tan(f32 f);
f32 f32_random();
f32 f32_random_range(f32 min, f32 max);

// -- Vector --
typedef union {
	f32 elements[2];
	struct {
		union {
			f32 x, r, u;
		};
		union {
			f32 y, g, v;
		};
	};
} vec2;

typedef union {
	f32 elements[3];
	struct {
		union {
			f32 x, r, u;
		};
		union {
			f32 y, g, v;
		};
		union {
			f32 z, b, w;
		};
	};
} vec3;

typedef union {
	f32 elements[4];
	struct {
		union {
			f32 x, r;
		};
		union {
			f32 y, g;
		};
		union {
			f32 z, b;
		};
		union {
			f32 w, a;
		};
	};
} vec4;
typedef vec4 quat;

// -- Ray --
typedef struct {
	vec3 origin, direction;
} ray;

// -- Matrix --
typedef union {
	f32 elements[3 * 3];
	struct {
		f32 m00, m01, m02;
		f32 m10, m11, m12;
		f32 m20, m21, m22;
	};
} mat3;

typedef union {
	f32 elements[4 * 4];
	struct {
		f32 m00, m01, m02, m03;
		f32 m10, m11, m12, m13;
		f32 m20, m21, m22, m23;
		f32 m30, m31, m32, m33;
	};
} mat4;

// -- Vector types --
#define vec2_zero (vec2) { 0.0f, 0.0f }
#define vec3_zero (vec3) { 0.0f, 0.0f, 0.0f }
#define vec4_zero (vec4) { 0.0f, 0.0f, 0.0f, 0.0f }

#define vec2_one (vec2) { 1.0f, 1.0f }
#define vec3_one (vec3) { 1.0f, 1.0f, 1.0f }
#define vec4_one (vec4) { 1.0f, 1.0f, 1.0f, 1.0f }

#define vec2_up (vec2) { 0.0f, 1.0f }
#define vec3_up (vec3) { 0.0f, 1.0f, 0.0f }
#define vec4_up (vec4) { 0.0f, 1.0f, 0.0f, 0.0f }

#define vec2_down (vec2) { 0.0f, -1.0f }
#define vec3_down (vec3) { 0.0f, -1.0f, 0.0f }
#define vec4_down (vec4) { 0.0f, -1.0f, 0.0f, 0.0f }

#define vec2_left (vec2) { -1.0f, 0.0f }
#define vec3_left (vec3) { -1.0f, 0.0f, 0.0f }
#define vec4_left (vec4) { -1.0f, 0.0f, 0.0f, 0.0f }

#define vec2_right (vec2) { 1.0f, 0.0f }
#define vec3_right (vec3) { 1.0f, 0.0f, 0.0f }
#define vec4_right (vec4) { 1.0f, 0.0f, 0.0f, 0.0f }

vec2 vec2_create_from_scalar(f32 f);
vec2 vec2_create(f32 x, f32 y);
vec2 vec2_add(vec2 left, vec2 right);
vec2 vec2_sub(vec2 left, vec2 right);
vec2 vec2_sub_scalar(vec2 v, f32 f);
vec2 vec2_mul(vec2 left, vec2 right);
vec2 vec2_mul_scalar(vec2 v, f32 f);
vec2 vec2_div(vec2 v, f32 f);
f32 vec2_len_sq(vec2 v);
f32 vec2_len(vec2 v);
vec2 vec2_normalize(vec2 v);
f32 vec2_distance_sq(vec2 left, vec2 right);
f32 vec2_distance(vec2 left, vec2 right);
b32 vec2_equal(vec2 left, vec2 right);

vec3 vec3_create(f32 x, f32 y, f32 z);
vec3 vec3_add(vec3 left, vec3 right);
vec3 vec3_sub(vec3 left, vec3 right);
vec3 vec3_mul(vec3 left, vec3 right);
vec3 vec3_mul_scalar(vec3 v, f32 f);
vec3 vec3_div(vec3 v, f32 f);
f32 vec3_len_sq(vec3 v);
f32 vec3_len(vec3 v);
vec3 vec3_normalize(vec3 v);
f32 vec3_distance_sq(vec3 left, vec3 right);
f32 vec3_distance(vec3 left, vec3 right);
b32 vec3_equal(vec3 left, vec3 right);
f32 vec3_dot(vec3 left, vec3 right);
vec3 vec3_cross(vec3 left, vec3 right);
vec3 vec3_reflect(vec3 v, vec3 normal);
vec3 vec3_random();
vec3 vec3_random_range(f32 min, f32 max);

vec4 vec4_create_from_vec3(vec3 v, f32 w);
vec4 vec4_create(f32 x, f32 y, f32 z, f32 w);
vec4 vec4_add(vec4 left, vec4 right);
vec4 vec4_sub(vec4 left, vec4 right);
vec4 vec4_mul(vec4 left, vec4 right);
vec4 vec4_mul_m4(vec4 v, mat4 m);
vec4 vec4_div(vec4 v, f32 f);
f32 vec4_len_sq(vec4 v);
f32 vec4_len(vec4 v);
vec4 vec4_normalize(vec4 v);
f32 vec4_distance_sq(vec4 left, vec4 right);
f32 vec4_distance(vec4 left, vec4 right);
b32 vec4_equal(vec4 left, vec4 right);
f32 vec4_dot(vec4 left, vec4 right);
vec3 vec4_to_vec3(vec4 v);
vec4 vec4_clamp(vec4 v, vec4 min, vec4 max);
u32 vec4_to_rgba_u32(vec4 color);
u32 vec4_to_argb_u32(vec4 color);
u32 vec4_to_abgr_u32(vec4 color);

// -- Matrix types --
#define mat3_identity (mat3) { 1.0f, 0.0f, 0.0f, \
							   0.0f, 1.0f, 0.0f, \
							   0.0f, 0.0f, 1.0f }
#define mat4_identity (mat4) { 1.0f, 0.0f, 0.0f, 0.0f, \
							   0.0f, 1.0f, 0.0f, 0.0f, \
							   0.0f, 0.0f, 1.0f, 0.0f, \
							   0.0f, 0.0f, 0.0f, 1.0f }

mat4 mat4_mul(mat4 left, mat4 right);
mat4 mat4_ortographic(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far);
// Fov is in radians
mat4 mat4_perspective(f32 fov, f32 aspect_ratio, f32 near, f32 far);
mat4 mat4_look_at(vec3 eye, vec3 center, vec3 up);
mat4 mat4_inverse(mat4 m);
mat4 mat4_transpose(mat4 m);
mat4 mat4_translation(vec3 position);
mat4 mat4_scale(vec3 scale);
mat4 mat4_euler_x(f32 angle);
mat4 mat4_euler_y(f32 angle);
mat4 mat4_euler_z(f32 angle);
mat4 mat4_euler_xyz(f32 x, f32 y, f32 z);

// -- Quaternion type --
#define quat_identity (quat) { 0.0f, 0.0f, 0.0f, 1.0f }

f32 quat_normal(quat q);
quat quat_normalize(quat q);
quat quat_conjugate(quat q);
quat quat_inverse(quat q);
quat quat_mul(quat left, quat right);
f32 quat_dot(quat left, quat right);
quat quat_axis_angle(vec3 axis, f32 angle);
mat4 quat_to_mat4(quat q);
vec3 quat_rotate_vec3(quat q, vec3 v);