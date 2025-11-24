#include "FEDatabase.h"

uintptr_t pFEDatabase = 0x521B3C;

uintptr_t FEDatabase_Get()
{
	return *(uintptr_t*)(pFEDatabase);
}

bool FEDatabase_IsWidescreen(uintptr_t db)
{
	return *(bool*)(db + 0x48 + 0xC);
}
