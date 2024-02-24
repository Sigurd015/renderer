#include "pch.h"
#include "renderer.h"
#include "core/platform.h"

typedef struct {
	image* buffer;

	// TODO: temporary
	u32 frame_count;
	vec4* accumulation_buffer;
} internal_state;
static internal_state s_state;

void renderer_init(u32 width, u32 height, u32_color_type format)
{
	s_state.buffer = image_create(width, height, format);
	image_fill(s_state.buffer, vec4_create(0.0f, 0.0f, 0.0f, 1.0f));

	// TODO: temporary
	s_state.accumulation_buffer = memory_allocate(sizeof(vec4) * width * height, MEMORY_TAG_ARRAY);
	s_state.frame_count = 1;
}

void renderer_swap_buffers()
{
	platform_present(s_state.buffer);
}

void renderer_clear(vec4 color)
{
	image_fill(s_state.buffer, color);
}

void renderer_shutdown()
{
	// TODO: temporary
	memory_free(s_state.accumulation_buffer, s_state.buffer->width * s_state.buffer->height * sizeof(vec4), MEMORY_TAG_ARRAY);

	image_destroy(s_state.buffer);
}

// TODO: temporary
typedef struct {
	f32 hit_distance;
	vec3 world_position;
	vec3 world_normal;

	i32 object_index;
} hit_payload;

hit_payload miss()
{
	hit_payload payload;
	payload.hit_distance = -1.0f;
	return payload;
}

hit_payload closes_hit(scene* scene, ray* ray, f32 hit_distance, i32 object_index)
{
	hit_payload payload;
	payload.hit_distance = hit_distance;
	payload.object_index = object_index;

	sphere* closest_sphere = darray_get(scene->spheres, object_index);

	vec3 origin = vec3_sub(ray->origin, closest_sphere->position);
	payload.world_position = vec3_add(ray->origin, vec3_mul_scalar(ray->direction, hit_distance));
	payload.world_normal = vec3_normalize(payload.world_position);

	payload.world_position = vec3_add(payload.world_position, closest_sphere->position);

	return payload;
}

#include <math.h>
f32 f32_sqrt(f32 f)
{
	return sqrtf(f);
}

hit_payload trace_ray(scene* scene, ray* ray)
{
	// rayDirection = glm::normalize(rayDirection);

	// (bx^2 + by^2)t^2 + (2(axbx + ayby))t + (ax^2 + ay^2 - r^2) = 0
	// where
	// a = ray origin
	// b = ray direction
	// r = radius
	// t = hit distance

	i32 closest_sphere = -1;
	f32 hit_distance = F32_MAX;

	for (u32 i = 0; i < darray_get_length(scene->spheres); i++)
	{
		sphere* sphere = darray_get(scene->spheres, i);

		vec3 origin = vec3_sub(ray->origin, sphere->position);

		f32 a = vec3_dot(ray->direction, ray->direction);
		f32 b = 2.0f * vec3_dot(ray->direction, origin);
		f32 c = vec3_dot(origin, origin) - sphere->radius * sphere->radius;

		// Quadratic forumula discriminant:
		// b^2 - 4ac

		f32 discriminant = b * b - 4.0f * a * c;
		if (discriminant < 0.0f)
			continue;

		// Quadratic formula:
		// (-b +- sqrt(discriminant)) / 2a

		// float t0 = (-b + glm::sqrt(discriminant)) / (2.0f * a); // Second hit distance (currently unused)
		float closest_t = (-b - sqrtf(discriminant)) / (2.0f * a);
		if (closest_t > 0.0f && closest_t < hit_distance)
		{
			hit_distance = closest_t;
			closest_sphere = (i32)i;
		}
	}

	if (closest_sphere < 0)
		return miss();

	return closes_hit(scene, ray, hit_distance, closest_sphere);
}

vec4 per_pixel(scene* scene, camera* cam, u32 x, u32 y)
{
	ray ray;
	ray.origin = cam->position;
	ray.direction = *(vec3*)darray_get(cam->ray_directions, x + y * s_state.buffer->width);

	vec3 light = vec3_zero;
	vec3 contribution = vec3_one;

	u32 bounces = 5;
	for (u32 i = 0; i < bounces; i++)
	{
		hit_payload payload = trace_ray(scene, &ray);
		if (payload.hit_distance < 0.0f)
		{
			vec3 sky_color = vec3_create(0.6f, 0.7f, 0.9f);
			//light = vec3_add(light, vec3_mul(contribution, sky_color));
			break;
		}

		sphere* sphere = darray_get(scene->spheres, payload.object_index);
		material* mat = darray_get(scene->materials, sphere->material_index);

		contribution = vec3_mul(contribution, mat->albedo);
		light = vec3_add(light, vec3_mul_scalar(mat->emission_color, mat->emission_power));

		ray.origin = vec3_add(payload.world_position, vec3_mul_scalar(payload.world_normal, 0.0001f));
		//ray.direction = vec3_reflect(ray.direction, vec3_add(payload.world_normal, vec3_mul_scalar(vec3_create(0.3f, 0.4f, -0.1f), mat->roughness)));
		ray.direction = vec3_normalize(vec3_add(payload.world_normal, vec3_create(0.1f, -0.4f, 0.6f)));
	}

	return vec4_create_from_vec3(light, 1.0f);
}

void renderer_draw(scene* scene, camera* cam)
{
	if (s_state.frame_count == 1)
	{
		memory_zero(s_state.accumulation_buffer, s_state.buffer->width * s_state.buffer->height * sizeof(vec4));
	}

	for (u32 y = 0; y < s_state.buffer->height; y++)
	{
		for (u32 x = 0; x < s_state.buffer->width; x++)
		{
			vec4 color = per_pixel(scene, cam, x, y);
			s_state.accumulation_buffer[x + y * s_state.buffer->width] = vec4_add(s_state.accumulation_buffer[x + y * s_state.buffer->width], color);

			vec4 accumulated_color = s_state.accumulation_buffer[x + y * s_state.buffer->width];
			accumulated_color = vec4_div(accumulated_color, (f32)s_state.frame_count);

			accumulated_color = vec4_clamp(accumulated_color, vec4_zero, vec4_one);
			image_set_pixel(s_state.buffer, x + y * s_state.buffer->width, accumulated_color);
		}
	}
}

void renderer_reset_frame_count()
{
	s_state.frame_count = 1;
}