#include "pch.h"
#include "image.h"

image* image_create(u32 width, u32 height)
{
	u64 header_size = sizeof(image);
	u64 data_size = width * height * 4;
	image* img = memory_allocate(header_size + data_size, MEMORY_TAG_IMAGE);
	img->width = width;
	img->height = height;
	return img;
}

u32 image_get_width(image* img)
{
	return img->width;
}
u32 image_get_height(image* img)
{
	return img->height;
}

void* image_get_data(image* img)
{
	return (void*)((byte*)img + sizeof(image));
}

void image_copy(image* dest, image* src)
{
	CORE_ASSERT(dest->width == src->width && dest->height == src->height, "image_copy - Images must have the same dimensions");

	memory_copy(image_get_data(dest), image_get_data(src), dest->width * dest->height * 4);
}

void image_set_data(image* img, void* data)
{
	memory_copy(image_get_data(img), data, img->width * img->height * 4);
}

void image_destroy(image* img)
{
	memory_free(img, sizeof(image) + img->width * img->height * 4, MEMORY_TAG_IMAGE);
}