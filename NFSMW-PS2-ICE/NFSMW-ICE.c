#include <stdint.h>
#include <string.h>
#include "NFSMW-ICE.h"
#include "ICEManager.h"
#include "Attrib.h"
#include "ActionQueue.h"
#include "NIS.h"
#include "ScreenPrintf.h"
//#include "includes/ps2timeutil.h"
#include "includes/minjector.h"

// functions
//void*(*FastMem_Alloc)(size_t bytes, const char* kind) = (void*(*)(size_t, const char*))(0x280A70);
//const char*(*getActionIDString)(int id) = (const char*(*)(int))(0x2DA2C8);

// constants
const char* CDActionDriveStr = (const char*)0x4872B8;
const char* CDActionDebugStr = (const char*)0x487488;
const char* CDActionIceStr = (const char*)0x48E800;
bool* Tweak_EnableICEAuthoring = (bool*)0x4EA82C;
int* DoScreenPrintf = (int*)0x525DA4;

ActionQueue IceInputQ;
int DoScreenPrintf_Backup;

// internal funcs
void CreateICEManagerActionQ()
{
    ActionQueue_ActionQueue(&IceInputQ, 1, Attrib_StringHash64("ice"), "ice", false);
    ICEManager_SetActionQ(&IceInputQ);
}

void SetCameraAIDesiredMode(CameraAI_Director* director, const char* mode)
{
    director->mDesiredMode.mString = mode;
    director->mDesiredMode.mHash32 = Attrib_StringHash32(mode);
    director->mDesiredMode.mHash64 = Attrib_StringHash64(mode);
}

void EnableICEEditor(CameraAI_Director* director)
{
    *Tweak_EnableICEAuthoring = true;
    SetCameraAIDesiredMode(director, CDActionIceStr);
    DoScreenPrintf_Backup = *DoScreenPrintf;
    *DoScreenPrintf = 0;
}

void ToggleDebugCam(CameraAI_Director* director)
{
    if (*Tweak_EnableICEAuthoring)
    {
        *Tweak_EnableICEAuthoring = false;
        SetCameraAIDesiredMode(director, CDActionDriveStr);
        *DoScreenPrintf = DoScreenPrintf_Backup;
    }
    else
    {
        SetCameraAIDesiredMode(director, CDActionDebugStr);
    }
}

void CameraAI_Director_SelectDebugAction(CameraAI_Director* director)
{
    void* mInputQ = &director->mInputQ;

    while (!ActionQueue_IsEmpty(mInputQ))
    {
        ActionRef ref = ActionQueue_GetAction(mInputQ);

        if (ref.actiondata->data)
        {
            switch (ref.actiondata->id)
            {
                case CAMERAACTION_ENABLE_ICE:
                    EnableICEEditor(director);
                    break;
                case CAMERAACTION_DEBUG:
                    ToggleDebugCam(director);
                    break;
                default:
                    break;
            }
        }

        ActionQueue_PopAction(mInputQ);
    }
}

int CheckICEEditor(int prevRet)
{
    int retVal = prevRet;
    if (!retVal)
    {
        *Tweak_EnableICEAuthoring = false;
        return retVal;
    }

    void* nisscene = NIS_GetScene(NULL);
    if (nisscene != 0)
    {
        *Tweak_EnableICEAuthoring = false;
        return 0;
    }

    if (*Tweak_EnableICEAuthoring)
    {
        ICEManager_EditorOn();
    }

    return retVal;
}

//void PrintActionIdEnum()
//{
//    const int numActionIds = 0x87;
//
//    LOG("enum ActionID\n{\n");
//    for (int i = 0; i < numActionIds; i++)
//    {
//        LOG("\t%s,\n", getActionIDString(i));
//    }
//    LOG("}\n");
//}

// hooks
void hkCameraAI_Director_SelectAction();
#ifndef __INTELLISENSE__
asm
(
    ".global hkCameraAI_Director_SelectAction\n"
    "hkCameraAI_Director_SelectAction:\n"
    "addiu $sp, -0x10\n"
    "sd $ra, 0($sp)\n"
    "move $a0, $s2\n" // THIS IS IN THE BRANCH DELAY SLOT
    "jal CameraAI_Director_SelectDebugAction\n"
    "ld $ra, 0($sp)\n"
    "addiu $sp, 0x10\n"
    "lw $v0, 0x2BC($s2)\n"
    "lui $v1, 0x16\n"
    "lw $a2, 0x18($s2)\n"
    "beqzl $v0, loc_163C34\n"
    "addiu $v1, $v1, 0x3BDC\n"
    "jr $v1\n"
    "loc_163C34:\n"
    "addiu $v1, $v1, 0x3C34\n"
    "jr $v1\n"
);
#endif

void hkCDActionIce_Construct();
#ifndef __INTELLISENSE__
asm
(
    ".global hkCDActionIce_Construct\n"
    "hkCDActionIce_Construct:\n"
    "addiu $sp, -0x10\n"
    "sd $ra, 0($sp)\n"
    "jalr $v0\n"
    "move $a0, $v0\n"
    "jal CheckICEEditor\n"
    "ld $ra, 0($sp)\n"
    "addiu $sp, 0x10\n"
    "jr $ra\n"
    "nop\n"
);
#endif


void NFSMW_ICE_Init()
{
	LOG("NFSMW_ICE_Init...\n");

    uintptr_t loc_163BD4 = 0x163BD4;
    minj_MakeJMPwNOP(loc_163BD4, (uintptr_t)&hkCameraAI_Director_SelectAction);
    uintptr_t loc_16881C = 0x16881C;
    minj_MakeCALL(loc_16881C, (uintptr_t)&hkCDActionIce_Construct);

    ScreenPrintf_Init();

    //PrintActionIdEnum();
}

void NFSMW_ICE_PostInit()
{
    LOG("NFSMW_ICE_PostInit...\n");
    CreateICEManagerActionQ();
}
