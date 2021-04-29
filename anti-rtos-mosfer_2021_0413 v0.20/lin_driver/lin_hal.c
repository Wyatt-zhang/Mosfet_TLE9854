/*******************************************************************************
* Copyright (c) 2015, JE
* All Rights Reserved.
* Dept.: APG Shared
* File: lin_sci.c
* Description:
* REQ IDs: 
* History:
* 2020-03-12,  Lei Yingjun
*******************************************************************************/


#include "lin_config.h"
#include "lin_hal.h"
#include "lin_tl_protocol.h"

#include <tle_device.h>
  


static lin_driver_seq_t lin_driver_state = LIN_UNINIT; 

static l_u8     current_frame_id;

static l_u8     current_pid;

static l_u8     current_frame_length;

static l_u8     response_data_index = 0;

static l_u16    frame_timeout_cnt = 0;

static l_u16    res_frame_timeout_cnt = 0;

static l_u16    idle_state_timeout_cnt = 0; 


static l_u8     tx_wake_up_counter = 0;
static l_u8     tx_wake_up_interval_time = 0;


#ifdef AUTOBAUD_ENABLED
static volatile l_u8 lin_ab_t2_state;
static l_u8 lin_ab_timeout_timer;
static volatile l_u16 lin_synch_time;
#endif /* end #ifdef AUTOBAUD_ENABLED */

/****************************************************************************
 * Function: lin_sci_init
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
void lin_sci_init(void)
{
   /* Reset UART to initial values */
   LIN_UART_CONTROL =      0x00u;

   /* Set UART to 8bit shift UART */
   LIN_UART_MODE0 =        0u;
   LIN_UART_MODE1 =        1u;

   /* Set Baudrate Generator and enable */
   LIN_UART_BCON_RUN =     0u; /*lint !e923*/   //add by peibinbin 20190521
   LIN_UART_BCON_PRE =     BRG_PRE;
   LIN_UART_BCON_FDSEL =   BRG_FD_SEL;
   LIN_UART_BCON_BG =      BRG_VAL;
   LIN_UART_BCON_RUN =     1u;

   /* Set Limits for Baudrate detection */
#ifdef AUTOBAUD_ENABLED
   LIN_UART_STATUS =       0x01u;		/* Break/Synch detection is disable */
   LIN_UART_CLR_STATUS =   LINST_MASK_SYNBRK;
#else
   LIN_UART_STATUS =       0x01u;		/* Break/Synch detection is disable */
   LIN_UART_CLR_STATUS =   LINST_MASK_SYNBRK;
#endif /* end #ifndef AUTOBAUD_ENABLED */

   LIN_UART_BR_SYN_DET =   BG_SEL;
	 
#ifdef AUTOBAUD_ENABLED
//   LIN_UART_BR_DIS = 1u;
//   LIN_UART_BR_DIS = 0u;
   LIN_UART_CLR_STATUS =   LINST_MASK_SYNBRK;
#endif /* end #ifndef AUTOBAUD_ENABLED */

   /* Enable UART reception */
   LIN_UART_RUN =          1u;

   /* UART interrupt enable */
   LIN_UART_IR_SET_EN =    1u;
   LIN_UART_IR_RIEN =      1u;
   LIN_UART_IR_TIEN =      0u;
   LIN_UART_IR_PENDING =   1u;
   #ifdef TLE985x
  	 NVIC_SetPriority((IRQn_Type)LIN_UART_IRQ_NR ,LIN_INTERRUPT_PRIORITY);
   #elif defined TLE984x
     LIN_UART_IR_PRIO =      (l_u8) ((LIN_INTERRUPT_PRIORITY & 0x0Fu) << 4u); /*lint !e923*/
   #endif //end of TLE985x
	 
	 
