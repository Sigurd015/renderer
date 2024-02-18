#include "pch.h"
#include "darray.h"

darray* _daray_create(u64 capacity, u64 stride)
{
	u64 header_size = sizeof(darray);
	u64 data_size = capacity * stride;
	darray* daray = memory_allocate(header_size + data_size, MEMORY_TAG_DARRAY);
	daray->capacity = capacity;
	daray->length = 0;
	daray->stride = stride;
	return daray;
}

void daray_destroy(darray* dary)
{
	u64 header_size = sizeof(darray);
	u64 data_size = dary->capacity * dary->stride + header_size;
	memory_free(dary, data_size, MEMORY_TAG_DARRAY);
}

darray* daray_resize(darray* dary)
{
	u64 length = dary->length;
	u64 stride = dary->stride;
	darray* new_daray = _daray_create(DARRAY_RESIZE_FACTOR * dary->capacity, stride);
	memory_copy(new_daray, dary, length * stride);

	new_daray->length = length;
	daray_destroy(dary);
	return new_daray;
}

void _daray_push(darray* dary, const void* data)
{
	u64 length = dary->length;
	u64 stride = dary->stride;
	if (length >= daray_capacity(dary)) {
		dary = daray_resize(dary);
	}

	u64 address = (u64)dary;
	address += (length * stride);
	memory_copy((void*)address, data, stride);
	dary->length++;
}

void daray_pop(darray* dary, void* dest)
{
	u64 length = dary->length;
	u64 stride = dary->stride;
	u64 address = (u64)dary;
	address += ((length - 1) * stride);
	memory_copy(dest, (void*)address, stride);
	dary->length--;
}

u64 darray_get_capacity(darray* dary)
{
	return dary->capacity;
}

u64 darray_get_length(darray* dary)
{
	return dary->length;
}

u64 darray_get_stride(darray* dary)
{
	return dary->stride;
}