#ifndef FILE_WRAPER_H_
#define FILE_WRAPER_H_

#if defined (__cplusplus)
extern "C" {
#endif // __cplusplus

#include <stdio.h>

#define fopen(file_name_, open_mode_) FOpenWraper(file_name_, open_mode_, __FILE__, __LINE__, __func__)

FILE* FOpenWraper(const char* file_name, const char* open_mode, 
                  const char* source_file, int source_line, const char* source_func);

#define fclose(file_) FCloseWraper(file_, __FILE__, __LINE__, __func__)

int FCloseWraper(FILE* file,
                 const char* source_file, int source_line, const char* source_func);

#if defined (__cplusplus)
}
#endif // __cplusplus

#endif // FILE_WRAPER_H_
