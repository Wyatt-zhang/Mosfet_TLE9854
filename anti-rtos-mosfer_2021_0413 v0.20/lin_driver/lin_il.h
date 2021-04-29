/*******************************************************************************
* Copyright (c) 2015, JE
* All Rights Reserved.
* Dept.: APG Shared
* File: lin_il.h
* Description:
* REQ IDs: 
* History:
* 2015-08-07,  Lei Yingjun
*******************************************************************************/

#ifndef LIN_IL_H
#define LIN_IL_H


#include "lin_protocol.h"


/*接收帧，数据域的定义*/
typedef union
{
    l_u8  bytes[8];

    struct
    {
              /*1st byte*/ 
      l_u32  reserved1			:8;
        
              /*2nd byte*/ 
      l_u32  reserved2			:8;
        
        /*3rd byte*/
l_u32  reseved3          :4;
l_u32  SWCMDtoFL			:3;
l_u32  RRWindowLock			:1;
      
      /*4th byte*/         
      l_u32  reserved4			:8;
        
            /*5th byte*/ 
      l_u32  reserved5			:8;
        
      /*6th byte*/
      l_u32  WindowCMDtoFL                  :3;
      l_u32  WindowCMDtoFR                  :3;
      l_u32  reserved6                    :2;
      
      /*7th byte*/        
      l_u32  reserved7                  :8;
        /*8th byte*/
      l_u32  reserved8                  :8;
    }ctr;
    
}lin_rx_data_t;

/*发送帧，数据域的定义*/
typedef union
{
    l_u8  bytes[8];   
  
    struct
    {
        /*1st byte*/
      l_u32  InitState			:1;
      l_u32  WindowAction		:2;
        l_u32 WindowPosState         :2;
        l_u32  WindowState       :2;
        l_u32  ResError          :1;
        
       /*2nd byte*/ 
l_u32  ECUerror			:1;
l_u32  SWAutoUp			:1;
l_u32  SWAutoDown			:1;
l_u32  SWManualUp			:1;
l_u32  SWManualDown			:1;  
l_u32  Reserved2			:1;   
l_u32  OverHeatProtect			:1;
l_u32  APState			:1;
  
       /*3rd byte*/ 
      l_u32  WindowPosPercent			:8;
       
            /*4th byte*/
      l_u32  reserved4			:8;
        
        /*5th byte*/
      l_u32  reserved5			:8;
        
      /*6th byte*/

      l_u32  reserved6                    :8;
      
      /*7th byte*/        
      l_u32  reserved7                  :8;
        /*8th byte*/
      l_u32  reserved8                  :8;
             
    }st;
    
}lin_tx_data_t;


/******************************** Variable **********************************/
 
extern lin_rx_data_t rx_data;
extern lin_tx_data_t tx_data;

extern l_bool err_frame_sent_flg;
extern l_bool st_frame_sent_flg;



/******************************** Functions **********************************/
void lin_signal_init(void);

void frame_unpack_ctr(void);
void frame_pack_st(void);
void frame_do_nothing(void);

void lin_rx_diag_frame(void);
void lin_period_handle(void);

l_bool get_ctr_frame_timeout_flg(void);



#endif  /*End of LIN_IL_H */
/*--------EOF--------*/
