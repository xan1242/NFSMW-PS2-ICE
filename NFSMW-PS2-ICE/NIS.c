#include "NIS.h"
#include "NFSMW-ICE.h"
#include "minjector.h"
#include <stddef.h>

void** INIS_Singleton;

void* NIS_GetInstance()
{
    return *INIS_Singleton;
}

void* NIS_GetScene(void* instance)
{
    const int vtidx_GetScene = 19;

    void* mNISInstance = instance;
    if (!mNISInstance)
        mNISInstance = NIS_GetInstance();
    if (!mNISInstance)
        return NULL;

    vftbl* vt = *(vftbl**)(mNISInstance);
    uintptr_t pFunc = vt[vtidx_GetScene].addr;

    return ((void* (*)(void*))(pFunc))(mNISInstance);
}

void NIS_Init()
{
    uintptr_t loc_163A38 = 0x163A38;
    INIS_Singleton = (void**)minj_GetPtr(loc_163A38, loc_163A38 + 4);
}
