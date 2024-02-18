#pragma once
#include "image.h"
#include "math/math.h"

void renderer_init();
void renderer_swap_buffers();
void renderer_clear(vec4 color);