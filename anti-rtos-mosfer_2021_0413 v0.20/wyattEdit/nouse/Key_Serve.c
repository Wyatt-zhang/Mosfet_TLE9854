
#include "Motor_Parameter.h"

#include "Key_Serve.h"












static uint8 Current_KeyStatus = KEY_IDLE;

/*
 up and down key always get one activated, but auto key is compatible with down and up keys

*/



 static uint8 Key_AdcMonitor(void)
{
	uint8 Adc_KeyStatus=0x0; // 0000 means no key press down
	
	uint16 varMv=0xFFFF; //defualt value,unit mV ,means no key press down
	
	//MON1 UP key detect
	if( ADC1_GetChResult_mV(&varMv,ADC1_MON1) == true )  
	{
		
		//mon1 press down if less than 0.5V
		if(varMv<500)
			Adc_KeyStatus = KEY_MANUALUP;//0x01; 0001
		else
			Adc_KeyStatus &=0xFE;  //clear 0001
	}
		
	//MON2  DOWN key detect
	if((ADC1_GetChResult_mV(&varMv,ADC1_MON2) == true) )
	{
		if(varMv<500)
			Adc_KeyStatus = KEY_MANUALDOWN; //0010
		else
			Adc_KeyStatus &= 0xFD;//clear 0010
	}
	
	//MON3 AUTO key detect

	if((ADC1_GetChResult_mV(&varMv,ADC1_MON3) == true) )
	{
		if(varMv<500)
			Adc_KeyStatus |= 0x4; //Auto Key 0100
		else
			Adc_KeyStatus &= 0xFB;//clear 0100
	}

	return Adc_KeyStatus;
}
/*
	Filter time is  multiply FilterTime_Cnt by action time typ. 1ms  in main function . ex. FilterTime(20ms)=  FilterTime_Cnt(20)*systick handle(1ms)
*/
static uint8 Adc_KeyStatus_Old = KEY_IDLE;
static uint8 FilterCnt=0;
static uint8 FilterTime_Cnt = 8;


static uint8 Key_StatusFilter(uint8 Adc_KeyStatus,uint8 FilterTime_Cnt)
{
	uint8 Filter_KeyStatus;
	if(Adc_KeyStatus != Adc_KeyStatus_Old)
	{
		Adc_KeyStatus_Old = Adc_KeyStatus;
		FilterCnt = 0;
		
	}
	else
	{
		++FilterCnt;
	}
	
	if(FilterCnt> FilterTime_Cnt)
	{
		Filter_KeyStatus = Adc_KeyStatus;
		FilterCnt = 0;
	}
	else
	{
		Filter_KeyStatus = Current_KeyStatus;
	}
	return Filter_KeyStatus;
}


/*
	according  to  Filter_KeyStatus and Current_KeyStatus ,Current_KeyStatus  will be decided

*/
static uint8 Key_StatusUpdate(uint8 Filter_KeyStatus)
{
	switch(Filter_KeyStatus)
	 {
		 case KEY_IDLE: 
				if((KEY_MANUALDOWN==Current_KeyStatus) || (KEY_MANUALUP==Current_KeyStatus))
				{
					Current_KeyStatus = KEY_IDLE;
				}
				else
				{
					//do nothing
				}
					break;

		 case KEY_MANUALUP: 
			    if( (KEY_MANUALDOWN == Current_KeyStatus) || (KEY_AUTODOWN == Current_KeyStatus ) )	
				{
					Current_KeyStatus = KEY_IDLE;
				}
				else
				{
					Current_KeyStatus = KEY_MANUALUP;
				}
					break;
		 
		 case KEY_MANUALDOWN:
			    if( (KEY_MANUALUP == Current_KeyStatus) || (KEY_AUTOUP == Current_KeyStatus ) )	
				{
					Current_KeyStatus = KEY_IDLE;
				}
				else
				{
					Current_KeyStatus = KEY_MANUALDOWN;
				}				
				
					break;
		 
		 case KEY_AUTOUP:
			    if( (KEY_MANUALDOWN == Current_KeyStatus) || (KEY_AUTODOWN == Current_KeyStatus ) )	
				{
					Current_KeyStatus = KEY_IDLE;
				}
				else
				{
					Current_KeyStatus = KEY_AUTOUP;
				}			 
					break;
		 
		 case KEY_AUTODOWN: 
			    if( (KEY_MANUALUP == Current_KeyStatus) || (KEY_AUTOUP == Current_KeyStatus ) )	
				{
					Current_KeyStatus = KEY_IDLE;
				}
				else
				{
					Current_KeyStatus = KEY_AUTODOWN;
				}
					break;
		 
	     default:   Current_KeyStatus = KEY_IDLE;				break;
		 
	 }
	 return Current_KeyStatus;
}


/*

	real key action monitor
*/

uint8 Key_AnalogMonitor(void){
	
	uint8 Temp_KeyStatus = KEY_IDLE;
	
	Temp_KeyStatus = Key_AdcMonitor();
	
	Temp_KeyStatus = Key_StatusFilter(Temp_KeyStatus,FilterTime_Cnt);
	
	Temp_KeyStatus = Key_StatusUpdate(Temp_KeyStatus);
	
	return Temp_KeyStatus;
	
}

/*
	set key status  by software

*/
uint8 KeyStatus_Set(uint8 KeyStatus )
{
	Current_KeyStatus = KeyStatus;
	
	return KeyStatus;
}

/*
	get key status  by software
*/
uint8 KeyStatus_Get(void)
{
	return Current_KeyStatus;
}
/*
	set filter time

*/
void KeyFilter_CntSet(uint8 Cnt)
{
	FilterTime_Cnt = Cnt;
}






