#include "Method_Serve.h"



/*һЩͨ�ô����������˲���PID��*/


/*
	Filter time is  multiply FilterTime_Cnt by action time typ. 1ms  in main function .
ex. FilterTime(20ms)=  FilterTime_Cnt(20)*systick handle(1ms)
*/


/*
    �����˲�����
    �ź���������һ���Ĵ�������Ϊһ�µĻ�������Ϊ����Ч���ź����룬
    ����Ϊ�����ź�
*/
void MethodCountFilter(uint8 InputSignal,CalcMethod *ptr){
	
	//��ǰ�����ź�״̬������֮ǰ���ź�״̬����Ϊ���ţ�����Ϊ0
	if(InputSignal != ptr->OldSignal)
	{
		ptr->OldSignal = InputSignal;
		
		ptr->SignalCnt = 0;
		
	}
	else//���� ����+1
	{
		++(ptr->SignalCnt);
	}
	
	//�������ڸ���ֵ����Ϊ��Ч���ź����룬�������ڵ�ֵCurrent_KeyStatus
	if( (ptr->SignalCnt) >= (ptr->SignalCntLimit))
	{
        ptr->OutputSignal = InputSignal;
        
		ptr->SignalCnt = 0;
	}
	else//���򲻸�������źţ���Ϊ����ź�û��
	{

	}
    
   
}

/*
	������ֵ�˲��㷨  ȥ��������Сֵ Ȼ��ȡƽ��
    ����ĳ��������2��8~12�ȽϺ�
*/
uint16 MethodMiddleFilter(uint16 a[],uint8 Num){
	uint32 temp = 0;
	
	uint16 tempmax=a[0],tempmin=a[0];
	
	uint8 cnt =0;
	
	while(cnt++<Num)
	{
		if(tempmax < a[cnt] )
		{
			tempmax = a[cnt];
		}
		if(tempmin > a[cnt])
		{
			tempmin = a[cnt] ;
		}
		temp += (uint32)a[cnt];
	}
	return (uint16)((temp - (uint32)tempmax - (uint32)tempmin )/(uint32)(Num-2));
}


