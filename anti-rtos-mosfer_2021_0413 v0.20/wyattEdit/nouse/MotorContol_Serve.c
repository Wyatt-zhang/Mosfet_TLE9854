#include "Motor_Parameter.h"

#include "MotorControl_Serve.h"

#include "PWM_Serve.h"

#include "Interrupt_Serve.h"

#include "Position_Serve.h"

#include "Speed_Serve.h"



float32 Duty_Pattern = 0;

uint16 StopPosition =0;


PWM_Params Up_Paras = PWM_UPDEFAULT;

PWM_Params Down_Paras = PWM_DOWNDEFAULT;

Params_Handle ptr_up= &Up_Paras;

Params_Handle ptr_down = &Down_Paras;



static uint8 VoltRef_PWMDuty(Params_Handle ptr)
{
	uint8 flag=0;
	
	uint16 Baterry_mV=0;
	
	float VBat=0.00;
	
	if( (ADC1_GetChResult_mV(&Baterry_mV,ADC1_VBAT_SENSE) == true) && (Baterry_mV > 0) )  
	{
		VBat = (float32)Baterry_mV/1000.000;
		
		ptr->Phase1_PWMDuty = (float32)(ptr->Phase1_VoltRef) / VBat*100.00;
		
		ptr->Phase2_PWMDuty = (float32)(ptr->Phase2_VoltRef) /VBat*100.00;
			
		ptr->Phase3_PWMDuty = (float32)(ptr->Phase3_VoltRef) /VBat*100.00;
			
		flag = 1;
			
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
	
	return flag;
}


static float32 Resolution_Set(float32 PWMDutyEnd,float32 PWMDuty_Start,uint16 HallPulseNumber)
{
	return ( (PWMDutyEnd - PWMDuty_Start)/(float32)HallPulseNumber );

}
static void ResolutionCalc(Params_Handle ptr)
{
	ptr->Resolution_Increase = Resolution_Set(ptr->Phase2_PWMDuty,ptr->Phase1_PWMDuty,ptr->Phase1_Pulse);
	
	ptr->Resolution_Decrease = Resolution_Set(ptr->Phase3_PWMDuty,ptr->Phase2_PWMDuty,ptr->Phase3_Pulse);
}


 //TravelCnt ��ʾ���ֵ--Ŀ��������ڵĵ㣬ÿһ��ֹͣ������0
static void DutyPattern(uint16 TravelCnt,float32 PWMDuty_Start,float32 Resolution)
{
	 Duty_Pattern = PWMDuty_Start + (float32)TravelCnt * Resolution;
}
 

static void ParamsInit_Running(void)
 {
	 //PWM is 0
	Duty_Pattern = 0;
	 
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

/*  
*/


float32 tempcrese;
 
 //�Ȼ��� ��PI
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
			tempcrese = SpeedController_PI();
			
			Duty_Pattern = ptr->Phase2_PWMDuty + tempcrese;
			
			if(Duty_Pattern >=100)
				Duty_Pattern = 100;
		}
			

	
}

 //�������������1 ,ͬʱ windowTravel ��������������������duty
uint8 SetFlag=0;
static void Zone1_Process(Params_Handle ptr,uint8 ZoneFlag,uint16 Adder)
{
					
		//���ٽ׶� ���ж��Ƿ��˴�����
		if(ZoneFlag==ZONE_3)
		{
			//������ ���ô� ������ٵ��ٶ�
			if(SetFlag==0)
			{	
				SetFlag = 1;
					
				WindowTravel_Set(0);
				
				Adder = 0;
			}
			
			DutyPattern(Adder,ptr->Phase2_PWMDuty,ptr->Resolution_Decrease);
		}
		else if(ZoneFlag==ZONE_4) //�������� ���ٽ׶�
		{
			Duty_Pattern = ptr->Phase3_PWMDuty;
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
				//Duty_Pattern = ptr->Phase2_PWMDuty;
				//pid ���ٽ׶�
				
				Duty_Pattern = ptr->Phase2_PWMDuty + SpeedController_PI();
				
				if(Duty_Pattern >=100)
					Duty_Pattern = 100;
			}			
		}
}

