#ifndef SCREENPRINTF_H
#define SCREENPRINTF_H

#include <stdint.h>
#include <stdarg.h>

#define SCREENPRINTF_MAXITEMS 64

typedef struct
{
    void* debugString;
    int16_t PosX;
    int16_t PosY;
    float Lifetime;
} ScreenPrintItem;

void ResetScreenPrintf();
void ScreenPrintf_Init();
void ScreenPrintf_PostInit();

void ScreenVPrintf(int x, int y, float duration, unsigned int color, const char* fmt, va_list argList);
void ScreenPrintf(int x, int y, float duration, unsigned int color, const char* fmt, ...);
void ScreenShadowPrintf(int x, int y, const char* fmt, ...);

extern int* DoScreenPrintf;

#endif