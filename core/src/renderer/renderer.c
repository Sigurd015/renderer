#include "pch.h"
#include "renderer.h"
#include "core/platform.h"

typedef struct {
	image* buffer;
} internal_state;
static internal_state s_state;

void renderer_init(u32 width, u32 height, image_format format)
{
	s_state.buffer = image_create(width, height, format, 0);
}

void renderer_swap_buffers()
{
	platform_present_surface(s_state.buffer);
}

void renderer_clear(vec4 color)
{
	image_fill(s_state.buffer, color);
}

void renderer_shutdown()
{
	image_destroy(s_state.buffer);
}