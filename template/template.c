/****************************************************************************************

  Project:  NIOS Experimentation

  Filename: template.c

  Author:   0xbadc0ded

  Purpose:  NIOS Client32 NLM Template

*****************************************************************************************

  Copyright (c) 2006 0xbadc0ded

****************************************************************************************/

#include "template.h"
#include <dosvmm.h>

//
//  Globals
//

static modHandle myModHandle; // Module Handle
static UINT8 **myMsgs = 0;    // Ptr to Messages in NLM file

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
    // Save some of the module parameters
    myModHandle = moduleHandle;
    myMsgs = msgs;

    // Say Hello World!
    NiosPrintf(myModHandle, MT_INFORM, "0xBADC0DED's TEMPLATE Module Version\r\n");
    NiosPrintf(myModHandle, MT_INFORM, "Copyright (c) 2006 0xbadc0ded, All rights reserved.\r\n");

    NiosPrintf(myModHandle, MT_INFORM, "Hello World!\r\n");

    return 0;
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
