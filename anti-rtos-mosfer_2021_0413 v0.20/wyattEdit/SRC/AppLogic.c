#include "AppLogic.h"

#include "Motor_Parameter.h"

#include "Key_Serve.h"

#include "Interrupt_Serve.h"

#include "Position_Serve.h"

#include "MotorStalling_Serve.h"


#include "MotorControl_Serve.h"

#include "AntiPinch_Serve.h"

#include <rtthread.h>
/*
if stalling and auto , stop the motor and clear the key, soft stop function enable
*/


uint8 MotorAction = STOP;



/*
��ת���߼�����
���룺MotorStalling ��ת״̬ 
�����MotorAction Key_Status ����˶��߼� ������״̬

*/
/***********************************************************************************************************
Description : 
Input	    : 
Output		: 
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
static uint8 stallFlag = 0;

static void StallingProcess(uint8 MotorStalling,uint8 Key_input)
{
	#if 1

    /*�����˶�ת*/
	if(MotorStalling ==UPSTALLING || MotorStalling ==DOWNSTALLING  ) 
	{
        if(Key_input==KEY_AUTOUP || Key_input ==KEY_AUTODOWN){
            
            stallFlag =0;
            
            KeyStatus_Set(KEY_IDLE);           
        
        }
        else{
            
            stallFlag = 1;   
        }
            

        MotorAction = STOP;
	
	}
	
    /*
    **������ֶ��������µĶ�ת���������л����м�̬-���У�����ܶ���
    �Զ��������µĶ�ת����Ҫ��
    ****/
    if(stallFlag==1 && Key_input!=KEY_IDLE){
        
    	MotorAction = STOP;
	
    }
    else{
        stallFlag =0;
    }
    

	#endif
}

