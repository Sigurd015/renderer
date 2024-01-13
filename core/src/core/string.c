#include "pch.h"
#include "string.h"

#include <string.h>

u64 string_length(const char* str)
{
	return strlen(str);
}

char* string_duplicate(const char* str)
{
	u64 len = string_length(str);
	char* str2 = memory_allocate(len + 1, MEMORY_TAG_STRING);
	memory_copy(str2, str, len + 1);
	return str2;
}