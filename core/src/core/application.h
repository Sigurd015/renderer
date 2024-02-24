#pragma once
#include "defines.h"
#include "platform.h"
#include "event.h"

typedef struct {
	int count;
	char** args;
} command_line_args;

typedef struct {
	platform_specification platform_spec;
	command_line_args command_line_args;
} application_specification;

typedef struct {
	application_specification application_spec;

	void(*init)();
	void(*shutdown)();
	void(*update)(float delta_time);
	void(*on_event)(event e);
} application;

void application_init(application* app);
void application_run();
void application_close();
void application_shutdown();