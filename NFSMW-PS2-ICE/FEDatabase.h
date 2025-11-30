#ifndef FEDATABASE_H
#define FEDATABASE_H

#include <stdbool.h>
#include <stdint.h>

uintptr_t FEDatabase_Get();
bool FEDatabase_IsWidescreen(uintptr_t db);
void FEDatabase_Init();

#endif