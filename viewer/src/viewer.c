#include "core.h"
#include "entry.h"

#define WINDOW_WIDTH 1280	
#define WINDOW_HEIGHT 720

static scene s_scene;
static camera s_camera;
typedef enum {
	TEST_RASTERIZATION,
	TEST_RAY_TRACING
} test_type;
static test_type s_test_type = TEST_RASTERIZATION;

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

	// TODO: may move to scene_create
	camera_create(&s_camera, DEG_TO_RAD(45.0f), 0.1f, 100.0f, WINDOW_WIDTH, WINDOW_HEIGHT);
	scene_create(&s_scene);

	// TODO: Temp for ray tracing
	{
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

	{
		entity e;
		entity_create(&e);

		transform_component tc;
		tc.position = vec3_zero;
		tc.scale = vec3_create(1.0f, 1.0f, 1.0f);
		tc.rotation = vec3_zero;

		entity_add_component(&e, COMPONENT_TRANSFORM, &tc);

		/*	mesh_component mc;
			mc.triangles = darray_create(triangle);
			{
				triangle t;
				t.vertices[0].position = vec3_create(-1.0f, -1.0f, 0.0f);
				t.vertices[1].position = vec3_create(1.0f, -1.0f, 0.0f);
				t.vertices[2].position = vec3_create(0.0f, 1.0f, 0.0f);
				mc.triangles = darray_push(mc.triangles, &t);
			}
			entity_add_component(&e, COMPONENT_MESH, &mc);*/

		scene_add_entity(&s_scene, &e);
	}
}

void viewer_update(f32 delta_time)
{
	//APP_LOG_INFO("Viewer update - %f", delta_time);

	if (input_is_key_down(KEY_D1))
	{
		s_test_type = TEST_RASTERIZATION;
	}
	else if (input_is_key_down(KEY_D2))
	{
		s_test_type = TEST_RAY_TRACING;
	}

	switch (s_test_type)
	{
	case TEST_RASTERIZATION:
	{
		camera_update(&s_camera, delta_time);

		entity* e = darray_get(s_scene.entities, 0);
		transform_component* tc = entity_get_component(e, COMPONENT_TRANSFORM);
		tc->rotation.z += DEG_TO_RAD(15.0f) * delta_time;
		renderer_draw(&s_scene, &s_camera);
		break;
	}
	case TEST_RAY_TRACING:
	{
		if (camera_update(&s_camera, delta_time))
		{
			renderer_reset_frame_count();
		}
		renderer_rt_draw(&s_scene, &s_camera);
		break;
	}
	}
}

void viewer_shutdown()
{
	camera_destroy(&s_camera);
	scene_destroy(&s_scene);
}

b8 viewer_on_wnd_resize(event e)
{
	APP_LOG_INFO("Window resize - %d, %d", e.context.wnd_resize.width, e.context.wnd_resize.height);

	camera_resize(&s_camera, e.context.wnd_resize.width, e.context.wnd_resize.height);

	return FALSE;
}

b8 on_mouse_move(event e)
{
	//APP_LOG_INFO("Mouse move - %f, %f", e.context.mouse_moved.x, e.context.mouse_moved.y);

	return FALSE;
}

b8 on_mouse_pressed(event e)
{
	//APP_LOG_INFO("Mouse pressed - %d", e.context.mouse_button_pressed.button);

	return FALSE;
}

b8 on_mouse_released(event e)
{
	//APP_LOG_INFO("Mouse released - %d", e.context.mouse_button_released.button);

	return FALSE;
}

b8 on_key_pressed(event e)
{
	//APP_LOG_INFO("Key pressed - %d, %d", e.context.key_pressed.key, e.context.key_pressed.repeat);

	return FALSE;
}

b8 on_key_released(event e)
{
	//APP_LOG_INFO("Key released - %d", e.context.key_released.key);

	return FALSE;
}

void viewer_on_event(event e)
{
	event_dispatcher(EVENT_TYPE_WINDOW_RESIZE, &e, viewer_on_wnd_resize);

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