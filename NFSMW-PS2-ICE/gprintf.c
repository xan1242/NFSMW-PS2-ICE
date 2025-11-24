#include "gprintf.h"
#include "includes/minjector.h"

int(*gprintf)(const char*, ...) = (int(*)(const char*, ...))(0);

#if (defined __DEBUG) || (defined __ENABLELOG)
static uintptr_t loc_36198C = 0x36198C;
#endif

void gprintf_init()
{
#if (defined __DEBUG) || (defined __ENABLELOG)
	uintptr_t addr = minj_GetBranchDestination(loc_36198C);
	if (!addr)
		return;

	gprintf = (int(*)(const char*, ...))(addr);
#endif
}
