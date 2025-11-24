#ifndef FEPACKAGEMANAGER_H
#define FEPACKAGEMANAGER_H

#include <stdint.h>
#include <stdbool.h>

void* FEPackageManager_Get();
//uintptr_t FEPackageManager_FindPackage(void* pkgmanager, const char* pkg_name);
bool FEPackageManager_SetUseIdleList(void* pkgmanager, const char* pkg_name, bool state);
void FEPackageManager_SetPermanent(void* pkgmanager, const char* pkg_name, bool state);

#endif