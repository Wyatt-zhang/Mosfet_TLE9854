#ifndef _KEYSERVE
		#define _KEYSERVE

//infineon include header
#include "types.h"




//根据规格书定义，从模拟案件输入量，判断现在的按键逻辑状态
uint8 Key_AnalogMonitor(void);



//获取系统中最新的按键的逻辑状态，并不是外界按键的输入状态
uint8 KeyStatus_Get(void);

//设置现在的按键状态
uint8 KeyStatus_Set(uint8 KeyStatus);



#endif




