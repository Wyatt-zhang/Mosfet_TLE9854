#include "Method_Serve.h"



/*一些通用处理函数，如滤波，PID等*/


/*
	Filter time is  multiply FilterTime_Cnt by action time typ. 1ms  in main function .
ex. FilterTime(20ms)=  FilterTime_Cnt(20)*systick handle(1ms)
*/


/*
    计数滤波方法
    信号连续采样一定的次数，都为一致的话，则认为是有效的信号输入，
    否则为干扰信号
*/
void MethodCountFilter(uint8 InputSignal,CalcMethod *ptr){
	
	//当前输入信号状态不等于之前的信号状态，视为干扰，变量为0
	if(InputSignal != ptr->OldSignal)
	{
		ptr->OldSignal = InputSignal;
		
		ptr->SignalCnt = 0;
		
	}
	else//等于 计数+1
	{
		++(ptr->SignalCnt);
	}
	
	//计数大于给定值，则为有效的信号输入，更新现在的值Current_KeyStatus
	if( (ptr->SignalCnt) >= (ptr->SignalCntLimit))
	{
        ptr->OutputSignal = InputSignal;
        
		ptr->SignalCnt = 0;
	}
	else//否则不更新输出信号，认为输出信号没变
	{

	}
    
   
}

/*
	滑动中值滤波算法  去掉最大和最小值 然后取平均
    数组的长度需大于2，8~12比较好
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


