#include "AppLogic.h"

#include "Motor_Parameter.h"

#include "Key_Serve.h"

#include "Interrupt_Serve.h"

#include "Position_Serve.h"

#include "MotorStalling_Serve.h"


#include "MotorControl_Serve.h"

#include "AntiPinch_Serve.h"

#include <rtthread.h>
/*
if stalling and auto , stop the motor and clear the key, soft stop function enable
*/


uint8 MotorAction = STOP;



/*
堵转的逻辑操作
输入：MotorStalling 堵转状态 
输出：MotorAction Key_Status 电机运动逻辑 按键的状态

*/
/***********************************************************************************************************
Description : 
Input	    : 
Output		: 
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
static uint8 stallFlag = 0;

static void StallingProcess(uint8 MotorStalling,uint8 Key_input)
{
	#if 1

    /*发生了堵转*/
	if(MotorStalling ==UPSTALLING || MotorStalling ==DOWNSTALLING  ) 
	{
        if(Key_input==KEY_AUTOUP || Key_input ==KEY_AUTODOWN){
            
            stallFlag =0;
            
            KeyStatus_Set(KEY_IDLE);           
        
        }
        else{
            
            stallFlag = 1;   
        }
            

        MotorAction = STOP;
	
	}
	
    /*
    **如果是手动按键导致的堵转，必须需切换到中间态-空闲，后才能动作
    自动按键导致的堵转不做要求
    ****/
    if(stallFlag==1 && Key_input!=KEY_IDLE){
        
    	MotorAction = STOP;
	
    }
    else{
        stallFlag =0;
    }
    

	#endif
}

