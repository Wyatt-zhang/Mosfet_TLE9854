#ifndef _MYADCSERVE
#define _MYADCSERVE

#include "types.h"


typedef struct {
  
    uint8 KeyStatus;
    
    
    sint16 TemperatureBDRV;
    sint16 TemperatureChip;
    
}ADCGet;

extern ADCGet StADCValue;

uint8 AdcKeyMonitor(void);
void AdcTempMonitor(void);
#endif

