
#ifndef _LINSERVE
#define _LINSERVE

#include "LIN_Serve.h"


#include "Motor_Parameter.h"

#include "lin_il.h"


extern lin_rx_data_t rx_data;

extern lin_tx_data_t tx_data;
 
uint8 SwitchLinCmd = KEY_IDLE;

 void LINCmdDeal(void)
{   
    /*
    *** 0x00 idle, 0x01  up,0x02 down, 0x03 auto up,0x04 auto down
    */
    uint8 temp = (uint8)rx_data.ctr.SWCMDtoFL;
    
    switch(temp){
        
        case 0x00:SwitchLinCmd = KEY_IDLE;
        break;
        
        case 0x01:SwitchLinCmd = KEY_MANUALUP;
        break;
        
        case 0x02:SwitchLinCmd = KEY_MANUALDOWN;
        break;
        
        case 0x03:SwitchLinCmd = KEY_AUTOUP;
        break;
        
        case 0x04:SwitchLinCmd = KEY_AUTODOWN;
        break;
           
        default:SwitchLinCmd = KEY_IDLE; break;
    
    }
    //·¢ËÍÊý¾Ý
    tx_data.st.InitState  = 1u;

}



#endif






