#pragma once

#include "core/application.h"
#include "core/log.h"

extern void application_create(application* app, application_command_line_args args);

int entry(int argc, char** argv)
{
	log_init();
	application app = { 0 };
	application_command_line_args args = { argc, argv };
	application_create(&app, args);
	application_init(&app);
	application_run();
	application_shutdown();
	log_shutdown();
	return 0;
}

#ifdef WINDOWS
#ifdef DIST
#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	return entry(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
	return entry(argc, argv);
}

#endif
#endif 