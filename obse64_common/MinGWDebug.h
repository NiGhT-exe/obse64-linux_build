#pragma once

#include "Log.h"
#include <string>
#include <ctime>

// Define MAX_PATH if not defined
#ifndef MAX_PATH
#define MAX_PATH 260
#endif

// Forward declaration of FILE
struct _iobuf;
typedef struct _iobuf FILE;

// Special debug logging for areas where SEH was converted to standard exceptions
class MinGWDebug
{
public:
    static void Initialize()
    {
        // Enable for all build types
        char logPath[MAX_PATH];
        std::time_t t = std::time(nullptr);
        std::tm* now = std::localtime(&t);
        
        snprintf(logPath, sizeof(logPath), "obse64_error_log_%04d%02d%02d_%02d%02d%02d.log", 
            now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, 
            now->tm_hour, now->tm_min, now->tm_sec);
            
        FILE* logFile = fopen(logPath, "w");
        SetLogFile(logFile);
        
        if (logFile)
        {
            fprintf(logFile, "OBSE64 Error Log\n");
            fprintf(logFile, "==============\n\n");
            fprintf(logFile, "Build type: %s\n", 
                #ifdef _MSC_VER
                "MSVC"
                #else
                "MinGW"
                #endif
            );
            fprintf(logFile, "Timestamp: %04d-%02d-%02d %02d:%02d:%02d\n\n",
                now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, 
                now->tm_hour, now->tm_min, now->tm_sec);
            fflush(logFile);
            
            _MESSAGE("MinGWDebug: Initialized debug log at %s", logPath);
        }
    }
    
    static void LogException(const char* function, const char* message)
    {
        FILE* logFile = GetLogFile();
        if (logFile)
        {
            std::time_t t = std::time(nullptr);
            std::tm* now = std::localtime(&t);
            
            fprintf(logFile, "[%02d:%02d:%02d] EXCEPTION in %s: %s\n", 
                now->tm_hour, now->tm_min, now->tm_sec,
                function, message);
            fflush(logFile);
            
            _MESSAGE("Error: Exception in %s: %s", function, message);
        }
    }
    
    static void Close()
    {
        FILE* logFile = GetLogFile();
        if (logFile)
        {
            fclose(logFile);
            SetLogFile(nullptr);
        }
    }
    
private:
    // Accessor functions to avoid ODR issues
    static FILE* GetLogFile();
    static void SetLogFile(FILE* file);
};

// Macro for simplified try/catch blocks with enhanced debugging
#define MINGW_TRY_BEGIN(funcName) try {
#define MINGW_TRY_END(funcName) } catch(...) { MinGWDebug::LogException(funcName, "Unhandled exception"); } 