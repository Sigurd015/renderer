#include "pch.h"
#include "log.h"

#include <stdio.h>
#include <stdarg.h>

#define LOG_BUFFER_SIZE 256

FILE* log_file = NULL;

void log_init()
{
#ifdef DIST
	log_file = fopen("log.txt", "w");
#endif 
}

void log_shutdown()
{
	if (log_file != NULL)
	{
		fclose(log_file);
		log_file = NULL;
	}
}

void log_to_console(log_level level, const char* type, const char* message)
{
	switch (level)
	{
	case LOG_LEVEL_ERROR:
		printf("\033[31m>%s-[ERROR]: %s\n\033[0m", type, message);
		break;
	case LOG_LEVEL_WARN:
		printf("\033[33m>%s-[WARN]: %s\n\033[0m", type, message);
		break;
	case LOG_LEVEL_INFO:
		printf("\033[32m>%s-[INFO]: %s\n\033[0m", type, message);
		break;
	}
}

void log_output(log_level level, const char* type, const char* format, ...)
{
	const char* level_strings[] = { "ERROR", "WARN", "INFO" };

	va_list args;
	va_start(args, format);
	char logMessage[LOG_BUFFER_SIZE];
	vsnprintf(logMessage, LOG_BUFFER_SIZE, format, args);
	va_end(args);
	
#ifdef DIST
	fprintf(log_file, ">%s-%s: %s\n", type, level_strings[level], logMessage);
#else
	log_to_console(level, type, logMessage);
#endif
}