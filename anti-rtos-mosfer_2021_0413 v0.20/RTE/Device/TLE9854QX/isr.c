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
#include "tle_device.h"
#include "int_defines.h"
#include "isr_defines.h"

/*******************************************************************************
**                             External CallBacks                             **
*******************************************************************************/

/* GPT1u Call Backs */
#if (GPT12E_T2_INT_EN == 1u)
  extern void GPT1_T2_CALLBACK(void);
#endif /*(GPT12E_T2_INT_EN == 1u)*/
#if (GPT12E_T3_INT_EN == 1u)
  extern void GPT1_T3_CALLBACK(void);
#endif /*(GPT12E_T3_INT_EN == 1u)*/
#if (GPT12E_T4_INT_EN == 1u)
  extern void GPT1_T4_CALLBACK(void);
#endif /*(GPT12E_T4_INT_EN == 1u)*/

/* GPT2 Call Backs */
#if (GPT12E_T5_INT_EN == 1u)
  extern void GPT2_T5_CALLBACK(void);
#endif /*(GPT12E_T5_INT_EN == 1u)*/
#if (GPT12E_T6_INT_EN == 1u)
  extern void GPT2_T6_CALLBACK(void);
#endif /*(GPT12E_T6_INT_EN == 1u)*/
#if (GPT12E_CAP_INT_EN == 1u)
  extern void GPT2_CAPREL_CALLBACK(void);
#endif /*(GPT12E_CAPREL_INT_EN == 1u)*/

/* ADC2 Call Backs */
#if (ADC2_VS_UP_INT_EN == 1u)
  extern void ADC2_VS_UP_CALLBACK(void);
#endif
#if (ADC2_VS_LO_INT_EN == 1u)
  extern void ADC2_VS_LO_CALLBACK(void);
#endif
#if (ADC2_VDDEXT_UP_INT_EN == 1u)
  extern void ADC2_VDDEXT_UP_CALLBACK(void);
#endif
#if (ADC2_VDDEXT_LO_INT_EN == 1u)
  extern void ADC2_VDDEXT_LO_CALLBACK(void);
#endif
#if (ADC2_VDDP_UP_INT_EN == 1u)
  extern void ADC2_VDDP_UP_CALLBACK(void);
#endif
#if (ADC2_VDDP_LO_INT_EN == 1u)
  extern void ADC2_VDDP_LO_CALLBACK(void);
#endif
#if (ADC2_VBG_UP_INT_EN == 1u)
  extern void ADC2_VBG_UP_CALLBACK(void);
#endif
#if (ADC2_VBG_LO_INT_EN == 1u)
  extern void ADC2_VBG_LO_CALLBACK(void);
#endif
#if (ADC2_VDDC_UP_INT_EN == 1u)
  extern void ADC2_VDDC_UP_CALLBACK(void);
#endif
#if (ADC2_VDDC_LO_INT_EN == 1u)
  extern void ADC2_VDDC_LO_CALLBACK(void);
#endif
#if (ADC2_SYS_TEMP_UP_INT_EN == 1u)
  extern void ADC2_SYS_TEMP_UP_CALLBACK(void);
#endif
#if (ADC2_SYS_TEMP_LO_INT_EN == 1u)
  extern void ADC2_SYS_TEMP_LO_CALLBACK(void);
#endif
#if (ADC2_VSD_UP_INT_EN == 1u)
  extern void ADC2_VSD_UP_CALLBACK(void);
#endif
#if (ADC2_VSD_LO_INT_EN == 1u)
  extern void ADC2_VSD_LO_CALLBACK(void);
#endif
#if (ADC2_VCP_UP_INT_EN == 1u)
  extern void ADC2_VCP_UP_CALLBACK(void);
#endif
#if (ADC2_VCP_LO_INT_EN == 1u)
  extern void ADC2_VCP_LO_CALLBACK(void);
#endif
#if (ADC2_CP_TEMP_UP_INT_EN == 1u)
  extern void ADC2_CP_TEMP_UP_CALLBACK(void);
#endif
#if (ADC2_CP_TEMP_LO_INT_EN == 1u)
  extern void ADC2_CP_TEMP_LO_CALLBACK(void);
#endif

/* ADC1u Call Backs */
#if (ADC1_CH0_INT_EN == 1u)
  extern void ADC1_CH0_CALLBACK(void);
#endif /*(ADC1_CH0_INT_EN == 1u)*/
#if (ADC1_CH1_INT_EN == 1u)
  extern void ADC1_CH1_CALLBACK(void);
#endif /*(ADC1_CH1_INT_EN == 1u)*/
#if (ADC1_CH2_INT_EN == 1u)
  extern void ADC1_CH2_CALLBACK(void);
#endif /*(ADC1_CH2_INT_EN == 1u)*/
#if (ADC1_CH3_INT_EN == 1u)
  extern void ADC1_CH3_CALLBACK(void);
#endif /*(ADC1_CH3_INT_EN == 1u)*/
#if (ADC1_CH4_INT_EN == 1u)
  extern void ADC1_CH4_CALLBACK(void);
#endif /*(ADC1_CH4_INT_EN == 1u)*/
#if (ADC1_CH5_INT_EN == 1u)
  extern void ADC1_CH5_CALLBACK(void);
#endif /*(ADC1_CH5_INT_EN == 1u)*/
#if (ADC1_CH6_INT_EN == 1u)
  extern void ADC1_CH6_CALLBACK(void);
#endif /*(ADC1_CH6_INT_EN == 1u)*/
#if (ADC1_CH7_INT_EN == 1u)
  extern void ADC1_CH7_CALLBACK(void);
#endif /*(ADC1_CH7_INT_EN == 1u)*/
#if (ADC1_CH8_INT_EN == 1u)
  extern void ADC1_CH8_CALLBACK(void);
#endif /*(ADC1_CH8_INT_EN == 1u)*/
#if (ADC1_CH9_INT_EN == 1u)
  extern void ADC1_CH9_CALLBACK(void);
#endif /*(ADC1_CH9_INT_EN == 1u)*/
//#if (ADC1_CH10_INT_EN == 1u)
//  extern void ADC1_CH10_CALLBACK(void);
//#endif /*(ADC1_CH10_INT_EN == 1u)*/
//#if (ADC1_CH11_INT_EN == 1u)
//  extern void ADC1_CH11_CALLBACK(void);
//#endif /*(ADC1_CH11_INT_EN == 1u)*/
#if (ADC1_CH12_INT_EN == 1u)
  extern void ADC1_CH12_CALLBACK(void);
#endif /*(ADC1_CH12_INT_EN == 1u)*/
#if (ADC1_CH13_INT_EN == 1u)
  extern void ADC1_CH13_CALLBACK(void);
#endif /*(ADC1_CH13_INT_EN == 1u)*/
#if (ADC1_EIM_INT_EN == 1u)
  extern void ADC1_EIM_CALLBACK(void);
#endif /*(ADC1_EIM_INT_EN == 1u)*/
#if (ADC1_ESM_INT_EN == 1u)
  extern void ADC1_ESM_CALLBACK(void);
#endif /*(ADC1_ESM_INT_EN == 1u)*/
#if (ADC1_DU1UP_INT_EN == 1u)
  extern void ADC1_DU1UP_CALLBACK(void);
#endif /*(ADC1_DU1UP_INT_EN == 1u)*/
#if (ADC1_DU1LO_INT_EN == 1u)
  extern void ADC1_DU1LO_CALLBACK(void);
#endif /*(ADC1_DU1LO_INT_EN == 1u)*/
#if (ADC1_PP_CH0_UP_INT_EN == 1u)
  extern void ADC1_PP_CH0_UP_CALLBACK(void);
#endif /*(ADC1_PP_CH0_UP_INT_EN == 1u)*/
#if (ADC1_PP_CH0_LO_INT_EN == 1u)
  extern void ADC1_PP_CH0_LO_CALLBACK(void);
#endif /*(ADC1_PP_CH0_LO_INT_EN == 1u)*/
#if (ADC1_PP_CH1_UP_INT_EN == 1u)
  extern void ADC1_PP_CH1_UP_CALLBACK(void);
#endif /*(ADC1_PP_CH1_UP_INT_EN == 1u)*/
#if (ADC1_PP_CH1_LO_INT_EN == 1u)
  extern void ADC1_PP_CH1_LO_CALLBACK(void);
#endif /*(ADC1_PP_CH1_LO_INT_EN == 1u)*/
#if (ADC1_PP_CH2_UP_INT_EN == 1u)
  extern void ADC1_PP_CH2_UP_CALLBACK(void);
#endif /*(ADC1_PP_CH2_UP_INT_EN == 1u)*/
#if (ADC1_PP_CH2_LO_INT_EN == 1u)
  extern void ADC1_PP_CH2_LO_CALLBACK(void);
#endif /*(ADC1_PP_CH2_LO_INT_EN == 1u)*/
#if (ADC1_PP_CH3_UP_INT_EN == 1u)
  extern void ADC1_PP_CH3_UP_CALLBACK(void);
#endif /*(ADC1_PP_CH3_UP_INT_EN == 1u)*/
#if (ADC1_PP_CH3_LO_INT_EN == 1u)
  extern void ADC1_PP_CH3_LO_CALLBACK(void);
#endif /*(ADC1_PP_CH3_LO_INT_EN == 1u)*/
#if (ADC1_PP_CH4_UP_INT_EN == 1u)
  extern void ADC1_PP_CH4_UP_CALLBACK(void);
#endif /*(ADC1_PP_CH4_UP_INT_EN == 1u)*/
#if (ADC1_PP_CH4_LO_INT_EN == 1u)
  extern void ADC1_PP_CH4_LO_CALLBACK(void);
#endif /*(ADC1_PP_CH4_LO_INT_EN == 1u)*/
#if (ADC1_PP_CH5_UP_INT_EN == 1u)
  extern void ADC1_PP_CH5_UP_CALLBACK(void);
#endif /*(ADC1_PP_CH5_UP_INT_EN == 1u)*/
#if (ADC1_PP_CH5_LO_INT_EN == 1u)
  extern void ADC1_PP_CH5_LO_CALLBACK(void);
#endif /*(ADC1_PP_CH5_LO_INT_EN == 1u)*/
#if (ADC1_PP_CH6_UP_INT_EN == 1u)
  extern void ADC1_PP_CH6_UP_CALLBACK(void);
#endif /*(ADC1_PP_CH6_UP_INT_EN == 1u)*/
#if (ADC1_PP_CH6_LO_INT_EN == 1u)
  extern void ADC1_PP_CH6_LO_CALLBACK(void);
#endif /*(ADC1_PP_CH6_LO_INT_EN == 1u)*/
#if (ADC1_PP_CH7_UP_INT_EN == 1u)
  extern void ADC1_PP_CH7_UP_CALLBACK(void);
#endif /*(ADC1_PP_CH7_UP_INT_EN == 1u)*/
#if (ADC1_PP_CH7_LO_INT_EN == 1u)
  extern void ADC1_PP_CH7_LO_CALLBACK(void);
#endif /*(ADC1_PP_CH7_LO_INT_EN == 1u)*/

/* CCU6 Call Backs*/
#if (CCU6_CH0_CM_R_INT_EN == 1u)
  extern void CCU6_CH0_CM_R_CALLBACK(void);
#endif
#if (CCU6_CH0_CM_F_INT_EN == 1u)
  extern void CCU6_CH0_CM_F_CALLBACK(void);
#endif
#if (CCU6_CH1_CM_R_INT_EN == 1u)
  extern void CCU6_CH1_CM_R_CALLBACK(void);
#endif
#if (CCU6_CH1_CM_F_INT_EN == 1u)
  extern void CCU6_CH1_CM_F_CALLBACK(void);
#endif
#if (CCU6_CH2_CM_R_INT_EN == 1u)
  extern void CCU6_CH2_CM_R_CALLBACK(void);
#endif
#if (CCU6_CH2_CM_F_INT_EN == 1u)
  extern void CCU6_CH2_CM_F_CALLBACK(void);
#endif
#if (CCU6_T12_OM_INT_EN == 1u)
  extern void CCU6_T12_OM_CALLBACK(void);
#endif
#if (CCU6_T12_PM_INT_EN == 1u)
  extern void CCU6_T12_PM_CALLBACK(void);
#endif
#if (CCU6_T13_CM_INT_EN == 1u)
  extern void CCU6_T13_CM_CALLBACK(void);
#endif
#if (CCU6_T13_PM_INT_EN == 1u)
  extern void CCU6_T13_PM_CALLBACK(void);
#endif
#if (CCU6_TRAP_INT_EN == 1u)
  extern void CCU6_TRAP_CALLBACK(void);
#endif
#if (CCU6_CHE_INT_EN == 1u)
  extern void CCU6_CORRECT_HALL_CALLBACK(void);
#endif
#if (CCU6_WHE_INT_EN == 1u)
  extern void CCU6_WRONG_HALL_CALLBACK(void);
#endif
#if (CCU6_MCM_STR_INT_EN == 1u)
  extern void CCU6_MCM_STR_CALLBACK(void);
#endif

/* SSC1 Call Backs*/
#if (SSC1_RX_INT_EN == 1u)
  extern void SSC1_RX_CALLBACK(void);
#endif
#if (SSC1_TX_INT_EN == 1u)
  extern void SSC1_TX_CALLBACK(void);
#endif
#if (SSC1_ERR_INT_EN == 1u)
  extern void SSC1_ERR_CALLBACK(void);
#endif

/* SSC2 Call Backs*/
#if (SSC2_RX_INT_EN == 1u)
  extern void SSC2_RX_CALLBACK(void);
#endif
#if (SSC2_TX_INT_EN == 1u)
  extern void SSC2_TX_CALLBACK(void);
#endif
#if (SSC2_ERR_INT_EN == 1u)
  extern void SSC2_ERR_CALLBACK(void);
#endif

/* UART1/TIMER2/LIN Call Backs*/
#if (UART1_RX_INT_EN == 1u)
  extern void UART1_RX_CALLBACK(void);
#endif
#if (UART1_TX_INT_EN == 1u)
  extern void UART1_TX_CALLBACK(void);
#endif
#if (TIMER2_TF2_INT_EN == 1u)
  extern void TIMER2_TF2_CALLBACK(void);
#endif
#if (TIMER2_EXF2_INT_EN == 1u)
  extern void TIMER2_EXF2_CALLBACK(void);
#endif
#if (LIN_OC_INT_EN == 1u)
  extern void LIN_OC_CALLBACK(void);
#endif
#if (LIN_OT_INT_EN == 1u)
  extern void LIN_OT_CALLBACK(void);
#endif
#if (LIN_TMOUT_INT_EN == 1u)
  extern void LIN_TMOUT_CALLBACK(void);
#endif
#if (LIN_M_SM_ERR_INT_EN == 1u)
  extern void LIN_M_SM_ERR_CALLBACK(void);
#endif
#if (LIN_EOF_INT_EN == 1u)
  extern void LIN_EOF_CALLBACK(void);
#endif
#if (LIN_ERR_INT_EN == 1u)
  extern void LIN_ERR_CALLBACK(void);
#endif

/* UART2/TIMER21/EXINT2 Call Backs*/
#if (UART2_RX_INT_EN == 1u)
  extern void UART2_RX_CALLBACK(void);
#endif
#if (UART2_TX_INT_EN == 1u)
  extern void UART2_TX_CALLBACK(void);
#endif
#if (TIMER21_TF2_INT_EN == 1u)
  extern void TIMER21_TF2_CALLBACK(void);
#endif
#if (TIMER21_EXF2_INT_EN == 1u)
  extern void TIMER21_EXF2_CALLBACK(void);
#endif
#if (SCU_EXINT2_RISING_INT_EN == 1u)
  extern void EXINT2_RISING_CALLBACK(void);
#endif
#if (SCU_EXINT2_FALLING_INT_EN == 1u)
  extern void EXINT2_FALLING_CALLBACK(void);
#endif

/* EXINT0u Call Backs*/
#if (SCU_EXINT0_RISING_INT_EN == 1u)
  extern void EXINT0_RISING_CALLBACK(void);
#endif
#if (SCU_EXINT0_FALLING_INT_EN == 1u)
  extern void EXINT0_FALLING_CALLBACK(void);
#endif

/* EXINT1u Call Backs*/
#if (SCU_EXINT1_RISING_INT_EN == 1u)
  extern void EXINT1_RISING_CALLBACK(void);
#endif
#if (SCU_EXINT1_FALLING_INT_EN == 1u)
  extern void EXINT1_FALLING_CALLBACK(void);
#endif

/* WAKEUP Call Backs*/
#if (PMU_WAKEUP_INT_EN == 1u)
  extern void PMU_WAKEUP_CALLBACK(void);
#endif

/* MATH DIV Call Backs*/
#if (MATH_DIVERR_INT_EN == 1u)
  extern void MATH_DIVERR_CALLBACK(void);
#endif
#if (MATH_DIVEOC_INT_EN == 1u)
  extern void MATH_DIVEOC_CALLBACK(void);
#endif

/* MONx Call Backs*/
#if (MON1_RISING_INT_EN == 1u)
  extern void MON1_RISING_CALLBACK(void);
#endif
#if (MON1_FALLING_INT_EN == 1u)
  extern void MON1_FALLING_CALLBACK(void);
#endif
#if (MON2_RISING_INT_EN == 1u)
  extern void MON2_RISING_CALLBACK(void);
#endif
#if (MON2_FALLING_INT_EN == 1u)
  extern void MON2_FALLING_CALLBACK(void);
#endif
#if (MON3_RISING_INT_EN == 1u)
  extern void MON3_RISING_CALLBACK(void);
#endif
#if (MON3_FALLING_INT_EN == 1u)
  extern void MON3_FALLING_CALLBACK(void);
#endif
#if (MON4_RISING_INT_EN == 1u)
  extern void MON4_RISING_CALLBACK(void);
#endif
#if (MON4_FALLING_INT_EN == 1u)
  extern void MON4_FALLING_CALLBACK(void);
#endif

/* BDRV Call Backs*/
#if (BDRV_HS1_OC_INT_EN == 1u)
  extern void BDRV_HS1_OC_CALLBACK(void);
#endif
#if (BDRV_LS1_OC_INT_EN == 1u)
  extern void BDRV_LS1_OC_CALLBACK(void);
#endif
#if (BDRV_HS2_OC_INT_EN == 1u)
  extern void BDRV_HS2_OC_CALLBACK(void);
#endif
#if (BDRV_LS2_OC_INT_EN == 1u)
  extern void BDRV_LS2_OC_CALLBACK(void);
#endif
#if (BDRV_HS1_DS_INT_EN == 1u)
  extern void BDRV_HS1_DS_CALLBACK(void);
#endif
#if (BDRV_LS1_DS_INT_EN == 1u)
  extern void BDRV_LS1_DS_CALLBACK(void);
#endif
#if (BDRV_HS2_DS_INT_EN == 1u)
  extern void BDRV_HS2_DS_CALLBACK(void);
#endif
#if (BDRV_LS2_DS_INT_EN == 1u)
  extern void BDRV_LS2_DS_CALLBACK(void);
#endif
#if (BDRV_SEQ_ERR_INT_EN == 1u)
  extern void BDRV_SEQ_ERR_CALLBACK(void);
#endif
#if (BDRV_VCP_LO2_INT_EN == 1u)
  extern void BDRV_VCP_LO_CALLBACK(void);
#endif

/* HS Call Backs*/
#if (HS_HS1_OT_INT_EN == 1u)
  extern void HS_HS1_OT_CALLBACK(void);
#endif
#if (HS_HS1_OL_INT_EN == 1u)
  extern void HS_HS1_OL_CALLBACK(void);
#endif
#if (HS_HS1_OC_INT_EN == 1u)
  extern void HS_HS1_OC_CALLBACK(void);
#endif

/* NMI Call Backs */
#if (SCU_NMI_WDT_INT_EN == 1u)
  extern void SCU_NMI_WDT_CALLBACK(void);
#endif
#if (SCU_NMI_PLL_INT_EN == 1u)
  extern void SCU_NMI_PLL_CALLBACK(void);
#endif
#if (SCU_NMI_OWD_INT_EN == 1u)
  extern void SCU_NMI_OWD_CALLBACK(void);
#endif
#if (SCU_NMI_MAP_INT_EN == 1u)
  extern void SCU_NMI_MAP_CALLBACK(void);
#endif
#if (SCU_NMI_STOF_INT_EN == 1u)
  extern void SCU_NMI_STOF_CALLBACK(void);
#endif

/* NMI ECC Error Call Backs*/
#if (SCU_ECC_RAM_DB_INT_EN == 1u)
  extern void SCU_ECC_RAM_DB_CALLBACK(void);
#endif
#if (SCU_ECC_NVM_DB_INT_EN == 1u)
  extern void SCU_ECC_NVM_DB_CALLBACK(void);
#endif

/* NMI Supply Error Call Backs*/
#if (PMU_VDDC_OV_INT_EN == 1u)
  extern void PMU_VDDC_OV_CALLBACK(void);
#endif /*(PMU_VDDC_OV_INT_EN == 1u)*/
#if (PMU_VDDC_OL_INT_EN == 1u)
  extern void PMU_VDDC_OL_CALLBACK(void);
#endif /*(PMU_VDDC_OL_INT_EN == 1u)*/
#if (PMU_VDDP_OV_INT_EN == 1u)
  extern void PMU_VDDP_OV_CALLBACK(void);
