/****************************************************************************************

  Project:  NIOS Experimentation

  Filename: template.h

  Author:   0xbadc0ded

  Purpose:  Template of NLM Project

*****************************************************************************************

  Copyright (c) 2006 0xbadc0ded

****************************************************************************************/

#ifndef __TEMPLATE_H__INCLUDED__
#define __TEMPLATE_H__INCLUDED__

#include    <nios.h>
#include    <nstdlib.h>

UINT32 NlmMain( modHandle myModuleHandle,
                modHandle unusedScreenHandle,
                UINT8  *commandLine,
                UINT8  *moduleLoadPath,
                UINT32 unitializedDataLength,
                UINT32 customDataFileHandle,
                UINT32 (*readProc)(),
                UINT32 customDataOffset,
                UINT32 customDataSize,
                UINT32 numMsgs,
                UINT8  **msgs );
UINT32 NlmCheckUnload (void*);
void NlmExit (void);

// Define the message macro
#define	MSG(a,b) myMsgs[b]

#endif // __TEMPLATE_H__INCLUDED__
