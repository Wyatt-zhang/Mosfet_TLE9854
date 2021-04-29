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

//8�ֽڶ���
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
    
		lin_sci_rx_isr();//�����ж����ݴ���
    
    
		UART1->SCONCLR.bit.RICLR = 1u;

}

//
static void thread_motion(void *param)
{
	while(1)
	{
		
		//�����ж�
		AntiPich();	
		
		//�����˶�ָ����ʹ����˶�
		Motion_Control(flag);
        
		#if 1
		lin_period_handle();
    
		lin_rx_diag_frame();
        #endif
	}
}


/*2ms�����ڶ�ʱ��ɨ�裬���µ��״̬*/
static void thread_data(void *param)
{
		//ι�����
		(void)WDT1_Service();
		
		//����˶�ָ��ĸ���
		flag =MotorCommnads_Update();

        //lin test
        LINCmdDeal();
        //
		cnt++;

}


//�¼���
struct rt_event MotorEvent;

//main thread  priority is priority_max/3 32/3=10 ջΪ256 bytes
int main(void)
{
	//��ʼ���¼���
	rt_event_init(&MotorEvent,"MotorStatus",RT_IPC_FLAG_PRIO);
	
	//��ʼ��hall speed signal�������� �ź���Ϊ0�����ȼ�����
	rt_sem_init(&sem_hall,"hall_process",0,RT_IPC_FLAG_PRIO);
	
	//���ڶ�ʱ�� 2ms ���ȼ�13
	rt_timer_init(&timer1,"monitor",thread_data,RT_NULL,2,RT_TIMER_FLAG_PERIODIC|RT_TIMER_FLAG_SOFT_TIMER);
	
	//�����������ȼ�16
	rt_thread_init(&threadmotor,"motiontask",thread_motion,RT_NULL,&threadmotor_stack[0],sizeof(threadmotor_stack),16,30);
	
	//������ʱ��
	rt_thread_startup(&threadmotor);
	
	//��������
	rt_timer_start(&timer1);
	
	//�����жϵװ봦������
	while(1)
	{

		//�ȴ�hall�ٶ� �ж����� �����ź���
		if(rt_sem_take(&sem_hall,RT_WAITING_FOREVER) == RT_EOK)
		{
			//��ʱ200us ��hall �����ź��ȶ��� �Ž��м���
			//���������������źŶ���������λ��ƫ�ƴӶ���������ͣ��Ư�Ƶ�����
			//infineon ��API�����ĵ���
			Delay_us(200);
			
			
			//ƽ��deltatick ����
			ISR_HallProcess();	
			
			cnt1++;	
		}

	}
	
}// main end


