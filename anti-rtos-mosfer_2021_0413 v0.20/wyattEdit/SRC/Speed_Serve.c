#include "tle_device.h"	
#include "Speed_Serve.h"

#include "Interrupt_Serve.h"	


#include "MotorControl_Serve.h"

#include "Motor_Parameter.h"
#include "Method_Serve.h"


/***********
    ���������ٶȺ͵�����
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
//ת��һ�ܲ���4��hall ����--�ʹŻ��ļ������й�
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
	
	//ԭʼ���ٶ����ݣ����鳤��Ϊ12
	AvrSpeed_Array[OldestSpeed_Num] = Temp_Speed; 	
	
	//����������ֵ�˲������ݣ������������ٶȶ���
	Speedfilter = MethodMiddleFilter(AvrSpeed_Array,SPEEDLENTH);
	
	//��һ����С ��С�����������������ٶȷ����ж�
	Speedfilter1 = Speedfilter /7 ;
	
	//��ŵ��˲���������� ����Ϊ12
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

	
	//��¼�������ݵ�λ��
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
 



//�ٶȲ�ֵ���������ȡ
static void ErrorAvrSpeedCalc(void)//
{
	uint8 OldestSpeedPos = 0;
	
	//���ϵ��ٶ�����
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
	
	//ֻ���ķ���ʱ���ٶ�����
	if(Buffer_1 > Buffer_2)
	{
		//��-�� ��ֵ --���������˲����ٶ����ߵ�б�ʣ�������� ����ȡ����б�ʵ��෴��������ʱ�ٶȵ�����б��Ϊ��
		Buffer_3 = Buffer_1 - Buffer_2	;	
	}
	else
	{
		Buffer_3 = 0;
	}
	//
	
	//�޷�
	#if 1
	if(Buffer_3 >= BUFFERMAX)
	{
		Buffer_3 = BUFFERMAX;
	}
	else
	{
	}
	#endif
	
	//�����ֵ����
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

//�����Դ��ƽ����ѹ
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
ֻ��ע�������ӵ����ƣ�����ע�����Ƿ�׼ȷ
*/
#if 1






//�������δ������ĵ�������
#define CURRENTLENTH		8u
static uint16 Current_Array[CURRENTLENTH]={0};

static uint8 OldestCurrent_Num = 0;
//


		//���������й�
		//����ĵ���������ȡ��ֵ��
		float32 R_reverse = 1000 ; //

		float32 Ke= 0.0008456 ;//; //


//�������������еĵ�������
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
	//ռ�ձ�ת��Ϊ��ѹ---��λV
	float32 VoltDuty = (float32)AvrVBatmV /1000.00 * PWMDuty/100.00 ;
	
	//���綯��--	ת�ٵı���
	float32 Emf= Ke*((float32)Speedfilter) ;
		
	//�������������Ϊ��
	//�ٶ�Ϊ0ʱ������Ϊ0
	//���μ���ĵ������룬���飬����Ϊ8
	//ѭ�����ݻ�����У����µ����ݸ�����ɵ�
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
	
	//���������˲� 
	//�˲���������С16��
	filterc = (MethodMiddleFilter(Current_Array,CURRENTLENTH)) >>4;
	
	
	//�����˲��������
	FilterCurrent_Array[OldestFilterCurrent_Num] = filterc;
	
	//ѭ�����ݻ�����У����µ����ݸ�����ɵ�
	if( ++OldestFilterCurrent_Num >= FILTERCURRENTLENTH )
	{
		OldestFilterCurrent_Num = 0;
	}
	
	//��¼���ϵ�����--�˲���ģ����ڵ�λ��
	NewestCurrent_Pos =  OldestFilterCurrent_Num;	//


}




#if 1

//ѭ�����У���֪�������ݵ�λ��--���ף���ô��һ��λ�ñ����������ݵ�λ��--��β
//���ȵ��� һ�����ϵ����� Ȼ�������µ����ݣ����¡�����
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
	
	//ƽ���ٶȼ���
	AvrSpeedCalc(AvrTicks);	
    
    //�ٶȲ�ֵ����
	ErrorAvrSpeedCalc();	
	
	//��������
	if( ADC1_GetChResult_mV(&Baterry_mV,ADC1_VBAT_SENSE) == true	)
	{
		
	}
	
	CurrentCalc(PWMDuty_Get(),Baterry_mV);
}






