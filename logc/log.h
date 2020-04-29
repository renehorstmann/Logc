/**
 * Copyright (c) 2020 renehorstmann
 *
 * Modified version of:
 * Copyright (c) 2017 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See `log.c` for details.
 */

#ifndef LOGC_LOG_H
#define LOGC_LOG_H

#ifndef LOGC_LEADING_TEXT
#define LOGC_LEADING_TEXT ""
#endif

#ifndef LOGC_NAMESPACE
#define LOGC_NAMESPACE logc
#endif

#define LogcConcat(a, b) a ## b
#define LogcNamespace(ns, name) LogcConcat(ns , name)

#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>

// use the following definition to stop using colors
// #define LOG_DO_NOT_USE_COLOR

typedef void (*log_lock_function)(void *user_data, bool lock);

enum log_level {
    LOG_TRACE, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_WTF, LOG_NUM_LEVELS
};

#define log_trace(...) LogcNamespace(LOGC_NAMESPACE, _base_)\
(LOG_TRACE, LOGC_LEADING_TEXT, __FILE__, __LINE__, __VA_ARGS__)

#define log_debug(...) LogcNamespace(LOGC_NAMESPACE, _base_)\
(LOG_DEBUG, LOGC_LEADING_TEXT, __FILE__, __LINE__, __VA_ARGS__)

#define log_info(...)  LogcNamespace(LOGC_NAMESPACE, _base_)\
(LOG_INFO,  LOGC_LEADING_TEXT, __FILE__, __LINE__, __VA_ARGS__)

#define log_warn(...)  LogcNamespace(LOGC_NAMESPACE, _base_)\
(LOG_WARN,  LOGC_LEADING_TEXT, __FILE__, __LINE__, __VA_ARGS__)

#define log_error(...) LogcNamespace(LOGC_NAMESPACE, _base_)\
(LOG_ERROR, LOGC_LEADING_TEXT, __FILE__, __LINE__, __VA_ARGS__)

#define log_wtf(...)   LogcNamespace(LOGC_NAMESPACE, _base_)\
(LOG_WTF,   LOGC_LEADING_TEXT, __FILE__, __LINE__, __VA_ARGS__)

void LogcNamespace(LOGC_NAMESPACE, _set_log_file)(FILE *file);

void LogcNamespace(LOGC_NAMESPACE, _set_min_level)(enum log_level level);

void LogcNamespace(LOGC_NAMESPACE, _set_quiet)(bool set);

void LogcNamespace(LOGC_NAMESPACE, _set_locking_function)(log_lock_function fun);

void LogcNamespace(LOGC_NAMESPACE, _set_locking_function_user_data)(void *user_data);

void LogcNamespace(LOGC_NAMESPACE, _base_)(enum log_level level, const char *leading_text,
                                              const char *file, int line, const char *format, ...);

#endif //LOGC_LOG_H
