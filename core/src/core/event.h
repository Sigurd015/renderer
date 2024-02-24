#pragma once
#include "defines.h"
#include "input/keycode.h"

typedef enum {
	EVENT_TYPE_NONE = 0,
	EVENT_TYPE_WINDOW_CLOSE,
	EVENT_TYPE_WINDOW_RESIZE,
	EVENT_TYPE_KEY_PRESSED,
	EVENT_TYPE_KEY_RELEASED,
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
	f32 zDelta;
	f32 padding;
} mouse_scrolled_event;
typedef struct {
	mouse_button button;
	f32 padding;
} mouse_button_pressed_event;
typedef struct {
	mouse_button button;
	f32 padding;
} mouse_button_released_event;
typedef struct {
	key_code key;
	b8 repeat;
	b8 padding[3];
} key_pressed_event;
typedef struct {
	key_code key;
	f32 padding;
} key_released_event;

typedef struct {
	union
	{
		wnd_resize_event wnd_resize;
		mouse_moved_event mouse_moved;
		mouse_scrolled_event mouse_scrolled;
		mouse_button_pressed_event mouse_button_pressed;
		mouse_button_released_event mouse_button_released;
		key_pressed_event key_pressed;
		key_released_event key_released;
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