#include "Motor_Parameter.h"

#include "MotorControl_Serve.h"

#include "PWM_Serve.h"

#include "Interrupt_Serve.h"

#include "Position_Serve.h"

#include "PIFunc.h"

#include "Key_Serve.h"



/*  �ⲿ��������*/
extern SpeedControl UpDirConfig;

extern SpeedControl DownDirConfig;	


typedef struct{
	
	uint16 Phase1_Pulse;	/****************  ����ֵ ����ָ��ռ�ձȣ�Phase2_VoltRef���ľ����������� ��Ӧ����λ�ô����еļ��پ������*/
	
	uint16 Phase3_Pulse;	/****************  ����ֵ ���ٵ�ָ��ռ�ձȣ�Phase3_VoltRef���ľ�������������Ӧ����λ�ô����еļ��پ������*/
	
	
	float32 Phase1_PWMDuty;/****************����ֵ   ����ʼʱ�ĵ�ռ�ձȣ��ɲο���ѹ/��Դ��ѹ*/

	float32 Phase2_PWMDuty;/****************����ֵ   �ȶ�ʱ-����ʱ��ռ�ձ�*/

	float32 Phase3_PWMDuty;/****************����ֵ   ����ʱ����ռ�ձ�*/
	
	
	float32 Resolution_Increase;/****************����ֵ   ����ʱ�ķֱ���*/

	float32 Resolution_Decrease;/****************����ֵ   ��ͣʱ�ķֱ���*/
	
	
	uint8 Direction;  // 1 is up, 0  is down �������еķ���
	
	uint8 ZoneFlag_StopPosition; //  zone1 zone2 zone3 zone4 �������ڵ�λ������
	
	float32 DutyRecord ; //��¼ռ�ձȣ�����zone1��zone2��zone3����ļ���
}PWM_Params;

typedef PWM_Params* Params_Handle;

#define PWM_UPDEFAULT 	{0,\
						0,\
						0,\
						0,\
						0,\
						0,\
						0,\
						1,\
						0,\
						0}

#define PWM_DOWNDEFAULT {0,\
						0,\
						0,\
						0,\
						0,\
						0,\
						0,\
						0,\
						0,\
						0}

float32 Duty_Pattern = 0;

static uint16 StopPosition =0;


PWM_Params Up_Paras = PWM_UPDEFAULT;

PWM_Params Down_Paras = PWM_DOWNDEFAULT;

static Params_Handle ptr_up= &Up_Paras;

static Params_Handle ptr_down = &Down_Paras;

