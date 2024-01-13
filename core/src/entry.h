#pragma once

#include "core/application.h"
#include "core/log.h"

extern void application_create(application* app);

int entry(int argc, char** argv)
{
	log_init();
	application app = { 0 };
	app.application_spec.command_line_args.args = argv;
	app.application_spec.command_line_args.count = argc;
	application_create(&app);
	application_init(&app);
	application_run();
	application_shutdown();
	log_shutdown();
	return 0;
}

#ifdef DIST
#ifdef WINDOWS
#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	return entry(__argc, __argv);
}

#elif defined(MACOS)

// TODO: Implement entry point for mac

#endif
#else

int main(int argc, char** argv)
{
	return entry(argc, argv);
}

#endif