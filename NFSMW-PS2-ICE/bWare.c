#include "bWare.h"

int(*bSPrintf)(char* destString, const char* fmt, ...) = (int(*)(char*, const char*, ...))(0x15A308);
int(*bVSPrintf)(char* destString, const char* fmt, char* argList) = (int(*)(char*, const char*, char*))(0x15A370);
float(*bGetTickerDifference)(unsigned int start_ticks, unsigned int end_ticks) = (float(*)(unsigned int, unsigned int))(0x1575D0);

