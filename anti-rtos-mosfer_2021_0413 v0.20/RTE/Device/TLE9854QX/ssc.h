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
/**
 * \file     ssc.h
 *
 * \brief    High-Speed Synchronous Serial Interface low level access library
 *
 * \version  V0.2.2
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
** BG           Blandine Guillot                                              **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V0.2.0: 2018-02-13, TS:   Initial version of revision history              **
** V0.2.1: 2019-01-28, TS:   __STATIC_INLINE changed to INLINE                **
**                           Doxygen update                                   **
**                           Revision history moved from ssc.c to ssc.h       **
** V0.2.2: 2020-03-02, BG:   Updated revision history format                  **
*******************************************************************************/

#ifndef SSC_H
#define SSC_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle985x.h"
#include "types.h"
#include "sfr_access.h"

/*******************************************************************************
**                          Global Macro Definitions                          **
*******************************************************************************/
/**\brief SSC1 Manual Baudrate*/
#define SSC1_tBit_us (1.0 / (SSC1_MAN_BAUDRATE / 1000.0))
/**\brief SSC2 Manual Baudrate*/
#define SSC2_tBit_us (1.0 / (SSC2_MAN_BAUDRATE / 1000.0))

/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/
/** \brief Initializes the SSC1 module.
 *
 * \ingroup ssc_api
 */
void SSC1_Init(void);

/** \brief Initializes the SSC2 module.
 *
 * \ingroup ssc_api
 */
void SSC2_Init(void);

