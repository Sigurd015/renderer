#pragma once
#include "defines.h"
#include "event.h"

typedef struct {
	char* name;
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