/*******************************************************************************
* Copyright (c) 2015, JE
* All Rights Reserved.
* Dept.: APG Shared
* File: lin_protocol.c
* Description:
* REQ IDs: 
* History:
* 2015-08-07,  Lei Yingjun
*******************************************************************************/

#include "lin_protocol.h"
#include "lin_config.h"
#include "lin_hal.h"
#include "lin_il.h"
#include "lin_tl_protocol.h"
#include "lin_diagnostic_support.h"


/****************************************************************************
 * Function: lin_process_parity
 * Param<void>:  pid: PID need to be send;  type: Check or Make parity
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
l_u8 lin_process_parity(l_u8 pid, l_u8 type)
{
    l_u8 parity;
    l_u8 ret;

    parity =(((BIT(pid,0)^BIT(pid,1)^BIT(pid,2)^BIT(pid,4))<<6)|
            ((~(BIT(pid,1)^BIT(pid,3)^BIT(pid,4)^BIT(pid,5)))<<7));  
    
    if (CHECK_PARITY == type)
    {
        if((pid & 0xC0u) != parity)
        {
            ret = 0xFF;
        }
        else
        {
            ret = (l_u8)(pid & 0x3Fu);
        }
    } 
    else 
    {
        ret = (l_u8)(pid | parity);
    }

    return (ret);  
}


/****************************************************************************
 * Function: lin_checksum
 * Param<void>:  
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
l_u8 lin_checksum(l_u8 *buffer, l_u8 length, l_u8 raw_pid)
{
    l_u16 check_sum;

    /* 1. PID correspond to Master request and Slave response, their checksum cal is classic
    the non-diagnostic frame is calculated in Enhanced */
    if((0x3C != raw_pid) && (0x7D != raw_pid))
    {
        check_sum = raw_pid;
    }
    else
    {
  	check_sum = 0;
    }

    for (; 0 < length; length--) 
    {
        check_sum += *(buffer++);
        /* 2. to deal with the carry  */
        if (check_sum > 0xFF)
        {
    	    check_sum -= 0xFF;
    	}
    }

    /* 3. to reverse */
    return (l_u8)(~check_sum);
}



/****************************************************************************
 * Function: lin_process_pid
 * Param<void>:  
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
void lin_process_id(l_u8 frame_id, l_u8 frame_pid)
{
    l_u8 i,j;
    l_u8 action;
    
    lin_goto_sleep_flg = 0;      /* Clear goto sleep flag */
    lin_mute_flg = 0;
  
    for (i = 0; i < LIN_NUM_OF_FRAMES; i++)
    {
        if(frame_id == lin_frame_cfg_id[i])
        {
            if(LIN_RES_PUB == lin_frame_cfg_array[i].response_type)  /* tx */
            {
                if(LIN_FRM_DIAGNOSTIC == lin_frame_cfg_array[i].frame_type) /* diagnostic frame */
                {
                    action = lin_tl_tx_task();
                    if(CLEAR == action)
                    {
                        lin_goto_idle_state();
                        break;
                    }
                }
                else if(LIN_FRM_EVENT == lin_frame_cfg_array[i].frame_type) /* event frame */
                {
//                    if((0x00 == tx_data.button_status) || (0x07 == tx_data.button_status))                
                    {
                        lin_goto_idle_state();
                        break;  
                    }
                }
                else
                {
                }
                
                lin_frame_cfg_array[i].process_fun();   
            
                for(j=0; j< lin_frame_cfg_array[i].data_length; j++)
                {
                    lin_driver_response_buffer[j] = lin_frame_cfg_array[i].pbuffer[j]; 
                }
                
                lin_driver_response_buffer[j] = lin_checksum(lin_driver_response_buffer, lin_frame_cfg_array[i].data_length, frame_pid);
                
                lin_sci_tx_response(lin_frame_cfg_array[i].data_length);
            }
            else if(LIN_RES_SUB == lin_frame_cfg_array[i].response_type)  /* rx */
            {
                lin_sci_rx_response(lin_frame_cfg_array[i].data_length); 
            }
            else
            {
                lin_goto_idle_state();
            }
          
            break; 
        }
    }
    
    if(i == LIN_NUM_OF_FRAMES)
    {
        lin_goto_idle_state();
    }
}



/****************************************************************************
 * Function: lin_handle_error
 * Param<void>:  
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
void lin_handle_error(lin_error_type_t error_type, l_u8 frame_id)
{
    switch (error_type) 
    {
        case LIN_PID_ERR:
          /* do nothing here */
            break;
        /* Frame error */
        case LIN_FRAME_ERR:
        case LIN_CHECKSUM_ERR:
        case LIN_READBACK_ERR:
        case LIN_NODATA_TIMEOUT:      
//            lin_error_in_response = 1;
            lin_word_status.bits.error_in_response = 1;
            if(0x3C == frame_id)
            {
								lin_tl_error_handle(TL_ERROR_WRONG_NT_FRAME);			/* LIN2.1 Conformance Test */
            }
            else if(0x3D == frame_id)
            {
              
            }
            else
            {
            }
            break;
            
        default:
            break;    
    }
    
//    lin_update_err_signal();
}



/****************************************************************************
 * Function: lin_update_rx
 * Param<void>:  
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
void lin_update_rx(l_u8 frame_id)
{
    l_u8 i,j;
    
//    lin_successful_transfer = 1;    /* Set successful transfer */
    lin_word_status.bits.successful_transfer = 1;
    
    for (i = 0; i < LIN_NUM_OF_FRAMES; i++)
    {
        if(frame_id == lin_frame_cfg_id[i])
        {
            for(j=0; j< lin_frame_cfg_array[i].data_length; j++)
            {
                lin_frame_cfg_array[i].pbuffer[j] = lin_driver_response_buffer[j]; 
            }
            
            lin_frame_cfg_array[i].process_fun();
                 
            LIN_FRAME_RESET_TIMETICK(i);
            
            if(LIN_FRAME_CHECK(i))
            {
                LIN_FRAME_OVERIDE(i);
            }
            else
            {
                LIN_FRAME_SET_NEW(i);
            }
      			
//      			if(0x3C == frame_id)
//      			{
      			  
//      			}
      			
            break;
        }
    }


}

/****************************************************************************
 * Function: lin_update_tx
 * Param<void>:  
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
void lin_update_tx(l_u8 frame_id)
{
    
//    lin_successful_transfer = 1;
//    lin_error_in_response = 0;
      lin_word_status.bits.successful_transfer = 1;
//      lin_word_status.bits.error_in_response = 0;
//    lin_update_err_signal();
    
    if (0x3D == frame_id) 
    {
        if(1 == get_reset_request_flg())   
        {
            put_reset_request_flg(0);
            /* reset the ecu */
//            asm("JMP 0xFFFE"); 
            //sw_watchdog_init();           peter lei 20160906
//            SW_WATCHDOG_RESET_CPU();
        }
    
    }
    else if(lin_frame_cfg_id[LIN_FRAME_ST] == frame_id)
    {
    	  st_frame_sent_flg = 1;
    	  lin_word_status.bits.error_in_response = 0;
    }    
    else
    {
    }
    
}


/****************************************************************************
 * Function: lin_goto_low_power_mode
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
void lin_goto_low_power_mode(void)
{
  
    lin_goto_sleep_mode();
    
}









