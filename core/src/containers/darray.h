#pragma once

#define DARAY_DEFAULT_CAPACITY 10
#define DARAY_RESIZE_FACTOR 2

enum {
	DARAY_CAPACITY,
	DARAY_LENGTH,
	DARAY_STRIDE,
	DARAY_FILED_COUNT
};

void* _daray_create(u64 capacity, u64 stride);
void daray_destroy(void* daray);

void _daray_push(void* daray, const void* data);
void daray_pop(void* daray, void* dest);

u64 _daray_get(void* daray, u64 field);

#define daray_create(type) \
_daray_create(DARAY_DEFAULT_CAPACITY, sizeof(type))

#define daray_push(daray, data) \
{ \
	typeof(data) temp = data; \
	_daray_push(daray, &temp); \
}

#define daray_capacity(daray) \
_daray_get(daray, DARAY_CAPACITY)

#define daray_length(daray) \
_daray_get(daray, DARAY_LENGTH)

#define daray_stride(daray) \
_daray_get(daray, DARAY_STRIDE)