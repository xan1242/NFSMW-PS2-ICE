#include "cFEng.h"

void* (*p_cFEng_Get)() = (void* (*)())(0x2340A0);
void(*p_cFEng_PushNoControlPackage)(void* cFEng, const char* pPackageName, int pPriority) = (void(*)(void*, const char*, int))(0x2344A0);


void* cFEng_Get()
{
	return p_cFEng_Get();
}

void cFEng_PushNoControlPackage(void* cFEng, const char* pPackageName, int pPriority)
{
	return p_cFEng_PushNoControlPackage(cFEng, pPackageName, pPriority);
}