#endif /*(PMU_VDDP_OV_INT_EN == 1u)*/
#if (PMU_VDDP_OL_INT_EN == 1u)
  extern void PMU_VDDP_OL_CALLBACK(void);
#endif /*(PMU_VDDP_OL_INT_EN == 1u)*/
#if (PMU_VDDEXT_UV_INT_EN == 1u)
  extern void PMU_VDDEXT_UV_CALLBACK(void);
#endif /*(PMU_VDDEXT_UV_INT_EN == 1u)*/
#if (PMU_VDDEXT_OT_INT_EN == 1u)
  extern void PMU_VDDEXT_OT_CALLBACK(void);
#endif /*(PMU_VDDEXT_OT_INT_EN == 1u)*/
#if (PMU_PMU_OT_INT_EN == 1u)
  extern void PMU_PMU_OT_CALLBACK(void);
#endif /*(PMU_PMU_OT_INT_EN == 1u)*/

/* Core Exceptions */
#if (CPU_HARDFAULT_EN == 1u)
  extern void CPU_HARDFAULT_CALLBACK(void);
#endif
#if (CPU_SYSTICK_EN == 1u)
  extern void CPU_SYSTICK_CALLBACK(void);
#endif

#define CCU6_SR0     0u
#define CCU6_SR1     1u
#define CCU6_SR2     2u
#define CCU6_SR3     3u
#define CCU6_INP_Msk 3u

/*******************************************************************************
**                         Global Function Definitions                        **
*******************************************************************************/

/*******************************************************************************
**                      GPT1 ISR                                              **
*******************************************************************************/
#if  ((GPT12E_T2_INT_EN == 1u)  || \
      (GPT12E_T3_INT_EN == 1u)  || \
      (GPT12E_T4_INT_EN == 1u))
void GPT1_IRQHandler(void)
{
#if (GPT12E_T2_INT_EN == 1u)
  /* GPT1u - T2 Interrupt */
  if (u1_Field_Rd32(&SCU->GPT12IEN.reg, (uint8)SCU_GPT12IEN_T2IE_Pos, SCU_GPT12IEN_T2IE_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&SCU->GPT12IRC.reg, (uint8)SCU_GPT12IRC_GPT1T2_Pos, SCU_GPT12IRC_GPT1T2_Msk) == (uint8)1)
    {
      GPT1_T2_CALLBACK();
      GPT12E_T2_Int_Clr();
    }
  }
#endif /*(GPT12E_T2_INT_EN == 1u)*/

#if (GPT12E_T3_INT_EN == 1u)
  /* GPT1u - T3 Interrupt */
  if (u1_Field_Rd32(&SCU->GPT12IEN.reg, (uint8)SCU_GPT12IEN_T3IE_Pos, SCU_GPT12IEN_T3IE_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&SCU->GPT12IRC.reg, (uint8)SCU_GPT12IRC_GPT1T3_Pos, SCU_GPT12IRC_GPT1T3_Msk) == (uint8)1)
    {
      GPT1_T3_CALLBACK();
      GPT12E_T3_Int_Clr();
    }
  }
#endif /*(GPT12E_T3_INT_EN == 1u)*/

#if (GPT12E_T4_INT_EN == 1u)
  /* GPT1u - T4 Interrupt */
  if (u1_Field_Rd32(&SCU->GPT12IEN.reg, (uint8)SCU_GPT12IEN_T4IE_Pos, SCU_GPT12IEN_T4IE_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&SCU->GPT12IRC.reg, (uint8)SCU_GPT12IRC_GPT1T4_Pos, SCU_GPT12IRC_GPT1T4_Msk) == (uint8)1)
    {
      GPT1_T4_CALLBACK();
      GPT12E_T4_Int_Clr();
    }
  }
#endif /*(GPT12E_T4_INT_EN == 1u)*/
}
#endif

/*******************************************************************************
**                      GPT2 ISR                                              **
*******************************************************************************/
#if  ((GPT12E_T5_INT_EN == 1u)  || \
      (GPT12E_T6_INT_EN == 1u)  || \
      (GPT12E_CAP_INT_EN == 1u))
void GPT2_IRQHandler(void)
{
#if (GPT12E_T5_INT_EN == 1u)
  /* GPT2 - T5 Interrupt */
  if (u1_Field_Rd32(&SCU->GPT12IEN.reg, (uint8)SCU_GPT12IEN_T5IE_Pos, SCU_GPT12IEN_T5IE_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&SCU->GPT12IRC.reg, (uint8)SCU_GPT12IRC_GPT2T5_Pos, SCU_GPT12IRC_GPT2T5_Msk) == (uint8)1)
    {
      GPT2_T5_CALLBACK();
      GPT12E_T5_Int_Clr();
    }
  }
#endif /*(GPT12E_T5_INT_EN == 1u)*/

#if (GPT12E_T6_INT_EN == 1u)
  /* GPT2 - T6 Interrupt */
  if (u1_Field_Rd32(&SCU->GPT12IEN.reg, (uint8)SCU_GPT12IEN_T6IE_Pos, SCU_GPT12IEN_T6IE_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&SCU->GPT12IRC.reg, (uint8)SCU_GPT12IRC_GPT2T6_Pos, SCU_GPT12IRC_GPT2T6_Msk) == (uint8)1)
    {
      GPT2_T6_CALLBACK();
      GPT12E_T6_Int_Clr();
    }
  }
#endif /*(GPT12E_T6_INT_EN == 1u)*/

#if (GPT12E_CAP_INT_EN == 1u)
  /* GPT2 - CAPREL Interrupt */
  if (u1_Field_Rd32(&SCU->GPT12IEN.reg, (uint8)SCU_GPT12IEN_CRIE_Pos, SCU_GPT12IEN_CRIE_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&SCU->GPT12IRC.reg, (uint8)SCU_GPT12IRC_GPT12CR_Pos, SCU_GPT12IRC_GPT12CR_Msk) == (uint8)1)
    {
      GPT2_CAPREL_CALLBACK();
      GPT12E_CapRel_Int_Clr();
    }
  }
#endif /*(GPT12E_CAPREL_INT_EN == 1u)*/
}
#endif

/*******************************************************************************
**                      ADC2 ISR                                              **
*******************************************************************************/
#if ((ADC2_VBG_UP_INT_EN == 1u)  || \
     (ADC2_VBG_LO_INT_EN == 1u))
void ADC2_IRQHandler(void)
{
#if (ADC2_VBG_UP_INT_EN == 1u)
  if (u1_Field_Rd32(&SCUPM->SYS_IRQ_CTRL.reg, (uint8)SCUPM_SYS_IRQ_CTRL_VREF1V2_OV_IE_Pos, SCUPM_SYS_IRQ_CTRL_VREF1V2_OV_IE_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&SCUPM->SYS_IS.reg, (uint8)SCUPM_SYS_IS_VREF1V2_OV_IS_Pos, SCUPM_SYS_IS_VREF1V2_OV_IS_Msk) == (uint8)1)
    {
      ADC2_VBG_UP_CALLBACK();
      ADC2_VBG_OV_Int_Clr();
    }
  }
#endif /*(ADC2_VBG_UP_INT_EN == 1u)*/

#if (ADC2_VBG_LO_INT_EN == 1u)
  if (u1_Field_Rd32(&SCUPM->SYS_IRQ_CTRL.reg, (uint8)SCUPM_SYS_IRQ_CTRL_VREF1V2_UV_IE_Pos, SCUPM_SYS_IRQ_CTRL_VREF1V2_UV_IE_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&SCUPM->SYS_IS.reg, (uint8)SCUPM_SYS_IS_VREF1V2_UV_IS_Pos, SCUPM_SYS_IS_VREF1V2_UV_IS_Msk) == (uint8)1)
    {
      ADC2_VBG_LO_CALLBACK();
      ADC2_VBG_UV_Int_Clr();
    }
  }
#endif /*(ADC2_VBG_LO_INT_EN == 1u)*/
}
#endif

/*******************************************************************************
**                      ADC1 ISR                                              **
*******************************************************************************/
#if    ((ADC1_CH0_INT_EN == 1u)       || \
        (ADC1_CH1_INT_EN == 1u)       || \
        (ADC1_CH2_INT_EN == 1u)       || \
        (ADC1_CH3_INT_EN == 1u)       || \
        (ADC1_CH4_INT_EN == 1u)       || \
        (ADC1_CH5_INT_EN == 1u)       || \
        (ADC1_CH6_INT_EN == 1u)       || \
        (ADC1_CH7_INT_EN == 1u)       || \
        (ADC1_CH8_INT_EN == 1u)       || \
        (ADC1_CH9_INT_EN == 1u)       || \
        (ADC1_CH12_INT_EN == 1u)      || \
        (ADC1_CH13_INT_EN == 1u)      || \
        (ADC1_EIM_INT_EN == 1u)       || \
        (ADC1_ESM_INT_EN == 1u))

void ADC1_IRQHandler(void)
{
#if (ADC1_CH0_INT_EN == 1u)
  /* ADC1 - Ch0 Interrupt */
  if (u1_Field_Rd32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH0_IEN_Pos, ADC1_IRQEN_1_IIR_CH0_IEN_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&ADC1->IRQS_1.reg, (uint8)ADC1_IRQS_1_IIR_CH0_IS_Pos, ADC1_IRQS_1_IIR_CH0_IS_Msk) == (uint8)1)
    {
      ADC1_CH0_CALLBACK();
      ADC1_Ch0_Int_Clr();
    }
  }
#endif /*(ADC1_CH0_INT_EN == 1u) */

#if (ADC1_CH1_INT_EN == 1u)
  /* ADC1 - Ch1 Interrupt */
  if (u1_Field_Rd32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_VS_IEN_Pos, ADC1_IRQEN_1_VS_IEN_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&ADC1->IRQS_1.reg, (uint8)ADC1_IRQS_1_VS_IS_Pos, ADC1_IRQS_1_VS_IS_Msk) == (uint8)1)
    {
      ADC1_CH1_CALLBACK();
      ADC1_Ch1_Int_Clr();
    }
  }
#endif /*(ADC1_CH1_INT_EN == 1u) */

#if (ADC1_CH2_INT_EN == 1u)
  /* ADC1 - Ch2 Interrupt */
  if (u1_Field_Rd32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH2_IEN_Pos, ADC1_IRQEN_1_IIR_CH2_IEN_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&ADC1->IRQS_1.reg, (uint8)ADC1_IRQS_1_IIR_CH2_IS_Pos, ADC1_IRQS_1_IIR_CH2_IS_Msk) == (uint8)1)
    {
      ADC1_CH2_CALLBACK();
      ADC1_Ch2_Int_Clr();
    }
  }
#endif /*(ADC1_CH2_INT_EN == 1u) */

#if (ADC1_CH3_INT_EN == 1u)
  /* ADC1 - Ch3 Interrupt */
  if (u1_Field_Rd32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH3_IEN_Pos, ADC1_IRQEN_1_IIR_CH3_IEN_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&ADC1->IRQS_1.reg, (uint8)ADC1_IRQS_1_IIR_CH3_IS_Pos, ADC1_IRQS_1_IIR_CH3_IS_Msk) == (uint8)1)
    {
      ADC1_CH3_CALLBACK();
      ADC1_Ch3_Int_Clr();
    }
  }
#endif /*(ADC1_CH3_INT_EN == 1u) */

#if (ADC1_CH4_INT_EN == 1u)
  /* ADC1 - Ch4 Interrupt */
  if (u1_Field_Rd32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH4_IEN_Pos, ADC1_IRQEN_1_IIR_CH4_IEN_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&ADC1->IRQS_1.reg, (uint8)ADC1_IRQS_1_IIR_CH4_IS_Pos, ADC1_IRQS_1_IIR_CH4_IS_Msk) == (uint8)1)
    {
      ADC1_CH4_CALLBACK();
      ADC1_Ch4_Int_Clr();
    }
  }
#endif /*(ADC1_CH4_INT_EN == 1u) */

#if (ADC1_CH5_INT_EN == 1u)
  /* ADC1 - Ch5 Interrupt */
  if (u1_Field_Rd32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH5_IEN_Pos, ADC1_IRQEN_1_IIR_CH5_IEN_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&ADC1->IRQS_1.reg, (uint8)ADC1_IRQS_1_IIR_CH5_IS_Pos, ADC1_IRQS_1_IIR_CH5_IS_Msk) == (uint8)1)
    {
      ADC1_CH5_CALLBACK();;
      ADC1_Ch5_Int_Clr();
    }
  }
#endif /*(ADC1_CH5_INT_EN == 1u) */

#if (ADC1_CH6_INT_EN == 1u)
  /* ADC1 - Ch6 Interrupt */
  if (u1_Field_Rd32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH6_IEN_Pos, ADC1_IRQEN_1_IIR_CH6_IEN_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&ADC1->IRQS_1.reg, (uint8)ADC1_IRQCLR_1_IIR_CH6_ISC_Pos, ADC1_IRQCLR_1_IIR_CH6_ISC_Msk) == (uint8)1)
    {
      ADC1_CH6_CALLBACK();
      ADC1_Ch6_Int_Clr();
    }
  }
#endif /*(ADC1_CH6_INT_EN == 1u) */

#if (ADC1_CH7_INT_EN == 1u)
  /* ADC1 - Ch7 Interrupt */
  if (u1_Field_Rd32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH7_IEN_Pos, ADC1_IRQEN_1_IIR_CH7_IEN_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&ADC1->IRQS_1.reg, (uint8)ADC1_IRQS_1_IIR_CH7_IS_Pos, ADC1_IRQS_1_IIR_CH7_IS_Msk) == (uint8)1)
    {
      ADC1_CH7_CALLBACK();
      ADC1_Ch7_Int_Clr();
    }
  }
#endif /*(ADC1_CH7_INT_EN == 1u) */

#if (ADC1_CH8_INT_EN == 1u)
  /* ADC1 - Ch8 Interrupt */
  if (u1_Field_Rd32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH8_IEN_Pos, ADC1_IRQEN_1_IIR_CH8_IEN_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&ADC1->IRQS_1.reg, (uint8)ADC1_IRQS_1_IIR_CH8_IS_Pos, ADC1_IRQS_1_IIR_CH8_IS_Msk) == (uint8)1)
    {
      ADC1_CH8_CALLBACK();
      ADC1_Ch8_Int_Clr();
    }
  }
#endif /*(ADC1_CH8_INT_EN == 1u) */

#if (ADC1_CH9_INT_EN == 1u)
  /* ADC1 - Ch9 Interrupt */
  if (u1_Field_Rd32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH9_IEN_Pos, ADC1_IRQEN_1_IIR_CH9_IEN_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&ADC1->IRQS_1.reg, (uint8)ADC1_IRQS_1_IIR_CH9_IS_Pos, ADC1_IRQS_1_IIR_CH9_IS_Msk) == (uint8)1)
    {
      ADC1_CH9_CALLBACK();
      ADC1_Ch9_Int_Clr();
    }
  }
#endif /*(ADC1_CH9_INT_EN == 1u) */

#if 0
  #if (ADC1_CH10_INT_EN == 1u)
    /* ADC1 - Ch10 Interrupt */
    if (u1_Field_Rd32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH10_IEN_Pos, ADC1_IRQEN_1_IIR_CH10_IEN_Msk) == (uint8)1)
    {
      if (u1_Field_Rd32(&ADC1->IRQS_1.reg, (uint8)ADC1_IRQS_1_IIR_CH10_IS_Pos, ADC1_IRQS_1_IIR_CH10_IS_Msk) == (uint8)1)
      {
        ADC1_CH10_CALLBACK();
        ADC1_Ch10_Int_Clr();
      }
    }
  #endif /*(ADC1_CH10_INT_EN == 1u) */
  
  #if (ADC1_CH11_INT_EN == 1u)
    /* ADC1 - Ch11 Interrupt */
    if (u1_Field_Rd32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH11_IEN_Pos, ADC1_IRQEN_1_IIR_CH11_IEN_Msk) == (uint8)1)
    {
      if (u1_Field_Rd32(&ADC1->IRQS_1.reg, (uint8)ADC1_IRQS_1_IIR_CH11_IS_Pos, ADC1_IRQS_1_IIR_CH11_IS_Msk) == (uint8)1)
      {
        ADC1_CH11_CALLBACK();
        ADC1_Ch11_Int_Clr();
      }
    }
  #endif /*(ADC1_CH11_INT_EN == 1u) */
#endif

#if (ADC1_CH12_INT_EN == 1u)
  /* ADC1 - Ch12 Interrupt */
  if (u1_Field_Rd32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH12_IEN_Pos, ADC1_IRQEN_1_IIR_CH12_IEN_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&ADC1->IRQS_1.reg, (uint8)ADC1_IRQS_1_IIR_CH12_IS_Pos, ADC1_IRQS_1_IIR_CH12_IS_Msk) == (uint8)1)
    {
      ADC1_CH12_CALLBACK();
      ADC1_Ch12_Int_Clr();
    }
  }
#endif /*(ADC1_CH12_INT_EN == 1u) */

#if (ADC1_CH13_INT_EN == 1u)
  /* ADC1 - Ch13 Interrupt */
  if (u1_Field_Rd32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH13_IEN_Pos, ADC1_IRQEN_1_IIR_CH13_IEN_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&ADC1->IRQS_1.reg, (uint8)ADC1_IRQS_1_IIR_CH13_IS_Pos, ADC1_IRQS_1_IIR_CH13_IS_Msk) == (uint8)1)
    {
      ADC1_CH13_CALLBACK();
      ADC1_Ch13_Int_Clr();
    }
  }
#endif /*(ADC1_CH13_INT_EN == 1u) */

#if (ADC1_EIM_INT_EN == 1u)
  /* ADC1 - EIM Interrupt */
  if (u1_Field_Rd32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_EIM_IEN_Pos, ADC1_IRQEN_1_EIM_IEN_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&ADC1->IRQS_1.reg, (uint8)ADC1_IRQS_1_EIM_IS_Pos, ADC1_IRQS_1_EIM_IS_Msk) == (uint8)1)
    {
      ADC1_EIM_CALLBACK();
      ADC1_EIM_Int_Clr();
    }
  }
#endif /*(ADC1_EIM_INT_EN == 1u) */

#if (ADC1_ESM_INT_EN == 1u)
  /* ADC1 - ESM Interrupt */
  if (u1_Field_Rd32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_ESM_IEN_Pos, ADC1_IRQEN_1_ESM_IEN_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&ADC1->IRQS_1.reg, (uint8)ADC1_IRQS_1_ESM_IS_Pos, ADC1_IRQS_1_ESM_IS_Msk) == (uint8)1)
    {
      ADC1_ESM_CALLBACK();
      ADC1_ESM_Int_Clr();
    }
  }
#endif /*(ADC1_ESM_INT_EN == 1u) */
}
#endif

/*******************************************************************************
**                      CCU6 SR0 ISR                                          **
*******************************************************************************/
#if ((CPU_NVIC_ISER & (1u << 4u)) != 0u)
void CCU6SR0_IRQHandler(void)
{
  if (u1_Field_Rd32(&SCU->IRCON4.reg, (uint8)SCU_IRCON4_CCU6SR0_Pos, SCU_IRCON4_CCU6SR0_Msk) == (uint8)1)
  {
#if (((CCU6_INP & (CCU6_INP_Msk << CCU6_INP_INPCC60_Pos)) == (CCU6_SR0 << CCU6_INP_INPCC60_Pos)) || defined(UNIT_TESTING_LV2))
#if (CCU6_CH0_CM_R_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENCC60R_Pos, (uint16)CCU6_IEN_ENCC60R_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_ICC60R_Pos, (uint16)CCU6_IS_ICC60R_Msk) == (uint8)1)
      {
        CCU6_CH0_CM_R_CALLBACK();
        CCU6_CH0_CM_R_Int_Clr();
      }
    }
#endif /*(CCU6_CH0_CM_R_INT_EN == 1u) */

#if (CCU6_CH0_CM_F_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENCC60F_Pos, (uint16)CCU6_IEN_ENCC60F_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_ICC60F_Pos, (uint16)CCU6_IS_ICC60F_Msk) == (uint8)1)
      {
        CCU6_CH0_CM_F_CALLBACK();
        CCU6_CH0_CM_F_Int_Clr();
      }
    }
#endif /*(CCU6_CH0_CM_F_INT_EN == 1u) */
#endif /*((CCU6_INP >> 0u) & 3u) == CCU6_SR0) */

#if (((CCU6_INP & (CCU6_INP_Msk << CCU6_INP_INPCC61_Pos)) == (CCU6_SR0 << CCU6_INP_INPCC61_Pos)) || defined(UNIT_TESTING_LV2))
#if (CCU6_CH1_CM_R_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENCC61R_Pos, (uint16)CCU6_IEN_ENCC61R_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_ICC61R_Pos, (uint16)CCU6_IS_ICC61R_Msk) == (uint8)1)
      {
        CCU6_CH1_CM_R_CALLBACK();
        CCU6_CH1_CM_R_Int_Clr();
      }
    }
#endif /*(CCU6_CH1_CM_R_INT_EN == 1u) */

