#ifndef _POSITIONSERVE
		#define _POSITIONSERVE
		
		
		
#include "tle_device.h"	

//��ʼ���������ϵ0 �ο��� ����ֵ -�趨ֵ
#define  WINDOWPOSITIONZERO  0x8000

typedef struct{

	
	uint16 SoftStopDistance; // ����ͣ��������ԭ��ĵľ���    ���ֵ -�趨ֵ

	
	uint16 SpeedIncreaseDistance ; // �ٶ���������ľ���  up���� ���ֵ -�趨ֵ
	

	
	uint16 SpeedDecreaseDistance; // ��ͣ�����ٶ��½������ֵľ���  up ����   ���ֵ -�趨ֵ
	


	uint16 SpeedHoldDistance;// ��ͣ���ٶȱ��ֺ㶨�ľ��� ���ֵ -�趨ֵ
		

	
	uint16 SoftStopPosition; // ��ʼ��������ͣ������ ����ֵ
	

	
}Pos;
typedef Pos* Pos_Handle;

typedef struct{
	uint16 Position1;// ��ʼ�������� ����ֵ
	
	uint16 Position2;// ��ʼ�������� ����ֵ
	
	uint16 Position3;// ��ʼ�������� ����ֵ

}Pos_Mark;

typedef Pos_Mark* Mark_Handle;

#define MARK_DEFAULTS 		{0,\
							 0,\
							 0}

#define UPPOS_DEFAULTS  	{0x24,\
							 200,\
							 150,\
							 50,\
							 0,}
							

#define DOWNPOS_DEFAULTS  	{0x24,\
							 200,\
							 150,\
							 50,\
							 0,}
							

							
uint8 WindowZoneGet_Up(const uint16 WindowPosition); 
							
uint8 WindowZoneGet_Down(const uint16 WindowPosition); 
							
uint8 SoftStopInit(uint8 StallingStatus);

uint16 DownSoftStopPos_Get(void);

uint16 UpSoftStopPos_Get(void);

uint16 Distance_Get(uint16 WindowPosition,uint8 Direction);
							
#endif
