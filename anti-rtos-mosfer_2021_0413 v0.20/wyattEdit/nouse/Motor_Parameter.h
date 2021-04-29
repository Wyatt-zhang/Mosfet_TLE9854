#ifndef _MOTORPARAMETER
		#define _MOTORPARAMETER
		
#include "tle_device.h"		


//Key status
#define  KEY_IDLE 			0  //0000(b)
#define  KEY_MANUALUP  		1  //0001
#define	 KEY_MANUALDOWN		2	//0010
#define  KEY_AUTOUP 		5	//0101
#define  KEY_AUTODOWN 		6 	//0110


#define  CLOCKWISE 			0


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

//
#define WINDOWPOSITION_ZERO_REF  0x8000

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

#endif