#if (CCU6_CH1_CM_F_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENCC61F_Pos, (uint16)CCU6_IEN_ENCC61F_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_ICC61F_Pos, (uint16)CCU6_IS_ICC61F_Msk) == (uint8)1)
      {
        CCU6_CH1_CM_F_CALLBACK();
        CCU6_CH1_CM_F_Int_Clr();
      }
    }
#endif /*(CCU6_CH1_CM_F_INT_EN == 1u) */
#endif /*((CCU6_INP >> 2u) & 3u) == CCU6_SR0) */

#if (((CCU6_INP & (CCU6_INP_Msk << CCU6_INP_INPCC62_Pos)) == (CCU6_SR0 << CCU6_INP_INPCC62_Pos)) || defined(UNIT_TESTING_LV2))
#if (CCU6_CH2_CM_R_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENCC62R_Pos, (uint16)CCU6_IEN_ENCC62R_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_ICC62R_Pos, (uint16)CCU6_IS_ICC62R_Msk) == (uint8)1)
      {
        CCU6_CH2_CM_R_CALLBACK();
        CCU6_CH2_CM_R_Int_Clr();
      }
    }
#endif /*(CCU6_CH2_CM_R_INT_EN == 1u) */

#if (CCU6_CH2_CM_F_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENCC62F_Pos, (uint16)CCU6_IEN_ENCC62F_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_ICC62F_Pos, (uint16)CCU6_IS_ICC62F_Msk) == (uint8)1)
      {
        CCU6_CH2_CM_F_CALLBACK();
        CCU6_CH2_CM_F_Int_Clr();
      }
    }
#endif /*(CCU6_CH2_CM_F_INT_EN == 1u) */
#endif /*((CCU6_INP >> 4u) & 3u) == CCU6_SR0) */

#if (((CCU6_INP & (CCU6_INP_Msk << CCU6_INP_INPT12_Pos)) == (CCU6_SR0 << CCU6_INP_INPT12_Pos)) || defined(UNIT_TESTING_LV2))
#if (CCU6_T12_OM_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENT12OM_Pos, (uint16)CCU6_IEN_ENT12OM_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_T12OM_Pos, (uint16)CCU6_IS_T12OM_Msk) == (uint8)1)
      {
        CCU6_T12_OM_CALLBACK();
        CCU6_T12_OM_Int_Clr();
      }
    }
#endif /*(CCU6_T12_OM_INT_EN == 1u) */

#if (CCU6_T12_PM_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENT12PM_Pos, (uint16)CCU6_IEN_ENT12PM_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_T12PM_Pos, (uint16)CCU6_IS_T12PM_Msk) == (uint8)1)
      {
        CCU6_T12_PM_CALLBACK();
        CCU6_T12_PM_Int_Clr();
      }
    }
#endif /*(CCU6_T12_OM_INT_EN == 1u) */
#endif /*((CCU6_INP >> 10u) & 3u) == CCU6_SR0) */

#if (((CCU6_INP & (CCU6_INP_Msk << CCU6_INP_INPT13_Pos)) == (CCU6_SR0 << CCU6_INP_INPT13_Pos)) || defined(UNIT_TESTING_LV2))
#if (CCU6_T13_CM_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENT13CM_Pos, (uint16)CCU6_IEN_ENT13CM_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_T13CM_Pos, (uint16)CCU6_IS_T13CM_Msk) == (uint8)1)
      {
        CCU6_T13_CM_CALLBACK();
        CCU6_T13_CM_Int_Clr();
      }
    }
#endif /*(CCU6_T13_CM_INT_EN == 1u) */

#if (CCU6_T13_PM_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENT13PM_Pos, (uint16)CCU6_IEN_ENT13PM_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_T13PM_Pos, (uint16)CCU6_IS_T13PM_Msk) == (uint8)1)
      {
        CCU6_T13_PM_CALLBACK();
        CCU6_T13_PM_Int_Clr();
      }
    }
#endif /*(CCU6_T13_PM_INT_EN == 1u) */
#endif /*((CCU6_INP >> 12u) & 3u) == CCU6_SR0) */

#if (((CCU6_INP & (CCU6_INP_Msk << CCU6_INP_INPERR_Pos)) == (CCU6_SR0 << CCU6_INP_INPERR_Pos)) || defined(UNIT_TESTING_LV2))
#if (CCU6_TRAP_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENTRPF_Pos, (uint16)CCU6_IEN_ENTRPF_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_TRPF_Pos, (uint16)CCU6_IS_TRPF_Msk) == (uint8)1)
      {
        CCU6_TRAP_CALLBACK();
        CCU6_TRAP_Int_Clr();
      }
    }
#endif /*(CCU6_TRAP_INT_EN == 1u) */

#if (CCU6_WHE_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENWHE_Pos, (uint16)CCU6_IEN_ENWHE_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_WHE_Pos, (uint16)CCU6_IS_WHE_Msk) == (uint8)1)
      {
        CCU6_WRONG_HALL_CALLBACK();
        CCU6_WHE_Int_Clr();
      }
    }
#endif /*(CCU6_WHE_INT_EN == 1u) */
#endif /*((CCU6_INP >> 8u) & 3u) == CCU6_SR0) */

#if (((CCU6_INP & (CCU6_INP_Msk << CCU6_INP_INPCHE_Pos)) == (CCU6_SR0 << CCU6_INP_INPCHE_Pos)) || defined(UNIT_TESTING_LV2))
#if (CCU6_CHE_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENCHE_Pos, (uint16)CCU6_IEN_ENCHE_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_CHE_Pos, (uint16)CCU6_IS_CHE_Msk) == (uint8)1)
      {
        CCU6_CORRECT_HALL_CALLBACK();
        CCU6_CHE_Int_Clr();
      }
    }
#endif /*(CCU6_CHE_INT_EN == 1u) */

#if (CCU6_MCM_STR_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENSTR_Pos, (uint16)CCU6_IEN_ENSTR_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_STR_Pos, (uint16)CCU6_IS_STR_Msk) == (uint8)1)
      {
        CCU6_MCM_STR_CALLBACK();
        CCU6_STR_Int_Clr();
      }
    }
#endif /*(CCU6_MCM_STR_INT_EN == 1u) */
#endif /*((CCU6_INP >> 6u) & 3u) == CCU6_SR0) */

    Field_Wrt32(&SCU->IRCON4CLR.reg, (uint8)SCU_IRCON4CLR_CCU6SR0C_Pos, SCU_IRCON4CLR_CCU6SR0C_Msk, 1u);
  }
}
#endif

/*******************************************************************************
**                      CCU6 SR1 ISR                                          **
*******************************************************************************/
#if ((CPU_NVIC_ISER & (1u << 5u)) != 0u)
void CCU6SR1_IRQHandler(void)
{
  if (u1_Field_Rd32(&SCU->IRCON4.reg, (uint8)SCU_IRCON4_CCU6SR1_Pos, SCU_IRCON4_CCU6SR1_Msk) == (uint8)1)
  {
#if (((CCU6_INP & (CCU6_INP_Msk << CCU6_INP_INPCC60_Pos)) == (CCU6_SR1 << CCU6_INP_INPCC60_Pos)) || defined(UNIT_TESTING_LV2))
#if (CCU6_CH0_CM_R_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENCC60R_Pos, (uint16)CCU6_IEN_ENCC60R_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_ICC60R_Pos, (uint16)CCU6_IS_ICC60R_Msk) == (uint8)1)
      {
        CCU6_CH0_CM_R_CALLBACK();
        CCU6_CH0_CM_R_Int_Clr();
      }
    }
#endif /*(CCU6_CH0_CM_R_INT_EN == 1u) */

#if (CCU6_CH0_CM_F_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENCC60F_Pos, (uint16)CCU6_IEN_ENCC60F_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_ICC60F_Pos, (uint16)CCU6_IS_ICC60F_Msk) == (uint8)1)
      {
        CCU6_CH0_CM_F_CALLBACK();
        CCU6_CH0_CM_F_Int_Clr();
      }
    }
#endif /*(CCU6_CH0_CM_F_INT_EN == 1u) */
#endif /*((CCU6_INP >> 0u) & 3u) == CCU6_SR1) */

#if (((CCU6_INP & (CCU6_INP_Msk << CCU6_INP_INPCC61_Pos)) == (CCU6_SR1 << CCU6_INP_INPCC61_Pos)) || defined(UNIT_TESTING_LV2))
#if (CCU6_CH1_CM_R_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENCC61R_Pos, (uint16)CCU6_IEN_ENCC61R_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_ICC61R_Pos, (uint16)CCU6_IS_ICC61R_Msk) == (uint8)1)
      {
        CCU6_CH1_CM_R_CALLBACK();
        CCU6_CH1_CM_R_Int_Clr();
      }
    }
#endif /*(CCU6_CH1_CM_R_INT_EN == 1u) */

#if (CCU6_CH1_CM_F_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENCC61F_Pos, (uint16)CCU6_IEN_ENCC61F_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_ICC61F_Pos, (uint16)CCU6_IS_ICC61F_Msk) == (uint8)1)
      {
        CCU6_CH1_CM_F_CALLBACK();
        CCU6_CH1_CM_F_Int_Clr();
      }
    }
#endif /*(CCU6_CH1_CM_F_INT_EN == 1u) */
#endif /*((CCU6_INP >> 2u) & 3u) == CCU6_SR1) */

#if (((CCU6_INP & (CCU6_INP_Msk << CCU6_INP_INPCC62_Pos)) == (CCU6_SR1 << CCU6_INP_INPCC62_Pos)) || defined(UNIT_TESTING_LV2))
#if (CCU6_CH2_CM_R_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENCC62R_Pos, (uint16)CCU6_IEN_ENCC62R_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_ICC62R_Pos, (uint16)CCU6_IS_ICC62R_Msk) == (uint8)1)
      {
        CCU6_CH2_CM_R_CALLBACK();
        CCU6_CH2_CM_R_Int_Clr();
      }
    }
#endif /*(CCU6_CH2_CM_R_INT_EN == 1u) */

#if (CCU6_CH2_CM_F_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENCC62F_Pos, (uint16)CCU6_IEN_ENCC62F_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_ICC62F_Pos, (uint16)CCU6_IS_ICC62F_Msk) == (uint8)1)
      {
        CCU6_CH2_CM_F_CALLBACK();
        CCU6_CH2_CM_F_Int_Clr();
      }
    }
#endif /*(CCU6_CH2_CM_F_INT_EN == 1u) */
#endif /*((CCU6_INP >> 4u) & 3u) == CCU6_SR1) */

#if (((CCU6_INP & (CCU6_INP_Msk << CCU6_INP_INPT12_Pos)) == (CCU6_SR1 << CCU6_INP_INPT12_Pos)) || defined(UNIT_TESTING_LV2))
#if (CCU6_T12_OM_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENT12OM_Pos, (uint16)CCU6_IEN_ENT12OM_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_T12OM_Pos, (uint16)CCU6_IS_T12OM_Msk) == (uint8)1)
      {
        CCU6_T12_OM_CALLBACK();
        CCU6_T12_OM_Int_Clr();
      }
    }
#endif /*(CCU6_T12_OM_INT_EN == 1u) */

#if (CCU6_T12_PM_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENT12PM_Pos, (uint16)CCU6_IEN_ENT12PM_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_T12PM_Pos, (uint16)CCU6_IS_T12PM_Msk) == (uint8)1)
      {
        CCU6_T12_PM_CALLBACK();
        CCU6_T12_PM_Int_Clr();
      }
    }
#endif /*(CCU6_T12_OM_INT_EN == 1u) */
#endif /*((CCU6_INP >> 10u) & 3u) == CCU6_SR1) */

#if (((CCU6_INP & (CCU6_INP_Msk << CCU6_INP_INPT13_Pos)) == (CCU6_SR1 << CCU6_INP_INPT13_Pos)) || defined(UNIT_TESTING_LV2))
#if (CCU6_T13_CM_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENT13CM_Pos, (uint16)CCU6_IEN_ENT13CM_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_T13CM_Pos, (uint16)CCU6_IS_T13CM_Msk) == (uint8)1)
      {
        CCU6_T13_CM_CALLBACK();
        CCU6_T13_CM_Int_Clr();
      }
    }
#endif /*(CCU6_T13_CM_INT_EN == 1u) */

#if (CCU6_T13_PM_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENT13PM_Pos, (uint16)CCU6_IEN_ENT13PM_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_T13PM_Pos, (uint16)CCU6_IS_T13PM_Msk) == (uint8)1)
      {
        CCU6_T13_PM_CALLBACK();
        CCU6_T13_PM_Int_Clr();
      }
    }
#endif /*(CCU6_T13_PM_INT_EN == 1u) */
#endif /*((CCU6_INP >> 12u) & 3u) == CCU6_SR1) */

#if (((CCU6_INP & (CCU6_INP_Msk << CCU6_INP_INPERR_Pos)) == (CCU6_SR1 << CCU6_INP_INPERR_Pos)) || defined(UNIT_TESTING_LV2))
#if (CCU6_TRAP_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENTRPF_Pos, (uint16)CCU6_IEN_ENTRPF_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_TRPF_Pos, (uint16)CCU6_IS_TRPF_Msk) == (uint8)1)
      {
        CCU6_TRAP_CALLBACK();
        CCU6_TRAP_Int_Clr();
      }
    }
#endif /*(CCU6_TRAP_INT_EN == 1u) */

#if (CCU6_WHE_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENWHE_Pos, (uint16)CCU6_IEN_ENWHE_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_WHE_Pos, (uint16)CCU6_IS_WHE_Msk) == (uint8)1)
      {
        CCU6_WRONG_HALL_CALLBACK();
        CCU6_WHE_Int_Clr();
      }
    }
#endif /*(CCU6_WHE_INT_EN == 1u) */
#endif /*((CCU6_INP >> 8u) & 3u) == CCU6_SR1) */

#if (((CCU6_INP & (CCU6_INP_Msk << CCU6_INP_INPCHE_Pos)) == (CCU6_SR1 << CCU6_INP_INPCHE_Pos)) || defined(UNIT_TESTING_LV2))
#if (CCU6_CHE_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENCHE_Pos, (uint16)CCU6_IEN_ENCHE_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_CHE_Pos, (uint16)CCU6_IS_CHE_Msk) == (uint8)1)
      {
        CCU6_CORRECT_HALL_CALLBACK();
        CCU6_CHE_Int_Clr();
      }
    }
#endif /*(CCU6_CHE_INT_EN == 1u) */

#if (CCU6_MCM_STR_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENSTR_Pos, (uint16)CCU6_IEN_ENSTR_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_STR_Pos, (uint16)CCU6_IS_STR_Msk) == (uint8)1)
      {
        CCU6_MCM_STR_CALLBACK();
        CCU6_STR_Int_Clr();
      }
    }
#endif /*(CCU6_MCM_STR_INT_EN == 1u) */
#endif /*((CCU6_INP >> 6u) & 3u) == CCU6_SR1) */

    Field_Wrt32(&SCU->IRCON4CLR.reg, (uint8)SCU_IRCON4CLR_CCU6SR1C_Pos, SCU_IRCON4CLR_CCU6SR1C_Msk, 1u);
  }
}
#endif

/*******************************************************************************
**                      CCU6 SR2 ISR                                          **
*******************************************************************************/
#if ((CPU_NVIC_ISER & (1u << 6u)) != 0u)
void CCU6SR2_IRQHandler(void)
{
  if (u1_Field_Rd32(&SCU->IRCON4.reg, (uint8)SCU_IRCON4_CCU6SR2_Pos, SCU_IRCON4_CCU6SR2_Msk) == (uint8)1)
  {
#if (((CCU6_INP & (CCU6_INP_Msk << CCU6_INP_INPCC60_Pos)) == (CCU6_SR2 << CCU6_INP_INPCC60_Pos)) || defined(UNIT_TESTING_LV2))
#if (CCU6_CH0_CM_R_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENCC60R_Pos, (uint16)CCU6_IEN_ENCC60R_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_ICC60R_Pos, (uint16)CCU6_IS_ICC60R_Msk) == (uint8)1)
      {
        CCU6_CH0_CM_R_CALLBACK();
        CCU6_CH0_CM_R_Int_Clr();
      }
    }
#endif /*(CCU6_CH0_CM_R_INT_EN == 1u) */

#if (CCU6_CH0_CM_F_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENCC60F_Pos, (uint16)CCU6_IEN_ENCC60F_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_ICC60F_Pos, (uint16)CCU6_IS_ICC60F_Msk) == (uint8)1)
      {
        CCU6_CH0_CM_F_CALLBACK();
        CCU6_CH0_CM_F_Int_Clr();
      }
    }
#endif /*(CCU6_CH0_CM_F_INT_EN == 1u) */
#endif /*((CCU6_INP >> 0u) & 3u) == CCU6_SR2) */

#if (((CCU6_INP & (CCU6_INP_Msk << CCU6_INP_INPCC61_Pos)) == (CCU6_SR2 << CCU6_INP_INPCC61_Pos)) || defined(UNIT_TESTING_LV2))
#if (CCU6_CH1_CM_R_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENCC61R_Pos, (uint16)CCU6_IEN_ENCC61R_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_ICC61R_Pos, (uint16)CCU6_IS_ICC61R_Msk) == (uint8)1)
      {
        CCU6_CH1_CM_R_CALLBACK();
        CCU6_CH1_CM_R_Int_Clr();
      }
    }
#endif /*(CCU6_CH1_CM_R_INT_EN == 1u) */

#if (CCU6_CH1_CM_F_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENCC61F_Pos, (uint16)CCU6_IEN_ENCC61F_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_ICC61F_Pos, (uint16)CCU6_IS_ICC61F_Msk) == (uint8)1)
      {
        CCU6_CH1_CM_F_CALLBACK();
        CCU6_CH1_CM_F_Int_Clr();
      }
    }
#endif /*(CCU6_CH1_CM_F_INT_EN == 1u) */
#endif /*((CCU6_INP >> 2u) & 3u) == CCU6_SR2) */

#if (((CCU6_INP & (CCU6_INP_Msk << CCU6_INP_INPCC62_Pos)) == (CCU6_SR2 << CCU6_INP_INPCC62_Pos)) || defined(UNIT_TESTING_LV2))
#if (CCU6_CH2_CM_R_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENCC62R_Pos, (uint16)CCU6_IEN_ENCC62R_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_ICC62R_Pos, (uint16)CCU6_IS_ICC62R_Msk) == (uint8)1)
      {
        CCU6_CH2_CM_R_CALLBACK();
        CCU6_CH2_CM_R_Int_Clr();
      }
    }
#endif /*(CCU6_CH2_CM_R_INT_EN == 1u) */

#if (CCU6_CH2_CM_F_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENCC62F_Pos, (uint16)CCU6_IEN_ENCC62F_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_ICC62F_Pos, (uint16)CCU6_IS_ICC62F_Msk) == (uint8)1)
      {
        CCU6_CH2_CM_F_CALLBACK();
        CCU6_CH2_CM_F_Int_Clr();
      }
    }
#endif /*(CCU6_CH2_CM_F_INT_EN == 1u) */
#endif /*((CCU6_INP >> 4u) & 3u) == CCU6_SR2) */

#if (((CCU6_INP & (CCU6_INP_Msk << CCU6_INP_INPT12_Pos)) == (CCU6_SR2 << CCU6_INP_INPT12_Pos)) || defined(UNIT_TESTING_LV2))
#if (CCU6_T12_OM_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENT12OM_Pos, (uint16)CCU6_IEN_ENT12OM_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_T12OM_Pos, (uint16)CCU6_IS_T12OM_Msk) == (uint8)1)
      {
        CCU6_T12_OM_CALLBACK();
        CCU6_T12_OM_Int_Clr();
      }
    }
#endif /*(CCU6_T12_OM_INT_EN == 1u) */

#if (CCU6_T12_PM_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENT12PM_Pos, (uint16)CCU6_IEN_ENT12PM_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_T12PM_Pos, (uint16)CCU6_IS_T12PM_Msk) == (uint8)1)
      {
        CCU6_T12_PM_CALLBACK();
        CCU6_T12_PM_Int_Clr();
      }
    }
#endif /*(CCU6_T12_OM_INT_EN == 1u) */
#endif /*((CCU6_INP >> 10u) & 3u) == CCU6_SR2) */

#if (((CCU6_INP & (CCU6_INP_Msk << CCU6_INP_INPT13_Pos)) == (CCU6_SR2 << CCU6_INP_INPT13_Pos)) || defined(UNIT_TESTING_LV2))
#if (CCU6_T13_CM_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENT13CM_Pos, (uint16)CCU6_IEN_ENT13CM_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_T13CM_Pos, (uint16)CCU6_IS_T13CM_Msk) == (uint8)1)
      {
        CCU6_T13_CM_CALLBACK();
        CCU6_T13_CM_Int_Clr();
      }
    }
#endif /*(CCU6_T13_CM_INT_EN == 1u) */

#if (CCU6_T13_PM_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENT13PM_Pos, (uint16)CCU6_IEN_ENT13PM_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_T13PM_Pos, (uint16)CCU6_IS_T13PM_Msk) == (uint8)1)
      {
        CCU6_T13_PM_CALLBACK();
        CCU6_T13_PM_Int_Clr();
      }
    }
#endif /*(CCU6_T13_PM_INT_EN == 1u) */
#endif /*((CCU6_INP >> 12u) & 3u) == CCU6_SR2) */

