#ifndef __METHODSERVE
		#define __METHODSERVE
		



#include "types.h"


typedef struct{
    

     uint8 SignalCnt;                       /*计数变量*/
     uint8 SignalCntLimit ;                 /*计数上限值*/
    
    
     uint8 OldSignal ;                       /*上一个信号*/
     uint8 OutputSignal ;                   /*输出信号*/

}CalcMethod;

//typedef CalcMethod *StCalcPTR;

/*外部声明，堵转，按键*/
extern CalcMethod StMotorStallFilter;
extern CalcMethod StKeyFilter;


void MethodCountFilter(uint8 InputSignal,CalcMethod *ptr);

uint16 MethodMiddleFilter(uint16 a[],uint8 Num);

#endif
