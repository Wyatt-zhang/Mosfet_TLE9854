/*******************************************************************************
* Copyright (c) 2015, JE
* All Rights Reserved.
* Dept.: APG Shared
* File: lin_diagnostic_service.c
* Description:
* REQ IDs: 
* History:
* 2015-09-07,  Lei Yingjun
*******************************************************************************/

#include "lin_diagnostic_service.h"
#include "lin_diagnostic_support.h"
#include "lin_config.h"
#include "lin_tl_protocol.h"
#include "lin_il.h"


const l_u8 part_number_geely[8] = {0x08, 0x88, 0x89, 0x42, 0x62, ' ', ' ', 'A'};
const l_u8 part_number_volvo[7] = {0x32, 0x22, 0x27, 0x37,  ' ', ' ', ' '};


/****************************************************************/
static l_u8 diag_request_nad = 0;
static l_u8 diag_response_nad = 0;

static l_u16 uds_rx_length = 0u;
static l_u8 current_service_id = 0xFF;

static void lin_diag_B0_service(void);
static void lin_diag_B1_service(void);
static void lin_diag_B2_service(void);
static void lin_diag_B3_service(void);
static void lin_diag_B4_service(void);
static void lin_diag_B5_service(void);
static void lin_diag_B6_service(void);
static void lin_diag_B7_service(void);

static void lin_diag_10_service(void);
static void lin_diag_22_service(void);
static void lin_diag_2E_service(void);
static void lin_diag_3E_service(void);


/********************************************************************************
 * Function: get_response_nad
 * Param<void>:
 * Return<>:
 * REQ IDs:
 * Discription:
 * Note:
*********************************************************************************/
l_u8 get_response_nad(void)
{
    return(diag_response_nad); 
}


/********************************************************************************
 * Function: lin_configration_identification_service
 * Param<void>:
 * Return<static void>:
 * REQ IDs:
 * Discription:
 * Note:
*********************************************************************************/
void lin_configration_identification_service(l_u8 service_id)
{

    if((LD_BROADCAST_NAD == diag_request_nad) || (LD_FUNCTIONAL_NAD == diag_request_nad) || (get_configured_nad() == diag_request_nad))
    {
          
        switch(service_id)
        {
            case DIAG_B0: 
              lin_diag_B0_service();
              break;
          
            case DIAG_B1: 
              lin_diag_B1_service();
              break;      
            
            case DIAG_B2: 
              lin_diag_B2_service();
              break;        
            
            case DIAG_B3: 
              lin_diag_B3_service();
              break;        
           
            case DIAG_B4: 
              lin_diag_B4_service();
              break;        
            
            case DIAG_B5: 
              lin_diag_B5_service();
              break;        
            
            case DIAG_B6: 
              lin_diag_B6_service();
              break;        
          
            case DIAG_B7: 
              lin_diag_B7_service();
              break;        

            default:
              diag_negative_response(current_service_id, RSP_SERVICE_NOT_SUPPORT);
              break;    
        }
    }
    else if((get_initial_nad() == diag_request_nad))
    {
        if(DIAG_B0 == service_id)
        {
            lin_diag_B0_service(); 
        }
        else
        {
        }
    }    
    else
    {
    }    
    
}

