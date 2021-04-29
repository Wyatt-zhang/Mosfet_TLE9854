#ifndef _SPEEDSERVE
		#define _SPEEDSERVE
		
#include "tle_device.h"		


void AvrSpeedtest(void);

float SpeedController_PI(void);

void PIParams_Reset(void);

void AvrSpeedCalc(uint16 DeltaTick);

#endif