#if (((CCU6_INP & (CCU6_INP_Msk << CCU6_INP_INPERR_Pos)) == (CCU6_SR2 << CCU6_INP_INPERR_Pos)) || defined(UNIT_TESTING_LV2))
#if (CCU6_TRAP_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENTRPF_Pos, (uint16)CCU6_IEN_ENTRPF_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_TRPF_Pos, (uint16)CCU6_IS_TRPF_Msk) == (uint8)1)
      {
        CCU6_TRAP_CALLBACK();
        CCU6_TRAP_Int_Clr();
      }
    }
#endif /*(CCU6_TRAP_INT_EN == 1u) */

#if (CCU6_WHE_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENWHE_Pos, (uint16)CCU6_IEN_ENWHE_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_WHE_Pos, (uint16)CCU6_IS_WHE_Msk) == (uint8)1)
      {
        CCU6_WRONG_HALL_CALLBACK();
        CCU6_WHE_Int_Clr();
      }
    }
#endif /*(CCU6_WHE_INT_EN == 1u) */
#endif /*((CCU6_INP >> 8u) & 3u) == CCU6_SR2) */

#if (((CCU6_INP & (CCU6_INP_Msk << CCU6_INP_INPCHE_Pos)) == (CCU6_SR2 << CCU6_INP_INPCHE_Pos)) || defined(UNIT_TESTING_LV2))
#if (CCU6_CHE_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENCHE_Pos, (uint16)CCU6_IEN_ENCHE_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_CHE_Pos, (uint16)CCU6_IS_CHE_Msk) == (uint8)1)
      {
        CCU6_CORRECT_HALL_CALLBACK();
        CCU6_CHE_Int_Clr();
      }
    }
#endif /*(CCU6_CHE_INT_EN == 1u) */

#if (CCU6_MCM_STR_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENSTR_Pos, (uint16)CCU6_IEN_ENSTR_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_STR_Pos, (uint16)CCU6_IS_STR_Msk) == (uint8)1)
      {
        CCU6_MCM_STR_CALLBACK();
        CCU6_STR_Int_Clr();
      }
    }
#endif /*(CCU6_MCM_STR_INT_EN == 1u) */
#endif /*((CCU6_INP >> 6u) & 3u) == CCU6_SR2) */

    Field_Wrt32(&SCU->IRCON4CLR.reg, (uint8)SCU_IRCON4CLR_CCU6SR2C_Pos, SCU_IRCON4CLR_CCU6SR2C_Msk, 1u);
  }
}
#endif

/*******************************************************************************
**                      CCU6 SR3 ISR                                          **
*******************************************************************************/
#if ((CPU_NVIC_ISER & (1u << 7u)) != 0u)
void CCU6SR3_IRQHandler(void)
{
  if (u1_Field_Rd32(&SCU->IRCON4.reg, (uint8)SCU_IRCON4_CCU6SR3_Pos, SCU_IRCON4_CCU6SR3_Msk) == (uint8)1)
  {
#if (((CCU6_INP & (CCU6_INP_Msk << CCU6_INP_INPCC60_Pos)) == (CCU6_SR3 << CCU6_INP_INPCC60_Pos)) || defined(UNIT_TESTING_LV2))
#if (CCU6_CH0_CM_R_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENCC60R_Pos, (uint16)CCU6_IEN_ENCC60R_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_ICC60R_Pos, (uint16)CCU6_IS_ICC60R_Msk) == (uint8)1)
      {
        CCU6_CH0_CM_R_CALLBACK();
        CCU6_CH0_CM_R_Int_Clr();
      }
    }
#endif /*(CCU6_CH0_CM_R_INT_EN == 1u) */

#if (CCU6_CH0_CM_F_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENCC60F_Pos, (uint16)CCU6_IEN_ENCC60F_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_ICC60F_Pos, (uint16)CCU6_IS_ICC60F_Msk) == (uint8)1)
      {
        CCU6_CH0_CM_F_CALLBACK();
        CCU6_CH0_CM_F_Int_Clr();
      }
    }
#endif /*(CCU6_CH0_CM_F_INT_EN == 1u) */
#endif /*((CCU6_INP >> 0u) & 3u) == CCU6_SR3) */

#if (((CCU6_INP & (CCU6_INP_Msk << CCU6_INP_INPCC61_Pos)) == (CCU6_SR3 << CCU6_INP_INPCC61_Pos)) || defined(UNIT_TESTING_LV2))
#if (CCU6_CH1_CM_R_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENCC61R_Pos, (uint16)CCU6_IEN_ENCC61R_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_ICC61R_Pos, (uint16)CCU6_IS_ICC61R_Msk) == (uint8)1)
      {
        CCU6_CH1_CM_R_CALLBACK();
        CCU6_CH1_CM_R_Int_Clr();
      }
    }
#endif /*(CCU6_CH1_CM_R_INT_EN == 1u) */

#if (CCU6_CH1_CM_F_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENCC61F_Pos, (uint16)CCU6_IEN_ENCC61F_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_ICC61F_Pos, (uint16)CCU6_IS_ICC61F_Msk) == (uint8)1)
      {
        CCU6_CH1_CM_F_CALLBACK();
        CCU6_CH1_CM_F_Int_Clr();
      }
    }
#endif /*(CCU6_CH1_CM_F_INT_EN == 1u) */
#endif /*((CCU6_INP >> 2u) & 3u) == CCU6_SR3) */

#if (((CCU6_INP & (CCU6_INP_Msk << CCU6_INP_INPCC62_Pos)) == (CCU6_SR3 << CCU6_INP_INPCC62_Pos)) || defined(UNIT_TESTING_LV2))
#if (CCU6_CH2_CM_R_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENCC62R_Pos, (uint16)CCU6_IEN_ENCC62R_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_ICC62R_Pos, (uint16)CCU6_IS_ICC62R_Msk) == (uint8)1)
      {
        CCU6_CH2_CM_R_CALLBACK();
        CCU6_CH2_CM_R_Int_Clr();
      }
    }
#endif /*(CCU6_CH2_CM_R_INT_EN == 1u) */

#if (CCU6_CH2_CM_F_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENCC62F_Pos, (uint16)CCU6_IEN_ENCC62F_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_ICC62F_Pos, (uint16)CCU6_IS_ICC62F_Msk) == (uint8)1)
      {
        CCU6_CH2_CM_F_CALLBACK();
        CCU6_CH2_CM_F_Int_Clr();
      }
    }
#endif /*(CCU6_CH2_CM_F_INT_EN == 1u) */
#endif /*((CCU6_INP >> 4u) & 3u) == CCU6_SR3) */

#if (((CCU6_INP & (CCU6_INP_Msk << CCU6_INP_INPT12_Pos)) == (CCU6_SR3 << CCU6_INP_INPT12_Pos)) || defined(UNIT_TESTING_LV2))
#if (CCU6_T12_OM_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENT12OM_Pos, (uint16)CCU6_IEN_ENT12OM_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_T12OM_Pos, (uint16)CCU6_IS_T12OM_Msk) == (uint8)1)
      {
        CCU6_T12_OM_CALLBACK();
        CCU6_T12_OM_Int_Clr();
      }
    }
#endif /*(CCU6_T12_OM_INT_EN == 1u) */

#if (CCU6_T12_PM_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENT12PM_Pos, (uint16)CCU6_IEN_ENT12PM_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_T12PM_Pos, (uint16)CCU6_IS_T12PM_Msk) == (uint8)1)
      {
        CCU6_T12_PM_CALLBACK();
        CCU6_T12_PM_Int_Clr();
      }
    }
#endif /*(CCU6_T12_OM_INT_EN == 1u) */
#endif /*((CCU6_INP >> 10u) & 3u) == CCU6_SR3) */

#if (((CCU6_INP & (CCU6_INP_Msk << CCU6_INP_INPT13_Pos)) == (CCU6_SR3 << CCU6_INP_INPT13_Pos)) || defined(UNIT_TESTING_LV2))
#if (CCU6_T13_CM_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENT13CM_Pos, (uint16)CCU6_IEN_ENT13CM_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_T13CM_Pos, (uint16)CCU6_IS_T13CM_Msk) == (uint8)1)
      {
        CCU6_T13_CM_CALLBACK();
        CCU6_T13_CM_Int_Clr();
      }
    }
#endif /*(CCU6_T13_CM_INT_EN == 1u) */

#if (CCU6_T13_PM_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENT13PM_Pos, (uint16)CCU6_IEN_ENT13PM_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_T13PM_Pos, (uint16)CCU6_IS_T13PM_Msk) == (uint8)1)
      {
        CCU6_T13_PM_CALLBACK();
        CCU6_T13_PM_Int_Clr();
      }
    }
#endif /*(CCU6_T13_PM_INT_EN == 1u) */
#endif /*((CCU6_INP >> 12u) & 3u) == CCU6_SR3) */

#if (((CCU6_INP & (CCU6_INP_Msk << CCU6_INP_INPERR_Pos)) == (CCU6_SR3 << CCU6_INP_INPERR_Pos)) || defined(UNIT_TESTING_LV2))
#if (CCU6_TRAP_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENTRPF_Pos, (uint16)CCU6_IEN_ENTRPF_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_TRPF_Pos, (uint16)CCU6_IS_TRPF_Msk) == (uint8)1)
      {
        CCU6_TRAP_CALLBACK();
        CCU6_TRAP_Int_Clr();
      }
    }
#endif /*(CCU6_TRAP_INT_EN == 1u) */

#if (CCU6_WHE_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENWHE_Pos, (uint16)CCU6_IEN_ENWHE_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_WHE_Pos, (uint16)CCU6_IS_WHE_Msk) == (uint8)1)
      {
        CCU6_WRONG_HALL_CALLBACK();
        CCU6_WHE_Int_Clr();
      }
    }
#endif /*(CCU6_WHE_INT_EN == 1u) */
#endif /*((CCU6_INP >> 8u) & 3u) == CCU6_SR3) */

#if (((CCU6_INP & (CCU6_INP_Msk << CCU6_INP_INPCHE_Pos)) == (CCU6_SR3 << CCU6_INP_INPCHE_Pos)) || defined(UNIT_TESTING_LV2))
#if (CCU6_CHE_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENCHE_Pos, (uint16)CCU6_IEN_ENCHE_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_CHE_Pos, (uint16)CCU6_IS_CHE_Msk) == (uint8)1)
      {
        CCU6_CORRECT_HALL_CALLBACK();
        CCU6_CHE_Int_Clr();
      }
    }
#endif /*(CCU6_CHE_INT_EN == 1u) */

#if (CCU6_MCM_STR_INT_EN == 1u)
    if (u1_Field_Rd16(&CCU6->IEN.reg, (uint8)(uint16)CCU6_IEN_ENSTR_Pos, (uint16)CCU6_IEN_ENSTR_Msk) == (uint8)1)
    {
      if (u1_Field_Rd16(&CCU6->IS.reg, (uint8)(uint16)CCU6_IS_STR_Pos, (uint16)CCU6_IS_STR_Msk) == (uint8)1)
      {
        CCU6_MCM_STR_CALLBACK();
        CCU6_STR_Int_Clr();
      }
    }
#endif /*(CCU6_MCM_STR_INT_EN == 1u) */
#endif /*((CCU6_INP >> 6u) & 3u) == CCU6_SR3) */

    Field_Wrt32(&SCU->IRCON4CLR.reg, (uint8)SCU_IRCON4CLR_CCU6SR3C_Pos, SCU_IRCON4CLR_CCU6SR3C_Msk, 1u);
  }
}
#endif

/*******************************************************************************
**                      SSC1 ISR                                              **
*******************************************************************************/
#if  ((SSC1_RX_INT_EN == 1u)  || \
      (SSC1_TX_INT_EN == 1u)  || \
      (SSC1_ERR_INT_EN == 1u))
void SSC1_IRQHandler(void)
{
#if (SSC1_RX_INT_EN == 1u)
  /* check for receive interrupt */
  if (u1_Field_Rd32(&SCU->MODIEN1.reg, (uint8)SCU_MODIEN1_RIREN1_Pos, SCU_MODIEN1_RIREN1_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&SCU->IRCON2.reg, (uint8)SCU_IRCON2_RIR1_Pos, SCU_IRCON2_RIR1_Msk) == (uint8)1)
    {
      SSC1_RX_CALLBACK();
      SSC1_RX_Int_Clr();
    }
  }
#endif /*(SSC1_RX_INT_EN == 1u) */

#if (SSC1_TX_INT_EN == 1u)
  /* check for transmit interrupt */
  if (u1_Field_Rd32(&SCU->MODIEN1.reg, (uint8)SCU_MODIEN1_TIREN1_Pos, SCU_MODIEN1_TIREN1_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&SCU->IRCON2.reg, (uint8)SCU_IRCON2_TIR1_Pos, SCU_IRCON2_TIR1_Msk) == (uint8)1)
    {
      SSC1_TX_CALLBACK();
      SSC1_TX_Int_Clr();
    }
  }
#endif /*(SSC1_TX_INT_EN == 1u) */

#if (SSC1_ERR_INT_EN == 1u)
  /* check for error interrupt */
  if (u1_Field_Rd32(&SCU->MODIEN1.reg, (uint8)SCU_MODIEN1_EIREN1_Pos, SCU_MODIEN1_EIREN1_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&SCU->IRCON2.reg, (uint8)SCU_IRCON2_EIR1_Pos, SCU_IRCON2_EIR1_Msk) == (uint8)1)
    {
      SSC1_ERR_CALLBACK();
      SSC1_Err_Int_Clr();
    }
  }
#endif /*(SSC1_ERR_INT_EN == 1u) */
}
#endif

/*******************************************************************************
**                      SSC2 ISR                                              **
*******************************************************************************/
#if  ((SSC2_RX_INT_EN == 1u)  || \
      (SSC2_TX_INT_EN == 1u)  || \
      (SSC2_ERR_INT_EN == 1u))
void SSC2_IRQHandler(void)
{
#if (SSC2_RX_INT_EN == 1u)
  /* check for receive interrupt */
  if (u1_Field_Rd32(&SCU->MODIEN1.reg, (uint8)SCU_MODIEN1_RIREN2_Pos, SCU_MODIEN1_RIREN2_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&SCU->IRCON3.reg, (uint8)SCU_IRCON3_RIR2_Pos, SCU_IRCON3_RIR2_Msk) == (uint8)1)
    {
      SSC2_RX_CALLBACK();
      SSC2_RX_Int_Clr();
    }
  }
#endif /*(SSC2_RX_INT_EN == 1u) */

#if (SSC2_TX_INT_EN == 1u)
  /* check for transmit interrupt */
  if (u1_Field_Rd32(&SCU->MODIEN1.reg, (uint8)SCU_MODIEN1_TIREN2_Pos, SCU_MODIEN1_TIREN2_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&SCU->IRCON3.reg, (uint8)SCU_IRCON3_TIR2_Pos, SCU_IRCON3_TIR2_Msk) == (uint8)1)
    {
      SSC2_TX_CALLBACK();
      SSC2_TX_Int_Clr();
    }
  }
#endif /*(SSC2_TX_INT_EN == 1u) */

#if (SSC2_ERR_INT_EN == 1u)
  /* check for error interrupt */
  if (u1_Field_Rd32(&SCU->MODIEN1.reg, (uint8)SCU_MODIEN1_EIREN2_Pos, SCU_MODIEN1_EIREN2_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&SCU->IRCON3.reg, (uint8)SCU_IRCON3_EIR2_Pos, SCU_IRCON3_EIR2_Msk) == (uint8)1)
    {
      SSC2_ERR_CALLBACK();
      SSC2_Err_Int_Clr();
    }
  }
#endif /*(SSC2_ERR_INT_EN == 1u) */
}
#endif

/*******************************************************************************
**                      UART1 ISR                                             **
*******************************************************************************/
#if    ((UART1_RX_INT_EN == 1u)    || \
        (UART1_TX_INT_EN == 1u)    || \
        (TIMER2_EXF2_INT_EN == 1u) || \
        (TIMER2_TF2_INT_EN == 1u)  || \
        (LIN_EOF_INT_EN == 1u)     || \
        (LIN_ERR_INT_EN == 1u)     || \
        (LIN_OC_INT_EN == 1u)      || \
        (LIN_OT_INT_EN == 1u)      || \
        (LIN_TMOUT_INT_EN == 1u)   || \
        (LIN_M_SM_ERR_INT_EN == 1u))
void UART1_IRQHandler(void)
{
#if (UART1_RX_INT_EN == 1u)
  if (u1_Field_Rd32(&SCU->MODIEN2.reg, (uint8)SCU_MODIEN2_RIEN1_Pos, SCU_MODIEN2_RIEN1_Msk) == (uint8)1)
  {
    /* check for receive interrupt */
    if (u1_Field_Rd32(&UART1->SCON.reg, (uint8)UART1_SCON_RI_Pos, UART1_SCON_RI_Msk) == (uint8)1)
    {
      UART1_RX_CALLBACK();
      UART1_RX_Int_Clr();
    }
  }
#endif /*(UART1_RX_INT_EN == 1u) */

#if (UART1_TX_INT_EN == 1u)
  if (u1_Field_Rd32(&SCU->MODIEN2.reg, (uint8)SCU_MODIEN2_TIEN1_Pos, SCU_MODIEN2_TIEN1_Msk) == (uint8)1)
  {
    /* check for transmit interrupt */
    if (u1_Field_Rd32(&UART1->SCON.reg, (uint8)UART1_SCON_TI_Pos, UART1_SCON_TI_Msk) == (uint8)1)
    {
      UART1_TX_CALLBACK();
      UART1_TX_Int_Clr();
    }
  }
#endif /*(UART1_TX_INT_EN == 1u) */

#if (TIMER2_TF2_INT_EN == 1u)
  if (u1_Field_Rd32(&TIMER2->CON1.reg, (uint8)TIMER2_CON1_TF2EN_Pos, TIMER2_CON1_TF2EN_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&TIMER2->CON.reg, (uint8)TIMER2_CON_TF2_Pos, TIMER2_CON_TF2_Msk) == (uint8)1)
    {
      TIMER2_TF2_CALLBACK();
      TIMER2_Overflow_Int_Clr();
    }
  }
#endif /*(TIMER2_TF2_INT_EN == 1u) */

#if (TIMER2_EXF2_INT_EN == 1u)
  if (u1_Field_Rd32(&TIMER2->CON1.reg, (uint8)TIMER2_CON1_EXF2EN_Pos, TIMER2_CON1_EXF2EN_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&TIMER2->CON.reg, (uint8)TIMER2_CON_EXF2_Pos, TIMER2_CON_EXF2_Msk) == (uint8)1)
    {
      TIMER2_EXF2_CALLBACK();
      TIMER2_External_Int_Clr();
    }
  }
#endif /*(TIMER2_EXF2_INT_EN == 1u) */

#if (LIN_OC_INT_EN == 1u)
  if (u1_Field_Rd32(&LIN->IRQEN.reg, (uint8)LIN_IRQEN_OC_IEN_Pos, LIN_IRQEN_OC_IEN_Msk) == (uint8)1)
  {
    /* LIN Over Current Interrupt */
    if (u1_Field_Rd32(&LIN->IRQS.reg, (uint8)LIN_IRQS_OC_IS_Pos, LIN_IRQS_OC_IS_Msk) == (uint8)1)
    {
      if (u1_Field_Rd32(&SCUPM->SYS_IS.reg, (uint8)SCUPM_SYS_IS_LIN_FAIL_IS_Pos, SCUPM_SYS_IS_LIN_FAIL_IS_Msk) == (uint8)1)
      {
        LIN_OC_CALLBACK();
        LIN_Over_Curr_Int_Clr();
      }
    }
  }
#endif /*((LIN_IRQEN & (1u << 5u)) != 0u) */

#if (LIN_OT_INT_EN == 1u)
  if (u1_Field_Rd32(&LIN->IRQEN.reg, (uint8)LIN_IRQEN_OT_IEN_Pos, LIN_IRQEN_OT_IEN_Msk) == (uint8)1)
  {
    /* LIN Over Temperature Interrupt */
    if (u1_Field_Rd32(&LIN->IRQS.reg, (uint8)LIN_IRQS_OT_IS_Pos, LIN_IRQS_OT_IS_Msk) == (uint8)1)
    {
      if(u1_Field_Rd32(&SCUPM->SYS_IS.reg, (uint8)SCUPM_SYS_IS_LIN_FAIL_IS_Pos, SCUPM_SYS_IS_LIN_FAIL_IS_Msk) == (uint8)1)
      {
        LIN_OT_CALLBACK();
        LIN_Over_Temp_Int_Clr();
      }
    }
  }
#endif /*((LIN_IRQEN & (1u << 4u)) != 0u) */

#if (LIN_TMOUT_INT_EN == 1u)
  if (u1_Field_Rd32(&LIN->IRQEN.reg, (uint8)LIN_IRQEN_TXD_TMOUT_IEN_Pos, LIN_IRQEN_TXD_TMOUT_IEN_Msk) == (uint8)1)
  {
    /* LIN TxD Timerout Interrupt */
    if (u1_Field_Rd32(&LIN->IRQS.reg, (uint8)LIN_IRQS_TXD_TMOUT_IS_Pos, LIN_IRQS_TXD_TMOUT_IS_Msk) == (uint8)1)
    {
      LIN_TMOUT_CALLBACK();
      LIN_Time_Out_Int_Clr();
    }
  }
