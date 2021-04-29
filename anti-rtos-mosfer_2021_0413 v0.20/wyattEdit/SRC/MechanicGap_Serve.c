
#include "MechanicGap_Serve.h"

#include "Motor_Parameter.h"


#if 1
static uint8 CntLimit = 16u;

static uint16 AvrArray[16]={0};
/*取运动开始时的前16个AvrDeltaTick，找出其最小对应的电机的pulse，即为gap*/
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
		//不需要补偿
	}
	else
	{
	//需要补偿 	Temp
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
	if(InitStep==INIT_STEP1 && Insert(AvrDeltaTick)==1)//上堵成功，往下运行，可以测出Down_Gap
	{
		Down_Gap = GapDetect(AvrArray);
		
		Insert_Ptr = 0;
	}
	else if(InitStep==INIT_STEP2 && Insert(AvrDeltaTick)==1 && UP_Gap!=0  )//下堵成功，往上运行，可以测出Up_Gap
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

