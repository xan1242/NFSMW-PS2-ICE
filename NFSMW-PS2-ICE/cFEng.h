#ifndef CFENG_H
#define CFENG_H

#include <stdint.h>

void* cFEng_Get();
void cFEng_PushNoControlPackage(void* cFEng, const char* pPackageName, int pPriority);

#endif