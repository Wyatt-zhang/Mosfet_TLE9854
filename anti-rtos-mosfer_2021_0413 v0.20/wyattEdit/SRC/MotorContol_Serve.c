#include "Motor_Parameter.h"

#include "MotorControl_Serve.h"

#include "PWM_Serve.h"

#include "Interrupt_Serve.h"

#include "Position_Serve.h"

#include "PIFunc.h"

#include "Key_Serve.h"



/*  外部变量申明*/
extern SpeedControl UpDirConfig;

extern SpeedControl DownDirConfig;	


typedef struct{
	
	uint16 Phase1_Pulse;	/****************  计算值 缓起到指定占空比（Phase2_VoltRef）的经过的脉冲数 ，应等于位置处理中的加速距离参数*/
	
	uint16 Phase3_Pulse;	/****************  计算值 减速到指定占空比（Phase3_VoltRef）的经过的脉冲数，应等于位置处理中的减速距离参数*/
	
	
	float32 Phase1_PWMDuty;/****************计算值   缓起开始时的的占空比，由参考电压/电源电压*/

	float32 Phase2_PWMDuty;/****************计算值   稳定时-调速时的占空比*/

	float32 Phase3_PWMDuty;/****************计算值   减速时最后的占空比*/
	
	
	float32 Resolution_Increase;/****************计算值   缓起时的分辨率*/

	float32 Resolution_Decrease;/****************计算值   缓停时的分辨率*/
	
	
	uint8 Direction;  // 1 is up, 0  is down 车窗运行的方向
	
	uint8 ZoneFlag_StopPosition; //  zone1 zone2 zone3 zone4 车窗所在的位置区域
	
	float32 DutyRecord ; //记录占空比，方便zone1和zone2，zone3区间的计算
}PWM_Params;

typedef PWM_Params* Params_Handle;

#define PWM_UPDEFAULT 	{0,\
						0,\
						0,\
						0,\
						0,\
						0,\
						0,\
						1,\
						0,\
						0}

#define PWM_DOWNDEFAULT {0,\
						0,\
						0,\
						0,\
						0,\
						0,\
						0,\
						0,\
						0,\
						0}

float32 Duty_Pattern = 0;

static uint16 StopPosition =0;


PWM_Params Up_Paras = PWM_UPDEFAULT;

PWM_Params Down_Paras = PWM_DOWNDEFAULT;

static Params_Handle ptr_up= &Up_Paras;

static Params_Handle ptr_down = &Down_Paras;

