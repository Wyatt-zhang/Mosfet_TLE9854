#ifndef _KEYSERVE
		#define _KEYSERVE
		
#include "tle_device.h"	





uint8 Key_AnalogMonitor(void);

void KeyFilter_CntSet(uint8 Cnt);

uint8 KeyStatus_Get(void);
uint8 KeyStatus_Set(uint8 KeyStatus);

#endif




