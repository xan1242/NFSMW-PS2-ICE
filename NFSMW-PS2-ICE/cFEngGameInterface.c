#include "cFEngGameInterface.h"
#include "ScreenPrintf.h"
#include "includes/minjector.h"

void(*p_cFEngGameInterface_EndPackageRendering)(void* obj, void* pkg) = (void(*)(void*, void*))(0);

void cFEngGameInterface_EndPackageRendering_Hook(void* obj, void* pkg)
{
	const uint32_t unkconst = 0x8046C2FB;
	uintptr_t pPkg = (uintptr_t)pkg;

	if (*(uint32_t*)(pPkg + 4) == unkconst)
		ResetScreenPrintf();

	return p_cFEngGameInterface_EndPackageRendering(obj, pkg);
}

void cFEngGameInterface_Init()
{
	uintptr_t loc_496DC4 = 0x496DC4;
	p_cFEngGameInterface_EndPackageRendering = (void(*)(void*, void*))(*(uintptr_t*)loc_496DC4);
	minj_WriteMemory32(loc_496DC4, (uint32_t)&cFEngGameInterface_EndPackageRendering_Hook);
}