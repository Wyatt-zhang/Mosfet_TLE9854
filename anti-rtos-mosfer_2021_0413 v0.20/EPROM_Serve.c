#include "EEPROM_Serve.h"



#if 0  


/*
****
****   �����ݴ�ŵ�flash�������4KB �У������infineon�ṩ�Ŀ⺯��
******
*/
#define FLASHSTARTADR = 0x1100F000;
#define PAGESIZE  0x80


static uint32 adrs =FLASHSTARTADR  ;
static uint8 Datatonvm[2]= {0x92,0x93};


void EEPROMDataSave(void)
{           
            //����һҳ������
            user_nvm_page_erase(adrs);
            
            //ָ����ַд������
            user_nvm_write(adrs,datatonvm,1u,0);

}

uint8 cntnvm =0;      
        
        if(cntnvm==0)
        {
            cntnvm=1;

        }
        
#endif


        