



#include "Interrupt_Serve.h"

#include "rtthread.h"




HallSign Hall = HALLDEFAULTS;



/*********isr callback functions***

interrupt serve function :
	1)HallSpeed_T2Call  GPT1 interrupt channel, priority 3 
	2)Sys_1msCall--1ms,priority is 3--default value
************************************/




/*
	T3 is 2.5Mhz- 0.8us,  16 bit register, every count is 0.8us, 0xFFFF is 52.4 ms,for hall speed signal capture

*/


void HallSpeed_T2Call(void)
{
	rt_interrupt_enter();
	
	Hall.HallStatus = SPEEDSIGNAL;
	
	Hall.HallStatusCnt128ms =0;	
	
	// get the value of T2 register, it is from T3 register
	Hall.HallSignalTick_New = GPT12E_T2_Value_Get();
	
	Hall.HallSignal_DeltaTick = Hall.HallSignalTick_New - Hall.HallSignalTick_Old;
	
	Hall.HallSignalTick_Old = Hall.HallSignalTick_New;
	//
		
	Hall.WindowTravel++;
	
	//Hall direction input signal P0.1,hardware related
	Hall.Motion_Direction= PORT_P01_Get();
	
	// when use this PCB, and pre-defined function-SetPWM_Duty_DownDir(uint8 Duty_Cycle) to drive motor ,Motion_Direction is 0 
	// function-SetPWM_Duty_UpDir(uint8 Duty_Cycle) to drive motor ,Motion_Direction is 1
	// so we jsut need get the real relationship between key and window direction
	if(Hall.Motion_Direction) 
	{
		#if COLOCKWISE
			Hall.WindowPosition--;
		#else
			Hall.WindowPosition++;
		#endif	
		
	}
	else// 0 is down 
	{
		#if COLOCKWISE
			Hall.WindowPosition++;
		#else
			Hall.WindowPosition--;
		#endif
	}

	rt_interrupt_leave();
	
}
uint16 WindowTravel_Get(void)
{
	return Hall.WindowTravel;
}

void WindowTravel_Set(uint16 Cnt)
{
	Hall.WindowTravel = Cnt;
}
uint16 WindowPosition_Get(void)
{
	return Hall.WindowPosition;
}

void WindowPosition_Set(uint16 Cnt)
{
	Hall.WindowPosition = Cnt;
}

uint16 HallSpeedTicks_Get(void)
{
	return Hall.HallSignal_DeltaTick;
}
void HallSpeedTicks_Reset(void)
{
	Hall.HallSignal_DeltaTick =0;
}


//25 is related to loop time  of function called.
uint8 HallSpeedSignal_StatusGet(void)
{
	if( (Hall.HallStatusCnt128ms)++ > 25u)
	{
		Hall.HallStatus = NO_SPEEDSIGNAL;
	}	
	return Hall.HallStatus;
}





