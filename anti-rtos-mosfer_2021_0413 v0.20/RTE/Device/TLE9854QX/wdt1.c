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
#include "wdt1.h"
#include "scu_defines.h"

/*******************************************************************************
**                        Private Variable Declarations                       **
*******************************************************************************/
/**\brief window counter for WDT1. It is incremented by the SysTick interrupt
 *\brief on every Millisecond. It is used by the function WDT1_Service()
 *\brief to determine the right service point for the WDT1.
 */
uint32 WD_Counter;
/**\brief is set in case a WDT1 Short Open Window is active.*/
bool bSOWactive;

/*******************************************************************************
**                         Global Function Definitions                        **
*******************************************************************************/
void WDT1_Init(void)
{
  /* trigger inital WDT1 service */
  SCUPM->WDT1_TRIG.reg = (uint32) SCUPM_WDT1_TRIG;
  /* reset window counter */
  WD_Counter = 0u;
  /* reset SOW active signal */
  bSOWactive = false;
}

void SysTick_Init(void)
{
  uint32 ui;

  /* calc SysTick reload based on SystemFrequency */
  ui = (uint32)SCU_FSYS / SysTickFreq;
  /* program SysTick Timer */
  CPU->SYSTICK_RVR.reg = ui;
  /* reset SysTick timer */
  CPU->SYSTICK_CVR.reg = 0u;
  /* CLKSRC=CPU clk */
  CPU->SYSTICK_CSR.bit.CLKSOURCE = 1u;
  /* TICK Interrupt = enabled */
  CPU->SYSTICK_CSR.bit.TICKINT = 1u;
  /* ENABLE SysTick Timer */
  CPU->SYSTICK_CSR.bit.ENABLE = 1u;
}

void WDT1_Stop(void)
{
  /* DISABLE SysTick Timer */
  Field_Mod32(&CPU->SYSTICK_CSR.reg, (uint8)CPU_SYSTICK_CSR_ENABLE_Pos, CPU_SYSTICK_CSR_ENABLE_Msk, 0u);
}

bool WDT1_Service(void)
{
  bool bResult;
  bResult = false;
  /* check if Window Counter is beyond 70% of WDT1 period  *
  * or if a SOW service has been done before              */

  if ((WD_Counter > (uint32)SCUPM_WDT1_TRIGGER) || (bSOWactive == true))
  {
    /* service WDT1 */
    Field_Wrt32all(&SCUPM->WDT1_TRIG.reg, (uint8)SCUPM_WDT1_TRIG);

    /* reset window counter */
    WD_Counter = 0u;
    /* reset "short open window" active flag */
    bSOWactive = false;

    bResult = true;
  }
  return (bResult);
}

void WDT1_SOW_Service(uint32 NoOfSOW)
{
  Field_Wrt32(&SCUPM->WDT1_TRIG.reg, (uint8)SCUPM_WDT1_TRIG_SOWCONF_Pos, SCUPM_WDT1_TRIG_SOWCONF_Msk, (NoOfSOW & 3u));

  bSOWactive = true;
}

void Delay_us(uint32 delay_time_us)
{
  uint32 delay_val;
  uint32 systick_val;
  uint32 delay_count;
  uint32 systick_cur;

  /* get current systick value */
  systick_val = Systick_Value_Get();

  while(delay_time_us >= (uint32)1000)
  {
    /* wait for underflow */
    while(Systick_Value_Get() < systick_val)
    {}
    /* wait target underflowed */
    while(Systick_Value_Get() > systick_val)
    {}

    delay_time_us -= (uint32)1000;
  }

  delay_count = delay_time_us * (uint32)One_us;
  /* get current systick value */
  systick_val = Systick_Value_Get();

  if( systick_val >= delay_count)
  {
    delay_val = systick_val - delay_count;
    /* wait underflow with 1 countdown detection */
    do
    {
      systick_cur = Systick_Value_Get();
    }
    while((systick_cur > delay_val) && (systick_cur < systick_val));
  }
  else
  {
    delay_val = Systick_ReloadValue_Get()- ( delay_count - systick_val );

    /* wait for underflow */
    while(Systick_Value_Get() < systick_val)
    {}
    /* wait target underflowed */
    while(Systick_Value_Get() > delay_val)
    {}
  }
}
