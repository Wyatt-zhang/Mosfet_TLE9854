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
#include "adc1.h"
#include "wdt1.h"
#include "int.h"
#include "scu.h"
#include "adc1_defines.h"

/*******************************************************************************
**                         Global Function Definitions                        **
*******************************************************************************/
void ADC1_Init(void)
{
  uint8_t i;

  /* set ADC1 clock divider */
  SCU->ADC1_CLK.reg = (uint32) SCU_ADC1_CLK;
  /* Sequencer0-1 configuration */
  ADC1->SQ0_1.reg = (uint32) ADC1_SQ0_1;
  /* Sequencer2-3 configuration */
  ADC1->SQ2_3.reg = (uint32) ADC1_SQ2_3;
  /* Sequencer4-5 configuration */
  ADC1->SQ4_5.reg = (uint32) ADC1_SQ4_5;
  /* Sequencer6-7 configuration */
  ADC1->SQ6_7.reg = (uint32) ADC1_SQ6_7;
  /* Sequencer8-9 configuration */
  ADC1->SQ8_9.reg = (uint32) ADC1_SQ8_9;
  /* Sequencer10-11 configuration */
  ADC1->SQ10_11.reg = (uint32) ADC1_SQ10_11;
  /* Sequencer12-13 configuration */
  ADC1->SQ12_13.reg = (uint32) ADC1_SQ12_13;

  ADC1->FILTCOEFF0_13.reg = (uint32) ADC1_FILTCOEFF0_13;
  ADC1->FILT_UPLO_CTRL.reg = ADC1_FILT_UPLO_CTRL;

  ADC1->CTRL3.reg = (uint32) ADC1_CTRL3;
  ADC1->CTRL5.reg = (uint32) ADC1_CTRL5;
  ADC1->CTRL2.reg = (uint32) ADC1_CTRL2;

  /* EIS / EMS configuration ***************************************************/
  ADC1->CHx_EIM.reg = (uint32) ADC1_CHx_EIM;
  ADC1->CHx_ESM.reg = (uint32) ADC1_CHx_ESM;

  /* Channel control registers configuration ***********************************/
  SCU->MODPISEL4.reg = (uint32) SCU_MODPISEL4;
  ADC1->DIFFCH_OUT1.reg = (uint32) ADC1_DIFFCH_OUT1;
  ADC1->DUIN_SEL.reg = (uint32) ADC1_DUIN_SEL;

  ADC1->DCHTH1_4_LOWER.reg = ADC1_DCHTH1_4_LOWER;
  ADC1->DCHTH1_4_UPPER.reg = ADC1_DCHTH1_4_UPPER;

  /* Result Register Configuration *********************************************/
  ADC1->FILT_OUT0.reg = (uint32) ADC1_FILT_OUT0;
  ADC1->FILT_OUT1.reg = (uint32) ADC1_FILT_OUT1;
  ADC1->FILT_OUT2.reg = (uint32) ADC1_FILT_OUT2;
  ADC1->FILT_OUT3.reg = (uint32) ADC1_FILT_OUT3;
  ADC1->FILT_OUT4.reg = (uint32) ADC1_FILT_OUT4;
  ADC1->FILT_OUT5.reg = (uint32) ADC1_FILT_OUT5;
  ADC1->FILT_OUT6.reg = (uint32) ADC1_FILT_OUT6;
  ADC1->FILT_OUT7.reg = (uint32) ADC1_FILT_OUT7;
  ADC1->FILT_OUT8.reg = (uint32) ADC1_FILT_OUT8;
  ADC1->FILT_OUT9.reg = (uint32) ADC1_FILT_OUT9;
  // ADC1->FILT_OUT10.reg = (uint32) ADC1_FILT_OUT10;
  // ADC1->FILT_OUT11.reg = (uint32) ADC1_FILT_OUT11;
  ADC1->FILT_OUT12.reg = (uint32) ADC1_FILT_OUT12;
  ADC1->FILT_OUT13.reg = (uint32) ADC1_FILT_OUT13;
  ADC1->FILT_OUTEIM.reg = (uint32) ADC1_FILT_OUTEIM;

  /* Post Processing ***********************************************************/
  ADC1->TH0_3_LOWER.reg = (uint32) ADC1_TH0_3_LOWER;
  ADC1->TH0_3_UPPER.reg = (uint32) ADC1_TH0_3_UPPER;
  ADC1->TH4_7_LOWER.reg = (uint32) ADC1_TH4_7_LOWER;
  ADC1->TH4_7_UPPER.reg = (uint32) ADC1_TH4_7_UPPER;
  ADC1->PP_MAP0_3.reg = (uint32) ADC1_PP_MAP0_3;
  ADC1->PP_MAP4_7.reg = (uint32) ADC1_PP_MAP4_7;

  /* Interrupt configuration ****************************************************/
  ADC1->IRQEN_1.reg = (uint32) ADC1_IRQEN_1;
  ADC1->IRQEN_2.reg = (uint32) ADC1_IRQEN_2;

  /* Enable ADC1 ****************************************************************/
  INT_Disable_Global_Int();

  /* Enable ADC1 in Peripheral Management Register */
  SCU->PMCON.bit.ADC1_DIS = 0;
  /* Enable Measurement Core Module*/
  ADC1->CTRL3.bit.MCM_PD_N = 1;

  /* ADC1 is switched on */
  ADC1_Power_On();

  /* apply 10ms delay to give ADC1 time to turn on */
  for (i = 0; i < 20u; i++)
  {
    Delay_us(500u);
    (void)WDT1_Service();
  }

  /* clear all collected interrupt status during ADC1 startup period */
  ADC1->IRQCLR_1.reg = 0xFFFFFFFFu;
  ADC1->IRQCLR_2.reg = 0xFFFFFFFFu;

  INT_Enable_Global_Int();
}

