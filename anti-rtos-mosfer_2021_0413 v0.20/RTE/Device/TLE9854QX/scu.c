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
#include "scu.h"
#include "wdt1.h"
#include "lin.h"
#include "scu_defines.h"
#include "pmu_defines.h"
#include "cmsis_misra.h"

/*******************************************************************************
**                         Global Function Definitions                        **
*******************************************************************************/
void SCU_Init(void)
{
  /***************************************************************************
   ** System Clock Output Control                                           **
  ***************************************************************************/
  SCU->COCON.reg = (uint32) (SCU_COCON);

  /***************************************************************************
   ** Watchdog Control (internal)                                           **
  ***************************************************************************/
  SCU->WDTREL.reg = (uint32) SCU_WDTREL;
  SCU->WDTWINB.reg = (uint32) SCU_WDTWINB;
  
  SCU_OpenPASSWD();	
  SCU->WDTCON.reg = (uint32) SCU_WDTCON;
  SCU_ClosePASSWD();
	
  /***************************************************************************
   ** Module Pin Select                                                     **
  ***************************************************************************/
#ifdef SCU_MODPISEL
  SCU->MODPISEL.reg = (uint32) SCU_MODPISEL;
#endif
#ifdef SCU_MODPISEL1
  SCU->MODPISEL1.reg = (uint32) SCU_MODPISEL1;
#endif
#ifdef SCU_MODPISEL2
  SCU->MODPISEL2.reg = (uint32) SCU_MODPISEL2;
#endif
  SCU->GPT12PISEL.reg = (uint32) SCU_GPT12PISEL;
}

void SCU_ClkInit(void)
{
  sint32 int_was_mask;
  /* disable all interrupts                */
  int_was_mask = CMSIS_Irq_Dis();
  /***************************************************************************
  ** NVM Protection Control                                                **
  ***************************************************************************/
#if (SCU_NVM_BOOT_PROT == 1u)
  user_nvm_protect_set((uint32) SCU_NVM_PROT_PW, (NVM_PASSWORD_SEGMENT_t)SCU_NVM_BOOT_PROT);
#endif
#if (SCU_NVM_CODE_PROT == 1u)
  user_nvm_protect_set((uint32) SCU_NVM_PROT_PW, (NVM_PASSWORD_SEGMENT_t)SCU_NVM_CODE_PROT);
#endif
#if (SCU_NVM_DATA_PROT == 1u)
  user_nvm_protect_set((uint32) SCU_NVM_PROT_PW, (NVM_PASSWORD_SEGMENT_t)SCU_NVM_DATA_PROT);
#endif

  /**************************************************************************
   ** PLL/SYSCLK Control                                                   **
   **************************************************************************/
  Field_Mod32(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIPLL_Pos, SCU_NMICON_NMIPLL_Msk, 0);
  Field_Mod32(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIWDT_Pos, SCU_NMICON_NMIWDT_Msk, 0);

  /* enable XTAL1/2 pins */
  SCU_OpenPASSWD();
  Field_Mod32(&SCU->XTAL_CTRL.reg, (uint8)SCU_XTAL_CTRL_XTAL12EN_Pos, SCU_XTAL_CTRL_XTAL12EN_Msk, SCU_XTAL_EN);
  SCU_ClosePASSWD();

  /* select LP_CLK */
  SCU_OpenPASSWD();
  Field_Mod32(&SCU->SYSCON0.reg, (uint8)SCU_SYSCON0_SYSCLKSEL_Pos, SCU_SYSCON0_SYSCLKSEL_Msk, 3u);
  SCU_ClosePASSWD();

  /* Oscillator Select */
  SCU_OpenPASSWD();
  Field_Wrt32all(&SCU->OSC_CON.reg, (uint32)SCU_OSC_CON);
  SCU_ClosePASSWD();

  SCU_OpenPASSWD();
  Field_Wrt32all(&SCU->PLL_CON.reg, (uint32)SCU_PLL_CON);
  SCU_ClosePASSWD();

  SCU_OpenPASSWD();
  Field_Wrt32all(&SCU->CMCON1.reg, (uint32)SCU_CMCON1);
  SCU_ClosePASSWD();

  /* reset PLL locking */
  SCU_OpenPASSWD();
  Field_Mod32(&SCU->PLL_CON.reg, (uint8)SCU_PLL_CON_RESLD_Pos, SCU_PLL_CON_RESLD_Msk, 1u);
  SCU_ClosePASSWD();
  /* set PLL_CON.bit.VCOBYP=0 */
  SCU_OpenPASSWD();	
  Field_Mod32(&SCU->PLL_CON.reg, (uint8)0x0, VCO_BYP_Msk, VCO_BYP_0);
  SCU_ClosePASSWD();		
  /* set PLL_CON.bit.OSCDISC=0 */
  SCU_OpenPASSWD();		
  Field_Mod32(&SCU->PLL_CON.reg, (uint8)0x0, OSC_DISC_Msk, OSC_DISC_0);
  SCU_ClosePASSWD();

	/* wait for PLL being locked           */
  while (u1_Field_Rd32(&SCU->PLL_CON.reg, (uint8)SCU_PLL_CON_LOCK_Pos, SCU_PLL_CON_LOCK_Msk) == (uint8)0)
  {
  }
	
  SCU_OpenPASSWD();
  /* 0u << 6u */
  Field_Wrt32all(&SCU->SYSCON0.reg, (uint32)0);
  SCU_ClosePASSWD();

  Field_Mod32(&SCU->NMISRCLR.reg, (uint8)SCU_NMISRCLR_FNMIPLLC_Pos, SCU_NMISRCLR_FNMIPLLC_Msk, 1u);

  /***************************************************************************
  ** Analog Clock Control                                                  **
  ***************************************************************************/

  SCU_OpenPASSWD();
  Field_Wrt32all(&SCU->APCLK.reg, (uint32)SCU_APCLK);
  SCU_ClosePASSWD();

  /* apply settings by setting APCLK_SET */
  /* APCLK_SET is cleared by HW once the clock settings are overtaken */
  SCU_OpenPASSWD();
  Field_Mod32(&SCU->APCLK_CTRL.reg, (uint8)SCU_APCLK_CTRL_APCLK_SET_Pos, SCU_APCLK_CTRL_APCLK_SET_Msk, 1u);
  SCU_ClosePASSWD();

  /* enable interrupts                     */
  if (int_was_mask == 0)
  {
    CMSIS_Irq_En();
  }
}