#endif /*((LIN_IRQEN & (1u << 6u)) != 0u) */

#if (LIN_M_SM_ERR_INT_EN == 1u)
  if (u1_Field_Rd32(&LIN->IRQEN.reg, (uint8)LIN_IRQEN_M_SM_ERR_IEN_Pos, LIN_IRQEN_M_SM_ERR_IEN_Msk) == (uint8)1)
  {
    /* LIN Transceiver Mode Error - Slope Mode Error Interrupt */
    if (u1_Field_Rd32(&LIN->IRQS.reg, (uint8)LIN_IRQS_M_SM_ERR_IS_Pos, LIN_IRQS_M_SM_ERR_IS_Msk) == (uint8)1)
    {
      LIN_M_SM_ERR_CALLBACK();
      LIN_Mode_Error_Int_Clr();
    }
  }
#endif /*((LIN_IRQEN & (1u << 3u)) != 0u) */

#if ((LIN_EOF_INT_EN == 1u) || \
     (LIN_ERR_INT_EN == 1u) )
  if (u1_Field_Rd32(&SCU->LINST.reg, (uint8)SCU_LINST_SYNEN_Pos, SCU_LINST_SYNEN_Msk) == (uint8)1)
  {
#if (LIN_EOF_INT_EN == 1u)
    if (u1_Field_Rd32(&SCU->LINST.reg, (uint8)SCU_LINST_EOFSYN_Pos, SCU_LINST_EOFSYN_Msk) == (uint8)1)
    {
      LIN_EOF_CALLBACK();
      LIN_End_Of_Sync_Int_Clr();
    }
#endif /* ((LIN_EOF_INT_EN == 1u) */
#if (LIN_ERR_INT_EN == 1u)
    if (u1_Field_Rd32(&SCU->LINST.reg, (uint8)SCU_LINST_ERRSYN_Pos, SCU_LINST_ERRSYN_Msk) == (uint8)1)
    {
      LIN_ERR_CALLBACK();
      LIN_Err_In_Sync_Int_Clr();
    }
#endif /* ((LIN_ERR_INT_EN == 1u) */
  }
#endif
}
#endif

/*******************************************************************************
**                      UART2 ISR                                             **
*******************************************************************************/
#if   ((UART2_RX_INT_EN == 1u)          || \
       (UART2_TX_INT_EN == 1u)          || \
       (TIMER21_EXF2_INT_EN == 1u)      || \
       (TIMER21_TF2_INT_EN == 1u)       || \
       (SCU_EXINT2_RISING_INT_EN == 1u) || \
       (SCU_EXINT2_FALLING_INT_EN == 1u))
void UART2_IRQHandler(void)
{
#if (UART2_RX_INT_EN == 1u)
  if (u1_Field_Rd32(&SCU->MODIEN2.reg, (uint8)SCU_MODIEN2_RIEN2_Pos, SCU_MODIEN2_RIEN2_Msk) == (uint8)1)
  {
    /* check for receive interrupt */
    if (u1_Field_Rd32(&UART2->SCON.reg, (uint8)UART2_SCON_RI_Pos, UART2_SCON_RI_Msk) == (uint8)1)
    {
      UART2_RX_CALLBACK();
      UART2_RX_Int_Clr();
    }
  }
#endif /*(UART2_RX_INT_EN == 1u) */

#if (UART2_TX_INT_EN == 1u)
  if (u1_Field_Rd32(&SCU->MODIEN2.reg, (uint8)SCU_MODIEN2_TIEN2_Pos, SCU_MODIEN2_TIEN2_Msk) == (uint8)1)
  {
    /* check for transmit interrupt */
    if (u1_Field_Rd32(&UART2->SCON.reg, (uint8)UART2_SCON_TI_Pos, UART2_SCON_TI_Msk) == (uint8)1)
    {
      UART2_TX_CALLBACK();
      UART2_TX_Int_Clr();
    }
  }
#endif /*(UART2_TX_INT_EN == 1u) */

#if (TIMER21_TF2_INT_EN == 1u)
  if (u1_Field_Rd32(&TIMER21->CON1.reg, (uint8)TIMER21_CON1_TF2EN_Pos, TIMER21_CON1_TF2EN_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&TIMER21->CON.reg, (uint8)TIMER21_CON_TF2_Pos, TIMER21_CON_TF2_Msk) == (uint8)1)
    {
      TIMER21_TF2_CALLBACK();
      TIMER21_Overflow_Int_Clr();
    }
  }
#endif /*(TIMER21_TF2_INT_EN == 1u) */

#if (TIMER21_EXF2_INT_EN == 1u)
  if (u1_Field_Rd32(&TIMER21->CON1.reg, (uint8)TIMER21_CON1_EXF2EN_Pos, TIMER21_CON1_EXF2EN_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&TIMER21->CON.reg, (uint8)TIMER21_CON_EXF2_Pos, TIMER21_CON_EXF2_Msk) == (uint8)1)
    {
      TIMER21_EXF2_CALLBACK();
      TIMER21_External_Int_Clr();
    }
  }
#endif /*(TIMER21_TF2_INT_EN == 1u) */

#if ((SCU_MODIEN2 & (1u << 5u)) != 0u)
#if (SCU_EXINT2_FALLING_INT_EN == 1u)
  if (u1_Field_Rd32(&SCU->EXICON0.reg, (uint8)5u, (1u << 5u)) != (uint8)0)
  {
    /* External Interrupt 2 - Falling Edge */
    if (u1_Field_Rd32(&SCU->IRCON0.reg, (uint8)SCU_IRCON0_EXINT2F_Pos, SCU_IRCON0_EXINT2F_Msk) == (uint8)1)
    {
      EXINT2_FALLING_CALLBACK();
      EXINT2_Falling_Edge_Int_Clr();
    }
  }
#endif /* (SCU_EXINT2_FALLING_INT_EN == 1u) */

#if (SCU_EXINT2_RISING_INT_EN == 1u)
  if (u1_Field_Rd32(&SCU->EXICON0.reg, (uint8)4u, (1u << 4u)) != (uint8)0)
  {
    /* External Interrupt 2 - Rising Edge */
    if (u1_Field_Rd32(&SCU->IRCON0.reg, (uint8)SCU_IRCON0_EXINT2R_Pos, SCU_IRCON0_EXINT2R_Msk) == (uint8)1)
    {
      EXINT2_RISING_CALLBACK();
      EXINT2_Rising_Edge_Int_Clr();
    }
  }
#endif /* (SCU_EXINT2_RISING_INT_EN == 1u) */
#endif /*((SCU_MODIEN2 & (1u << 5u)) != 0u) */
}
#endif

/*******************************************************************************
**                      EXTINT0 ISR                                           **
*******************************************************************************/
#if  ((SCU_EXINT0_RISING_INT_EN == 1u) || \
      (SCU_EXINT0_FALLING_INT_EN == 1u))
void EXINT0_IRQHandler(void)
{
#if ((SCU_MODIEN3 & (1u << 0u)) != 0u)
#if (SCU_EXINT0_FALLING_INT_EN == 1u)
  if (u1_Field_Rd32(&SCU->EXICON0.reg, (uint8)1u, (1u << 1u)) != (uint8)0)
  {
    /* External Interrupt 0 - Falling Edge */
    if (u1_Field_Rd32(&SCU->IRCON0.reg, (uint8)SCU_IRCON0_EXINT0F_Pos, SCU_IRCON0_EXINT0F_Msk) == (uint8)1)
    {
      EXINT0_FALLING_CALLBACK();
      EXINT0_Falling_Edge_Int_Clr();
    }
  }
#endif /* (SCU_EXINT0_FALLING_INT_EN == 1u) */

#if (SCU_EXINT0_RISING_INT_EN == 1u)
  if (u1_Field_Rd32(&SCU->EXICON0.reg, 0u, 1u) != (uint8)0)
  {
    /* External Interrupt 0 - Rising Edge */
    if (u1_Field_Rd32(&SCU->IRCON0.reg, (uint8)SCU_IRCON0_EXINT0R_Pos, SCU_IRCON0_EXINT0R_Msk) == (uint8)1)
    {
      EXINT0_RISING_CALLBACK();
      EXINT0_Rising_Edge_Int_Clr();
    }
  }
#endif /* (SCU_EXINT0_RISING_INT_EN == 1u) */
#endif /* ((SCU_MODIEN3 & (1u << 0u)) != 0u) */
}
#endif

/*******************************************************************************
**                      EXTINT1 ISR                                           **
*******************************************************************************/
#if ((SCU_EXINT1_RISING_INT_EN == 1u) || \
     (SCU_EXINT1_FALLING_INT_EN == 1u))
void EXINT1_IRQHandler(void)
{
#if ((SCU_MODIEN4 & (1u << 0u)) != 0u)
#if (SCU_EXINT1_FALLING_INT_EN == 1u)
  if (u1_Field_Rd32(&SCU->EXICON0.reg, (uint8)3u, (1u << 3u)) != (uint8)0)
  {
    /* External Interrupt 1 - Falling Edge */
    if (u1_Field_Rd32(&SCU->IRCON0.reg, (uint8)SCU_IRCON0_EXINT1F_Pos, SCU_IRCON0_EXINT1F_Msk) == (uint8)1)
    {
      EXINT1_FALLING_CALLBACK();
      EXINT1_Falling_Edge_Int_Clr();
    }
  }
#endif /* (SCU_EXINT1_FALLING_INT_EN == 1u) */
#if (SCU_EXINT1_RISING_INT_EN == 1u)
  if (u1_Field_Rd32(&SCU->EXICON0.reg, (uint8)2u, (1u << 2u)) != (uint8)0)
  {
    /* External Interrupt 1 - Rising Edge */
    if (u1_Field_Rd32(&SCU->IRCON0.reg, (uint8)SCU_IRCON0_EXINT1R_Pos, SCU_IRCON0_EXINT1R_Msk) == (uint8)1)
    {
      EXINT1_RISING_CALLBACK();
      EXINT1_Rising_Edge_Int_Clr();
    }
  }
#endif /* (SCU_EXINT1_RISING_INT_EN == 1u) */
#endif /*((SCU_MODIEN4 & (1u << 0u)) != 0u) */
}
#endif

/*******************************************************************************
**                      WAKEUP ISR                                           **
*******************************************************************************/
#if (PMU_WAKEUP_INT_EN == 1u)
void WAKEUP_IRQHandler(void)
{
  if (u1_Field_Rd32(&SCU->WAKECON.reg, (uint8)SCU_WAKECON_WAKEUPEN_Pos, SCU_WAKECON_WAKEUPEN_Msk) == (uint8)1)
  {
    /* WAKEUP Interrupt */
    if (u1_Field_Rd32(&SCU->IRCON5.reg, (uint8)SCU_IRCON5_WAKEUP_Pos, SCU_IRCON5_WAKEUP_Msk) == (uint8)1)
    {
      PMU_WAKEUP_CALLBACK();
      WAKEUP_Int_Clr();
    }
  }
}
#endif

/*******************************************************************************
**                      MATH DIV ISR                                           **
*******************************************************************************/
#if ((MATH_DIVERR_INT_EN == 1u) || \
     (MATH_DIVEOC_INT_EN == 1u))
void DIV_IRQHandler(void)
{
#if (MATH_DIVERR_INT_EN == 1u)
  if (u1_Field_Rd32(&MATH->EVIER.reg, (uint8)MATH_EVIER_DIVERRIEN_Pos, MATH_EVIER_DIVERRIEN_Msk) == (uint8)1)
  {
    /* Divider Error Interrupt */
    if (u1_Field_Rd32(&MATH->EVFR.reg, (uint8)MATH_EVFR_DIVERR_Pos, MATH_EVFR_DIVERR_Msk) == (uint8)1)
    {
      MATH_DIVERR_CALLBACK();
      MATH_DIVERR_Int_Clr();
    }
  }
#endif
#if (MATH_DIVEOC_INT_EN == 1u)
  if (u1_Field_Rd32(&MATH->EVIER.reg, (uint8)MATH_EVIER_DIVEOCIEN_Pos, MATH_EVIER_DIVEOCIEN_Msk) == (uint8)1)
  {
    /* Divider End of Calculation Interrupt */
    if (u1_Field_Rd32(&MATH->EVFR.reg, (uint8)MATH_EVFR_DIVEOC_Pos, MATH_EVFR_DIVEOC_Msk) == (uint8)1)
    {
      MATH_DIVEOC_CALLBACK();
      MATH_DIVEOC_Int_Clr();
    }
  }
#endif
}
#endif

/*******************************************************************************
**                      CP ISR                                              **
*******************************************************************************/
#if    ((ADC2_VSD_UP_INT_EN == 1u)    || \
        (ADC2_VSD_LO_INT_EN == 1u)    || \
        (BDRV_VCP_LO2_INT_EN == 1u)   || \
        (ADC2_VCP_UP_INT_EN == 1u)    || \
        (ADC2_VCP_LO_INT_EN == 1u)    || \
        (ADC2_CP_TEMP_UP_INT_EN == 1u)|| \
        (ADC2_CP_TEMP_LO_INT_EN == 1u))
void CP_IRQHandler(void)
{
#if (ADC2_VCP_LO_INT_EN == 1u)
  if (u1_Field_Rd32(&BDRV->CP_IRQEN.reg, (uint8)BDRV_CP_IRQEN_VCP_LOTH1_IEN_Pos, BDRV_CP_IRQEN_VCP_LOTH1_IEN_Msk) == (uint8)1)
  {
    /* Charge Pump output voltage low threshold measured by ADC2-Ch2 */
    if (u1_Field_Rd32(&BDRV->CP_IRQS.reg, (uint8)BDRV_CP_IRQS_VCP_LOTH1_IS_Pos, BDRV_CP_IRQS_VCP_LOTH1_IS_Msk) == (uint8)1)
    {
      ADC2_VCP_LO_CALLBACK();
      ADC2_VCP_UV_Int_Clr();
    }
  }
#endif /*(ADC2_VCP_LO_INT_EN == 1u) */

#if (ADC2_VCP_UP_INT_EN == 1u)
  if (u1_Field_Rd32(&BDRV->CP_IRQEN.reg, (uint8)BDRV_CP_IRQEN_VCP_UPTH_IEN_Pos, BDRV_CP_IRQEN_VCP_UPTH_IEN_Msk) == (uint8)1)
  {
    /* Charge Pump output voltage upper threshold measured by ADC2-Ch2 */
    if (u1_Field_Rd32(&BDRV->CP_IRQS.reg, (uint8)BDRV_CP_IRQS_VCP_UPTH_IS_Pos, BDRV_CP_IRQS_VCP_UPTH_IS_Msk) == (uint8)1)
    {
      ADC2_VCP_UP_CALLBACK();
      ADC2_VCP_OV_Int_Clr();
    }
  }
#endif /*(ADC2_VCP_UP_INT_EN == 1u) */

#if (ADC2_VSD_LO_INT_EN == 1u)
  if (u1_Field_Rd32(&BDRV->CP_IRQEN.reg, (uint8)BDRV_CP_IRQEN_VSD_LOTH_IEN_Pos, BDRV_CP_IRQEN_VSD_LOTH_IEN_Msk) == (uint8)1)
  {
    /* Charge Pump input voltage low threshold measured by ADC2-Ch1 */
    if (u1_Field_Rd32(&BDRV->CP_IRQS.reg, (uint8)BDRV_CP_IRQS_VSD_LOTH_IS_Pos, BDRV_CP_IRQS_VSD_LOTH_IS_Msk) == (uint8)1)
    {
      ADC2_VSD_LO_CALLBACK();
      ADC2_VSD_UV_Int_Clr();
    }
  }
#endif /*(ADC2_VSD_LO_INT_EN == 1u) */

#if (ADC2_VSD_UP_INT_EN == 1u)
  if (u1_Field_Rd32(&BDRV->CP_IRQEN.reg, (uint8)BDRV_CP_IRQEN_VSD_UPTH_IEN_Pos, BDRV_CP_IRQEN_VSD_UPTH_IEN_Msk) == (uint8)1)
  {
    /* Charge Pump input voltage upper threshold measured by ADC2-Ch1 */
    if (u1_Field_Rd32(&BDRV->CP_IRQS.reg, (uint8)BDRV_CP_IRQS_VSD_UPTH_IS_Pos, BDRV_CP_IRQS_VSD_UPTH_IS_Msk) == (uint8)1)
    {
      ADC2_VSD_UP_CALLBACK();
      ADC2_VSD_OV_Int_Clr();
    }
  }
#endif /*(ADC2_VSD_UP_INT_EN == 1u) */

#if (BDRV_VCP_LO2_INT_EN == 1u)
  if (u1_Field_Rd32(&BDRV->CP_IRQEN.reg, (uint8)BDRV_CP_IRQEN_VCP_LOTH2_IEN_Pos, BDRV_CP_IRQEN_VCP_LOTH2_IEN_Msk) == (uint8)1)
  {
    /* Charge Pump output voltage low threshold comparator in BDRV module */
    if (u1_Field_Rd32(&BDRV->CP_IRQS.reg, (uint8)BDRV_CP_IRQS_VCP_LOTH2_IS_Pos, BDRV_CP_IRQS_VCP_LOTH2_IS_Msk) == (uint8)1)
    {
      BDRV_VCP_LO_CALLBACK();
      BDRV_VCP_LO_Int_Clr();
    }
  }
#endif /*(BDRV_VCP_LO2_INT_EN == 1u) */

#if (ADC2_CP_TEMP_UP_INT_EN == 1u)
  if (u1_Field_Rd32(&BDRV->CP_IRQEN.reg, (uint8)BDRV_CP_IRQEN_VCP_OTSD_IEN_Pos, BDRV_CP_IRQEN_VCP_OTSD_IEN_Msk) == (uint8)1)
  {
    /* Charge Pump output voltage low threshold comparator in BDRV module */
    if (u1_Field_Rd32(&BDRV->CP_IRQS.reg, (uint8)BDRV_CP_IRQS_VCP_OTSD_IS_Pos, BDRV_CP_IRQS_VCP_OTSD_IS_Msk) == (uint8)1)
    {
      ADC2_CP_TEMP_UP_CALLBACK();
      BDRV_VCP_OTSD_Int_Clr();
    }
  }
#endif /*(ADC2_CP_TEMP_UP_INT_EN == 1u) */

#if (ADC2_CP_TEMP_LO_INT_EN == 1u)
  if (u1_Field_Rd32(&BDRV->CP_IRQEN.reg, (uint8)BDRV_CP_IRQEN_VCP_OTW_IEN_Pos, BDRV_CP_IRQEN_VCP_OTW_IEN_Msk) == (uint8)1)
  {
    /* Charge Pump output voltage low threshold comparator in BDRV module */
    if (u1_Field_Rd32(&BDRV->CP_IRQS.reg, (uint8)BDRV_CP_IRQS_VCP_OTW_IS_Pos, BDRV_CP_IRQS_VCP_OTW_IS_Msk) == (uint8)1)
    {
      ADC2_CP_TEMP_LO_CALLBACK();
      BDRV_VCP_OTW_Int_Clr();
    }
  }
#endif /*(ADC2_CP_TEMP_LO_INT_EN == 1u) */

}
#endif

/*******************************************************************************
**                      BDRV ISR                                              **
*******************************************************************************/
#if     ((BDRV_HS1_OC_INT_EN == 1u)     || \
         (BDRV_LS1_OC_INT_EN == 1u)     || \
         (BDRV_HS2_OC_INT_EN == 1u)     || \
         (BDRV_LS2_OC_INT_EN == 1u)     || \
         (BDRV_HS1_DS_INT_EN == 1u)     || \
         (BDRV_LS1_DS_INT_EN == 1u)     || \
         (BDRV_HS2_DS_INT_EN == 1u)     || \
         (BDRV_LS2_DS_INT_EN == 1u)     || \
         (BDRV_SEQ_ERR_INT_EN == 1u))
