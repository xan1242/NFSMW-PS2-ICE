#ifndef ATTRIB_H
#define ATTRIB_H

#include <stdint.h>

typedef struct _Attrib_StringKey
{
	uint64_t mHash64;
	uint32_t mHash32;
	const char* mString;
}Attrib_StringKey;

uint32_t Attrib_StringHash32(const char* k);
uint64_t Attrib_StringHash64(const char* k);

#endif