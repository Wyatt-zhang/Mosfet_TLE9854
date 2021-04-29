/*******************************************************************************
* Copyright (c) 2015, JE
* All Rights Reserved.
* Dept.: APG Shared
* File: lin_diagnostic_support.c
* Description:
* REQ IDs: 
* History:
* 2015-09-07,  Lei Yingjun
*******************************************************************************/

#include "lin_diagnostic_support.h"
#include "lin_diagnostic_service.h"
#include "lin_tl_protocol.h"
#include "lin_config.h"



static l_bool uds_reset_request_flag = 0;


static uds_mode_t uds_session = UDS_SESSION_STD;
static l_u16 uds_session_remain_time  = UDS_SESSION_MAX_TIME;  	/* The remain time from ex-mode to std-mode */

static l_bool uds_request_reset = 0;
static l_u16 uds_reset_remain_time = 0;

static uds_secure_st_t uds_secure_status = UDS_LOCKED_ALL;
static l_u8 uds_faa_cnt = 0;
static l_u16 uds_faa_locked_remain_time = UDS_SECURITY_MAX_TIME; 	/* the rest time from UDS_UNSECURE to UDS_SECURE */


//#pragma DATA_SEG UDS_FLAG_DATA
volatile l_u8 uds_prog_request = UDS_NO_PROG_REQUEST; 	/* Store in UDS_PROG_REQ_FLAG_ADDR after shutdown */
volatile l_u8 uds_faa_flag = UDS_ACCESS_UNDELAY_FLAG; 	/* Store in UDS_FAA_FLAG_STORE_ADDR after shutdown */
volatile l_u8 uds_fail_seed_key_rcnt = 0xFF;  			/* Store in UDS_FAILED_SEED_KEY_RCNT_ADDR after shutdown */
//#pragma DATA_SEG DEFAULT




/********************************************************************************
 * Function: get_reset_request_flg
 * Param<U1 service>:
 * Param<U1 response_code>:
 * Return<void>:
 * REQ IDs:
 * Discription:
 * Note: 
********************************************************************************/
l_bool get_reset_request_flg(void)
{
    return(uds_reset_request_flag); 
}

void put_reset_request_flg(l_bool reset_flg)
{
    uds_reset_request_flag = reset_flg; 
}



/********************************************************************************
 * Function: uds_transmit_response_msg
 * Param<U1 service>:
 * Param<U1 response_code>:
 * Return<void>:
 * REQ IDs:
 * Discription:
 * Note: 
********************************************************************************/
void diag_transmit_response_msg(l_u16 data_length, l_u8 *data_buffer)
{
    lin_tx_response_msg(data_buffer, data_length);
}


/********************************************************************************
 * Function: diag_negative_response
 * Param<U1 service>:
 * Param<U1 response_code>:
 * Return<void>:
 * REQ IDs:
 * Discription:
 * Note: 
********************************************************************************/
void diag_negative_response(l_u8 service, l_u8 response_code)
{
    l_u8 array_u8_response[3];

    array_u8_response[0] = NEGATIVE_RESPONSE;
    array_u8_response[1] = service;
    array_u8_response[2] = response_code;
    UDS_RECEIVE_VALID_REQUEST();
    diag_transmit_response_msg(3u, array_u8_response);
}

/********************************************************************************
 * Function: diag_response_pending
 * Param<U1 service>:
 * Param<U1 response_code>:
 * Return<void>:
 * REQ IDs:
 * Discription:
 * Note: 
********************************************************************************/
void diag_response_pending(l_u8 service)
{
    l_u8 array_u8_response[3];

    array_u8_response[0] = NEGATIVE_RESPONSE;
    array_u8_response[1] = service;
    array_u8_response[2] = 0x78;
    UDS_RECEIVE_VALID_REQUEST();
    diag_transmit_response_msg(3u, array_u8_response);
}

/********************************************************************************
 * Function: lin_diag_no_response
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription:
 * Note: 
********************************************************************************/
void diag_no_response(void)
{
    UDS_RECEIVE_VALID_REQUEST();
    
    
}

/********************************************************************************
 * Function: uds_get_session
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription:
 * Note: 
********************************************************************************/
uds_mode_t uds_get_session(void)
{
    return uds_session;
}

/********************************************************************************
 * Function: uds_get_secure_status
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription:
 * Note: 
********************************************************************************/
uds_secure_st_t uds_get_secure_status(void)
{
    return uds_secure_status;
}

/********************************************************************************
 * Function: uds_lock_all_access
 * Param<void>:
 * Return<static void>: secure status
 * REQ IDs:
 * Discription:
 * Note:
**********************************************************************************/
void uds_lock_all_access(void)
{
//    prog_condition_ok = FALSE;
    uds_secure_status = UDS_LOCKED_ALL;
}

