#include "PIFunc.h"

#include "Interrupt_Serve.h"

typedef struct
{
	float32 Give;
	float32 Kp;
	float32 Ki;
	float32 LastE;
	float32 PresentE;
	float32 OutMax;
	float32 OutMin;
	float32 Output;
	float32 FeedBack;
	float32 LastOutput;
	
	float32 SpeedRef_HallTicks;/* AvrDeltaticks--interval time of two hall pulses,uint is T3 timer count */
	
}PIFunc;

typedef PIFunc* PIFunc_Handle;

//Kp=2.0, outMax=1,outmin=-1
#define PIFUNC_DEFAULTS {0,\
	1.1,\
	0.002,\
	0,\
	0,\
	1.0,\
	-1.0,\
	0,\
	0,\
	0,\
	4000}

static PIFunc SpeedPI= PIFUNC_DEFAULTS;

static PIFunc_Handle ptr=&SpeedPI;	
	
	
/*
**increase PI type	
*/
static void PIFunc_Calc(PIFunc_Handle p)
{

	//get error
	p->PresentE = p->Give - p->FeedBack;
	
	//set the output
	p->Output = p->LastOutput + (p->Kp)*(p->PresentE - p->LastE) + (p->Ki)*(p->PresentE);
	
	//output limit
	if((p->Output)>(p->OutMax))
	{
		p->Output = p->OutMax ;
	}
	else if((p->Output)<(p->OutMin))
	{
		p->Output = p->OutMin;
	}
	else
	{
	}
	
	// save data
	p->LastOutput = p->Output ;
	
	p->LastE = p->PresentE;
}


/*
** before every action,PI parameters must be reset 
*/
void PIParams_Reset(void)
{	
	SpeedPI.LastE = 0;
	
	SpeedPI.PresentE =0;
	
	SpeedPI.LastOutput =0;	
}


/***********************************************************************************************************
Description : PI调节器
Input	    :电机的转速--用相邻两个霍尔脉冲的时间来表示，给定的转速---也用用相邻两个霍尔脉冲的时间来表示
Output		: 占空比增加部分
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/

float32 PI_SpeedController(void)
{
	float32 Avrtick = (float32 )HallSpeedTicks_Get();
	
	float32 duty_increase = 0;
	
	//Give is 4000ticks
	ptr->Give = -1;
	
	//ensure Feedback is 0~2
	if( Avrtick < ( ptr->SpeedRef_HallTicks * 2.0 )) 
	{
		ptr->FeedBack = Avrtick /(ptr->SpeedRef_HallTicks)*(-1.0); 
			
	}
	else
	{
		ptr->FeedBack = -2.0;
	}

	
	// PI calc
	PIFunc_Calc(ptr);
	
	duty_increase = (ptr->Output) * 50.0 ;
	
	return duty_increase;
}

