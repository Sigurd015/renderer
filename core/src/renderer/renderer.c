#include "pch.h"
#include "renderer.h"
#include "core/platform.h"

typedef struct {
	image* buffer;
	vec4 clear_color;

	// For ray tracing
	u32 frame_count;
	vec4* accumulation_buffer;
} internal_state;
static internal_state s_state;

void renderer_init(u32 width, u32 height, image_format format)
{
	s_state.buffer = image_create(width, height, format);
	s_state.clear_color = vec4_create(0.0f, 0.0f, 0.0f, 1.0f);

	// For ray tracing
	s_state.accumulation_buffer = memory_allocate(sizeof(vec4) * width * height, MEMORY_TAG_ARRAY);
	s_state.frame_count = 1;
}

void renderer_swap_buffers()
{
	image_flip_vertically(s_state.buffer);
	platform_present(s_state.buffer);
}

void renderer_set_clear_color(vec4 color)
{
	s_state.clear_color = color;
}

void renderer_clear()
{
	image_fill(s_state.buffer, s_state.clear_color);
}

void renderer_shutdown()
{
	// For ray tracing
	memory_free(s_state.accumulation_buffer, image_get_width(s_state.buffer) * image_get_height(s_state.buffer) * sizeof(vec4), MEMORY_TAG_ARRAY);

	image_destroy(s_state.buffer);
}

// --- Rasterization pipeline ---

// Bresenham's line algorithm
// see: https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
void draw_line(vec2 p0, vec2 p1, vec4 color)
{
	// Temporary
	CORE_ASSERT(p0.x >= 0 && p0.x < image_get_width(s_state.buffer), "draw_line - p0.x out of bounds");
	CORE_ASSERT(p0.y >= 0 && p0.y < image_get_height(s_state.buffer), "draw_line - p0.y out of bounds");
	CORE_ASSERT(p1.x >= 0 && p1.x < image_get_width(s_state.buffer), "draw_line - p1.x out of bounds");
	CORE_ASSERT(p1.y >= 0 && p1.y < image_get_height(s_state.buffer), "draw_line - p1.y out of bounds");

	b8 steep = f32_abs(p1.y - p0.y) > f32_abs(p1.x - p0.x);
	i32 x0 = (i32)p0.x;
	i32 y0 = (i32)p0.y;
	i32 x1 = (i32)p1.x;
	i32 y1 = (i32)p1.y;

	if (steep)
	{
		i32_swap(&x0, &y0);
		i32_swap(&x1, &y1);
	}

	if (x0 > x1)
	{
		i32_swap(&x0, &x1);
		i32_swap(&y0, &y1);
	}

	i32 deltax = x1 - x0;
	i32 deltay = i32_abs(y1 - y0);
	i32 error = deltax / 2;
	i32 y = y0;
	i32 ystep = (y0 < y1) ? 1 : -1;

	for (i32 x = x0; x <= x1; x++)
	{
		if (steep)
		{
			image_set_pixel(s_state.buffer, (u32)y + (u32)x * image_get_width(s_state.buffer), color);
		}
		else
		{
			image_set_pixel(s_state.buffer, (u32)x + (u32)y * image_get_width(s_state.buffer), color);
		}

		error -= deltay;
		if (error < 0)
		{
			y += ystep;
			error += deltax;
		}
	}
}

// Temporary
void draw_triangle(vec2 p0, vec2 p1, vec2 p2, vec4 color)
{
	draw_line(p0, p1, color);
	draw_line(p1, p2, color);
	draw_line(p2, p0, color);
}

