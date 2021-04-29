#include "tle_device.h"	

#include "Motor_Parameter.h"

#include "Key_Serve.h"

#include "Method_Serve.h"

#include "MyAdc_Serve.h"



/* �����߼�������Ϊlocal ��������� lin�������� ,���ȼ� local >lin
�����lin��
*/

//test for now
extern uint8 SwitchLinCmd;



//���ü����˲�����
//20*2ms
CalcMethod StKeyFilter = {0,20,KEY_IDLE,KEY_IDLE};


/*
 ��Ҫ���� ����local�������߼�״̬��ת��

*/

typedef struct{
    uint8 TempKey;      /*��ʱ�İ�������߼�*/

    uint8 KeyComing ;  /*��ǰ��Ч���밴��*/
    
    uint8 OldKey ; /*��һ�ε���Ч���밴��*/
    
    uint8 OutputKey ; /*��������İ����߼�*/

}LocalKey;

LocalKey StKeyLogic = {KEY_IDLE};
   

/*�����߼���ֻ��Ӧһ��һ����Ч��������--�������غ��½���
�����м�̬--key_idleΪ�͵�ƽ������Ϊ�ߵ�ƽ
*/
static void LocalKeyLogic(uint8 LocalKeyFliter)
{
    
    /***  �����LIN �����źŵ��߼��� LIN�Ŀ����������
    ****
    */
    
    #if 0
    if(SwitchLinCmd!=0)/*��LIN��������*/
    {
        StKeyFilter.OutputSignal = SwitchLinCmd;    
    }
    #endif
    
    
    //�������뾭��һ���м�̬--Key_idle,�Ÿ������ڵ�OutKey,������ϵͳ�����ж���  
    if( StKeyLogic.OldKey ==KEY_IDLE || LocalKeyFliter ==KEY_IDLE)
    {
        /*���key ���µ��м�̬key*/
        StKeyLogic.TempKey = StKeyLogic.OutputKey; 
        
        
        StKeyLogic.KeyComing = LocalKeyFliter;///*������ע�ͣ�����Ϊ��һ�ε���Ч��ƽ���룬Ϊ��Ч���ź�*/       
    }
    else 
    {       
    }
    
    //StKeyLogic.KeyComing = LocalKeyFliter;/*������ע�ͣ����Դ� idle->manual->auto->manual������Ϊÿһ�ε���Ч��ƽ����Ϊ��Ч��ƽ*/
    
    
    StKeyLogic.OldKey = LocalKeyFliter; /*���¿��ص�����״̬*/
    
    
    /*��ͻ�����*/
	switch(StKeyLogic.KeyComing)
	 {
		 case KEY_IDLE: 
				if((KEY_AUTODOWN== StKeyLogic.TempKey) || (KEY_AUTOUP== StKeyLogic.TempKey))
				{
					StKeyLogic.OutputKey = StKeyLogic.TempKey;
				}
				else
				{
					StKeyLogic.OutputKey = KEY_IDLE;
				}
					break;

		 case KEY_MANUALUP: 
			    if( KEY_IDLE == StKeyLogic.TempKey )	
				{
					StKeyLogic.OutputKey = KEY_MANUALUP;
				}
				else
				{
					StKeyLogic.OutputKey = KEY_IDLE;
				}
					break;
		 
		 case KEY_MANUALDOWN:
			    if(  KEY_IDLE == StKeyLogic.TempKey )	
				{
					StKeyLogic.OutputKey = KEY_MANUALDOWN;
				}
				else
				{
					StKeyLogic.OutputKey = KEY_IDLE;
				}				
				
					break;
		 
		 case KEY_AUTOUP:
			    if( (KEY_IDLE == StKeyLogic.TempKey )||(KEY_MANUALUP == StKeyLogic.TempKey)  )	
				{
					StKeyLogic.OutputKey = KEY_AUTOUP;
				}
				else
				{
					StKeyLogic.OutputKey = KEY_IDLE;
				}			 
					break;
		 
		 case KEY_AUTODOWN: 
			    if( (KEY_IDLE == StKeyLogic.TempKey) || (KEY_MANUALDOWN == StKeyLogic.TempKey ) )	
				{
					StKeyLogic.OutputKey = KEY_AUTODOWN;
				}
				else
				{
					StKeyLogic.OutputKey = KEY_IDLE;
				}
					break;
		 
	     default:   StKeyLogic.OutputKey = KEY_IDLE;				break;
		 
	 }
 
}






/*
	real key action monitor
*/

uint8 Key_AnalogMonitor(void){

    MethodCountFilter(AdcKeyMonitor(),&StKeyFilter);
   
	LocalKeyLogic(StKeyFilter.OutputSignal);
	
	return StKeyLogic.OutputKey;
	
}

/*
	set key status  by software
*/
uint8 KeyStatus_Set(uint8 KeyStatus )
{
    StKeyFilter.OutputSignal = KeyStatus;

	StKeyLogic.OutputKey = KEY_IDLE;
    
    StKeyLogic.TempKey = KEY_IDLE;
    
    StKeyLogic.OldKey = KEY_IDLE;
	
	return KeyStatus;
}

/*
	get key status  by software
*/
uint8 KeyStatus_Get(void)
{
	return StKeyLogic.OutputKey;
}







