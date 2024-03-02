#pragma once
#include "image.h"
#include "scene.h"
#include "camera.h"

void renderer_init(u32 width, u32 height, image_format format);
void renderer_swap_buffers();
void renderer_set_clear_color(vec4 color);
void renderer_clear();
void renderer_shutdown();

// --- Rasterization pipeline ---
void renderer_draw(scene* scene, camera* cam);
// ------------------------------

// --- Ray tracing pipeline ---
void renderer_rt_draw(scene* scene, camera* cam);
void renderer_reset_frame_count();
// ----------------------------