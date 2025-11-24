//#include <stdio.h>
#include "includes/pcsx2f_api.h"
#include "includes/minjector.h"
#include "gprintf.h"
#include "NFSMW-ICE.h"

int CompatibleCRCList[] = { NFSMW_OPM_DEMO_CRC };

uintptr_t loc_2EF1FC = 0x2EF1FC;
void(*InitializeEverything)(int argc, char** argv) = (void(*)(int, char**))(0);

void early_init()
{
    // get the game's printf function address for debugging purposes
    gprintf_init();
}

void InitializeEverything_Hook(int argc, char** argv)
{
    NFSMW_ICE_Init();
    InitializeEverything(argc, argv);
    NFSMW_ICE_PostInit();
}

void init()
{
    early_init();

    LOG("NFSMW-ICE Plugin Init\n");

    uintptr_t pInitializeEverything = minj_GetBranchDestination(loc_2EF1FC);
    InitializeEverything = (void(*)(int, char**))(pInitializeEverything);
    minj_MakeCALL(loc_2EF1FC, (uintptr_t)&InitializeEverything_Hook);
}

int main()
{
    return 0;
}