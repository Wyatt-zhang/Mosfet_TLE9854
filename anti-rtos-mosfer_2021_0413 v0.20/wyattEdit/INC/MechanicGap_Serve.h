

#ifndef __MECHANICGAP
#define __MECHANICGAP
		
#include "tle_device.h"		

 uint16  GapCompensate(uint8 MotorDirec,uint16 WindowPos);
uint16 GapLogic(uint8 MotorDirec,uint8 InitStep,uint16 WindowPos,uint16 AvrDeltaTick);
#endif
