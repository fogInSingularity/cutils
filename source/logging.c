#include "logging.h"

#if defined (__cplusplus)
extern "C" {
#endif // __cplusplus

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <assert.h>

#undef fopen
#undef fclose

// static ---------------------------------------------------------------------

static FILE* log_file = NULL;

static void LoggingDtor(void);

// global ---------------------------------------------------------------------

LoggingStatus LoggingSetup(const char *log_file_name) {
    assert(log_file_name != NULL); // for debug
    if (log_file_name == NULL) { return kLoggingStatus_NullPassed; }

    FILE* try_open_log_file = fopen(log_file_name, "w");
    if (try_open_log_file == NULL) { return kLoggingStatus_CantOpenFile; }

    int set_buf_status = setvbuf(try_open_log_file, NULL, _IONBF, 0);
    if (!set_buf_status) { 
        fclose(try_open_log_file);
        return kLoggingStatus_InternalError; 
    }

    int atexit_status = atexit(LoggingDtor);
    if (!atexit_status) {
        fclose(try_open_log_file);
        return kLoggingStatus_InternalError;
    }

    log_file = try_open_log_file;

    return kLoggingStatus_Ok;
}

LoggingStatus LogHidden(const char* source_file_name, 
                        const int source_line_num, 
                        const char* source_func_name, 
                        const char* format_str, 
                        ...) 
{
    assert(format_str       != NULL);
    assert(source_file_name != NULL);
    assert(source_line_num  >= 0);
    assert(source_func_name != NULL);

    if ((format_str == NULL)
        || (source_file_name == NULL)
        || (source_func_name == NULL)
        || (source_line_num < 0)) 
    { return kLoggingStatus_NullPassed; }
    
    if (log_file == NULL) { return kLoggingStatus_UninitLog; }

#if defined (DEBUG)    
    va_list args;
    va_start(args, format_str);

    fprintf(log_file, "[%s:%s:%d]:\n", source_file_name, source_func_name, source_line_num);
    vfprintf(log_file, format_str, args);

    va_end(args);
#else 
    // do nothing    
#endif // DEBUG
    return kLoggingStatus_Ok;
}

// static ---------------------------------------------------------------------

static void LoggingDtor(void) {
    if (log_file == NULL) { return ; }

    fclose(log_file);
    log_file = NULL;
}

#if defined (__cplusplus)
}
#endif // __cplusplus
