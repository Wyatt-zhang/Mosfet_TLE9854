#include "tle_device.h"	
#include "Speed_Serve.h"

#include "Interrupt_Serve.h"	


#include "MotorControl_Serve.h"

#include "Motor_Parameter.h"
#include "Method_Serve.h"


/***********
    计算电机的速度和电流；
************
*********
*/
/*  when motor is at stopping action, deltatick is needed to set to zero  */

//calc Motor Speed- rpm
#define GPT13_BASE_CLK   2500000u

#define SPEEDLENTH     		12u

static uint8 OldestSpeed_Num = 0;

static uint8 NewestSpeedPos_Rec = 0;

static uint16 AvrSpeed_Array[SPEEDLENTH]={0};

static uint16 AvrSpeedFilter_Array[SPEEDLENTH]={0};

uint16 Temp_Speed=0;

uint16 Speedfilter=0;

uint16 Speedfilter1 = 0;


//just for test
uint16 Buffer_4 = 0;
uint16 Speedfilter2 = 0;
uint8  speedspace = 0;
//转动一周产生4个hall 脉冲--和磁环的极对数有关
static void AvrSpeedCalc(uint16 Avrtick)
{

	if(Avrtick!=0)
	{
		Temp_Speed = (uint16)((float32)(GPT13_BASE_CLK*60u)/(float32)(Avrtick*4) );
	}
	else
	{
		Temp_Speed = 0;
	}
	
	//原始的速度数据，数组长度为12
	AvrSpeed_Array[OldestSpeed_Num] = Temp_Speed; 	
	
	//经过滑动中值滤波的数据，有利于消除速度抖动
	Speedfilter = MethodMiddleFilter(AvrSpeed_Array,SPEEDLENTH);
	
	//进一步缩小 减小波动，有利于用作速度防夹判断
	Speedfilter1 = Speedfilter /7 ;
	
	//存放到滤波后的数组内 长度为12
	AvrSpeedFilter_Array[OldestSpeed_Num] = Speedfilter1;
    
//test    
    if(speedspace == 7)
    {
         Buffer_4 =  MINUS(Speedfilter2,Speedfilter1); 
         
         Speedfilter2 = Speedfilter1;
        
        speedspace = 0;
    }
    else
    {
        speedspace++;
    }

	
	//记录最新数据的位置
	NewestSpeedPos_Rec = OldestSpeed_Num;
	
	if( ++OldestSpeed_Num >= SPEEDLENTH)
	{
		OldestSpeed_Num = 0;
	}
	else
	{
	}
	
}





#define ERRORSPEEDLENTH     96u

#define BUFFERMAX     		800u

static uint8 OldestError_Num = 0;

static uint16 NewestErrorSpeedPos_Rec = 0;

uint16 Buffer_1=0,Buffer_2=0,Buffer_3=0;


static uint16 SpeedError_array[ERRORSPEEDLENTH]={0};
 



//速度差值趋势数组获取
static void ErrorAvrSpeedCalc(void)//
{
	uint8 OldestSpeedPos = 0;
	
	//最老的速度数据
	if( NewestSpeedPos_Rec==(SPEEDLENTH-1))
	{
		OldestSpeedPos = 0;
	}
	else
	{
		OldestSpeedPos = NewestSpeedPos_Rec + 1;
	} 
	
	Buffer_1 = AvrSpeedFilter_Array[OldestSpeedPos];
	
	Buffer_2 = AvrSpeedFilter_Array[NewestSpeedPos_Rec];
	
	//只关心防夹时的速度趋势
	if(Buffer_1 > Buffer_2)
	{
		//旧-新 差值 --计算现在滤波后速度曲线的斜率，方便计算 这里取正常斜率的相反数，防夹时速度的曲线斜率为正
		Buffer_3 = Buffer_1 - Buffer_2	;	
	}
	else
	{
		Buffer_3 = 0;
	}
	//
	
	//限幅
	#if 1
	if(Buffer_3 >= BUFFERMAX)
	{
		Buffer_3 = BUFFERMAX;
	}
	else
	{
	}
	#endif
	
	//存入差值数组
	SpeedError_array[OldestError_Num] = Buffer_3; 
	
	NewestErrorSpeedPos_Rec = OldestError_Num;
	
	
	if(++OldestError_Num >= ERRORSPEEDLENTH)
	{
		OldestError_Num = 0;
	}
	else
	{
	}
}


