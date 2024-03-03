#pragma once
#include "component.h"

typedef struct {
	transform_component transform;
	
	void* components[COMPONENT_COUNT];
} entity;

void entity_create(entity* e);
void entity_destroy(entity* e);
void entity_has_component(entity* e, component_type type);
void entity_add_component(entity* e, component_type type, void* component);
void entity_remove_component(entity* e, component_type type);