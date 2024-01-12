#include "pch.h"
#include "event.h"

void event_dispatcher(event_type type, event* e, event_callback callback)
{
	if (e->type == type)
	{
		e->handled |= callback(*e);
	}
}

event event_create(event_type type, event_context context)
{
	event e;
	e.type = type;
	e.context = context;
	e.handled = FALSE;
	return e;
}