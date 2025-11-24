#include <stdint.h>
#include <stddef.h>
#include "ICEManager.h"

uintptr_t pTheICEManager = 0x004EB6B8;

void ICEManager_SetActionQ(void* ActionQ)
{
    const size_t offActionQPtr = 0x1CBC;
    *(void**)(pTheICEManager + offActionQPtr) = ActionQ;
}

void ICEManager_EditorOn()
{
    const size_t offMode = 0x1B70;
    *(int*)(pTheICEManager + offMode) = 1;
}

void ICEManager_EditorOff()
{
    const size_t offMode = 0x1B70;
    *(int*)(pTheICEManager + offMode) = 0;
}

//uintptr_t ICEManager_Get()
//{
//    return pTheICEManager;
//}