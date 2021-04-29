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
#include "mon.h"
#include "wdt1.h"
#include "mon_defines.h"
#include "isr_defines.h"

/*******************************************************************************
**                         Global Function Definitions                        **
*******************************************************************************/
void MONx_Init(void)
{
  PMU->MON_CNF1.reg = (uint32) PMU_MON_CNF1;
  SCU->MONIEN.reg = (uint32) SCU_MONIEN;
}

uint8 MONx_Get_Status(uint8 Monx)
{
  uint8 sts;
  uint8 pos;
  uint32 msk;
  
  if (Monx < 5u)
  {
  	pos = (uint8)((Monx *8u) - 1u);
  	msk = (uint32)1u << pos;
  	sts = u1_Field_Rd32(&PMU->MON_CNF1.reg, (uint8)pos, (uint32)msk);
  }
  else
  {
  	sts = 0;
  }
  return(sts);
}


uint8 MONx_Debounce(uint8 Monx,uint8 MonActiveState)
{
  uint32 debounce = 1;

  while (debounce > 0u)
  {
    /* wait until MONx button is released and remember that it was pressed */
    while (MONx_Get_Status(Monx) != MonActiveState)
    {
      (void)WDT1_Service();
      debounce = 20000;
    }
    debounce--;
  }
  return (MONx_Get_Status(Monx));
}
