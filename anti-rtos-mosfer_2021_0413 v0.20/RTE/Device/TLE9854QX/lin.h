/*
 ***********************************************************************************************************************
 *
 * Copyright (c) 2017, Infineon Technologies AG
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
/**
 * \file     lin.h
 *
 * \brief    LIN low level access library
 *
 * \version  V0.2.3
 * \date     02. Mar 2020
 *
 * \note This file violates [MISRA 2012 Rule 11.1, required], [MISRA 2012 Rule 11.4, advisory], [MISRA 2012 Rule 11.6, required], [MISRA 2012 Rule 2.5, advisory]
 */

/*******************************************************************************
**                             Author(s) Identity                             **
********************************************************************************
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** TS           T&S                                                           **
** JO           Julia Ott                                                     **
** BG           Blandine Guillot                                              **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V0.2.0: 2018-02-13, TS:   Initial version of revision history              **
** V0.2.1: 2019-01-28, TS:   __STATIC_INLINE changed to INLINE                **
**                           Doxygen Update                                   **
**                           Revision history moved from lin.c to lin.h       **
** V0.2.2: 2019-06-27, JO:   Added macro LIN_GET_MODE_DISABLED                **
** V0.2.3: 2020-03-02, BG:   Updated revision history format                  **
*******************************************************************************/

#ifndef LIN_H
#define LIN_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle985x.h"
#include "types.h"
#include "sfr_access.h"

/*******************************************************************************
**                         Global Macro Definitions                           **
*******************************************************************************/
/**\brief LIN MODE, SLEEP MODE */
#define LIN_MODE_SLEEP    (0u)
/**\brief LIN MODE, RCV ONLY MODE */
#define LIN_MODE_RCV_ONLY (1u)
/**\brief LIN MODE, NORMAL MODE */
#define LIN_MODE_NORMAL   (3u)

/**\brief LIN MODE READ, LIN MODULE DISABLED */
#define LIN_GET_MODE_DISABLED (0u)
/**\brief LIN MODE READ, SLEEP MODE */
#define LIN_GET_MODE_SLEEP    (1u)
/**\brief LIN MODE READ, RCV ONLY MODE */
#define LIN_GET_MODE_RCV_ONLY (5u)
/**\brief LIN MODE READ, NORMAL MODE */
#define LIN_GET_MODE_NORMAL   (7u)

/**\brief LIN SLOPE MODE, NORMAL SLOPE */
#define LIN_SLOPE_NORMAL  (0u)
/**\brief LIN SLOPE MODE, FAST SLOPE */
#define LIN_SLOPE_FAST    (1u)
/**\brief LIN SLOPE MODE, LOW SLOPE */
#define LIN_SLOPE_LOW     (2u)
/**\brief LIN SLOPE MODE, FLASH SLOPE */
#define LIN_SLOPE_FLASH   (3u)

/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/
/** \brief Initializes the LIN module.
 *
 * \ingroup lin_api
 */
void LIN_Init(void);

