#ifndef _PIFUNC
		#define _PIFUNC
		
#include "tle_device.h"		


typedef struct
{
	float Give;
	float Kp;
	float Ki;
	float LastE;
	float PresentE;
	float OutMax;
	float OutMin;
	float Output;
	float FeedBack;
	float LastOutput;
	
}PIFunc;

typedef PIFunc* PIFunc_Handle;

//Kp=2.0, outMax=1,outmin=-1
#define PIFUNC_DEFAULTS {0,\
	1.1,\
	0.002,\
	0,\
	0,\
	1.0,\
	-1.0,\
	0,\
	0,\
	0,}

void PIFunc_Calc(PIFunc_Handle p);
	
#endif
