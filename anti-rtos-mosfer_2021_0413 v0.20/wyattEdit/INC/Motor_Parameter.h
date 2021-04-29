#ifndef _MOTORPARAMETER
		#define _MOTORPARAMETER
		
#include "types.h"	

//事件集的使用
#define EVENT_UNDERVOLT  (1<<0)
#define EVENT_OVERVOLT   (1<<1)


#define  EVENTHAPPEND		1
#define  EVENTNOHAPPEND		0

//Key status
#define  KEY_IDLE 			0   //0000(b)
#define  KEY_MANUALUP  		1   //0001
#define	 KEY_MANUALDOWN		2	//0010
#define  KEY_AUTOUP 		5	//0101
#define  KEY_AUTODOWN 		6 	//0110

//relationship of real window up and down with pre-setting directions
//0 is opposite 1 is same
/*
**P型马达设定
*/
#define  COLOCKWISE 		1

#define  HALLDIR			1

//hall signal
#define	 NO_SPEEDSIGNAL 	0
#define	 SPEEDSIGNAL		1
		

//Motor Stalling
#define  NO_STALLING 		1
#define  UPSTALLING			2
#define	 DOWNSTALLING		3

//Motor Action
#define  STOP 				0
#define  MANUAL_UP 			1		
#define	 MANUAL_DOWN		2
#define  AUTO_UP 			5
#define	 AUTO_DOWN 			6

//初始化后的坐标系0 参考点 绝对值 -设定值
#define WINDOWPOSITION_ZERO_REF  0x8000

//车窗的的长度 实际测量值为42厘米  霍尔脉冲数为 1180 个 一个脉冲的距离为 420/1180 mm 
//4mm 大概 12个脉冲 200mm 大概是600个脉冲 150mm 为 450 个脉冲
#define VIHECLEWINDOWLENGTH  42 
#define APREVERSEPULSE  	450u

#define APZONETOP  25
#define APZONEBOTTOM 600



//Pisition zone
#define  ZONE_1				1
#define  ZONE_2 			2		
#define	 ZONE_3				3
#define  ZONE_4 			4
#define	 ZONE_SOFTSTOP 		5

//Init Step
#define  INIT_STEP0			0
#define  INIT_STEP1			1
#define  INIT_STEP2			2		
#define	 INIT_STEP3			3



typedef struct{
	uint16  IncreasePulse;		/* 缓起阶段的距离  */
	uint16  DecreasePulse;		/* 下降阶段的距离  */
	uint8   ConstantPulse;		/* 速度保持恒定阶段的距离  */
	uint8   SoftStopPulse;		/*软停点距离上限或者下限的距离--霍尔脉冲数表示*/
	uint8   Phase1Volt;  		/* 缓起的初始电压  */
	uint8   Phase2Volt;			/* 进入PI调速区的初始电压  */
	uint8   Pahse3Volt;			/* 下降区的最终电压，也是速度恒定区的电压  */
}SpeedControl;

// 初始化后，绝对值坐标才是正确的,有利于自动按键下的运动控制的计算
typedef struct{
	
	uint16 SoftStopPosition;	/*上下软停点坐标 绝对值*/
	
	uint16 Position_Zone4;		/*缓停区间过后，进入zone4区间段的绝对值坐标*/
	
	uint16 Position_Zone3;		/*进入zone3缓停区的绝对值坐标*/
	
	uint16 Position_Zone2;		/*进入zone3区间绝对值坐标---如果车窗从这个位置启动可以满足完整的加速过程，减速过程，然后是PWM保持过程，最后软停 */

}Pos_Mark;


#define MAX(x,y)    ((x>=y)?x:y)
#define MIN(x,y)    ((x<=y)?x:y)
#define MINUS(x,y)    ((x>y)?((x)-(y)):0)
#endif
