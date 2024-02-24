#include "core.h"
#include "entry.h"

// TODO: temporary
#define WINDOW_WIDTH 1280	
#define WINDOW_HEIGHT 720

static scene s_scene;
static camera s_camera;

void viewer_init()
{
	darray* dary = darray_create(u32);

	for (u32 i = 0; i < 100; i++)
	{
		dary = darray_push(dary, &i);
	}

	for (u32 i = 0; i < 100; i++)
	{
		APP_LOG_INFO("Darray - %d", *(u32*)darray_get(dary, i));
	}

	dary = darray_resize(dary, 200);

	for (u32 i = 0; i < 200; i++)
	{
		dary = darray_push(dary, &i);
	}

	for (u32 i = 0; i < 200; i++)
	{
		APP_LOG_INFO("Darray - %d", *(u32*)darray_get(dary, i));
	}

	darray_clear(dary);

	for (u32 i = 0; i < 300; i++)
	{
		dary = darray_push(dary, &i);
	}

	for (u32 i = 0; i < 300; i++)
	{
		APP_LOG_INFO("Darray - %d", *(u32*)darray_get(dary, i));
	}

	darray_destroy(dary);

	// TODO: temporary
	camera_create(&s_camera, DEG_TO_RAD(45.0f), 0.1f, 100.0f, 1920, 1080);
	s_scene.materials = darray_create(material);
	s_scene.spheres = darray_create(sphere);

	material mat;
	mat.albedo = vec3_one;
	mat.roughness = 1.0f;
	mat.metallic = 0.0f;
	mat.emission_color = vec3_zero;
	mat.emission_power = 0.0f;

	// Pink
	{
		mat.albedo = vec3_create(1.0f, 0.0f, 1.0f);
		mat.roughness = 0.0f;
		s_scene.materials = darray_push(s_scene.materials, &mat);
	}

	// Blue
	{
		mat.albedo = vec3_create(0.2f, 0.3f, 1.0f);
		mat.roughness = 0.1f;
		s_scene.materials = darray_push(s_scene.materials, &mat);
	}

	// Orange
	{
		mat.albedo = vec3_create(0.8f, 0.5f, 0.2f);
		mat.roughness = 0.1f;
		mat.emission_color = mat.albedo;
		mat.emission_power = 2.0f;
		s_scene.materials = darray_push(s_scene.materials, &mat);
	}

	sphere sphere;
	sphere.position = vec3_zero;
	sphere.radius = 0.5f;
	sphere.material_index = 0;

	{
		sphere.position = vec3_zero;
		sphere.radius = 1.0f;
		sphere.material_index = 0;
		s_scene.spheres = darray_push(s_scene.spheres, &sphere);
	}

	{
		sphere.position = vec3_create(0.0f, -101.0f, 0.0f);
		sphere.radius = 100.0f;
		sphere.material_index = 1;
		s_scene.spheres = darray_push(s_scene.spheres, &sphere);
	}

	{
		sphere.position = vec3_create(2.0f, 0.0f, 0.0f);
		sphere.radius = 1.0f;
		sphere.material_index = 2;
		s_scene.spheres = darray_push(s_scene.spheres, &sphere);
	}
}

void viewer_update(f32 delta_time)
{
	//APP_LOG_INFO("Viewer update - %f", delta_time);

#if 0
	vec4 color = vec4_zero;

	if (input_is_key(KEY_Q))
	{
		color = vec4_create(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else if (input_is_key(KEY_W))
	{
		color = vec4_create(0.0f, 1.0f, 0.0f, 1.0f);
	}
	else if (input_is_key(KEY_E))
	{
		color = vec4_create(0.0f, 0.0f, 1.0f, 1.0f);
	}
	else if (input_is_key(KEY_R))
	{
		color = vec4_create(1.0f, 1.0f, 1.0f, 1.0f);
	}
	renderer_clear(color);
#else
	if (camera_update(&s_camera, delta_time))
	{
		renderer_reset_frame_count();
	}

	camera_resize(&s_camera, WINDOW_WIDTH, WINDOW_HEIGHT);

	renderer_draw(&s_scene, &s_camera);
#endif
}

void viewer_shutdown()
{
	camera_release(&s_camera);
	darray_destroy(s_scene.materials);
	darray_destroy(s_scene.spheres);
}

b8 on_mouse_move(event e)
{
	//APP_LOG_INFO("Mouse move - %f, %f", e.context.mouse_moved.x, e.context.mouse_moved.y);

	return FALSE;
}

b8 on_mouse_pressed(event e)
{
	APP_LOG_INFO("Mouse pressed - %d", e.context.mouse_button_pressed.button);

	return FALSE;
}

b8 on_mouse_released(event e)
{
	APP_LOG_INFO("Mouse released - %d", e.context.mouse_button_released.button);

	return FALSE;
}

b8 on_key_pressed(event e)
{
	APP_LOG_INFO("Key pressed - %d, %d", e.context.key_pressed.key, e.context.key_pressed.repeat);

	return FALSE;
}

b8 on_key_released(event e)
{
	APP_LOG_INFO("Key released - %d", e.context.key_released.key);

	return FALSE;
}

void viewer_on_event(event e)
{
	event_dispatcher(EVENT_TYPE_MOUSE_MOVED, &e, on_mouse_move);
	event_dispatcher(EVENT_TYPE_MOUSE_BUTTON_PRESSED, &e, on_mouse_pressed);
	event_dispatcher(EVENT_TYPE_MOUSE_BUTTON_RELEASED, &e, on_mouse_released);

	event_dispatcher(EVENT_TYPE_KEY_PRESSED, &e, on_key_pressed);
	event_dispatcher(EVENT_TYPE_KEY_RELEASED, &e, on_key_released);
}

void application_create(application* app)
{
	app->application_spec.platform_spec.name = "Viewer";
	app->application_spec.platform_spec.width = WINDOW_WIDTH;
	app->application_spec.platform_spec.height = WINDOW_HEIGHT;
	app->application_spec.platform_spec.resizable = FALSE;
	app->application_spec.platform_spec.maximizable = FALSE;
	app->application_spec.platform_spec.minimizable = TRUE;
	app->init = viewer_init;
	app->update = viewer_update;
	app->shutdown = viewer_shutdown;
	app->on_event = viewer_on_event;
}