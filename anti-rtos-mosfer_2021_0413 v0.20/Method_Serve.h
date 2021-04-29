#ifndef __METHODSERVE
		#define __METHODSERVE
		



#include "types.h"


typedef struct{
    

     uint8 SignalCnt;                       /*��������*/
     uint8 SignalCntLimit ;                 /*��������ֵ*/
    
    
     uint8 OldSignal ;                       /*��һ���ź�*/
     uint8 OutputSignal ;                   /*����ź�*/

}CalcMethod;

//typedef CalcMethod *StCalcPTR;

/*�ⲿ��������ת������*/
extern CalcMethod StMotorStallFilter;
extern CalcMethod StKeyFilter;


void MethodCountFilter(uint8 InputSignal,CalcMethod *ptr);

uint16 MethodMiddleFilter(uint16 a[],uint8 Num);

#endif
