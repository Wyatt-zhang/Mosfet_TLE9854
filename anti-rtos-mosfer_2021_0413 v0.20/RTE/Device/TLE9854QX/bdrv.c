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
#include "bdrv.h"
#include "bdrv_defines.h"
#include "scu.h"
#include "wdt1.h"

/*******************************************************************************
**                         Global Function Definitions                        **
*******************************************************************************/
void BDRV_Init(void)
{
  /* Set BDRV clock */
  SCU->BRDRV_CLK.reg = (uint32) SCU_BRDRV_CLK;
  /* apply settings by setting APCLK_SET */
  /* APCLK_SET is cleared by HW once the clock settings are overtaken */
  SCU_OpenPASSWD();
  Field_Mod32(&SCU->APCLK_CTRL.reg, (uint8)SCU_APCLK_CTRL_APCLK_SET_Pos, SCU_APCLK_CTRL_APCLK_SET_Msk, 1u);
  SCU_ClosePASSWD();
	
  /* Set charge pump clock */
  BDRV->CP_CLK_CTRL.reg = (uint32) BDRV_CP_CLK_CTRL;

  /* Set charge pump control, clear status bits
   * Keep the bootrom value for Charge Pump Output Voltage Trimming
   */
  SCU->PASSWD.reg = PASSWD_Open;
  BDRV->CP_CTRL.reg = (BDRV->CP_CTRL.reg & BDRV_CP_CTRL_VTHVCP_TRIM_Msk) | (uint32) BDRV_CP_CTRL;
  SCU->PASSWD.reg = PASSWD_Close;

  /* Set trimming register */
  SCU->PASSWD.reg = PASSWD_Open;
  BDRV->TRIM_DRVx.reg = (uint32) BDRV_TRIM_DRVx;
  SCU->PASSWD.reg = PASSWD_Close;

  /* Set bridge driver control 3 */
  BDRV->CTRL3.reg = (uint32) BDRV_CTRL3;
  BDRV->CTRL1.reg = 0u;
  BDRV->CTRL2.reg = (uint32) BDRV_CTRL2;

  BDRV->SEQMAP.reg = (uint32) BDRV_SEQMAP;
  BDRV->PWMSRCSEL.reg = (uint32) BDRV_PWMSRCSEL;

  BDRV->SEQAFHB1IC.reg = (uint32) BDRV_SEQAFHB1IC;
  BDRV->SEQAFHB1CD.reg = (uint32) BDRV_SEQAFHB1CD;
  BDRV->OFFSEQHB1TC.reg = (uint32) BDRV_OFFSEQHB1TC;
  BDRV->ONSEQHB1TC.reg = (uint32) BDRV_ONSEQHB1TC;
  BDRV->OFFSEQHB1IC.reg = (uint32) BDRV_OFFSEQHB1IC;
  BDRV->ONSEQHB1IC.reg = (uint32) BDRV_ONSEQHB1IC;

#ifdef UC_FEATURE_HB2
  BDRV->SEQAFHB2IC.reg = (uint32) BDRV_SEQAFHB2IC;
  BDRV->SEQAFHB2CD.reg = (uint32) BDRV_SEQAFHB2CD;
  BDRV->OFFSEQHB2TC.reg = (uint32) BDRV_OFFSEQHB2TC;
  BDRV->ONSEQHB2TC.reg = (uint32) BDRV_ONSEQHB2TC;
  BDRV->OFFSEQHB2IC.reg = (uint32) BDRV_OFFSEQHB2IC;
  BDRV->ONSEQHB2IC.reg = (uint32) BDRV_ONSEQHB2IC;
#endif

  BDRV->IGATECLMPOFFC.reg = (uint32) BDRV_IGATECLMPOFFC;
  BDRV->IGATECLMPONC.reg = (uint32) BDRV_IGATECLMPONC;

  /* Interrupt configuration ****************************************************/
  BDRV->IRQEN.reg = (uint32) BDRV_IRQEN;
  BDRV->CP_IRQEN.reg = (uint32) BDRV_CP_IRQEN;
}

#ifdef UC_FEATURE_HB2
void BDRV_Set_Bridge(TBdrv_Ch_LS_Cfg LS1_Cfg, TBdrv_Ch_Cfg HS1_Cfg, TBdrv_Ch_LS_Cfg LS2_Cfg, TBdrv_Ch_Cfg HS2_Cfg)
{
  Field_Wrt32(&BDRV->CTRL1.reg, (uint8)BDRV_CTRL1_LS1_EN_Pos, MASK_WORD, ((uint32)HS2_Cfg << 24u) | ((uint32)HS1_Cfg << 16u) | ((uint32)LS2_Cfg << 8u) | ((uint32)LS1_Cfg));
}
#else
void BDRV_Set_Bridge(TBdrv_Ch_LS_Cfg LS1_Cfg, TBdrv_Ch_Cfg HS1_Cfg)
{
  Field_Wrt32(&BDRV->CTRL1.reg, (uint8)BDRV_CTRL1_LS1_EN_Pos, MASK_WORD, ((uint32)HS1_Cfg << 16u) | ((uint32)LS1_Cfg));
}  
#endif

