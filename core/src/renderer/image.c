#include "pch.h"
#include "image.h"

image* image_create(u32 width, u32 height, u32_color_type format)
{
	u64 header_size = sizeof(image);
	u64 data_size = width * height * 4;
	image* img = memory_allocate(header_size + data_size, MEMORY_TAG_IMAGE);
	img->data = (void*)((byte*)img + header_size);
	img->format = format;
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

u32_color_type image_get_format(image* img)
{
	return img->format;
}

void* image_get_data(image* img)
{
	return img->data;
}

void image_fill(image* img, vec4 color)
{
	u32 color_u32 = vec4_to_u32(color, img->format);
	byte* data = (byte*)image_get_data(img);
	for (u32 i = 0; i < img->width * img->height; i++)
	{
		*(u32*)(data + i * 4) = color_u32;
	}
}

void image_copy(image* dest, image* src)
{
	CORE_ASSERT(dest->width == src->width && dest->height == src->height, "image_copy - Images must have the same dimensions");

	if (dest->format == src->format)
		memory_copy(image_get_data(dest), image_get_data(src), dest->width * dest->height * 4);
	else
	{
		byte* src_data = (byte*)image_get_data(src);
		byte* dest_data = (byte*)image_get_data(dest);
		for (u32 i = 0; i < src->width * src->height; i++)
		{
			u8 src_r = 0, src_g = 0, src_b = 0, src_a = 0;

			switch (src->format)
			{
			case U32_COLOR_TYPE_ABGR:
			{
				src_a = src_data[i * 4 + 0];
				src_b = src_data[i * 4 + 1];
				src_g = src_data[i * 4 + 2];
				src_r = src_data[i * 4 + 3];
				break;
			}
			case U32_COLOR_TYPE_ARGB:
			{
				src_a = src_data[i * 4 + 0];
				src_r = src_data[i * 4 + 1];
				src_g = src_data[i * 4 + 2];
				src_b = src_data[i * 4 + 3];
				break;
			}
			case U32_COLOR_TYPE_RGBA:
			{
				src_r = src_data[i * 4 + 0];
				src_g = src_data[i * 4 + 1];
				src_b = src_data[i * 4 + 2];
				src_a = src_data[i * 4 + 3];
				break;
			}
			}

			switch (dest->format)
			{
			case U32_COLOR_TYPE_ABGR:
			{
				dest_data[i * 4 + 0] = src_a;
				dest_data[i * 4 + 1] = src_b;
				dest_data[i * 4 + 2] = src_g;
				dest_data[i * 4 + 3] = src_r;
				break;
			}
			case U32_COLOR_TYPE_ARGB:
			{
				dest_data[i * 4 + 0] = src_a;
				dest_data[i * 4 + 1] = src_r;
				dest_data[i * 4 + 2] = src_g;
				dest_data[i * 4 + 3] = src_b;
				break;
			}
			case U32_COLOR_TYPE_RGBA:
			{
				dest_data[i * 4 + 0] = src_r;
				dest_data[i * 4 + 1] = src_g;
				dest_data[i * 4 + 2] = src_b;
				dest_data[i * 4 + 3] = src_a;
				break;
			}
			}
		}
	}
}

// Notice data format should be the same as the image format
void image_copy_to_data(image* img, void* data)
{
	memory_copy(data, image_get_data(img), img->width * img->height * 4);
}

// Notice data format should be the same as the image format
void image_set_data(image* img, void* data)
{
	memory_copy(image_get_data(img), data, img->width * img->height * 4);
}

void image_set_pixel(image* img, u32 index, vec4 color)
{
	CORE_ASSERT(index < img->width * img->height, "image_set_pixel - Index out of bounds");

	u32 color_u32 = vec4_to_u32(color, img->format);
	byte* data = (byte*)image_get_data(img);
	*(u32*)(data + index * 4) = color_u32;
}

void image_destroy(image* img)
{
	memory_free(img, sizeof(image) + img->width * img->height * 4, MEMORY_TAG_IMAGE);
}