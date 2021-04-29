#include "EEPROM_Serve.h"



#if 0  


/*
****
****   把数据存放到flash区的最后4KB 中，需调用infineon提供的库函数
******
*/
#define FLASHSTARTADR = 0x1100F000;
#define PAGESIZE  0x80


static uint32 adrs =FLASHSTARTADR  ;
static uint8 Datatonvm[2]= {0x92,0x93};


void EEPROMDataSave(void)
{           
            //擦除一页的数据
            user_nvm_page_erase(adrs);
            
            //指定地址写入数据
            user_nvm_write(adrs,datatonvm,1u,0);

}

uint8 cntnvm =0;      
        
        if(cntnvm==0)
        {
            cntnvm=1;

        }
        
#endif


        