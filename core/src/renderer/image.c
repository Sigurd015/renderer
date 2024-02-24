#include "pch.h"
#include "image.h"

image* image_create(u32 width, u32 height, image_format format)
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

image_format image_get_format(image* img)
{
	return img->format;
}

void* image_get_data(image* img)
{
	return img->data;
}

void image_flip_vertically(image* img)
{
	u32* data = (u32*)image_get_data(img);
	for (u32 y = 0; y < img->height / 2; y++)
	{
		for (u32 x = 0; x < img->width; x++)
		{
			u32 index1 = y * img->width + x;
			u32 index2 = (img->height - y - 1) * img->width + x;
			u32 temp = data[index1];
			data[index1] = data[index2];
			data[index2] = temp;
		}
	}
}

void image_flip_horizontally(image* img)
{
	u32* data = (u32*)image_get_data(img);
	for (u32 y = 0; y < img->height; y++)
	{
		for (u32 x = 0; x < img->width / 2; x++)
		{
			u32 index1 = y * img->width + x;
			u32 index2 = y * img->width + (img->width - x - 1);
			u32 temp = data[index1];
			data[index1] = data[index2];
			data[index2] = temp;
		}
	}
}

u32 get_u32_color_by_format(vec4 color, image_format format)
{
	switch (format)
	{
	case IMAGE_FORMAT_ABGR: return vec4_to_abgr_u32(color);
	case IMAGE_FORMAT_ARGB: return vec4_to_argb_u32(color);
	case IMAGE_FORMAT_RGBA: return vec4_to_rgba_u32(color);
	}
	return 0;
}

void image_fill(image* img, vec4 color)
{
	u32 color_u32 = get_u32_color_by_format(color, img->format);
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
			case IMAGE_FORMAT_ABGR:
			{
				src_a = src_data[i * 4 + 0];
				src_b = src_data[i * 4 + 1];
				src_g = src_data[i * 4 + 2];
				src_r = src_data[i * 4 + 3];
				break;
			}
			case IMAGE_FORMAT_ARGB:
			{
				src_a = src_data[i * 4 + 0];
				src_r = src_data[i * 4 + 1];
				src_g = src_data[i * 4 + 2];
				src_b = src_data[i * 4 + 3];
				break;
			}
			case IMAGE_FORMAT_RGBA:
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
			case IMAGE_FORMAT_ABGR:
			{
				dest_data[i * 4 + 0] = src_a;
				dest_data[i * 4 + 1] = src_b;
				dest_data[i * 4 + 2] = src_g;
				dest_data[i * 4 + 3] = src_r;
				break;
			}
			case IMAGE_FORMAT_ARGB:
			{
				dest_data[i * 4 + 0] = src_a;
				dest_data[i * 4 + 1] = src_r;
				dest_data[i * 4 + 2] = src_g;
				dest_data[i * 4 + 3] = src_b;
				break;
			}
			case IMAGE_FORMAT_RGBA:
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

	u32 color_u32 = get_u32_color_by_format(color, img->format);
	byte* data = (byte*)image_get_data(img);
	*(u32*)(data + index * 4) = color_u32;
}

void image_destroy(image* img)
{
	memory_free(img, sizeof(image) + img->width * img->height * 4, MEMORY_TAG_IMAGE);
}