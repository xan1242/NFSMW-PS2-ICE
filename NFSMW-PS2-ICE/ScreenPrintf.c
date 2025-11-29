#include "NFSMW-ICE.h"
#include "ScreenPrintf.h"
#include "FEPackageManager.h"
#include "FEng.h"
#include "cFEng.h"
#include "cFEngGameInterface.h"
#include "bWare.h"
#include "FEDatabase.h"
#include "ICEManager.h"
#include "includes/minjector.h"
#include <stdbool.h>
#include <stdarg.h>
//#include <stdio.h>

const char* ScreenPrintf_FngName = (const char*)0x49C1D0;
ScreenPrintItem ScreenPrintItemTable[SCREENPRINTF_MAXITEMS];
int* DoScreenPrintf = (int*)0x525DA4;
float* RealTimeElapsed = (float*)0x5253F8;
unsigned int* RealTimeFrames = (unsigned int*)0x5253EC;
unsigned int last_realtime_frames;
void(*DisplayDebugScreenPrints)() = (void(*)())(0);

// we need to update these for ICE anyway...
float* PreviousCpuFrameTime = (float*)0x524AE8;
float* PreviousGpuFrameTime = (float*)0x524AEC;
float* PreviousRenderFrameTime = (float*)0x524AFC;
float* PreviousGpuFrameRate = (float*)0x524AF0;
float* PreviousCpuFrameRate = (float*)0x524AF4;
unsigned int* RenderTimingStart = (unsigned int*)0x524B0C;
unsigned int* RenderTimingEnd = (unsigned int*)0x524B10;
unsigned int* FrameTimingStartTime = (unsigned int*)0x524B14;
unsigned int* FrameTimingEndTime = (unsigned int*)0x524B18;


void ScreenPrintItem_Reset(ScreenPrintItem* item)
{
	item->PosX = 0;
	item->PosY = 0;
	item->Lifetime = -1.0f;
	if (item->debugString)
		FEngSetInvisible(item->debugString);
}

void ScreenPrintItem_Init(ScreenPrintItem* item, void* obj)
{
	item->debugString = obj;
	ScreenPrintItem_Reset(item);
}

void InitScreenPrintf()
{
	char tmpstr[32];

	void* cfeng = cFEng_Get();
	void* fepm = FEPackageManager_Get();

	cFEng_PushNoControlPackage(cfeng, ScreenPrintf_FngName, 104);
	FEPackageManager_SetUseIdleList(fepm, ScreenPrintf_FngName, true);
	FEPackageManager_SetPermanent(fepm, ScreenPrintf_FngName, true);

	for (int i = 0; i < SCREENPRINTF_MAXITEMS; i++)
	{
		bSPrintf(tmpstr, "SCREENPRINTF%d", i);
		uint32_t hash = FEHashUpper(tmpstr);
		void* obj = FEngFindString(ScreenPrintf_FngName, hash);
		ScreenPrintItem_Init(&ScreenPrintItemTable[i], obj);
	}
}

void ResetScreenPrintf()
{
	for (int i = 0; i < SCREENPRINTF_MAXITEMS; i++)
	{
		ScreenPrintItem* item = &ScreenPrintItemTable[i];
		if (item->Lifetime >= 0.0f)
		{
			item->Lifetime -= *RealTimeElapsed;

			if (item->Lifetime < 0.0f && item->debugString)
			{
				FEngSetInvisible(item->debugString);
			}
		}
	}
}

void FixWidescreen(int* x)
{
	if (!FEDatabase_IsWidescreen(FEDatabase_Get()))
		return;

	if (ICEManager_IsEditorOn())
		return;

	if (*x >= -10)
	{
		if (*x <= 10)
			return;
		*x = *x + 120;
	}
	else
	{
		*x = *x - 120;
	}
}

ScreenPrintItem* GetScreenPrintItemAtLocation(int x, int y)
{
	for (int i = 0; i < SCREENPRINTF_MAXITEMS; i++)
	{
		if ((x == ScreenPrintItemTable[i].PosX) && (y == ScreenPrintItemTable[i].PosY))
			return &ScreenPrintItemTable[i];
	}

	return NULL;
}

