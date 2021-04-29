
#include "Motor_Parameter.h"
/*infineon include*/
#include "tle_device.h"	


#include "Interrupt_Serve.h"

/*rtos include*/
#include "rtthread.h"

/*�ź������������ж����ݴ�����*/
extern struct rt_semaphore sem_hall;

typedef struct{
	
	uint8 HallStatus ;				/***********�����ٶ��źŵĴ���״̬***************/
	
	uint8 HallStatusCnt;			/*************ͳ���ٶȻ����ź�û���ֵĴ���*************/
	
	uint8 HallStatusCntLimit;		/*************�ٶȻ����ź�û���ֵĴ���������ֵ*************/
	
	uint8 Motion_Direction;			/*************�����˶��ķ���*************/
	
	uint16 WindowPosition ;			/*********����λ�þ���ֵ ensure ��������ʱ������ռ�ձ� ����  = 0x5000*****************/

	uint16 WindowTravel ; 			/***********����λ�����ֵ-�������һ�ε�ֹͣ��λ�� ***************/

	uint16 HallSignalTick_New; 		/*************��ǰ�ٶȻ��������ʱ��*************/

	uint16 HallSignalTick_Old; 		/***************��һ���ٶȻ��������ʱ��***********/

	uint16 HallSignal_DeltaTick;	/*************�����ٶȻ��������ʱ���ֵ*************/
	
	uint16 AvrDeltaTick;			/*************�ٶȻ��������ʱ���ֵ��ƽ��ֵ*************/

}HallSignal;

typedef HallSignal* Hall_Handler;

#define HALLDEFAULTS {NO_SPEEDSIGNAL,\
						0,\
						10u,\
						0,\
						0x5000,\
						0,\
						0,\
						0,\
						0,\
						0}


HallSignal Hall = HALLDEFAULTS;





/*
**����ƽ��ֵ �˳��Ż������ȴ��������
*/
static uint8 Num =0;

static uint16 _Array[4]={0};

static uint8 initdatacnt =0;


//
static uint8 initdatacnt1 =0;

uint16 tteqt1 = 0;

static void AvrCalc(uint16 DeltaTick)
{

	_Array[Num] = DeltaTick /4; //
		
	//��Ϊ���תһȦ��4��pulse��������ʱǰ3��deltatick ������AVR
	//����ǰ24�� ���ƻ�еgap�������ٶȲ��� ��������
	if( ++initdatacnt>28 )	
	{
		initdatacnt = 29;
		
		Hall.AvrDeltaTick = _Array[0] + _Array[1] + _Array[2] + _Array[3] ;		
	}
	
	//test
	if(++initdatacnt1>3)
	{
		initdatacnt1 = 29;
		tteqt1 = _Array[0] + _Array[1] + _Array[2] + _Array[3] ;
	}
	//test end 
	
	if(++Num >= 4)
	{
		
		Num = 0;
	}
	else
	{
	}

}




/*
********isr callback functions***

interrupt serve function :
	1)HallSpeed_T2Call  GPT1 interrupt channel, priority 3 
	2)Sys_1msCall--1ms,priority is 3--default value
***********************************
*/


/*
	T3 is 2.5Mhz- 0.8us, 16 bit register, every count is 0.8us, 0xFFFF is 52.4 ms,for hall speed signal capture

*/

void HallSpeed_T2Call(void)
{
	rt_interrupt_enter();
	
	//	
	Hall.WindowTravel++;
	
	
	//send semaphore to start thread
	rt_sem_release(&sem_hall);
	
	//
	rt_interrupt_leave();	
}

/*�г̲����Ļ�ȡ�����ֵ*/
uint16 WindowTravel_Get(void)
{
	return Hall.WindowTravel;
}

void WindowTravel_Set(uint16 Cnt)
{
	Hall.WindowTravel = Cnt;
}


/*��������ֵ�Ļ�ȡ������ֵ*/
uint16 WindowPosition_Get(void)
{
	return Hall.WindowPosition;
}

void WindowPosition_Set(uint16 Cnt)
{
	Hall.WindowPosition = Cnt;
}

/*�����ٶ��йػ�ȡ*/
uint16 HallSpeedTicks_Get(void)
{
	return Hall.AvrDeltaTick;
}
static void HallSpeedTicks_Reset(void)
{
	Hall.AvrDeltaTick =0;
	
	Hall.HallSignalTick_New = 0;
	
	Hall.HallSignalTick_Old = 0;
	
	Hall.HallSignal_DeltaTick = 0;
	
	initdatacnt = 0 ;
	
	initdatacnt1 =0;
}



/*�����жϵװ����ݴ���*/
void ISR_HallProcess(void)
{
	#if 1
	//Hall direction input signal P0.1,hardware related
	Hall.Motion_Direction= PORT_P01_Get(); // 
	
	
	
	// Motion_Direction is 1 , window down direction ,++,HALLDIR; 0-window up direction
	if(Hall.Motion_Direction) //1
	{	
		#if HALLDIR
			Hall.WindowPosition++;
		#else
			Hall.WindowPosition--;
		#endif
	}
	else//0
	{
		#if HALLDIR
			Hall.WindowPosition--;
		#else
			Hall.WindowPosition++;
		#endif	
	}
		
	#endif
	
	Hall.HallStatus = SPEEDSIGNAL;
	
	Hall.HallStatusCnt = 0;	
	
	// get the value of T2 register, it is from T3 register
	Hall.HallSignalTick_New = GPT12E_T2_Value_Get();
	
	Hall.HallSignal_DeltaTick = Hall.HallSignalTick_New - Hall.HallSignalTick_Old;

	Hall.HallSignalTick_Old = Hall.HallSignalTick_New;
	//
	
	AvrCalc(Hall.HallSignal_DeltaTick);
	
}

/*
**
**   hall signal 20ms���ڵļ�⣬���20ms��hall ���򲻴���hall speed signal
*/

/***********************************************************************************************************
Description : ����2ms������һ��hall signal 20ms���ڵļ�⣬���20ms��hall ���򲻴���hall speed signal
Input	    : /
Output		: �����źŴ��ڵ�״̬
Return		: /
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/

static void HallMonitor(void)
{
	if( ++(Hall.HallStatusCnt) > Hall.HallStatusCntLimit)
	{
		Hall.HallStatus= NO_SPEEDSIGNAL;
		
		Hall.HallStatusCnt = 0;
		
		HallSpeedTicks_Reset();
	}
	else
	{
	}

}
/***********************************************************************************************************
Description : �����ź��Ƿ����
Input	    : /
Output		: 
Return		: �����ź��Ƿ����
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/
uint8 HallSpeedSignal_StatusGet(void)
{	
	HallMonitor();
	
	return Hall.HallStatus;
}
