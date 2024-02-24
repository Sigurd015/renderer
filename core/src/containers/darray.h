#pragma once

#define DARRAY_DEFAULT_CAPACITY 10
#define DARRAY_RESIZE_FACTOR 2

typedef struct {
	u64 capacity;
	u64 length;
	u64 stride;
	void* data;
} darray;

darray* _darray_create(u64 capacity, u64 stride);
void darray_destroy(darray* dary);
darray* darray_resize(darray* dary, u64 new_capacity);
void darray_clear(darray* dary);

darray* darray_push(darray* dary, const void* data);
void darray_pop(darray* dary, void* dest);
void darray_pop_at(darray* dary, u64 index, void* dest);
const void* darray_get(darray* dary, u64 index);
const void* darray_get_data(darray* dary);

u64 darray_get_capacity(darray* dary);
u64 darray_get_length(darray* dary);
u64 darray_get_stride(darray* dary);

#define darray_create(type) \
_darray_create(DARRAY_DEFAULT_CAPACITY, sizeof(type))