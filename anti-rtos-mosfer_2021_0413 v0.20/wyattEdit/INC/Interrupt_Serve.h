#ifndef _INTERRUPTSERVE
		#define _INTERRUPTSERVE
			


#include "types.h"

//���������жϺ��������ⲿ��������
//�������Ķ�������infineon config������õ�
extern void HallSpeed_T2Call(void);



						

						
/*״̬�ӿں���������������ģ�����*/		

//�����жϴ�����Ҫ���������						
void ISR_HallProcess(void);

//�����ٶȻ���������ƽ��tickֵ
uint16 HallSpeedTicks_Get(void) ;

//�ٶȻ��������źŵ�״̬��ȡ
uint8 HallSpeedSignal_StatusGet(void);

//�ٶȻ�������200ms�Ƿ���ڵļ��
//void HallMonitor(void);

//�����г�--��������ʾ���趨
void WindowTravel_Set(uint16 Cnt);

//�����г�--��������ʾ����ȡ												
uint16 WindowTravel_Get(void);

//����������ֵ��ȡ---������������ʾ
uint16 WindowPosition_Get(void);

//����������ֵ����---������������ʾ
void WindowPosition_Set(uint16 Cnt);
		
#endif
