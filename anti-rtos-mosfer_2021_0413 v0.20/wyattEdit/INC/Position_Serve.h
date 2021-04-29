#ifndef _POSITIONSERVE
		#define _POSITIONSERVE
		
		
#include "types.h"	
void PosParas_Init(void);	

uint8 WindowZoneGet_Up(const uint16 WindowPosition); 

uint8 WindowZoneGet_Down(const uint16 WindowPosition); 

void InitStepSet(uint8 SetFLag);	


uint8 SoftStopInit(uint8 StallingStatus);


uint16 Distance_Get(uint16 WindowPosition,uint8 Direction);


#endif
