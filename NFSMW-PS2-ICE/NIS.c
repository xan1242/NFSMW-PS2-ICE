#include "NIS.h"
#include "NFSMW-ICE.h"
#include <stddef.h>

void** INIS_Singleton = (void**)0x52D8D4;

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
