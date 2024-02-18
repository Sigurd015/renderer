#pragma once
#include "defines.h"

typedef struct {
    u32 width;
    u32 height;
} image;

image* image_create(u32 width, u32 height);
u32 image_get_width(image* img);
u32 image_get_height(image* img);
void* image_get_data(image* img);
void image_copy(image* dest, image* src);
void image_set_data(image* img, void* data);
void image_destroy(image* img);