#ifdef AUTOBAUD_ENABLED
   #ifdef TLE985x
			/* Select input EXINT0_2 for external interrupt 0. */
			LIN_TIMER_MODPISEL = 2u;
			/* Timer 2 external input is selected by MODPISEL2. */
			LIN_TIMER_MODPISEL1 = 0u;
			/* Timer2 external input is T2Ex_x (T2EXISCNF) */
			LIN_TIMER_MODPISEL2 = 0x0200u;			
   #elif defined TLE984x	 
			LIN_TIMER_EXCON = 0u; /*lint !e923*/
			LIN_TIMER_EXIS = 1u; /*lint !e923*/
	 #endif//end of TLE985x
	 
   LIN_TIMER_PRE =         1u;  /* T2CLK = PCLK (20MHz) */
   LIN_TIMER_PRE_EN =      1u;  /* Timer2 Prescaler is used (T2PRE) */
   LIN_TIMER_COUNTER_EN =  0u;  /* UpDown Counter function disabled */
   LIN_TIMER_EDGE_SELECT = 0u;  /* Timer2 starts on external falling edge */
   LIN_TIMER_EXT_START =   1u;  /* Timer2 starts on external event */

   LIN_TIMER_CAP_REL =     1u;  /* Capture Mode */
   LIN_TIMER_T_C_SEL =     0u;  /* Timer function */
   LIN_TIMER_EXT_EN =      0u;  /* External Events disabled */

   /* set Timer2 interrupts */
   LIN_TIMER_EXT_IR_EN =   0u;  /* Interrupt for external events disabled */
   LIN_TIMER_INT_IR_EN =   0u;  /* Interrupt for Timer2 overflow disabled */

   /* Timer2 is needed for baudrate synchronization */
   LIN_UART_IR_SET_EN =    1u;
#endif /* end #ifdef AUTOBAUD_ENABLED */
    
    
    /* Enter IDLE state */
    lin_goto_idle_state();
}



/****************************************************************************
 * Function: lin_sci_deinit
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
void lin_sci_deinit(void)
{   
		/* Reset UART to initial values */
		LIN_UART_CONTROL =      0x00u;
    
		LIN_UART_BCON_RUN =     0u;
    
    lin_driver_state = LIN_UNINIT;
	
#ifdef AUTOBAUD_ENABLED	
	  LIN_TIMER_RUN = 0u;				/* stop timer */
    LIN_TIMER_EXT_IR_EN = 0u;	/* Interrupt for external events disabled */
    LIN_TIMER_EXT_EN = 0u;		/* External Events disabled */
#endif /* end #ifdef AUTOBAUD_ENABLED */	
	
}


#ifdef AUTOBAUD_ENABLED
/****************************************************************************
 * Function: lin_hal_init_T2
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
static void lin_hal_init_T2 (void)
{
   LIN_UART_BCON_RUN = 0u;          /* stop baudrate generator */
   LIN_TIMER_RUN = 0u;              /* stop timer for reinit */

   LIN_TIMER_HIGH = 0u;             /* reset the count value to '0' */
   LIN_TIMER_LOW = 0u;

   LIN_TIMER_EXT_EN = 1u;           /* External Events enabled */
   LIN_TIMER_EXT_IR_EN = 1u;        /* Interrupt for external events enabled */
   LIN_UART_CLR_STATUS = LINST_MASK_SYNBRK;
   lin_ab_timeout_timer = 0u;
}

