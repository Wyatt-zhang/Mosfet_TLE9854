/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-07-24     Tanek        the first version
 * 2018-11-12     Ernest Chen  modify copyright
 */
 
#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>


//add by wyatt
#if 1

/* lin driver*/
#include "lin_hal.h"


#include "tle_device.h"	 

/* init TLE9854x hardware */
static void HardwareInit(void)
{
	//config by wizard 
	TLE_Init();
	
	//Hall start
	GPT12E_T3_Start();
	
	//CCU6 block
	CCU6_StartTmr_T12();

	//enable  pwm output  for mosfet
	BDRV_Set_Bridge(Ch_LS_PWM,Ch_PWM,Ch_LS_PWM,Ch_PWM);
    
    /*lin communication init*/
    lin_sci_init();
}


static uint32_t SystemCoreClock = 0x2625A00; //40MHz

void SystemCoreClockUpdate(void)
{

	  CPU->SYSTICK_CSR.bit.CLKSOURCE = 1u;
	  /* TICK Interrupt = enabled */
	  CPU->SYSTICK_CSR.bit.TICKINT = 1u;
	  /* ENABLE SysTick Timer */
	  CPU->SYSTICK_CSR.bit.ENABLE = 1u;
}

static uint32_t _SysTick_Config(rt_uint32_t ticks)
{
    if ((ticks - 1) > 0x2625A00)
    {
        return 1;
    }
	
	 /* program SysTick Timer */
	  CPU->SYSTICK_RVR.reg = ticks;
	  /* reset SysTick timer */
	  CPU->SYSTICK_CVR.reg = 0u;
	  /* CLKSRC=CPU clk */
	  CPU->SYSTICK_CSR.bit.CLKSOURCE = 1u;
	  /* TICK Interrupt = enabled */
	  CPU->SYSTICK_CSR.bit.TICKINT = 1u;
	  /* ENABLE SysTick Timer */
	  CPU->SYSTICK_CSR.bit.ENABLE = 1u;	
	
    return 0;    
}

#endif







#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
#define RT_HEAP_SIZE 0
 uint32_t rt_heap[RT_HEAP_SIZE];     // heap default size: 4K(1024 * 4)
RT_WEAK void *rt_heap_begin_get(void)
{
    return rt_heap;
}

RT_WEAK void *rt_heap_end_get(void)
{
    return rt_heap + RT_HEAP_SIZE;
}
#endif

/**
 * This function will initial your board.
 */
void rt_hw_board_init()
{
    
    /* System Tick Configuration */
    _SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);
	
    /* System Clock Update */
    SystemCoreClockUpdate();	
	
	//add by wyatt hardware init
	HardwareInit();
	//end 
	
    /* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());
#endif
}

void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();
	
	// add by wyatt
	//watch dog count++
	WDT1_Window_Count();
    
	#if 1
		lin_sci_timeout();//Ö¡Êý¾Ý³¬Ê± ¶ªÆú
    #endif
	//end
	
    /* leave interrupt */
    rt_interrupt_leave();
}
