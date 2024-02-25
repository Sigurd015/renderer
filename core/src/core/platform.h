#pragma once
#include "defines.h"
#include "event.h"
#include "renderer/image.h"

typedef struct {
	const char* name;
	u32 width;
	u32 height;
	b8 resizable;
	b8 maximizable;
	b8 minimizable;
	b8 full_screen;

	void(*msg_callback)(event e);
} platform_specification;

void platform_init(platform_specification* spec);
void platform_update();
void platform_shutdown();
void* platform_get_window_handle();
u32 platform_get_window_width();
u32 platform_get_window_height();
void platform_set_window_title(const char* title);
f64 platform_get_time();
f64 platform_get_absolute_time();

// Input
void platform_input_update();
b8 platform_is_key(key_code key);
b8 platform_is_key_down(key_code key);
b8 platform_is_mouse_button(mouse_button button);
b8 platform_is_mouse_button_down(mouse_button button);
vec2 platform_get_mouse_position();
void platform_set_cursor(b8 visible);

// Renderer
void platform_present(image* buffer);

// Memory
void platform_zero_memory(void* mem, u64 size);
void* platform_allocate(u64 size, u8 alignment);
void platform_free(void* mem, u8 alignment);
void platform_copy_memory(void* dest, void* src, u64 size);