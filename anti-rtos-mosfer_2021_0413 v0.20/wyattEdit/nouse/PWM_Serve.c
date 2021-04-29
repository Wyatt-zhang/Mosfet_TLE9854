
#include "PWM_Serve.h"




// for window up and down

/*  
pre-defined:
		HS1 and LS2 mosfets are on
		Window direction is down
test reulst:
		Hall direction signal is high level and P0.1 is 0
		Duty_Cycle:100~0,higer duty, higher speed

*/
 void SetPWM_Duty_DownDir(float32 Duty_Cycle) 
{
		uint16 PeriodTick=0,Tick=0;
	
		if(Duty_Cycle>100.00) 
		{
			Duty_Cycle=100.00;
		}
		else if(Duty_Cycle <0)
		{
			Duty_Cycle=0;
		}
			
		//Ch1 is for HS2 and LS2, value setting is to HS2 mosfet,0 is low level ouput, HS2 mosfet is off and LS2 is on
		CCU6_Ch1_Value_Set(0);
		
		//Get the PWM period ticks
		PeriodTick = CCU6_T12_Period_Value_Get();
		
		//Calculate ticks from Duty_Cycle
		Tick= (uint16)( (float32)PeriodTick/100.00*Duty_Cycle);	
	
		//Ch0 is for HS1 and LS1, value setting is to HS1 mosfet,if 0 ,then low level ouput, HS1 mosfet is off and LS1 is on
		CCU6_Ch0_Value_Set(Tick); 

		CCU6_T12_Str_En();//Enable shadow register transfer action, compare register will be updated.  
}


/*
pre-defined:
		HS2 and LS1 mosfets are on
		Window direction is up 
test reulst:
		Hall direction signal is high level and P0.1 is 1
		Duty_Cycle:100~0,higer duty, higher speed
*/
 void SetPWM_Duty_UpDir(float32 Duty_Cycle)
{
		uint16 PeriodTick=0,Tick=0;
	
		if(Duty_Cycle>100.00)
		{
			Duty_Cycle = 100.00;
		}
		else if(Duty_Cycle <0)
		{
			Duty_Cycle = 0;
		}
		
		//Get the PWM period ticks
		PeriodTick = CCU6_T12_Period_Value_Get();
		
		//Ch1 is for HS2 and LS2, value setting is to HS2 mosfet,PeriodTick is High level ouput, HS2 mosfet is on and LS2 is off
		CCU6_Ch1_Value_Set(PeriodTick);
				
		//Calculate ticks from Duty_Cycle
		Tick = (uint16)( (float32)PeriodTick/100.00*(100.00-Duty_Cycle) );
		
		CCU6_Ch0_Value_Set(Tick);
		
		CCU6_T12_Str_En();
		
}
/*      hs1/hs2 0% duty cycle  low level output, mosfet  is off
		ls1/ls2 100% duty cycle high level output,mosfet is  on
		whole H bridge is deactivated.
*/

 void HBridgePWM_Off(void)
{
		CCU6_Ch0_Value_Set(0);
	
		CCU6_Ch1_Value_Set(0);
	
		CCU6_T12_Str_En();
}



