#pragma once
#include "defines.h"
#include "math/math.h"
#include "containers/darray.h"

typedef enum {
	COMPONENT_TRANSFORM,
	COMPONENT_MESH,
	COMPONENT_COUNT
} component_type;

typedef struct {
	vec3 position;
	vec3 rotation;
	vec3 scale;
} transform_component;

mat4 transform_get_matrix(transform_component* t);

typedef struct {
	// TODO: may move to mesh when implemented mesh support
	darray* triangles;
} mesh_component;