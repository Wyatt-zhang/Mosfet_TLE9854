
#include "MechanicGap_Serve.h"

#include "Motor_Parameter.h"


#if 1
static uint8 CntLimit = 16u;

static uint16 AvrArray[16]={0};
/*ȡ�˶���ʼʱ��ǰ16��AvrDeltaTick���ҳ�����С��Ӧ�ĵ����pulse����Ϊgap*/
static uint8  GapDetect(uint16 AvrDeltaTick[])//uint16 WindownTravel,
{
	uint16 TempMin = 0xFFFF;

	uint8 MechGap = 0 ;
	
	uint8 Cnt=0;
	
	while(Cnt<CntLimit)
	{
		if(AvrDeltaTick[Cnt]<TempMin)
		{
			TempMin = AvrDeltaTick[Cnt];
			
			MechGap = Cnt;
		}
		Cnt++;		
	}

	return MechGap;
}	
#endif 

static uint8 PreMotorDirec = 0;
static uint8 UP_Gap = 0;
static uint8 Down_Gap = 0;
 uint16  GapCompensate(uint8 MotorDirec,uint16 WindowPos)
{
	uint16 Temp = WindowPos;
	
	if(MotorDirec==PreMotorDirec)
	{
		//����Ҫ����
	}
	else
	{
	//��Ҫ���� 	Temp
		if(MotorDirec==0)//up
		{
			Temp += UP_Gap;
		}
		else
		{
			Temp  -=Down_Gap;
		}

	}
	
	PreMotorDirec = MotorDirec ;
	
	return Temp;
}

static uint8 Insert_Ptr = 0;
static uint8 Insert(uint16 AvrDeltaTick)
{
	uint8 Temp = 0;
	
	if(Insert_Ptr<CntLimit)
	{
		AvrArray[Insert_Ptr++] = 	AvrDeltaTick;
	}
	else
	{
		Temp =1;
	}
	return Temp;
}
	#if 1
uint16 GapLogic(uint8 MotorDirec,uint8 InitStep,uint16 WindowPos,uint16 AvrDeltaTick)
{
	uint16 Temp = 0;
	if(InitStep==INIT_STEP1 && Insert(AvrDeltaTick)==1)//�϶³ɹ����������У����Բ��Down_Gap
	{
		Down_Gap = GapDetect(AvrArray);
		
		Insert_Ptr = 0;
	}
	else if(InitStep==INIT_STEP2 && Insert(AvrDeltaTick)==1 && UP_Gap!=0  )//�¶³ɹ����������У����Բ��Up_Gap
	{
		UP_Gap =  GapDetect(AvrArray);
	}
	else
	{
	}
	
	Temp = GapCompensate(MotorDirec,WindowPos);
	
	return Temp;
}

#endif

