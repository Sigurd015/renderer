#pragma once

typedef enum log_level {
	LOG_LEVEL_ERROR = 0,
	LOG_LEVEL_WARN = 1,
	LOG_LEVEL_INFO = 2,
} log_level;

void log_init();
void log_shutdown();

void log_output(log_level level, const char* type, const char* format, ...);

#define CORE_LOG_ERROR(format, ...) log_output(LOG_LEVEL_ERROR, "[CORE]", format, ##__VA_ARGS__);
#define CORE_LOG_WARN(format, ...) log_output(LOG_LEVEL_WARN, "[CORE]", format, ##__VA_ARGS__);
#define CORE_LOG_INFO(format, ...) log_output(LOG_LEVEL_INFO, "[CORE]", format, ##__VA_ARGS__);

#define APP_LOG_ERROR(format, ...) log_output(LOG_LEVEL_ERROR, "[APP]", format, ##__VA_ARGS__);
#define APP_LOG_WARN(format, ...) log_output(LOG_LEVEL_WARN, "[APP]", format, ##__VA_ARGS__);
#define APP_LOG_INFO(format, ...) log_output(LOG_LEVEL_INFO, "[APP]", format, ##__VA_ARGS__);