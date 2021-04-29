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
#include "pmu.h"
#include "wdt1.h"
#include "pmu_defines.h"
#include "cmsis_misra.h"

/*******************************************************************************
**                         Global Function Definitions                        **
*******************************************************************************/
void PMU_Init(void)
{
  PMU->VDDEXT_CTRL.reg = (uint32) PMU_VDDEXT_CTRL;
  PMU->SLEEP.reg = (uint32) PMU_SLEEP;

  PMU->SUPPLY_STS.reg = (uint32) PMU_SUPPLY_STS;
  PMU->LIN_WAKE_EN.reg = (uint32) PMU_LIN_WAKE_EN;

  PMU->OT_CTRL.reg = (uint32) PMU_OT_CTRL;

  PMU->WAKE_CNF_GPIO0.reg = (uint32) PMU_WAKE_CNF_GPIO0;
  PMU->WAKE_CNF_GPIO1.reg = (uint32) PMU_WAKE_CNF_GPIO1;

  PMU->CNF_RST_TFB.reg = (uint32) PMU_CNF_RST_TFB;
  PMU->CNF_WAKE_FILTER.reg = (uint32) PMU_CNF_WAKE_FILTER;
  
  PMU->DRV_CTRL.reg = (uint32) PMU_DRV_CTRL;
}

bool PMU_VDDEXT_On(void)
{
  bool bRet = false;

  Field_Mod32(&PMU->VDDEXT_CTRL.reg, (uint8)PMU_VDDEXT_CTRL_VDDEXT_ENABLE_Pos, (uint8)PMU_VDDEXT_CTRL_VDDEXT_ENABLE_Msk, 1u);

  /* delay 200us, to give VDDEXT some time to ramp up */
  Delay_us(200u);
  /* return the status of VDDEXT_CTRL.STABLE */
  if (u1_Field_Rd32(&PMU->VDDEXT_CTRL.reg, (uint8)PMU_VDDEXT_CTRL_VDDEXT_STABLE_Pos, (uint8)PMU_VDDEXT_CTRL_VDDEXT_STABLE_Msk) == 1u)
  {
    bRet = true;
  }
  return (bRet) ;
}
