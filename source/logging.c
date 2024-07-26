#include "logging.h"

#if defined (__cplusplus)
extern "C" {
#endif // __cplusplus

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdarg.h>

#include "color.h"

// static ---------------------------------------------------------------------

static FILE* log_file;
static bool is_logging_init = false;

// global ---------------------------------------------------------------------

LoggingStatus LoggingCtor(const char *log_file_name) {
  assert(log_file_name != NULL); // for debug
  if (log_file_name == NULL) { return kLoggingStatus_NullPassed; }

  FILE* try_open_log_file = fopen(log_file_name, "w");
  if (try_open_log_file == NULL) { return kLoggingStatus_CantOpenFile; }

  int set_buf_res = setvbuf(try_open_log_file, NULL, _IONBF, 0);
  if (set_buf_res != 0) { assert(0 && "cant turn unbuffered io"); }

  log_file = try_open_log_file;
  is_logging_init = true;

  return kLoggingStatus_Ok;
}

LoggingStatus LoggingDtor(void) {
  if (!is_logging_init) { return kLoggingStatus_UninitDtor; }

  fclose(log_file);
  is_logging_init = false;

  return kLoggingStatus_Ok;
}

void LogHidden(const char* source_file_name, const int source_line_num, const char* format_str, ...) {
#if defined (DEBUG)
  assert(format_str != NULL);
  if (format_str == NULL) { return; } // NOTE maybe return status

  va_list args;
  va_start(args, format_str);

  fprintf(log_file, "[%s:%d]:\n", source_file_name, source_line_num);
  vfprintf(log_file, format_str, args);
  fprintf(log_file, "\n");

  va_end(args);
#endif // DEBUG
}

#if defined (__cplusplus)
}
#endif // __cplusplus
