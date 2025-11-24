#include "bWare.h"

int(*bSPrintf)(char* destString, const char* fmt, ...) = (int(*)(char*, const char*, ...))(0x15A308);
int(*bVSPrintf)(char* destString, const char* fmt, char* argList) = (int(*)(char*, const char*, char*))(0x15A370);