void uds_invalid_unlock(void)
{
    if (uds_faa_cnt < UDS_INVALID_ACCESS_MAX_TIMES)
    {
        uds_faa_cnt++;
    }
    
    if (uds_faa_cnt >= UDS_INVALID_ACCESS_MAX_TIMES)
    {
        uds_faa_flag = UDS_ACCESS_DELAY_FLAG;
        uds_faa_locked_remain_time = UDS_SECURITY_MAX_TIME; 
    }
}




/********************************************************************************
 * Function: uds_set_diagnostic_mode
 * Param<void>:
 * Return<static void>: l_u8
 * REQ IDs:
 * Discription:
 * Note:
*********************************************************************************/
l_u8 uds_set_diagnostic_mode(uds_mode_t uds_mode_type)
{
    l_u8 u8_rsp_code = RSP_NO_NEGATIVE_STATE;
    l_u16 uds_mode_modify = UDS_SESSION_GET_MODIFY_CODE(uds_session,uds_mode_type);

    switch (uds_mode_modify)
    {
        case UDS_SESSION_STD_TO_STD:
        case UDS_SESSION_STD_TO_EOL:
        case UDS_SESSION_EOL_TO_EOL:
        
        case UDS_SESSION_STD_TO_CODE:
        case UDS_SESSION_EOL_TO_CODE:
        case UDS_SESSION_CODE_TO_STD:
        case UDS_SESSION_CODE_TO_EOL:
        case UDS_SESSION_CODE_TO_CODE:
//            org_access_type = 0;
            uds_session = uds_mode_type;
            break;
            
        case UDS_SESSION_EOL_TO_STD:
//            org_access_type = 0;

            uds_session = uds_mode_type;
            break;
            
        case UDS_SESSION_STD_TO_PROG:
        case UDS_SESSION_EOL_TO_PROG:
            if(1)
            {
                uds_prog_request = UDS_PROG_REQUEST_PENDING;
//                EEPROM_Write = ineeprom_write(&uds_prog_request, UDS_PROG_REQUEST, 1);
                uds_reset_request_flag = 1;
            }
            else
            {
                u8_rsp_code = RSP_CONDITIONS_NOT_CORRECT;
            }
            break;

        case UDS_SESSION_PROG_TO_EOL:
        case UDS_SESSION_PROG_TO_STD:
        case UDS_SESSION_PROG_TO_PROG:
        default:
            u8_rsp_code = RSP_SUBFUNCTION_NOT_SUPPORTED;
            break;
    }
    
    return u8_rsp_code;
}

/***********************************************************************************
 * Function: uds_reset_task
 * Param<void>:
 * Return<static void>: 
 * REQ IDs:



 * Discription:
 * Note:
************************************************************************************/
static void uds_reset_task(void)
{
  if(1 == uds_request_reset)
  {
    if(uds_reset_remain_time > 0)
    {
      uds_reset_remain_time--;
      if(uds_reset_remain_time == 0)
      {
//        SW_WATCHDOG_RESET_CPU();
      }
    }
  }  
}

/***********************************************************************************
 * Function: uds_period_task
 * Param<void>:
 * Return<static void>: BOOL
 * REQ IDs:
 * Discription:
 * Note:
************************************************************************************/
void uds_period_task(void)
{

    /* lock/unlock state task */
    if (uds_faa_locked_remain_time > 0)
    {
        uds_faa_locked_remain_time--;
        if (0 == uds_faa_locked_remain_time)
        {
            uds_faa_cnt = 0;
            uds_faa_flag = UDS_ACCESS_UNDELAY_FLAG;
        }
    }

    /* session control task */
    if (UDS_SESSION_STD != uds_session)
    {
        if (0 == uds_session_remain_time)
        {
//            org_access_type = 0;
//            prog_condition_ok = FALSE;
            uds_session = UDS_SESSION_STD;
            uds_session_remain_time  = UDS_SESSION_MAX_TIME;
            uds_secure_status = UDS_LOCKED_ALL;
        }
        else
        {
            uds_session_remain_time--;
        }
    }

    /*if(1 == uds_request_reset)
    {
        if(uds_reset_remain_time > 0)
        {
            uds_reset_remain_time--;
            if(uds_reset_remain_time == 0)
            {
                SW_WATCHDOG_RESET_CPU();
            }
        }
    } */
    uds_reset_task(); 
}


/********************************************************************************
 * Function: uds_ecu_reset
 * Return<void>:
 * REQ IDs:
 * Discription:
 * Note: 
********************************************************************************/
void uds_ecu_reset(void)
{
    uds_request_reset = 1;
    uds_reset_remain_time = 10;	  
	  
}