/*******************************************************************************
**                        Inline Function Declarations                        **
*******************************************************************************/
/** \brief Clears transmit interrupt flag for SSC1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the transmit interrupt for SSC1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SSC1_TX_Int_En();
 *   if ((uint8)SCU->IRCON2.bit.TIR1 == (uint8)1)
 *   {
 *     SSC1_TX_CALLBACK();
 *     SSC1_TX_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE void SSC1_TX_Int_Clr(void);

/** \brief Clears receive interrupt flag for SSC1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the receive interrupt for SSC1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SSC1_RX_Int_En();
 *   if ((uint8)SCU->IRCON2.bit.RIR1 == (uint8)1)
 *   {
 *     SSC1_RX_CALLBACK();
 *     SSC1_RX_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE void SSC1_RX_Int_Clr(void);

/** \brief Clears error interrupt flag for SSC1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the error interrupt for SSC1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SSC1_Err_Int_En();
 *   if ((uint8)SCU->IRCON2.bit.EIR1 == (uint8)1)
 *   {
 *     SSC1_ERR_CALLBACK();
 *     SSC1_Err_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE void SSC1_Err_Int_Clr(void);

/** \brief Clears transmit interrupt flag for SSC2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats thd transmit interrupt for SSC2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SSC2_TX_Int_En();
 *   if ((uint8)SCU->IRCON3.bit.TIR2 == (uint8)1)
 *   {
 *     SSC2_TX_CALLBACK();
 *     SSC2_TX_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE void SSC2_TX_Int_Clr(void);

/** \brief Clears receive interrupt flag for SSC2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the receive interrupt for SSC2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SSC2_RX_Int_En();
 *   if ((uint8)SCU->IRCON3.bit.RIR2 == (uint8)1)
 *   {
 *     SSC2_RX_CALLBACK();
 *     SSC2_RX_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE void SSC2_RX_Int_Clr(void);

/** \brief Clears error interrupt flag for SSC2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the error interrupt for SSC2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SSC2_Err_Int_En();
 *   if ((uint8)SCU->IRCON3.bit.EIR2 == (uint8)1)
 *   {
 *     SSC2_ERR_CALLBACK();
 *     SSC2_Err_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE void SSC2_Err_Int_Clr(void);

/** \brief Enables transmit interrupt for SSC1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats thd transmit interrupt for SSC1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SSC1_TX_Int_En();
 *   if ((uint8)SCU->IRCON2.bit.TIR1 == (uint8)1)
 *   {
 *     SSC1_TX_CALLBACK();
 *     SSC1_TX_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE void SSC1_TX_Int_En(void);

/** \brief Disables transmit interrupt for SSC1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats thd transmit interrupt for SSC1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SSC1_TX_Int_En();
 *   if ((uint8)SCU->IRCON2.bit.TIR1 == (uint8)1)
 *   {
 *     SSC1_TX_CALLBACK();
 *     SSC1_TX_Int_Clr();
 *   }
 *   SSC1_TX_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE void SSC1_TX_Int_Dis(void);

/** \brief Enables receive interrupt for SSC1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the receive interrupt for SSC1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SSC1_RX_Int_En();
 *   if ((uint8)SCU->IRCON2.bit.RIR1 == (uint8)1)
 *   {
 *     SSC1_RX_CALLBACK();
 *     SSC1_RX_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE void SSC1_RX_Int_En(void);

/** \brief Disables receive interrupt for SSC1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the receive interrupt for SSC1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SSC1_RX_Int_En();
 *   if ((uint8)SCU->IRCON2.bit.RIR1 == (uint8)1)
 *   {
 *     SSC1_RX_CALLBACK();
 *     SSC1_RX_Int_Clr();
 *   }
 *   SSC1_RX_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE void SSC1_RX_Int_Dis(void);

/** \brief Enables error interrupt for SSC1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the error interrupt for SSC1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SSC1_Err_Int_En();
 *   if ((uint8)SCU->IRCON2.bit.EIR1 == (uint8)1)
 *   {
 *     SSC1_ERR_CALLBACK();
 *     SSC1_Err_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE void SSC1_Err_Int_En(void);

/** \brief Disables error interrupt for SSC1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the error interrupt for SSC1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SSC1_Err_Int_En();
 *   if ((uint8)SCU->IRCON2.bit.EIR1 == (uint8)1)
 *   {
 *     SSC1_ERR_CALLBACK();
 *     SSC1_Err_Int_Clr();
 *   }
 *   SSC1_Err_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE void SSC1_Err_Int_Dis(void);

/** \brief Enables transmit interrupt for SSC2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats thd transmit interrupt for SSC2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SSC2_TX_Int_En();
 *   if ((uint8)SCU->IRCON3.bit.TIR2 == (uint8)1)
 *   {
 *     SSC2_TX_CALLBACK();
 *     SSC2_TX_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE void SSC2_TX_Int_En(void);

/** \brief Disables transmit interrupt for SSC2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats thd transmit interrupt for SSC2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SSC2_TX_Int_En();
 *   if ((uint8)SCU->IRCON3.bit.TIR2 == (uint8)1)
 *   {
 *     SSC2_TX_CALLBACK();
 *     SSC2_TX_Int_Clr();
 *   }
 *   SSC2_TX_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE void SSC2_TX_Int_Dis(void);

/** \brief Enables receive interrupt for SSC2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the receive interrupt for SSC2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SSC2_RX_Int_En();
 *   if ((uint8)SCU->IRCON3.bit.RIR2 == (uint8)1)
 *   {
 *     SSC2_RX_CALLBACK();
 *     SSC2_RX_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE void SSC2_RX_Int_En(void);

/** \brief Disables receive interrupt for SSC2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the receive interrupt for SSC2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SSC2_RX_Int_En();
 *   if ((uint8)SCU->IRCON3.bit.RIR2 == (uint8)1)
 *   {
 *     SSC2_RX_CALLBACK();
 *     SSC2_RX_Int_Clr();
 *   }
 *   SSC2_RX_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE void SSC2_RX_Int_Dis(void);

/** \brief Enables error interrupt for SSC2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the error interrupt for SSC2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SSC2_Err_Int_En();
 *   if ((uint8)SCU->IRCON3.bit.EIR2 == (uint8)1)
 *   {
 *     SSC2_ERR_CALLBACK();
 *     SSC2_Err_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE void SSC2_Err_Int_En(void);

/** \brief Disables error interrupt for SSC2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the error interrupt for SSC2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SSC2_Err_Int_En();
 *   if ((uint8)SCU->IRCON3.bit.EIR2 == (uint8)1)
 *   {
 *     SSC2_ERR_CALLBACK();
 *     SSC2_Err_Int_Clr();
 *   }
 *   SSC2_Err_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE void SSC2_Err_Int_Dis(void);

/** \brief Clears Transmit Error flag for SSC1.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Transmit Error flag for SSC1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SSC1_TE_Sts_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE void SSC1_TE_Sts_Clr(void);

/** \brief Clears Receive Error flag for SSC1.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Receive Error flag for SSC1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SSC1_RE_Sts_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE void SSC1_RE_Sts_Clr(void);

/** \brief Clears Phase Error flag for SSC1.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Phase Error flag for SSC1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SSC1_PE_Sts_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE void SSC1_PE_Sts_Clr(void);

/** \brief Clears BaudRate Error flag for SSC1.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears BaudRate Error flag for SSC1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SSC1_BE_Sts_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE void SSC1_BE_Sts_Clr(void);

/** \brief Clears Transmit Error flag for SSC2.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Transmit Error flag for SSC2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SSC2_TE_Sts_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE void SSC2_TE_Sts_Clr(void);

/** \brief Clears Receive Error flag for SSC2.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Receive Error flag for SSC2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SSC2_RE_Sts_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE void SSC2_RE_Sts_Clr(void);

/** \brief Clears Phase Error flag for SSC2.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Phase Error flag for SSC2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SSC2_PE_Sts_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE void SSC2_PE_Sts_Clr(void);

/** \brief Clears BaudRate Error flag for SSC2.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears BaudRate Error flag for SSC2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SSC2_BE_Sts_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE void SSC2_BE_Sts_Clr(void);

/** \brief Sends SSC1 data word.
 *
 * \param DataWord Data to send
 *
 * \brief <b>Example</b><br>
 * \brief This example sends "A" with SSC1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     SSC1_SendWord(0x41);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE void SSC1_SendWord(uint16 DataWord);

/** \brief Reads SSC1 data word from receive buffer.
 *
 * \return Received data
 *
 * \brief <b>Example</b><br>
 * \brief This example receives data with SSC1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 data;
 *
 *     data = SSC1_ReadWord();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE uint16 SSC1_ReadWord(void);

/** \brief Sends SSC2 data word.
 *
 * \param DataWord Data to send
 *
 * \brief <b>Example</b><br>
 * \brief This example sends "A" with SSC2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     SSC2_SendWord(0x41);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE void SSC2_SendWord(uint16 DataWord);

/** \brief Reads SSC2 data word from receive buffer.
 *
 * \return Received data
 *
 * \brief <b>Example</b><br>
 * \brief This example receives data with SSC2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 data;
 *
 *     data = SSC2_ReadWord();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ssc_api
 */
