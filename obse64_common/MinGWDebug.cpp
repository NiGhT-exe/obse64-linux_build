#include "MinGWDebug.h"

// Global variable instead of a static class member
// This helps avoid ODR issues with FILE*
namespace {
    FILE* g_debugLogFile = nullptr;
}

// Accessor functions
FILE* MinGWDebug::GetLogFile() {
    return g_debugLogFile;
}

void MinGWDebug::SetLogFile(FILE* file) {
    g_debugLogFile = file;
} 