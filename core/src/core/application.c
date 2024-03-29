#include "pch.h"
#include "application.h"
#include "renderer/renderer.h"

typedef struct {
	application* app;

	b8 running;
	b8 minimized;
	f64 last_frame_time;

	u64 fps;
	f64 frame_count_time;
} internal_state;
static internal_state s_state;

b8 on_wnd_close(event e)
{
	application_close();
	return TRUE;
}

b8 on_wnd_resize(event e)
{
	if (e.context.wnd_resize.width == 0 || e.context.wnd_resize.height == 0)
	{
		s_state.minimized = TRUE;
		return TRUE;
	}
	else
	{
		s_state.minimized = FALSE;
		renderer_resize(e.context.wnd_resize.width, e.context.wnd_resize.height);
		return FALSE;
	}
}

void on_event(event e)
{
	event_dispatcher(EVENT_TYPE_WINDOW_CLOSE, &e, on_wnd_close);
	event_dispatcher(EVENT_TYPE_WINDOW_RESIZE, &e, on_wnd_resize);

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
	s_state.minimized = FALSE;
}

void application_run()
{
	while (s_state.running)
	{
		f64 time = platform_get_time();
		f64 delta_time = time - s_state.last_frame_time;
		s_state.last_frame_time = time;

		platform_input_update();

		if (!s_state.minimized)
			s_state.app->update(delta_time);

		platform_update();

		// Display the frame
		{
			s_state.frame_count_time += delta_time;
			s_state.fps++;
			
			if (s_state.frame_count_time >= 1.0)
			{
				char temp[256];
				string_format(temp, 256, "FPS: %d", s_state.fps);
				platform_set_window_title(temp);
				CORE_LOG_INFO("FPS: %d", s_state.fps);
				s_state.frame_count_time = 0.0;
				s_state.fps = 0.0;
			}
		}	
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