ScreenPrintItem* GetUnusedScreenPrintItem()
{
	for (int i = 0; i < SCREENPRINTF_MAXITEMS; i++)
	{
		if (ScreenPrintItemTable[i].Lifetime < 0.0f)
			return &ScreenPrintItemTable[i];
	}

	return NULL;
}



void ScreenVPrintf(int x, int y, float duration, unsigned int color, const char* fmt, va_list argList)
{
	ScreenPrintItem* item = NULL;
	char tmpstr[128];

	if (!*DoScreenPrintf)
		return;

	FixWidescreen(&x);

	if (duration != 0.0f)
        item = GetScreenPrintItemAtLocation(x, y);

    if (!item)
        item = GetUnusedScreenPrintItem();

	if (!item || (!item->debugString))
		return;

	item->Lifetime = duration;
	item->PosX = x;
	item->PosY = y;

	// #TODO FPU registers do NOT align in the same way as GCC!
	bVSPrintf(tmpstr, fmt, argList);
	//vsprintf(tmpstr, fmt, argList);

	FEColor fecolor;
	FEColor_FEColor(&fecolor, color);
	FEObject_SetColor(item->debugString, &fecolor, false);
	FEPrintf(item->debugString, tmpstr);
	FEngSetTopLeft(item->debugString, x, y);
	FEngSetVisible(item->debugString);
}

void ScreenPrintf(int x, int y, float duration, unsigned int color, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	ScreenVPrintf(x, y, duration, color, fmt, args);

	va_end(args);
}

void ScreenPrintfStandard(int x, int y, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	ScreenVPrintf(x, y, 0.0f, 0xFFFFFFFF, fmt, args);

	va_end(args);
}

void ScreenShadowPrintf(int x, int y, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	ScreenVPrintf(x + 1, y + 1, 0.0f, 0x80000000, fmt, args);
	ScreenVPrintf(x, y, 0.0f, 0xFFFFFFFF, fmt, args);

	va_end(args);
}

void DisplayDebugScreenPrints_Hook()
{
	float renderFT;
	float renderFR;
	float cpuFT;
	float cpuFR;
	float dispFR;

	if ((*RealTimeFrames & 8) != (last_realtime_frames & 8))
	{
		last_realtime_frames = *RealTimeFrames;

		renderFR = 0.0f;
		renderFT = bGetTickerDifference(*RenderTimingStart, *RenderTimingEnd);
		cpuFT = bGetTickerDifference(*RenderTimingStart, *RenderTimingEnd);

		if (renderFT != 0.0f)
			*PreviousRenderFrameTime = renderFT;
		if (cpuFT < 0.1f)
			cpuFT = 0.1f;
		if (renderFT > 0.1)
			renderFR = 1000.0f / renderFT;

		*PreviousCpuFrameTime = cpuFT;
		*PreviousGpuFrameTime = renderFT;
		*PreviousCpuFrameRate = 1000.0f / cpuFT;
		*PreviousGpuFrameRate = renderFR;
	}

#ifdef SCREENPRINTF_SHOWFPS
	ScreenPrintf(-300, -30, 0.0f, 0xFFFFFFFF, "C: %.2f ms", *PreviousCpuFrameTime);
	if (*PreviousGpuFrameTime)
		ScreenPrintf(-200, -30, 0.0f, 0xFFFFFFFF, "G: %.2fms", *PreviousGpuFrameTime);

	// MIN
	if (*PreviousCpuFrameRate < *PreviousGpuFrameRate)
		dispFR = *PreviousCpuFrameRate;
	else
		dispFR = *PreviousGpuFrameRate;

	ScreenPrintf(-300, -15, 0.0f, 0xFFFFFFFF, "F: %.2f fps", dispFR);
#endif


	return DisplayDebugScreenPrints();
}

void ScreenPrintf_Init()
{
	cFEngGameInterface_Init();

	uintptr_t loc_2EEF50 = 0x2EEF50;
	DisplayDebugScreenPrints = (void(*)())(minj_GetBranchDestination(loc_2EEF50));
	minj_MakeCALL(loc_2EEF50, (uintptr_t)&DisplayDebugScreenPrints_Hook);
}

void ScreenPrintf_PostInit()
{
	*DoScreenPrintf = true;
	InitScreenPrintf();
}