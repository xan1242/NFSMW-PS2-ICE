#include "ePoly.h"
#include "minjector.h"

void(*p_ePoly_ePoly)(void* that) = (void(*)(void*))(0);

void ePoly_ePoly(ePoly* poly)
{
	return p_ePoly_ePoly(poly);
}

void ePoly_Init()
{
	uintptr_t loc_202B1C = 0x202B1C;
	p_ePoly_ePoly = (void(*)(void*))(minj_GetBranchDestination(loc_202B1C));
}