INLINE uint16 SSC2_ReadWord(void);

/*******************************************************************************
**                         Inline Function Definitions                        **
*******************************************************************************/
INLINE void SSC1_TX_Int_Clr()
{
  Field_Wrt32(&SCU->IRCON2CLR.reg, (uint8)SCU_IRCON2CLR_TIR1C_Pos, SCU_IRCON2CLR_TIR1C_Msk, 1u);
}

INLINE void SSC1_RX_Int_Clr()
{
  Field_Wrt32(&SCU->IRCON2CLR.reg, (uint8)SCU_IRCON2CLR_RIR1C_Pos, SCU_IRCON2CLR_RIR1C_Msk, 1u);
}

INLINE void SSC1_Err_Int_Clr()
{
  Field_Wrt32(&SCU->IRCON2CLR.reg, (uint8)SCU_IRCON2CLR_EIR1C_Pos, SCU_IRCON2CLR_EIR1C_Msk, 1u);
}

INLINE void SSC2_TX_Int_Clr()
{
  Field_Wrt32(&SCU->IRCON3CLR.reg, (uint8)SCU_IRCON3CLR_TIR2C_Pos, SCU_IRCON3CLR_TIR2C_Msk, 1u);
}

INLINE void SSC2_RX_Int_Clr()
{
  Field_Wrt32(&SCU->IRCON3CLR.reg, (uint8)SCU_IRCON3CLR_RIR2C_Pos, SCU_IRCON3CLR_RIR2C_Msk, 1u);
}

INLINE void SSC2_Err_Int_Clr()
{
  Field_Wrt32(&SCU->IRCON3CLR.reg, (uint8)SCU_IRCON3CLR_EIR2C_Pos, SCU_IRCON3CLR_EIR2C_Msk, 1u);
}

INLINE void SSC1_TX_Int_En()
{
  Field_Mod32(&SCU->MODIEN1.reg, (uint8)SCU_MODIEN1_TIREN1_Pos, SCU_MODIEN1_TIREN1_Msk, 1u);
}

INLINE void SSC1_TX_Int_Dis()
{
  Field_Mod32(&SCU->MODIEN1.reg, (uint8)SCU_MODIEN1_TIREN1_Pos, SCU_MODIEN1_TIREN1_Msk, 0u);
}

INLINE void SSC1_RX_Int_En()
{
  Field_Mod32(&SCU->MODIEN1.reg, (uint8)SCU_MODIEN1_RIREN1_Pos, SCU_MODIEN1_RIREN1_Msk, 1u);
}

INLINE void SSC1_RX_Int_Dis()
{
  Field_Mod32(&SCU->MODIEN1.reg, (uint8)SCU_MODIEN1_RIREN1_Pos, SCU_MODIEN1_RIREN1_Msk, 0u);
}

INLINE void SSC1_Err_Int_En()
{
  Field_Mod32(&SCU->MODIEN1.reg, (uint8)SCU_MODIEN1_EIREN1_Pos, SCU_MODIEN1_EIREN1_Msk, 1u);
}

INLINE void SSC1_Err_Int_Dis()
{
  Field_Mod32(&SCU->MODIEN1.reg, (uint8)SCU_MODIEN1_EIREN1_Pos, SCU_MODIEN1_EIREN1_Msk, 0u);
}

