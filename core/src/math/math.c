#include "pch.h"
#include "math.h"

#include <math.h>
#include <stdlib.h>

b8 rand_seeded = FALSE;

void set_seed()
{
	if (!rand_seeded) {
		srand((u32)platform_get_absolute_time());
		rand_seeded = TRUE;
	}
}

i32 i32_random()
{
	set_seed();
	return rand();
}

i32 i32_random_range(i32 min, i32 max)
{
	set_seed();
	return rand() % (max - min + 1) + min;
}

f32 f32_sqrt(f32 f)
{
	return sqrtf(f);
}

f32 f32_clamp(f32 f, f32 min, f32 max)
{
	if (f < min) return min;
	if (f > max) return max;
	return f;
}

f32 f32_sin(f32 f)
{
	return sinf(f);
}

f32 f32_cos(f32 f)
{
	return cosf(f);
}

f32 f32_tan(f32 f)
{
	return tanf(f);
}

f32 f32_random()
{
	return (f32)i32_random() / (f32)RAND_MAX;
}

f32 f32_random_range(f32 min, f32 max)
{
	return min + ((f32)i32_random() / (f32)RAND_MAX) * (max - min);
}