/********************************************************************************
 * Function: lin_diag_request_dispose
 * Param<void>:
 * Return<static void>:
 * REQ IDs:
 * Discription:
 * Note:
*********************************************************************************/
void lin_diag_request_dispose(l_u8 request_nad)
{
    
    current_service_id = tl_get_rx_data(0); 
    uds_rx_length = tl_get_rx_length();
    
    diag_request_nad = request_nad;
    diag_response_nad = get_configured_nad();

    if(current_service_id >= DIAG_B0 && current_service_id <= DIAG_B7)
    {
        lin_configration_identification_service(current_service_id);  
    }
    else
    {
        if((LD_BROADCAST_NAD == request_nad) || (LD_FUNCTIONAL_NAD == request_nad) || (get_configured_nad() == request_nad))
        {
            switch(current_service_id)
            {
                case DIAG_10: 
                  lin_diag_10_service();
                  break;        
                       
                case DIAG_22: 
                  lin_diag_22_service();
                  break;        
                
                case DIAG_2E: 
                  lin_diag_2E_service();
                  break;        
                       
                case DIAG_3E: 
                  lin_diag_3E_service();
                  break;
                
                default:
                  if ((LD_FUNCTIONAL_NAD == diag_request_nad) || (LD_BROADCAST_NAD == diag_request_nad))
                  {
                      diag_no_response();
                  }
                  else
                  {
                      diag_negative_response(current_service_id, RSP_SERVICE_NOT_SUPPORT);
                  }
                  break;
            }
        }
        else
        {
            diag_no_response();
        }
    }

}


/********************************************************************************
 * Function: lin_diag_B0_service
 * Param<void>:
 * Return<static void>:
 * REQ IDs:
 * Discription: assign NAD service
 * Note:
*********************************************************************************/
static void lin_diag_B0_service(void)
{
    l_u16 temp_supplier_id, temp_function_id;
    l_u8 new_NAD;
    l_u8 positive_rsp_buffer[2] = {0};

    temp_supplier_id = tl_get_rx_data(1) + ((l_u16)tl_get_rx_data(2) << 8);
    temp_function_id = tl_get_rx_data(3) + ((l_u16)tl_get_rx_data(4) << 8);
    new_NAD = tl_get_rx_data(5);
    
    if((get_initial_nad() == diag_request_nad) && (temp_supplier_id == product_id.supplier_id) && (temp_function_id == product_id.function_id))
    {
        set_configured_nad(new_NAD);
        
        diag_response_nad = get_initial_nad();
        positive_rsp_buffer[0] = UDS_GET_POSITIVE_RESPONSE(DIAG_B0);
        diag_transmit_response_msg(1u, positive_rsp_buffer);
    }
    else
    {
        diag_no_response(); 
    }
    
}

/********************************************************************************
 * Function: lin_diag_B1_service
 * Param<void>:
 * Return<static void>:
 * REQ IDs:
 * Discription: assign frame id service
 * Note:  (LIN2.0)
*********************************************************************************/
static void lin_diag_B1_service(void)
{
#if 1
    
    diag_negative_response(current_service_id, RSP_SERVICE_NOT_SUPPORT);

#else

    l_u16 temp_supplier_id, temp_function_id;
    l_u8 new_pid;
    l_u8 positive_rsp_buffer[2] = {0};

    temp_supplier_id = tl_get_rx_data(1) + ((l_u16)tl_get_rx_data(2) << 8);
    temp_function_id = tl_get_rx_data(3) + ((l_u16)tl_get_rx_data(4) << 8);
    new_pid = tl_get_rx_data(5);
    
    if((temp_supplier_id == product_id.supplier_id) && (temp_function_id == product_id.function_id))
    {
     /* need to add something */
//        lin_configured_NAD = new_pid;
        
        positive_rsp_buffer[0] = UDS_GET_POSITIVE_RESPONSE(DIAG_B1);
        diag_transmit_response_msg(1u, positive_rsp_buffer);
    }
    else
    {
        diag_no_response(); 
    }

#endif
}

