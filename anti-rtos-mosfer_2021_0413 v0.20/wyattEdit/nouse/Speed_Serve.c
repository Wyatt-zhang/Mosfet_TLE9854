#include "stdlib.h"

#include "Speed_Serve.h"

#include "Interrupt_Serve.h"	

#include "PIFunc.h"

#define SPEEDNUM 4u

static uint8 OldestData_Num = 0;

 uint16 DeltaTick_Array[SPEEDNUM] = {0};
 
 uint32 temp;


 uint16 AvrDeltatick =0;
 


void AvrSpeedCalc(uint16 DeltaTick)
{
	
	if(OldestData_Num > SPEEDNUM)
	{
		OldestData_Num = 0;
	}
	else
	{
	}
	
	DeltaTick_Array[OldestData_Num] =DeltaTick ; //(uint32)DeltaTick;
	
	temp = (uint32)DeltaTick_Array[0] + (uint32)DeltaTick_Array[1] + (uint32)DeltaTick_Array[2] + (uint32)DeltaTick_Array[3] ;
	
	AvrDeltatick = (uint16)(temp /(uint32)SPEEDNUM) ;
		
	OldestData_Num++;
}



PIFunc p1= PIFUNC_DEFAULTS;

PIFunc* p=&p1;


void PIParams_Reset(void)
{
	
	
	p->LastE = 0;
	
	p->PresentE =0;
	
	p->LastOutput =0;
		
}


float SpeedRef_HallTicks = 4000.00;// means 5000 ticks

float duty_increase;

float SpeedController_PI(void)
{
	
	//Give is 5000ticks
	p->Give = -1;
	
	//ensure Feedback is 0~2
	if( (float)AvrDeltatick < (2.0*SpeedRef_HallTicks))
	{
		p->FeedBack = ((float)AvrDeltatick)/SpeedRef_HallTicks *(-1.0); //
			
	}
	else
	{
		p->FeedBack = -2.0;
	}

	
	// PI calc
	PIFunc_Calc(p);
	
	duty_increase = (p->Output) * 50.0 ;
	
	return duty_increase;
}


void AvrSpeedtest(void)
{
	AvrSpeedCalc(HallSpeedTicks_Get());
						
}

