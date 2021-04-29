/*******************************************************************************
* Copyright (c) 2015, JE
* All Rights Reserved.
* Dept.: APG Shared
* File: lin_tl_protocol.c
* Description:
* REQ IDs: 
* History:
* 2015-08-07,  Lei Yingjun
*******************************************************************************/

#include "lin_tl_protocol.h"
#include "lin_config.h"
#include "lin_diagnostic_support.h"
#include "lin_diagnostic_service.h"


#define TL_DEFAULT_CF_ST  0         /* [1ms], ST = 0ms */
#define TL_TIMEOUT_CF_CF  1000      /* [1ms], Cr = 1000ms */


lin_tl_data_t lin_tl_data;


/****************************************************************************
 * Function: tl_memory_copy
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
void tl_data_init(void)
{
    lin_tl_data.mode = TL_MODE_IDLE;

    lin_tl_data.rx_queue_status = LD_NO_DATA;
    lin_tl_data.tx_queue_status = LD_NO_DATA;
    
    lin_tl_data.index = 0;
    lin_tl_data.length = 0;
    
    lin_tl_data.cf.st = TL_DEFAULT_CF_ST;
    lin_tl_data.cf.sn = 0;
    
    lin_tl_data.timeout.counter = 0;
    lin_tl_data.timeout.type = LD_NO_CHECK_TIMEOUT;    
}


/****************************************************************************
 * Function: tl_memory_copy
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
void tl_memory_copy(l_u8 * addr_to, const l_u8 * addr_from, l_u16 size)
{
    l_u32 i = 0;
    for (i = 0u; i < size; i++)
    {
        *addr_to++ = *addr_from++;
    }
}


/****************************************************************************
 * Function: lin_tl_error_handle
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
void lin_tl_error_handle(lin_tl_error_t tl_error_type)
{
    switch(tl_error_type)
    {
      case TL_ERROR_SF_UNEXPECTED:
      case TL_ERROR_FF_UNEXPECTED:
      case TL_ERROR_CF_UNEXPECTED:
      case TL_ERROR_WRONG_NT_FRAME:
      case TL_ERROR_WRONG_SN:
      case TL_ERROR_TIMEOUT:
         tl_data_init();
         break;
      case TL_ERROR_MESSAGE_TOO_BIG:
         /* ignore */
         break;
      case TL_ERROR_INTERNAL:
      case TL_ERROR_UNKNOWN_FRAME:
         break;
      default:
         break;      
      
    }
}


/****************************************************************************
 * Function: tl_timer_task
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
void tl_timer_task(void)
{
    if (LD_NO_CHECK_TIMEOUT != lin_tl_data.timeout.type)
    {
        lin_tl_data.timeout.counter -= 1;
        if(0 == lin_tl_data.timeout.counter)
        {
            /* update status of transport layer */
            lin_tl_error_handle(TL_ERROR_TIMEOUT);
        }
    }

    if(lin_tl_data.cf.st > 0)
    {
        lin_tl_data.cf.st--; 
    }

}


