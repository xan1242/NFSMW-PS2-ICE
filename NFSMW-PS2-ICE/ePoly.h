#ifndef EPOLY_H
#define EPOLY_H

#include "bWare.h"

typedef struct
{
	bVector3 Vertices[4];
	float UVs[4][2];
	float UVsMask[4][2];
	unsigned char Colours[4][4];
	unsigned char flags;
	unsigned char Flailer;
} ePoly;

void ePoly_ePoly(ePoly* poly);
void ePoly_Init();

#endif