uint32 ADC1_GetChAttFactor(uint8 channel)
{
  uint32 fact;

  if (channel < 2u)
  {
    /* fs = Vref_in_mV / correction_factor / full_scale_bits * 1024 */
    /* fs = 1211 / 0,047 / 2^10 * 1024 */
    fact = (uint32) 25766;     /* ch0-1 */
  }
  else if (channel < 6u)
  {
    /* fs = 1211 / 0,039 */
    fact = (uint32) 31051;    /* ch2-5 */
  }
  else if (channel < 13u)
  {
    /* fs = 1211 / 0,227 */
    fact = (uint32) 5335;     /* ch6-12 */
  }
  else
  {
    /* fs = 1211 / 0,352 */
    fact = (uint32) 3440;     /* ch13 */
  }
  return (fact);
}

bool ADC1_GetChResult(uint16 * pVar, uint8 channel)
{
  const volatile uint32 *pBaseAddr;
  uint32 addr;
  uint8 vf;
  bool res = false;

  addr = (uint32)&ADC1->FILT_OUT0.reg;
  
  if (channel < 12u)
  {
    addr += (uint32)channel * 4u;
  }
  else if (channel < 13u)
  {
    addr += (uint32)&ADC1->FILT_OUT12.reg - (uint32)&ADC1->FILT_OUT0.reg;
  }
  else
  {
   addr += (uint32)&ADC1->FILT_OUT13.reg - (uint32)&ADC1->FILT_OUT0.reg;
  }

  /* violation: cast from unsigned int to pointer [MISRA Rule 45]*/
  pBaseAddr = (volatile uint32 *) addr;
  
  /* Pos-/Msk-Fields are taken from Channel0, these values are the same for each result register */
  vf = u1_Field_Rd32(pBaseAddr, (uint8)ADC1_FILT_OUT0_VF0_Pos, ADC1_FILT_OUT0_VF0_Msk);

  /* update the value only if there is valid data in result register */
  if (vf == (uint8)1)
  {
    /* Pos-/Msk-Fields are taken from Channel0, these values are the same for each result register */
    *pVar = u16_Field_Rd32(pBaseAddr, (uint8)ADC1_FILT_OUT0_FILT_OUT_CH0_Pos, ADC1_FILT_OUT0_FILT_OUT_CH0_Msk) / 4u;
    res = true;
  }
  return (res);
} /* End of ADC1_GetChResult */

bool ADC1_GetChResult_mV(uint16 * pVar_mV, uint8 channel)
{
  uint16 var;
  uint32 fs;
  bool result_valid;

  result_valid = ADC1_GetChResult(&var, channel);
  if (result_valid == true)
  {
    if(var > 0u)
    {
      fs = ADC1_GetChAttFactor(channel);
      *pVar_mV = (uint16) (((var * fs) - (fs >> 1u)) >> 10u);
    }
    else
    {
      *pVar_mV = 0u;
    }
  }
  return (result_valid);
}

bool ADC1_GetEIMResult(uint16 * pVar)
{
  uint8 vf;
  bool res;
  res = false;

  vf = u1_Field_Rd32(&ADC1->FILT_OUTEIM.reg, (uint8)ADC1_FILT_OUTEIM_VF_EIM_Pos, ADC1_FILT_OUTEIM_VF_EIM_Msk);
  
  if (vf == (uint8)1)
  {
    *pVar = u16_Field_Rd32(&ADC1->FILT_OUTEIM.reg, (uint8)ADC1_FILT_OUTEIM_FILT_OUT_EIM_Pos, ADC1_FILT_OUTEIM_FILT_OUT_EIM_Msk) / 4u;
    res = true;
  }
  return (res);
} /* End of ADC1_GetEIMResult */

bool ADC1_GetEIMResult_mV(uint16 * pVar_mV)
{
  uint16 var;
  uint32 fs;
  bool result_valid;

  result_valid = ADC1_GetEIMResult(&var);
  
  if (result_valid == true)
  {
    if(var > 0u)
    {
      fs = ADC1_GetChAttFactor(ADC1_EIM_Channel_Read());
      *pVar_mV = (uint16) (((var * fs) - (fs >> 1u)) >> 10u);
    }
    else
    {
        *pVar_mV = 0u;
    }
  }
  return (result_valid);
} /* End of ADC1_GetEIMResult */
