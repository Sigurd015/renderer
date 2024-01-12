#pragma once

// ----- types -----
typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef float f32;
typedef double f64;

typedef u8 byte;

typedef int b32;
typedef char b8;

#define TRUE 1
#define FALSE 0

static_assert(sizeof(i8) == 1, "i8 is not 1 byte");
static_assert(sizeof(i16) == 2, "i16 is not 2 bytes");
static_assert(sizeof(i32) == 4, "i32 is not 4 bytes");
static_assert(sizeof(i64) == 8, "i64 is not 8 bytes");

static_assert(sizeof(u8) == 1, "u8 is not 1 byte");
static_assert(sizeof(u16) == 2, "u16 is not 2 bytes");
static_assert(sizeof(u32) == 4, "u32 is not 4 bytes");
static_assert(sizeof(u64) == 8, "u64 is not 8 bytes");

static_assert(sizeof(f32) == 4, "f32 is not 4 bytes");
static_assert(sizeof(f64) == 8, "f64 is not 8 bytes");

#define BIT(x) (1 << x)