void BDRV_IRQHandler(void)
{
#if (BDRV_HS1_OC_INT_EN == 1u)
  if (u1_Field_Rd32(&BDRV->IRQEN.reg, (uint8)BDRV_IRQEN_HS1_OC_IEN_Pos, BDRV_IRQEN_HS1_OC_IEN_Msk) == (uint8)1)
  {
    /* HS1 Over Current Interrupt */
    if (u1_Field_Rd32(&BDRV->IRQS.reg, (uint8)BDRV_IRQS_HS1_OC_IS_Pos, BDRV_IRQS_HS1_OC_IS_Msk) == (uint8)1)
    {
      BDRV_HS1_OC_CALLBACK();
      BDRV_HS1_OC_Int_Clr();
    }
  }
#endif /*(BDRV_HS1_OC_INT_EN == 1u) */

#if (BDRV_LS1_OC_INT_EN == 1u)
  if (u1_Field_Rd32(&BDRV->IRQEN.reg, (uint8)BDRV_IRQEN_LS1_OC_IEN_Pos, BDRV_IRQEN_LS1_OC_IEN_Msk) == (uint8)1)
  {
    /* LS1 Over Current Interrupt */
    if (u1_Field_Rd32(&BDRV->IRQS.reg, (uint8)BDRV_IRQS_LS1_OC_IS_Pos, BDRV_IRQS_LS1_OC_IS_Msk) == (uint8)1)
    {
      BDRV_LS1_OC_CALLBACK();
      BDRV_LS1_OC_Int_Clr();
    }
  }
#endif /*(BDRV_LS1_OC_INT_EN == 1u) */

#if (BDRV_HS2_OC_INT_EN == 1u)
  if (u1_Field_Rd32(&BDRV->IRQEN.reg, (uint8)BDRV_IRQEN_HS2_OC_IEN_Pos, BDRV_IRQEN_HS2_OC_IEN_Msk) == (uint8)1)
  {
    /* HS2 Over Current Interrupt */
    if (u1_Field_Rd32(&BDRV->IRQS.reg, (uint8)BDRV_IRQS_HS2_OC_IS_Pos, BDRV_IRQS_HS2_OC_IS_Msk) == (uint8)1)
    {
      BDRV_HS2_OC_CALLBACK();
      BDRV_HS2_OC_Int_Clr();
    }
  }
#endif /*(BDRV_HS2_OC_INT_EN == 1u) */

#if (BDRV_LS2_OC_INT_EN == 1u)
  if (u1_Field_Rd32(&BDRV->IRQEN.reg, (uint8)BDRV_IRQEN_LS2_OC_IEN_Pos, BDRV_IRQEN_LS2_OC_IEN_Msk) == (uint8)1)
  {
    /* LS2 Over Current Interrupt */
    if (u1_Field_Rd32(&BDRV->IRQS.reg, (uint8)BDRV_IRQS_LS2_OC_IS_Pos, BDRV_IRQS_LS2_OC_IS_Msk) == (uint8)1)
    {
      BDRV_LS2_OC_CALLBACK();
      BDRV_LS2_OC_Int_Clr();
    }
  }
#endif /*(BDRV_LS2_OC_INT_EN == 1u) */

#if (BDRV_HS1_DS_INT_EN == 1u)
  if (u1_Field_Rd32(&BDRV->IRQEN.reg, (uint8)BDRV_IRQEN_HS1_DS_IEN_Pos, BDRV_IRQEN_HS1_DS_IEN_Msk) == (uint8)1)
  {
    /* HS1 Drain Source Monitoring Interrupt */
    if (u1_Field_Rd32(&BDRV->IRQS.reg, (uint8)BDRV_IRQS_HS1_DS_IS_Pos, BDRV_IRQS_HS1_DS_IS_Msk) == (uint8)1)
    {
      BDRV_HS1_DS_CALLBACK();
      BDRV_HS1_DS_Int_Clr();
    }
  }
#endif /*(BDRV_HS1_DS_INT_EN == 1u) */

#if (BDRV_LS1_DS_INT_EN == 1u)
  if (u1_Field_Rd32(&BDRV->IRQEN.reg, (uint8)BDRV_IRQEN_LS1_DS_IEN_Pos, BDRV_IRQEN_LS1_DS_IEN_Msk) == (uint8)1)
  {
    /* LS1 Drain Source Monitoring Interrupt */
    if (u1_Field_Rd32(&BDRV->IRQS.reg, (uint8)BDRV_IRQS_LS1_DS_IS_Pos, BDRV_IRQS_LS1_DS_IS_Msk) == (uint8)1)
    {
      BDRV_LS1_DS_CALLBACK();
      BDRV_LS1_DS_Int_Clr();
    }
  }
#endif /*(BDRV_LS1_DS_INT_EN == 1u) */

#if (BDRV_HS2_DS_INT_EN == 1u)
  if (u1_Field_Rd32(&BDRV->IRQEN.reg, (uint8)BDRV_IRQEN_HS2_DS_IEN_Pos, BDRV_IRQEN_HS2_DS_IEN_Msk) == (uint8)1)
  {
    /* HS2 Drain Source Monitoring Interrupt */
    if (u1_Field_Rd32(&BDRV->IRQS.reg, (uint8)BDRV_IRQS_HS2_DS_IS_Pos, BDRV_IRQS_HS2_DS_IS_Msk) == (uint8)1)
    {
      BDRV_HS2_DS_CALLBACK();
      BDRV_HS2_DS_Int_Clr();
    }
  }
#endif /*(BDRV_HS2_DS_INT_EN == 1u) */

#if (BDRV_LS2_DS_INT_EN == 1u)
  if (u1_Field_Rd32(&BDRV->IRQEN.reg, (uint8)BDRV_IRQEN_LS2_DS_IEN_Pos, BDRV_IRQEN_LS2_DS_IEN_Msk) == (uint8)1)
  {
    /* LS2 Drain Source Monitoring Interrupt */
    if (u1_Field_Rd32(&BDRV->IRQS.reg, (uint8)BDRV_IRQS_LS2_DS_IS_Pos, BDRV_IRQS_LS2_DS_IS_Msk) == (uint8)1)
    {
      BDRV_LS2_DS_CALLBACK();
      BDRV_LS2_DS_Int_Clr();
    }
  }
#endif /*(BDRV_LS2_DS_INT_EN == 1u) */

#if (BDRV_SEQ_ERR_INT_EN == 1u)
  if (u1_Field_Rd32(&BDRV->IRQEN.reg, (uint8)BDRV_IRQEN_SEQ_ERR_IEN_Pos, BDRV_IRQEN_SEQ_ERR_IEN_Msk) == (uint8)1)
  {
    /* Driver Sequence Error Interrupt */
    if (u1_Field_Rd32(&BDRV->IRQS.reg, (uint8)BDRV_IRQS_SEQ_ERR_IS_Pos, BDRV_IRQS_SEQ_ERR_IS_Msk) == (uint8)1)
    {
      BDRV_SEQ_ERR_CALLBACK();
      BDRV_SEQ_ERR_Int_Clr();
    }
  }
#endif /*(BDRV_SEQ_ERR_INT_EN == 1u) */
}
#endif


/*******************************************************************************
**                      HS ISR                                              **
*******************************************************************************/
#if      ((HS_HS1_OT_INT_EN == 1u)     || \
          (HS_HS1_OL_INT_EN == 1u)     || \
          (HS_HS1_OC_INT_EN == 1u))
void HS_IRQHandler(void)
{
#if (HS_HS1_OT_INT_EN == 1u)
  if (u1_Field_Rd32(&HS->IRQEN.reg, (uint8)HS_IRQEN_HS1_OT_IEN_Pos, HS_IRQEN_HS1_OT_IEN_Msk) == (uint8)1)
  {
    /* HS1 Over Temp Interrupt */
    if (u1_Field_Rd32(&HS->IRQS.reg, (uint8)HS_IRQS_HS1_OT_IS_Pos, HS_IRQS_HS1_OT_IS_Msk) == (uint8)1)
    {
      HS_HS1_OT_CALLBACK();
      HS_HS1_OT_Int_Clr();
    }
  }
#endif /*(HS_HS1_OT_INT_EN == 1u) */

#if (HS_HS1_OL_INT_EN == 1u)
  if (u1_Field_Rd32(&HS->IRQEN.reg, (uint8)HS_IRQEN_HS1_OL_IEN_Pos, HS_IRQEN_HS1_OL_IEN_Msk) == (uint8)1)
  {
    /* HS1 Over Load Interrupt */
    if (u1_Field_Rd32(&HS->IRQS.reg, (uint8)HS_IRQS_HS1_OL_IS_Pos, HS_IRQS_HS1_OL_IS_Msk) == (uint8)1)
    {
      HS_HS1_OL_CALLBACK();
      HS_HS1_OL_Int_Clr();
    }
  }
#endif /*(HS_HS1_OL_INT_EN == 1u) */

#if (HS_HS1_OC_INT_EN == 1u)
  if (u1_Field_Rd32(&HS->IRQEN.reg, (uint8)HS_IRQEN_HS1_OC_IEN_Pos, HS_IRQEN_HS1_OC_IEN_Msk) == (uint8)1)
  {
    /* HS1 Over Current Interrupt */
    if (u1_Field_Rd32(&HS->IRQS.reg, (uint8)HS_IRQS_HS1_OC_IS_Pos, HS_IRQS_HS1_OC_IS_Msk) == (uint8)1)
    {
      HS_HS1_OC_CALLBACK();
      HS_HS1_OC_Int_Clr();
    }
  }
#endif /*(HS_HS1_OC_INT_EN == 1u) */
}
#endif

/*******************************************************************************
**                      CSA ISR                                              **
*******************************************************************************/
#if ((CPU_NVIC_ISER & (1u << 20u)) != 0u)
void CSA_IRQHandler(void)
{
  if (u1_Field_Rd32(&ADC1->PP_MAP0_3.reg, (uint8)ADC1_PP_MAP0_3_EN_PP_MAP2_Pos, ADC1_PP_MAP0_3_EN_PP_MAP2_Msk) == (uint8)1)
  {
    if (u8_Field_Rd32(&ADC1->PP_MAP0_3.reg, (uint8)ADC1_PP_MAP0_3_PP_MAP2_Pos, ADC1_PP_MAP0_3_PP_MAP2_Msk) == (uint8)0xD)
    {
#if (ADC1_PP_CH2_UP_INT_EN == 1u)
    /* ADC1 - PP Ch2 UP Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH2_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH2_UP_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH2_UP_IS_Pos, ADC1_IRQS_2_PP_CH2_UP_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH2_UP_CALLBACK();
          ADC1_PP_Ch2_UP_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH2_UP_INT_EN == 1u) */
#if (ADC1_PP_CH2_LO_INT_EN == 1u)
      /* ADC1 - PP Ch2 LO Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH2_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH2_LO_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH2_LO_IS_Pos, ADC1_IRQS_2_PP_CH2_LO_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH2_LO_CALLBACK();
          ADC1_PP_Ch2_LO_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH2_LO_INT_EN == 1u) */
    }
  }

  if (u1_Field_Rd32(&ADC1->PP_MAP0_3.reg, (uint8)ADC1_PP_MAP0_3_EN_PP_MAP3_Pos, ADC1_PP_MAP0_3_EN_PP_MAP3_Msk) == (uint8)1)
  {
    if (u8_Field_Rd32(&ADC1->PP_MAP0_3.reg, (uint8)ADC1_PP_MAP0_3_PP_MAP3_Pos, ADC1_PP_MAP0_3_PP_MAP3_Msk) == (uint8)0xD)
    {
#if (ADC1_PP_CH3_UP_INT_EN == 1u)
      /* ADC1 - PP Ch3 UP Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH3_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH3_UP_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH3_UP_IS_Pos, ADC1_IRQS_2_PP_CH3_UP_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH3_UP_CALLBACK();
          ADC1_PP_Ch3_UP_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH3_UP_INT_EN == 1u) */
#if (ADC1_PP_CH3_LO_INT_EN == 1u)
    /* ADC1 - PP Ch3 LO Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH3_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH3_LO_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH3_LO_IS_Pos, ADC1_IRQS_2_PP_CH3_LO_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH3_LO_CALLBACK();
          ADC1_PP_Ch3_LO_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH3_LO_INT_EN == 1u) */
    }
  }

  if (u1_Field_Rd32(&ADC1->PP_MAP4_7.reg, (uint8)ADC1_PP_MAP4_7_EN_PP_MAP4_Pos, ADC1_PP_MAP4_7_EN_PP_MAP4_Msk) == (uint8)1)
  {
    if (u8_Field_Rd32(&ADC1->PP_MAP4_7.reg, (uint8)ADC1_PP_MAP4_7_PP_MAP4_Pos, ADC1_PP_MAP4_7_PP_MAP4_Msk) == (uint8)0xD)
    {
#if (ADC1_PP_CH4_UP_INT_EN == 1u)
    /* ADC1 - PP Ch4 UP Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH4_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH4_UP_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH4_UP_IS_Pos, ADC1_IRQS_2_PP_CH4_UP_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH4_UP_CALLBACK();
          ADC1_PP_Ch4_UP_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH4_UP_INT_EN == 1u) */
#if (ADC1_PP_CH4_LO_INT_EN == 1u)
    /* ADC1 - PP Ch4 LO Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH4_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH4_LO_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH4_LO_IS_Pos, ADC1_IRQS_2_PP_CH4_LO_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH4_LO_CALLBACK();
          ADC1_PP_Ch4_LO_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH4_LO_INT_EN == 1u) */
    }
  }

  if (u1_Field_Rd32(&ADC1->PP_MAP4_7.reg, (uint8)ADC1_PP_MAP4_7_EN_PP_MAP5_Pos, ADC1_PP_MAP4_7_EN_PP_MAP5_Msk) == (uint8)1)
  {
    if (u8_Field_Rd32(&ADC1->PP_MAP4_7.reg, (uint8)ADC1_PP_MAP4_7_PP_MAP5_Pos, ADC1_PP_MAP4_7_PP_MAP5_Msk) == (uint8)0xD)
    {
#if (ADC1_PP_CH5_UP_INT_EN == 1u)
    /* ADC1 - PP Ch5 UP Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH5_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH5_UP_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH5_UP_IS_Pos, ADC1_IRQS_2_PP_CH5_UP_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH5_UP_CALLBACK();
          ADC1_PP_Ch5_UP_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH5_UP_INT_EN == 1u) */
#if (ADC1_PP_CH5_LO_INT_EN == 1u)
    /* ADC1 - PP Ch5 LO Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH5_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH5_LO_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH5_LO_IS_Pos, ADC1_IRQS_2_PP_CH5_LO_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH5_LO_CALLBACK();
          ADC1_PP_Ch5_LO_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH5_LO_INT_EN == 1u) */
    }
  }

  if (u1_Field_Rd32(&ADC1->PP_MAP4_7.reg, (uint8)ADC1_PP_MAP4_7_EN_PP_MAP6_Pos, ADC1_PP_MAP4_7_EN_PP_MAP6_Msk) == (uint8)1)
  {
    if (u8_Field_Rd32(&ADC1->PP_MAP4_7.reg, (uint8)ADC1_PP_MAP4_7_PP_MAP6_Pos, ADC1_PP_MAP4_7_PP_MAP6_Msk) == (uint8)0xD)
    {
#if (ADC1_PP_CH6_UP_INT_EN == 1u)
    /* ADC1 - PP Ch6 UP Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH6_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH6_UP_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH6_UP_IS_Pos, ADC1_IRQS_2_PP_CH6_UP_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH6_UP_CALLBACK();
          ADC1_PP_Ch6_UP_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH6_UP_INT_EN == 1u) */
#if (ADC1_PP_CH6_LO_INT_EN == 1u)
    /* ADC1 - PP Ch6 LO Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH6_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH6_LO_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH6_LO_IS_Pos, ADC1_IRQS_2_PP_CH6_LO_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH6_LO_CALLBACK();
          ADC1_PP_Ch6_LO_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH6_LO_INT_EN == 1u) */
    }
  }

  if (u1_Field_Rd32(&ADC1->PP_MAP4_7.reg, (uint8)ADC1_PP_MAP4_7_EN_PP_MAP7_Pos, ADC1_PP_MAP4_7_EN_PP_MAP7_Msk) == (uint8)1)
  {
    if (u8_Field_Rd32(&ADC1->PP_MAP4_7.reg, (uint8)ADC1_PP_MAP4_7_PP_MAP7_Pos, ADC1_PP_MAP4_7_PP_MAP7_Msk) == (uint8)0xD)
    {
#if (ADC1_PP_CH7_UP_INT_EN == 1u)
    /* ADC1 - PP Ch7 UP Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH7_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH7_UP_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH7_UP_IS_Pos, ADC1_IRQS_2_PP_CH7_UP_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH7_UP_CALLBACK();
          ADC1_PP_Ch7_UP_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH7_UP_INT_EN == 1u) */
#if (ADC1_PP_CH7_LO_INT_EN == 1u)
    /* ADC1 - PP Ch7 LO Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH7_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH7_LO_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH7_LO_IS_Pos, ADC1_IRQS_2_PP_CH7_LO_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH7_LO_CALLBACK();
          ADC1_PP_Ch7_LO_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH7_LO_INT_EN == 1u) */
    }
  }
}
#endif

/*******************************************************************************
**                      DU1 ISR                                              **
*******************************************************************************/
#if    ((ADC1_DU1UP_INT_EN == 1u)        || \
        (ADC1_DU1LO_INT_EN == 1u))

void DU1_IRQHandler(void)
{
#if (ADC1_DU1UP_INT_EN == 1u)
  /* ADC1 - DU1UP Interrupt */
  if (u1_Field_Rd32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_DU1UP_IEN_Pos, ADC1_IRQEN_1_DU1UP_IEN_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&ADC1->IRQS_1.reg, (uint8)ADC1_IRQS_1_DU1UP_IS_Pos, ADC1_IRQS_1_DU1UP_IS_Msk) == (uint8)1)
    {
      ADC1_DU1UP_CALLBACK();
      ADC1_DU1UP_Int_Clr();
    }
  }
#endif /*(ADC1_DU1UP_INT_EN == 1u) */

#if (ADC1_DU1LO_INT_EN == 1u)
  /* ADC1 - DU1LO Interrupt */
  if (u1_Field_Rd32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_DU1LO_IEN_Pos, ADC1_IRQEN_1_DU1LO_IEN_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&ADC1->IRQS_1.reg, (uint8)ADC1_IRQS_1_DU1LO_IS_Pos, ADC1_IRQS_1_DU1LO_IS_Msk) == (uint8)1)
    {
      ADC1_DU1LO_CALLBACK();
      ADC1_DU1LO_Int_Clr();
    }
  }
#endif /*(ADC1_DU1LO_INT_EN == 1u) */
}
#endif

