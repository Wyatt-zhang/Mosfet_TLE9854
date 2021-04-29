#ifndef _INTERRUPTSERVE
		#define _INTERRUPTSERVE
			


#include "types.h"

//霍尔脉冲中断函数，的外部定义声明
//函数名的定义是用infineon config软件配置的
extern void HallSpeed_T2Call(void);



						

						
/*状态接口函数，供其它功能模块调用*/		

//霍尔中断触发后，要处理的任务						
void ISR_HallProcess(void);

//两个速度霍尔脉冲间的平均tick值
uint16 HallSpeedTicks_Get(void) ;

//速度霍尔脉冲信号的状态获取
uint8 HallSpeedSignal_StatusGet(void);

//速度霍尔脉冲200ms是否存在的检测
//void HallMonitor(void);

//车窗行程--脉冲数表示，设定
void WindowTravel_Set(uint16 Cnt);

//车窗行程--脉冲数表示，获取												
uint16 WindowTravel_Get(void);

//车窗的坐标值获取---霍尔脉冲数表示
uint16 WindowPosition_Get(void);

//车窗的坐标值设置---霍尔脉冲数表示
void WindowPosition_Set(uint16 Cnt);
		
#endif
