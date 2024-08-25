#include "logging.h"
#include <time.h>

#if defined (__cplusplus)
extern "C" {
#endif // __cplusplus

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <assert.h>

// static ---------------------------------------------------------------------

static FILE* log_file = NULL;
static bool is_logging_init = false;

static void LoggingDtor(void);

// global ---------------------------------------------------------------------

LoggingStatus LoggingSetup(const char *log_file_name) {
    assert(log_file_name != NULL); // for debug
    if (log_file_name == NULL) { return kLoggingStatus_NullPassed; }

    FILE* try_open_log_file = fopen(log_file_name, "w");
    if (try_open_log_file == NULL) { return kLoggingStatus_CantOpenFile; }

    int set_buf_res = setvbuf(try_open_log_file, NULL, _IONBF, 0);
    if (set_buf_res != 0) { assert(0 && "cant turn unbuffered io"); }

    log_file = try_open_log_file;
    is_logging_init = true;

    atexit(LoggingDtor);

    return kLoggingStatus_Ok;
}

void LogHidden(const char* source_file_name, 
               const int source_line_num, 
               const char* source_func_name, 
               const char* format_str, 
               ...) 
{
#if defined (DEBUG)
    assert(format_str != NULL);
    if (format_str == NULL) { return ; } // NOTE maybe return status

    if (!is_logging_init) { return ; }
        
    va_list args;
    va_start(args, format_str);

    fprintf(log_file, "[%s:%s:%d]: ", source_file_name, source_func_name, source_line_num);
    vfprintf(log_file, format_str, args);

    va_end(args);
#else
    (void)source_file_name;
    (void)source_line_num;
    (void)source_func_name;
    (void)format_str;
#endif // DEBUG
}

// static ---------------------------------------------------------------------

static void LoggingDtor(void) {
    if (!is_logging_init) { return ; }

    fclose(log_file);
    is_logging_init = false;
}

#if defined (__cplusplus)
}
#endif // __cplusplus
