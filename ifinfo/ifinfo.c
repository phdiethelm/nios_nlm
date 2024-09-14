/****************************************************************************************

  Project:  NIOS Experimentation

  Filename: ifinfo.c

  Author:   0xbadc0ded

  Purpose:  NIOS TCP/IP Interface information

*****************************************************************************************

  Copyright (c) 2006 0xbadc0ded

****************************************************************************************/

#include "ifinfo.h"
#include "undoc_ifinfo.h"
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
    // Variables used
    ip_extended_if_info ifinfo;

    // Save some of the module parameters
    myModHandle = moduleHandle;
    myMsgs = msgs;

    // Get Interface Information
    ifinfo.iex_signature = IEX_SIGNATURE;
    ifinfo.iex_version = IEX_VERSION;
    ifinfo.iex_length = IEX_BUFFER_SIZE;
    ifinfo.iex_if_id = IEX_FIRST_INTERFACE;

    while (IPExtendedIFInfo(&ifinfo) == UDP_OK)
    {
        NiosPrintf(myModHandle, MT_INFORM, "Interface Information for Board id %d\r\n", ifinfo.iex_board_num);

        // Print Network type
        NiosPrintf(myModHandle, MT_INFORM, "    Network Type:     0x%08X\r\n", ifinfo.iex_net_type);
        NiosPrintf(myModHandle, MT_INFORM, "    Max. Packet size: %ld bytes\r\n", ifinfo.iex_packet_mx);
        NiosPrintf(myModHandle, MT_INFORM, "    Opt. Packet size: %ld bytes\r\n", ifinfo.iex_packet_opt);

        // Print IP Address
        NiosPrintf(myModHandle, MT_INFORM, "    IP Address:       %d.%d.%d.%d\r\n",
                   ifinfo.iex_local_addr.ip_array[0],
                   ifinfo.iex_local_addr.ip_array[1],
                   ifinfo.iex_local_addr.ip_array[2],
                   ifinfo.iex_local_addr.ip_array[3]);

        // Print Subnet mask
        NiosPrintf(myModHandle, MT_INFORM, "    Subnet Mask:      %d.%d.%d.%d\r\n",
                   ifinfo.iex_net_mask.ip_array[0],
                   ifinfo.iex_net_mask.ip_array[1],
                   ifinfo.iex_net_mask.ip_array[2],
                   ifinfo.iex_net_mask.ip_array[3]);
        // Print MAC address

        NiosPrintf(myModHandle, MT_INFORM, "    Physical Address: %02X:%02X:%02X:%02X:%02X:%02X\r\n",
                   ifinfo.iex_our_snpa[SNPA_MX - 6],
                   ifinfo.iex_our_snpa[SNPA_MX - 5],
                   ifinfo.iex_our_snpa[SNPA_MX - 4],
                   ifinfo.iex_our_snpa[SNPA_MX - 3],
                   ifinfo.iex_our_snpa[SNPA_MX - 2],
                   ifinfo.iex_our_snpa[SNPA_MX - 1],
                   ifinfo.iex_our_snpa[SNPA_MX - 0]);

        NiosPrintf(myModHandle, MT_INFORM, "\r\n");
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
UINT32 NlmCheckUnload(void *screenID)
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
