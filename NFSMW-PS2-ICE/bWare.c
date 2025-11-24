#include "bWare.h"

int(*bSPrintf)(char* destString, const char* fmt, ...) = (int(*)(char*, const char*, ...))(0x15A308);

