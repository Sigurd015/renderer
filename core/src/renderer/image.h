#pragma once
#include "defines.h"
#include "math/math.h"

typedef enum {
	IMAGE_FORMAT_RGBA,
	IMAGE_FORMAT_ARGB,
	IMAGE_FORMAT_ABGR
} image_format;

typedef struct {
	u32 width;
	u32 height;
	image_format format;
	void* data;
} image;

image* image_create(u32 width, u32 height, image_format format);
u32 image_get_width(image* img);
u32 image_get_height(image* img);
image_format image_get_format(image* img);
void* image_get_data(image* img);
void image_fill(image* img, vec4 color);
void image_copy(image* dest, image* src);
void image_copy_to_data(image* img, void* data);
void image_set_data(image* img, void* data);
void image_destroy(image* img);