/*******************************************************************************
* Copyright (c) 2015, JE
* All Rights Reserved.
* Dept.: APG Shared
* File: lin_il.c
* Description:
* REQ IDs: 
* History:
* 2015-08-07,  Lei Yingjun
*******************************************************************************/

#include "lin_il.h"
#include "lin_config.h"
#include "lin_tl_protocol.h"


#define T_DIAG_START_TIME		100
static l_u8 u8_diag_start_timer = T_DIAG_START_TIME;	/* 400ms */

/*结构体对象，接收和发送*/
lin_rx_data_t rx_data;
lin_tx_data_t tx_data;


static l_bool ctr_frame_timeout_flg = 0; /* CTR Frame timeout flag */


l_bool err_frame_sent_flg = 0;
l_bool st_frame_sent_flg = 0;

/**********************************************************************************
* Function: lin_signal_init
* Param:
* Return<void>:
* REQ IDs:
* Discription:
* Note:
************************************************************************************/
void lin_signal_init(void)
{
    l_u8 index= 0;
    
 
    while(index++ <=7)
    {
        rx_data.bytes[index]=0;
        tx_data.bytes[index]=0;
    }
    #if 0
    rx_data.ctr.position_request = 0;
    rx_data.ctr.position_reset = 0; 
    rx_data.ctr.torque_request = 0;
    rx_data.ctr.request_move_enable = 0;    
    rx_data.ctr.position_default = 0;
    rx_data.ctr.reserved1 = 0x3F;     
    
    
    tx_data.st.roll_count = 0;
    tx_data.st.internal_fault = 1u;
    tx_data.st.operational_fault = 0;
    tx_data.st.torque_feedback = 0;
    tx_data.st.com_err = 0;
    tx_data.st.position_feedback = 0;   
    tx_data.st.reserved = 0x3FFF;
    #endif 

}


/**********************************************************************************
* Function: frame_unpack_ctr
* Param:
* Return<void>:
* REQ IDs:
* Discription:
* Note:
************************************************************************************/

/*接收帧，数据域的处理*/
void frame_unpack_ctr(void)
{
        
    l_u8 index= 0;
    
    ctr_frame_timeout_flg = 0;
   
    while(index<=7)
    {
        rx_data.bytes[index] = lin_frame_cfg_array[LIN_FRAME_CTR].pbuffer[index];
        
        index++;
    }
}


/**********************************************************************************
* Function: frame_pack_st
* Param:
* Return<void>:
* REQ IDs:
* Discription:
* Note:
************************************************************************************/
void frame_pack_st(void)
{
    l_u8 index= 0;
    
    while(index<=7)
    {
        lin_frame_cfg_array[LIN_FRAME_ST].pbuffer[index] = tx_data.bytes[index];
        
        index++;
    }


}


/**********************************************************************************
* Function: frame_do_nothing
* Param:
* Return<void>:
* REQ IDs:
* Discription:
* Note:
************************************************************************************/
void frame_do_nothing(void)
{

}

/**********************************************************************************
* Function: lin_rx_diag_frame
* Param:
* Return<void>:
* REQ IDs:
* Discription:
* Note:
************************************************************************************/
void lin_rx_diag_frame(void)
{   
    /* check diagnostic request */
    if(0 != LIN_FRAME_CHECK(LIN_FRAME_MASTER_REQUEST))
    {
        LIN_FRAME_CLEAR(LIN_FRAME_MASTER_REQUEST);
        
        if(0x00 == lin_frame_cfg_array[LIN_FRAME_MASTER_REQUEST].pbuffer[0])  /* Check goto sleep */
        {
            lin_goto_sleep_flg = 1;

            //lin_goto_low_power_mode(); 
        }
        else
        {
            lin_tl_rx_handler();   /* LIN transport layer */
        }
    }  
}


/**********************************************************************************
* Function: lin_period_handle
* Param:
* Return<void>:
* REQ IDs:
* Discription:
* Note:
************************************************************************************/
void lin_period_handle(void)
{
    l_u8 frame_index;   
    
    for(frame_index = 0; frame_index < LIN_NUM_OF_FRAMES; frame_index++)
    {
       if(lin_frame_buf_array[frame_index].period > 0)
       {
            if(LIN_RES_SUB == lin_frame_cfg_array[frame_index].response_type)	/* frame to receive */
            {
                if(0 != LIN_FRAME_CHECK(frame_index))
                {
//                    LIN_FRAME_RESET_TIMETICK(frame_index);
//                  if(lin_frame_cfg_array[frame_index].process_fun != NULL)
//          		{
//          			lin_frame_cfg_array[frame_index].process_fun();
//          		}
                }
                else
                {
                    if(lin_frame_buf_array[frame_index].tick > 0)
                    {
                        lin_frame_buf_array[frame_index].tick--;
                    }
                    if(0 == lin_frame_buf_array[frame_index].tick)
                    {
                        LIN_FRAME_RESET_TIMETICK(frame_index);
                        LIN_FRAME_TIMEOUT_SET(frame_index);
                    }
                }              
            }
            else if(LIN_RES_PUB == lin_frame_cfg_array[frame_index].response_type)  /* frame to tx */
            {
              
            }
            else
            {
            }
       }
    }
       
    
  	if(u8_diag_start_timer > 0)
  	{
            u8_diag_start_timer--;
            LIN_FRAME_RESET_TIMETICK(LIN_FRAME_CTR);
            LIN_FRAME_TIMEOUT_CLEAR(LIN_FRAME_CTR);        /*ZHENG LIU 20170222*/
  	}
        else
	{
            /* frame CTR timeout diagnose */
            if(LIN_FRAME_TIMEOUT_CHECK(LIN_FRAME_CTR))
            {
                LIN_FRAME_TIMEOUT_CLEAR(LIN_FRAME_CTR);
                ctr_frame_timeout_flg = 1; 
            }
            else if(LIN_FRAME_CHECK(LIN_FRAME_CTR))
            {
                LIN_FRAME_CLEAR(LIN_FRAME_CTR);
                ctr_frame_timeout_flg = 0;
            }
            else
            {
            }    
	}
    
}


/********************************************************************************
 * Function: get_ctr_frame_timeout_flg
 * Param<void>:
 * Return<>:
 * REQ IDs:
 * Discription:
 * Note:
*********************************************************************************/
l_bool get_ctr_frame_timeout_flg(void)
{
    return(ctr_frame_timeout_flg); 
}

