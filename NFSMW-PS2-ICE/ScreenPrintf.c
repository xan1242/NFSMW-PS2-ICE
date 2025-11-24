#include "NFSMW-ICE.h"
#include "ScreenPrintf.h"
#include "FEPackageManager.h"
#include "FEng.h"
#include "cFEng.h"
#include "bWare.h"
#include "includes/minjector.h"
#include <stdbool.h>

const char* ScreenPrintf_FngName = (const char*)0x49C1D0;
ScreenPrintItem ScreenPrintItemTable[SCREENPRINTF_MAXITEMS];

void ScreenPrintItem_Init(ScreenPrintItem* item, uintptr_t obj)
{
	item->debugString = (void*)obj;
	item->PosX = 0;
	item->PosY = 0;
	item->Lifetime = -1.0f;
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
		uintptr_t obj = FEngFindString(ScreenPrintf_FngName, hash);
		if (obj)
			FEngSetInvisible(obj);
		ScreenPrintItem_Init(&ScreenPrintItemTable[i], obj);
	}
}

void ScreenPrintf_Init()
{
	//LOG("ScreenPrintf_Init stub...\n");
}

void ScreenPrintf_PostInit()
{
	InitScreenPrintf();
}