#ifndef BWARE_H
#define BWARE_H

#include <stdint.h>

extern int(*bSPrintf)(char* destString, const char* fmt, ...);
extern int(*bVSPrintf)(char* destString, const char* fmt, char* argList);

#endif