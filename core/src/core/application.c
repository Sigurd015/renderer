#include "pch.h"
#include "application.h"

typedef struct {
	application* app;

	b8 running;
} internal_state;
static internal_state s_state;

void on_wnd_close(event* e)
{
	application_close();
}

void on_event(event e)
{
	event_dispatcher(EVENT_TYPE_WINDOW_CLOSE, &e, on_wnd_close);

	if (!e.handled)
		s_state.app->on_event(e);
}

void application_init(application* app)
{
	s_state.app = app;

	app->application_spec.platform_spec.msg_callback = on_event;
	platform_init(&app->application_spec.platform_spec);

	app->init();

	s_state.running = TRUE;
}

void application_run()
{
	while (s_state.running)
	{
		s_state.app->update(0.0f);

		platform_update();
	}
}

void application_close()
{
	s_state.running = FALSE;
}

void application_shutdown()
{
	s_state.app->shutdown();

	platform_shutdown();
}