#if (PMU_SLEEP_MODE == 1u)
/* violation: Last value assigned to variable 'dummy' (defined at line 282) not used [MISRA 2012 Rule 2.2, required] */
void SCU_EnterSleepMode(void)
{
  /* violation: Previously assigned value to variable 'dummy' has not been used */
  /* This function assumes the desired     *
  * wake up sources are enabled already   */
  uint32 dummy;
  /* to remove compiler warning of unused  *
  * dummy variable                        */
  dummy = 0;
  dummy = dummy;
  /* set LIN Trx into Sleep Mode if LIN is enabled */
  if(LIN_Get_Mode() != LIN_GET_MODE_DISABLED)
  {
    LIN_Set_Mode(LIN_MODE_SLEEP);
    /* wait until LIN Trx switched           *
    * into Sleep Mode                       */
    while ((LIN_Get_Mode() != LIN_GET_MODE_SLEEP))
    {
    }
    /* wait approx. 100µs in order to pass   *
    * the filter time + margin inside the   *
    * LIN Trx. to avoid a false wake up     */
    Delay_us(100u);    
  }

  /* dummy read to clr wake up status      *
  * to prevent the device from wakeing up *
  * immediately because of still set      *
  * wake up flags                         */
  dummy = u32_Field_Rd32(&PMU->WAKE_STATUS.reg, (uint8)PMU_WAKE_STATUS_LIN_WAKE_Pos, MASK_WORD);

  /* stop WDT1 (SysTick) to prevent any    *
  * SysTick interrupt to disturb the      *
  * Sleep Mode Entry sequence             */
  WDT1_Stop();
  /* Trigger a ShortOpenWindow on WDT1     *
  * to prevent an unserviced WDT1 by      *
  * accident                              */
  WDT1_SOW_Service(1u);
  /* disable all interrupts                */
  (void)CMSIS_Irq_Dis();
  /* open passwd to access PMCON0 register */
  SCU_OpenPASSWD();
  /* set SleepMode flag in PMCON0        */
  Field_Wrt32all(&SCU->PMCON0.reg, (uint32)0x02);
  CMSIS_WFE();
  CMSIS_WFE();
  /* dont do anything anymore            *
  * device is in SleepMode              */
#ifndef UNIT_TESTING_LV2
  for (;;)
  {
  }
#endif
  /* device is in Sleep Mode now          *
  * wake up performs RESET               */
}
#endif

