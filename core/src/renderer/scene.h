#pragma once
#include "defines.h"
#include "math/math.h"
#include "containers/darray.h"

typedef struct {
	vec3 position;
} vertex;

typedef struct {
	u32 indices[3];
} index;

typedef struct {
	vertex vertices[3];
} triangle;

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
	// For ray tracing, currently only supports spheres
	darray* spheres;

	// For rasterization, may move to mesh when implemented mesh support
	darray* triangles;
	darray* materials;
} scene;