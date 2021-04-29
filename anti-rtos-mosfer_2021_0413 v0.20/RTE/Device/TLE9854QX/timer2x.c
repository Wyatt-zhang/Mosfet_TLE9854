/*
 ***********************************************************************************************************************
 *
 * Copyright (c) 2015, Infineon Technologies AG
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
**                                  Includes                                  **
*******************************************************************************/
#include "timer2x.h"
#include "timer2x_defines.h"
#include "scu_defines.h"

/*******************************************************************************
**                             External CallBacks                             **
*******************************************************************************/
uint32 Sys_Freq;

/*******************************************************************************
**                         Global Function Definitions                        **
*******************************************************************************/
void TIMER2_Init(void)
{
#if (TIMER2_Configuration_En == 1u)
  TIMER2->RC.reg = (uint32) TIMER2_RC2;
  TIMER2->CNT.reg = (uint32) TIMER2_T2;
  TIMER2->MOD.reg = (uint32) TIMER2_MOD;
  TIMER2->CON.reg = (uint32) TIMER2_CON;
  TIMER2->CON1.reg = (uint32) TIMER2_CON1;
  Sys_Freq = SCU_FSYS;
#endif
}

void TIMER21_Init(void)
{
#if (TIMER21_Configuration_En == 1u)
  TIMER21->RC.reg = (uint32) TIMER21_RC2;
  TIMER21->CNT.reg = (uint32) TIMER21_T2;
  TIMER21->MOD.reg = (uint32) TIMER21_MOD;
  TIMER21->CON.reg = (uint32) TIMER21_CON;
  TIMER21->CON1.reg = (uint32) TIMER21_CON1;
  Sys_Freq = SCU_FSYS;
#endif
}

bool TIMER2_Interval_Timer_Setup(uint32 timer_interval_us)
{
  bool res;
  uint64 timer_ticks;
  uint32 clk_prescaler;
  /* set initial result to false */
  res = false;

  /* Check that the input timer_interval_us is at least the minimum specified */
  if(timer_interval_us >= MIN_TIMER_INTERVAL_US)
  {
    /* calculate timer ticks based on TIMER2 frequency */
    timer_ticks = ((uint64)timer_interval_us * ((uint64)Sys_Freq / (uint64)1000)) / (uint64)1000;

    /* preload TIMER2 clock prescaler with 'div 1' */
    clk_prescaler = (uint8)TIMER2x_Clk_Div_1;
    /* as long as calculated timer ticks is larger than the TIMER2 value register **
    ** can hold (16bit), increase the prescaler by one, and divide the timer      **
    ** ticks by 2                                                                 */
    while (timer_ticks > (uint64)0xFFFF)
    {
      clk_prescaler++;
      timer_ticks >>= 1u;
    }
    /* timer operates in reload mode, and is upcounting by default */
    timer_ticks = (uint64)0x10000 - timer_ticks;
    /* if the clock prescaler is within the allowed range */
    if (clk_prescaler <= (uint32)TIMER2x_Clk_Div_128)
    {
      /* select Reload Mode */
      TIMER2_Mode_Reload_Set();
      /* program the calculated prescaler */
      TIMER2_Clk_Prescaler_Sel((uint8)clk_prescaler);
      /* disable external up/down counter mode **
      ** counter is counting up by default     */
      TIMER2_UpDownCount_Dis();
      /* program first period */
      TIMER2_Value_Set((uint16)timer_ticks);
      /* program reload value */
      TIMER2_Reload_Value_Set((uint16)timer_ticks);
      /* set result to true */
      res = true;
    }
  }
  return(res);
}

bool TIMER21_Interval_Timer_Setup(uint32 timer_interval_us)
{
  bool res;
  uint64 timer_ticks;
  uint8 clk_prescaler;
  /* set initial result to false */
  res = false;

  /* Check that the input timer_interval_us is at least the minimum specified */
  if(timer_interval_us >= MIN_TIMER_INTERVAL_US)
  {
    /* calculate timer ticks based on TIMER21 frequency */
    timer_ticks = ((uint64)timer_interval_us * ((uint64)Sys_Freq / (uint64)1000)) / (uint64)1000;

    /* preload TIMER21 clock prescaler with 'div 1' */
    clk_prescaler = (uint8)TIMER2x_Clk_Div_1;
    /* as long as calculated timer ticks is larger than the TIMER21 value register **
    ** can hold (16bit), increase the prescaler by one, and divide the timer       **
    ** ticks by 2                                                                  */
    while (timer_ticks > (uint64)0xFFFFu)
    {
      clk_prescaler++;
      timer_ticks >>= 1u;
    }
    /* timer operates in reload mode, and is upcounting by default */
    timer_ticks = (uint64)0x10000 - timer_ticks;
    /* if the clock prescaler is within the allowed range */
    if (clk_prescaler <= (uint32)TIMER2x_Clk_Div_128)
    {
      /* select Reload Mode */
      TIMER21_Mode_Reload_Set();
      /* program the calculated prescaler */
      TIMER21_Clk_Prescaler_Sel((uint8)clk_prescaler);
      /* disable external up/down counter mode **
      ** counter is counting up by default     */
      TIMER21_UpDownCount_Dis();
      /* program first period */
      TIMER21_Value_Set((uint16)timer_ticks);
      /* program reload value */
      TIMER21_Reload_Value_Set((uint16)timer_ticks);
      /* set result to true */
      res = true;
    }
  }
  return(res);
}
