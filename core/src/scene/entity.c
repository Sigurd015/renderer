#include "pch.h"
#include "entity.h"

static u32 s_component_sizes[COMPONENT_COUNT] = {
	sizeof(transform_component),
	sizeof(mesh_component),
};

void entity_create(entity* e)
{
	memory_zero(e, sizeof(entity));
}

void entity_destroy(entity* e)
{
	for (u32 j = 0; j < COMPONENT_COUNT; j++)
	{
		entity_remove_component(e, j);
	}
}

void entity_has_component(entity* e, component_type type)
{
	return e->components[type] != 0;
}

void entity_add_component(entity* e, component_type type, void* component)
{
	if (type == COMPONENT_TRANSFORM)
	{
		e->transform = *(transform_component*)component;
		return;
	}

	if (e->components[type])
	{
		memory_free(e->components[type], s_component_sizes[type], MEMORY_TAG_COMPONENT);
	}

	e->components[type] = memory_allocate(s_component_sizes[type], MEMORY_TAG_COMPONENT);
	memory_copy(e->components[type], component, s_component_sizes[type]);
}

void entity_remove_component(entity* e, component_type type)
{
	if (type == COMPONENT_TRANSFORM)
		return;

	if (e->components[type])
	{
		memory_free(e->components[type], s_component_sizes[type], MEMORY_TAG_COMPONENT);
		e->components[type] = 0;
	}
}