#ifndef FENG_H
#define FENG_H

#include <stdint.h>

uint32_t FEHashUpper(const char* String);
uintptr_t FEngFindString(const char* pkg_name, uint32_t hash);
//void FEngSetInvisible(const char* pkg_name, uint32_t hash);
void FEngSetInvisible(uintptr_t obj);

#endif