void renderer_draw(scene* scene, camera* cam)
{
	image_fill(s_state.buffer, s_state.clear_color);

	// Temporary
	vec4 color = vec4_create(1.0f, 0.0f, 0.0f, 1.0f);
	draw_triangle(vec2_create(200.0f, 200.0f), vec2_create(300.0f, 200.0f), vec2_create(250.0f, 300.0f), vec4_create(1.0f, 0.0f, 0.0f, 1.0f));
	draw_triangle(vec2_create(900.0f, 200.0f), vec2_create(1000.0f, 200.0f), vec2_create(950.0f, 300.0f), vec4_create(0.0f, 1.0f, 0.0f, 1.0f));
	draw_triangle(vec2_create(500.0f, 400.0f), vec2_create(600.0f, 400.0f), vec2_create(550.0f, 500.0f), vec4_create(0.0f, 0.0f, 1.0f, 1.0f));
	draw_line(vec2_zero, vec2_create(1279.0f, 719.0f), vec4_create(1.0f, 0.0f, 0.0f, 1.0f));
	draw_line(vec2_create(0, 719.0f), vec2_create(1279.0f, 0.0f), vec4_create(1.0f, 0.0f, 0.0f, 1.0f));
	draw_line(vec2_create(0, 360.0f), vec2_create(1279.0f, 360.0f), vec4_create(1.0f, 0.0f, 0.0f, 1.0f));
	draw_line(vec2_create(640.0f, 0.0f), vec2_create(640.0f, 719.0f), vec4_create(1.0f, 0.0f, 0.0f, 1.0f));
}

// ------------------------------

// --- Ray tracing pipeline ---
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

hit_payload trace_ray(scene* scene, ray* ray)
{
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
		f32 b = 2.0f * vec3_dot(origin, ray->direction);
		f32 c = vec3_dot(origin, origin) - sphere->radius * sphere->radius;

		// Quadratic forumula discriminant:
		// b^2 - 4ac

		f32 discriminant = b * b - 4.0f * a * c;
		if (discriminant < 0.0f)
			continue;

		// Quadratic formula:
		// (-b +- sqrt(discriminant)) / 2a

		//float t0 = (-b + f32_sqrt(discriminant)) / (2.0f * a); // Second hit distance (currently unused)
		float closest_t = (-b - f32_sqrt(discriminant)) / (2.0f * a);
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
	ray.origin = camera_get_position(cam);
	ray.direction = *(vec3*)darray_get(cam->ray_directions, x + y * image_get_width(s_state.buffer));

	vec3 light = vec3_zero;
	vec3 contribution = vec3_one;

	u32 bounces = 5;
	for (u32 i = 0; i < bounces; i++)
	{
		hit_payload payload = trace_ray(scene, &ray);
		if (payload.hit_distance < 0.0f)
		{
			vec3 sky_color = vec3_create(0.6f, 0.7f, 0.9f);
			light = vec3_add(light, vec3_mul(contribution, sky_color));
			break;
		}

		sphere* sphere = darray_get(scene->spheres, payload.object_index);
		material* mat = darray_get(scene->materials, sphere->material_index);

		contribution = vec3_mul(contribution, mat->albedo);
		light = vec3_add(light, vec3_mul_scalar(mat->emission_color, mat->emission_power));

		ray.origin = vec3_add(payload.world_position, vec3_mul_scalar(payload.world_normal, 0.0001f));
		//ray.direction = vec3_reflect(ray.direction, vec3_add(payload.world_normal, vec3_mul_scalar(vec3_random(-0.5f, 0.5f), mat->roughness)));
		ray.direction = vec3_normalize(vec3_add(payload.world_normal, vec3_normalize(vec3_random(-1.0f, 1.0f))));
	}

	return vec4_create_from_vec3(light, 1.0f);
}

void renderer_rt_draw(scene* scene, camera* cam)
{
	image_fill(s_state.buffer, s_state.clear_color);

	if (s_state.frame_count == 1)
	{
		memory_zero(s_state.accumulation_buffer, image_get_width(s_state.buffer) * image_get_height(s_state.buffer) * sizeof(vec4));
	}

	for (u32 y = 0; y < image_get_height(s_state.buffer); y++)
	{
		for (u32 x = 0; x < image_get_width(s_state.buffer); x++)
		{
			vec4 color = per_pixel(scene, cam, x, y);
			s_state.accumulation_buffer[x + y * image_get_width(s_state.buffer)] = vec4_add(s_state.accumulation_buffer[x + y * image_get_width(s_state.buffer)], color);

			vec4 accumulated_color = s_state.accumulation_buffer[x + y * image_get_width(s_state.buffer)];
			accumulated_color = vec4_div(accumulated_color, (f32)s_state.frame_count);

			accumulated_color = vec4_clamp(accumulated_color, vec4_zero, vec4_one);
			image_set_pixel(s_state.buffer, x + y * image_get_width(s_state.buffer), accumulated_color);
		}
	}

	s_state.frame_count++;
}

void renderer_reset_frame_count()
{
	s_state.frame_count = 1;
}
// ----------------------------