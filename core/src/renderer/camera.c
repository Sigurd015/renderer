#include "pch.h"
#include "camera.h"
#include "input/input.h"

void recalculate_view(camera* cam)
{
	cam->view = mat4_look_at(cam->position, vec3_add(cam->position, cam->forward_direction), vec3_up);
	cam->inverse_view = mat4_inverse(cam->view);
}

void recalculate_projection(camera* cam)
{
	cam->projection = mat4_perspective(cam->fov, (f32)cam->viewport_width / (f32)cam->viewport_height, cam->near_plane, cam->far_plane);
	cam->inverse_projection = mat4_inverse(cam->projection);
}

void recalculate_ray_directions(camera* cam)
{
	cam->ray_directions = darray_resize(cam->ray_directions, cam->viewport_width * cam->viewport_height);

	for (u32 y = 0; y < cam->viewport_height; y++)
	{
		for (u32 x = 0; x < cam->viewport_width; x++)
		{
			vec2 coord = vec2_create((f32)x / (f32)cam->viewport_width, (f32)y / (f32)cam->viewport_height);
			coord = vec2_sub_scalar(vec2_mul_scalar(coord, 2.0f), 1.0f);

			vec4 target = vec4_mul_m4(vec4_create(coord.x, coord.y, 1.0f, 1.0f), cam->inverse_projection);
			vec3 ray_direction = vec4_to_vec3(vec4_mul_m4(vec4_create_from_vec3(vec3_normalize(vec3_div(vec4_to_vec3(target), target.w)), 0.0f), cam->inverse_view));
			cam->ray_directions = darray_push(cam->ray_directions, &ray_direction);
		}
	}
}

// Fov is in radians
void camera_create(camera* cam, f32 fov, f32 near_plane, f32 far_plane, u32 viewport_width, u32 viewport_height)
{
	cam->fov = fov;
	cam->near_plane = near_plane;
	cam->far_plane = far_plane;
	cam->viewport_width = viewport_width;
	cam->viewport_height = viewport_height;
	cam->position = vec3_create(0.0f, 0.0f, 5.0f);
	cam->forward_direction = vec3_create(0.0f, 0.0f, -1.0f);
	cam->last_mouse_position = vec2_zero;
	cam->view = mat4_identity;
	cam->projection = mat4_identity;
	cam->inverse_view = mat4_identity;
	cam->inverse_projection = mat4_identity;
	cam->ray_directions = darray_create(ray);
}

b8 camera_update(camera* cam, f32 delta_time)
{
	vec2 mousePos = input_get_mouse_position();
	vec2 delta = vec2_mul_scalar(vec2_sub(mousePos, cam->last_mouse_position), 0.002f);
	cam->last_mouse_position = mousePos;

	if (!input_is_mouse_button_down(MOUSE_BUTTON_RIGHT))
	{
		input_set_cursor(TRUE);
		return FALSE;
	}

	input_set_cursor(FALSE);

	b8 moved = FALSE;

	vec3 rightDirection = vec3_cross(cam->forward_direction, vec3_up);

	f32 speed = 5.0f;

	// Movement
	if (input_is_key_down(KEY_W))
	{
		cam->position = vec3_add(cam->position, vec3_mul_scalar(cam->forward_direction, speed * delta_time));
		moved = TRUE;
	}
	else if (input_is_key_down(KEY_S))
	{
		cam->position = vec3_sub(cam->position, vec3_mul_scalar(cam->forward_direction, speed * delta_time));
		moved = TRUE;
	}

	if (input_is_key_down(KEY_A))
	{
		cam->position = vec3_sub(cam->position, vec3_mul_scalar(rightDirection, speed * delta_time));
		moved = TRUE;
	}
	else if (input_is_key_down(KEY_D))
	{
		cam->position = vec3_add(cam->position, vec3_mul_scalar(rightDirection, speed * delta_time));
		moved = TRUE;
	}

	if (input_is_key_down(KEY_Q))
	{
		cam->position = vec3_sub(cam->position, vec3_mul_scalar(vec3_up, speed * delta_time));
		moved = TRUE;
	}
	else if (input_is_key_down(KEY_E))
	{
		cam->position = vec3_add(cam->position, vec3_mul_scalar(vec3_up, speed * delta_time));
		moved = TRUE;
	}

	// Rotation
	if (delta.x != 0.0f || delta.y != 0.0f)
	{
		float pitchDelta = delta.y * 0.3f;
		float yawDelta = delta.x * 0.3f;

		quat q = quat_normalize(quat_mul(quat_axis_angle(rightDirection, -pitchDelta), quat_axis_angle(vec3_up, -yawDelta)));
		cam->forward_direction = quat_rotate_vec3(q, cam->forward_direction);
		moved = TRUE;
	}

	if (moved)
	{
		recalculate_view(cam);
		recalculate_ray_directions(cam);
	}
	return moved;
}

void camera_resize(camera* cam, u32 width, u32 height)
{
	cam->viewport_width = width;
	cam->viewport_height = height;

	recalculate_projection(cam);
	recalculate_ray_directions(cam);
}

void camera_release(camera* cam)
{
	darray_destroy(cam->ray_directions);
}

mat4 camera_get_view(camera* cam)
{
	return cam->view;
}

mat4 camera_get_projection(camera* cam)
{
	return cam->projection;
}

mat4 camera_get_inverse_view(camera* cam)
{
	return cam->inverse_view;
}

mat4 camera_get_inverse_projection(camera* cam)
{
	return cam->inverse_projection;
}

vec3 camera_get_position(camera* cam)
{
	return cam->position;
}

vec3 camera_get_forward_direction(camera* cam)
{
	return cam->forward_direction;
}

darray* camera_get_ray_directions(camera* cam)
{
	return cam->ray_directions;
}