/****************************************************************************
 * Function: lin_hal_brreg_calc
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
static void lin_hal_brreg_calc(void)
{
   lin_synch_time = (l_u16)(((l_u16)(lin_synch_time >> 2u)) >> BRG_PRE);
   /* (MISRA-C:2004 MISRA Rule 13.7/R, 14.1/R, e506) Constant value Boolean
    * Outcome depends on generated code. */
   LIN_UART_BCON_FDSEL = (l_u8) (((l_u8)(lin_synch_time & 0x1Fu)) >> ((BRG_PRE == 0u)?1u:0u)); /*lint !e506*/
   lin_synch_time = (l_u16) (lin_synch_time >> 5u);
   if (lin_synch_time >= MIN_BDREG)
   {
      if (lin_synch_time <= MAX_BDREG)
      {
        LIN_UART_BCON_BG = (uint32_t)((uint32_t)lin_synch_time & 0x7FFu);
//				LIN_UART_BCON_BGL = (l_u8)(lin_synch_time & 0x07);
//				LIN_UART_BCON_BGH = (l_u8)(lin_synch_time >> 3);        
				lin_driver_state = LIN_RECEIVE_PID;
				
				if(lin_synch_time >= 125 && lin_synch_time <= 135)	/* 19.2kbps */
				{
						lin_frame_timeout_val[0] = lin_frame_timeout_val_19200[0];
						lin_frame_timeout_val[1] = lin_frame_timeout_val_19200[1];
						lin_frame_timeout_val[2] = lin_frame_timeout_val_19200[2];
						lin_frame_timeout_val[3] = lin_frame_timeout_val_19200[3];
						lin_frame_timeout_val[4] = lin_frame_timeout_val_19200[4];
						lin_frame_timeout_val[5] = lin_frame_timeout_val_19200[5];
						lin_frame_timeout_val[6] = lin_frame_timeout_val_19200[6];
						lin_frame_timeout_val[7] = lin_frame_timeout_val_19200[7];
														
				}
				else if(lin_synch_time >= 230 && lin_synch_time <= 277)	/* 9.6kbps, 10.4kbps */
				{
						lin_frame_timeout_val[0] = lin_frame_timeout_val_9600[0];
						lin_frame_timeout_val[1] = lin_frame_timeout_val_9600[1];
						lin_frame_timeout_val[2] = lin_frame_timeout_val_9600[2];
						lin_frame_timeout_val[3] = lin_frame_timeout_val_9600[3];
						lin_frame_timeout_val[4] = lin_frame_timeout_val_9600[4];
						lin_frame_timeout_val[5] = lin_frame_timeout_val_9600[5];
						lin_frame_timeout_val[6] = lin_frame_timeout_val_9600[6];
						lin_frame_timeout_val[7] = lin_frame_timeout_val_9600[7];					
				}
				else if(lin_synch_time >= 480 && lin_synch_time <= 625)	/* 4.8kbps */
				{
						lin_frame_timeout_val[0] = lin_frame_timeout_val_4800[0];
						lin_frame_timeout_val[1] = lin_frame_timeout_val_4800[1];
						lin_frame_timeout_val[2] = lin_frame_timeout_val_4800[2];
						lin_frame_timeout_val[3] = lin_frame_timeout_val_4800[3];
						lin_frame_timeout_val[4] = lin_frame_timeout_val_4800[4];
						lin_frame_timeout_val[5] = lin_frame_timeout_val_4800[5];
						lin_frame_timeout_val[6] = lin_frame_timeout_val_4800[6];
						lin_frame_timeout_val[7] = lin_frame_timeout_val_4800[7];						
				}	
				else
				{
				}
				
      }
      else
      {
         lin_ab_timeout_timer = LIN_AUTOBAUD_TIMEOUT + 1u;
         lin_ab_t2_state = 7u;
      }
   }
   else
   {
      lin_ab_timeout_timer = LIN_AUTOBAUD_TIMEOUT + 1u;
      lin_ab_t2_state = 7u;
   }
   LIN_UART_BCON_RUN = 1u;
}

