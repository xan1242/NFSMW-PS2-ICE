#ifndef SCREENPRINTF_H
#define SCREENPRINTF_H

#include <stdint.h>

#define SCREENPRINTF_MAXITEMS 64

typedef struct
{
    void* debugString;
    int16_t PosX;
    int16_t PosY;
    float Lifetime;
} ScreenPrintItem;


void ScreenPrintf_Init();
void ScreenPrintf_PostInit();

#endif