/********************************************************************************
 * Function: lin_diag_B2_service
 * Param<void>:
 * Return<static void>:
 * REQ IDs:
 * Discription: read by identify service  
 * Note: (mandatory)
*********************************************************************************/
static void lin_diag_B2_service(void)
{
    l_u16 temp_supplier_id, temp_function_id;
    l_u8 temp_id;
    l_u8 positive_rsp_buffer[6] = {0};

    temp_id = tl_get_rx_data(1);
    temp_supplier_id = tl_get_rx_data(2) + ((l_u16)tl_get_rx_data(3) << 8);
    temp_function_id = tl_get_rx_data(4) + ((l_u16)tl_get_rx_data(5) << 8);
    
    if(((temp_supplier_id == product_id.supplier_id) || (temp_supplier_id == LD_ANY_SUPPLIER))
    && ((temp_function_id == product_id.function_id) || (temp_function_id == LD_ANY_FUNCTION)))
    {
        switch(temp_id)
        {
          case 0:  /* LIN Product Identification */
              positive_rsp_buffer[0] = UDS_GET_POSITIVE_RESPONSE(DIAG_B2);
              positive_rsp_buffer[1] = (l_u8)product_id.supplier_id;
              positive_rsp_buffer[2] = (l_u8)(product_id.supplier_id >> 8);
              positive_rsp_buffer[3] = (l_u8)product_id.function_id;
              positive_rsp_buffer[4] = (l_u8)(product_id.function_id >> 8);
              positive_rsp_buffer[5] = product_id.variant;
              diag_transmit_response_msg(6u, positive_rsp_buffer);
              break;
          

          default:
//              diag_negative_response(current_service_id, RSP_REQUEST_OUT_OF_RANGE);
              diag_negative_response(current_service_id, 0x12);		/* LIN2.1 Conformance Test */			
              break;
        }
    }
    else
    {
        diag_no_response();          //peter lei 20170919
//        diag_negative_response(current_service_id, RSP_REQUEST_OUT_OF_RANGE); 
    }

}

/********************************************************************************
 * Function: lin_diag_B3_service
 * Param<void>:
 * Return<static void>:
 * REQ IDs:
 * Discription: conditional change NAD service
 * Note:
*********************************************************************************/
static void lin_diag_B3_service(void)
{
#if 1
    
    diag_negative_response(current_service_id, RSP_SERVICE_NOT_SUPPORT);

#else

    l_u8 temp_id, temp_byte, temp_mask, temp_invert, new_nad;
    l_u8 positive_rsp_buffer[2] = {0};

    temp_id = tl_get_rx_data(1);
    temp_byte = tl_get_rx_data(2);
    temp_mask = tl_get_rx_data(3);
    temp_invert = tl_get_rx_data(4);
    new_nad = tl_get_rx_data(5);
    
    if(0 == temp_id)
    {
     /* need to add something */
        if(1 == temp_byte)
        {
            temp_byte = (l_u8)product_id.supplier_id;
        }
        else if(2 == temp_byte)
        {
            temp_byte = (l_u8)(product_id.supplier_id >> 8);
        }
        else if(3 == temp_byte)
        {
            temp_byte = (l_u8)product_id.function_id;
        }
        else if(4 == temp_byte)
        {
            temp_byte = (l_u8)(product_id.function_id >> 8);
        }
        else if(5 == temp_byte)
        {
            temp_byte = product_id.variant;
        }
        else
        {
        }
        
        if(0 == (temp_byte ^ temp_invert & temp_mask))
        {
          set_configured_nad(new_NAD);
        
          positive_rsp_buffer[0] = UDS_GET_POSITIVE_RESPONSE(DIAG_B3);
          diag_transmit_response_msg(1u, positive_rsp_buffer);
        }
        else
        {
            diag_no_response(); 
        }
    }
    else
    {
        diag_no_response(); 
    }

#endif
}

/********************************************************************************
 * Function: lin_diag_B4_service
 * Param<void>:
 * Return<static void>:
 * REQ IDs:
 * Discription: data dump service
 * Note:
*********************************************************************************/
static void lin_diag_B4_service(void)
{
    diag_negative_response(current_service_id, RSP_SERVICE_NOT_SUPPORT);
}


/********************************************************************************
 * Function: lin_diag_B5_service
 * Param<void>:
 * Return<static void>:
 * REQ IDs:
 * Discription: assign NAD via SN service
 * Note:
*********************************************************************************/
static void lin_diag_B5_service(void)
{
    diag_negative_response(current_service_id, RSP_SERVICE_NOT_SUPPORT);
}


