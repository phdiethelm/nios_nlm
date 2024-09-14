#ifndef __IFINFO_H__INCLUDED__
#define __IFINFO_H__INCLUDED__

#define SNPA_MX             10
#define UDP_OK              0

/* 
** Extended IP interface information block --
** Structure returned by the IPExtendedIFInfo API. 
*/

/* union to allow different interpretations of an IP address. */
typedef union ip_addr {
    unsigned char    ip_array[4];
    unsigned short   ip_short[2];
    unsigned long    ip_long;
} ip_addr;

/* 
** Extended IP interface information block --
** Structure returned by the IPExtendedIFInfo API. 
*/
typedef struct ip_extended_if_info {
   unsigned long      iex_signature;   /* API signature */
   unsigned long      iex_version;     /* API version   */
   unsigned long      iex_length;      /* buffer size    */
   unsigned long      iex_flags;        /* flags          */
   unsigned long      iex_if_id;        /* interface id   */
   unsigned long      iex_timestamp;    /* creation time  */
   ip_addr               iex_local_addr;   /* interface's IP address     */
   ip_addr               iex_net_mask;     /* network mask               */
   ip_addr               iex_broadcast;    /* broadcast address          */
   unsigned long      iex_packet_mx;  /* maximum outgoing packet    */
   unsigned long      iex_packet_opt; /* optimum outgoing packet    */
   unsigned long      iex_reasm_mx;   /* maximum reassembled packet */
   int                      iex_net_type;         /* network type               */
   unsigned long      iex_board_num;   /* ODI board number          */
   unsigned char      iex_our_snpa[ SNPA_MX ]; /* SNPA for interface  */
} ip_extended_if_info;

/* Miscellaneous constants */
#define IEX_SIGNATURE         0x49455849 /*'IEXI' */
#define IEX_MAJOR_VERSION     1
#define IEX_MINOR_VERSION     0
#define IEX_VERSION      ((IEX_MAJOR_VERSION << 16) | IEX_MINOR_VERSION)
#define IEX_BUFFER_SIZE       sizeof( ip_extended_if_info )
#define IEX_FIRST_INTERFACE   0

/*
Name:  IPExtendedIFInfo - return info about the next network interface

Sample Call:-
    
          info.iex_signature = IEX_SIGNATURE;
          info.iex_version   = IEX_VERSION;
          info.iex_length     = IEX_BUFFER_SIZE;
          info.iex_if_id        = IEX_FIRST_INTERFACE;
          while (IPExtendedIFInfo( &info ) == UDP_OK) {
               ...
          }

Description:
Return information about the next network interface.  The caller must
provide an information buffer at least as large as IEX_BUFFER_SIZE. 

Return:
UDP_OK                             Success // defined as Zero
UDPE_NORESOURCES        Null pointer or insufficient buffer space
USPE_BADVERSION            Illegal signature or version
UDPE_NOLOCAL                 No match found

*/

int IPExtendedIFInfo( struct ip_extended_if_info * );

#endif