/****************************************************************************
 * Function: lin_hal_T2_ISR
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
void lin_hal_T2_ISR(void)
{
   if (lin_ab_t2_state == 5u)
   {
      LIN_TIMER_RUN = 0u;
      LIN_TIMER_EXT_IR_EN = 0u;
      LIN_TIMER_EXT_EN = 0u;
      lin_ab_t2_state = 0u;
      lin_synch_time = (l_u16) ((l_u16)((l_u16)LIN_TIMER_CAP_H << 8u) | ((l_u16)LIN_TIMER_CAP_L));
      lin_hal_brreg_calc();
   }
   else
   {
      lin_ab_t2_state++;
   }
}

/****************************************************************************
 * Function: l_autobaud_control
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
void l_autobaud_control(void)
{
   if(lin_ab_t2_state != 0u)
   {
      lin_ab_timeout_timer++;
      if(lin_ab_timeout_timer >= LIN_AUTOBAUD_TIMEOUT)
      {
         lin_driver_state = LIN_IDLE;
         lin_sci_init();
				
         lin_ab_t2_state = 0u;
         lin_ab_timeout_timer = 0u;
      }
   }
}
/****************************************************************************
 * Function: l_hal_baudrate_control
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
void l_hal_baudrate_control(void)
{
   l_u16 lin_temp_word;
   if (lin_driver_state == LIN_IDLE)
   {
      lin_temp_word = (l_u16) LIN_UART_BCON_BG;
      if (lin_temp_word > MAX_BDREG)
      {
         LIN_UART_BCON_FDSEL = BRG_FD_SEL;
         LIN_UART_BCON_BG = BRG_VAL;
      }
      if (lin_temp_word < MIN_BDREG)
      {
         LIN_UART_BCON_FDSEL = BRG_FD_SEL;
         LIN_UART_BCON_BG = BRG_VAL;
      }
   }
}

#endif /* end ifdef AUTOBAUD_ENABLED */


/****************************************************************************
 * Function: lin_sci_tx_wake_up
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
void lin_sci_tx_wake_up(void)
{   
    if((lin_driver_state == LIN_IDLE) || (lin_driver_state == LIN_SLEEP_MODE)) 
    {       
        /* Send wake signal byte = 0x80 */
        LIN_UART_BUFFER = 0x80;

        tx_wake_up_counter = 2;
        tx_wake_up_interval_time = 200;
                
        /* Set Lin state to idle */
        lin_goto_idle_state();
    }
}

/****************************************************************************
 * Function: lin_goto_idle_state
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
void lin_goto_idle_state(void)
{
  
    idle_state_timeout_cnt = IDLE_STATE_TIMEOUT_VALUE;
    
    lin_driver_state = LIN_IDLE;
    
}

/****************************************************************************
 * Function: lin_goto_sleep_state
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
void lin_goto_sleep_mode(void)
{
  
    lin_driver_state = LIN_SLEEP_MODE;
    
}


/****************************************************************************
 * Function: lin_sci_rx_response
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
void lin_sci_rx_response(l_u8  msg_length)
{
    response_data_index = 0;
    
    current_frame_length = msg_length;
    
    lin_driver_state = LIN_RECEIVE_DATA;  /* Set LIN Status */ 
  
}

/****************************************************************************
 * Function: lin_sci_tx_response
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
void lin_sci_tx_response(l_u8  msg_length)
{
    response_data_index = 0;
    
    current_frame_length = msg_length;
    
    LIN_UART_BUFFER = lin_driver_response_buffer[0]; /* Send First byte */
    
    lin_driver_state = LIN_SEND_DATA;  /* Set LIN Status */
}