/********************************************************************************
 * Function: lin_diag_B6_service
 * Param<void>:
 * Return<static void>:
 * REQ IDs:
 * Discription: save configuration service
 * Note:
*********************************************************************************/
static void lin_diag_B6_service(void)
{
#if 0
    
    diag_negative_response(current_service_id, RSP_SERVICE_NOT_SUPPORT);

#else

    l_u8 positive_rsp_buffer[2] = {0};

    positive_rsp_buffer[0] = UDS_GET_POSITIVE_RESPONSE(DIAG_B6);
    diag_transmit_response_msg(1u, positive_rsp_buffer);

    /* save the configuration */

#endif
}


/********************************************************************************
 * Function: lin_diag_B7_service
 * Param<void>:
 * Return<static void>:
 * REQ IDs:
 * Discription: assign frame id range service
 * Note: (mandatory)
*********************************************************************************/
static void lin_diag_B7_service(void)
{
    l_u8 i, start_index, pid[4];
    l_u8 positive_rsp_buffer[2] = {0};

    start_index = tl_get_rx_data(1);
    pid[0] = tl_get_rx_data(2);
    pid[1] = tl_get_rx_data(3);
    pid[2] = tl_get_rx_data(4);
    pid[3] = tl_get_rx_data(5);

    if(start_index > LIN_NUM_OF_FRAMES - 3)
    {
         diag_negative_response(current_service_id, RSP_GENERAL_REJECT);
    }
    else
    {
        if((start_index + 3) > (LIN_NUM_OF_FRAMES - 3))
        {
            for(i = start_index + 3; i > LIN_NUM_OF_FRAMES - 2; i--)
            {
                 if(0xFF != pid[i - start_index])
                 {
                      diag_negative_response(current_service_id, RSP_GENERAL_REJECT);
                      return;
                 }
            }
        }

        for(i = 0; i < 4; i++)
        {
            switch(pid[i])
            {
              case 0x00:  /* Unassign frame */
                  lin_frame_cfg_id[start_index + i] = 0xFF;
                  break;
              
              case 0xFF:
                  /* do not care */
                  break;
            
              default:
                  lin_frame_cfg_id[start_index + i] = (pid[i] & 0x3F);
                  break;
            }
        }
        
        positive_rsp_buffer[0] = UDS_GET_POSITIVE_RESPONSE(DIAG_B7);
        diag_transmit_response_msg(1u, positive_rsp_buffer);
    }


}




