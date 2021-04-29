
#include "Motor_Parameter.h"

#include "MotorStalling_Serve.h"

#include "Method_Serve.h"

/*���ü����˲�������400ms��תʱ��*/
CalcMethod StMotorStallFilter = {0,200,NO_STALLING,NO_STALLING};

/*
***  �˱�־λ�Զ�����������תֹͣ��״̬���Զ���Ϊ�Ƕ�ת״̬-MotorStalling_Monitor������
***
*/

#if 1

/*
******
****  ��תΪ�������Ϊ���޻����ٶ��źź��˶�ָ��Ϊ�˶�
****  �ֶ��Զ���ʱ����תΪ�϶�ת״̬ ���ֶ��º��Զ���ʱ ��תΪ�¶�ת״̬
*/
static uint8 MotorStalling_Monitor(uint8 HallSpeedStatus,uint8 MotorAction)
{	
	uint8 TempStallingStatus = NO_STALLING;
	
	if( (HallSpeedStatus == NO_SPEEDSIGNAL) && ( (MotorAction) != STOP) ) 
	{

		if( (MotorAction ==AUTO_UP) || (MotorAction == MANUAL_UP))
		{
			TempStallingStatus = UPSTALLING;
		}
		else
		{			
			TempStallingStatus = DOWNSTALLING;
		}

	}
	else
	{
		TempStallingStatus = NO_STALLING;
	}
	return TempStallingStatus;
		
}

#endif



/**
***�˺���2ms����һ�Σ�ͨ����400ms��û���յ�hall�ٶ����壬����Ϊ�Ƕ�ת
***
***  
*/
 uint8 MotorStalling_StatusGet(uint8 HallSignal_Speed, uint8 MotorAction_Status)
{   
    MethodCountFilter(MotorStalling_Monitor( HallSignal_Speed,MotorAction_Status),&StMotorStallFilter);
	
    return StMotorStallFilter.OutputSignal;
   
}


