#pragma once
#include "defines.h"
#include "math/math.h"

typedef struct {
	u32 width;
	u32 height;
	u32_color_type format;
	void* data;
} image;

image* image_create(u32 width, u32 height, u32_color_type format);
u32 image_get_width(image* img);
u32 image_get_height(image* img);
u32_color_type image_get_format(image* img);
void* image_get_data(image* img);
void image_fill(image* img, vec4 color);
void image_copy(image* dest, image* src);
void image_copy_to_data(image* img, void* data);
void image_set_data(image* img, void* data);
void image_set_pixel(image* img, u32 index, vec4 color);
void image_destroy(image* img);