/*
������ͣ�ĵ��߼�����
���룺WindowPos��MotorAction  �����λ��--��ʼ�����λ�ã�������˶�״̬
�����MotorAction Key_Status ����˶��߼� ������״̬

*/
/***********************************************************************************************************
Description : �Զ��²���
Input	    : 
Output		: ռ�ձ�
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
static uint8 WindowZoneCheck(uint16 WindowPos)
{
	uint8 flag =0;
	
	if(MotorAction==AUTO_UP)
	{
		flag = WindowZoneGet_Up(WindowPos);
	}
	else if(MotorAction == AUTO_DOWN)
	{
		flag = WindowZoneGet_Down(WindowPos);
	}
	else
	{
	}
	return flag;

}
/***********************************************************************************************************
Description : 
Input	    : 
Output		: 
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
static void SoftStopProcess(uint16 WindowPos,uint8 StallingStatus)
{
	
	if( SoftStopInit( StallingStatus) == INIT_STEP2)//�Ѿ���ʼ��
	{
		if( WindowZoneCheck(WindowPos) == ZONE_SOFTSTOP ) //λ����ͣ��
		{
			MotorAction = STOP;
			
			KeyStatus_Set(KEY_IDLE);
		}
		else
		{
		}	
	}
	else//δ��ʼ��
	{
		//��ʼ������ǰ ,�Զ��������ֶ���������
		if( MotorAction==AUTO_UP )
		{
			MotorAction = MANUAL_UP;
			
			KeyStatus_Set(KEY_MANUALUP);
		}
		else if(MotorAction==AUTO_DOWN)//δ��ʼ�����Զ��°����ֶ��µ�PWM�����߼�������
		{
			MotorAction = MANUAL_DOWN;
		}	
		else
		{
		}
	}
	

}


#if 1



uint8 PinchEventCompleteFlag = 0;

//4s
#define ANTIWINDOWTIME 				4000u
#define APNORMAL  						0
#define APWINDOWTIME1 					1
#define APWINDOWTIME2_TEMP  			2
#define APWINDOWTIME2   				3

rt_tick_t APWindowTime1 = 0;

rt_tick_t APWindowTime2 = 0;

uint8 Auto_upDisable = 0;

uint8 ApState = APNORMAL;

uint8 AntiOverrideFlag = 0;

uint8 APWindowTime2sOut = 0;
/***********************************************************************************************************
Description : �������ƴ����߼�
Input	    : 
Output		: 
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
static uint8  Anti_Override(uint8 APEventOccurFlag)
{
	rt_tick_t Anticurrenttime = rt_tick_get();
	
	uint8 Temp =0;
	
	uint8 AntiAPFLag = APEventOccurFlag ;

	//�ж���û�г���2s��ʱ�䴰
	if(ApState ==APWINDOWTIME1 )
	{
		if( Anticurrenttime>((rt_tick_t)ANTIWINDOWTIME + APWindowTime1))
		{
			APWindowTime2sOut = 1;
		}
		else
		{
			APWindowTime2sOut=0u;
		}

	} 
	else if(ApState ==APWINDOWTIME2 )
	{
		if( Anticurrenttime>((rt_tick_t)ANTIWINDOWTIME + APWindowTime2))
		{
			APWindowTime2sOut = 1;
		}
		else
		{
			APWindowTime2sOut=0u;
			
			AntiOverrideFlag = 1;
		}

	}
	else
	{
	}
	//

	
	//��һ������ʱ�䴰�¼���������¼��ǰ��ʱ��ڵ�--������־��ɷ�ת����
	if(PinchEventCompleteFlag ==1u && 
		ApState==APNORMAL)
	{
		ApState = APWINDOWTIME1;
		
		PinchEventCompleteFlag = 0;
		
		APWindowTime1 = Anticurrenttime;	
	}//�ڵ�һ������ʱ�䴰��,�����˵ڶ��η����¼�
	else if(AntiAPFLag ==1u && 
		ApState==APWINDOWTIME1)
	{
		ApState = APWINDOWTIME2_TEMP;
	
	}//���η��л�����ɣ������ڶ�������ʱ�䴰
	else if(PinchEventCompleteFlag ==1u && 
		ApState==APWINDOWTIME2_TEMP)
	{
		ApState = APWINDOWTIME2;
		
		PinchEventCompleteFlag = 0;
		
		APWindowTime2 = Anticurrenttime;
	}
	else
	{
	}
	
	
	#if 1
	//���Ƿ���ʱ����½����� ���� ��ʱ
	if( (AntiAPFLag!=1 &&(MotorAction==AUTO_DOWN || MotorAction==MANUAL_DOWN))
		|| APWindowTime2sOut==1u )
	{
		ApState = APNORMAL;
				
		APWindowTime1 = 0;
		
		APWindowTime2 = 0;
		
		APWindowTime2sOut=0u;
		
		AntiOverrideFlag = 0;
	}
	else if(MotorAction==AUTO_UP || MotorAction==MANUAL_UP || APWindowTime2sOut==0u)
	{
	
	}
	else
	{
	}
	
	if(AntiOverrideFlag==1)
	{
		Auto_upDisable =1;
		
		Temp = Auto_upDisable;
	}
	else
	{
		Auto_upDisable =0;
	}
	#endif 
	
	return Temp;
}
		
#endif

/***********************************************************************************************************
Description : ���л����߼�
Input	    : 
Output		: 
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
 static void APProcess(uint8 PinchFlag,uint16 WindowPos,uint8 Motorstalling)
{
	//�гַ�����¼
	uint8 Temp =0;
	
	if(PinchFlag)//�гַ���
	{	
		Temp = 1;
		
		//��ת�½�450������ ���ߵ�����ͣ��
		if( WindowPos < ( (uint16)APREVERSEPULSE + WindowStopPos_Get()) &&  
			WindowZoneGet_Down(WindowPos)!=ZONE_SOFTSTOP)
		{
			MotorAction  = AUTO_DOWN;
				
			KeyStatus_Set(KEY_AUTODOWN);		
		}
		else
		{	
			#if 1
			//������б�־
			Set_PinchFlag();
			
			//��������¼�
			PinchEventCompleteFlag = 1;
			
			MotorAction = STOP;
				
			KeyStatus_Set(KEY_IDLE);
			
			#endif
		}
				
	}
	else
	{
	}
	
	#if 1
	//�������ƹ���Ϊ��
	if( Anti_Override(Temp)==1 )
	{
		//��ֹ�Զ������Ĺ��ܣ��Զ����ֶ�
		if(MotorAction ==AUTO_UP)
		{
			MotorAction = MANUAL_UP;
				
			KeyStatus_Set(KEY_MANUALUP);		
		}
		
		//��������״̬�У��϶·��������³�ʼ����initStep =0
		//�˳��������ƹ���
		if(Motorstalling == UPSTALLING)
		{
			InitStepSet(INIT_STEP0);
		}

	}
	#endif
}


/***********************************************************************************************************
Description : ����һЩ������Ϣ �жϵ��Ӧ����������
Input	    : ������λ�ã�����������Ϣ
Output		: 
Return		: ������˶�ָ��
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/

uint8 MotorCommnads_Update(void)
{
	uint8 Key_Status,MotorStalling,HallSpeed;
	
	uint16 WindowPos = WindowPosition_Get();
	
	uint8 PinchFlag = Get_PinchStatus();
	
	/*  ��ȡ����Ͱ������й�״̬*/
	//����״̬
	Key_Status = Key_AnalogMonitor();
		
	//��һ����� ����˶�״̬�����ɰ���״̬���ı�
	MotorAction = Key_Status;	
	
	#if 1
	//hall�ٶ��źŵ�״̬
	HallSpeed = HallSpeedSignal_StatusGet();
	
	//�����ת��״̬
	MotorStalling = MotorStalling_StatusGet(HallSpeed,MotorAction);
		
    
	/*����ÿ��������������key and motor action*/
	//��ת�߼�����
	StallingProcess(MotorStalling,Key_Status);
	
    #if 1
    
	//��ͣ���߼�����
	SoftStopProcess(WindowPos,MotorStalling);
	
	//���е��߼�����
	//�����г� �Զ��½�
	APProcess(PinchFlag,WindowPos,MotorStalling);
    #endif
    
	#endif
	

	return MotorAction;

}
uint8 Get_MotorAction(void)
{
	return MotorAction;
}


