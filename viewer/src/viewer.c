#include "core.h"
#include "entry.h"

void viewer_init()
{
}

void viewer_update(float deltatime)
{
	//APP_LOG_INFO("Viewer update - %f", deltatime);

	vec4 color = vec4_create(1.0f, 0.0f, 0.0f, 1.0f);
	renderer_clear(color);
}

void viewer_shutdown()
{
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

void viewer_on_event(event e)
{
	event_dispatcher(EVENT_TYPE_MOUSE_MOVED, &e, on_mouse_move);
	event_dispatcher(EVENT_TYPE_MOUSE_BUTTON_PRESSED, &e, on_mouse_pressed);
	event_dispatcher(EVENT_TYPE_MOUSE_BUTTON_RELEASED, &e, on_mouse_released);
}

void application_create(application* app)
{
	app->application_spec.platform_spec.name = "Viewer";
	app->application_spec.platform_spec.width = 1920;
	app->application_spec.platform_spec.height = 1080;
	app->application_spec.platform_spec.resizable = TRUE;
	app->application_spec.platform_spec.maximizable = TRUE;
	app->application_spec.platform_spec.minimizable = TRUE;
	app->init = viewer_init;
	app->update = viewer_update;
	app->shutdown = viewer_shutdown;
	app->on_event = viewer_on_event;
}