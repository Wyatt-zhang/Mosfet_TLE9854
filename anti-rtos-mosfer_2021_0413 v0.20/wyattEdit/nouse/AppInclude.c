#include "AppInclude.h"


void HardwareInit(void)
{

    TLE_Init();
	
	// for Hall signal capture
	GPT12E_T3_Start();
	
	//CCU6 block--PWM
	CCU6_StartTmr_T12();

	//enable  pwm output  for mosfet bridge
	BDRV_Set_Bridge(Ch_LS_PWM,Ch_PWM,Ch_LS_PWM,Ch_PWM);
}

/*
if stalling and auto , stop the motor and clear the key, soft stop function enable
*/
uint8  stallingtestautodown = 99;
uint8  stallingtestautoup = 99;
uint8 MotorAction = STOP;

uint8 MotorCommnads_Update(uint8 Key_Status,uint8 SoftStopInitFlag,uint8 SoftStopFlag,uint8 MotorStalling)
{

	
	//防止初始化过程前 按到了 自动上升键导致误初始化
	if( MotorAction==AUTO_UP )
	{
		if(SoftStopInitFlag!=1)
		{
			MotorAction = STOP;
		}		
		else
		{
		}
	}
	else
	{
	}
		
	if (MotorStalling == UPSTALLING) 
	{
		stallingtestautoup= 11;
		
		if(Key_Status == KEY_AUTOUP)
		{
			MotorAction = STOP;
			
			KeyStatus_Set(KEY_IDLE);
		}
		else
		{	
		}
	
	}
	else if(MotorStalling == DOWNSTALLING)
	{
		stallingtestautodown = 11;
		
		if(Key_Status == KEY_AUTODOWN)
		{
			MotorAction = STOP;
			
			KeyStatus_Set(KEY_IDLE);
		}
		else
		{
		}
		
	}
	else
	{
	}


	if(SoftStopFlag==ZONE_SOFTSTOP)
	{
		MotorAction = STOP;
		
		KeyStatus_Set(KEY_IDLE);
	}
	else
	{
		MotorAction = Key_Status;
	}

	return MotorAction;

}

uint8 MotorStatus_Get(void)
{
	return MotorAction;
}
void MotorStatus_Set(uint8 SetStatus)
{
	MotorAction = SetStatus ;
}