#if (PMU_STOP_MODE == 1u)
/* violation: Last value assigned to variable 'dummy' (defined at line 346) not used [MISRA 2012 Rule 2.2, required] */
void SCU_EnterStopMode(void)
{
  sint32 int_was_mask;
  /* violation: Previously assigned value to variable 'dummy' has not been used */
  uint32 dummy;
  /* to remove compiler warning of unused  *
  * dummy variable                        */
  dummy = 0;
  dummy = dummy;
  /* dummy read to clr wake up status      *
  * to prevent the device from wakeing up *
  * immediately because of still set      *
  * wake up flags                         */
  dummy = u32_Field_Rd32(&PMU->WAKE_STATUS.reg, (uint8)PMU_WAKE_STATUS_LIN_WAKE_Pos, MASK_WORD);
  /* stop WDT1 (SysTick) to prevent any    *
  * SysTick interrupt to disturb the      *
  * Sleep Mode Entry sequence             */
  WDT1_Stop();
  /* Trigger a ShortOpenWindow on WDT1     *
  * to prevent an unserviced WDT1 by      *
  * accident                              */
  WDT1_SOW_Service(1u);
  /* disable all interrupts                */
  int_was_mask = CMSIS_Irq_Dis();

  /* select LP_CLK as sys clock            */
  SCU_OpenPASSWD();
  Field_Mod32(&SCU->SYSCON0.reg, (uint8)SCU_SYSCON0_SYSCLKSEL_Pos, (uint32)SCU_SYSCON0_SYSCLKSEL_Msk, 3U);
  SCU_ClosePASSWD();

  /* select OSC_PLL async.                 */
  SCU_OpenPASSWD();
  Field_Mod32(&SCU->OSC_CON.reg, (uint8)SCU_OSC_CON_OSCSS_Pos, (uint32)SCU_OSC_CON_OSCSS_Msk, 3U);
  SCU_ClosePASSWD();

  /* open passwd to access PMCON0 register */
  SCU_OpenPASSWD();

  /* set PowerDown flag in PMCON0        */
  Field_Wrt32all(&SCU->PMCON0.reg, (uint32)0x04);
  CMSIS_WFE();
  CMSIS_WFE();
  CMSIS_NOP();
  CMSIS_NOP();
  CMSIS_NOP();
  CMSIS_NOP();

  /* dont do anything anymore            *
  * device is in PowerDown Mode         */
  /***************************************/
  /********* DEVICE IN STOP MODE *********/
  /***************************************/
  /* Device has been woken up            */
  /* reset PLL locking                   */
  SCU_OpenPASSWD();
  Field_Mod32(&SCU->PLL_CON.reg, (uint8)SCU_PLL_CON_RESLD_Pos, SCU_PLL_CON_RESLD_Msk, 1u);
  SCU_ClosePASSWD();
  /* set PLL_CON.bit.VCOBYP=0 */
  SCU_OpenPASSWD();	
  Field_Mod32(&SCU->PLL_CON.reg, (uint8)0x0, VCO_BYP_Msk, VCO_BYP_0);
  SCU_ClosePASSWD();		
  /* set PLL_CON.bit.OSCDISC=0 */
  SCU_OpenPASSWD();		
  Field_Mod32(&SCU->PLL_CON.reg, (uint8)0x0, OSC_DISC_Msk, OSC_DISC_0);
  SCU_ClosePASSWD();
	
	/* wait for PLL being locked           */
  while (u1_Field_Rd32(&SCU->PLL_CON.reg, (uint8)SCU_PLL_CON_LOCK_Pos, SCU_PLL_CON_LOCK_Msk) == (uint8)0)
  {
  }
	
  /* switch fSYS back to                 *
  * user configuration                  */
  SCU_OpenPASSWD();
  Field_Wrt32all(&SCU->SYSCON0.reg, (uint32)0);
  SCU_ClosePASSWD();

  /* enable interrupts                     */
  if (int_was_mask == 0)
  {
    CMSIS_Irq_En();
  }

  /* Init SysTick                          */
  SysTick_Init();

  /* Init and service WDT1                 */
  WDT1_Init();
}
#endif

int32_t SCU_ChangeNVMProtection(NVM_PASSWORD_SEGMENT_t Protection, uint8 Action)
{
  int32_t result;
  result = (int32_t)ERR_LOG_ERROR;
  if (Action == PROTECTION_CLEAR)
  {
    if (Protection == NVM_PASSWORD_SEGMENT_BOOT)
    {
      result = (int32_t)user_nvm_protect_clear((uint32) SCU_NVM_PROT_PW, Protection);
    }
    else if (Protection == NVM_PASSWORD_SEGMENT_CODE)
    {
      result = (int32_t)user_nvm_protect_clear((uint32) SCU_NVM_PROT_PW, Protection);
    }
    else if (Protection == NVM_PASSWORD_SEGMENT_DATA)
    {
      result = (int32_t)user_nvm_protect_clear((uint32) SCU_NVM_PROT_PW, Protection);
    }
    else
    {

    }
  }
  else
  {
    if (Protection == NVM_PASSWORD_SEGMENT_BOOT)
    {
      result = (int32_t)user_nvm_protect_set((uint32) SCU_NVM_PROT_PW, Protection);
    }
    else if (Protection == NVM_PASSWORD_SEGMENT_CODE)
    {
      result = (int32_t)user_nvm_protect_set((uint32) SCU_NVM_PROT_PW, Protection);
    }
    else if (Protection == NVM_PASSWORD_SEGMENT_DATA)
    {
      result = (int32_t)user_nvm_protect_set((uint32) SCU_NVM_PROT_PW, Protection);
    }
    else
    {

    }
  }
  return (result);
}
