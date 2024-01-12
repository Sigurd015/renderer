#pragma once
#include "defines.h"

typedef enum {
	EVENT_TYPE_NONE = 0,
	EVENT_TYPE_WINDOW_CLOSE, 
	EVENT_TYPE_WINDOW_RESIZE,
	EVENT_TYPE_KEY_PRESSED, 
	EVENT_TYPE_KEY_RELEASED, 
	EVENT_TYPE_KEY_TYPED,
	EVENT_TYPE_MOUSE_BUTTON_PRESSED, 
	EVENT_TYPE_MOUSE_BUTTON_RELEASED, 
	EVENT_TYPE_MOUSE_MOVED, 
	EVENT_TYPE_MOUSE_SCROLLED,
	EVENT_TYPE_COUNT
} event_type;

typedef struct {
	u32 width;
	u32 height;
} wnd_resize_event;
typedef struct {
	f32 x;
	f32 y;
} mouse_moved_event;
typedef struct {
	f32 yOffset;
	f32 padding;
} mouse_scrolled_event;

typedef struct {
	union
	{
		wnd_resize_event wnd_resize;
		mouse_moved_event mouse_moved;
		mouse_scrolled_event mouse_scrolled;
	};
} event_context;

typedef struct {
	event_type type;
	b8 handled;
	event_context context;
} event;

typedef b8(*event_callback)(event e);

void event_dispatcher(event_type type, event* event, event_callback callback);
event event_create(event_type type, event_context context);