/*******************************************************************************
**                        Inline Function Declarations                        **
*******************************************************************************/
/** \brief Sets LIN Trx. Mode
 *
 * \param Mode LIN Mode Selection
 *
 * \brief <b>Example</b><br>
 * \brief This example sets LIN Transmitter Sleep Mode as Transceiver power mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     LIN_Set_Mode(0x00);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Set_Mode(uint8 Mode);

/** \brief Gets LIN Trx. Mode
 *
 * \return Lin Trx Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example reads LIN Transmitter Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint16 mode;
 *
 *    mode = LIN_Get_Mode();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE uint8 LIN_Get_Mode(void);

/** \brief Sets LIN Trx. Slope Mode
 *
 * \param SlopeMode Trx Slope Mode Selection
 *
 * \brief <b>Example</b><br>
 * \brief This example sets LIN Normal Mode as Transmitter Slope mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     LIN_Set_Slope(0x00);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Set_Slope(uint8 SlopeMode);

/** \brief Enables Baud Rate Detection.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Baud Rate Detection.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     LIN_Break_Detect_En();  
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Break_Detect_En(void);

/** \brief Disables Baud Rate Detection.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Baud Rate Detection.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     LIN_Break_Detect_Dis();  
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Break_Detect_Dis(void);

/** \brief Selects Baud Rate Detection.
 *
 * \param value BGSEL Value (2 bits)
 *
 * \brief <b>Example</b><br>
 * \brief This example selects the first range of the Baud Rate Detection.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     LIN_BaudRate_Range_Sel(0x00);  
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_BaudRate_Range_Sel(uint8 value);

/** \brief Clears LIN Receiver Overcurrent interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN Receiver Overcurrent interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_Over_Curr_Int_En();
 *   if (((uint8)LIN->IRQS.bit.OC_IS == (uint8)1) && ((uint8)SCUPM->SYS_IS.bit.LIN_FAIL_IS == (uint8)1))
 *   {
 *     LIN_OC_CALLBACK();
 *     LIN_Over_Curr_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Over_Curr_Int_Clr(void);

/** \brief Clears LIN Receiver Overtemperature interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN Receiver Overtemperature interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_Over_Temp_Int_En();
 *   if (((uint8)LIN->IRQS.bit.OT_IS == (uint8)1) && ((uint8)SCUPM->SYS_IS.bit.LIN_FAIL_IS == (uint8)1))
 *   {
 *     LIN_OT_CALLBACK();
 *     LIN_Over_Temp_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Over_Temp_Int_Clr(void);

/** \brief Clears LIN TXD time-out interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN TXD time-out interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_Time_Out_Int_En();
 *   if ((uint8)LIN->IRQS.bit.TXD_TMOUT_IS == (uint8)1)
 *   {
 *     LIN_TMOUT_CALLBACK();
 *     LIN_Time_Out_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Time_Out_Int_Clr(void);

/** \brief Clears LIN Transceiver Mode Error - Slope Mode Error interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN Transceiver Mode Error - Slope Mode Error interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_M_SM_ERR_Int_En();
 *   if ((uint8)LIN->IRQS.bit.M_SM_ERR_IS == (uint8)1)
 *   {
 *     LIN_M_SM_ERR_CALLBACK();
 *     LIN_Mode_Error_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Mode_Error_Int_Clr(void);

/** \brief Clears End of SYN Byte interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN End of SYN Byte interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    LIN_Sync_Int_En();
 *   if (LIN_End_Of_Sync_Sts() == (uint8)1)
 *   {
 *     LIN_EOF_CALLBACK();
 *     LIN_End_Of_Sync_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_End_Of_Sync_Int_Clr(void);

/** \brief Clears SYN Byte Error interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example threats the SYN Byte Error interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    LIN_Sync_Int_En();
 *   if (LIN_Err_In_Sync_Sts() == (uint8)1)
 *   {
 *     LIN_ERR_CALLBACK();
 *     LIN_Err_In_Sync_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Err_In_Sync_Int_Clr(void);

/** \brief Clears Break Field flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Break Field flag.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     LIN_Break_Int_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Break_Int_Clr(void);

/** \brief Enables LIN Transceiver Overcurrent interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN Receiver Overcurrent interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_Over_Curr_Int_En();
 *   if (((uint8)LIN->IRQS.bit.OC_IS == (uint8)1) && ((uint8)SCUPM->SYS_IS.bit.LIN_FAIL_IS == (uint8)1))
 *   {
 *     LIN_OC_CALLBACK();
 *     LIN_Over_Curr_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Over_Curr_Int_En(void);

/** \brief Disables LIN Transceiver Overcurrent interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN Receiver Overcurrent interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_Over_Curr_Int_En();
 *   if (((uint8)LIN->IRQS.bit.OC_IS == (uint8)1) && ((uint8)SCUPM->SYS_IS.bit.LIN_FAIL_IS == (uint8)1))
 *   {
 *     LIN_OC_CALLBACK();
 *     LIN_Over_Curr_Int_Clr();
 *   }
 *   LIN_Over_Curr_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Over_Curr_Int_Dis(void);

/** \brief Enables LIN Transceiver Overtemperature interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN Receiver Overtemperature interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_Over_Temp_Int_En();
 *   if (((uint8)LIN->IRQS.bit.OT_IS == (uint8)1) && ((uint8)SCUPM->SYS_IS.bit.LIN_FAIL_IS == (uint8)1))
 *   {
 *     LIN_OT_CALLBACK();
 *     LIN_Over_Temp_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Over_Temp_Int_En(void);

/** \brief Disables LIN Transceiver Overtemperature interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN Receiver Overtemperature interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_Over_Temp_Int_En();
 *   if (((uint8)LIN->IRQS.bit.OT_IS == (uint8)1) && ((uint8)SCUPM->SYS_IS.bit.LIN_FAIL_IS == (uint8)1))
 *   {
 *     LIN_OT_CALLBACK();
 *     LIN_Over_Temp_Int_Clr();
 *   }
 *   LIN_Over_Temp_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Over_Temp_Int_Dis(void);

/** \brief Enables LIN Transceiver TxD-Timeout interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN TXD time-out interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_Time_Out_Int_En();
 *   if ((uint8)LIN->IRQS.bit.TXD_TMOUT_IS == (uint8)1)
 *   {
 *     LIN_TMOUT_CALLBACK();
 *     LIN_Time_Out_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Time_Out_Int_En(void);

/** \brief Disables LIN Transceiver TxD-Timeout interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN TXD time-out interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_Time_Out_Int_En();
 *   if ((uint8)LIN->IRQS.bit.TXD_TMOUT_IS == (uint8)1)
 *   {
 *     LIN_TMOUT_CALLBACK();
 *     LIN_Time_Out_Int_Clr();
 *   }
 *   LIN_Time_Out_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Time_Out_Int_Dis(void);

/** \brief Enables LIN Transceiver Mode Error - Slope Mode Error interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN Transceiver Mode Error - Slope Mode Error interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_M_SM_ERR_Int_En();
 *   if ((uint8)LIN->IRQS.bit.M_SM_ERR_IS == (uint8)1)
 *   {
 *     LIN_M_SM_ERR_CALLBACK();
 *     LIN_Mode_Error_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_M_SM_ERR_Int_En(void);

/** \brief Disables LIN Transceiver Mode Error - Slope Mode Error interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN Transceiver Mode Error - Slope Mode Error interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_M_SM_ERR_Int_En();
 *   if ((uint8)LIN->IRQS.bit.M_SM_ERR_IS == (uint8)1)
 *   {
 *     LIN_M_SM_ERR_CALLBACK();
 *     LIN_Mode_Error_Int_Clr();
 *   }
 *   LIN_M_SM_ERR_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_M_SM_ERR_Int_Dis(void);

/** \brief Enables End of SYN Byte and SYN Byte Error interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN End of SYN Byte interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_Sync_Int_En();
 *   if (LIN_End_Of_Sync_Sts() == (uint8)1)
 *   {
 *     LIN_EOF_CALLBACK();
 *     LIN_End_Of_Sync_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Sync_Int_En(void);

/** \brief Disables End of SYN Byte and SYN Byte Error interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN End of SYN Byte interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_Sync_Int_En();
 *   if (LIN_End_Of_Sync_Sts() == (uint8)1)
 *   {
 *     LIN_EOF_CALLBACK();
 *     LIN_End_Of_Sync_Int_Clr();
 *   }
 *   LIN_Sync_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE void LIN_Sync_Int_Dis(void);

/** \brief Reads End of SYN Byte Interrupt Status.
 *
 * \return End of SYN Byte Interrupt Status
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the LIN End of SYN Byte interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   LIN_Sync_Int_En();
 *   if (LIN_End_Of_Sync_Sts() == (uint8)1)
 *   {
 *     LIN_EOF_CALLBACK();
 *     LIN_End_Of_Sync_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE uint8 LIN_End_Of_Sync_Sts(void);

/** \brief Reads SYN Byte Error Interrupt Status.
 *
 * \return SYN Byte Error Interrupt Status
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the SYN Byte Error interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    LIN_Sync_Int_En();
 *   if (LIN_Err_In_Sync_Sts() == (uint8)1)
 *   {
 *     LIN_ERR_CALLBACK();
 *     LIN_Err_In_Sync_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE uint8 LIN_Err_In_Sync_Sts(void);

/** \brief Reads Break Field Status.
 *
 * \return Break Field Status
 *
 * \brief <b>Example</b><br>
 * \brief This example reads Break Field Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint8 status;
 *
 *    status = LIN_Break_Sts();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup lin_api
 */
