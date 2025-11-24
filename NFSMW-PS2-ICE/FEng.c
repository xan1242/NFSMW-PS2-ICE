#include "FEng.h"

uint32_t(*pFEHashUpper)(const char* String) = (uint32_t(*)(const char*))(0x2700B0);
uintptr_t(*pFEngFindString)(const char* pkg_name, uint32_t hash) = (uintptr_t(*)(const char*, uint32_t))(0x232F00);
//void(*pFEngSetInvisible)(const char* pkg_name, uint32_t hash) = (void(*)(const char*, uint32_t))(0x23AB10);
void(*pFEngSetInvisible)(uintptr_t obj) = (void(*)(uintptr_t))(0x231738);

uint32_t FEHashUpper(const char* String)
{
	return pFEHashUpper(String);
}

uintptr_t FEngFindString(const char* pkg_name, uint32_t hash)
{
	return pFEngFindString(pkg_name, hash);
}

//void FEngSetInvisible(const char* pkg_name, uint32_t hash)
//{
//	return pFEngSetInvisible(pkg_name, hash);
//}

void FEngSetInvisible(uintptr_t obj)
{
	return pFEngSetInvisible(obj);
}
