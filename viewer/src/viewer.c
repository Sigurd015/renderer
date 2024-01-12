#include "core.h"
#include "entry.h"

void viewer_init()
{
	APP_LOG_ERROR("Viewer init - %d", 1);
	APP_LOG_WARN("Viewer init- %d", 2);
	APP_LOG_INFO("Viewer init- %d", 3);
}

void viewer_update(float deltatime)
{
	APP_LOG_ERROR("Viewer update - %f", deltatime);
	APP_LOG_WARN("Viewer update - %f", deltatime);
	APP_LOG_INFO("Viewer update - %f", deltatime);
}

void viewer_shutdown()
{
	APP_LOG_ERROR("Viewer shutdown - %d", 1);
	APP_LOG_WARN("Viewer shutdown - %d", 2);
	APP_LOG_INFO("Viewer shutdown - %d", 3);
}

void viewer_on_event(event e)
{
	APP_LOG_ERROR("Viewer event - %d", 1);
	APP_LOG_WARN("Viewer event - %d", 2);
	APP_LOG_INFO("Viewer event - %d", 3);
}

void application_create(application* app, application_command_line_args args)
{
	app->application_spec.platform_spec.name = "viewer";
	app->application_spec.platform_spec.width = 1920;
	app->application_spec.platform_spec.height = 1080;
	app->application_spec.platform_spec.resizable = TRUE;
	app->application_spec.platform_spec.maximizable = TRUE;
	app->application_spec.platform_spec.minimizable = TRUE;
	app->application_spec.command_line_args = args;
	app->init = viewer_init;
	app->update = viewer_update;
	app->shutdown = viewer_shutdown;
	app->on_event = viewer_on_event;
}