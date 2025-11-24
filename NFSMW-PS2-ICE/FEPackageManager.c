#include "FEPackageManager.h"

void* (*pFEPackageManager_Get)() = (void* (*)())(0x25AD08);
uintptr_t(*pFEPackageManager_FindPackage)(void* pkgmanager, const char* pkg_name) = (uintptr_t(*)(void*, const char*))(0x25AFF8);
uintptr_t(*pFEPackageManager_FindFEPackageData)(void* pkgmanager, const char* pkg_name) = (uintptr_t(*)(void*, const char*))(0x25B170);

void* FEPackageManager_Get()
{
	return pFEPackageManager_Get();
}

//uintptr_t FEPackageManager_FindPackage(void* pkgmanager, const char* pkg_name)
//{
//	return pFEPackageManager_FindPackage(pkgmanager, pkg_name);
//}

bool FEPackageManager_SetUseIdleList(void* pkgmanager, const char* pkg_name, bool state)
{
	uintptr_t pkg = pFEPackageManager_FindPackage(pkgmanager, pkg_name);
	if (!pkg)
		return false;

	*(bool*)(pkg + 0x18) = state;

	return true;
}

void FEPackageManager_SetPermanent(void* pkgmanager, const char* pkg_name, bool state)
{
	uintptr_t pkgdata = pFEPackageManager_FindFEPackageData(pkgmanager, pkg_name);
	*(uint16_t*)(pkgdata + 0x20) = (uint16_t)state;
}
