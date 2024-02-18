#pragma once

#define DARRAY_DEFAULT_CAPACITY 10
#define DARRAY_RESIZE_FACTOR 2

typedef struct {
	u64 capacity;
	u64 length;
	u64 stride;
} darray;

darray* _darray_create(u64 capacity, u64 stride);
void darray_destroy(darray* dary);

void _darray_push(darray* dary, const void* data);
void darray_pop(darray* dary, void* dest);

u64 darray_get_capacity(darray* dary);
u64 darray_get_length(darray* dary);
u64 darray_get_stride(darray* dary);

#define darray_create(type) \
_darray_create(DARRAY_DEFAULT_CAPACITY, sizeof(type))

#define darray_push(dary, data) \
{ \
	typeof(data) temp = data; \
	_darray_push(dary, &temp); \
}