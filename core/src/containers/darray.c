#include "pch.h"
#include "darray.h"

void* _daray_create(u64 capacity, u64 stride)
{
	u64 header_size = DARAY_FILED_COUNT * sizeof(u64);
	u64 data_size = capacity * stride;
	u64* daray = memory_allocate(header_size + data_size, MEMORY_TAG_DARRAY);
	memory_zero(daray, header_size + data_size);
	daray[DARAY_CAPACITY] = capacity;
	daray[DARAY_STRIDE] = stride;
	daray[DARAY_LENGTH] = 0;
	return daray + DARAY_FILED_COUNT;
}

void daray_destroy(void* daray)
{
	u64* header = (u64*)daray - DARAY_FILED_COUNT;
	u64 header_size = DARAY_FILED_COUNT * sizeof(u64);
	u64 data_size = header[DARAY_CAPACITY] * header[DARAY_STRIDE] + header_size;
	memory_free(header, data_size, MEMORY_TAG_DARRAY);
}

void daray_set(void* daray, u64 field, u64 value)
{
	u64* header = (u64*)daray - DARAY_FILED_COUNT;
	header[field] = value;
}

void* daray_resize(void* daray)
{
	u64 length = daray_length(daray);
	u64 stride = daray_stride(daray);
	void* new_daray = _daray_create(DARAY_RESIZE_FACTOR * daray_capacity(daray), stride);
	memory_copy(new_daray, daray, length * stride);

	daray_set(new_daray, DARAY_LENGTH, length);
	daray_destroy(daray);
	return new_daray;
}

void _daray_push(void* daray, const void* data)
{
	u64 length = daray_length(daray);
	u64 stride = daray_stride(daray);
	if (length >= daray_capacity(daray)) {
		daray = daray_resize(daray);
	}

	u64 address = (u64)daray;
	address += (length * stride);
	memory_copy((void*)address, data, stride);
	daray_set(daray, DARAY_LENGTH, length + 1);
}

void daray_pop(void* daray, void* dest)
{
	u64 length = daray_length(daray);
	u64 stride = daray_stride(daray);
	u64 address = (u64)daray;
	address += ((length - 1) * stride);
	memory_copy(dest, (void*)address, stride);
	daray_set(daray, DARAY_LENGTH, length - 1);
}

u64 _daray_get(void* daray, u64 field)
{
	u64* header = (u64*)daray - DARAY_FILED_COUNT;
	return header[field];
}