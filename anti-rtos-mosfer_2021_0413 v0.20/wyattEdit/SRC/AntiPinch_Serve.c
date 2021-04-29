#include "Motor_Parameter.h"
#include "AntiPinch_Serve.h"
#include "Speed_Serve.h"
#include "Interrupt_Serve.h"
#include "AppLogic.h"

#include "MotorControl_Serve.h"
typedef struct{
	uint8 FilterValueLow;			/*no used for current*/
	
	#if 0
	uint8 FilterValueMid;			/*no used*/
	uint8 FilterValueHigh;			/*no used*/
	
	uint8 CntLow;					/*no used*/
	uint8 CntMid;					/*no used*/
	uint8 CntHigh;					/*no used*/
	
	uint8 CntLowValueLimit;			/*no used*/
	uint8 CntMidValueLimit;			/*no used*/
	uint8 CntHighValueLimit;		/*no used*/
	#endif 
	
	uint16 ValueLimit;				/* sum value of speed error or current error for calculating pinch event*/
	
	uint8 APFlag;					/* speed or current pinch event, 1 is occured */
	
	uint8 UPcnt; 	 				/* record data number*/
	uint8 UPcntValueLimit; 			/*  �����Ч���ݵ���Ŀ*/
	
	uint8 WindowLength;         	/* how many data of number for calculating pinch event*/
}APConfig;

typedef APConfig*  APConfigHandler;

#define APCURRENT_SUMLIMIT  155
#define APSPEED_SUMLIMIT  	400

#define APCURRENTWINDOW  20
#define APSPEEDWINDOW	 48

#define CURRENTPARAMS  {0,\
						APCURRENT_SUMLIMIT,\
						0,\
						0,\
						18,\
						APCURRENTWINDOW}

#define SPEEDPARAMS    {4,\
						APSPEED_SUMLIMIT,\
						0,\
						0,\
						43,\
						APSPEEDWINDOW}


/*structure variable*/
APConfig StAPSpeed = SPEEDPARAMS ;
						
APConfig StAPCurrent = CURRENTPARAMS ;


/*Pinch event��1 is occured,0 is not*/						
uint8 PinchFlag = 0;
						


#if APSPEEDTEST
	uint16 ApSpeedSum =0;
#endif						

/***********************************************************************************************************
Description : Judge pinch event from speed data
Input	    : 48 latest  data of  speed array
Output		: 
Return		: Speed pinchflag 
History		: Wyatt zhang(2020/12/29)
***************************************************************************************************************/						
static uint8 APSpeedMonitor(void)
{		
	uint16 speedError = PopiFarrayData();
	
	uint8 tempCnt = StAPSpeed.WindowLength;
	
	uint16 speedErrorSum =0;
	
	/**/
	StAPSpeed.UPcnt = 0;
	
	/*process speed error data  */
	for(;tempCnt>0;tempCnt--)
	{
		/*lowest level value 4,if reached over,record the count and sum of speed error*/
		if( speedError <= StAPSpeed.FilterValueLow ) 
		{

		}
		else 
		{	
			(StAPSpeed.UPcnt)++;
			
			speedErrorSum += speedError;			
		}
		
		speedError = PopiFarrayData();
	}	
	
	/* judge from the conditions*/
	if ( (StAPSpeed.UPcnt > StAPSpeed.UPcntValueLimit) &&  
         (speedErrorSum> StAPSpeed.ValueLimit)     )
    {
		StAPSpeed.APFlag = EVENTHAPPEND;
    }
    else
    {
		StAPSpeed.APFlag = EVENTNOHAPPEND;
    }

	/*for debuging */	
	#if  APSPEEDTEST
		ApSpeedSum = speedErrorSum;
	#endif
	
	return (StAPSpeed.APFlag);
}










#if APCURRENTTEST
		
	uint16 sumI = 0;
#endif						


