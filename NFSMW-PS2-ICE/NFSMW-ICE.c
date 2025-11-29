#include <stdint.h>
#include <string.h>
#include "NFSMW-ICE.h"
#include "ICEManager.h"
#include "Attrib.h"
#include "ActionQueue.h"
#include "NIS.h"
#include "ScreenPrintf.h"
#include "eViewPlatInterface.h"
#include "ePoly.h"
#include "includes/minjector.h"

#define BASEPOLY_HASH 0xC6AFDD7E
#define ICESPLASH_HASH 0x8F8D5FDB
#define SOLIDGREY_HASH 0x32283A11
#define GREYMAP_HASH 0x317EC0F4

// functions
//void*(*FastMem_Alloc)(size_t bytes, const char* kind) = (void*(*)(size_t, const char*))(0x280A70);
//const char*(*getActionIDString)(int id) = (const char*(*)(int))(0x2DA2C8);
void*(*GetTextureInfo)(unsigned int name_hash, int return_default_texture_if_not_found, int include_unloaded_textures) = (void*(*)(unsigned int, int, int))(0);

// constants
const char* CDActionDriveStr = (const char*)0x4872B8;
const char* CDActionDebugStr = (const char*)0x487488;
const char* CDActionIceStr = (const char*)0x48E800;
bool* Tweak_EnableICEAuthoring = (bool*)0x4EA82C;

// ICE runs at 30FPS
const float ScreenPrintfTime = (1.0f / 30.0f);

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
    *DoScreenPrintf = 1;
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


void IceScrPrintf(int x, int y, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    ScreenVPrintf(x, y, ScreenPrintfTime, 0xFFFFFFFF, fmt, args);

    va_end(args);
}



void IceScrShadowPrintf(int x, int y, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    ScreenVPrintf(x + 1, y + 1, ScreenPrintfTime, 0x80000000, fmt, args);
    ScreenVPrintf(x, y, ScreenPrintfTime, 0xFFFFFFFF, fmt, args);

    va_end(args);
}

unsigned int IceGetTextureID(int iceT)
{
    unsigned int result = 0;

    switch (iceT)
    {
        case ICETexture_eSolid:
            result = SOLIDGREY_HASH;
            break;
        case ICETexture_eAlpha:
            result = GREYMAP_HASH;
            break;
        case ICETexture_eLogo:
            result = ICESPLASH_HASH;
            break;
        default:
            //LOG("ERROR: UNKNOWN ICE TEXTURE ID: %d\n", iceT);
            break;
    }

    return result;
}

void IceSetPolyColor(unsigned char* dst, const bVector4* src)
{
    dst[0] = (unsigned char)(src->x);
    dst[1] = (unsigned char)(src->y);
    dst[2] = (unsigned char)(src->z);
    dst[3] = (unsigned char)(src->w);
}

void IceRenderPoly(void* view, ICEPoly* pPoly, bVector4* pColor0, bVector4* pColor1, int texture/*, void* pLocalWorld*/)
{
    ePoly outPoly;
    ePoly_ePoly(&outPoly);
    
    memcpy(outPoly.Vertices, pPoly->Vertices, sizeof(bVector3) * 4);

    // Z is messed up...
    outPoly.Vertices[0].z *= -4000.0f;
    outPoly.Vertices[1].z *= -4000.0f;
    outPoly.Vertices[2].z *= -4000.0f;
    outPoly.Vertices[3].z *= -4000.0f;
    
    // #TODO: for some reason the colors are (maybe) screwed up a bit...
    // figure out if gcc is messing up something or if the game is overwriting the colors mid-draw OR if it's just PCSX2 messing up...
    IceSetPolyColor(outPoly.Colours[0], pColor0);
    IceSetPolyColor(outPoly.Colours[1], pColor1);
    IceSetPolyColor(outPoly.Colours[2], pColor1);
    IceSetPolyColor(outPoly.Colours[3], pColor0);

    unsigned int texID = IceGetTextureID(texture);
    void* texinfo = GetTextureInfo(texID, 1, 0);

    eViewPlatInterface_Render(view, &outPoly, texinfo, 0);
}

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

    uintptr_t loc_14305C = 0x14305C;
    GetTextureInfo = (void* (*)(unsigned int, int, int))(minj_GetBranchDestination(loc_14305C));

    ScreenPrintf_Init();
    eViewPlatInterface_Init();
    ePoly_Init();


    //PrintActionIdEnum();
}

void NFSMW_ICE_PostInit()
{
    LOG("NFSMW_ICE_PostInit...\n");
    CreateICEManagerActionQ();
    ScreenPrintf_PostInit();

    minj_MakeJMPwNOP(0x16F360, (uintptr_t)&IceScrShadowPrintf);
    minj_MakeJMPwNOP(0x16F340, (uintptr_t)&IceScrPrintf);
    minj_MakeJMPwNOP(0x16F388, (uintptr_t)&IceRenderPoly);
}
