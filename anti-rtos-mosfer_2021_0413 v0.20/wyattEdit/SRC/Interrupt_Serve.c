
#include "Motor_Parameter.h"
/*infineon include*/
#include "tle_device.h"	


#include "Interrupt_Serve.h"

/*rtos include*/
#include "rtthread.h"

/*信号量用来唤醒中断数据处理函数*/
extern struct rt_semaphore sem_hall;

typedef struct{
	
	uint8 HallStatus ;				/***********霍尔速度信号的存在状态***************/
	
	uint8 HallStatusCnt;			/*************统计速度霍尔信号没出现的次数*************/
	
	uint8 HallStatusCntLimit;		/*************速度霍尔信号没出现的次数的上限值*************/
	
	uint8 Motion_Direction;			/*************车窗运动的方向*************/
	
	uint16 WindowPosition ;			/*********车窗位置绝对值 ensure 缓起启动时，不会占空比 过大  = 0x5000*****************/

	uint16 WindowTravel ; 			/***********车窗位置相对值-相对于上一次的停止点位置 ***************/

	uint16 HallSignalTick_New; 		/*************当前速度霍尔脉冲的时间*************/

	uint16 HallSignalTick_Old; 		/***************上一次速度霍尔脉冲的时间***********/

	uint16 HallSignal_DeltaTick;	/*************两次速度霍尔脉冲的时间差值*************/
	
	uint16 AvrDeltaTick;			/*************速度霍尔脉冲的时间差值的平均值*************/

}HallSignal;

typedef HallSignal* Hall_Handler;

#define HALLDEFAULTS {NO_SPEEDSIGNAL,\
						0,\
						10u,\
						0,\
						0x5000,\
						0,\
						0,\
						0,\
						0,\
						0}


HallSignal Hall = HALLDEFAULTS;





/*
**计算平均值 滤除磁环不均匀带来的误差
*/
static uint8 Num =0;

static uint16 _Array[4]={0};

static uint8 initdatacnt =0;


//
static uint8 initdatacnt1 =0;

uint16 tteqt1 = 0;

static void AvrCalc(uint16 DeltaTick)
{

	_Array[Num] = DeltaTick /4; //
		
	//因为电机转一圈有4个pulse，刚启动时前3个deltatick 不计算AVR
	//丢掉前24个 改善机械gap带来的速度波动 造成误防夹
	if( ++initdatacnt>28 )	
	{
		initdatacnt = 29;
		
		Hall.AvrDeltaTick = _Array[0] + _Array[1] + _Array[2] + _Array[3] ;		
	}
	
	//test
	if(++initdatacnt1>3)
	{
		initdatacnt1 = 29;
		tteqt1 = _Array[0] + _Array[1] + _Array[2] + _Array[3] ;
	}
	//test end 
	
	if(++Num >= 4)
	{
		
		Num = 0;
	}
	else
	{
	}

}




/*
********isr callback functions***

interrupt serve function :
	1)HallSpeed_T2Call  GPT1 interrupt channel, priority 3 
	2)Sys_1msCall--1ms,priority is 3--default value
***********************************
*/


/*
	T3 is 2.5Mhz- 0.8us, 16 bit register, every count is 0.8us, 0xFFFF is 52.4 ms,for hall speed signal capture

*/

void HallSpeed_T2Call(void)
{
	rt_interrupt_enter();
	
	//	
	Hall.WindowTravel++;
	
	
	//send semaphore to start thread
	rt_sem_release(&sem_hall);
	
	//
	rt_interrupt_leave();	
}

/*行程参数的获取，相对值*/
uint16 WindowTravel_Get(void)
{
	return Hall.WindowTravel;
}

void WindowTravel_Set(uint16 Cnt)
{
	Hall.WindowTravel = Cnt;
}


/*车窗坐标值的获取，绝对值*/
uint16 WindowPosition_Get(void)
{
	return Hall.WindowPosition;
}

void WindowPosition_Set(uint16 Cnt)
{
	Hall.WindowPosition = Cnt;
}

/*车窗速度有关获取*/
uint16 HallSpeedTicks_Get(void)
{
	return Hall.AvrDeltaTick;
}
static void HallSpeedTicks_Reset(void)
{
	Hall.AvrDeltaTick =0;
	
	Hall.HallSignalTick_New = 0;
	
	Hall.HallSignalTick_Old = 0;
	
	Hall.HallSignal_DeltaTick = 0;
	
	initdatacnt = 0 ;
	
	initdatacnt1 =0;
}



/*霍尔中断底半数据处理*/
void ISR_HallProcess(void)
{
	#if 1
	//Hall direction input signal P0.1,hardware related
	Hall.Motion_Direction= PORT_P01_Get(); // 
	
	
	
	// Motion_Direction is 1 , window down direction ,++,HALLDIR; 0-window up direction
	if(Hall.Motion_Direction) //1
	{	
		#if HALLDIR
			Hall.WindowPosition++;
		#else
			Hall.WindowPosition--;
		#endif
	}
	else//0
	{
		#if HALLDIR
			Hall.WindowPosition--;
		#else
			Hall.WindowPosition++;
		#endif	
	}
		
	#endif
	
	Hall.HallStatus = SPEEDSIGNAL;
	
	Hall.HallStatusCnt = 0;	
	
	// get the value of T2 register, it is from T3 register
	Hall.HallSignalTick_New = GPT12E_T2_Value_Get();
	
	Hall.HallSignal_DeltaTick = Hall.HallSignalTick_New - Hall.HallSignalTick_Old;

	Hall.HallSignalTick_Old = Hall.HallSignalTick_New;
	//
	
	AvrCalc(Hall.HallSignal_DeltaTick);
	
}

/*
**
**   hall signal 20ms存在的检测，如果20ms无hall ，则不存在hall speed signal
*/

/***********************************************************************************************************
Description : 函数2ms倍调用一次hall signal 20ms存在的检测，如果20ms无hall ，则不存在hall speed signal
Input	    : /
Output		: 霍尔信号存在的状态
Return		: /
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/

static void HallMonitor(void)
{
	if( ++(Hall.HallStatusCnt) > Hall.HallStatusCntLimit)
	{
		Hall.HallStatus= NO_SPEEDSIGNAL;
		
		Hall.HallStatusCnt = 0;
		
		HallSpeedTicks_Reset();
	}
	else
	{
	}

}
/***********************************************************************************************************
Description : 霍尔信号是否存在
Input	    : /
Output		: 
Return		: 霍尔信号是否存在
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
uint8 HallSpeedSignal_StatusGet(void)
{	
	HallMonitor();
	
	return Hall.HallStatus;
}