float32 Temprecord;
uint16 Temprecord1;
uint16 Adder1=0;
static void Zone2_Process(Params_Handle ptr,uint8 ZoneFlag,uint16 WindowPosition,uint16 Adder)
{
	float32 y,y1;
		
	if( ZoneFlag!=ZONE_4)
	{
		y = ptr->Phase1_PWMDuty + (ptr->Resolution_Increase) * (float32)Adder;

		Adder1 = Distance_Get(WindowPosition,ptr->Direction);//��p1�ľ���
		
		y1 = ptr->Phase3_PWMDuty - (float32)Adder1 *(ptr->Resolution_Decrease);
		
		#if 1
		if(y >= y1)
		{
			if(SetFlag==0)
			{	
				SetFlag = 1;
				
				Temprecord = y ;
				
				Temprecord1 = Adder;

			}
			Duty_Pattern = Temprecord + (float32)(Adder-Temprecord1) *(ptr->Resolution_Decrease);
		}
		else
		{
			Duty_Pattern = y;
		}
		#endif
				
	}
	else
	{
		Duty_Pattern =  ptr->Phase3_PWMDuty; 
	}


}
static void Zone3_Process(Params_Handle ptr,uint8 zoneflag,uint16 Adder)
{

	uint16 tempdis;
	 
	float32 tempstart;
	
	if(zoneflag!=ZONE_4)
	{
		tempdis = Distance_Get(StopPosition,ptr->Direction);//��P1�ľ���
		
		tempstart = ptr->Phase3_PWMDuty - (float32)tempdis *(ptr->Resolution_Decrease);
				
		DutyPattern(Adder,tempstart,ptr->Resolution_Decrease);
		
		if(Duty_Pattern >= 63.3 && (ptr->Direction == 1))
		{
			Duty_Pattern = 63.3 ;
		}
		else if(Duty_Pattern >= 54.3 && (ptr->Direction == 0))
		{
			Duty_Pattern = 54.3 ;
		}
			
		
	}
	else
	{
		Duty_Pattern = ptr->Phase3_PWMDuty;		
	}

}

uint8 testcnt11=0;
uint8 temp123 =0;
uint8 ZoneFlag_windowpos=0;



static void Duty_AutoProcess(Params_Handle ptr)
 {
	uint16 WindowPos;

	uint16 Adder;
	 
	Adder = WindowTravel_Get();//���ֵ-�˴ε��г�
	 
	WindowPos = WindowPosition_Get();//����ֵ
	 

	if(1 == ptr->Direction)
		ZoneFlag_windowpos = WindowZoneGet_Up(WindowPos);
	else
		ZoneFlag_windowpos = WindowZoneGet_Down(WindowPos);
	 
	
	
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
static void Auto_Up(void)
{


	Duty_AutoProcess(ptr_up);

	#if COLOCKWISE
		SetPWM_Duty_UpDir(Duty_Pattern);
	#else
		SetPWM_Duty_DownDir(Duty_Pattern);
	#endif
	
}


static void Manual_Up(void)
{
	
	Duty_ManualProcess(ptr_up);
	
	#if COLOCKWISE
		SetPWM_Duty_UpDir(Duty_Pattern); 
	#else
		SetPWM_Duty_DownDir(Duty_Pattern); 
	#endif
}

static void Manual_Down(void)
{
	
	Duty_ManualProcess(ptr_down);
	
	#if COLOCKWISE
		SetPWM_Duty_DownDir(Duty_Pattern); 
	#else
		SetPWM_Duty_UpDir(Duty_Pattern); 
	#endif
}

static void Auto_Down(void)
{
	Duty_AutoProcess(ptr_down);

	#if COLOCKWISE
		SetPWM_Duty_DownDir(Duty_Pattern); 
	#else
		SetPWM_Duty_UpDir(Duty_Pattern);
	#endif
}

/**/
static void Motor_Stop(void)
{

	HBridgePWM_Off();//shutdown pwm
	
	ParamsInit_Running(); // 
	
	HallSpeedTicks_Reset();//hall pulse tick time set 0
	
	WindowTravel_Set(0);//window Travel set 0
	
	SetFlag =0;//��������������ı�־Ϊ
	
}


 

//uint8 MotorAction = STOP;

void Motion_Control(uint8 MotorAction)
{
	 switch(MotorAction)
	 {
		 case MANUAL_UP: Manual_Up();				break;
		 
		 case MANUAL_DOWN: Manual_Down();			break;
		 
		 case AUTO_UP: Auto_Up();					break;
		 
		 case AUTO_DOWN: Auto_Down();				break;
		 
		 default:   Motor_Stop();					break;
		 
	 }

}

