#ifndef _MOTORPARAMETER
		#define _MOTORPARAMETER
		
#include "types.h"	

//�¼�����ʹ��
#define EVENT_UNDERVOLT  (1<<0)
#define EVENT_OVERVOLT   (1<<1)


#define  EVENTHAPPEND		1
#define  EVENTNOHAPPEND		0

//Key status
#define  KEY_IDLE 			0   //0000(b)
#define  KEY_MANUALUP  		1   //0001
#define	 KEY_MANUALDOWN		2	//0010
#define  KEY_AUTOUP 		5	//0101
#define  KEY_AUTODOWN 		6 	//0110

//relationship of real window up and down with pre-setting directions
//0 is opposite 1 is same
/*
**P������趨
*/
#define  COLOCKWISE 		1

#define  HALLDIR			1

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

//��ʼ���������ϵ0 �ο��� ����ֵ -�趨ֵ
#define WINDOWPOSITION_ZERO_REF  0x8000

//�����ĵĳ��� ʵ�ʲ���ֵΪ42����  ����������Ϊ 1180 �� һ������ľ���Ϊ 420/1180 mm 
//4mm ��� 12������ 200mm �����600������ 150mm Ϊ 450 ������
#define VIHECLEWINDOWLENGTH  42 
#define APREVERSEPULSE  	450u

#define APZONETOP  25
#define APZONEBOTTOM 600



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



typedef struct{
	uint16  IncreasePulse;		/* ����׶εľ���  */
	uint16  DecreasePulse;		/* �½��׶εľ���  */
	uint8   ConstantPulse;		/* �ٶȱ��ֺ㶨�׶εľ���  */
	uint8   SoftStopPulse;		/*��ͣ��������޻������޵ľ���--������������ʾ*/
	uint8   Phase1Volt;  		/* ����ĳ�ʼ��ѹ  */
	uint8   Phase2Volt;			/* ����PI�������ĳ�ʼ��ѹ  */
	uint8   Pahse3Volt;			/* �½��������յ�ѹ��Ҳ���ٶȺ㶨���ĵ�ѹ  */
}SpeedControl;

// ��ʼ���󣬾���ֵ���������ȷ��,�������Զ������µ��˶����Ƶļ���
typedef struct{
	
	uint16 SoftStopPosition;	/*������ͣ������ ����ֵ*/
	
	uint16 Position_Zone4;		/*��ͣ������󣬽���zone4����εľ���ֵ����*/
	
	uint16 Position_Zone3;		/*����zone3��ͣ���ľ���ֵ����*/
	
	uint16 Position_Zone2;		/*����zone3�������ֵ����---������������λ�������������������ļ��ٹ��̣����ٹ��̣�Ȼ����PWM���ֹ��̣������ͣ */

}Pos_Mark;


#define MAX(x,y)    ((x>=y)?x:y)
#define MIN(x,y)    ((x<=y)?x:y)
#define MINUS(x,y)    ((x>y)?((x)-(y)):0)
#endif
