#ifndef _POSITIONSERVE
		#define _POSITIONSERVE
		
		
		
#include "tle_device.h"	

//初始化后的坐标系0 参考点 绝对值 -设定值
#define  WINDOWPOSITIONZERO  0x8000

typedef struct{

	
	uint16 SoftStopDistance; // 上软停点离坐标原点的的距离    相对值 -设定值

	
	uint16 SpeedIncreaseDistance ; // 速度上升区间的距离  up方向 相对值 -设定值
	

	
	uint16 SpeedDecreaseDistance; // 缓停区内速度下降到保持的距离  up 方向   相对值 -设定值
	


	uint16 SpeedHoldDistance;// 缓停区速度保持恒定的距离 相对值 -设定值
		

	
	uint16 SoftStopPosition; // 初始化后，上软停点坐标 绝对值
	

	
}Pos;
typedef Pos* Pos_Handle;

typedef struct{
	uint16 Position1;// 初始化后，坐标 绝对值
	
	uint16 Position2;// 初始化后，坐标 绝对值
	
	uint16 Position3;// 初始化后，坐标 绝对值

}Pos_Mark;

typedef Pos_Mark* Mark_Handle;

#define MARK_DEFAULTS 		{0,\
							 0,\
							 0}

#define UPPOS_DEFAULTS  	{0x24,\
							 200,\
							 150,\
							 50,\
							 0,}
							

#define DOWNPOS_DEFAULTS  	{0x24,\
							 200,\
							 150,\
							 50,\
							 0,}
							

							
uint8 WindowZoneGet_Up(const uint16 WindowPosition); 
							
uint8 WindowZoneGet_Down(const uint16 WindowPosition); 
							
uint8 SoftStopInit(uint8 StallingStatus);

uint16 DownSoftStopPos_Get(void);

uint16 UpSoftStopPos_Get(void);

uint16 Distance_Get(uint16 WindowPosition,uint8 Direction);
							
#endif
