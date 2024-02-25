#include "pch.h"
#include "string.h"

#include <string.h>
#include <stdarg.h>
#include <stdio.h>

void string_format(char* buffer, u64 buffer_size, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	vsnprintf(buffer, buffer_size, format, args);
	va_end(args);
}