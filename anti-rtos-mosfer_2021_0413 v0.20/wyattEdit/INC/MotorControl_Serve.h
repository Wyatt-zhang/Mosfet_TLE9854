#ifndef _MOTORCONTROLSERVE
#define _MOTORCONTROLSERVE

#include "tle_device.h"	


					


//motor action related
void Motion_Control(uint8 MotorAction);
						
float32 PWMDuty_Get(void);

void testap(void);
uint16 WindowStopPos_Get(void);
#endif


