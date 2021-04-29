#include "Motor_Parameter.h"

#include "Position_Serve.h"

#include "Interrupt_Serve.h"

/*  外部变量申明*/
extern SpeedControl UpDirConfig;

extern SpeedControl DownDirConfig;		

extern Pos_Mark		UP_Pos;

extern Pos_Mark		Down_Pos;
						
						
uint8 InitStep = 0;


static uint16 WindowPositionMax =0;  // 初始化后 的最大坐标值 绝对值





/***********************************************************************************************************
Description : 正确初始化一些与缓起缓停，Pid控制，软停相关运动控制的一些绝对坐标值参数
Input	    : 
Output		: 运动区域绝对值坐标
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
void PosParas_Init(void)
{
		//up direction
		UP_Pos.SoftStopPosition 	=  WINDOWPOSITION_ZERO_REF 		  + UpDirConfig.SoftStopPulse;//SOFTSTOPDISTANCE;
		 
		UP_Pos.Position_Zone4 		= UP_Pos.SoftStopPosition + UpDirConfig.ConstantPulse;//CONSTANT_PAHSE;//
	
		UP_Pos.Position_Zone3 		= UP_Pos.Position_Zone4     + UpDirConfig.DecreasePulse;//DECREASE_PAHSE;//
	
		UP_Pos.Position_Zone2 		= UP_Pos.Position_Zone3  + UpDirConfig.IncreasePulse;//INCREASE_PAHSE;//

	
		//down direction
		Down_Pos.SoftStopPosition	=          WindowPositionMax 		- DownDirConfig.SoftStopPulse;//SOFTSTOPDISTANCE;//

		Down_Pos.Position_Zone4	  	= Down_Pos.SoftStopPosition - DownDirConfig.ConstantPulse;//CONSTANT_PAHSE;//
	
		Down_Pos.Position_Zone3   	= Down_Pos.Position_Zone4	      - DownDirConfig.DecreasePulse;//DECREASE_PAHSE;//
	
		Down_Pos.Position_Zone2		= Down_Pos.Position_Zone3 - DownDirConfig.IncreasePulse; //INCREASE_PAHSE;	
}

/*
	Only initialize once,WindowTravelMax will be set  手动自动 上下堵都有效
*/
/***********************************************************************************************************
Description : 
Input	    : 
Output		: 
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
uint8 SoftStopInit(uint8 StallingStatus)
{
	// up stalling is the first movement
	if( (StallingStatus == UPSTALLING) && (InitStep== INIT_STEP0) )
	{
		WindowPosition_Set(WINDOWPOSITION_ZERO_REF);      //坐标原点初始化 绝对值
		
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

/*
	only work after initiation 
*/



void InitStepSet(uint8 SetFLag)
{
	InitStep = SetFLag;
}



/*

把整个车窗的运动区域分成了以下区间
Zone1 区间启动 -有完整的加速 调速阶段 减速 恒定阶段
Zone2 区间启动--加速阶段 减速阶段  恒定阶段
Zone3 区间启动--减速阶段  恒定阶段	
Zone4 区间启动-恒定阶段	
ZONE_SOFTSTOP ----软停区域
*/
//初始化后才有效
/***********************************************************************************************************
Description : 车窗上升时，判断车窗的位置区域
Input	    : 车窗坐标绝对值
Output		: 
Return		: 位置区域
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
uint8 WindowZoneGet_Up(const uint16 WindowPosition) //将决定 缓气缓停的PWM  
{
	uint8 flag = 0;
	
		if(WindowPosition>=UP_Pos.Position_Zone2)
		{
			flag = ZONE_1;
		}
		else if(WindowPosition<UP_Pos.Position_Zone2 && WindowPosition>=UP_Pos.Position_Zone3)
		{
			flag = ZONE_2;
		}
		else if(WindowPosition<UP_Pos.Position_Zone3 && WindowPosition>=UP_Pos.Position_Zone4)
		{
			flag = ZONE_3;
		}
		else if(WindowPosition<UP_Pos.Position_Zone4 && WindowPosition>UP_Pos.SoftStopPosition)
		{
			flag = ZONE_4;
		}
		else //软停点区域
		{
			flag = ZONE_SOFTSTOP;
		}
	

	return flag;	

}
/***********************************************************************************************************
Description : 车窗下降时，判断车窗的位置区域
Input	    : 车窗坐标绝对值
Output		: 
Return		: 位置区域
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
uint8 WindowZoneGet_Down(const uint16 WindowPosition) 
{
	uint8 flag = 0;
	
		if(WindowPosition <= Down_Pos.Position_Zone2)
		{
			flag = ZONE_1;
		}
		else if(WindowPosition>Down_Pos.Position_Zone2 && WindowPosition<=Down_Pos.Position_Zone3)
		{
			flag = ZONE_2;
		}
		else if(WindowPosition>Down_Pos.Position_Zone3 && WindowPosition<=Down_Pos.Position_Zone4 )
		{
			flag = ZONE_3;
		}
		else if(WindowPosition>Down_Pos.Position_Zone4 && WindowPosition<Down_Pos.SoftStopPosition)
		{
			flag = ZONE_4;
		}
		else //软停点区域
		{
			flag = ZONE_SOFTSTOP;
		}
	
	return flag;	

}
 


/***********************************************************************************************************
Description : PWM保持区间段的起始绝对值坐标 与现在车窗位置之间的相对距离
			  有利于计算从 Zone2/3 区间启动时的运动控制
Input	    : 车窗绝对值坐标与运行方向
Output		: 
Return		: 相对距离
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
uint16 Distance_Get(uint16 WindowPosition,uint8 Direction)
{
	uint16 Temp;
	
	if(Direction == 0) //0 is down  direction
	{
			Temp = Down_Pos.Position_Zone4 - WindowPosition ;
	}
	else
	{
			Temp =  WindowPosition - UP_Pos.Position_Zone4 ;
	}

	
	return Temp;
}





