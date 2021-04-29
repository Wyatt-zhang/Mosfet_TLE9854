#include "Motor_Parameter.h"

#include "Position_Serve.h"

#include "Interrupt_Serve.h"
		 

uint8 InitStep = 0;


uint16 WindowPositionMax =0;  // 初始化后 的最大坐标值 绝对值
uint16 WindowStopPosition; //初始化后，车窗的位置停止点坐标 绝对值

Pos UpPos_Paras = UPPOS_DEFAULTS;
Pos DownPos_Paras = DOWNPOS_DEFAULTS;

Pos_Mark StopPosZone_Up = MARK_DEFAULTS ,StopPosZone_Down = MARK_DEFAULTS  ;
Pos_Mark RunningPosZone = MARK_DEFAULTS;

static void PosParas_Init(void)
{
		
		UpPos_Paras.SoftStopPosition =  WINDOWPOSITIONZERO + UpPos_Paras.SoftStopDistance;//
		 
		StopPosZone_Up.Position1 = UpPos_Paras.SoftStopPosition + UpPos_Paras.SpeedHoldDistance;
	
		StopPosZone_Up.Position2  = StopPosZone_Up.Position1  + UpPos_Paras.SpeedDecreaseDistance;
	
		StopPosZone_Up.Position3 = StopPosZone_Up.Position2 + UpPos_Paras.SpeedIncreaseDistance;	

		DownPos_Paras.SoftStopPosition = WindowPositionMax - DownPos_Paras.SoftStopDistance;

		StopPosZone_Down.Position1 = DownPos_Paras.SoftStopPosition - DownPos_Paras.SpeedHoldDistance;
	
		StopPosZone_Down.Position2  = StopPosZone_Down.Position1  - DownPos_Paras.SpeedDecreaseDistance;
	
		StopPosZone_Down.Position3 = StopPosZone_Down.Position2 - DownPos_Paras.SpeedIncreaseDistance;		
}

/*
	Only initialize once,WindowTravelMax will be set  手动自动 上下堵都有效
*/
uint8 SoftStopInit(uint8 StallingStatus)
{
	// up stalling is the first movement
	if( (StallingStatus == UPSTALLING) && (InitStep== INIT_STEP0) )
	{
		WindowPosition_Set(WINDOWPOSITIONZERO);      //坐标原点初始化 绝对值
		
		InitStep = INIT_STEP1;
	}	
	else if( (StallingStatus == DOWNSTALLING) && (InitStep== INIT_STEP1) ) 	//down stalling is the second movement
	{
		WindowPositionMax = WindowPosition_Get();     //坐标最大值初始化 绝对值
		
		PosParas_Init();
		
		InitStep = INIT_STEP2 ;	
	}
	else
	{
	}
	return InitStep;
	
}

/*  below is right only after init.   */
// get down soft stop point
uint16 DownSoftStopPos_Get(void)
{
	return  DownPos_Paras.SoftStopPosition;
}
//get up soft stop point
uint16 UpSoftStopPos_Get(void)
{
	return UpPos_Paras.SoftStopPosition;
	
}


 uint8 WindowZoneGet_Up(const uint16 WindowPosition) //将决定 缓气缓停的PWM  
{
	uint8 flag = 0;
	
		if(WindowPosition>=StopPosZone_Up.Position3)
		{
			flag = ZONE_1;
		}
		else if(WindowPosition<StopPosZone_Up.Position3 && WindowPosition>=StopPosZone_Up.Position2)
		{
			flag = ZONE_2;
		}
		else if(WindowPosition<StopPosZone_Up.Position2 && WindowPosition>=StopPosZone_Up.Position1 )
		{
			flag = ZONE_3;
		}
		else if(WindowPosition<StopPosZone_Up.Position1 && WindowPosition>UpPos_Paras.SoftStopPosition)
		{
			flag = ZONE_4;
		}
		else //软停点
		{
			flag = ZONE_SOFTSTOP;
		}
	

	return flag;	

}
 uint8 WindowZoneGet_Down(const uint16 WindowPosition) //将决定 缓气缓停的PWM 
{
	uint8 flag = 0;
	
		if(WindowPosition <= StopPosZone_Down.Position3)
		{
			flag = ZONE_1;
		}
		else if(WindowPosition>StopPosZone_Down.Position3 && WindowPosition<=StopPosZone_Down.Position2)
		{
			flag = ZONE_2;
		}
		else if(WindowPosition>StopPosZone_Down.Position2 && WindowPosition<=StopPosZone_Down.Position1 )
		{
			flag = ZONE_3;
		}
		else if(WindowPosition>StopPosZone_Down.Position1 && WindowPosition<DownPos_Paras.SoftStopPosition)
		{
			flag = ZONE_4;
		}
		else //软停点
		{
			flag = ZONE_SOFTSTOP;
		}
	
	return flag;	

}

uint16 Distance_Get(uint16 WindowPosition,uint8 Direction)
{
	uint16 Temp;
	
	if(Direction == 0) //0 is down
	{
			Temp = StopPosZone_Down.Position1 - WindowPosition ;
	}
	else
	{
			Temp =  WindowPosition - StopPosZone_Up.Position1  ;
	}

	
	return Temp;
}





