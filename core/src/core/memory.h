#pragma once

typedef enum {
	MEMORY_TAG_UNKNOWN,
	MEMORY_TAG_ARRAY,
	MEMORY_TAG_DARRAY,
	MEMORY_TAG_STRING,
	MEMORY_TAG_IMAGE,
	MEMORY_TAG_COUNT
} memory_tag;

void memory_init();
void memory_shutdown();
void* memory_allocate(u64 size, memory_tag tag);
void memory_free(void* block, u64 size, memory_tag tag);
void memory_zero(void* block, u64 size);
void memory_copy(void* dest, void* src, u64 size);