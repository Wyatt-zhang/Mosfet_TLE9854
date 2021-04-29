#include "Motor_Parameter.h"

#include "Position_Serve.h"

#include "Interrupt_Serve.h"

/*  �ⲿ��������*/
extern SpeedControl UpDirConfig;

extern SpeedControl DownDirConfig;		

extern Pos_Mark		UP_Pos;

extern Pos_Mark		Down_Pos;
						
						
uint8 InitStep = 0;


static uint16 WindowPositionMax =0;  // ��ʼ���� ���������ֵ ����ֵ





/***********************************************************************************************************
Description : ��ȷ��ʼ��һЩ�뻺��ͣ��Pid���ƣ���ͣ����˶����Ƶ�һЩ��������ֵ����
Input	    : 
Output		: �˶��������ֵ����
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
void PosParas_Init(void)
{
		//up direction
		UP_Pos.SoftStopPosition 	=  WINDOWPOSITION_ZERO_REF 		  + UpDirConfig.SoftStopPulse;//SOFTSTOPDISTANCE;
		 
		UP_Pos.Position_Zone4 		= UP_Pos.SoftStopPosition + UpDirConfig.ConstantPulse;//CONSTANT_PAHSE;//
	
		UP_Pos.Position_Zone3 		= UP_Pos.Position_Zone4     + UpDirConfig.DecreasePulse;//DECREASE_PAHSE;//
	
		UP_Pos.Position_Zone2 		= UP_Pos.Position_Zone3  + UpDirConfig.IncreasePulse;//INCREASE_PAHSE;//

	
		//down direction
		Down_Pos.SoftStopPosition	=          WindowPositionMax 		- DownDirConfig.SoftStopPulse;//SOFTSTOPDISTANCE;//

		Down_Pos.Position_Zone4	  	= Down_Pos.SoftStopPosition - DownDirConfig.ConstantPulse;//CONSTANT_PAHSE;//
	
		Down_Pos.Position_Zone3   	= Down_Pos.Position_Zone4	      - DownDirConfig.DecreasePulse;//DECREASE_PAHSE;//
	
		Down_Pos.Position_Zone2		= Down_Pos.Position_Zone3 - DownDirConfig.IncreasePulse; //INCREASE_PAHSE;	
}

/*
	Only initialize once,WindowTravelMax will be set  �ֶ��Զ� ���¶¶���Ч
*/
/***********************************************************************************************************
Description : 
Input	    : 
Output		: 
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
uint8 SoftStopInit(uint8 StallingStatus)
{
	// up stalling is the first movement
	if( (StallingStatus == UPSTALLING) && (InitStep== INIT_STEP0) )
	{
		WindowPosition_Set(WINDOWPOSITION_ZERO_REF);      //����ԭ���ʼ�� ����ֵ
		
		InitStep = INIT_STEP1;
	}	
	else if( (StallingStatus == DOWNSTALLING) && (InitStep== INIT_STEP1) ) 	//down stalling is the second movement
	{
		WindowPositionMax = WindowPosition_Get();     //�������ֵ��ʼ�� ����ֵ
		
		PosParas_Init();
		
		InitStep = INIT_STEP2 ;	
	}
	else
	{
	}
	return InitStep;
	
}

/*
	only work after initiation 
*/



void InitStepSet(uint8 SetFLag)
{
	InitStep = SetFLag;
}



/*

�������������˶�����ֳ�����������
Zone1 �������� -�������ļ��� ���ٽ׶� ���� �㶨�׶�
Zone2 ��������--���ٽ׶� ���ٽ׶�  �㶨�׶�
Zone3 ��������--���ٽ׶�  �㶨�׶�	
Zone4 ��������-�㶨�׶�	
ZONE_SOFTSTOP ----��ͣ����
*/
//��ʼ�������Ч
/***********************************************************************************************************
Description : ��������ʱ���жϳ�����λ������
Input	    : �����������ֵ
Output		: 
Return		: λ������
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
uint8 WindowZoneGet_Up(const uint16 WindowPosition) //������ ������ͣ��PWM  
{
	uint8 flag = 0;
	
		if(WindowPosition>=UP_Pos.Position_Zone2)
		{
			flag = ZONE_1;
		}
		else if(WindowPosition<UP_Pos.Position_Zone2 && WindowPosition>=UP_Pos.Position_Zone3)
		{
			flag = ZONE_2;
		}
		else if(WindowPosition<UP_Pos.Position_Zone3 && WindowPosition>=UP_Pos.Position_Zone4)
		{
			flag = ZONE_3;
		}
		else if(WindowPosition<UP_Pos.Position_Zone4 && WindowPosition>UP_Pos.SoftStopPosition)
		{
			flag = ZONE_4;
		}
		else //��ͣ������
		{
			flag = ZONE_SOFTSTOP;
		}
	

	return flag;	

}
/***********************************************************************************************************
Description : �����½�ʱ���жϳ�����λ������
Input	    : �����������ֵ
Output		: 
Return		: λ������
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
uint8 WindowZoneGet_Down(const uint16 WindowPosition) 
{
	uint8 flag = 0;
	
		if(WindowPosition <= Down_Pos.Position_Zone2)
		{
			flag = ZONE_1;
		}
		else if(WindowPosition>Down_Pos.Position_Zone2 && WindowPosition<=Down_Pos.Position_Zone3)
		{
			flag = ZONE_2;
		}
		else if(WindowPosition>Down_Pos.Position_Zone3 && WindowPosition<=Down_Pos.Position_Zone4 )
		{
			flag = ZONE_3;
		}
		else if(WindowPosition>Down_Pos.Position_Zone4 && WindowPosition<Down_Pos.SoftStopPosition)
		{
			flag = ZONE_4;
		}
		else //��ͣ������
		{
			flag = ZONE_SOFTSTOP;
		}
	
	return flag;	

}
 


/***********************************************************************************************************
Description : PWM��������ε���ʼ����ֵ���� �����ڳ���λ��֮�����Ծ���
			  �����ڼ���� Zone2/3 ��������ʱ���˶�����
Input	    : ��������ֵ���������з���
Output		: 
Return		: ��Ծ���
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
uint16 Distance_Get(uint16 WindowPosition,uint8 Direction)
{
	uint16 Temp;
	
	if(Direction == 0) //0 is down  direction
	{
			Temp = Down_Pos.Position_Zone4 - WindowPosition ;
	}
	else
	{
			Temp =  WindowPosition - UP_Pos.Position_Zone4 ;
	}

	
	return Temp;
}





