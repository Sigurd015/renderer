#pragma once
#include "defines.h"
#include "math/math.h"
#include "containers/darray.h"

// Perspective camera
typedef struct {
	f32 fov, near_plane, far_plane;
	vec3 position, forward_direction;

	u32 viewport_width, viewport_height;
	vec2 last_mouse_position;

	mat4 view, projection, inverse_view, inverse_projection;

	// For ray tracing
	darray* ray_directions;
} camera;

void camera_create(camera* cam, f32 fov, f32 near_plane, f32 far_plane, u32 viewport_width, u32 viewport_height);
b8 camera_update(camera* cam, f32 delta_time);
void camera_resize(camera* cam, u32 width, u32 height);
void camera_destroy(camera* cam);
mat4 camera_get_view(camera* cam);
mat4 camera_get_projection(camera* cam);
mat4 camera_get_inverse_view(camera* cam);
mat4 camera_get_inverse_projection(camera* cam);
vec3 camera_get_position(camera* cam);
vec3 camera_get_forward_direction(camera* cam);
darray* camera_get_ray_directions(camera* cam);