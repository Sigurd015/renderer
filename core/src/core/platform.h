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
f64 platform_get_time();

void platform_present_surface(image* surface);

// Memory
void platform_zero_memory(void* mem, u64 size);
void* platform_allocate(u64 size, u8 alignment);
void platform_free(void* mem, u8 alignment);
void platform_copy_memory(void* dest, void* src, u64 size);