/********************************************************************************
 * Function: lin_diag_10_service
 * Param<void>:
 * Return<static void>:
 * REQ IDs:
 * Discription: 
 * Note:
*********************************************************************************/
static void lin_diag_10_service(void)
{
    l_u8    request_mode_pram;
    l_u8    response_code;
    uds_mode_t request_mode_type;
    l_u8    positive_rsp_buffer[6] = {0};
    
    if(uds_rx_length != DIA_10_MIN_LEN) 
	  {
        diag_negative_response(current_service_id, RSP_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
	  }
	  else
	  {
    	    
    	  request_mode_pram = tl_get_rx_data(1);
    	  request_mode_type = (uds_mode_t)(request_mode_pram & UDS_SUB_FUNCITON_PARAMETER_MASK);
    	  
        response_code = uds_set_diagnostic_mode(request_mode_type);
        if(RSP_NO_NEGATIVE_STATE != response_code)
        {
    //        org_access_type = 0;
            if((LD_FUNCTIONAL_NAD == diag_request_nad) || (LD_BROADCAST_NAD == diag_request_nad))
            {
                diag_no_response();
            }
            else
            {
                diag_negative_response(current_service_id, response_code);
            }
        }
        else
        {
    //        uds_lock_all_access();
            if (CLEAR == UDS_GET_SUB_FUNCTION_INDICATION_BIT(request_mode_pram))
            {
                /* transmit positive response */
                positive_rsp_buffer[0] = UDS_GET_POSITIVE_RESPONSE(DIAG_10);
                positive_rsp_buffer[1] = request_mode_type;
                positive_rsp_buffer[2] = 0x00;
                positive_rsp_buffer[3] = 0x32;
                positive_rsp_buffer[4] = 0x01;
                positive_rsp_buffer[5] = 0xF4;
                diag_transmit_response_msg(6, positive_rsp_buffer);
                return;
            }
            else
            {
                diag_no_response();
            }
        }          	  
	  }

}



/********************************************************************************
 * Function: lin_diag_22_service
 * Param<void>:
 * Return<static void>:
  * REQ IDs:
 * Discription: 
 * Note:
*********************************************************************************/
static void lin_diag_22_service(void)
{   
    l_u16 cur_id;
    l_u16  i;
    l_u16 cur_rsp_index = 0;
    l_u8  rx_data_index;
    l_u8  remain_data_length;
    l_u8  *u8_pos_rsp = lin_tl_data.queue;
    l_u8  u8_temp_buffer[10] = {0};
   
    
    if(uds_rx_length < DIA_22_MIN_LEN) 
    {
        diag_negative_response(current_service_id, RSP_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
    }
    else
    {
        remain_data_length = uds_rx_length - 1;
        if ((remain_data_length & 0x01u ) != 0)
        {
            diag_negative_response(current_service_id, RSP_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
        }
        else if (remain_data_length > 10)
        {
            diag_negative_response(current_service_id, RSP_REQUEST_OUT_OF_RANGE);
        }        
        else
        {
            for(i = 0; i < remain_data_length; i++)
            {
                u8_temp_buffer[i] = tl_get_rx_data(i+1);  
            }
            
            u8_pos_rsp[cur_rsp_index++] = UDS_GET_POSITIVE_RESPONSE(DIAG_22);
            rx_data_index = 0;
            while (remain_data_length > 0)
            {
                cur_id = ((l_u16)u8_temp_buffer[rx_data_index++]) << 8;
                cur_id |= u8_temp_buffer[rx_data_index++];
                remain_data_length -= 2;
                u8_pos_rsp[cur_rsp_index++] = cur_id >> 8;
                u8_pos_rsp[cur_rsp_index++] = cur_id & 0x00FFu;
                switch(cur_id)
                {
           
                    /* HW Part Number Geely format */
                    case 0xF1AA:
                        u8_pos_rsp[cur_rsp_index++] = part_number_geely[0];
                        u8_pos_rsp[cur_rsp_index++] = part_number_geely[1];
                        u8_pos_rsp[cur_rsp_index++] = part_number_geely[2];
                        u8_pos_rsp[cur_rsp_index++] = part_number_geely[3];
                        u8_pos_rsp[cur_rsp_index++] = part_number_geely[4];
                        u8_pos_rsp[cur_rsp_index++] = part_number_geely[5];
                        u8_pos_rsp[cur_rsp_index++] = part_number_geely[6];
                        u8_pos_rsp[cur_rsp_index++] = part_number_geely[7];
                        break;                     
                    
                    /* HW Part Number Volvo Cars format */
                    case 0xF12A:
                        u8_pos_rsp[cur_rsp_index++] = part_number_volvo[0];
                        u8_pos_rsp[cur_rsp_index++] = part_number_volvo[1];
                        u8_pos_rsp[cur_rsp_index++] = part_number_volvo[2];
                        u8_pos_rsp[cur_rsp_index++] = part_number_volvo[3];
                        u8_pos_rsp[cur_rsp_index++] = part_number_volvo[4];
                        u8_pos_rsp[cur_rsp_index++] = part_number_volvo[5];
                        u8_pos_rsp[cur_rsp_index++] = part_number_volvo[6];
                        break;      
                    
                    default:
                        /* Please comfirm never enter here */
                        diag_negative_response(current_service_id, RSP_REQUEST_OUT_OF_RANGE);
                        return;
                }          
          
            }
            diag_transmit_response_msg(cur_rsp_index, u8_pos_rsp);
        }
    }
}


/********************************************************************************
 * Function: lin_diag_2E_service
 * Param<void>:
 * Return<static void>:
 * REQ IDs:

 * Discription: 
 * Note:
*********************************************************************************/
static void lin_diag_2E_service(void)
{
    l_u16 cur_id;
    l_u8  rx_data_index;
    l_u8  u8_pos_rsp[3] = {0};  
 

#if 0     
    if(UDS_SESSION_STD == uds_get_session()) 
    {
        diag_negative_response(current_service_id, RSP_SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION);
    }    
    else if(UDS_LOCKED_ALL == uds_get_secure_status()) 
    {
        diag_negative_response(current_service_id, RSP_SECURITY_ACCESS_DENIED);
    }
#endif
//    else if(uds_rx_length < DIA_2E_MIN_LEN) 
    if(uds_rx_length < DIA_2E_MIN_LEN)  
    {
        diag_negative_response(current_service_id, RSP_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
    }
    else
    {
        rx_data_index = 1;
        u8_pos_rsp[0] = UDS_GET_POSITIVE_RESPONSE(current_service_id);
        u8_pos_rsp[1] = tl_get_rx_data(rx_data_index++);
        u8_pos_rsp[2] = tl_get_rx_data(rx_data_index++);

        cur_id = ((l_u16)u8_pos_rsp[1]) << 8;
        cur_id |= ((l_u16)u8_pos_rsp[2]);
        
        switch(cur_id)
        {
           
            /* Door Position */
            case 0xC000:
                  if ((uds_rx_length - 3) != 1)
                  {
                      diag_negative_response(current_service_id, RSP_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
                  }
                  else
                  {
                      diag_transmit_response_msg(3, u8_pos_rsp);	
//                    EE = ineeprom_write(&lin_tl_data.queue[rx_data_index], EE_DOOR_ID_ADDR, 4);
                      
                  }
                  break;	                         	
          	       	
          	
          default:
                diag_negative_response(current_service_id, RSP_REQUEST_OUT_OF_RANGE);
                break;
        }
   
	  
	  
	  }

}


/********************************************************************************
 * Function: lin_diag_3E_service
 * Param<void>:
 * Return<static void>:
 * REQ IDs:
 * Discription: 
 * Note:
*********************************************************************************/
static void lin_diag_3E_service(void)
{
    l_u8 u8_zero_sub_function = 1u;
    l_u8 u8_pos_rsp_buffer[2] = {0x00u};

	  if(uds_rx_length != DIA_3E_MIN_LEN) 
	  {
        diag_negative_response(DIAG_3E, RSP_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
        return;
	  }
    
    u8_pos_rsp_buffer[0] = UDS_GET_POSITIVE_RESPONSE(DIAG_3E);
    u8_zero_sub_function = tl_get_rx_data(1);
    if (0x00u == u8_zero_sub_function)
    {
        u8_pos_rsp_buffer[0] = UDS_GET_POSITIVE_RESPONSE(DIAG_3E);
        u8_pos_rsp_buffer[1] = 0x00;
        diag_transmit_response_msg(2,u8_pos_rsp_buffer);
    }
    else if (0x80u == u8_zero_sub_function)
    {
        diag_no_response();
    }
    else
    {
        if ((LD_FUNCTIONAL_NAD == diag_request_nad) || (LD_BROADCAST_NAD == diag_request_nad))
        {
            diag_no_response();
        }
        else
        {
            diag_negative_response(DIAG_3E, RSP_SUBFUNCTION_NOT_SUPPORTED);
        }
    }

}