INLINE uint8 LIN_Break_Sts(void);

/*******************************************************************************
**                         Inline Function Definitions                        **
*******************************************************************************/
INLINE void LIN_Set_Mode(uint8 Mode)
{
  Field_Mod32(&LIN->CTRL.reg, (uint8)LIN_CTRL_MODE_Pos, LIN_CTRL_MODE_Msk, Mode);  
}

INLINE uint8 LIN_Get_Mode(void)
{
  return(u8_Field_Rd32(&LIN->CTRL.reg, (uint8)LIN_CTRL_MODE_FB_Pos, LIN_CTRL_MODE_FB_Msk));  
}

INLINE void LIN_Set_Slope(uint8 SlopeMode)
{
  LIN_Set_Mode(LIN_MODE_SLEEP);  
  Field_Mod32(&LIN->CTRL.reg, (uint8)LIN_CTRL_SM_Pos, LIN_CTRL_SM_Msk, SlopeMode);    
  LIN_Set_Mode(LIN_MODE_NORMAL);    
}

INLINE void LIN_Break_Detect_En()
{
  Field_Mod32(&SCU->LINST.reg, (uint8)SCU_LINST_BRDIS_Pos, SCU_LINST_BRDIS_Msk, 0u);
}

INLINE void LIN_Break_Detect_Dis()
{
  Field_Mod32(&SCU->LINST.reg, (uint8)SCU_LINST_BRDIS_Pos, SCU_LINST_BRDIS_Msk, 1u);
}