void BDRV_Clr_Sts(uint32 Sts_Bit)
{
  Field_Wrt32all(&BDRV->IRQCLR.reg, (uint32)Sts_Bit);
  /* add an extra clear access in order to ensure the clear of           */
  /* the status flags is executed before the status flags are read again */
  Field_Wrt32all(&BDRV->IRQCLR.reg, (uint32)0);
}

void BDRV_Set_Channel(TBdrv_Ch BDRV_Ch, TBdrv_Ch_Cfg Ch_Cfg)
{
  Field_Mod32(&BDRV->CTRL1.reg, (uint8)((uint32)BDRV_Ch << 3u), ((uint32)0x0F << ((uint32)BDRV_Ch << 3u)), ((uint32)Ch_Cfg & 15u));
}

void BDRV_Set_Int_Channel(TBdrv_Ch BDRV_Ch, TBdrv_Ch_Int Ch_Int)
{

  /* set DS_Int */
  Field_Mod32(&BDRV->IRQEN.reg, (uint8)(4u + ((uint32)BDRV_Ch << 3u)), ((uint32)0x1 << (4u + ((uint32)BDRV_Ch << 3u))), ((uint32)Ch_Int & 1u));

  /* set OC_Int */
  Field_Mod32(&BDRV->IRQEN.reg, (uint8)(6u + ((uint32)BDRV_Ch << 3u)), ((uint32)0x1 << (6u + ((uint32)BDRV_Ch << 3u))), ((uint32)Ch_Int >> (uint8)1) & 1u);

  /* enable BDRV interrupt node */
  if (u32_Field_Rd32(&BDRV->IRQEN.reg, (uint8)BDRV_IRQEN_HB1_ASEQ_IEN_Pos, (uint32)BDRV_IRQ_EN_BITS) != (uint32)0u)
  {
    Field_Mod32(&CPU->NVIC_ISER.reg, (uint8)CPU_NVIC_ISER_Int_BDRV_Pos, CPU_NVIC_ISER_Int_BDRV_Msk, 1u);
  }
}

void BDRV_Set_DSM_Threshold(TBdrv_DSM_Threshold BDRV_Threshold)
{
  Field_Mod32(&BDRV->CTRL3.reg, (uint8)BDRV_CTRL3_DSMONVTH_Pos, BDRV_CTRL3_DSMONVTH_Msk, (uint32)BDRV_Threshold);
}

void BDRV_Set_Channel_Comp(uint8 gain_hs, uint8 gain_ls)
{
  SCU_OpenPASSWD();
  Field_Wrt32(&BDRV->DCTRIM_DRVx.reg, (uint8)BDRV_DCTRIM_DRVx_COMPENS_HS_Pos, BDRV_COMP_BITS, (uint32)gain_hs | ((uint32)gain_ls << (uint8)8));
  SCU_ClosePASSWD();
}

#ifdef UC_FEATURE_HB2
bool BDRV_Diag_OpenLoad(void)
{
  /* HSx_OC/LSx_OC and HSx_DS/LSx/DS bits */
  uint8 iBDRV_Int_En;
  bool bOpenLoad;
  uint32 lCTRL3;

  bOpenLoad = false;

  /* save bridge driver interrupt enable */
  iBDRV_Int_En = u1_Field_Rd32(&CPU->NVIC_ISER.reg, (uint8)CPU_NVIC_ISER_Int_BDRV_Pos, CPU_NVIC_ISER_Int_BDRV_Msk);

  /* disable bridge driver interrupt */
  Field_Wrt32(&CPU->NVIC_ICER.reg, (uint8)CPU_NVIC_ICER_Int_BDRV_Pos, CPU_NVIC_ICER_Int_BDRV_Msk, 1u);

  /* save CTRL3 register */
  lCTRL3 = u16_Field_Rd32(&BDRV->CTRL3.reg, (uint8)BDRV_CTRL3_DSMONVTH_Pos, MASK_WORD);

  /* set DSMONVTH = 7 (1.75V) */
  BDRV_Set_DSM_Threshold(Threshold_1_75_V);

  /* check Phase 1 and 2 */
  BDRV_Set_Channel(LS1, Ch_En);
  BDRV_Set_Channel(LS2, Ch_En);
  BDRV_Set_Channel(HS1, Ch_En);
  BDRV_Set_Channel(HS2, Ch_En);

  /* enable HS1 DS-Current Source */
  BDRV_Set_Channel(HS1, Ch_DCS);

  /* Delay, give the DS-Current source some time to settle *
   * delay time depents on the attached motor              */
  Delay_us(800u);

  /* clear status flags */
  Field_Wrt32(&BDRV->IRQCLR.reg, (uint8)BDRV_IRQCLR_HB1_ASEQ_ISC_Pos, MASK_WORD, BDRV_IRQ_CLR_BITS);
  /* add an extra clear access in order to ensure the clear of           *
   * the status flags is executed before the status flags are read again */
  Field_Wrt32(&BDRV->IRQCLR.reg, (uint8)BDRV_IRQCLR_HB1_ASEQ_ISC_Pos, MASK_WORD, 0u);

  /* check status flags */
  if (u32_Field_Rd32(&BDRV->IRQS.reg, (uint8)BDRV_IRQS_HB1_ASEQ_IS_Pos, BDRV_IRQ_CLR_BITS) != (uint32)0u)
  {
    bOpenLoad = true;
  }

  /* switch off all drivers */
  Field_Clr32(&BDRV->CTRL1.reg, (uint32)MASK_WORD);

  /* restore CTRL3 register */
  Field_Wrt32(&BDRV->CTRL3.reg, (uint8)BDRV_CTRL3_DSMONVTH_Pos, MASK_WORD, lCTRL3);

  /* restore interrupt */
  if (iBDRV_Int_En == (uint8)1)
  {
    Field_Mod32(&CPU->NVIC_ISER.reg, (uint8)CPU_NVIC_ISER_Int_BDRV_Pos, CPU_NVIC_ISER_Int_BDRV_Msk, 1u);
  }
  return (bOpenLoad);
}
#endif

