#ifndef FENG_H
#define FENG_H

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    uint32_t b;
    uint32_t g;
    uint32_t r;
    uint32_t a;
} FEColor;

void FEColor_FEColor(FEColor* obj, uint32_t Col);
void FEObject_SetColor(void* obj, const FEColor* color, bool bRelative);
extern void(*FEPrintf)(void* obj, const char* fmt, ...);

uint32_t FEHashUpper(const char* String);
void* FEngFindString(const char* pkg_name, uint32_t hash);
//void FEngSetInvisible(const char* pkg_name, uint32_t hash);
void FEngSetInvisible(void* obj);
void FEngSetVisible(void* obj);
void FEngSetTopLeft(void* obj, float x, float y);

#endif