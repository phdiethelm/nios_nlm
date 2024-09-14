/****************************************************************************************

  Project:  NIOS Experimentation

  Filename: listnlm.c

  Author:   0xbadc0ded

  Purpose:  Lists all loaded NLM's

*****************************************************************************************

  Copyright (c) 2006 0xbadc0ded

****************************************************************************************/

#include "listnlm.h"
#include <nios.h>
#include <module.h>

//
//  Globals
//

static modHandle myModHandle; // Module Handle
static UINT8 **myMsgs = 0;    // Ptr to Messages in NLM file

void ListNlmPrintHeader()
{
    NiosPrintf(myModHandle, MT_INFORM, "%-12s %-10s %-10s %-10s %-10s %-10s %-10s\r\n",
               "Name", "Nlm Type", "Ref Count", "Total Mem", "Init Rtn", "Exit Rtn", "Check Rtn");
    NiosPrintf(myModHandle, MT_INFORM,
               "------------ ---------- ---------- ---------- ---------- ---------- ----------\r\n");
}

//
//  NlmMain
//
//  Main of NLM Module
//    This function is called when the NLM is loaded to perform any
//    initialization necessary. If the return code from this function
//    is non-zero then the NLM is not loaded.
//
UINT32 NlmMain(modHandle moduleHandle,
               modHandle screenHandle,
               UINT8 *commandLine,
               UINT8 *moduleLoadPath,
               UINT32 unitializedDataLength,
               UINT32 customDataFileHandle,
               UINT32 (*readProc)(UINT32 customFileHandle, UINT32 customOffset, UINT8 *buf, UINT32 UINT8sToRead),
               UINT32 customDataOffset,
               UINT32 customDataSize,
               UINT32 numMsgs,
               UINT8 **msgs)
{
    // Variables
    struct LoadedModuleStruct modInfo;
    void *context = NULL;

    // Save some of the module parameters
    myModHandle = moduleHandle;
    myMsgs = msgs;

    // List Header
    ListNlmPrintHeader();

    while (0 == NiosEnumLoadedModules(&context, &modInfo, sizeof(modInfo)))
    {
        NiosPrintf(myModHandle, MT_INFORM, "%-12s 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X\r\n",
                   modInfo.name + 1,
                   modInfo.moduleType,
                   modInfo.numReferencedModules,
                   modInfo.totalAllocatedMemory,
                   modInfo.initRoutine,
                   modInfo.exitRoutine,
                   modInfo.checkRoutine);
    }

    return -1;
}

//
//  NlmCheckUnload
//
//  Check if module can be unloaded
//    This routine is called before unloading the NLM to determine if it
//    is safe to be unloaded. If the return code from this function
//    is non-zero then unloading the NLM is unsafe.
//
UINT32 NlmCheckUnload(void *ScreenID)
{
    return 0;
}

//
//  NlmExit
//
//  Exit of the NLM
//    This routine is called when the NLM module is unloaded from memory.
//
void NlmExit()
{
}