/****************************************************************************
 * Function: lin_tl_handler
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
void lin_tl_rx_handler(void)
{
    l_u8 NAD, sn;
    l_u8 frame_type;
    l_u16 data_length;

    NAD = TL_RX_BUFFER[0];
    frame_type = (l_u8)(TL_RX_BUFFER[1] & 0xF0);

    if ((LD_BROADCAST_NAD != NAD) && (LD_FUNCTIONAL_NAD != NAD) && (get_configured_nad() != NAD) && (get_initial_nad() != NAD)) 
    {
        /* ignore any response */
        lin_tl_error_handle(TL_ERROR_WRONG_NT_FRAME);          
    }
    else if((TL_MODE_IDLE != lin_tl_data.mode) && (LD_FUNCTIONAL_NAD == NAD))
    {
        lin_tl_data.timeout.counter = TL_TIMEOUT_CF_CF;
        lin_tl_data.timeout.type = LD_CHECK_N_CR_TIMEOUT;
    }
    else
    {
        switch(frame_type)
        {
            /*---------------------------------------------*/
            /*              SF - SINGLE FRAME              */
            /*---------------------------------------------*/        
            case PCI_SF:
                data_length = TL_RX_BUFFER[1] & 0x0F;
                if((0 == data_length) || (data_length > 6)) 
                {
                    /* ignore the message */ 
                }
                else
                {
                    tl_memory_copy(lin_tl_data.queue, &TL_RX_BUFFER[2], data_length);
                    lin_tl_data.length = data_length;
                    
                    lin_tl_data.mode = TL_MODE_IDLE;
                    lin_tl_data.timeout.type = LD_NO_CHECK_TIMEOUT;
                    /* notice diagnostic layer */
                    lin_diag_request_dispose(NAD);
                }
                break; 

            /*---------------------------------------------*/
            /*              FF - FIRST FRAME               */
            /*---------------------------------------------*/
            case PCI_FF:
                data_length = (l_u16)(TL_RX_BUFFER[1] & 0x0F) << 8;
                data_length += TL_RX_BUFFER[2];
                if((0 == data_length) || (data_length <= 6)) 
                {
                    /* ignore the message */ 
                }
                else
                {
                    if(data_length > MAX_QUEUE_SIZE)
                    {
                        /* ignore the message */
                    }
                    else
                    {
                      
                        lin_tl_data.length = data_length;
                        tl_memory_copy(lin_tl_data.queue, &TL_RX_BUFFER[3], NT_FF_DATA_LENGTH);
                        
                        lin_tl_data.index = NT_FF_DATA_LENGTH;
                        lin_tl_data.cf.sn = 1;
                        
                        lin_tl_data.mode = TL_MODE_WAIT_CF;
                        lin_tl_data.timeout.type = LD_CHECK_N_CR_TIMEOUT;
                        lin_tl_data.timeout.counter = TL_TIMEOUT_CF_CF;
                    }
                }            
                break;     
         
            /*---------------------------------------------*/
            /*           CF - CONSECUTIVE FRAME            */
            /*---------------------------------------------*/        
            case PCI_CF:
                if(TL_MODE_WAIT_CF != lin_tl_data.mode) 
                {
                    /* ignore the message */ 
                }
                else
                {
                     data_length = lin_tl_data.length - lin_tl_data.index;
                     if(data_length > NT_CF_DATA_LENGTH)
                     {
                          data_length = NT_CF_DATA_LENGTH;
                     }
                
                     sn = TL_RX_BUFFER[1] & 0x0F;
                     if(sn != lin_tl_data.cf.sn)
                     {
                        /* abort the message */
                        lin_tl_error_handle(TL_ERROR_WRONG_SN);
                     }
                     else
                     {
                          tl_memory_copy(&lin_tl_data.queue[lin_tl_data.index], &TL_RX_BUFFER[2], data_length);
                          lin_tl_data.index += data_length;
                          
                          if(lin_tl_data.index == lin_tl_data.length)
                          {
                              lin_tl_data.mode = TL_MODE_IDLE;
                              lin_tl_data.timeout.type = LD_NO_CHECK_TIMEOUT;
                              
                              /* notice diagnostic layer */ 
                              lin_diag_request_dispose(NAD); 
                          }
                          else
                          {
                              lin_tl_data.cf.sn++;
                              if(lin_tl_data.cf.sn > 15)
                              {
                                  lin_tl_data.cf.sn = 0;
                              }
                              
                              lin_tl_data.mode = TL_MODE_WAIT_CF;
                              lin_tl_data.timeout.type = LD_CHECK_N_CR_TIMEOUT;
                              lin_tl_data.timeout.counter = TL_TIMEOUT_CF_CF;
                          }
                     }
                }
                break;
                
            default:
                /* ignore this PDU */
                break;      
        }
    }
}

