#ifndef _MOTORCONTROLSERVE
#define _MOTORCONTROLSERVE

#include "tle_device.h"	


typedef struct{
	
	uint8 Phase1_VoltRef;
	
	uint8 Phase2_VoltRef;
	
	uint8 Phase3_VoltRef;
	
	uint16 Phase1_Pulse;
	
	uint16 Phase3_Pulse;
	
	float32 Phase1_PWMDuty;

	float32 Phase2_PWMDuty;

	float32 Phase3_PWMDuty;
	
	float32 Resolution_Increase;

	float32 Resolution_Decrease;
	
	uint8 Direction;  // 1 is up, 0  is down
	
	uint8 ZoneFlag_StopPosition; //  zone1 zone2 zone3 zone4
}PWM_Params;

typedef PWM_Params* Params_Handle;

#define PWM_UPDEFAULT 	{4,\
						12,\
						7,\
						200,\
						150,\
						50.0,\
						100.0,\
						40.0,\
						1,\
						1,\
						1,\
						0}
#define PWM_DOWNDEFAULT {4,\
						12,\
						3,\
						200,\
						150,\
						50.0,\
						100.0,\
						40.0,\
						1,\
						1,\
						0,\
						0,}


						


//motor action related
void Motion_Control(uint8 MotorAction);
void MotorStatus_Set(uint8 SetStatus);
uint8 MotorStatus_Get(void);
#endif


