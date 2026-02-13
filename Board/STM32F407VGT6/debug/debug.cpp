#include "debug.h"
#include "usart.h"
#include <cstring>
#include <cstdio>

extern UART_HandleTypeDef huart4;

Debug& Debug::instance()
{
    static Debug dbg;
    return dbg;
}

void Debug::print(const char* msg)
{
    HAL_UART_Transmit(&huart4, (uint8_t*)msg, strlen(msg), 100);
}

void Debug::printf(const char* fmt, ...)
{
    char buffer[128];

    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    HAL_UART_Transmit(&huart4, (uint8_t*)buffer, strlen(buffer), 100);
}

/* Wrapper functions */

void print(const char* msg)
{
    Debug::instance().print(msg);
}

void printf_dbg(const char* fmt, ...)
{
    char buffer[128];

    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    Debug::instance().print(buffer);
}
