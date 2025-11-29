#ifndef BWARE_H
#define BWARE_H

#include <stdint.h>

typedef struct _bVector3
{
	float x, y, z, pad;
} bVector3;

typedef struct _bVector4
{
	float x, y, z, w;
} bVector4;

extern int(*bSPrintf)(char* destString, const char* fmt, ...);
extern int(*bVSPrintf)(char* destString, const char* fmt, char* argList);

#endif