/*******************************************************************************
**                      MONx ISR                                           **
*******************************************************************************/
#if ((CPU_NVIC_ISER & (1u << 22u)) != 0u)
void MONx_IRQHandler(void)
{
  uint8 pp2_map;
  uint8 pp3_map;
  uint8 pp4_map;
  uint8 pp5_map;
  uint8 pp6_map;
  uint8 pp7_map;
  pp2_map = u8_Field_Rd32(&ADC1->PP_MAP0_3.reg, (uint8)ADC1_PP_MAP0_3_PP_MAP2_Pos, ADC1_PP_MAP0_3_PP_MAP2_Msk);
  pp3_map = u8_Field_Rd32(&ADC1->PP_MAP0_3.reg, (uint8)ADC1_PP_MAP0_3_PP_MAP3_Pos, ADC1_PP_MAP0_3_PP_MAP3_Msk);
  pp4_map = u8_Field_Rd32(&ADC1->PP_MAP4_7.reg, (uint8)ADC1_PP_MAP4_7_PP_MAP4_Pos, ADC1_PP_MAP4_7_PP_MAP4_Msk);
  pp5_map = u8_Field_Rd32(&ADC1->PP_MAP4_7.reg, (uint8)ADC1_PP_MAP4_7_PP_MAP5_Pos, ADC1_PP_MAP4_7_PP_MAP5_Msk);
  pp6_map = u8_Field_Rd32(&ADC1->PP_MAP4_7.reg, (uint8)ADC1_PP_MAP4_7_PP_MAP6_Pos, ADC1_PP_MAP4_7_PP_MAP6_Msk);
  pp7_map = u8_Field_Rd32(&ADC1->PP_MAP4_7.reg, (uint8)ADC1_PP_MAP4_7_PP_MAP7_Pos, ADC1_PP_MAP4_7_PP_MAP7_Msk);

#if ((SCU_MONIEN & (1u << 0u)) != 0u)
#if (MON1_FALLING_INT_EN == 1u)
  if ((u1_Field_Rd32(&SCU->EXICON1.reg, (uint8)1u, (1u << 1u))) != 0u)
  {
    /* MON1 Pin Interrupt - Falling Edge */
    if (u1_Field_Rd32(&SCU->IRCON1.reg, (uint8)SCU_IRCON1_MON1F_Pos, SCU_IRCON1_MON1F_Msk) == (uint8)1)
    {
      MON1_FALLING_CALLBACK();
      MON1_Falling_Edge_Int_Clr();
    }
  }
#endif /* (MON1_FALLING_INT_EN == 1u) */

#if (MON1_RISING_INT_EN == 1u)
  if (u1_Field_Rd32(&SCU->EXICON1.reg, 0u, 1u) != 0u)
  {
    /* MON1 Pin Interrupt - Rising Edge */
    if (u1_Field_Rd32(&SCU->IRCON1.reg, (uint8)SCU_IRCON1_MON1R_Pos, SCU_IRCON1_MON1R_Msk) == (uint8)1)
    {
      MON1_RISING_CALLBACK();
      MON1_Rising_Edge_Int_Clr();
    }
  }
#endif /* (MON1_RISING_INT_EN == 1u) */
#endif /*((SCU_MONIEN & (1u << 0u)) != 0u) */
#if ((SCU_MONIEN & (1u << 1u)) != 0u)
#if (MON2_FALLING_INT_EN == 1u)
  if ((u1_Field_Rd32(&SCU->EXICON1.reg, (uint8)3u, (1u << 3u))) != 0u)
  {
    /* MON2 Pin Interrupt - Falling Edge */
    if (u1_Field_Rd32(&SCU->IRCON1.reg, (uint8)SCU_IRCON1_MON2F_Pos, SCU_IRCON1_MON2F_Msk) == (uint8)1)
    {
      MON2_FALLING_CALLBACK();
      MON2_Falling_Edge_Int_Clr();
    }
  }
#endif /* (MON2_FALLING_INT_EN == 1u) */

#if (MON2_RISING_INT_EN == 1u)
  if ((u1_Field_Rd32(&SCU->EXICON1.reg, (uint8)2u, (1u << 2u))) != 0u)
  {
    /* MON2 Pin Interrupt - Rising Edge */
    if (u1_Field_Rd32(&SCU->IRCON1.reg, (uint8)SCU_IRCON1_MON2R_Pos, SCU_IRCON1_MON2R_Msk) == (uint8)1)
    {
      MON2_RISING_CALLBACK();
      MON2_Rising_Edge_Int_Clr();
    }
  }
#endif /* (MON2_RISING_INT_EN == 1u) */
#endif /*((SCU_MONIEN & (1u << 1u)) != 0u) */
#if ((SCU_MONIEN & (1u << 2u)) != 0u)
#if (MON3_FALLING_INT_EN == 1u)
  if ((u1_Field_Rd32(&SCU->EXICON1.reg, (uint8)5u, (1u << 5u))) != 0u)
  {
    /* MON3 Pin Interrupt - Falling Edge */
    if (u1_Field_Rd32(&SCU->IRCON1.reg, (uint8)SCU_IRCON1_MON3F_Pos, SCU_IRCON1_MON3F_Msk) == (uint8)1)
    {
      MON3_FALLING_CALLBACK();
      MON3_Falling_Edge_Int_Clr();
    }
  }
#endif /* (MON3_FALLING_INT_EN == 1u) */

#if (MON3_RISING_INT_EN == 1u)
  if ((u1_Field_Rd32(&SCU->EXICON1.reg, (uint8)4u, (1u << 4u))) != 0u)
  {
    /* MON3 Pin Interrupt - Rising Edge */
    if (u1_Field_Rd32(&SCU->IRCON1.reg, (uint8)SCU_IRCON1_MON3R_Pos, SCU_IRCON1_MON3R_Msk) == (uint8)1)
    {
      MON3_RISING_CALLBACK();
      MON3_Rising_Edge_Int_Clr();
    }
  }
#endif /* (MON3_RISING_INT_EN == 1u) */
#endif /*((SCU_MONIEN & (1u << 2u)) != 0u) */
#if ((SCU_MONIEN & (1u << 3u)) != 0u)
#if (MON4_FALLING_INT_EN == 1u)
  if ((u1_Field_Rd32(&SCU->EXICON1.reg, (uint8)7u, (1u << 7u))) != 0u)
  {
    /* MON4 Pin Interrupt - Falling Edge */
    if (u1_Field_Rd32(&SCU->IRCON1.reg, (uint8)SCU_IRCON1_MON4F_Pos, SCU_IRCON1_MON4F_Msk) == (uint8)1)
    {
      MON4_FALLING_CALLBACK();
      MON4_Falling_Edge_Int_Clr();
    }
  }
#endif /* (MON4_FALLING_INT_EN == 1u) */

#if (MON4_RISING_INT_EN == 1u)
  if ((u1_Field_Rd32(&SCU->EXICON1.reg, (uint8)6u, (1u << 6u))) != 0u)
  {
    /* MON4 Pin Interrupt - Rising Edge */
    if (u1_Field_Rd32(&SCU->IRCON1.reg, (uint8)SCU_IRCON1_MON4R_Pos, SCU_IRCON1_MON4R_Msk) == (uint8)1)
    {
      MON4_RISING_CALLBACK();
      MON4_Rising_Edge_Int_Clr();
    }
  }
#endif /* (MON4_RISING_INT_EN == 1u) */
#endif /*((SCU_MONIEN & (1u << 3u)) != 0u) */

  if (u1_Field_Rd32(&ADC1->PP_MAP0_3.reg, (uint8)ADC1_PP_MAP0_3_EN_PP_MAP2_Pos, ADC1_PP_MAP0_3_EN_PP_MAP2_Msk) == (uint8)1)
  {
    if (((uint8)0x2 <= pp2_map) && (pp2_map <= (uint8)0x5))
    {
#if (ADC1_PP_CH2_UP_INT_EN == 1u)
    /* ADC1 - PP Ch2 UP Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH2_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH2_UP_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH2_UP_IS_Pos, ADC1_IRQS_2_PP_CH2_UP_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH2_UP_CALLBACK();
          ADC1_PP_Ch2_UP_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH2_UP_INT_EN == 1u) */
#if (ADC1_PP_CH2_LO_INT_EN == 1u)
      /* ADC1 - PP Ch2 LO Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH2_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH2_LO_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH2_LO_IS_Pos, ADC1_IRQS_2_PP_CH2_LO_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH2_LO_CALLBACK();
          ADC1_PP_Ch2_LO_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH2_LO_INT_EN == 1u) */
    }
  }

  if (u1_Field_Rd32(&ADC1->PP_MAP0_3.reg, (uint8)ADC1_PP_MAP0_3_EN_PP_MAP3_Pos, ADC1_PP_MAP0_3_EN_PP_MAP3_Msk) == (uint8)1)
  {
    if (((uint8)0x2 <= pp3_map) && (pp3_map <= (uint8)0x5))
    {
#if (ADC1_PP_CH3_UP_INT_EN == 1u)
    /* ADC1 - PP Ch3 UP Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH3_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH3_UP_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH3_UP_IS_Pos, ADC1_IRQS_2_PP_CH3_UP_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH3_UP_CALLBACK();
          ADC1_PP_Ch3_UP_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH3_UP_INT_EN == 1u) */
#if (ADC1_PP_CH3_LO_INT_EN == 1u)
    /* ADC1 - PP Ch3 LO Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH3_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH3_LO_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH3_LO_IS_Pos, ADC1_IRQS_2_PP_CH3_LO_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH3_LO_CALLBACK();
          ADC1_PP_Ch3_LO_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH3_LO_INT_EN == 1u) */
    }
  }

  if (u1_Field_Rd32(&ADC1->PP_MAP4_7.reg, (uint8)ADC1_PP_MAP4_7_EN_PP_MAP4_Pos, ADC1_PP_MAP4_7_EN_PP_MAP4_Msk) == (uint8)1)
  {
    if (((uint8)0x2 <= pp4_map) && (pp4_map <= (uint8)0x5))
    {
#if (ADC1_PP_CH4_UP_INT_EN == 1u)
    /* ADC1 - PP Ch4 UP Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH4_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH4_UP_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH4_UP_IS_Pos, ADC1_IRQS_2_PP_CH4_UP_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH4_UP_CALLBACK();
          ADC1_PP_Ch4_UP_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH4_UP_INT_EN == 1u) */
#if (ADC1_PP_CH4_LO_INT_EN == 1u)
    /* ADC1 - PP Ch4 LO Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH4_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH4_LO_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH4_LO_IS_Pos, ADC1_IRQS_2_PP_CH4_LO_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH4_LO_CALLBACK();
          ADC1_PP_Ch4_LO_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH4_LO_INT_EN == 1u) */
    }
  }

  if (u1_Field_Rd32(&ADC1->PP_MAP4_7.reg, (uint8)ADC1_PP_MAP4_7_EN_PP_MAP5_Pos, ADC1_PP_MAP4_7_EN_PP_MAP5_Msk) == (uint8)1)
  {
    if (((uint8)0x2 <= pp5_map) && (pp5_map <= (uint8)0x5))
    {
#if (ADC1_PP_CH5_UP_INT_EN == 1u)
    /* ADC1 - PP Ch5 UP Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH5_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH5_UP_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH5_UP_IS_Pos, ADC1_IRQS_2_PP_CH5_UP_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH5_UP_CALLBACK();
          ADC1_PP_Ch5_UP_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH5_UP_INT_EN == 1u) */
#if (ADC1_PP_CH5_LO_INT_EN == 1u)
    /* ADC1 - PP Ch5 LO Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH5_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH5_LO_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH5_LO_IS_Pos, ADC1_IRQS_2_PP_CH5_LO_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH5_LO_CALLBACK();
          ADC1_PP_Ch5_LO_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH5_LO_INT_EN == 1u) */
    }
  }

  if (u1_Field_Rd32(&ADC1->PP_MAP4_7.reg, (uint8)ADC1_PP_MAP4_7_EN_PP_MAP6_Pos, ADC1_PP_MAP4_7_EN_PP_MAP6_Msk) == (uint8)1)
  {
    if (((uint8)0x2 <= pp6_map) && (pp6_map <= (uint8)0x5))
    {
#if (ADC1_PP_CH6_UP_INT_EN == 1u)
    /* ADC1 - PP Ch6 UP Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH6_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH6_UP_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH6_UP_IS_Pos, ADC1_IRQS_2_PP_CH6_UP_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH6_UP_CALLBACK();
          ADC1_PP_Ch6_UP_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH6_UP_INT_EN == 1u) */
#if (ADC1_PP_CH6_LO_INT_EN == 1u)
    /* ADC1 - PP Ch6 LO Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH6_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH6_LO_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH6_LO_IS_Pos, ADC1_IRQS_2_PP_CH6_LO_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH6_LO_CALLBACK();
          ADC1_PP_Ch6_LO_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH6_LO_INT_EN == 1u) */
    }
  }

  if (u1_Field_Rd32(&ADC1->PP_MAP4_7.reg, (uint8)ADC1_PP_MAP4_7_EN_PP_MAP7_Pos, ADC1_PP_MAP4_7_EN_PP_MAP7_Msk) == (uint8)1)
  {
    if (((uint8)0x2 <= pp7_map) && (pp7_map <= (uint8)0x5))
    {
#if (ADC1_PP_CH7_UP_INT_EN == 1u)
    /* ADC1 - PP Ch7 UP Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH7_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH7_UP_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH7_UP_IS_Pos, ADC1_IRQS_2_PP_CH7_UP_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH7_UP_CALLBACK();
          ADC1_PP_Ch7_UP_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH7_UP_INT_EN == 1u) */
#if (ADC1_PP_CH7_LO_INT_EN == 1u)
    /* ADC1 - PP Ch7 LO Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH7_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH7_LO_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH7_LO_IS_Pos, ADC1_IRQS_2_PP_CH7_LO_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH7_LO_CALLBACK();
          ADC1_PP_Ch7_LO_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH7_LO_INT_EN == 1u) */
    }
  }
}
#endif

/*******************************************************************************
**                      PORT2 ISR                                              **
*******************************************************************************/
#if ((CPU_NVIC_ISER & (1u << 23u)) != 0u)
void PORT2_IRQHandler(void)
{
  uint8 pp2_map;
  uint8 pp3_map;
  uint8 pp4_map;
  uint8 pp5_map;
  uint8 pp6_map;
  uint8 pp7_map;
  pp2_map = u8_Field_Rd32(&ADC1->PP_MAP0_3.reg, (uint8)ADC1_PP_MAP0_3_PP_MAP2_Pos, ADC1_PP_MAP0_3_PP_MAP2_Msk);
  pp3_map = u8_Field_Rd32(&ADC1->PP_MAP0_3.reg, (uint8)ADC1_PP_MAP0_3_PP_MAP3_Pos, ADC1_PP_MAP0_3_PP_MAP3_Msk);
  pp4_map = u8_Field_Rd32(&ADC1->PP_MAP4_7.reg, (uint8)ADC1_PP_MAP4_7_PP_MAP4_Pos, ADC1_PP_MAP4_7_PP_MAP4_Msk);
  pp5_map = u8_Field_Rd32(&ADC1->PP_MAP4_7.reg, (uint8)ADC1_PP_MAP4_7_PP_MAP5_Pos, ADC1_PP_MAP4_7_PP_MAP5_Msk);
  pp6_map = u8_Field_Rd32(&ADC1->PP_MAP4_7.reg, (uint8)ADC1_PP_MAP4_7_PP_MAP6_Pos, ADC1_PP_MAP4_7_PP_MAP6_Msk);
  pp7_map = u8_Field_Rd32(&ADC1->PP_MAP4_7.reg, (uint8)ADC1_PP_MAP4_7_PP_MAP7_Pos, ADC1_PP_MAP4_7_PP_MAP7_Msk);

  if (u1_Field_Rd32(&ADC1->PP_MAP0_3.reg, (uint8)ADC1_PP_MAP0_3_EN_PP_MAP2_Pos, ADC1_PP_MAP0_3_EN_PP_MAP2_Msk) == (uint8)1)
  {
    if (((uint8)0x6 <= pp2_map) && (pp2_map <= (uint8)0xC))
    {
#if (ADC1_PP_CH2_UP_INT_EN == 1u)
    /* ADC1 - PP Ch2 UP Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH2_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH2_UP_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH2_UP_IS_Pos, ADC1_IRQS_2_PP_CH2_UP_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH2_UP_CALLBACK();
          ADC1_PP_Ch2_UP_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH2_UP_INT_EN == 1u) */
#if (ADC1_PP_CH2_LO_INT_EN == 1u)
    /* ADC1 - PP Ch2 LO Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH2_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH2_LO_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH2_LO_IS_Pos, ADC1_IRQS_2_PP_CH2_LO_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH2_LO_CALLBACK();
          ADC1_PP_Ch2_LO_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH2_LO_INT_EN == 1u) */
    }
  }

  if (u1_Field_Rd32(&ADC1->PP_MAP0_3.reg, (uint8)ADC1_PP_MAP0_3_EN_PP_MAP3_Pos, ADC1_PP_MAP0_3_EN_PP_MAP3_Msk) == (uint8)1)
  {
    if (((uint8)0x6 <= pp3_map) && (pp3_map <= (uint8)0xC))
    {
#if (ADC1_PP_CH3_UP_INT_EN == 1u)
    /* ADC1 - PP Ch3 UP Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH3_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH3_UP_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH3_UP_IS_Pos, ADC1_IRQS_2_PP_CH3_UP_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH3_UP_CALLBACK();
          ADC1_PP_Ch3_UP_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH3_UP_INT_EN == 1u) */
#if (ADC1_PP_CH3_LO_INT_EN == 1u)
    /* ADC1 - PP Ch3 LO Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH3_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH3_LO_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH3_LO_IS_Pos, ADC1_IRQS_2_PP_CH3_LO_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH3_LO_CALLBACK();
          ADC1_PP_Ch3_LO_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH3_LO_INT_EN == 1u) */
    }
  }

  if (u1_Field_Rd32(&ADC1->PP_MAP4_7.reg, (uint8)ADC1_PP_MAP4_7_EN_PP_MAP4_Pos, ADC1_PP_MAP4_7_EN_PP_MAP4_Msk) == (uint8)1)
  {
    if (((uint8)0x6 <= pp4_map) && (pp4_map <= (uint8)0xC))
    {
#if (ADC1_PP_CH4_UP_INT_EN == 1u)
    /* ADC1 - PP Ch4 UP Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH4_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH4_UP_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH4_UP_IS_Pos, ADC1_IRQS_2_PP_CH4_UP_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH4_UP_CALLBACK();
          ADC1_PP_Ch4_UP_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH4_UP_INT_EN == 1u) */
#if (ADC1_PP_CH4_LO_INT_EN == 1u)
    /* ADC1 - PP Ch4 LO Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH4_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH4_LO_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH4_LO_IS_Pos, ADC1_IRQS_2_PP_CH4_LO_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH4_LO_CALLBACK();
          ADC1_PP_Ch4_LO_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH4_LO_INT_EN == 1u) */
    }
  }

  if (u1_Field_Rd32(&ADC1->PP_MAP4_7.reg, (uint8)ADC1_PP_MAP4_7_EN_PP_MAP5_Pos, ADC1_PP_MAP4_7_EN_PP_MAP5_Msk) == (uint8)1)
  {
    if (((uint8)0x6 <= pp5_map) && (pp5_map <= (uint8)0xC))
    {
#if (ADC1_PP_CH5_UP_INT_EN == 1u)
    /* ADC1 - PP Ch5 UP Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH5_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH5_UP_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH5_UP_IS_Pos, ADC1_IRQS_2_PP_CH5_UP_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH5_UP_CALLBACK();
          ADC1_PP_Ch5_UP_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH5_UP_INT_EN == 1u) */
#if (ADC1_PP_CH5_LO_INT_EN == 1u)
    /* ADC1 - PP Ch5 LO Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH5_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH5_LO_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH5_LO_IS_Pos, ADC1_IRQS_2_PP_CH5_LO_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH5_LO_CALLBACK();
          ADC1_PP_Ch5_LO_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH5_LO_INT_EN == 1u) */
    }
  }

  if (u1_Field_Rd32(&ADC1->PP_MAP4_7.reg, (uint8)ADC1_PP_MAP4_7_EN_PP_MAP6_Pos, ADC1_PP_MAP4_7_EN_PP_MAP6_Msk) == (uint8)1)
  {
    if (((uint8)0x6 <= pp6_map) && (pp6_map <= (uint8)0xC))
    {
#if (ADC1_PP_CH6_UP_INT_EN == 1u)
    /* ADC1 - PP Ch6 UP Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH6_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH6_UP_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH6_UP_IS_Pos, ADC1_IRQS_2_PP_CH6_UP_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH6_UP_CALLBACK();
          ADC1_PP_Ch6_UP_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH6_UP_INT_EN == 1u) */
#if (ADC1_PP_CH6_LO_INT_EN == 1u)
    /* ADC1 - PP Ch6 LO Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH6_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH6_LO_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH6_LO_IS_Pos, ADC1_IRQS_2_PP_CH6_LO_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH6_LO_CALLBACK();
          ADC1_PP_Ch6_LO_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH6_LO_INT_EN == 1u) */
    }
  }

  if (u1_Field_Rd32(&ADC1->PP_MAP4_7.reg, (uint8)ADC1_PP_MAP4_7_EN_PP_MAP7_Pos, ADC1_PP_MAP4_7_EN_PP_MAP7_Msk) == (uint8)1)
  {
    if (((uint8)0x6 <= pp7_map) && (pp7_map <= (uint8)0xC))
    {
#if (ADC1_PP_CH7_UP_INT_EN == 1u)
    /* ADC1 - PP Ch7 UP Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH7_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH7_UP_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH7_UP_IS_Pos, ADC1_IRQS_2_PP_CH7_UP_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH7_UP_CALLBACK();
          ADC1_PP_Ch7_UP_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH7_UP_INT_EN == 1u) */
#if (ADC1_PP_CH7_LO_INT_EN == 1u)
    /* ADC1 - PP Ch7 LO Interrupt */
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH7_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH7_LO_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH7_LO_IS_Pos, ADC1_IRQS_2_PP_CH7_LO_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH7_LO_CALLBACK();
          ADC1_PP_Ch7_LO_Int_Clr();
        }
      }
#endif /*(ADC1_PP_CH7_LO_INT_EN == 1u) */
    }
  }
}
#endif

/*******************************************************************************
**                      NMI ISR                                               **
*******************************************************************************/
#if     ((SCU_NMI_WDT_INT_EN      == 1u)     || \
         (SCU_NMI_PLL_INT_EN      == 1u)     || \
         (SCU_NMI_STOF_INT_EN     == 1u)     || \
         (SCU_NMI_OWD_INT_EN      == 1u)     || \
         (SCU_NMI_MAP_INT_EN      == 1u)     || \
         (SCU_ECC_RAM_DB_INT_EN   == 1u)     || \
         (SCU_ECC_NVM_DB_INT_EN   == 1u)     || \
         (ADC2_SYS_TEMP_UP_INT_EN == 1u)     || \
         (ADC2_SYS_TEMP_LO_INT_EN == 1u)     || \
         (ADC2_VS_UP_INT_EN       == 1u)     || \
         (ADC2_VS_LO_INT_EN       == 1u)     || \
         (ADC2_VDDC_UP_INT_EN     == 1u)     || \
         (ADC2_VDDC_LO_INT_EN     == 1u)     || \
         (ADC2_VDDP_UP_INT_EN     == 1u)     || \
         (ADC2_VDDP_LO_INT_EN     == 1u)     || \
         (PMU_VDDEXT_UV_INT_EN    == 1u)     || \
         (PMU_VDDEXT_OT_INT_EN    == 1u)     || \
         (PMU_VDDC_OV_INT_EN      == 1u)     || \
         (PMU_VDDC_OL_INT_EN      == 1u)     || \
         (PMU_VDDP_OV_INT_EN      == 1u)     || \
         (PMU_VDDP_OL_INT_EN      == 1u)     || \
         (PMU_PMU_OT_INT_EN       == 1u)     || \
         (ADC2_VDDEXT_UP_INT_EN   == 1u)     || \
         (ADC2_VDDEXT_LO_INT_EN   == 1u)     || \
         (ADC1_PP_CH0_UP_INT_EN   == 1u)     || \
         (ADC1_PP_CH0_LO_INT_EN   == 1u)     || \
         (ADC1_PP_CH1_UP_INT_EN   == 1u)     || \
         (ADC1_PP_CH1_LO_INT_EN   == 1u))

void NMI_Handler(void)
{
#if (SCU_NMI_WDT_INT_EN == 1u)
  if (u1_Field_Rd32(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIWDT_Pos, SCU_NMICON_NMIWDT_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&SCU->NMISR.reg, (uint8)SCU_NMISR_FNMIWDT_Pos, SCU_NMISR_FNMIWDT_Msk) == (uint8)1)
    {
      if (u1_Field_Rd32(&SCU->WDTCON.reg, (uint8)SCU_WDTCON_WDTEN_Pos, SCU_WDTCON_WDTEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&SCU->WDTCON.reg, (uint8)SCU_WDTCON_WDTPR_Pos, SCU_WDTCON_WDTPR_Msk) == (uint8)1)
        {
          SCU_NMI_WDT_CALLBACK();
          NMI_WDT_Int_Clr();
        }
      }
    }
  }