/*
上下软停的的逻辑操作
输入：WindowPos，MotorAction  电机的位置--初始化后的位置，电机的运动状态
输出：MotorAction Key_Status 电机运动逻辑 按键的状态

*/
/***********************************************************************************************************
Description : 自动下操作
Input	    : 
Output		: 占空比
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
static uint8 WindowZoneCheck(uint16 WindowPos)
{
	uint8 flag =0;
	
	if(MotorAction==AUTO_UP)
	{
		flag = WindowZoneGet_Up(WindowPos);
	}
	else if(MotorAction == AUTO_DOWN)
	{
		flag = WindowZoneGet_Down(WindowPos);
	}
	else
	{
	}
	return flag;

}
/***********************************************************************************************************
Description : 
Input	    : 
Output		: 
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
static void SoftStopProcess(uint16 WindowPos,uint8 StallingStatus)
{
	
	if( SoftStopInit( StallingStatus) == INIT_STEP2)//已经初始化
	{
		if( WindowZoneCheck(WindowPos) == ZONE_SOFTSTOP ) //位于软停点
		{
			MotorAction = STOP;
			
			KeyStatus_Set(KEY_IDLE);
		}
		else
		{
		}	
	}
	else//未初始化
	{
		//初始化过程前 ,自动挡按照手动挡来工作
		if( MotorAction==AUTO_UP )
		{
			MotorAction = MANUAL_UP;
			
			KeyStatus_Set(KEY_MANUALUP);
		}
		else if(MotorAction==AUTO_DOWN)//未初始化，自动下按照手动下的PWM控制逻辑来动作
		{
			MotorAction = MANUAL_DOWN;
		}	
		else
		{
		}
	}
	

}


#if 1



uint8 PinchEventCompleteFlag = 0;

//4s
#define ANTIWINDOWTIME 				4000u
#define APNORMAL  						0
#define APWINDOWTIME1 					1
#define APWINDOWTIME2_TEMP  			2
#define APWINDOWTIME2   				3

rt_tick_t APWindowTime1 = 0;

rt_tick_t APWindowTime2 = 0;

uint8 Auto_upDisable = 0;

uint8 ApState = APNORMAL;

uint8 AntiOverrideFlag = 0;

uint8 APWindowTime2sOut = 0;
/***********************************************************************************************************
Description : 防夹抑制处理逻辑
Input	    : 
Output		: 
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
static uint8  Anti_Override(uint8 APEventOccurFlag)
{
	rt_tick_t Anticurrenttime = rt_tick_get();
	
	uint8 Temp =0;
	
	uint8 AntiAPFLag = APEventOccurFlag ;

	//判断有没有超过2s的时间窗
	if(ApState ==APWINDOWTIME1 )
	{
		if( Anticurrenttime>((rt_tick_t)ANTIWINDOWTIME + APWindowTime1))
		{
			APWindowTime2sOut = 1;
		}
		else
		{
			APWindowTime2sOut=0u;
		}

	} 
	else if(ApState ==APWINDOWTIME2 )
	{
		if( Anticurrenttime>((rt_tick_t)ANTIWINDOWTIME + APWindowTime2))
		{
			APWindowTime2sOut = 1;
		}
		else
		{
			APWindowTime2sOut=0u;
			
			AntiOverrideFlag = 1;
		}

	}
	else
	{
	}
	//

	
	//第一个防夹时间窗事件触发，记录当前的时间节点--触发标志完成反转回退
	if(PinchEventCompleteFlag ==1u && 
		ApState==APNORMAL)
	{
		ApState = APWINDOWTIME1;
		
		PinchEventCompleteFlag = 0;
		
		APWindowTime1 = Anticurrenttime;	
	}//在第一个防夹时间窗内,发生了第二次防夹事件
	else if(AntiAPFLag ==1u && 
		ApState==APWINDOWTIME1)
	{
		ApState = APWINDOWTIME2_TEMP;
	
	}//二次防夹回退完成，开启第二个防夹时间窗
	else if(PinchEventCompleteFlag ==1u && 
		ApState==APWINDOWTIME2_TEMP)
	{
		ApState = APWINDOWTIME2;
		
		PinchEventCompleteFlag = 0;
		
		APWindowTime2 = Anticurrenttime;
	}
	else
	{
	}
	
	
	#if 1
	//不是防夹时候的下降动作 或者 超时
	if( (AntiAPFLag!=1 &&(MotorAction==AUTO_DOWN || MotorAction==MANUAL_DOWN))
		|| APWindowTime2sOut==1u )
	{
		ApState = APNORMAL;
				
		APWindowTime1 = 0;
		
		APWindowTime2 = 0;
		
		APWindowTime2sOut=0u;
		
		AntiOverrideFlag = 0;
	}
	else if(MotorAction==AUTO_UP || MotorAction==MANUAL_UP || APWindowTime2sOut==0u)
	{
	
	}
	else
	{
	}
	
	if(AntiOverrideFlag==1)
	{
		Auto_upDisable =1;
		
		Temp = Auto_upDisable;
	}
	else
	{
		Auto_upDisable =0;
	}
	#endif 
	
	return Temp;
}
		
#endif

/***********************************************************************************************************
Description : 防夹回退逻辑
Input	    : 
Output		: 
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
 static void APProcess(uint8 PinchFlag,uint16 WindowPos,uint8 Motorstalling)
{
	//夹持发生记录
	uint8 Temp =0;
	
	if(PinchFlag)//夹持发生
	{	
		Temp = 1;
		
		//反转下降450个脉冲 或者到下软停点
		if( WindowPos < ( (uint16)APREVERSEPULSE + WindowStopPos_Get()) &&  
			WindowZoneGet_Down(WindowPos)!=ZONE_SOFTSTOP)
		{
			MotorAction  = AUTO_DOWN;
				
			KeyStatus_Set(KEY_AUTODOWN);		
		}
		else
		{	
			#if 1
			//清除防夹标志
			Set_PinchFlag();
			
			//防夹完成事件
			PinchEventCompleteFlag = 1;
			
			MotorAction = STOP;
				
			KeyStatus_Set(KEY_IDLE);
			
			#endif
		}
				
	}
	else
	{
	}
	
	#if 1
	//防夹抑制功能为真
	if( Anti_Override(Temp)==1 )
	{
		//禁止自动上升的功能，自动变手动
		if(MotorAction ==AUTO_UP)
		{
			MotorAction = MANUAL_UP;
				
			KeyStatus_Set(KEY_MANUALUP);		
		}
		
		//防夹抑制状态中，上堵发生，重新初始化，initStep =0
		//退出防夹抑制功能
		if(Motorstalling == UPSTALLING)
		{
			InitStepSet(INIT_STEP0);
		}

	}
	#endif
}


/***********************************************************************************************************
Description : 根据一些输入信息 判断电机应该怎样运行
Input	    : 按键，位置，霍尔脉冲信息
Output		: 
Return		: 电机的运动指令
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/

uint8 MotorCommnads_Update(void)
{
	uint8 Key_Status,MotorStalling,HallSpeed;
	
	uint16 WindowPos = WindowPosition_Get();
	
	uint8 PinchFlag = Get_PinchStatus();
	
	/*  获取电机和按键的有关状态*/
	//按键状态
	Key_Status = Key_AnalogMonitor();
		
	//第一层操作 电机运动状态首先由按键状态来改变
	MotorAction = Key_Status;	
	
	#if 1
	//hall速度信号的状态
	HallSpeed = HallSpeedSignal_StatusGet();
	
	//电机堵转的状态
	MotorStalling = MotorStalling_StatusGet(HallSpeed,MotorAction);
		
    
	/*以下每个操作都会设置key and motor action*/
	//堵转逻辑操作
	StallingProcess(MotorStalling,Key_Status);
	
    #if 1
    
	//软停的逻辑操作
	SoftStopProcess(WindowPos,MotorStalling);
	
	//防夹的逻辑操作
	//发生夹持 自动下降
	APProcess(PinchFlag,WindowPos,MotorStalling);
    #endif
    
	#endif
	

	return MotorAction;

}
uint8 Get_MotorAction(void)
{
	return MotorAction;
}


