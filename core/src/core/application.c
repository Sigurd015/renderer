#include "pch.h"
#include "application.h"
#include "renderer/renderer.h"

typedef struct {
	application* app;

	b8 running;
	f64 last_frame_time;
} internal_state;
static internal_state s_state;

b8 on_wnd_close(event* e)
{
	application_close();
	return TRUE;
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

	memory_init();

	app->application_spec.platform_spec.msg_callback = on_event;
	platform_init(&app->application_spec.platform_spec);

	app->init();

	s_state.running = TRUE;
}

void application_run()
{
	while (s_state.running)
	{
		f64 time = platform_get_time();
		f64 delta_time = time - s_state.last_frame_time;
		s_state.last_frame_time = time;

		s_state.app->update(delta_time);

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

	// Notice renderer_init is called in platform_init
	renderer_shutdown();
	platform_shutdown();

	memory_shutdown();
}