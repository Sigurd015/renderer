#include "pch.h"
#include "darray.h"

darray* _darray_create(u64 capacity, u64 stride)
{
	u64 header_size = sizeof(darray);
	u64 data_size = capacity * stride;
	darray* darray = memory_allocate(header_size + data_size, MEMORY_TAG_DARRAY);
	darray->capacity = capacity;
	darray->length = 0;
	darray->stride = stride;
	darray->data = (void*)((byte*)darray + header_size);
	return darray;
}

void darray_destroy(darray* dary)
{
	memory_free(dary, dary->capacity * dary->stride + sizeof(darray), MEMORY_TAG_DARRAY);
}

// Notice dont forget the return value, the pointer to the array is changed
darray* darray_resize(darray* dary, u64 new_capacity)
{
	u64 stride = dary->stride;
	darray_destroy(dary);
	return _darray_create(new_capacity, stride);
}

void darray_clear(darray* dary)
{
	dary->length = 0;
}

// Notice dont forget the return value, when resize is called, the pointer to the array is changed
darray* darray_push(darray* dary, const void* data)
{
	u64 length = dary->length;
	u64 stride = dary->stride;
	u64 capacity = dary->capacity;

	void* dest = (void*)((byte*)dary->data + (length * stride));
	darray* ary = dary;
	if (length >= capacity) {
		ary = _darray_create(DARRAY_RESIZE_FACTOR * capacity, stride);
		memory_copy(ary->data, dary->data, length * stride);

		ary->length = length;
		darray_destroy(dary);

		dest = (void*)((byte*)ary->data + (length * stride));
	}

	memory_copy(dest, data, stride);
	ary->length++;
	return ary;
}

void darray_pop(darray* dary, void* dest)
{
	u64 length = dary->length;
	u64 stride = dary->stride;
	CORE_ASSERT(length > 0, "darray_pop - Array is empty");

	memory_copy(dest, (void*)((byte*)dary->data + (length * stride)), stride);
	dary->length--;
}

void darray_pop_at(darray* dary, u64 index, void* dest)
{
	u64 length = dary->length;
	u64 stride = dary->stride;
	CORE_ASSERT(index < length, "darray_pop_at - Index out of bounds");

	void* data_ptr = (void*)((byte*)dary->data + (index * stride));
	memory_copy(dest, data_ptr, stride);
	memory_copy(data_ptr, (void*)((byte*)data_ptr + stride), (length - index) * stride);
	dary->length--;
}

const void* darray_get(darray* dary, u64 index)
{
	u64 length = dary->length;
	u64 stride = dary->stride;
	CORE_ASSERT(index < length, "darray_get - Index out of bounds");

	return (void*)((byte*)dary->data + (index * stride));
}

const void* darray_get_data(darray* dary)
{
	return dary->data;
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