
#include "Motor_Parameter.h"

#include "MotorStalling_Serve.h"

#include "Method_Serve.h"

/*调用计数滤波方法，400ms堵转时间*/
CalcMethod StMotorStallFilter = {0,200,NO_STALLING,NO_STALLING};

/*
***  此标志位自动清除：当因堵转停止后，状态会自动变为非堵转状态-MotorStalling_Monitor的作用
***
*/

#if 1

/*
******
****  堵转为真的条件为：无霍尔速度信号和运动指令为运动
****  手动自动上时。堵转为上堵转状态 ，手动下和自动下时 堵转为下堵转状态
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
***此函数2ms调用一次，通电且400ms内没有收到hall速度脉冲，则认为是堵转
***
***  
*/
 uint8 MotorStalling_StatusGet(uint8 HallSignal_Speed, uint8 MotorAction_Status)
{   
    MethodCountFilter(MotorStalling_Monitor( HallSignal_Speed,MotorAction_Status),&StMotorStallFilter);
	
    return StMotorStallFilter.OutputSignal;
   
}


