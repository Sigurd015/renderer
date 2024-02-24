#pragma once
#include "defines.h"
#include "math/math.h"
#include "containers/darray.h"

// TODO: temporary
typedef struct {
	vec3 albedo;
	f32 metallic;
	f32 roughness;
	vec3 emission_color;
	f32 emission_power;
} material;

typedef struct {
	vec3 position;
	f32 radius;

	u32 material_index;
} sphere;

typedef struct {
	darray* spheres;
	darray* materials;
} scene;