/***********************************************************************************************************
Description : �ɸ�����ѹֵ������ռ�ձ�
Input	    : ��Դ��ѹ���ο���ѹ�趨ֵ
Output		: ÿ���ڵ��ռ�ձ�
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
static void VoltRef_PWMDuty(Params_Handle ptr)
{
	uint16 Baterry_mV=0;
	
	float32 VBat=0.00;
	
	if( (ADC1_GetChResult_mV(&Baterry_mV,ADC1_VBAT_SENSE) == true) && (Baterry_mV > 0) )  
	{
		VBat = (float32)Baterry_mV/1000.000;
		
		if(ptr->Direction == 1)//up
		{
			ptr->Phase1_PWMDuty = (float32)(UpDirConfig.Phase1Volt) / VBat*100.00;
			
			ptr->Phase2_PWMDuty = (float32)(UpDirConfig.Phase2Volt) /VBat*100.00;
				
			ptr->Phase3_PWMDuty = (float32)(UpDirConfig.Pahse3Volt) /VBat*100.00;	

			ptr->Phase1_Pulse = UpDirConfig.IncreasePulse;
			
			ptr->Phase3_Pulse = UpDirConfig.DecreasePulse;			
		}
		else//down
		{
			ptr->Phase1_PWMDuty = (float32)(DownDirConfig.Phase1Volt) / VBat*100.00;
			
			ptr->Phase2_PWMDuty = (float32)(DownDirConfig.Phase2Volt) /VBat*100.00;
				
			ptr->Phase3_PWMDuty = (float32)(DownDirConfig.Pahse3Volt) /VBat*100.00;	
			
			ptr->Phase1_Pulse = DownDirConfig.IncreasePulse;
			
			ptr->Phase3_Pulse = DownDirConfig.DecreasePulse;
		}

			
			
		if( ptr->Phase1_PWMDuty >100.00)
		{
			ptr->Phase1_PWMDuty = 100.00;
		}
		else
		{
		}
		
		if(ptr->Phase2_PWMDuty>100.00)
		{
			ptr->Phase2_PWMDuty =100.00;
		}
		else
		{
		}

	}
	else
	{
	}

}

/***********************************************************************************************************
Description : �ֱ��ʼ���
Input	    : ��ֹ��ռ�ձȣ�����������Ŀ
Output		: 
Return		: �ֱ���--ÿ����һ��������Ҫ���ӻ��߼��ٵ�ռ�ձ�
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
static float32 Resolution_Set(float32 PWMDutyEnd,float32 PWMDuty_Start,uint16 HallPulseNumber)
{
	return ( (PWMDutyEnd - PWMDuty_Start)/(float32)HallPulseNumber );

}
/***********************************************************************************************************
Description : ����ͣ�ķֱ��ʼ���
Input	    : ����ͣ�ľ��
Output		: �ֱ���
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
static void ResolutionCalc(Params_Handle ptr)
{
	ptr->Resolution_Increase = Resolution_Set(ptr->Phase2_PWMDuty,ptr->Phase1_PWMDuty,ptr->Phase1_Pulse);
	
	ptr->Resolution_Decrease = Resolution_Set(ptr->Phase3_PWMDuty,ptr->Phase2_PWMDuty,ptr->Phase3_Pulse);
}

/***********************************************************************************************************
Description :����ͣ�����У����㵱ǰλ�õ�ռ�ձ�
Input	    : TravelCnt ��ʾ���ֵ--Ŀ��������ڵĵ㣬ÿһ��ֹͣ������0
			�˶���ʼ���ռ�ձȣ��ֱ���
Output		: ռ�ձ�
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
 
static void DutyPattern(uint16 TravelCnt,float32 PWMDuty_Start,float32 Resolution)
{
	 Duty_Pattern = PWMDuty_Start + (float32)TravelCnt * Resolution;
}
 
/***********************************************************************************************************
Description : �˶�����ǰ��һЩ������ʼ��
Input	    : 
Output		: 
				ʵʱռ�ձ���0
				�ȶ����������PID������λ
				�����ڵ㣨�����ȶ�����ͣ����ռ�ձȼ���
				����ͣ�ķֱ���
				������ֹͣλ������---���˶���ʼǰ��λ������
				����ֹͣλ����������
				
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
static void ParamsInit_Running(void)
 {
	 //PWM is 0
	Duty_Pattern = 0;
	
     //λ�õ����¼��㣬�����ڵ���
    PosParas_Init();		
     
	 //r
	ptr_up->DutyRecord = 0; 
	
	ptr_down->DutyRecord = 0; 
	 
	//PI parameters reset
	PIParams_Reset();
	
	 
	//according to voltage, set Phase1_PWMDuty  Phase2_PWMDuty  Phase3_PWMDuty
	VoltRef_PWMDuty(ptr_down);
	
	VoltRef_PWMDuty(ptr_up);
	 
	//update resolution
	ResolutionCalc(ptr_down);
	 
	ResolutionCalc(ptr_up);
	 
	 
	//��ʼ�������ȷ

	StopPosition = WindowPosition_Get(); // window stop position record
	 
	Down_Paras.ZoneFlag_StopPosition = WindowZoneGet_Down(StopPosition);
	
	Up_Paras.ZoneFlag_StopPosition = WindowZoneGet_Up(StopPosition);
		
	//

 }



/***********************************************************************************************************
Description : �ֶ����������µ� �˶������߼����Ȼ��� ��PI
Input	    : �г̣���ʼռ�ձȣ��ֱ���
Output		: ռ�ձ�
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
static void Duty_ManualProcess(Params_Handle ptr)
{
		uint16 TravelPulse;
	
		//�߹����г� ��ֹͣ��Ƚ�
		TravelPulse = WindowTravel_Get();
	
		//���ٽ׶� phase1
		if( (Duty_Pattern < (ptr->Phase2_PWMDuty) ) && (TravelPulse <= (ptr->Phase1_Pulse) ))
		{	
			DutyPattern(TravelPulse,ptr->Phase1_PWMDuty,ptr->Resolution_Increase);
		}
		else
		{
			//pid ���ٽ׶�
			Duty_Pattern = ptr->Phase2_PWMDuty + PI_SpeedController();
			
			if(Duty_Pattern >=100)
			{
				Duty_Pattern = 100;
			}
			else
			{
			}

		}
			

	
}

/***********************************************************************************************************
Description : �Զ����������µ� �˶������߼����� zone1��������
Input	    : ptr---PWM�ṹ��ָ��
			  ZoneFlag---���ڳ��������ĸ�����
				Adder---���ڳ�����λ����������֮��ľ��룬�г�
Output		: ռ�ձ�
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
static void Zone1_Process(Params_Handle ptr,uint8 ZoneFlag,uint16 Adder)
{
					
		//���ٽ׶� ���жϵ�ǰ�Ƿ��˴�����
		if(ZoneFlag==ZONE_3)
		{
			//������ ���ô� ������ٵ��ٶ�
			//����������� windowTravel ��������������������duty
			if(ptr->DutyRecord == 0)//�˿�ռ�ձȲ���
			{					
				//��adder����				
				WindowTravel_Set(0);
								
				//���ٺ��ռ�ձ�
				ptr->DutyRecord = Duty_Pattern;
				
				//���¼���ֱ���
				ptr->Resolution_Decrease = Resolution_Set(ptr->Phase3_PWMDuty,ptr->DutyRecord,ptr->Phase3_Pulse);
				
			}
			else
			{
			//��������ռ�ձȵ���ģʽ��		
				DutyPattern(Adder,ptr->DutyRecord,ptr->Resolution_Decrease);
			}
		}
		else if(ZoneFlag==ZONE_4) //�������� ���ٽ׶�
		{
			Duty_Pattern = ptr->Phase3_PWMDuty;
		}
		else if(ZoneFlag== ZONE_SOFTSTOP)//��ͣ���� ռ�ձ�Ϊ0 �����������������ֹͣ����Χ�����ռ�ձ�ͻ��
		{
			Duty_Pattern =0;
		}
		else 
		{
			//���ٽ׶�  
			//pid ���ٽ׶� 
			if( (Duty_Pattern < (ptr->Phase2_PWMDuty) ) && (Adder <= (ptr->Phase1_Pulse) ))
			{	
				DutyPattern(Adder,ptr->Phase1_PWMDuty,ptr->Resolution_Increase);
			}
			else
			{
				
				Duty_Pattern = ptr->Phase2_PWMDuty + PI_SpeedController();
				
				if(Duty_Pattern >=100)
					Duty_Pattern = 100;
			}			
		}
}






/***********************************************************************************************************
Description : �Զ����������µ� �˶������߼����� zone2��������
Input	    : ptr---PWM�ṹ��ָ��
			  ZoneFlag---���ڳ��������ĸ�����
			  WindowPosition --���ڳ�����λ��
			  Adder---���ڳ�����λ����������֮��ľ���
Output		: Duty_Pattern -- ռ�ձ�
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/

static void Zone2_Process(Params_Handle ptr,uint8 ZoneFlag,uint16 WindowPosition,uint16 Adder)
{
	float32 y,y1;

	uint16 tempadder=0;	


		//����ʼ�㣬�����������ߵĹ��ɣ�ռ�ձȵı仯
		y = ptr->Phase1_PWMDuty + (ptr->Resolution_Increase) * (float32)Adder;
		
		if(ZoneFlag==ZONE_2)//��zone2������ô����һ���ڼ��٣���û�е���ָ����ռ�ձ�
		{
			Duty_Pattern = y;
		}
		else if(ZoneFlag==ZONE_3)//��zone3���򣬳������ܵ�����ָ����ռ�ձȣ�����Ҫ�ж�
		{
			//���ڳ���λ����PWM��������ε���ʼ����ֵ���� ֮�����Ծ���
			tempadder = Distance_Get(WindowPosition,ptr->Direction);
			
			//������������Ӧ�½����ߵ�ռ�ձ�
			y1 = ptr->Phase3_PWMDuty - (float32)tempadder *(ptr->Resolution_Decrease);
			
			#if 1
			//�ﵽ�ٽ�㣬��ʼ�½�����ģʽ
			if(y >= y1)
			{
				Duty_Pattern = y1;
			}
			else//û�ﵽ�ٽ�㣬��������
			{
				Duty_Pattern = y;
			}
			#endif		
		}
		else if(ZoneFlag== ZONE_SOFTSTOP)//��ͣ���� ռ�ձ�Ϊ0 
		{
			Duty_Pattern =0;
		}
		else 
		{
			//zone4 ���� pwm �㶨
			Duty_Pattern =  ptr->Phase3_PWMDuty; 
		}


}


/***********************************************************************************************************
Description : �Զ����������µ� �˶������߼����� zone3��������
Input	    : ptr---PWM�ṹ��ָ��
			  ZoneFlag---���ڳ��������ĸ�����
			  Adder---���ڳ�����λ����������֮��ľ��룬�г�
Output		: Duty_Pattern -- ռ�ձ�
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
float32 DutyWatch =0;
static void Zone3_Process(Params_Handle ptr,uint8 ZoneFlag,uint16 Adder)
{	
	if(ZoneFlag!=ZONE_4)
	{	
		//ռ�ձ��½�ģʽ		
		DutyPattern(Adder,ptr->DutyRecord,ptr->Resolution_Decrease);
		
		//direction 1 is window up; 0 is window down
		//��������������Ӧ�½����ߵ�ռ�ձȣ����ڸ�����ֵ����ô���մ�ֵ����
		if(Duty_Pattern >= 63.3 && (ptr->Direction == 1))
		{
			Duty_Pattern = 63.3 ;
		}
		else if(Duty_Pattern >= 54.3 && (ptr->Direction == 0))
		{
			Duty_Pattern = 54.3 ;
		}
			
	}
	else if(ZoneFlag== ZONE_SOFTSTOP)//��ͣ���� ռ�ձ�Ϊ0 
	{
			Duty_Pattern =0;
	}
	else
	{
		Duty_Pattern = ptr->Phase3_PWMDuty;		
	}
	DutyWatch = Duty_Pattern;
}




/***********************************************************************************************************
Description : �Զ��˶��Ĵ������
Input	    : ptr---PWM�ṹ��ָ��
Output		: Duty_Pattern -- ռ�ձ�
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
 static void Duty_AutoProcess(Params_Handle ptr)
 {
	uint16 WindowPos=0;

	uint16 Adder=0;
	
	uint8 ZoneFlag_windowpos=0;
	
	uint16 tempdis;
	 
	Adder = WindowTravel_Get();//���ֵ-�������ڵ�λ����������֮��ľ���
	 
	WindowPos = WindowPosition_Get();//����ֵ--�������ڵ�λ��
	 
	//�ж����ڵĳ���λ��λ���ĸ�����
	if(1 == ptr->Direction)
	{
		ZoneFlag_windowpos = WindowZoneGet_Up(WindowPos);	
	}
	else
	{
		ZoneFlag_windowpos = WindowZoneGet_Down(WindowPos);
	}

	//�ж�����λ��--����λ�� ���ĸ����� �Ӷ�ִ����Ӧ�Ĳ���	 
	switch( ptr->ZoneFlag_StopPosition )
	{
		//�������ļ��� ���ٽ׶� ���� �㶨�׶�
		case ZONE_1 :
		
			
			Zone1_Process(ptr,ZoneFlag_windowpos,Adder);
	
		break;
		//
		
		// ���ٽ׶� ���ٽ׶�  �㶨�׶�
		case ZONE_2 : 

			Zone2_Process(ptr,ZoneFlag_windowpos,WindowPos,Adder);
			
		break;
		//
		
		//���ٽ׶�  �㶨�׶�		
		case ZONE_3 :
			
			//������˶�ʱ������ú��� ��DutyRecord��0
			//
			if(ptr->DutyRecord == 0)
			{
				//��ʼ�����ٶȺ㶨��zone4�Ľ��������ľ���-��������
				tempdis = Distance_Get(StopPosition,ptr->Direction);
		
				//��ʼ�������Ӧ�½����ߵ�ռ�ձ�ֵ
				ptr->DutyRecord = ptr->Phase3_PWMDuty - (float32)tempdis *(ptr->Resolution_Decrease);
			}
			
			Zone3_Process(ptr,ZoneFlag_windowpos,Adder);
			
		break;
		//
		
		//�㶨�׶�		
		case ZONE_4 :
			Duty_Pattern = ptr->Phase3_PWMDuty;
		
		break;
			
		default: break;
	}
	  
  } 
  
/***********************************************************************************************************
Description : �Զ��ϲ���
Input	    : 
Output		: ռ�ձ�
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/  
static void AutoUp(void)
{
	Duty_AutoProcess(ptr_up);		
}

/***********************************************************************************************************
Description : �ֶ��ϲ���
Input	    : 
Output		: ռ�ձ�
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
static void ManualUp(void)
{
	
	Duty_ManualProcess(ptr_up);
		
}
/***********************************************************************************************************
Description : �ֶ��²���
Input	    : 
Output		: ռ�ձ�
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
static void ManualDown(void)
{
	Duty_ManualProcess(ptr_down);
}


/***********************************************************************************************************
Description : �Զ��²���
Input	    : 
Output		: ռ�ձ�
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
static void AutoDown(void)
{
	
	Duty_AutoProcess(ptr_down);
	
	
}

/***********************************************************************************************************
Description : ���ֹͣ����ʱ�Ĳ�������
Input	    : 
Output		: ���������õ�
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
static void MotorStop(void)
{

	HBridgePWM_Off();//shutdown pwm
	
	ParamsInit_Running(); // �˶�ʱ�Ĳ�������
	
	WindowTravel_Set(0);//window Travel set 0
	

	
}
/***********************************************************************************************************
Description : 
Input	    : 
Output		: 
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
void testap(void)
{
	ParamsInit_Running(); // 
	
	WindowTravel_Set(0);//window Travel set 0���г���0
	

}
/***********************************************************************************************************
Description : �˶��ӿں���
Input	    : �˶�ָ��
Output		: ��Ӧ���˶�״̬
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
void Motion_Control(uint8 MotorAction)
{
	 switch(MotorAction)
	 {
		 case MANUAL_UP: 
			ManualUp();//output duty
			DutySet_RealUpDir(Duty_Pattern);//act according to duty 
		 break;
		 
		 case MANUAL_DOWN: 
			ManualDown();	
			DutySet_RealDownDir(Duty_Pattern);		 
		 break;
		 
		 case AUTO_UP: 
			AutoUp();	
			DutySet_RealUpDir(Duty_Pattern);		 
		 break;
		 
		 case AUTO_DOWN: 
			AutoDown();
			DutySet_RealDownDir(Duty_Pattern);			 
		 break;
		 
		 default:   MotorStop();					break;
		 
	 }

}
float32 PWMDuty_Get(void)
{
	return Duty_Pattern;
}

#if 0
float32 PWMDuty_Set(void)
{
	return Duty_Pattern;
}
#endif

uint16 WindowStopPos_Get(void)
{
	return StopPosition;
}

