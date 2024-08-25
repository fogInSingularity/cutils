#ifndef LOGGING_H_
#define LOGGING_H_

#if defined (__cplusplus)
extern "C" {
#endif // __cplusplus

#if !defined (STRINGIFY)
#define STRINGIFY(x) #x
#endif // STRINGIFY

typedef enum LoggingStatus {
    kLoggingStatus_Ok            = -1,
    
    kLoggingStatus_UninitEnum    =  0,

    kLoggingStatus_NullPassed    =  1,
    kLoggingStatus_CantOpenFile  =  2,
    kLoggingStatus_UninitLog     =  3,
    kLoggingStatus_InternalError =  4,
} LoggingStatus;

LoggingStatus LoggingSetup(const char* log_file_name);

#define Log(...) do { LogHidden(__FILE__, __LINE__, __func__, __VA_ARGS__); } while (0)

LoggingStatus LogHidden(const char* source_file_name, 
                        const int source_line_num, 
                        const char* source_func_name, 
                        const char* format_str, 
                        ...) __attribute__((format(printf, 4, 5)));

#if defined (__cplusplus)
}
#endif // __cplusplus

#endif // LOGGING_H_
