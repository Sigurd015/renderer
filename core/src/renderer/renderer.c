#include "pch.h"
#include "renderer.h"
#include "core/platform.h"

typedef struct {
	image* backbuffer;
	image* frontbuffer;

} internal_state;
static internal_state s_state;

void renderer_init()
{
	s_state.backbuffer = platform_create_surface();
	s_state.frontbuffer = image_create(image_get_width(s_state.backbuffer), image_get_height(s_state.backbuffer));
}

void renderer_swap_buffers()
{
	image_copy(s_state.backbuffer, s_state.frontbuffer);
	platform_present_surface(s_state.backbuffer);
}

void renderer_clear(vec4 color)
{
	byte* pixel = (byte*)image_get_data(s_state.frontbuffer);

	u32 color_u32 = vec4_to_u32(color);
	for (u32 y = 0; y < image_get_height(s_state.frontbuffer); ++y)
	{
		for (u32 x = 0; x < image_get_width(s_state.frontbuffer); ++x)
		{
			*(u32*)pixel = color_u32;
			pixel += 4;
		}
	}
}