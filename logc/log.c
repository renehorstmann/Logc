/*
 * Copyright (c) 2020 renehorstmann
 *
 * Modified version of:
 * Copyright (c) 2017 rxi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "log.h"

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
