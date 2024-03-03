#include "pch.h"
#include "scene.h"

void scene_create(scene* s)
{
	s->materials = darray_create(material);
	s->spheres = darray_create(sphere);
	s->entities = darray_create(entity);
}

void scene_destroy(scene* s)
{
	darray_destroy(s->materials);
	darray_destroy(s->spheres);

	// Destroy entities
	for (u32 i = 0; i < darray_get_length(s->entities); i++)
	{
		entity_destroy(darray_get(s->entities, i));
	}
	darray_destroy(s->entities);
}

void scene_add_entity(scene* s, entity* e)
{
	s->entities = darray_push(s->entities, e);
}