#endif /*((SCU_NMICON & (1u << 0u)) != 0u) */

#if (SCU_NMI_PLL_INT_EN == 1u)
  if (u1_Field_Rd32(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIPLL_Pos, SCU_NMICON_NMIPLL_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&SCU->NMISR.reg, (uint8)SCU_NMISR_FNMIPLL_Pos, SCU_NMISR_FNMIPLL_Msk) == (uint8)1)
    {
      if (u1_Field_Rd32(&SCU->PLL_CON.reg, (uint8)SCU_PLL_CON_LOCK_Pos, SCU_PLL_CON_LOCK_Msk) == (uint8)1)
      {
        SCU_NMI_PLL_CALLBACK();
        NMI_PLL_Int_Clr();
      }
    }
  }
#endif /*((SCU_NMICON & (1u << 1u)) != 0u) */

#if  ((ADC2_SYS_TEMP_UP_INT_EN == 1u)  || \
      (ADC2_SYS_TEMP_LO_INT_EN == 1u))
  if (u1_Field_Rd32(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIOT_Pos, SCU_NMICON_NMIOT_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&SCU->NMISR.reg, (uint8)SCU_NMISR_FNMIOT_Pos, SCU_NMISR_FNMIOT_Msk) == (uint8)1)
    {
#if (ADC2_SYS_TEMP_LO_INT_EN == 1u)
      if (u1_Field_Rd32(&SCUPM->SYS_IRQ_CTRL.reg, (uint8)SCUPM_SYS_IRQ_CTRL_SYS_OTWARN_IE_Pos, SCUPM_SYS_IRQ_CTRL_SYS_OTWARN_IE_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&SCUPM->SYS_IS.reg, (uint8)SCUPM_SYS_IS_SYS_OTWARN_IS_Pos, SCUPM_SYS_IS_SYS_OTWARN_IS_Msk) == (uint8)1)
        {
          ADC2_SYS_TEMP_LO_CALLBACK();
          ADC2_TEMP_WARN_Int_Clr();
        }
      }
#endif /*((SCUPM_SYS_IRQ_CTRL & (1u << 8u)) != 0u) */

#if (ADC2_SYS_TEMP_UP_INT_EN == 1u)
      if (u1_Field_Rd32(&SCUPM->SYS_IRQ_CTRL.reg, (uint8)SCUPM_SYS_IRQ_CTRL_SYS_OT_IE_Pos, SCUPM_SYS_IRQ_CTRL_SYS_OT_IE_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&SCUPM->SYS_IS.reg, (uint8)SCUPM_SYS_IS_SYS_OT_IS_Pos, SCUPM_SYS_IS_SYS_OT_IS_Msk) == (uint8)1)
        {
          ADC2_SYS_TEMP_UP_CALLBACK();
          ADC2_TEMP_OT_Int_Clr();
        }
      }
#endif /*((SCUPM_SYS_IRQ_CTRL & (1u << 9u)) != 0u) */
    }
  }
#endif /*((SCU_NMICON & (1u << 3u)) != 0u) */


#if (SCU_NMI_OWD_INT_EN == 1u)
  if (u1_Field_Rd32(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIOWD_Pos, SCU_NMICON_NMIOWD_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&SCU->NMISR.reg, (uint8)SCU_NMISR_FNMIOWD_Pos, SCU_NMISR_FNMIOWD_Msk) == (uint8)1)
    {
      SCU_NMI_OWD_CALLBACK();
      NMI_OWD_Int_Clr();
    }
  }
#endif /*((SCU_NMICON & (1u << 4u)) != 0u) */

#if (SCU_NMI_MAP_INT_EN == 1u)
  if (u1_Field_Rd32(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIMAP_Pos, SCU_NMICON_NMIMAP_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&SCU->NMISR.reg, (uint8)SCU_NMISR_FNMIMAP_Pos, SCU_NMISR_FNMIMAP_Msk) == (uint8)1)
    {
      SCU_NMI_MAP_CALLBACK();
      NMI_MAP_Int_Clr();
    }
  }
#endif /*((SCU_NMICON & (1u << 5u)) != 0u) */

#if ((SCU_ECC_RAM_DB_INT_EN == 1u) || \
     (SCU_ECC_NVM_DB_INT_EN == 1u))
  if (u1_Field_Rd32(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIECC_Pos, SCU_NMICON_NMIECC_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&SCU->NMISR.reg, (uint8)SCU_NMISR_FNMIECC_Pos, SCU_NMISR_FNMIECC_Msk) == (uint8)1)
    {
#if (SCU_ECC_RAM_DB_INT_EN == 1u)
      if (u1_Field_Rd32(&SCU->EDCCON.reg, (uint8)SCU_EDCCON_RIE_Pos, SCU_EDCCON_RIE_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&SCU->EDCSTAT.reg, (uint8)SCU_EDCSTAT_RDBE_Pos, SCU_EDCSTAT_RDBE_Msk) == (uint8)1)
        {
          SCU_ECC_RAM_DB_CALLBACK();
          ECC_RAM_DoubleBit_Int_Clr();
        }
      }
#endif /*((SCU_EDCCON & (1u << 0u)) != 0u) */

#if (SCU_ECC_NVM_DB_INT_EN == 1u)
      if (u1_Field_Rd32(&SCU->EDCCON.reg, (uint8)SCU_EDCCON_NVMIE_Pos, SCU_EDCCON_NVMIE_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&SCU->EDCSTAT.reg, (uint8)SCU_EDCSTAT_NVMDBE_Pos, SCU_EDCSTAT_NVMDBE_Msk) == (uint8)1)
        {
          SCU_ECC_NVM_DB_CALLBACK();
          ECC_NVM_DoubleBit_Int_Clr();
        }
      }
#endif /*((SCU_EDCCON & (1u << 2u)) != 0u) */
    }
  }
#endif /*((SCU_NMICON & (1u << 6u)) != 0u) */

#if     ((ADC2_VS_UP_INT_EN == 1u)      || \
         (ADC2_VS_LO_INT_EN == 1u)      || \
         (ADC2_VDDC_UP_INT_EN == 1u)    || \
         (ADC2_VDDC_LO_INT_EN == 1u)    || \
         (ADC2_VDDEXT_UP_INT_EN == 1u)  || \
         (ADC2_VDDEXT_LO_INT_EN == 1u)  || \
         (ADC2_VDDP_UP_INT_EN == 1u)    || \
         (ADC2_VDDP_LO_INT_EN == 1u)    || \
         (PMU_VDDEXT_UV_INT_EN == 1u)   || \
         (PMU_VDDEXT_OT_INT_EN == 1u)   || \
         (PMU_VDDC_OV_INT_EN == 1u)     || \
         (PMU_VDDC_OL_INT_EN == 1u)     || \
         (PMU_VDDP_OV_INT_EN == 1u)     || \
         (PMU_VDDP_OL_INT_EN == 1u)     || \
         (PMU_PMU_OT_INT_EN == 1u)      || \
         (ADC1_PP_CH0_UP_INT_EN == 1u)  || \
         (ADC1_PP_CH0_LO_INT_EN == 1u)  || \
         (ADC1_PP_CH1_UP_INT_EN == 1u)  || \
         (ADC1_PP_CH1_LO_INT_EN == 1u))

  if (u1_Field_Rd32(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMISUP_Pos, SCU_NMICON_NMISUP_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&SCU->NMISR.reg, (uint8)SCU_NMISR_FNMISUP_Pos, SCU_NMISR_FNMISUP_Msk) == (uint8)1)
    {
#if (ADC1_PP_CH0_UP_INT_EN == 1u)
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH0_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH0_UP_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH0_UP_IS_Pos, ADC1_IRQS_2_PP_CH0_UP_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH0_UP_CALLBACK();
          ADC1_PP_Ch0_UP_Int_Clr();
        }
      }
#endif /*((ADC1_IRQEN_2 & (1u << 16u)) != 0u) */

#if (ADC1_PP_CH0_LO_INT_EN == 1u)
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH0_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH0_LO_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH0_LO_IS_Pos, ADC1_IRQS_2_PP_CH0_LO_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH0_LO_CALLBACK();
          ADC1_PP_Ch0_LO_Int_Clr();
        }
      }
#endif /*((ADC1_IRQEN_2 & (1u << 0u)) != 0u) */

#if (ADC1_PP_CH1_UP_INT_EN == 1u)
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_VS_UP_IEN_Pos, ADC1_IRQEN_2_VS_UP_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_VS_UP_IS_Pos, ADC1_IRQS_2_VS_UP_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH1_UP_CALLBACK();
          ADC1_PP_Ch1_UP_Int_Clr();
        }
      }
#endif /*((ADC1_IRQEN_2 & (1u << 17u)) != 0u) */

#if (ADC1_PP_CH1_LO_INT_EN == 1u)
      if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_VS_LO_IEN_Pos, ADC1_IRQEN_2_VS_LO_IEN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_VS_LO_IS_Pos, ADC1_IRQS_2_VS_LO_IS_Msk) == (uint8)1)
        {
          ADC1_PP_CH1_LO_CALLBACK();
          ADC1_PP_Ch1_LO_Int_Clr();
        }
      }
#endif /*((ADC1_IRQEN_2 & (1u << 1u)) != 0u) */

#if (ADC2_VDDEXT_LO_INT_EN == 1u)
      if (u1_Field_Rd32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CTRL_VDDEXT_UV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDDEXT_UV_IE_Msk) == (uint8)1)
      {
        /* VDDEXT Undervoltage measured by ADC2-Ch3 */
        if (u1_Field_Rd32(&SCUPM->SYS_SUPPLY_IRQ_STS.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_STS_VDDEXT_UV_IS_Pos, SCUPM_SYS_SUPPLY_IRQ_STS_VDDEXT_UV_IS_Msk) == (uint8)1)
        {
          ADC2_VDDEXT_LO_CALLBACK();
          ADC2_VDDEXT_UV_Int_Clr();
        }
      }
#endif /*(ADC2_VDDEXT_LO_INT_EN == 1u) */

#if (ADC2_VDDEXT_UP_INT_EN == 1u)
      if (u1_Field_Rd32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CTRL_VDDEXT_OV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDDEXT_OV_IE_Msk) == (uint8)1)
      {
        /* VDDEXT Undervoltage measured by ADC2-Ch3 */
        if (u1_Field_Rd32(&SCUPM->SYS_SUPPLY_IRQ_STS.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_STS_VDDEXT_OV_IS_Pos, SCUPM_SYS_SUPPLY_IRQ_STS_VDDEXT_OV_IS_Msk) == (uint8)1)
        {
          ADC2_VDDEXT_UP_CALLBACK();
          ADC2_VDDEXT_OV_Int_Clr();
        }
      }
#endif /*(ADC2_VDDEXT_UP_INT_EN == 1u) */

#if (ADC2_VDDC_UP_INT_EN == 1u)
      if (u1_Field_Rd32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD1V5_OV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD1V5_OV_IE_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&SCUPM->SYS_SUPPLY_IRQ_STS.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_STS_VDD1V5_OV_IS_Pos, SCUPM_SYS_SUPPLY_IRQ_STS_VDD1V5_OV_IS_Msk) == (uint8)1)
        {
          ADC2_VDDC_UP_CALLBACK();
          ADC2_VDDC_OV_Int_Clr();
        }
      }
#endif /*((SCU_SYS_SUPPLY_IRQ_CTRL & (1u << 14u)) != 0u) */

#if (ADC2_VDDC_LO_INT_EN == 1u)
      if (u1_Field_Rd32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD1V5_UV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD1V5_UV_IE_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&SCUPM->SYS_SUPPLY_IRQ_STS.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_STS_VDD1V5_UV_IS_Pos, SCUPM_SYS_SUPPLY_IRQ_STS_VDD1V5_UV_IS_Msk) == (uint8)1)
        {
          ADC2_VDDC_LO_CALLBACK();
          ADC2_VDDC_UV_Int_Clr();
        }
      }
#endif /*((SCU_SYS_SUPPLY_IRQ_CTRL & (1u << 6u)) != 0u) */

#if (ADC2_VDDP_UP_INT_EN == 1u)
      if (u1_Field_Rd32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD5V_OV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD5V_OV_IE_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&SCUPM->SYS_SUPPLY_IRQ_STS.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_STS_VDD5V_OV_IS_Pos, SCUPM_SYS_SUPPLY_IRQ_STS_VDD5V_OV_IS_Msk) == (uint8)1)
        {
          ADC2_VDDP_UP_CALLBACK();
          ADC2_VDDP_OV_Int_Clr();
        }
      }
#endif /*((SCU_SYS_SUPPLY_IRQ_CTRL & (1u << 12u)) != 0u) */

#if (ADC2_VDDP_LO_INT_EN == 1u)
      if (u1_Field_Rd32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD5V_UV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD5V_UV_IE_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&SCUPM->SYS_SUPPLY_IRQ_STS.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_STS_VDD5V_UV_IS_Pos, SCUPM_SYS_SUPPLY_IRQ_STS_VDD5V_UV_IS_Msk) == (uint8)1)
        {
          ADC2_VDDP_LO_CALLBACK();
          ADC2_VDDP_UV_Int_Clr();
        }
      }
#endif /*((SCU_SYS_SUPPLY_IRQ_CTRL & (1u << 4u)) != 0u) */

#if (ADC2_VS_UP_INT_EN == 1u)
      if (u1_Field_Rd32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CTRL_VS_OV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VS_OV_IE_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&SCUPM->SYS_SUPPLY_IRQ_STS.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_STS_VS_OV_IS_Pos, SCUPM_SYS_SUPPLY_IRQ_STS_VS_OV_IS_Msk) == (uint8)1)
        {
          ADC2_VS_UP_CALLBACK();
          ADC2_VS_OV_Int_Clr();
        }
      }
#endif /*((SCU_SYS_SUPPLY_IRQ_CTRL & (1u << 8u)) != 0u) */

#if (ADC2_VS_LO_INT_EN == 1u)
      if (u1_Field_Rd32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CTRL_VS_UV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VS_UV_IE_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&SCUPM->SYS_SUPPLY_IRQ_STS.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_STS_VS_UV_IS_Pos, SCUPM_SYS_SUPPLY_IRQ_STS_VS_UV_IS_Msk) == (uint8)1)
        {
          ADC2_VS_LO_CALLBACK();
          ADC2_VS_UV_Int_Clr();
        }
      }
#endif /*((SCU_SYS_SUPPLY_IRQ_CTRL & (1u << 0u)) != 0u) */

#if ((PMU_VDDC_OV_INT_EN == 1u) || \
     (PMU_VDDC_OL_INT_EN == 1u))
      if (u1_Field_Rd32(&PMU->SUPPLY_STS.reg, (uint8)PMU_SUPPLY_STS_PMU_1V5_FAIL_EN_Pos, PMU_SUPPLY_STS_PMU_1V5_FAIL_EN_Msk) == (uint8)1)
      {
    #if (PMU_VDDC_OV_INT_EN == 1u)
        if (u1_Field_Rd32(&PMU->SUPPLY_STS.reg, (uint8)PMU_SUPPLY_STS_PMU_1V5_OVERVOLT_Pos, PMU_SUPPLY_STS_PMU_1V5_OVERVOLT_Msk) == (uint8)1)
        {
          PMU_VDDC_OV_CALLBACK();
        }
    #endif
    #if (PMU_VDDC_OL_INT_EN == 1u)
        if (u1_Field_Rd32(&PMU->SUPPLY_STS.reg, (uint8)PMU_SUPPLY_STS_PMU_1V5_OVERLOAD_Pos, PMU_SUPPLY_STS_PMU_1V5_OVERLOAD_Msk) == (uint8)1)
        {
          PMU_VDDC_OL_CALLBACK();
        }
    #endif
      }
#endif /*((PMU_SUPPLY_STS & (1u << 2u)) != 0u) */

#if ((PMU_VDDP_OV_INT_EN == 1u) || \
     (PMU_VDDP_OL_INT_EN == 1u))
      if (u1_Field_Rd32(&PMU->SUPPLY_STS.reg, (uint8)PMU_SUPPLY_STS_PMU_5V_FAIL_EN_Pos, PMU_SUPPLY_STS_PMU_5V_FAIL_EN_Msk) == (uint8)1)
      {
    #if (PMU_VDDP_OV_INT_EN == 1u)
        if (u1_Field_Rd32(&PMU->SUPPLY_STS.reg, (uint8)PMU_SUPPLY_STS_PMU_5V_OVERVOLT_Pos, PMU_SUPPLY_STS_PMU_5V_OVERVOLT_Msk) == (uint8)1)
        {
          PMU_VDDP_OV_CALLBACK();
        }
    #endif
    #if (PMU_VDDP_OL_INT_EN == 1u)
        if (u1_Field_Rd32(&PMU->SUPPLY_STS.reg, (uint8)PMU_SUPPLY_STS_PMU_5V_OVERLOAD_Pos, PMU_SUPPLY_STS_PMU_5V_OVERLOAD_Msk) == (uint8)1)
        {
          PMU_VDDP_OL_CALLBACK();
        }
    #endif
      }
#endif /*((PMU_SUPPLY_STS & (1u << 6u)) != 0u) */

#if (PMU_PMU_OT_INT_EN == 1u)
      if (u1_Field_Rd32(&PMU->OT_CTRL.reg, (uint8)PMU_OT_CTRL_PMU_OT_INT_EN_Pos, PMU_OT_CTRL_PMU_OT_INT_EN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&PMU->SUPPLY_STS.reg, (uint8)PMU_SUPPLY_STS_PMU_OVERTEMP_Pos, PMU_SUPPLY_STS_PMU_OVERTEMP_Msk) == (uint8)1)
        {
          PMU_PMU_OT_CALLBACK();
        }
      }
#endif /*((PMU_SUPPLY_STS & (1u << 3u)) != 0u) */

#if  ((PMU_VDDEXT_UV_INT_EN == 1u)   || \
      (PMU_VDDEXT_OT_INT_EN == 1u))
      if (u1_Field_Rd32(&PMU->VDDEXT_CTRL.reg, (uint8)PMU_VDDEXT_CTRL_VDDEXT_FAIL_EN_Pos, PMU_VDDEXT_CTRL_VDDEXT_FAIL_EN_Msk) == (uint8)1)
      {
      #if (PMU_VDDEXT_OT_INT_EN == 1u)
        if (u1_Field_Rd32(&PMU->VDDEXT_CTRL.reg, (uint8)PMU_VDDEXT_CTRL_VDDEXT_OT_IS_Pos, PMU_VDDEXT_CTRL_VDDEXT_OT_IS_Msk) == (uint8)1)
        {
          PMU_VDDEXT_OT_CALLBACK();
          PMU_VDDEXT_OT_Int_Clr();
        }
      #endif
      #if (PMU_VDDEXT_UV_INT_EN == 1u)
        if (u1_Field_Rd32(&PMU->VDDEXT_CTRL.reg, (uint8)PMU_VDDEXT_CTRL_VDDEXT_UV_IS_Pos, PMU_VDDEXT_CTRL_VDDEXT_UV_IS_Msk) == (uint8)1)
        {
          PMU_VDDEXT_UV_CALLBACK();
          PMU_VDDEXT_UV_Int_Clr();
        }
      #endif
      }
#endif /*((PMU_VDDEXT_CTRL & (1u << 2u)) != 0u) */
    }
  }
#endif /*((SCU_NMICON & (1u << 7u)) != 0u) */

#if (SCU_NMI_STOF_INT_EN == 1u)
  if (u1_Field_Rd32(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMISTOF_Pos, SCU_NMICON_NMISTOF_Msk) == (uint8)1)
  {
    if (u1_Field_Rd32(&SCU->NMISR.reg, (uint8)SCU_NMISR_FNMISTOF_Pos, SCU_NMISR_FNMISTOF_Msk) == (uint8)1)
    {
      if (u1_Field_Rd32(&SCU->STACK_OVF_CTRL.reg, (uint8)SCU_STACK_OVF_CTRL_STOF_EN_Pos, SCU_STACK_OVF_CTRL_STOF_EN_Msk) == (uint8)1)
      {
        if (u1_Field_Rd32(&SCU->STACK_OVF_STS.reg, (uint8)SCU_STACK_OVF_STS_STOF_STS_Pos, SCU_STACK_OVF_STS_STOF_STS_Msk) == (uint8)1)
        {
          SCU_NMI_STOF_CALLBACK();
          NMI_STOF_Int_Clr();
        }
      }
    }
  }
#endif /*((SCU_NMICON & (1u << 8u)) != 0u) */
}
#endif

/*******************************************************************************
**                      HardFault ISR                                         **
*******************************************************************************/

#if 0
void HardFault_Handler(void)
{
#if (CPU_HARDFAULT_EN == 1u)
    CPU_HARDFAULT_CALLBACK();
#endif /*(CPU_HARDFAULT_EN == 1u)*/
}

/*******************************************************************************
**                      SysTick ISR                                           **
*******************************************************************************/
void SysTick_Handler(void)
{
#if (CPU_SYSTICK_EN == 1u)
    CPU_SYSTICK_CALLBACK();
#endif /*(CPU_SYSTICK_EN == 1u)*/

  WDT1_Window_Count();
}
#endif

