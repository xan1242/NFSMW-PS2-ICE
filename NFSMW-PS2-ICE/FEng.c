#include "FEng.h"

uint32_t(*pFEHashUpper)(const char* String) = (uint32_t(*)(const char*))(0x2700B0);
void*(*pFEngFindString)(const char* pkg_name, uint32_t hash) = (void*(*)(const char*, uint32_t))(0x232F00);
//void(*pFEngSetInvisible)(const char* pkg_name, uint32_t hash) = (void(*)(const char*, uint32_t))(0x23AB10);
void(*pFEngSetInvisible)(void* obj) = (void(*)(void*))(0x231738);
void(*pFEngSetVisible)(void* obj) = (void(*)(void*))(0x2317A8);
void(*pFEngSetTopLeft)(void* obj, float x, float y) = (void(*)(void*, float, float))(0x231DE0);
void(*pFEColor_FEColor)(FEColor* obj, uint32_t Col) = (void(*)(FEColor*, uint32_t))(0x27D068);
void(*pFEObject_SetColor)(void* obj, const FEColor* color, bool bRelative) = (void(*)(void*, const FEColor*, bool))(0x276D78);
void(*FEPrintf)(void* obj, const char* fmt, ...) = (void(*)(void*, const char*, ...))(0x233130);

void FEObject_SetColor(void* obj, const FEColor* color, bool bRelative)
{
	return pFEObject_SetColor(obj, color, bRelative);
}

void FEColor_FEColor(FEColor* obj, uint32_t Col)
{
	return pFEColor_FEColor(obj, Col);
}

uint32_t FEHashUpper(const char* String)
{
	return pFEHashUpper(String);
}

void* FEngFindString(const char* pkg_name, uint32_t hash)
{
	return pFEngFindString(pkg_name, hash);
}

//void FEngSetInvisible(const char* pkg_name, uint32_t hash)
//{
//	return pFEngSetInvisible(pkg_name, hash);
//}

void FEngSetInvisible(void* obj)
{
	return pFEngSetInvisible(obj);
}

void FEngSetVisible(void* obj)
{
	return pFEngSetVisible(obj);
}

void FEngSetTopLeft(void* obj, float x, float y)
{
	return pFEngSetTopLeft(obj, x, y);
}