/****************************************************************************
 * Function: lin_sci_timeout
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
void lin_sci_timeout(void)
{
    
#if (TL_FRAME_SUPPORT == TL_MULTI_FRAME)

    tl_timer_task();
    
#endif
    
   
    switch(lin_driver_state) 
    {
        case LIN_IDLE:
          if(tx_wake_up_interval_time > 0) 
          {
              tx_wake_up_interval_time--;
              if(0 == tx_wake_up_interval_time)
              {
                  if(tx_wake_up_counter > 0)
                  {
                      /* Send wake signal byte = 0x80 */
                      LIN_UART_BUFFER = 0x80;
                      
                      tx_wake_up_counter--;                      
                      tx_wake_up_interval_time = 200;
                  }            
              }
          }           
          
          
          if(idle_state_timeout_cnt == 0) 
          {
              /* Set LIN mode to sleep mode */
              lin_mute_flg = 1;

              lin_handle_error(LIN_BUS_ACTIVITY_TIMEOUT, 0xFF);
              
              idle_state_timeout_cnt = IDLE_STATE_TIMEOUT_VALUE;    /* reset max idle timeout */
              /* Set state to sleep mode */
              lin_driver_state = LIN_SLEEP_MODE;
          } 
          else 
          {
              idle_state_timeout_cnt--;
          }
          break;
          
        case LIN_SEND_PID:    /* Master */
        case LIN_RECEIVE_SYN:
        case LIN_RECEIVE_PID:
        case LIN_SEND_DATA:
        case LIN_SEND_DATA_COMPLETED:
          /* timeout send has occurred - change state of the node and inform core */
          if(0 == frame_timeout_cnt)
          {
              lin_goto_idle_state();
          }
          else 
          {
              frame_timeout_cnt--;
          }
          break;
          
        case LIN_RECEIVE_DATA:
          /* timeout receive has occurred - change state of the node and inform core */
          if(res_frame_timeout_cnt == 0) 
          {
              if(response_data_index > 0)
              {
                  /* set lin status: error_in_response */
//                  l_status.byte |= LIN_STA_ERROR_RESP;

                  lin_handle_error(LIN_NODATA_TIMEOUT, current_frame_id);
              }
              lin_goto_idle_state();
          } 
          else 
          {
              res_frame_timeout_cnt--;
          }
          break;
          
        default:
          break; 
    }
		
#ifdef AUTOBAUD_ENABLED   
    l_autobaud_control();
		l_hal_baudrate_control();
#endif		
}


/****************************************************************************
 * Function: lin_sci_rx_data
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
void lin_sci_rx_data(l_u8 data)
{
    l_u8 tmp_byte;
    
    tmp_byte = data;
    
    switch(lin_driver_state)
    {
        case LIN_RECEIVE_SYN:      /******************* Receiving SYN byte ******************/
            if (0x55 == tmp_byte)
            {
                lin_driver_state = LIN_RECEIVE_PID;
            }
            else
            {
                lin_goto_idle_state();
            }
            break; 
      
        case LIN_RECEIVE_PID:     /************************ Receiving PID **************************/
            current_frame_id = lin_process_parity(tmp_byte, CHECK_PARITY);
            current_pid = tmp_byte;
            if(current_frame_id != 0xFF)
            {
                lin_process_id(current_frame_id, current_pid);
                
                /* Set Maximum response frame timeout */
                res_frame_timeout_cnt = lin_frame_timeout_val[current_frame_length - 1]; 
            }
            else
            {
                lin_handle_error(LIN_PID_ERR, current_frame_id);
                
                lin_goto_idle_state();
            }
            
        
            break;
      
        case LIN_RECEIVE_DATA:    /************************ Receiving DATA **************************/
            lin_driver_response_buffer[response_data_index++] = tmp_byte;
            
            if(response_data_index == current_frame_length + 1)   /* Check bytes received fully */
            {
                if(lin_checksum(lin_driver_response_buffer, current_frame_length, current_pid) == tmp_byte)  /*** Checksum OK ***/
                {
                    LIN_UART_IR_RIEN = 0;    /* disable RX interrupt */
                    
                    lin_update_rx(current_frame_id);
                
                    LIN_UART_IR_RIEN = 1;    /* enable RX interrupt */                  
                    
                    
                    lin_goto_idle_state();
                }
                else      /*** Checksum ERROR ***/
                {
                    lin_handle_error(LIN_CHECKSUM_ERR, current_frame_id);
                    
                    lin_goto_idle_state();
                }
            }
            else
            {
            }
            break;
            
        case LIN_SEND_DATA:       /*********************** Sending DATA ************************/

						if (tmp_byte != lin_driver_response_buffer[response_data_index])
						{
								lin_handle_error(LIN_READBACK_ERR, current_frame_id);
								lin_goto_idle_state();
								break;
						}

        
            if(response_data_index < current_frame_length)
            {
                response_data_index++;
                LIN_UART_BUFFER = lin_driver_response_buffer[response_data_index]; 
            }
            else
            {
                
                LIN_UART_IR_RIEN = 0;    /* disable RX interrupt */
              
                lin_update_tx(current_frame_id);
            
                LIN_UART_IR_RIEN = 1;    /* enable RX interrupt */
                			
                lin_goto_idle_state();                      
            }
        
            break;
            
        case LIN_SLEEP_MODE:  /*********************** Waking up ************************/
            if ((tmp_byte == 0xF0) || (tmp_byte == 0xE0) || (tmp_byte == 0xC0) || (tmp_byte == 0x80) || (tmp_byte == 0x00)) 
            {
                lin_goto_idle_state();    /* Set idle timeout again */
                lin_mute_flg = 0;
            }
            break;        
        
        default:
            break;
    }
  
}


