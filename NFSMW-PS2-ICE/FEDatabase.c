#include "FEDatabase.h"
#include "minjector.h"

uintptr_t pFEDatabase = 0x521B3C;

uintptr_t FEDatabase_Get()
{
	return *(uintptr_t*)(pFEDatabase);
}

bool FEDatabase_IsWidescreen(uintptr_t db)
{
	return *(bool*)(db + 0x48 + 0xC);
}

void FEDatabase_Init()
{
	uintptr_t loc_225430 = 0x225430;
	pFEDatabase = minj_GetPtr(loc_225430, loc_225430 + 4);
}
