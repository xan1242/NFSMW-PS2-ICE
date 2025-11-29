#ifndef NFSMW_ICE_H
#define NFSMW_ICE_H

#include "gprintf.h"
#include <stdbool.h>
#include "Attrib.h"
#include "ActionQueue.h"
#include "bWare.h"

#if (defined __DEBUG) || (defined __ENABLELOG)
#define LOG(fmt, ...) gprintf("NFSMW-ICE: " fmt, ##__VA_ARGS__)
#else
#define LOG(fmt, ...)
#endif

// Definitions

#define NFSMW_OPM_DEMO_CRC 0x61D112E4

#ifndef __INTELLISENSE__
__attribute__((packed)) 
#endif

typedef struct _CameraAI_Director
{
	void* vftable;
	int mViewID;
	Attrib_StringKey mDesiredMode;
	void* mAction;
	uint32_t unk1;
	ActionQueue mInputQ;

}CameraAI_Director;

typedef struct _vftbl
{
    uintptr_t unk;
    uintptr_t addr;
}vftbl;

typedef struct _ICEPoly
{
	bVector3 Vertices[4];
} ICEPoly;

typedef enum
{
	ICETexture_eLogo,
	ICETexture_eAlpha,
	ICETexture_eSolid,
	ICETexture_eNumTextures,
} ICETexture;

// Functions

void NFSMW_ICE_Init();
void NFSMW_ICE_PostInit();





#endif