#if 1
uint16   PopiFarrayData(void)
{
	if(NewestErrorSpeedPos_Rec==0)
	{
		NewestErrorSpeedPos_Rec = ERRORSPEEDLENTH -1;
		
		return SpeedError_array[0];
	}
	else
	{
		return SpeedError_array[NewestErrorSpeedPos_Rec--];
	}
}
#endif





#if 0

//计算电源的平均电压
#define VOLTNUM        4u

static uint8 OldestVolt_Num = 0;

static uint16 VBatmV_Array[VOLTNUM] = {0};

static uint16 AvrVBatmV =0;

// power volt for current calc
static void AvrVoltCalc(uint16 Baterry_mV)
{

	VBatmV_Array[OldestVolt_Num] = Baterry_mV / VOLTNUM;
	
	AvrVBatmV= VBatmV_Array[0] + VBatmV_Array[1] + VBatmV_Array[2] + VBatmV_Array[3];
	
	if(++OldestVolt_Num >= VOLTNUM)
	{
		OldestVolt_Num = 0;
	}
	else
	{
	}

}
#endif

/*  Current process 
只关注电流增加的趋势，不关注电流是否准确
*/
#if 1






//存放用来未经处理的电流数据
#define CURRENTLENTH		8u
static uint16 Current_Array[CURRENTLENTH]={0};

static uint8 OldestCurrent_Num = 0;
//


		//电流计算有关
		//电阻的倒数，随意取的值，
		float32 R_reverse = 1000 ; //

		float32 Ke= 0.0008456 ;//; //


//存放用来计算防夹的电流数据
#define FILTERCURRENTLENTH	25u
uint16 FilterCurrent_Array[FILTERCURRENTLENTH] = {0};

static uint8 OldestFilterCurrent_Num = 0;
static uint8 NewestCurrent_Pos =0;
//


uint16 filterc=0;

/*
	IR = U- Ke*n = VoltDuty - Emf
*/
static void CurrentCalc(float32 PWMDuty,uint16 AvrVBatmV)
{	
	//占空比转换为电压---单位V
	float32 VoltDuty = (float32)AvrVBatmV /1000.00 * PWMDuty/100.00 ;
	
	//反电动势--	转速的倍数
	float32 Emf= Ke*((float32)Speedfilter) ;
		
	//计算电流，电流为正
	//速度为0时，电流为0
	//初次计算的电流放入，数组，长度为8
	//循环数据缓冲队列，最新的数据覆盖最旧的
	if(Speedfilter == 0)
	{
		Current_Array[OldestCurrent_Num]  = 0;
	}
	else
	{
		Current_Array[OldestCurrent_Num] = (uint16)( MINUS(VoltDuty,Emf) *  R_reverse); 
	}
		
	if( ++OldestCurrent_Num >= CURRENTLENTH)
	{
		OldestCurrent_Num = 0;
	}	
	//
	
	//电流数据滤波 
	//滤波后数据缩小16倍
	filterc = (MethodMiddleFilter(Current_Array,CURRENTLENTH)) >>4;
	
	
	//放入滤波后的数组
	FilterCurrent_Array[OldestFilterCurrent_Num] = filterc;
	
	//循环数据缓冲队列，最新的数据覆盖最旧的
	if( ++OldestFilterCurrent_Num >= FILTERCURRENTLENTH )
	{
		OldestFilterCurrent_Num = 0;
	}
	
	//记录最老的数据--滤波后的，所在的位置
	NewestCurrent_Pos =  OldestFilterCurrent_Num;	//


}




#if 1

//循环队列，已知最老数据的位置--队首，那么下一个位置便是最新数据的位置--队尾
//首先弹出 一个最老的数据 然后是最新的数据，次新。。。
uint16  PopCurrentData(void)
{

	if( NewestCurrent_Pos ==0)
	{
		NewestCurrent_Pos = FILTERCURRENTLENTH -1;
		
		return FilterCurrent_Array[0];
	}
	else
	{
		return FilterCurrent_Array[NewestCurrent_Pos--];
	}
}

#endif



#endif

void AvrSpeedCurrentCalc(uint16 AvrTicks)
{
	uint16 Baterry_mV = 0;
	
	//平均速度计算
	AvrSpeedCalc(AvrTicks);	
    
    //速度差值计算
	ErrorAvrSpeedCalc();	
	
	//电流计算
	if( ADC1_GetChResult_mV(&Baterry_mV,ADC1_VBAT_SENSE) == true	)
	{
		
	}
	
	CurrentCalc(PWMDuty_Get(),Baterry_mV);
}






