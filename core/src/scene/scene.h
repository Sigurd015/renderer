#pragma once
#include "defines.h"
#include "math/math.h"
#include "containers/darray.h"
#include "scene/entity.h"

typedef struct {
	vec3 position;
} vertex;

typedef struct {
	u32 indices[3];
} index;

typedef struct {
	vertex vertices[3];
} triangle;

// TODO: Temporarily for ray tracing
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
	// TODO: Temporarily for ray tracing
	darray* spheres;

	darray* entities;
	darray* materials;
} scene;

void scene_create(scene* s);
void scene_destroy(scene* s);
void scene_add_entity(scene* s, entity* e);