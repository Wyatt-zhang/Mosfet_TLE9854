/*******************************************************************************
* Copyright (c) 2015, JE
* All Rights Reserved.
* Dept.: APG Shared
* File: lin_tl_protocol.h
* Description:
* REQ IDs: 
* History:
* 2015-08-07,  Lei Yingjun
*******************************************************************************/

#ifndef LIN_TL_PROTOCOL_H
#define LIN_TL_PROTOCOL_H


#include "lin_protocol.h"


#define MAX_QUEUE_SIZE    40       /* maximum size of queue */

#define LD_FUNCTIONAL_NAD      0x7E   /* functional NAD */
#define LD_BROADCAST_NAD       0x7F   /* broadcast NAD */
#define LD_ANY_SUPPLIER        0x7FFF /* Supplier ID */
#define LD_ANY_FUNCTION        0xFFFF /* Function ID */ 


#define PCI_SF            0x00     /* single frame */
#define PCI_FF            0x10     /* first frame */
#define PCI_CF            0x20     /* consecutive frame */


#define NT_SF_DATA_LENGTH  6
#define NT_FF_DATA_LENGTH  5
#define NT_CF_DATA_LENGTH  6


/******************************** Typedefs **********************************/

/* status of queue */
typedef enum 
{                           
  LD_NO_DATA,         /* Queue is empty, has no data */
  LD_DATA_AVAILABLE,  /* data in queue is available */
  LD_RECEIVE_ERROR,   /* receive data is error */
  LD_QUEUE_FULL,      /* the queue is full */
  LD_QUEUE_AVAILABLE, /* queue is available for insert data */
  LD_QUEUE_EMPTY,     /* queue is empty */
  LD_TRANSMIT_ERROR   /* error while transmitting */
}ld_queue_status_t;


/* status of lin tl message */
typedef enum 
{ 
  LD_NO_MSG,            /* no message */               
  LD_IN_PROGRESS,       /* in progress */
  LD_COMPLETED,         /* completed */
  LD_FAILED,            /* failed */
  LD_N_AS_TIMEOUT,      /* N_As timeout */
  LD_N_CR_TIMEOUT,      /* N_Cr timeout */
  LD_WRONG_SN           /* wrong sequence number */
}lin_tl_msg_status_t;


/* types of tl timeout */
typedef enum 
{
  LD_NO_CHECK_TIMEOUT,      /* No check timeout */
  LD_CHECK_N_AS_TIMEOUT,    /* check N_As timeout */
  LD_CHECK_N_CR_TIMEOUT     /* check N_Cr timeout */
}lin_tl_timeout_t;


/* TP mode */
typedef enum 
{
   TL_MODE_IDLE     = 0u, /* Waiting,   not actively sending/receiving */
   TL_MODE_SEND_SF,       /* Sending,   sending SF                     */
   TL_MODE_SEND_FF,       /* Sending,   sending FF                     */
   TL_MODE_SEND_CF,       /* Sending,   sending CF                     */
   TL_MODE_WAIT_CF,       /* Receiving, waiting CF                     */
}lin_tl_mode_t;


typedef enum 
{
  TL_ERROR_OK = 0u,           /*everything run as expected - no error*/
  TL_ERROR_WRONG_SN,          /*Wrong SquenceNumber*/
  TL_ERROR_SF_UNEXPECTED,     /*SF unexpected*/
  TL_ERROR_FF_UNEXPECTED,     /*FF unexpected*/
  TL_ERROR_CF_UNEXPECTED,     /*CF unexpected*/
  TL_ERROR_WRONG_LIN_FRAME,   /*Wrong LIN frame*/
  TL_ERROR_WRONG_NT_FRAME,    /*Wrong TP frame*/
  TL_ERROR_MESSAGE_TOO_BIG,   /*Message too big for buffer size*/
  TL_ERROR_TIMEOUT,           /*Timeout expires*/
  TL_ERROR_INTERNAL,          /*Internal Error*/
  TL_ERROR_UNKNOWN_FRAME
} lin_tl_error_t;



/******************************** Variable **********************************/

#define TL_RX_BUFFER            lin_frame_cfg_array[LIN_FRAME_MASTER_REQUEST].pbuffer
#define TL_TX_BUFFER            lin_frame_cfg_array[LIN_FRAME_SlAVE_RESPONSE].pbuffer

typedef struct
{
    lin_tl_mode_t     mode;             /* mode  */
    
    l_u8    queue[MAX_QUEUE_SIZE];   /* receive queue data */
    
    ld_queue_status_t rx_queue_status;
    ld_queue_status_t tx_queue_status;    
    
    l_u16   index;                   /* index of message in tx queue */
    l_u16   length;                  /* length of message in tx queue */
    
    struct
    {
        l_u8 st;                        /* space time between 2 consective frame */
        l_u8 sn;                        /* serial number of consective frame */
    } cf;
    
    struct
    {
        l_u16       counter;            /* timeout counter */
        lin_tl_timeout_t   type;        /* TL timeout type */
    } timeout;

}lin_tl_data_t;

extern lin_tl_data_t lin_tl_data;


/******************************** Functions **********************************/

extern void tl_data_init(void);
extern void tl_timer_task(void);
extern void lin_tl_rx_handler(void);
extern void lin_tx_response_msg(const l_u8 * diag_data, l_u16 diag_data_length);
extern l_bool lin_tl_tx_task(void);
extern void lin_tl_error_handle(lin_tl_error_t tl_error_type);

extern l_u16 tl_get_rx_length(void);
extern l_u8 tl_get_rx_data(l_u16 index);

 
#endif /*End of LIN_TL_PROTOCOL_H */
/*--------EOF--------*/