#ifdef UC_FEATURE_HB2
TBDRV_Off_Diag BDRV_Off_Diagnosis(void)
{
  TBDRV_Off_Diag res;
  uint8 iBDRV_Int_En;
  uint32 lCTRL3;

  res.GlobFailSts = false;
  res.Phase1 = Ch_Ok;
  res.Phase2 = Ch_Ok;
  
  /* save bridge driver interrupt enable */
  iBDRV_Int_En = u1_Field_Rd32(&CPU->NVIC_ISER.reg, (uint8)CPU_NVIC_ISER_Int_BDRV_Pos, CPU_NVIC_ISER_Int_BDRV_Msk);
  /* disable bridge driver interrupt */
  Field_Wrt32(&CPU->NVIC_ICER.reg, (uint8)CPU_NVIC_ICER_Int_BDRV_Pos, CPU_NVIC_ICER_Int_BDRV_Msk, 1u);

  /* save CTRL3 register */
  lCTRL3 = u16_Field_Rd32(&BDRV->CTRL3.reg, (uint8)BDRV_CTRL3_DSMONVTH_Pos, MASK_WORD);

  BDRV_Set_Bridge(Ch_LS_En, Ch_En, Ch_LS_En, Ch_En);

  /* set DSMONVTH = 0 (0.25V) */
  BDRV_Set_DSM_Threshold(Threshold_0_125_V);

  /* enable diagnostic current source on HSx drivers */
  BDRV_Set_Channel(HS1, Ch_DCS);
  BDRV_Set_Channel(HS2, Ch_DCS);

  /* Delay, give the DS-Current source some time to settle *
  * delay time depends on the attached motor              */
  Delay_us(800u);

  /* clear status flags */
  Field_Wrt32(&BDRV->IRQCLR.reg, (uint8)BDRV_IRQCLR_HB1_ASEQ_ISC_Pos, MASK_WORD, BDRV_IRQ_CLR_BITS);

  /* check status flags */
  if ((BDRV->IRQS.reg & (uint32)BDRV_DS_STS_BITS) != 0u)
  {
    res.GlobFailSts = true;
    if (u1_Field_Rd32(&BDRV->IRQS.reg, (uint8)BDRV_IRQS_HS1_DS_STS_Pos, BDRV_IRQS_HS1_DS_STS_Msk) == 1u)
    {
      res.Phase1 = Ch_Short_to_VBat;
    }
    if (u1_Field_Rd32(&BDRV->IRQS.reg, (uint8)BDRV_IRQS_LS1_DS_STS_Pos, BDRV_IRQS_LS1_DS_STS_Msk) == 1u)
    {
      res.Phase1 = Ch_Short_to_Gnd;
    }
    if (u1_Field_Rd32(&BDRV->IRQS.reg, (uint8)BDRV_IRQS_HS2_DS_STS_Pos, BDRV_IRQS_HS2_DS_STS_Msk) == 1u)
    {
      res.Phase2 = Ch_Short_to_VBat;
    }
    if (u1_Field_Rd32(&BDRV->IRQS.reg, (uint8)BDRV_IRQS_LS2_DS_STS_Pos, BDRV_IRQS_LS2_DS_STS_Msk) == 1u)
    {
      res.Phase2 = Ch_Short_to_Gnd;
    }
  }

  /* switch off all drivers */
  Field_Clr32(&BDRV->CTRL1.reg, (uint32)MASK_WORD);

  /* restore CTRL3 register */
  Field_Wrt32(&BDRV->CTRL3.reg, (uint8)BDRV_CTRL3_DSMONVTH_Pos, MASK_WORD, lCTRL3);

  /* restore interrupt */
  if (iBDRV_Int_En == (uint8)1)
  {
    Field_Mod32(&CPU->NVIC_ISER.reg, (uint8)CPU_NVIC_ISER_Int_BDRV_Pos, CPU_NVIC_ISER_Int_BDRV_Msk, 1u);
  }

  return(res);
}
#endif
