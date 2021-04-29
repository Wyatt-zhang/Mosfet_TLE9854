/*******************************************************************************
* Copyright (c) 2015, JE
* All Rights Reserved.
* Dept.: APG Shared
* File: lin_config.h
* Description:
* REQ IDs: 
* History:
* 2015-08-07,  Lei Yingjun
*******************************************************************************/

#ifndef LIN_CONFIG_H
#define LIN_CONFIG_H


#include "lin_protocol.h"


/****** Autobaud ******/
//#define AUTOBAUD_ENABLED


/* Define operating mode */
#define MASTER_MODE     0 
#define SLAVE_MODE      1 
#define LIN_OPERATE_MODE   SLAVE_MODE


/* Define protocol version */
#define PROTOCOL_21       0  
#define PROTOCOL_J2602    1  
#define PROTOCOL_20       2 
#define LIN_PROTOCOL    PROTOCOL_21


/***** Diagnostic class selection ******/
#define DIAG_CLASS_I          0
#define DIAG_CLASS_II         1
#define DIAG_CLASS_III        2

#define DIAG_CLASS_SUPPORT    DIAG_CLASS_III

/****** FRAME SUPPORT DEFINITION *******/
#define TL_SINGLE_FRAME       0
#define TL_MULTI_FRAME        1

#define TL_FRAME_SUPPORT      TL_MULTI_FRAME


/************************** Interfaces *************************/
typedef enum 
{ 
   LI0
}l_ifc_handle;



#define MCU_BUS_CLK      40000000

//通信的波特率
#define LIN_BAUD_RATE    19200

//lin通信的时基？
#define TIME_BASE_PERIOD   1000

//总线上无信号的时间？
#define IDLE_STATE_TIMEOUT_VALUE    5000   /* [1ms], */

/**************************   Frame   *****************************/

/* Number of frames */
#define LIN_NUM_OF_FRAMES  4 

/* List of lin frames */
typedef enum 
{
   LIN_FRAME_CTR = 0,  
   
   LIN_FRAME_ST,

   LIN_FRAME_MASTER_REQUEST,
   LIN_FRAME_SlAVE_RESPONSE,
} lin_frame_handle; 

/* lin frame config */
typedef struct LIN_FRAME_CONFIG_T
{
   lin_frame_type_t frame_type;
   lin_frame_response_t response_type;   
   l_u8 	data_length;
   l_u8   *pbuffer;
   void (*process_fun)(void);
}lin_frame_config_t;

typedef union LIN_FRAME_STATE_T
{
   l_u8 all;
   struct
   {
  	 l_u8 new_msg   : 1;
  	 l_u8 overide   : 1;
  	 l_u8 timeout   : 1;
  	 l_u8 rsvd      : 5;
   }bit;
}lin_frame_state_t;

typedef struct LIN_FRAME_BUF_CFG_T
{
   lin_frame_state_t msg_st;
   l_u16 period; /* [10ms] */
   l_u16 tick;
}lin_frame_buf_cfg_t;


#define LIN_FRAME_CHECK(frame_index)          (0 != lin_frame_buf_array[frame_index].msg_st.bit.new_msg)
#define LIN_FRAME_SET_NEW(frame_index)        lin_frame_buf_array[frame_index].msg_st.bit.new_msg = 1
#define LIN_FRAME_OVERIDE(frame_index)        lin_frame_buf_array[frame_index].msg_st.bit.overide = 1
#define LIN_FRAME_CLEAR(frame_index)       do {   lin_frame_buf_array[frame_index].msg_st.bit.new_msg = 0; \
                                              lin_frame_buf_array[frame_index].msg_st.bit.overide = 0; \
                                              lin_frame_buf_array[frame_index].msg_st.bit.timeout = 0; \
                                          }while(0)

#define LIN_FRAME_EMPTY_CHECK(frame_index)    (0 == lin_frame_buf_array[frame_index].msg_st.bit.new_msg)
#define LIN_FRAME_TIMEOUT_SET(frame_index)    lin_frame_buf_array[frame_index].msg_st.bit.timeout = 1
#define LIN_FRAME_TIMEOUT_CLEAR(frame_index)  lin_frame_buf_array[frame_index].msg_st.bit.timeout = 0
#define LIN_FRAME_RESET_TIMETICK(frame_index) lin_frame_buf_array[frame_index].tick = lin_frame_buf_array[frame_index].period
#define LIN_FRAME_TIMEOUT_CHECK(frame_index)  (0 != lin_frame_buf_array[frame_index].msg_st.bit.timeout)


/************************** variables *****************************/


extern lin_word_status_t lin_word_status;

extern l_bool lin_goto_sleep_flg;
extern l_bool lin_mute_flg;


extern l_u8 lin_driver_response_buffer[9];


extern l_u8 lin_frame_cfg_id[LIN_NUM_OF_FRAMES];
extern const lin_frame_config_t lin_frame_cfg_array[LIN_NUM_OF_FRAMES];
extern lin_frame_buf_cfg_t lin_frame_buf_array[LIN_NUM_OF_FRAMES];


extern l_u16 lin_frame_timeout_val[8];
extern const l_u16 lin_frame_timeout_val_19200[8];
extern const l_u16 lin_frame_timeout_val_9600[8];
extern const l_u16 lin_frame_timeout_val_4800[8];

extern lin_product_id_t product_id;


/************************** functions *****************************/

extern l_u8 get_configured_nad(void);
extern void set_configured_nad(l_u8 nad);

extern l_u8 get_initial_nad(void);
extern void set_initial_nad(l_u8 nad);




 #endif  /*End of LIN_CONFIG_H */
/*--------EOF--------*/


