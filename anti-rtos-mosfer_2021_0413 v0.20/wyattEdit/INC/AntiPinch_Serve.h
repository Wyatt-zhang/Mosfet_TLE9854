#ifndef _ANTIPINCHSERVE
		#define _ANTIPINCHSERVE
		

#include "tle_device.h"	

#define APSPEEDTEST   	1
#define APCURRENTTEST 	1

void AntiPich(void);

uint8 Get_PinchStatus(void);

void Set_PinchFlag(void);

#endif