/****************************************************************************
 * Function: lin_sci_rx_isr
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
void lin_sci_rx_isr(void)
{
    l_u8 temp_linst;
    l_u8 tmp_byte;
		l_u8 sci_stopbit;

		tmp_byte = (l_u8) LIN_UART_BUFFER;
		sci_stopbit = (l_u8) LIN_UART_9BITREC;
	
		temp_linst = (l_u8) LIN_UART_STATUS;
		LIN_UART_CLR_STATUS = LINST_MASK_SYNBRK;
  
    /*******************************/
    /***    BREAK DETECTED      ****/
    /*******************************/
   if (((temp_linst & 0x38u) == 0u) && (tmp_byte == 0u) && (sci_stopbit == 0u)
		 && ((LIN_IDLE == lin_driver_state)||(LIN_SLEEP_MODE == lin_driver_state)) )
   {
#ifdef AUTOBAUD_ENABLED
				lin_ab_t2_state = 1u;
				lin_ab_timeout_timer = 0u;     
				lin_hal_init_T2();
#endif /* end #ifdef AUTOBAUD_ENABLED */	
	
//		 lin_have_received_flg = 1;
		 
		    /* check state of node is SLEEP_MODE */
        if(LIN_SLEEP_MODE == lin_driver_state)
        {
//            lin_goto_idle_state();
            lin_mute_flg = 0;
            
            lin_word_status.bits.bus_activity = 1;
            
            /* Set max frame timeout */
            frame_timeout_cnt = lin_frame_timeout_val[7];

            lin_driver_state = LIN_RECEIVE_SYN;
        }
        else
        {
            /* reset lin status */
            lin_word_status.bits.bus_activity = 1;
          
            /* Set max frame timeout */
            frame_timeout_cnt = lin_frame_timeout_val[7];

            lin_driver_state = LIN_RECEIVE_SYN;
        }
        
        tx_wake_up_counter = 0;
        tx_wake_up_interval_time = 0;
   }	
	

    /*******************************/
    /***  FRAME ERROR DETECTED   ***/
    /*******************************/
    else if((0 == sci_stopbit) && (LIN_IDLE != lin_driver_state)) 
    {
        
        /* set lin status: error_in_response, framing_error */
//        l_status.byte |= (LIN_STA_ERROR_RESP|LIN_STA_FRAME_ERR);
        
        if((lin_driver_state == LIN_RECEIVE_DATA) || (lin_driver_state == LIN_SEND_DATA) || (lin_driver_state == LIN_SEND_DATA_COMPLETED)) 
        {
            lin_handle_error(LIN_FRAME_ERR, current_frame_id);
      	}
      	
        lin_goto_idle_state();
    }    
    /*******************************/
    /***    BYTE RECIEVED        ***/
    /*******************************/    
    else if(0 != sci_stopbit)
    {
        /******** Byte Received ********/
        lin_sci_rx_data(tmp_byte);
//        lin_have_received_flg = 1; 
    }
    else
    {
      
    }
    
}