/***********************************************************************************************************
Description : 由给定电压值，计算占空比
Input	    : 电源电压，参考电压设定值
Output		: 每个节点的占空比
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
static void VoltRef_PWMDuty(Params_Handle ptr)
{
	uint16 Baterry_mV=0;
	
	float32 VBat=0.00;
	
	if( (ADC1_GetChResult_mV(&Baterry_mV,ADC1_VBAT_SENSE) == true) && (Baterry_mV > 0) )  
	{
		VBat = (float32)Baterry_mV/1000.000;
		
		if(ptr->Direction == 1)//up
		{
			ptr->Phase1_PWMDuty = (float32)(UpDirConfig.Phase1Volt) / VBat*100.00;
			
			ptr->Phase2_PWMDuty = (float32)(UpDirConfig.Phase2Volt) /VBat*100.00;
				
			ptr->Phase3_PWMDuty = (float32)(UpDirConfig.Pahse3Volt) /VBat*100.00;	

			ptr->Phase1_Pulse = UpDirConfig.IncreasePulse;
			
			ptr->Phase3_Pulse = UpDirConfig.DecreasePulse;			
		}
		else//down
		{
			ptr->Phase1_PWMDuty = (float32)(DownDirConfig.Phase1Volt) / VBat*100.00;
			
			ptr->Phase2_PWMDuty = (float32)(DownDirConfig.Phase2Volt) /VBat*100.00;
				
			ptr->Phase3_PWMDuty = (float32)(DownDirConfig.Pahse3Volt) /VBat*100.00;	
			
			ptr->Phase1_Pulse = DownDirConfig.IncreasePulse;
			
			ptr->Phase3_Pulse = DownDirConfig.DecreasePulse;
		}

			
			
		if( ptr->Phase1_PWMDuty >100.00)
		{
			ptr->Phase1_PWMDuty = 100.00;
		}
		else
		{
		}
		
		if(ptr->Phase2_PWMDuty>100.00)
		{
			ptr->Phase2_PWMDuty =100.00;
		}
		else
		{
		}

	}
	else
	{
	}

}

/***********************************************************************************************************
Description : 分辨率计算
Input	    : 起止的占空比，霍尔脉冲数目
Output		: 
Return		: 分辨率--每经过一个脉冲需要增加或者减少的占空比
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
static float32 Resolution_Set(float32 PWMDutyEnd,float32 PWMDuty_Start,uint16 HallPulseNumber)
{
	return ( (PWMDutyEnd - PWMDuty_Start)/(float32)HallPulseNumber );

}
/***********************************************************************************************************
Description : 缓起缓停的分辨率计算
Input	    : 缓起缓停的句柄
Output		: 分辨率
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
static void ResolutionCalc(Params_Handle ptr)
{
	ptr->Resolution_Increase = Resolution_Set(ptr->Phase2_PWMDuty,ptr->Phase1_PWMDuty,ptr->Phase1_Pulse);
	
	ptr->Resolution_Decrease = Resolution_Set(ptr->Phase3_PWMDuty,ptr->Phase2_PWMDuty,ptr->Phase3_Pulse);
}

/***********************************************************************************************************
Description :缓起缓停过程中，计算当前位置的占空比
Input	    : TravelCnt 表示相对值--目标点与现在的点，每一次停止都需置0
			运动开始点的占空比，分辨率
Output		: 占空比
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
 
static void DutyPattern(uint16 TravelCnt,float32 PWMDuty_Start,float32 Resolution)
{
	 Duty_Pattern = PWMDuty_Start + (float32)TravelCnt * Resolution;
}
 
/***********************************************************************************************************
Description : 运动控制前，一些参数初始化
Input	    : 
Output		: 
				实时占空比置0
				稳定调速区间的PID参数复位
				各个节点（缓起，稳定，缓停）的占空比计算
				缓起缓停的分辨率
				车窗的停止位置坐标---即运动开始前的位置坐标
				车窗停止位置所在区间
				
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
static void ParamsInit_Running(void)
 {
	 //PWM is 0
	Duty_Pattern = 0;
	
     //位置的重新计算，有利于调试
    PosParas_Init();		
     
	 //r
	ptr_up->DutyRecord = 0; 
	
	ptr_down->DutyRecord = 0; 
	 
	//PI parameters reset
	PIParams_Reset();
	
	 
	//according to voltage, set Phase1_PWMDuty  Phase2_PWMDuty  Phase3_PWMDuty
	VoltRef_PWMDuty(ptr_down);
	
	VoltRef_PWMDuty(ptr_up);
	 
	//update resolution
	ResolutionCalc(ptr_down);
	 
	ResolutionCalc(ptr_up);
	 
	 
	//初始化后才正确

	StopPosition = WindowPosition_Get(); // window stop position record
	 
	Down_Paras.ZoneFlag_StopPosition = WindowZoneGet_Down(StopPosition);
	
	Up_Paras.ZoneFlag_StopPosition = WindowZoneGet_Up(StopPosition);
		
	//

 }



/***********************************************************************************************************
Description : 手动按键激活下的 运动控制逻辑：先缓起 再PI
Input	    : 行程，初始占空比，分辨率
Output		: 占空比
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
static void Duty_ManualProcess(Params_Handle ptr)
{
		uint16 TravelPulse;
	
		//走过的行程 与停止点比较
		TravelPulse = WindowTravel_Get();
	
		//加速阶段 phase1
		if( (Duty_Pattern < (ptr->Phase2_PWMDuty) ) && (TravelPulse <= (ptr->Phase1_Pulse) ))
		{	
			DutyPattern(TravelPulse,ptr->Phase1_PWMDuty,ptr->Resolution_Increase);
		}
		else
		{
			//pid 调速阶段
			Duty_Pattern = ptr->Phase2_PWMDuty + PI_SpeedController();
			
			if(Duty_Pattern >=100)
			{
				Duty_Pattern = 100;
			}
			else
			{
			}

		}
			

	
}

/***********************************************************************************************************
Description : 自动按键激活下的 运动控制逻辑：在 zone1区间启动
Input	    : ptr---PWM结构体指针
			  ZoneFlag---现在车窗处于哪个区域
				Adder---现在车窗的位置与启动点之间的距离，行程
Output		: 占空比
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
static void Zone1_Process(Params_Handle ptr,uint8 ZoneFlag,uint16 Adder)
{
					
		//减速阶段 先判断当前是否到了此区域
		if(ZoneFlag==ZONE_3)
		{
			//先清零 再用此 计算减速的速度
			//进入减速区后， windowTravel 重新清零计数，方便计算duty
			if(ptr->DutyRecord == 0)//此刻占空比不变
			{					
				//把adder清零				
				WindowTravel_Set(0);
								
				//调速后的占空比
				ptr->DutyRecord = Duty_Pattern;
				
				//重新计算分辨率
				ptr->Resolution_Decrease = Resolution_Set(ptr->Phase3_PWMDuty,ptr->DutyRecord,ptr->Phase3_Pulse);
				
			}
			else
			{
			//减速区的占空比调节模式，		
				DutyPattern(Adder,ptr->DutyRecord,ptr->Resolution_Decrease);
			}
		}
		else if(ZoneFlag==ZONE_4) //减速区域 恒速阶段
		{
			Duty_Pattern = ptr->Phase3_PWMDuty;
		}
		else if(ZoneFlag== ZONE_SOFTSTOP)//软停区域 占空比为0 ，不加这个条件，在停止点周围会出现占空比突变
		{
			Duty_Pattern =0;
		}
		else 
		{
			//加速阶段  
			//pid 调速阶段 
			if( (Duty_Pattern < (ptr->Phase2_PWMDuty) ) && (Adder <= (ptr->Phase1_Pulse) ))
			{	
				DutyPattern(Adder,ptr->Phase1_PWMDuty,ptr->Resolution_Increase);
			}
			else
			{
				
				Duty_Pattern = ptr->Phase2_PWMDuty + PI_SpeedController();
				
				if(Duty_Pattern >=100)
					Duty_Pattern = 100;
			}			
		}
}






/***********************************************************************************************************
Description : 自动按键激活下的 运动控制逻辑：在 zone2区间启动
Input	    : ptr---PWM结构体指针
			  ZoneFlag---现在车窗处于哪个区域
			  WindowPosition --现在车窗的位置
			  Adder---现在车窗的位置与启动点之间的距离
Output		: Duty_Pattern -- 占空比
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/

static void Zone2_Process(Params_Handle ptr,uint8 ZoneFlag,uint16 WindowPosition,uint16 Adder)
{
	float32 y,y1;

	uint16 tempadder=0;	


		//从起始点，按照增加曲线的规律，占空比的变化
		y = ptr->Phase1_PWMDuty + (ptr->Resolution_Increase) * (float32)Adder;
		
		if(ZoneFlag==ZONE_2)//在zone2区域，那么车窗一定在加速，且没有到达指定的占空比
		{
			Duty_Pattern = y;
		}
		else if(ZoneFlag==ZONE_3)//在zone3区域，车窗可能到达了指定的占空比，所以要判断
		{
			//现在车窗位置与PWM保持区间段的起始绝对值坐标 之间的相对距离
			tempadder = Distance_Get(WindowPosition,ptr->Direction);
			
			//算出现在坐标对应下降曲线的占空比
			y1 = ptr->Phase3_PWMDuty - (float32)tempadder *(ptr->Resolution_Decrease);
			
			#if 1
			//达到临界点，开始下降曲线模式
			if(y >= y1)
			{
				Duty_Pattern = y1;
			}
			else//没达到临界点，还是增加
			{
				Duty_Pattern = y;
			}
			#endif		
		}
		else if(ZoneFlag== ZONE_SOFTSTOP)//软停区域 占空比为0 
		{
			Duty_Pattern =0;
		}
		else 
		{
			//zone4 区域 pwm 恒定
			Duty_Pattern =  ptr->Phase3_PWMDuty; 
		}


}


/***********************************************************************************************************
Description : 自动按键激活下的 运动控制逻辑：在 zone3区间启动
Input	    : ptr---PWM结构体指针
			  ZoneFlag---现在车窗处于哪个区域
			  Adder---现在车窗的位置与启动点之间的距离，行程
Output		: Duty_Pattern -- 占空比
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
float32 DutyWatch =0;
static void Zone3_Process(Params_Handle ptr,uint8 ZoneFlag,uint16 Adder)
{	
	if(ZoneFlag!=ZONE_4)
	{	
		//占空比下降模式		
		DutyPattern(Adder,ptr->DutyRecord,ptr->Resolution_Decrease);
		
		//direction 1 is window up; 0 is window down
		//如果车窗的坐标对应下降曲线的占空比，大于给定的值，那么按照此值给定
		if(Duty_Pattern >= 63.3 && (ptr->Direction == 1))
		{
			Duty_Pattern = 63.3 ;
		}
		else if(Duty_Pattern >= 54.3 && (ptr->Direction == 0))
		{
			Duty_Pattern = 54.3 ;
		}
			
	}
	else if(ZoneFlag== ZONE_SOFTSTOP)//软停区域 占空比为0 
	{
			Duty_Pattern =0;
	}
	else
	{
		Duty_Pattern = ptr->Phase3_PWMDuty;		
	}
	DutyWatch = Duty_Pattern;
}




/***********************************************************************************************************
Description : 自动运动的处理过程
Input	    : ptr---PWM结构体指针
Output		: Duty_Pattern -- 占空比
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
 static void Duty_AutoProcess(Params_Handle ptr)
 {
	uint16 WindowPos=0;

	uint16 Adder=0;
	
	uint8 ZoneFlag_windowpos=0;
	
	uint16 tempdis;
	 
	Adder = WindowTravel_Get();//相对值-车窗现在的位置与启动点之间的距离
	 
	WindowPos = WindowPosition_Get();//绝对值--车窗现在的位置
	 
	//判断现在的车窗位置位于哪个区域
	if(1 == ptr->Direction)
	{
		ZoneFlag_windowpos = WindowZoneGet_Up(WindowPos);	
	}
	else
	{
		ZoneFlag_windowpos = WindowZoneGet_Down(WindowPos);
	}

	//判断启动位置--绝对位置 在哪个区域 从而执行相应的操作	 
	switch( ptr->ZoneFlag_StopPosition )
	{
		//有完整的加速 调速阶段 减速 恒定阶段
		case ZONE_1 :
		
			
			Zone1_Process(ptr,ZoneFlag_windowpos,Adder);
	
		break;
		//
		
		// 加速阶段 减速阶段  恒定阶段
		case ZONE_2 : 

			Zone2_Process(ptr,ZoneFlag_windowpos,WindowPos,Adder);
			
		break;
		//
		
		//减速阶段  恒定阶段		
		case ZONE_3 :
			
			//电机不运动时，会调用函数 将DutyRecord置0
			//
			if(ptr->DutyRecord == 0)
			{
				//起始点与速度恒定区zone4的进入点坐标的距离-脉冲数，
				tempdis = Distance_Get(StopPosition,ptr->Direction);
		
				//起始点坐标对应下降曲线的占空比值
				ptr->DutyRecord = ptr->Phase3_PWMDuty - (float32)tempdis *(ptr->Resolution_Decrease);
			}
			
			Zone3_Process(ptr,ZoneFlag_windowpos,Adder);
			
		break;
		//
		
		//恒定阶段		
		case ZONE_4 :
			Duty_Pattern = ptr->Phase3_PWMDuty;
		
		break;
			
		default: break;
	}
	  
  } 
  
/***********************************************************************************************************
Description : 自动上操作
Input	    : 
Output		: 占空比
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/  
static void AutoUp(void)
{
	Duty_AutoProcess(ptr_up);		
}

/***********************************************************************************************************
Description : 手动上操作
Input	    : 
Output		: 占空比
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
static void ManualUp(void)
{
	
	Duty_ManualProcess(ptr_up);
		
}
/***********************************************************************************************************
Description : 手动下操作
Input	    : 
Output		: 占空比
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
static void ManualDown(void)
{
	Duty_ManualProcess(ptr_down);
}


/***********************************************************************************************************
Description : 自动下操作
Input	    : 
Output		: 占空比
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
static void AutoDown(void)
{
	
	Duty_AutoProcess(ptr_down);
	
	
}

/***********************************************************************************************************
Description : 电机停止运行时的参数设置
Input	    : 
Output		: 参数的设置等
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
static void MotorStop(void)
{

	HBridgePWM_Off();//shutdown pwm
	
	ParamsInit_Running(); // 运动时的参数设置
	
	WindowTravel_Set(0);//window Travel set 0
	

	
}
/***********************************************************************************************************
Description : 
Input	    : 
Output		: 
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
void testap(void)
{
	ParamsInit_Running(); // 
	
	WindowTravel_Set(0);//window Travel set 0，行程置0
	

}
/***********************************************************************************************************
Description : 运动接口函数
Input	    : 运动指令
Output		: 相应的运动状态
Return		: 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
void Motion_Control(uint8 MotorAction)
{
	 switch(MotorAction)
	 {
		 case MANUAL_UP: 
			ManualUp();//output duty
			DutySet_RealUpDir(Duty_Pattern);//act according to duty 
		 break;
		 
		 case MANUAL_DOWN: 
			ManualDown();	
			DutySet_RealDownDir(Duty_Pattern);		 
		 break;
		 
		 case AUTO_UP: 
			AutoUp();	
			DutySet_RealUpDir(Duty_Pattern);		 
		 break;
		 
		 case AUTO_DOWN: 
			AutoDown();
			DutySet_RealDownDir(Duty_Pattern);			 
		 break;
		 
		 default:   MotorStop();					break;
		 
	 }

}
float32 PWMDuty_Get(void)
{
	return Duty_Pattern;
}

#if 0
float32 PWMDuty_Set(void)
{
	return Duty_Pattern;
}
#endif

uint16 WindowStopPos_Get(void)
{
	return StopPosition;
}

