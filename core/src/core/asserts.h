#pragma once

#include "core/log.h"

#ifdef WINDOWS
#define DEBUGBREAK() __debugbreak()
#elif defined(MACOS)
//TODO: Implement debugbreak for mac
#else
#error "Platform doesn't support debugbreak yet!"
#endif

#ifndef DIST
#ifdef DEBUG
#define CORE_ASSERT(expr,format, ...) {if(!(expr)){DEBUGBREAK();}}
#else
#define CORE_ASSERT(expr,format, ...) {if(!(expr)){CORE_LOG_ERROR(format, ##__VA_ARGS__);}}
#endif 
#else
#define CORE_ASSERT(expr,format, ...)
#endif