#include "Attrib.h"

uint32_t(*pAttrib_StringHash32)(const char* k) = (uint32_t(*)(const char*))(0x150FF8);
uint64_t(*pAttrib_StringHash64)(const char* k) = (uint64_t(*)(const char*))(0x1514C8);

uint32_t Attrib_StringHash32(const char* k)
{
	return pAttrib_StringHash32(k);
}

uint64_t Attrib_StringHash64(const char* k)
{
	return pAttrib_StringHash64(k);
}
