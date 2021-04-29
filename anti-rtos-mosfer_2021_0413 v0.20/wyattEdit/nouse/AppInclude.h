#ifndef _APPINCLUDE
		#define _APPINCLUDE
		


#include "stdlib.h"

#include "Motor_Parameter.h"

#include "Key_Serve.h"

#include "PWM_Serve.h"

#include "Interrupt_Serve.h"

#include "Position_Serve.h"

#include "MotorStalling_Serve.h"

#include "Speed_Serve.h"

#include "PIFunc.h"

#include "MotorControl_Serve.h"


uint8 MotorCommnads_Update(uint8 Key_Status,uint8 SoftStopInitFlag,uint8 SoftStopFlag,uint8 MotorStalling);

void HardwareInit(void);

#endif
