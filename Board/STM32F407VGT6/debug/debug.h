#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "main.h"
#include <cstdarg>

class Debug {
public:
    static Debug& instance();

    void print(const char* msg);
    void printf(const char* fmt, ...);

private:
    Debug() = default;
};

void print(const char* msg);
void printf_dbg(const char* fmt, ...);

#endif
