#include "Motor_Parameter.h"

#include "ADC_Serve.h"

#include "tle_device.h"	

#include "rtthread.h"
typedef struct{
	uint16 BatterymV;
	uint16 Mon1ChannelmV;
	uint16 Mon2ChannelmV;
	uint16 Mon3ChannelmV;
	
	
	#if 1
	uint16 UnderVolt;
	uint16 OverVolt;
	uint16 GapVolt;
	rt_tick_t UnderVoltTime;
	rt_tick_t OverVoltTime;
	#endif
}AdcVolt;

AdcVolt StVolt = {0,0,0,0,8800,16200,200,0,0};	

#define ONESECOND   1000u
#define HALFSECOND   500u


void AdcVoltMonitor(void)
{
	//power 
	if( ADC1_GetChResult_mV(&(StVolt.BatterymV),ADC1_VBAT_SENSE) == true)
	{
		if(StVolt.BatterymV <StVolt.UnderVolt )
		{
			//低压事件发生
			rt_event_send(&MotorEvent,EVENT_UNDERVOLT);
		}
		else if(StVolt.BatterymV > StVolt.OverVolt)
		{	
			//高压事件发生
			rt_event_send(&MotorEvent,EVENT_UNDERVOLT);
		}
		else
		{
		}
	}
	
	//MON1 UP key detect
	if( ADC1_GetChResult_mV(&(StVolt.Mon1ChannelmV),ADC1_MON1) == true )  
	{
		
	}
		
	//MON2  DOWN key detect
	if((ADC1_GetChResult_mV(&(StVolt.Mon2ChannelmV),ADC1_MON2) == true) )
	{

	}
	
	//MON3 AUTO key detect
	if((ADC1_GetChResult_mV(&(StVolt.Mon3ChannelmV),ADC1_MON3) == true) )
	{

	}

}

void volttest(void)
{
	rt_uint32_t e;
	
	if(rt_event_recv(&MotorEvent,EVENT_UNDERVOLT,
					RT_EVENT_FLAG_OR,RT_WAITING_NO,&e)== RT_EOK)
	{
	
	}
}



