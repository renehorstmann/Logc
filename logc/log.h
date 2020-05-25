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

// exactly one source file must define:
// #define LOGC_SOURCE
// before including log.h
// or log.c must be included as source file

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


//
// source implementation
//
#ifdef LOGC_SOURCE
// copy of log.c
#include <stdlib.h>
#include <string.h>
#include <time.h>

static struct {
    FILE *log_file;
    enum log_level level;
    bool quiet;
    log_lock_function lock_function;
    void *used_data;
} local;


static const char *level_names[] = {
        "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "WTF"
};

#ifndef LOG_DO_NOT_USE_COLOR
static const char *level_colors[] = {
        "\x1b[94m", "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m", "\x1b[35m"
};
#endif


static void lock() {
    if (local.lock_function) {
        local.lock_function(local.used_data, true);
    }
}


static void unlock() {
    if (local.lock_function) {
        local.lock_function(local.used_data, false);
    }
}


void LogcNamespace(LOGC_NAMESPACE, _set_log_file)(FILE *file) {
    local.log_file = file;
}

void LogcNamespace(LOGC_NAMESPACE, _set_min_level)(enum log_level level) {
    local.level = level;
}

void LogcNamespace(LOGC_NAMESPACE, _set_quiet)(bool set) {
    local.quiet = set;
}

void LogcNamespace(LOGC_NAMESPACE, _set_locking_function)(log_lock_function fun) {
    local.lock_function = fun;
}

void LogcNamespace(LOGC_NAMESPACE, _set_locking_function_user_data)(void *user_data) {
    local.used_data = user_data;
}


void LogcNamespace(LOGC_NAMESPACE, _base_)(enum log_level level, const char *leading_text,
                                              const char *file, int line, const char *format, ...) {
    if (level < local.level) {
        return;
    }

    /* Acquire lock_function */
    lock();

    /* Get current time */
    time_t t = time(NULL);
    struct tm *lt = localtime(&t);

    /* Log to stderr */
    if (!local.quiet) {
        va_list args;
        char buf[16];
        buf[strftime(buf, sizeof(buf), "%H:%M:%S", lt)] = '\0';
#ifdef LOG_DO_NOT_USE_COLOR
        fprintf(stderr, "%s %-5s %s:%d: %s",
                buf, level_names[level], file, line, leading_text);
#else
        fprintf(stderr, LOGC_LEADING_TEXT "%s %s%-5s\x1b[0m \x1b[90m%s:%d:\x1b[0m %s",
                buf, level_colors[level], level_names[level], file, line, leading_text);
#endif
        va_start(args, format);
        vfprintf(stderr, format, args);
        va_end(args);
        fprintf(stderr, "\n");
        fflush(stderr);
    }

    /* Log to file */
    if (local.log_file) {
        va_list args;
        char buf[32];
        buf[strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", lt)] = '\0';
        fprintf(local.log_file, LOGC_LEADING_TEXT "%s %-5s %s:%d: %s",
                buf, level_names[level], file, line, leading_text);
        va_start(args, format);
        vfprintf(local.log_file, format, args);
        va_end(args);
        fprintf(local.log_file, "\n");
        fflush(local.log_file);
    }

    /* Release lock_function */
    unlock();
}

#endif


#endif //LOGC_LOG_H
