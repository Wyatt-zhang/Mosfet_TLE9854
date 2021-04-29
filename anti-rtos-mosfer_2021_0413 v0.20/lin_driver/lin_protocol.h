/*******************************************************************************
* Copyright (c) 2015, JE
* All Rights Reserved.
* Dept.: APG Shared
* File: lin_protocol.h
* Description:
* REQ IDs: 
* History:
* 2015-08-07,  Lei Yingjun
*******************************************************************************/

#ifndef LIN_PROTOCOL_H
#define LIN_PROTOCOL_H


//#include "global_variable.h"


/****** Define data type used for LIN driver *******/

typedef signed   char l_s8;
typedef unsigned char l_u8;

typedef volatile signed   char l_vs8;
typedef volatile unsigned char l_vu8;

typedef signed short l_s16;
typedef unsigned short l_u16;

typedef volatile signed short l_vs16;
typedef volatile unsigned short l_vu16;

typedef signed long l_s32;
typedef unsigned long l_u32;

typedef volatile signed long l_vs32;
typedef volatile unsigned long l_vu32;

typedef unsigned char l_bool;

#define CLEAR   0				
#define SET    1				

#define MAKE_PARITY   0					/* make parity bits */
#define CHECK_PARITY  1					/* check parity bits */

#define BIT(A,B)      (((A)>>(B))&0x01)   /* return bit has position \a B in byte \a A, A is the variable while */

/******************************** Typedefs **********************************/



/* Checksum type */
typedef enum LIN_CHECKSUM_T
{
  NORMAL_CHECKSUM,    
  ENHANCED_CHECKSUM   
} lin_checksum_type_t;

/* LIN error type */
typedef enum LIN_ERROR_T
{
	LIN_PID_ERR,              /* LIN_PID_ERR */
	LIN_FRAME_ERR ,           /* LIN_FRAME_ERR */
	LIN_CHECKSUM_ERR,         /* LIN_CHECKSUM_ERR */
	LIN_READBACK_ERR,         /* LIN_READBACK_ERR */
	LIN_NODATA_TIMEOUT,       /* Nodata timeout */
	LIN_BUS_ACTIVITY_TIMEOUT  /* LIN_BUS_ACTIVITY_TIMEOUT */
} lin_error_type_t;


/* lin sci sequence */
typedef enum LIN_DRIVER_SEQ_T
{
    LIN_UNINIT = 0,
    LIN_IDLE,
    LIN_SEND_BREAK,
    LIN_SEND_SYN,
    LIN_SEND_PID,
    LIN_RECEIVE_SYN,
    LIN_RECEIVE_PID,
    LIN_IGNORE_DATA,
    LIN_RECEIVE_DATA,
    LIN_SEND_DATA,
    LIN_SEND_DATA_COMPLETED,
    LIN_SLEEP_MODE,
}lin_driver_seq_t;


/* lin word status */
typedef union LIN_WORD_STATUS_T 
{                    
  l_u16 word;   
  struct 
  { 
	  l_u16 last_pid            :8;        /* Last PID */
	  
	  l_u16 error_in_response   :1;        /* Error in response */
	  l_u16 successful_transfer :1;        /* Successful transfer */
	  l_u16 overrun             :1;        /* Overrun */
	  l_u16 gotosleep           :1;        /* Goto sleep */
	  l_u16 bus_activity        :1;        /* Bus activity */
	  l_u16 frame_collision     :1;        /* Event triggered frame collision */
	  l_u16 save_config         :1;        /* Save configuration */
	  l_u16                     :1;        
  }bits; 
}lin_word_status_t;



/* types of frame */
typedef enum LIN_FRAME_TYPE_T
{
	LIN_FRM_UNCONDITIONAL  = 0x00,        /* Unconditional frame */
	LIN_FRM_EVENT  = 0x01,           	    /* Event triggered frame */
	LIN_FRM_SPORADIC = 0x10,              /* Sporadic frame */
	LIN_FRM_DIAGNOSTIC  = 0x11            /* Diagnostic frame */
}lin_frame_type_t;

/* lin frame response */
typedef enum LIN_FRAME_RESPONSE_T
{
	LIN_RES_NOTHING = 0x00,    	          /* This frame does not require to response */
	LIN_RES_PUB = 0x01,          	        /* Publisher response */
	LIN_RES_SUB = 0x10              	    /* Subscriber response */
}lin_frame_response_t;



/* product id structure */
typedef struct LIN_PRODUCT_ID_T
{
  l_u16 supplier_id;        /* Supplier ID */
  l_u16 function_id;        /* Function ID */
  l_u8 variant;             /* Variant value */
} lin_product_id_t;



/******************************** Functions **********************************/


extern l_u8 lin_process_parity(l_u8 pid, l_u8 type);
extern void lin_process_id(l_u8 frame_id, l_u8 frame_pid);
extern void lin_handle_error(lin_error_type_t error_type, l_u8 frame_id);
extern l_u8 lin_checksum(l_u8 *buffer, l_u8 length, l_u8 raw_pid);
extern void lin_update_rx(l_u8 frame_id);
extern void lin_update_tx(l_u8 frame_id);
extern void lin_goto_low_power_mode(void);

#endif  /*End of LIN_PROTOCOL_H */
/*--------EOF--------*/

