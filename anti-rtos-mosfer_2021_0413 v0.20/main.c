/*
 ***********************************************************************************************************************
 *
 * Copyright (c) 2018, Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 *   Redistributions of source code must retain the above copyright notice, this list of conditions and the  following
 *   disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *   following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *   Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 *   products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT  OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 **********************************************************************************************************************/

/*******************************************************************************
**                             Author(s) Identity                             **
********************************************************************************
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** DM           Daniel Mysliwitz                                              **
** BG           Blandine Guillot                                              **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V0.1.0: 2015-08-07, DM:   Initial version                                  **
** V0.1.1: 2020-03-02, BG:   Updated revision history format                  **
*******************************************************************************/

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "ProjectHeaders.h"

#include <rtthread.h>

#include "lin.h"
#include "lin_hal.h"

#include "lin_il.h"
/*******************************************************************************
**                          Private Macro Definitions                         **
*******************************************************************************/

/*******************************************************************************
**                        Private Function Declarations                       **
*******************************************************************************/

/*******************************************************************************
**                        Private Variable Definitions                        **
*******************************************************************************/

//8字节对齐
ALIGN(RT_ALIGN_SIZE)



struct rt_thread  threadmotor;

char threadmotor_stack[320];

struct rt_semaphore sem_hall;

struct rt_timer timer1;

/*******************************************************************************
**                        Private Constant Definitions                        **
*******************************************************************************/

uint16 cnt=0;

uint8 flag=0; 

uint16 cnt1=0;


extern void uart_isr(void){
    
		lin_sci_rx_isr();//接收中断数据处理
    
    
		UART1->SCONCLR.bit.RICLR = 1u;

}

//
static void thread_motion(void *param)
{
	while(1)
	{
		
		//防夹判断
		AntiPich();	
		
		//依据运动指令驱使电机运动
		Motion_Control(flag);
        
		#if 1
		lin_period_handle();
    
		lin_rx_diag_frame();
        #endif
	}
}


/*2ms的周期定时器扫描，更新电机状态*/
static void thread_data(void *param)
{
		//喂软件狗
		(void)WDT1_Service();
		
		//电机运动指令的更新
		flag =MotorCommnads_Update();

        //lin test
        LINCmdDeal();
        //
		cnt++;

}


//事件集
struct rt_event MotorEvent;

//main thread  priority is priority_max/3 32/3=10 栈为256 bytes
int main(void)
{
	//初始化事件集
	rt_event_init(&MotorEvent,"MotorStatus",RT_IPC_FLAG_PRIO);
	
	//初始化hall speed signal处理工作的 信号量为0，优先级队列
	rt_sem_init(&sem_hall,"hall_process",0,RT_IPC_FLAG_PRIO);
	
	//周期定时器 2ms 优先级13
	rt_timer_init(&timer1,"monitor",thread_data,RT_NULL,2,RT_TIMER_FLAG_PERIODIC|RT_TIMER_FLAG_SOFT_TIMER);
	
	//任务函数，优先级16
	rt_thread_init(&threadmotor,"motiontask",thread_motion,RT_NULL,&threadmotor_stack[0],sizeof(threadmotor_stack),16,30);
	
	//启动定时器
	rt_thread_startup(&threadmotor);
	
	//启动任务
	rt_timer_start(&timer1);
	
	//霍尔中断底半处理任务
	while(1)
	{

		//等待hall速度 中断来临 接受信号量
		if(rt_sem_take(&sem_hall,RT_WAITING_FOREVER) == RT_EOK)
		{
			//延时200us 待hall 方向信号稳定后 才进行计算
			//有利于消除方向信号抖动，导致位置偏移从而，上下软停点漂移的问题
			//infineon 的API函数的调用
			Delay_us(200);
			
			
			//平均deltatick 计算
			ISR_HallProcess();	
			
			cnt1++;	
		}

	}
	
}// main end