INLINE void LIN_BaudRate_Range_Sel(uint8 value)
{
  Field_Mod32(&SCU->LINST.reg, (uint8)SCU_LINST_BGSEL_Pos, SCU_LINST_BGSEL_Msk, value);
}

INLINE void LIN_Over_Curr_Int_Clr()
{
  Field_Wrt32(&LIN->IRQCLR.reg, (uint8)LIN_IRQCLR_OC_ISC_Pos, LIN_IRQCLR_OC_ISC_Msk, 1u);
}

INLINE void LIN_Over_Temp_Int_Clr()
{
  Field_Wrt32(&LIN->IRQCLR.reg, (uint8)LIN_IRQCLR_OT_ISC_Pos, LIN_IRQCLR_OT_ISC_Msk, 1u);
}

INLINE void LIN_Time_Out_Int_Clr()
{
  Field_Wrt32(&LIN->IRQCLR.reg, (uint8)LIN_IRQCLR_TXD_TMOUT_ISC_Pos, LIN_IRQCLR_TXD_TMOUT_ISC_Msk, 1u);
}

INLINE void LIN_Mode_Error_Int_Clr()
{
  Field_Wrt32(&LIN->IRQCLR.reg, (uint8)LIN_IRQCLR_M_SM_ERR_ISC_Pos, LIN_IRQCLR_M_SM_ERR_ISC_Msk, 1u);
}

INLINE void LIN_End_Of_Sync_Int_Clr()
{
  Field_Wrt32(&SCU->LINSCLR.reg, (uint8)SCU_LINSCLR_EOFSYNC_Pos, SCU_LINSCLR_EOFSYNC_Msk, 1u);
}