/***********************************************************************************************************
Description : judge pinch event from current error data 
			  current is growing when pinch event happened.
Input	    : 20 latest data of current array
Output		: 
Return		: current pinchflag 
History		: wyatt zhang(2020/12/29)
***************************************************************************************************************/	
static uint8 APCurrentMonitor(void)
{
	//�ȵ���һ�����ϵ�����
	uint16 OldPos = PopCurrentData(); 
	
	//ȡ���µ�����
	uint16 ptr_cur = PopCurrentData();
	
	uint8 cnt = StAPCurrent.WindowLength;
	
	uint16 currentErrorSum = 0;
	
	StAPCurrent.UPcnt = 0;
	
	for(;cnt>0;cnt--)
	{
		if( ptr_cur > OldPos)
		{
			currentErrorSum += (ptr_cur - OldPos);	
				
			(StAPCurrent.UPcnt)++;
		}
		else
		{
		}
		
		ptr_cur = PopCurrentData();
		
	}	
	
	/**/
    if ( (StAPCurrent.UPcnt > StAPCurrent.UPcntValueLimit) && 
         ( currentErrorSum > StAPCurrent.ValueLimit)     )
    {
			StAPCurrent.APFlag = EVENTHAPPEND;
    }
    else
    {
			StAPCurrent.APFlag = EVENTNOHAPPEND;
    }	
	
	#if APCURRENTTEST
		sumI = currentErrorSum;
	#endif	
	
	return (StAPCurrent.APFlag);
}



/***********************************************************************************************************
Description : check if window position is located at anti-pinch area
Input	    : currrent WindowPosition-- absolute value
Output		: 
Return		: anti-pinch area flag,1 is loacted at this area
History		: wyatt zhang(2020/12/30)
***************************************************************************************************************/
static uint8 AntiZoneCheck(uint16 WindowPosition)
{
	uint8 flag = 0;
	
	if( WindowPosition>=(WINDOWPOSITION_ZERO_REF+APZONETOP) &&
		 WindowPosition<=(WINDOWPOSITION_ZERO_REF+APZONEBOTTOM))
	{
		flag = 1 ;
	}
	
	return flag;
}




/***********************************************************************************************************
Description : judge if pinch event is occured
				
Input	    : currrent WindowPosition-- absolute value
Output		: 
Return		: 
History		: wyatt zhang(2020/12/30)
***************************************************************************************************************/

/* input parameters from other function block*/
typedef struct
{
	uint8 		MotorAction;
	
	uint16 		Avrticks;
	
	uint16 		WindowPosition;
	
}AntiPinchInput;

AntiPinchInput StAPInput ={0} ;

void AntiPich(void)
{
	//����˶�״̬
	StAPInput.MotorAction = Get_MotorAction();
	
	//���λ��
	StAPInput.WindowPosition = WindowPosition_Get();
	
	//������ٶȣ� ������hall�����ʱ���ʾ
	StAPInput.Avrticks = HallSpeedTicks_Get();
	
	/*motor speed(rpm) and current calculate*/
	AvrSpeedCurrentCalc(StAPInput.Avrticks);		
	
	#if 1
	//�Զ��Ϻ�λ�ڷ�����������������
	if( StAPInput.MotorAction == AUTO_UP && AntiZoneCheck(StAPInput.WindowPosition)==1 ) //
	{
		//�����г������Ƿ�����
		APCurrentMonitor();
		
		//�ٶȼг������Ƿ�����
		APSpeedMonitor();
				
		/* both speed pinch and current pinch events happened simulitaneously*/
		if( (StAPSpeed.APFlag)==EVENTHAPPEND && (StAPCurrent.APFlag)==EVENTHAPPEND)
		{
			//�г��¼�����
			PinchFlag =EVENTHAPPEND;
			
			//��λһЩ������������˵��ٶȿ���
			testap();
		}
		else//������������0 ����ɻ��˾����ж�ʧ��
		{

		}
	}
	else
	{
	}

	#endif
}


uint8 Get_PinchStatus(void)
{
	return PinchFlag;
}
void Set_PinchFlag(void)
{
	PinchFlag =0;
}







