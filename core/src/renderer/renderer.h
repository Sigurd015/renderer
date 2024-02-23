#pragma once
#include "image.h"
#include "math/math.h"

void renderer_init(u32 width, u32 height, image_format format);
void renderer_swap_buffers();
void renderer_clear(vec4 color);
void renderer_shutdown();