INLINE void SSC2_TX_Int_En()
{
  Field_Mod32(&SCU->MODIEN1.reg, (uint8)SCU_MODIEN1_TIREN2_Pos, SCU_MODIEN1_TIREN2_Msk, 1u);
}

INLINE void SSC2_TX_Int_Dis()
{
  Field_Mod32(&SCU->MODIEN1.reg, (uint8)SCU_MODIEN1_TIREN2_Pos, SCU_MODIEN1_TIREN2_Msk, 0u);
}

INLINE void SSC2_RX_Int_En()
{
  Field_Mod32(&SCU->MODIEN1.reg, (uint8)SCU_MODIEN1_RIREN2_Pos, SCU_MODIEN1_RIREN2_Msk, 1u);
}

INLINE void SSC2_RX_Int_Dis()
{
  Field_Mod32(&SCU->MODIEN1.reg, (uint8)SCU_MODIEN1_RIREN2_Pos, SCU_MODIEN1_RIREN2_Msk, 0u);
}

INLINE void SSC2_Err_Int_En()
{
  Field_Mod32(&SCU->MODIEN1.reg, (uint8)SCU_MODIEN1_EIREN2_Pos, SCU_MODIEN1_EIREN2_Msk, 1u);
}

INLINE void SSC2_Err_Int_Dis()
{
  Field_Mod32(&SCU->MODIEN1.reg, (uint8)SCU_MODIEN1_EIREN2_Pos, SCU_MODIEN1_EIREN2_Msk, 0u);
}

INLINE void SSC1_TE_Sts_Clr()
{
  Field_Wrt32(&SSC1->ISRCLR.reg, (uint8)SSC1_ISRCLR_TECLR_Pos, SSC1_ISRCLR_TECLR_Msk, 1u);
}

INLINE void SSC1_RE_Sts_Clr()
{
  Field_Wrt32(&SSC1->ISRCLR.reg, (uint8)SSC1_ISRCLR_RECLR_Pos, SSC1_ISRCLR_RECLR_Msk, 1u);
}

INLINE void SSC1_PE_Sts_Clr()
{
  Field_Wrt32(&SSC1->ISRCLR.reg, (uint8)SSC1_ISRCLR_PECLR_Pos, SSC1_ISRCLR_PECLR_Msk, 1u);
}

INLINE void SSC1_BE_Sts_Clr()
{
  Field_Wrt32(&SSC1->ISRCLR.reg, (uint8)SSC1_ISRCLR_BECLR_Pos, SSC1_ISRCLR_BECLR_Msk, 1u);
}

INLINE void SSC2_TE_Sts_Clr()
{
  Field_Wrt32(&SSC2->ISRCLR.reg, (uint8)SSC2_ISRCLR_TECLR_Pos, SSC2_ISRCLR_TECLR_Msk, 1u);
}

INLINE void SSC2_RE_Sts_Clr()
{
  Field_Wrt32(&SSC2->ISRCLR.reg, (uint8)SSC2_ISRCLR_RECLR_Pos, SSC2_ISRCLR_RECLR_Msk, 1u);
}

INLINE void SSC2_PE_Sts_Clr()
{
  Field_Wrt32(&SSC2->ISRCLR.reg, (uint8)SSC2_ISRCLR_PECLR_Pos, SSC2_ISRCLR_PECLR_Msk, 1u);
}

INLINE void SSC2_BE_Sts_Clr()
{
  Field_Wrt32(&SSC2->ISRCLR.reg, (uint8)SSC2_ISRCLR_BECLR_Pos, SSC2_ISRCLR_BECLR_Msk, 1u);
}

INLINE void SSC1_SendWord(uint16 DataWord)
{
  Field_Wrt32(&SSC1->TB.reg, (uint8)SSC1_TB_TB_VALUE_Pos, SSC1_TB_TB_VALUE_Msk, DataWord);  
}

INLINE uint16 SSC1_ReadWord(void)
{
  return(u16_Field_Rd32(&SSC1->RB.reg, (uint8)SSC1_RB_RB_VALUE_Pos, SSC1_RB_RB_VALUE_Msk));  
}

INLINE void SSC2_SendWord(uint16 DataWord)
{
  Field_Wrt32(&SSC2->TB.reg, (uint8)SSC2_TB_TB_VALUE_Pos, SSC2_TB_TB_VALUE_Msk, DataWord);    
}

INLINE uint16 SSC2_ReadWord(void)
{
  return(u16_Field_Rd32(&SSC2->RB.reg, (uint8)SSC2_RB_RB_VALUE_Pos, SSC2_RB_RB_VALUE_Msk));  
}

#endif
