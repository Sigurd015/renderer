#include "pch.h"
#include "memory.h"
#include "platform.h"

typedef struct {
	u64 total_allocated;
	u64 tagged_allocated[MEMORY_TAG_COUNT];
} memory_stats;
static memory_stats s_stats;

void memory_init()
{
	platform_zero_memory(&s_stats, sizeof(s_stats));
}

void memory_shutdown()
{

}

void* memory_allocate(u64 size, memory_tag tag)
{
	CORE_ASSERT(tag != MEMORY_TAG_UNKNOWN, "memory_alloc - Tag not implemented");

	s_stats.total_allocated += size;
	s_stats.tagged_allocated[tag] += size;

	// TODO: Implement memory alignment
	void* block = platform_allocate(size, FALSE);
	platform_zero_memory(block, size);
	return block;
}

void memory_free(void* block, u64 size, memory_tag tag)
{
	CORE_ASSERT(tag != MEMORY_TAG_UNKNOWN, "memory_free - Tag not implemented");

	s_stats.total_allocated -= size;
	s_stats.tagged_allocated[tag] -= size;

	platform_free(block, FALSE);
}

void memory_zero(void* block, u64 size)
{
	platform_zero_memory(block, size);
}

void memory_copy(void* dest, void* src, u64 size)
{
	platform_copy_memory(dest, src, size);
}