/****************************************************************************
 * Function: lin_tx_response_msg
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
void lin_tx_response_msg(const l_u8 * diag_data, l_u16 diag_data_length)
{
    if(diag_data_length > MAX_QUEUE_SIZE)
    {
      
    }
    else
    {
        if(TL_MODE_IDLE == lin_tl_data.mode)
        {
            tl_memory_copy(lin_tl_data.queue, diag_data, diag_data_length); 
            lin_tl_data.index = 0;
            lin_tl_data.length = diag_data_length;
            
            lin_tl_data.timeout.type = LD_CHECK_N_CR_TIMEOUT;        
            lin_tl_data.timeout.counter = TL_TIMEOUT_CF_CF;
            
            if(lin_tl_data.length > NT_SF_DATA_LENGTH)
            {
                lin_tl_data.mode = TL_MODE_SEND_FF;    
            }
            else
            {
                lin_tl_data.mode = TL_MODE_SEND_SF;    
            }        
        
        }
      
    }
    
}


/****************************************************************************
 * Function: lin_tl_tx_task
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
l_bool lin_tl_tx_task(void)
{
    l_u8 index;  
    l_u16 length;           
    l_bool action = CLEAR;
    
    if((TL_MODE_IDLE == lin_tl_data.mode) || (TL_MODE_WAIT_CF == lin_tl_data.mode))
    {
    }
    else
    {
        for(index = 0; index < 8; index++)
        {
            TL_TX_BUFFER[index] = 0xFF; 
        }        
        
        switch(lin_tl_data.mode)
        {
          /*---------------------------------------------*/
          /*              SF - SINGLE FRAME              */
          /*---------------------------------------------*/                
          case TL_MODE_SEND_SF:
              TL_TX_BUFFER[0] = get_response_nad();
              TL_TX_BUFFER[1] = (l_u8)(PCI_SF | lin_tl_data.length);
              tl_memory_copy(&TL_TX_BUFFER[2], lin_tl_data.queue, lin_tl_data.length);
              
              lin_tl_data.mode = TL_MODE_IDLE;
              lin_tl_data.timeout.type = LD_NO_CHECK_TIMEOUT;          
              
              action = SET;
              break;
              
          /*---------------------------------------------*/
          /*              FF - FIRST FRAME               */
          /*---------------------------------------------*/
          case TL_MODE_SEND_FF:
              lin_tl_data.index = 0;
              TL_TX_BUFFER[0] = get_configured_nad();
              TL_TX_BUFFER[1] = PCI_FF | (lin_tl_data.length >> 8u);
              TL_TX_BUFFER[2] = (l_u8)lin_tl_data.length;
              tl_memory_copy(&TL_TX_BUFFER[3], lin_tl_data.queue, NT_FF_DATA_LENGTH);
              
              lin_tl_data.index += NT_FF_DATA_LENGTH;
              lin_tl_data.cf.sn = 1;
              lin_tl_data.mode = TL_MODE_SEND_CF;
              lin_tl_data.timeout.type = LD_CHECK_N_CR_TIMEOUT;
              lin_tl_data.timeout.counter = TL_TIMEOUT_CF_CF;
              lin_tl_data.cf.st = TL_DEFAULT_CF_ST;
              
              action = SET;
              break;
              
          
          /*---------------------------------------------*/
          /*           CF - CONSECUTIVE FRAME            */
          /*---------------------------------------------*/        
          case TL_MODE_SEND_CF:
              if(0 == lin_tl_data.cf.st)
              {
                  length = lin_tl_data.length - lin_tl_data.index;
                  if(length > NT_CF_DATA_LENGTH)
                  {
                      length = NT_CF_DATA_LENGTH; 
                  }
                  
                  TL_TX_BUFFER[0] = get_configured_nad();
                  TL_TX_BUFFER[1] = PCI_CF | lin_tl_data.cf.sn;
                  tl_memory_copy(&TL_TX_BUFFER[2], &lin_tl_data.queue[lin_tl_data.index], length);
                  
                  lin_tl_data.cf.sn++;  
                  if(lin_tl_data.cf.sn > 15)
                  {
                      lin_tl_data.cf.sn = 0;
                  }
                                    
                  lin_tl_data.index += length;
                  if(lin_tl_data.index == lin_tl_data.length)
                  {
                      lin_tl_data.mode = TL_MODE_IDLE;  
                      lin_tl_data.timeout.type = LD_NO_CHECK_TIMEOUT;
                  }
                  else
                  {
                      lin_tl_data.mode = TL_MODE_SEND_CF;
                      lin_tl_data.timeout.type = LD_CHECK_N_CR_TIMEOUT;
                      lin_tl_data.timeout.counter = TL_TIMEOUT_CF_CF;
                      lin_tl_data.cf.st = TL_DEFAULT_CF_ST;
                  }
                  
                  action = SET;
              }
              break;
                
          /*---------------------------------------------*/
          /*                  Undefined                  */
          /*---------------------------------------------*/        
          default:
              break;
        }
      
    }
    
    return action;
}



/****************************************************************************
 * Function: tl_get_rx_length
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
l_u16 tl_get_rx_length(void)
{
    return (lin_tl_data.length);
}


/****************************************************************************
 * Function: tl_get_rx_data
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
l_u8 tl_get_rx_data(l_u16 index)
{
    return (lin_tl_data.queue[index]);
}











