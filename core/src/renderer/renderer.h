#pragma once
#include "image.h"
#include "math/math.h"
#include "scene.h"
#include "camera.h"

void renderer_init(u32 width, u32 height, u32_color_type format);
void renderer_swap_buffers();
void renderer_clear(vec4 color);
void renderer_shutdown();

// TODO: temporary
void renderer_draw(scene* scene, camera* cam);
void renderer_reset_frame_count();