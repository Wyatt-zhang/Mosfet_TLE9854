#ifndef _KEYSERVE
		#define _KEYSERVE

//infineon include header
#include "types.h"




//���ݹ���鶨�壬��ģ�ⰸ�����������ж����ڵİ����߼�״̬
uint8 Key_AnalogMonitor(void);



//��ȡϵͳ�����µİ������߼�״̬����������簴��������״̬
uint8 KeyStatus_Get(void);

//�������ڵİ���״̬
uint8 KeyStatus_Set(uint8 KeyStatus);



#endif




