
#include "Motor_Parameter.h"
#include "MotorStalling_Serve.h"



static uint8 StallingStatus = NO_STALLING;

static uint8 MotorStalling_Monitor(uint8 HallSpeedStatus,uint8 MotorAction)
{	
	uint8 TempStallingStatus = NO_STALLING;
	
	if( (HallSpeedStatus == NO_SPEEDSIGNAL) && ( MotorAction != STOP ) ) 
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


/*
	stalling status filter , no filter action for noStalling status
	filter time  625ms ~ 900ms is roboust
*/
static uint8 StallingStatus_Old = NO_STALLING;
static uint8 FilterCnt =25;
static uint8 Cnt=0;



static uint8 MotorStalling_Filter(uint8 TempStallingStatus,uint8 FilterCnt)
{
	uint8 StallingStatus_Filter = NO_STALLING ;
	
	
	switch(TempStallingStatus)
	{
		case NO_STALLING: 
			StallingStatus_Old = NO_STALLING; 
			break;
		
		default :
			if( TempStallingStatus!= StallingStatus_Old )
			{
				 StallingStatus_Old = TempStallingStatus ;
				 Cnt = 0;
			}
			else
			{
				
				if( ++Cnt>FilterCnt)
				{
					StallingStatus_Filter = TempStallingStatus ;
					Cnt = 0;
				}
				else
				{
				}
				
			}
		
			break;
	}


	return StallingStatus_Filter;
}


/* interface function*/
 uint8 MotorStalling_StatusGet(uint8 HallSignal_Speed,uint8 MotorAction_Status)
{
	
	uint8 TempStalling_status;
	
    TempStalling_status	= MotorStalling_Monitor( HallSignal_Speed,MotorAction_Status);
	
	StallingStatus  = MotorStalling_Filter(TempStalling_status,FilterCnt);	
	
	return StallingStatus;
}


