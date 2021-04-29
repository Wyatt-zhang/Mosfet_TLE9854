#ifndef _INTERRUPTSERVE
		#define _INTERRUPTSERVE
			
#include "Motor_Parameter.h"

typedef struct{
	
	uint8 HallStatus ;
	
	uint8 HallStatusCnt128ms ;
	
	uint8 Motion_Direction;
	
	uint16 WindowPosition ;// 车窗位置绝对值 ensure 缓起启动时，不会占空比 过大  = 0x5000

	uint16 WindowTravel ; //车窗位置相对值 相对于上一次的停止点位置 0

	uint16 HallSignalTick_New;

	uint16 HallSignalTick_Old;

	uint16 HallSignal_DeltaTick;

}HallSign;

typedef HallSign* Hall_Handler;

#define HALLDEFAULTS {NO_SPEEDSIGNAL,\
						0,\
						0,\
						0x5000,\
						0,\
						0,\
						0,\
						0}


						
		//isr related

		extern void HallSpeed_T2Call(void);
		//
		
		uint16 HallSpeedTicks_Get(void) ;
						
		void HallSpeedTicks_Reset(void);
	
		
		uint8 HallSpeedSignal_StatusGet(void);
		
		void WindowTravel_Set(uint16 Cnt);
												
		uint16 WindowTravel_Get(void);
						
		uint16 WindowPosition_Get(void);
		
		void WindowPosition_Set(uint16 Cnt);
		
		//void NoHallSpeedSignalCheck(void);
#endif