INLINE void LIN_Err_In_Sync_Int_Clr()
{
  Field_Wrt32(&SCU->LINSCLR.reg, (uint8)SCU_LINSCLR_ERRSYNC_Pos, SCU_LINSCLR_ERRSYNC_Msk, 1u);
}

INLINE void LIN_Break_Int_Clr()
{
  Field_Wrt32(&SCU->LINSCLR.reg, (uint8)SCU_LINSCLR_BRKC_Pos, SCU_LINSCLR_BRKC_Msk, 1u);
}

INLINE void LIN_Over_Curr_Int_En()
{
  Field_Mod32(&LIN->IRQEN.reg, (uint8)LIN_IRQEN_OC_IEN_Pos, LIN_IRQEN_OC_IEN_Msk, 1u);
}

INLINE void LIN_Over_Curr_Int_Dis()
{
  Field_Mod32(&LIN->IRQEN.reg, (uint8)LIN_IRQEN_OC_IEN_Pos, LIN_IRQEN_OC_IEN_Msk, 0u);
}

INLINE void LIN_Over_Temp_Int_En()
{
  Field_Mod32(&LIN->IRQEN.reg, (uint8)LIN_IRQEN_OT_IEN_Pos, LIN_IRQEN_OT_IEN_Msk, 1u);
}

INLINE void LIN_Over_Temp_Int_Dis()
{
  Field_Mod32(&LIN->IRQEN.reg, (uint8)LIN_IRQEN_OT_IEN_Pos, LIN_IRQEN_OT_IEN_Msk, 0u);
}

INLINE void LIN_Time_Out_Int_En()
{
  Field_Mod32(&LIN->IRQEN.reg, (uint8)LIN_IRQEN_TXD_TMOUT_IEN_Pos, LIN_IRQEN_TXD_TMOUT_IEN_Msk, 1u);
}

INLINE void LIN_Time_Out_Int_Dis()
{
  Field_Mod32(&LIN->IRQEN.reg, (uint8)LIN_IRQEN_TXD_TMOUT_IEN_Pos, LIN_IRQEN_TXD_TMOUT_IEN_Msk, 0u);
}

INLINE void LIN_M_SM_ERR_Int_En()
{
  Field_Mod32(&LIN->IRQEN.reg, (uint8)LIN_IRQEN_M_SM_ERR_IEN_Pos, LIN_IRQEN_M_SM_ERR_IEN_Msk, 1u);
}

INLINE void LIN_M_SM_ERR_Int_Dis()
{
  Field_Mod32(&LIN->IRQEN.reg, (uint8)LIN_IRQEN_M_SM_ERR_IEN_Pos, LIN_IRQEN_M_SM_ERR_IEN_Msk, 0u);
}

INLINE void LIN_Sync_Int_En()
{
  Field_Mod32(&SCU->LINST.reg, (uint8)SCU_LINST_SYNEN_Pos, SCU_LINST_SYNEN_Msk, 1u);
}

INLINE void LIN_Sync_Int_Dis()
{
  Field_Mod32(&SCU->LINST.reg, (uint8)SCU_LINST_SYNEN_Pos, SCU_LINST_SYNEN_Msk, 0u);
}

INLINE uint8 LIN_End_Of_Sync_Sts()
{
  return(u1_Field_Rd32(&SCU->LINST.reg, (uint8)SCU_LINST_EOFSYN_Pos, SCU_LINST_EOFSYN_Msk));
}

INLINE uint8 LIN_Err_In_Sync_Sts()
{
  return(u1_Field_Rd32(&SCU->LINST.reg, (uint8)SCU_LINST_ERRSYN_Pos, SCU_LINST_ERRSYN_Msk));
}

INLINE uint8 LIN_Break_Sts()
{
  return(u1_Field_Rd32(&SCU->LINST.reg, (uint8)SCU_LINST_BRK_Pos, SCU_LINST_BRK_Msk));
}

#endif
