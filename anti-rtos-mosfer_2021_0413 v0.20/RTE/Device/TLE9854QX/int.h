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
 * \file     int.h
 *
 * \brief    Interrupt low level access library
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
**                           Revision history moved from int.c to int.h       **
**                           NMI Mask macros added to meet MISRA 2012         **
**                           EXINTx Mask macros added to meet MISRA 2012      **
** V0.2.2: 2020-03-02, BG:   Updated revision history format                  **
*******************************************************************************/

#ifndef INT_H
#define INT_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle985x.h"
#include "types.h"
#include "sfr_access.h"

/*******************************************************************************
**                          Global Macro Definitions                          **
*******************************************************************************/
/**\brief NMI Flags selection macro, NMI_WDT */
#define NMI_WDT  (1u << 0u)
/**\brief NMI Flags selection macro, NMI_PLL */
#define NMI_PLL  (1u << 1u)
/**\brief NMI Flags selection macro, NMI_OT */
#define NMI_OT   (1u << 3u)
/**\brief NMI Flags selection macro, NMI_OWT */
#define NMI_OWT  (1u << 4u)
/**\brief NMI Flags selection macro, NMI_MAP */
#define NMI_MAP  (1u << 5u)
/**\brief NMI Flags selection macro, NMI_ECC */
#define NMI_ECC  (1u << 6u)
/**\brief NMI Flags selection macro, NMI_SUP */
#define NMI_SUP  (1u << 7u)
/**\brief NMI Flags selection macro, NMI_STOF */
#define NMI_STOF (1u << 8u)

/**\brief External Interrupt 0 Rising Edge Bit Position */
#define SCU_EXICON0_EXINT0_RE_Pos (0UL)
/**\brief External Interrupt 0 Rising Edge Bit Mask */
#define SCU_EXICON0_EXINT0_RE_Msk (0x01UL)
/**\brief External Interrupt 0 Falling Edge Bit Position */
#define SCU_EXICON0_EXINT0_FE_Pos (1UL)
/**\brief External Interrupt 0 Falling Edge Bit Mask */
#define SCU_EXICON0_EXINT0_FE_Msk (0x02UL)
/**\brief External Interrupt 1 Rising Edge Bit Position */
#define SCU_EXICON0_EXINT1_RE_Pos (2UL)
/**\brief External Interrupt 1 Rising Edge Bit Mask */
#define SCU_EXICON0_EXINT1_RE_Msk (0x04UL)
/**\brief External Interrupt 1 Falling Edge Bit Position */
#define SCU_EXICON0_EXINT1_FE_Pos (3UL)
/**\brief External Interrupt 1 Falling Edge Bit Mask */
#define SCU_EXICON0_EXINT1_FE_Msk (0x08UL)
/**\brief External Interrupt 2 Rising Edge Bit Position */
#define SCU_EXICON0_EXINT2_RE_Pos (4UL)
/**\brief External Interrupt 2 Rising Edge Bit Mask */
#define SCU_EXICON0_EXINT2_RE_Msk (0x10UL)
/**\brief External Interrupt 2 Falling Edge Bit Position */
#define SCU_EXICON0_EXINT2_FE_Pos (5UL)
/**\brief External Interrupt 2 Falling Edge Bit Mask */
#define SCU_EXICON0_EXINT2_FE_Msk (0x20UL)

/**\brief NMI Status Read Bit Mask */
#define SCU_NMISR_Msk (0x1FBu)
/**\brief NMI Clear Bit Mask */
#define SCU_NMICLR_Msk (0x33u)

/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/
/** \brief Initializes the Interrupt module.
 *
 * \ingroup int_api
 */
void INT_Init(void);

/*******************************************************************************
**                        Inline Function Declarations                        **
*******************************************************************************/
/** \brief Enables Global Interrupt (Pending interrupt requests are not blocked from the core).
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Global Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Global_Int_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Global_Int_En(void);

/** \brief Disables Global Interrupt (All pending interrupt requests,except NMI, are blocked from the core).
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Global Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Global_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Global_Int_Dis(void);

/** \brief Enables RAM Double Bit ECC Error Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the RAM Double Bit ECC Error Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_ECC_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIECC == (uint8)1)
 *   {
 *     ECC_RAM_DoubleBit_Int_En();
 *     if ((uint8)SCU->EDCSTAT.bit.RDBE == (uint8)1)
 *     {
 *       SCU_ECC_RAM_DB_CALLBACK();
 *       ECC_RAM_DoubleBit_Int_Clr();
 *     }
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void ECC_RAM_DoubleBit_Int_En(void);

/** \brief Disables RAM Double Bit ECC Error Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the RAM Double Bit ECC Error Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_ECC_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIECC == (uint8)1)
 *   {
 *     ECC_RAM_DoubleBit_Int_En();
 *     if ((uint8)SCU->EDCSTAT.bit.RDBE == (uint8)1)
 *     {
 *       SCU_ECC_RAM_DB_CALLBACK();
 *       ECC_RAM_DoubleBit_Int_Clr();
 *     }
 *   }
 *   ECC_RAM_DoubleBit_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void ECC_RAM_DoubleBit_Int_Dis(void);

/** \brief Enables NVM Double Bit ECC Error Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the NVM Double Bit ECC Error Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_ECC_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIECC == (uint8)1)
 *   {
 *     ECC_NVM_DoubleBit_Int_En();
 *     if ((uint8)SCU->EDCSTAT.bit.NVMDBE == (uint8)1)
 *     {
 *       SCU_ECC_NVM_DB_CALLBACK();
 *       ECC_NVM_DoubleBit_Int_Clr();
 *     }
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void ECC_NVM_DoubleBit_Int_En(void);

/** \brief Disables NVM Double Bit ECC Error Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the NVM Double Bit ECC Error Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_ECC_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIECC == (uint8)1)
 *   {
 *     ECC_NVM_DoubleBit_Int_En();
 *     if ((uint8)SCU->EDCSTAT.bit.NVMDBE == (uint8)1)
 *     {
 *       SCU_ECC_NVM_DB_CALLBACK();
 *       ECC_NVM_DoubleBit_Int_Clr();
 *     }
 *   }
 *   ECC_NVM_DoubleBit_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void ECC_NVM_DoubleBit_Int_Dis(void);

/** \brief Clears RAM Single Bit Error Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example checks the RAM Single Bit Error Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   if ((uint8)SCU->EDCSTAT.bit.RSBE == (uint8)1)
 *   {
 *     ECC_RAM_SingleBit_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void ECC_RAM_SingleBit_Int_Clr(void);

/** \brief Clears RAM Double Bit ECC Error Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the RAM Double Bit ECC Error Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ECC_RAM_DoubleBit_Int_En();
 *   if ((uint8)SCU->EDCSTAT.bit.RDBE == (uint8)1)
 *   {
 *     SCU_ECC_RAM_DB_CALLBACK();
 *     ECC_RAM_DoubleBit_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void ECC_RAM_DoubleBit_Int_Clr(void);

/** \brief Clears NVM Double Bit ECC Error Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the NVM Double Bit ECC Error Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ECC_NVM_DoubleBit_Int_En();
 *   if ((uint8)SCU->EDCSTAT.bit.NVMDBE == (uint8)1)
 *   {
 *     SCU_ECC_NVM_DB_CALLBACK();
 *     ECC_NVM_DoubleBit_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void ECC_NVM_DoubleBit_Int_Clr(void);

/** \brief Enables External Interrupt 0x on rising edge.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 0x on rising edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT0_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT0R == (uint8)1)
 *   {
 *     EXINT0_RISING_CALLBACK();
 *     EXINT0_Rising_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT0_Rising_Edge_Int_En(void);

/** \brief Disables External Interrupt 0x on rising edge.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 0x on rising edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT0_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT0R == (uint8)1)
 *   {
 *     EXINT0_RISING_CALLBACK();
 *     EXINT0_Rising_Edge_Int_Clr();
 *   }
 *   EXINT0_Rising_Edge_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT0_Rising_Edge_Int_Dis(void);

/** \brief Enables External Interrupt 0x on falling edge.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 0x on falling edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT0_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT0F == (uint8)1)
 *   {
 *     EXINT0_FALLING_CALLBACK();
 *     EXINT0_Falling_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT0_Falling_Edge_Int_En(void);

/** \brief Disables External Interrupt 0x on falling edge.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 0x on falling edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT0_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT0F == (uint8)1)
 *   {
 *     EXINT0_FALLING_CALLBACK();
 *     EXINT0_Falling_Edge_Int_Clr();
 *   }
 *   EXINT0_Falling_Edge_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT0_Falling_Edge_Int_Dis(void);

/** \brief Enables External Interrupt 1x on rising edge.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 1x on rising edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT1_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT1R == (uint8)1)
 *   {
 *     EXINT1_RISING_CALLBACK();
 *     EXINT1_Rising_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT1_Rising_Edge_Int_En(void);

/** \brief Disables External Interrupt 1x on rising edge.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 1x on rising edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT1_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT1R == (uint8)1)
 *   {
 *     EXINT1_RISING_CALLBACK();
 *     EXINT1_Rising_Edge_Int_Clr();
 *   }
 *   EXINT1_Rising_Edge_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT1_Rising_Edge_Int_Dis(void);

/** \brief Enables External Interrupt 1x on falling edge.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 1x on falling edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT1_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT1F == (uint8)1)
 *   {
 *     EXINT1_FALLING_CALLBACK();
 *     EXINT1_Falling_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT1_Falling_Edge_Int_En(void);

/** \brief Disables External Interrupt 1x on falling edge.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 1x on falling edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT1_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT1F == (uint8)1)
 *   {
 *     EXINT1_FALLING_CALLBACK();
 *     EXINT1_Falling_Edge_Int_Clr();
 *   }
 *   EXINT1_Falling_Edge_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT1_Falling_Edge_Int_Dis(void);

/** \brief Enables External Interrupt 2x on rising edge.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 2x on rising edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT2_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT2R == (uint8)1)
 *   {
 *     EXINT2_RISING_CALLBACK();
 *     EXINT2_Rising_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT2_Rising_Edge_Int_En(void);

/** \brief Disables External Interrupt 2x on rising edge.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 2x on rising edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT2_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT2R == (uint8)1)
 *   {
 *     EXINT2_RISING_CALLBACK();
 *     EXINT2_Rising_Edge_Int_Clr();
 *   }
 *   EXINT2_Rising_Edge_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT2_Rising_Edge_Int_Dis(void);

/** \brief Enables External Interrupt 2x on falling edge.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 2x on falling edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT2_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT2F == (uint8)1)
 *   {
 *     EXINT2_FALLING_CALLBACK();
 *     EXINT2_Falling_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT2_Falling_Edge_Int_En(void);

/** \brief Disables External Interrupt 2x on falling edge.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 2x on falling edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT2_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT2F == (uint8)1)
 *   {
 *     EXINT2_FALLING_CALLBACK();
 *     EXINT2_Falling_Edge_Int_Clr();
 *   }
 *   EXINT2_Falling_Edge_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT2_Falling_Edge_Int_Dis(void);

/** \brief Clears Interrupt Flag for External Interrupt 0x on rising edge.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 0x on rising edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT0_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT0R == (uint8)1)
 *   {
 *     EXINT0_RISING_CALLBACK();
 *     EXINT0_Rising_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT0_Rising_Edge_Int_Clr(void);

/** \brief Clears Interrupt Flag for External Interrupt 0x on falling edge.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 0x on falling edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT0_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT0F == (uint8)1)
 *   {
 *     EXINT0_FALLING_CALLBACK();
 *     EXINT0_Falling_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT0_Falling_Edge_Int_Clr(void);

/** \brief Clears Interrupt Flag for External Interrupt 1x on rising edge.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 1x on rising edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT1_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT1R == (uint8)1)
 *   {
 *     EXINT1_RISING_CALLBACK();
 *     EXINT1_Rising_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT1_Rising_Edge_Int_Clr(void);

/** \brief Clears Interrupt Flag for External Interrupt 1x on falling edge.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 1x on falling edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT1_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT1F == (uint8)1)
 *   {
 *     EXINT1_FALLING_CALLBACK();
 *     EXINT1_Falling_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT1_Falling_Edge_Int_Clr(void);

/** \brief Clears Interrupt Flag for External Interrupt 2x on rising edge.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 2x on rising edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT2_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT2R == (uint8)1)
 *   {
 *     EXINT2_RISING_CALLBACK();
 *     EXINT2_Rising_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT2_Rising_Edge_Int_Clr(void);

/** \brief Clears Interrupt Flag for External Interrupt 2x on falling edge.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Interrupt 2x on falling edge.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   EXINT2_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON0.bit.EXINT2F == (uint8)1)
 *   {
 *     EXINT2_FALLING_CALLBACK();
 *     EXINT2_Falling_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void EXINT2_Falling_Edge_Int_Clr(void);

/** \brief Enables Watchdog Timer NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Watchdog Timer NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_WDT_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIWDT == (uint8)1)
 *   {
 *     if (SCU->WDTCON.bit.WDTEN == 1u)
 *     {
 *       if (SCU->WDTCON.bit.WDTPR == 1u)
 *       {
 *         SCU_NMI_WDT_CALLBACK();
 *         NMI_WDT_Int_Clr();
 *     }
 *     }
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_WDT_Int_En(void);

/** \brief Disables Watchdog Timer NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Watchdog Timer NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_WDT_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIWDT == (uint8)1)
 *   {
 *     if (SCU->WDTCON.bit.WDTEN == 1u)
 *     {
 *       if (SCU->WDTCON.bit.WDTPR == 1u)
 *      {
 *         SCU_NMI_WDT_CALLBACK();
 *         NMI_WDT_Int_Clr();
 *     }
 *     }
 *   }
 *   NMI_WDT_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_WDT_Int_Dis(void);

/** \brief Enables PLL Loss of Lock NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the PLL Loss of Lock NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_PLL_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIPLL == (uint8)1)
 *   {
 *     if (SCU->PLL_CON.bit.LOCK == 1u)
 *     {
 *       SCU_NMI_PLL_CALLBACK();
 *       NMI_PLL_Int_Clr();
 *     }
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_PLL_Int_En(void);

/** \brief Disables PLL Loss of Lock NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the PLL Loss of Lock NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_PLL_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIPLL == (uint8)1)
 *   {
 *     if (SCU->PLL_CON.bit.LOCK == 1u)
 *     {
 *       SCU_NMI_PLL_CALLBACK();
 *       NMI_PLL_Int_Clr();
 *     }
 *   }
 *   NMI_PLL_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_PLL_Int_Dis(void);

/** \brief Enables ECC Error NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the RAM Double Bit ECC Error Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_ECC_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIECC == (uint8)1)
 *   {
 *     ECC_RAM_DoubleBit_Int_En();
 *     if ((uint8)SCU->EDCSTAT.bit.RDBE == (uint8)1)
 *     {
 *       SCU_ECC_RAM_DB_CALLBACK();
 *       ECC_RAM_DoubleBit_Int_Clr();
 *     }
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_ECC_Int_En(void);

/** \brief Disables ECC Error NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the RAM Double Bit ECC Error Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_ECC_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIECC == (uint8)1)
 *   {
 *     ECC_RAM_DoubleBit_Int_En();
 *     if ((uint8)SCU->EDCSTAT.bit.RDBE == (uint8)1)
 *     {
 *       SCU_ECC_RAM_DB_CALLBACK();
 *       ECC_RAM_DoubleBit_Int_Clr();
 *     }
 *   }
 *   NMI_ECC_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_ECC_Int_Dis(void);

/** \brief Enables NVM Map Error NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the NVM Map Error NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_MAP_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIMAP == (uint8)1)
 *   {
 *     SCU_NMI_MAP_CALLBACK();
 *     NMI_MAP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_MAP_Int_En(void);

/** \brief Disables NVM Map Error NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the NVM Map Error NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_MAP_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIMAP == (uint8)1)
 *   {
 *     SCU_NMI_MAP_CALLBACK();
 *     NMI_MAP_Int_Clr();
 *   }
 *   NMI_MAP_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_MAP_Int_Dis(void);

/** \brief Enables Supply Prewarning NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 PostProcessing Channel0 Upper Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_SUP_Int_En();
 *   if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH0_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH0_UP_IEN_Msk) == (uint8)1)
 *   {
 *     if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH0_UP_IS_Pos, ADC1_IRQS_2_PP_CH0_UP_IS_Msk) == (uint8)1)
 *     {
 *       ADC1_PP_CH0_UP_CALLBACK();
 *       ADC1_PP_Ch0_UP_Int_Clr();
 *     }
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_SUP_Int_En(void);

/** \brief Disables Supply Prewarning NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 PostProcessing Channel0 Upper Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_SUP_Int_En();
 *   if (u1_Field_Rd32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH0_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH0_UP_IEN_Msk) == (uint8)1)
 *   {
 *     if (u1_Field_Rd32(&ADC1->IRQS_2.reg, (uint8)ADC1_IRQS_2_PP_CH0_UP_IS_Pos, ADC1_IRQS_2_PP_CH0_UP_IS_Msk) == (uint8)1)
 *     {
 *       ADC1_PP_CH0_UP_CALLBACK();
 *       ADC1_PP_Ch0_UP_Int_Clr();
 *     }
 *   }
 *   NMI_SUP_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_SUP_Int_Dis(void);

/** \brief Enables Oscillator Watchdog NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Oscillator Watchdog NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_OWD_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIOWD == (uint8)1)
 *   {
 *     SCU_NMI_OWD_CALLBACK();
 *     NMI_OWD_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_OWD_Int_En(void);

/** \brief Disables Oscillator Watchdog NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Oscillator Watchdog NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_OWD_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIOWD == (uint8)1)
 *   {
 *     SCU_NMI_OWD_CALLBACK();
 *     NMI_OWD_Int_Clr();
 *   }
 *   NMI_OWD_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_OWD_Int_Dis(void);

/** \brief Enables NMI OT.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC2 System Temperature Low Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_OT_Int_En();
 *   if (u1_Field_Rd32(&SCUPM->SYS_IRQ_CTRL.reg, (uint8)SCUPM_SYS_IRQ_CTRL_SYS_OTWARN_IE_Pos, SCUPM_SYS_IRQ_CTRL_SYS_OTWARN_IE_Msk) == (uint8)1)
 *   {
 *     if (u1_Field_Rd32(&SCUPM->SYS_IS.reg, (uint8)SCUPM_SYS_IS_SYS_OTWARN_IS_Pos, SCUPM_SYS_IS_SYS_OTWARN_IS_Msk) == (uint8)1)
 *     {
 *       ADC2_SYS_TEMP_LO_CALLBACK();
 *       ADC2_TEMP_WARN_Int_Clr();
 *     }
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_OT_Int_En(void);

/** \brief Disables NMI OT.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC2 System Tempertaure Low Interrpt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_OT_Int_En();
 *   if (u1_Field_Rd32(&SCUPM->SYS_IRQ_CTRL.reg, (uint8)SCUPM_SYS_IRQ_CTRL_SYS_OTWARN_IE_Pos, SCUPM_SYS_IRQ_CTRL_SYS_OTWARN_IE_Msk) == (uint8)1)
 *   {
 *     if (u1_Field_Rd32(&SCUPM->SYS_IS.reg, (uint8)SCUPM_SYS_IS_SYS_OTWARN_IS_Pos, SCUPM_SYS_IS_SYS_OTWARN_IS_Msk) == (uint8)1)
 *     {
 *       ADC2_SYS_TEMP_LO_CALLBACK();
 *       ADC2_TEMP_WARN_Int_Clr();
 *     }
 *   }
 *   NMI_OT_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_OT_Int_Dis(void);

/** \brief Enables Stack Overflow NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Stack Overflow NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_STOF_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMISTOF == (uint8)1)
 *   {
 *     STOF_Int_En();
 *     if (SCU->STACK_OVF_STS.bit.STOF_STS == 1u)
 *      {
 *       SCU_NMI_STOF_CALLBACK();
 *       NMI_STOF_Int_Clr();
 *     }
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_STOF_Int_En(void);

/** \brief Disables Stack Overflow NMI.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Stack Overflow NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_STOF_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMISTOF == (uint8)1)
 *   {
 *     STOF_Int_En();
 *     if (SCU->STACK_OVF_STS.bit.STOF_STS == 1u)
 *      {
 *       SCU_NMI_STOF_CALLBACK();
 *       NMI_STOF_Int_Clr();
 *     }
 *   }
 *   NMI_STOF_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_STOF_Int_Dis(void);

/** \brief Clears Watchdog Timer NMI Flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Watchdog Timer NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_WDT_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIWDT == (uint8)1)
 *   {
 *     if (SCU->WDTCON.bit.WDTEN == 1u)
 *     {
 *       if (SCU->WDTCON.bit.WDTPR == 1u)
 *      {
 *         SCU_NMI_WDT_CALLBACK();
 *         NMI_WDT_Int_Clr();
 *     }
 *     }
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_WDT_Int_Clr(void);

/** \brief Clears PLL Loss of Lock NMI Flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the PLL Loss of Lock NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_PLL_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIPLL == (uint8)1)
 *   {
 *     if (SCU->PLL_CON.bit.LOCK == 1u)
 *     {
 *       SCU_NMI_PLL_CALLBACK();
 *       NMI_PLL_Int_Clr();
 *     }
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_PLL_Int_Clr(void);

/** \brief Clears Oscillator Watchdog NMI Flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Oscillator Watchdog NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_OWD_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIOWD == (uint8)1)
 *   {
 *     SCU_NMI_OWD_CALLBACK();
 *     NMI_OWD_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_OWD_Int_Clr(void);

/** \brief Clears NVM Map Error NMI Flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the NVM Map Error NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_OWD_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMIMAP == (uint8)1)
 *   {
 *     SCU_NMI_MAP_CALLBACK();
 *     NMI_MAP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_MAP_Int_Clr(void);

/** \brief Enables Stack Overflow.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Stack Overflow NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_STOF_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMISTOF == (uint8)1)
 *   {
 *     NMI_STOF_En();
 *     if (SCU->STACK_OVF_STS.bit.STOF_STS == 1u)
 *     {
 *       SCU_NMI_STOF_CALLBACK();
 *       NMI_STOF_Int_Clr();
 *     }
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_STOF_En(void);

/** \brief Disables Stack Overflow.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Stack Overflow NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_STOF_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMISTOF == (uint8)1)
 *   {
 *     NMI_STOF_En();
 *     if (SCU->STACK_OVF_STS.bit.STOF_STS == 1u)
 *     {
 *       SCU_NMI_STOF_CALLBACK();
 *       NMI_STOF_Int_Clr();
 *     }
 *   }
 *   NMI_STOF_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_STOF_Dis(void);

/** \brief Clears Stack Overflow status.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Stack Overflow NMI.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_STOF_Int_En();
 *   if ((uint8)SCU->NMISR.bit.FNMISTOF == (uint8)1)
 *   {
 *     STOF_Int_En();
 *     if (SCU->STACK_OVF_STS.bit.STOF_STS == 1u)
 *     {
 *       SCU_NMI_STOF_CALLBACK();
 *       NMI_STOF_Int_Clr();
 *     }
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_STOF_Int_Clr(void);

/** \brief Sets Interrupt Pending for PORT2.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Interrupt Pending for PORT2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_PORT2_Pend_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_PORT2_Pend_Set(void);

/** \brief Sets Interrupt Pending for MONx.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Interrupt Pending for MONx.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_MON_Pend_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_MON_Pend_Set(void);

/** \brief Sets Interrupt Pending for Differential Unit.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Interrupt Pending for Differential Unit.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_DU_Pend_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_DU_Pend_Set(void);

/** \brief Sets Interrupt Pending for Current Sense Amplifier.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Interrupt Pending for Current Sense Amplifier.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_OPA_Pend_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_OPA_Pend_Set(void);

/** \brief Sets Interrupt Pending for High-Side Switch.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Interrupt Pending for High-Side Switch.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_HS_Pend_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_HS_Pend_Set(void);

/** \brief Sets Interrupt Pending for Bridge Driver.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Interrupt Pending for Bridge Driver.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_BDRV_Pend_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_BDRV_Pend_Set(void);

/** \brief Sets Interrupt Pending for Charge Pump.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Interrupt Pending for Charge Pump.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_CP_Pend_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_CP_Pend_Set(void);

/** \brief Sets Interrupt Pending for Math Divider.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Interrupt Pending for Math Divider.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_MATHDIV_Pend_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_MATHDIV_Pend_Set(void);

/** \brief Sets Interrupt Pending for WAKEUP.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Interrupt Pending for WAKEUP.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_WAKEUP_Pend_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_WAKEUP_Pend_Set(void);

/** \brief Sets Interrupt Pending for EXINT1.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Interrupt Pending for EXINT1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_EXINT1_Pend_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_EXINT1_Pend_Set(void);

/** \brief Sets Interrupt Pending for EXINT0.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Interrupt Pending for EXINT0.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_EXINT0_Pend_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_EXINT0_Pend_Set(void);

/** \brief Sets Interrupt Pending for UART2.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Interrupt Pending for UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_UART2_Pend_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_UART2_Pend_Set(void);

/** \brief Sets Interrupt Pending for UART1.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Interrupt Pending for UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_UART1_Pend_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_UART1_Pend_Set(void);

/** \brief Sets Interrupt Pending for SSC2.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Interrupt Pending for SSC2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_SSC2_Pend_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_SSC2_Pend_Set(void);

/** \brief Sets Interrupt Pending for SSC1.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Interrupt Pending for SSC1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_SSC1_Pend_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_SSC1_Pend_Set(void);

/** \brief Sets Interrupt Pending for CCU6 SR3.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Interrupt Pending for CCU6 SR3.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_CCU6SR3_Pend_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_CCU6SR3_Pend_Set(void);

/** \brief Sets Interrupt Pending for CCU6 SR2.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Interrupt Pending for CCU6 SR2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_CCU6SR2_Pend_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_CCU6SR2_Pend_Set(void);

/** \brief Sets Interrupt Pending for CCU6 SR1.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Interrupt Pending for CCU6 SR1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_CCU6SR1_Pend_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_CCU6SR1_Pend_Set(void);

/** \brief Sets Interrupt Pending for CCU6 SR0.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Interrupt Pending for CCU6 SR0.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_CCU6SR0_Pend_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_CCU6SR0_Pend_Set(void);

/** \brief Sets Interrupt Pending for ADC1.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Interrupt Pending for ADC1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_ADC1_Pend_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_ADC1_Pend_Set(void);

/** \brief Sets Interrupt Pending for ADC2.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Interrupt Pending for ADC2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_ADC2_Pend_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_ADC2_Pend_Set(void);

/** \brief Sets Interrupt Pending for GPT2.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Interrupt Pending for GPT2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_GPT2_Pend_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_GPT2_Pend_Set(void);

/** \brief Sets Interrupt Pending for GPT1.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Interrupt Pending for GPT1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_GPT1_Pend_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_GPT1_Pend_Set(void);

/** \brief Clears Interrupt Pending for PORT2.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Interrupt Pending for PORT2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_PORT2_Pend_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_PORT2_Pend_Clr(void);

/** \brief Clears Interrupt Pending for MONx.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Interrupt Pending for MONx.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_MON_Pend_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_MON_Pend_Clr(void);

/** \brief Clears Interrupt Pending for Differential Unit.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Interrupt Pending for Differential Unit.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_DU_Pend_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_DU_Pend_Clr(void);

/** \brief Clears Interrupt Pending for Current Sense Amplifier.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Interrupt Pending for Current Sense Amplifier.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_OPA_Pend_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_OPA_Pend_Clr(void);

/** \brief Clears Interrupt Pending for High-Side Switch.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Interrupt Pending for High-Side Switch.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_HS_Pend_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_HS_Pend_Clr(void);

/** \brief Clears Interrupt Pending for Bridge Driver.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Interrupt Pending for Bridge Driver.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_BDRV_Pend_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_BDRV_Pend_Clr(void);

/** \brief Clears Interrupt Pending for Charge Pump.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Interrupt Pending for Charge Pump.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_CP_Pend_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_CP_Pend_Clr(void);

/** \brief Clears Interrupt Pending for Math Divider.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Interrupt Pending for Math Divider.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_MATHDIV_Pend_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_MATHDIV_Pend_Clr(void);

/** \brief Clears Interrupt Pending for WAKEUP.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Interrupt Pending for WAKEUP.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_WAKEUP_Pend_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_WAKEUP_Pend_Clr(void);

/** \brief Clears Interrupt Pending for EXINT1.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Interrupt Pending for EXINT1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_EXINT1_Pend_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_EXINT1_Pend_Clr(void);

/** \brief Clears Interrupt Pending for EXINT0.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Interrupt Pending for EXINT0.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_EXINT0_Pend_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_EXINT0_Pend_Clr(void);

/** \brief Clears Interrupt Pending for UART2.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Interrupt Pending for UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_UART2_Pend_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_UART2_Pend_Clr(void);

/** \brief Clears Interrupt Pending for UART1.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Interrupt Pending for UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_UART1_Pend_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_UART1_Pend_Clr(void);

/** \brief Clears Interrupt Pending for SSC2.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Interrupt Pending for SSC2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_SSC2_Pend_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_SSC2_Pend_Clr(void);

/** \brief Clears Interrupt Pending for SSC1.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Interrupt Pending for SSC1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_SSC1_Pend_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_SSC1_Pend_Clr(void);

/** \brief Clears Interrupt Pending for CCU6 SR3.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Interrupt Pending for CCU6 SR3.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_CCU6SR3_Pend_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_CCU6SR3_Pend_Clr(void);

/** \brief Clears Interrupt Pending for CCU6 SR2.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Interrupt Pending for CCU6 SR2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_CCU6SR2_Pend_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_CCU6SR2_Pend_Clr(void);

/** \brief Clears Interrupt Pending for CCU6 SR1.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Interrupt Pending for CCU6 SR1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_CCU6SR1_Pend_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_CCU6SR1_Pend_Clr(void);

/** \brief Clears Interrupt Pending for CCU6 SR0.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Interrupt Pending for CCU6 SR0.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_CCU6SR0_Pend_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_CCU6SR0_Pend_Clr(void);

/** \brief Clears Interrupt Pending for ADC1.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Interrupt Pending for ADC1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_ADC1_Pend_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_ADC1_Pend_Clr(void);

/** \brief Clears Interrupt Pending for ADC2.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Interrupt Pending for ADC2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_ADC2_Pend_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_ADC2_Pend_Clr(void);

/** \brief Clears Interrupt Pending for GPT2.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Interrupt Pending for GPT2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_GPT2_Pend_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_GPT2_Pend_Clr(void);

/** \brief Clears Interrupt Pending Status for GPT1.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Interrupt Pending for GPT1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   Int_GPT1_Pend_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void Int_GPT1_Pend_Clr(void);

/** \brief Sets NMI Pending.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets NMI Pending.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   NMI_Pend_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void NMI_Pend_Set(void);

/** \brief Sets PENDSV Pending.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PENDSV Pending.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PENDSV_Pend_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void PENDSV_Pend_Set(void);

/** \brief Clears PENDSV Pending Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears PENDSV Pending Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PENDSV_Pend_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void PENDSV_Pend_Clr(void);

/** \brief Sets SysTick Exception Pending.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets SysTick Exception Pending.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SysTick_Pend_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void SysTick_Pend_Set(void);

/** \brief Clears SysTick Exception Pending Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears SysTick Exception Pending Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SysTick_Pend_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void SysTick_Pend_Clr(void);

/** \brief Reads out the NMI Status
 *
 * \return NMI status flags
 *
 * \brief <b>Example</b><br>
 * \brief This example Reads out the NMI Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *    uint16 val;
 *
 *    val = INT_Get_NMI_Status();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE uint16 INT_Get_NMI_Status(void);

/** \brief Clears the NMI Status flags
 *
 * \param Flags NMI Status bit mask
 *
 * \brief <b>Example</b><br>
 * \brief This example Clears All the NMI Status flags.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   INT_Clr_NMI_Status(0x33);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void INT_Clr_NMI_Status(uint8 Flags);

/** \brief Enables the global interrupt IEN0.EA
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Global Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   INT_Enable_Global_Int();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void INT_Enable_Global_Int(void);

/** \brief Disables the global interrupt IEN0.EA
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Global Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   INT_Disable_Global_Int();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup int_api
 */
INLINE void INT_Disable_Global_Int(void);

/*******************************************************************************
**                        Inline Function Definitions                         **
*******************************************************************************/
INLINE void Global_Int_En()
{
  Field_Wrt32(&SCU->IEN0.reg, (uint8)SCU_IEN0_EA_Pos, SCU_IEN0_EA_Msk, 1u);
}

INLINE void Global_Int_Dis()
{
  Field_Wrt32(&SCU->IEN0.reg, (uint8)SCU_IEN0_EA_Pos, SCU_IEN0_EA_Msk, 0u);
}

INLINE void ECC_RAM_DoubleBit_Int_En()
{
  Field_Mod32(&SCU->EDCCON.reg, (uint8)SCU_EDCCON_RIE_Pos, SCU_EDCCON_RIE_Msk, 1u);
}

INLINE void ECC_RAM_DoubleBit_Int_Dis()
{
  Field_Mod32(&SCU->EDCCON.reg, (uint8)SCU_EDCCON_RIE_Pos, SCU_EDCCON_RIE_Msk, 0u);
}

INLINE void ECC_NVM_DoubleBit_Int_En()
{
  Field_Mod32(&SCU->EDCCON.reg, (uint8)SCU_EDCCON_NVMIE_Pos, SCU_EDCCON_NVMIE_Msk, 1u);
}

INLINE void ECC_NVM_DoubleBit_Int_Dis()
{
  Field_Mod32(&SCU->EDCCON.reg, (uint8)SCU_EDCCON_NVMIE_Pos, SCU_EDCCON_NVMIE_Msk, 0u);
}

INLINE void ECC_RAM_SingleBit_Int_Clr()
{
  Field_Wrt32(&SCU->EDCSCLR.reg, (uint8)SCU_EDCSCLR_RSBEC_Pos, SCU_EDCSCLR_RSBEC_Msk, 1u);
}

INLINE void ECC_RAM_DoubleBit_Int_Clr()
{
  Field_Wrt32(&SCU->EDCSCLR.reg, (uint8)SCU_EDCSCLR_RDBEC_Pos, SCU_EDCSCLR_RDBEC_Msk, 1u);
}

INLINE void ECC_NVM_DoubleBit_Int_Clr()
{
  Field_Wrt32(&SCU->EDCSCLR.reg, (uint8)SCU_EDCSCLR_NVMDBEC_Pos, SCU_EDCSCLR_NVMDBEC_Msk, 1u);
}

INLINE void EXINT0_Rising_Edge_Int_En()
{
  Field_Mod32(&SCU->EXICON0.reg, (uint8)SCU_EXICON0_EXINT0_RE_Pos, SCU_EXICON0_EXINT0_RE_Msk, 1u);
}

INLINE void EXINT0_Rising_Edge_Int_Dis()
{
  Field_Mod32(&SCU->EXICON0.reg, (uint8)SCU_EXICON0_EXINT0_RE_Pos, SCU_EXICON0_EXINT0_RE_Msk, 0u);
}

INLINE void EXINT0_Falling_Edge_Int_En()
{
  Field_Mod32(&SCU->EXICON0.reg, (uint8)SCU_EXICON0_EXINT0_FE_Pos, SCU_EXICON0_EXINT0_FE_Msk, 1u);
}

INLINE void EXINT0_Falling_Edge_Int_Dis()
{
  Field_Mod32(&SCU->EXICON0.reg, (uint8)SCU_EXICON0_EXINT0_FE_Pos, SCU_EXICON0_EXINT0_FE_Msk, 0u);
}

INLINE void EXINT1_Rising_Edge_Int_En()
{
  Field_Mod32(&SCU->EXICON0.reg, (uint8)SCU_EXICON0_EXINT1_RE_Pos, SCU_EXICON0_EXINT1_RE_Msk, 1u);
}

INLINE void EXINT1_Rising_Edge_Int_Dis()
{
  Field_Mod32(&SCU->EXICON0.reg, (uint8)SCU_EXICON0_EXINT1_RE_Pos, SCU_EXICON0_EXINT1_RE_Msk, 0u);
}

INLINE void EXINT1_Falling_Edge_Int_En()
{
  Field_Mod32(&SCU->EXICON0.reg, (uint8)SCU_EXICON0_EXINT1_FE_Pos, SCU_EXICON0_EXINT1_FE_Msk, 1u);
}

INLINE void EXINT1_Falling_Edge_Int_Dis()
{
  Field_Mod32(&SCU->EXICON0.reg, (uint8)SCU_EXICON0_EXINT1_FE_Pos, SCU_EXICON0_EXINT1_FE_Msk, 0u);
}

INLINE void EXINT2_Rising_Edge_Int_En()
{
  Field_Mod32(&SCU->EXICON0.reg, (uint8)SCU_EXICON0_EXINT2_RE_Pos, SCU_EXICON0_EXINT2_RE_Msk, 1u);
}

INLINE void EXINT2_Rising_Edge_Int_Dis()
{
  Field_Mod32(&SCU->EXICON0.reg, (uint8)SCU_EXICON0_EXINT2_RE_Pos, SCU_EXICON0_EXINT2_RE_Msk, 0u);
}

INLINE void EXINT2_Falling_Edge_Int_En()
{
  Field_Mod32(&SCU->EXICON0.reg, (uint8)SCU_EXICON0_EXINT2_FE_Pos, SCU_EXICON0_EXINT2_FE_Msk, 1u);
}

INLINE void EXINT2_Falling_Edge_Int_Dis()
{
  Field_Mod32(&SCU->EXICON0.reg, (uint8)SCU_EXICON0_EXINT2_FE_Pos, SCU_EXICON0_EXINT2_FE_Msk, 0u);
}

INLINE void EXINT0_Rising_Edge_Int_Clr()
{
  Field_Wrt32(&SCU->IRCON0CLR.reg, (uint8)SCU_IRCON0CLR_EXINT0RC_Pos, SCU_IRCON0CLR_EXINT0RC_Msk, 1u);
}

INLINE void EXINT0_Falling_Edge_Int_Clr()
{
  Field_Wrt32(&SCU->IRCON0CLR.reg, (uint8)SCU_IRCON0CLR_EXINT0FC_Pos, SCU_IRCON0CLR_EXINT0FC_Msk, 1u);
}

INLINE void EXINT1_Rising_Edge_Int_Clr()
{
  Field_Wrt32(&SCU->IRCON0CLR.reg, (uint8)SCU_IRCON0CLR_EXINT1RC_Pos, SCU_IRCON0CLR_EXINT1RC_Msk, 1u);
}

INLINE void EXINT1_Falling_Edge_Int_Clr()
{
  Field_Wrt32(&SCU->IRCON0CLR.reg, (uint8)SCU_IRCON0CLR_EXINT1FC_Pos, SCU_IRCON0CLR_EXINT1FC_Msk, 1u);
}

INLINE void EXINT2_Rising_Edge_Int_Clr()
{
  Field_Wrt32(&SCU->IRCON0CLR.reg, (uint8)SCU_IRCON0CLR_EXINT2RC_Pos, SCU_IRCON0CLR_EXINT2RC_Msk, 1u);
}

INLINE void EXINT2_Falling_Edge_Int_Clr()
{
  Field_Wrt32(&SCU->IRCON0CLR.reg, (uint8)SCU_IRCON0CLR_EXINT2FC_Pos, SCU_IRCON0CLR_EXINT2FC_Msk, 1u);
}

INLINE void NMI_WDT_Int_En()
{
  Field_Mod32(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIWDT_Pos, SCU_NMICON_NMIWDT_Msk, 1u);
}

INLINE void NMI_WDT_Int_Dis()
{
  Field_Mod32(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIWDT_Pos, SCU_NMICON_NMIWDT_Msk, 0u);
}

INLINE void NMI_PLL_Int_En()
{
  Field_Mod32(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIPLL_Pos, SCU_NMICON_NMIPLL_Msk, 1u);
}

INLINE void NMI_PLL_Int_Dis()
{
  Field_Mod32(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIPLL_Pos, SCU_NMICON_NMIPLL_Msk, 0u);
}

INLINE void NMI_ECC_Int_En()
{
  Field_Mod32(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIECC_Pos, SCU_NMICON_NMIECC_Msk, 1u);
}

INLINE void NMI_ECC_Int_Dis()
{
  Field_Mod32(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIECC_Pos, SCU_NMICON_NMIECC_Msk, 0u);
}

INLINE void NMI_MAP_Int_En()
{
  Field_Mod32(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIMAP_Pos, SCU_NMICON_NMIMAP_Msk, 1u);
}

INLINE void NMI_MAP_Int_Dis()
{
  Field_Mod32(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIMAP_Pos, SCU_NMICON_NMIMAP_Msk, 0u);
}

INLINE void NMI_SUP_Int_En()
{
  Field_Mod32(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMISUP_Pos, SCU_NMICON_NMISUP_Msk, 1u);
}

INLINE void NMI_SUP_Int_Dis()
{
  Field_Mod32(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMISUP_Pos, SCU_NMICON_NMISUP_Msk, 0u);
}

INLINE void NMI_OWD_Int_En()
{
  Field_Mod32(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIOWD_Pos, SCU_NMICON_NMIOWD_Msk, 1u);
}

INLINE void NMI_OWD_Int_Dis()
{
  Field_Mod32(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIOWD_Pos, SCU_NMICON_NMIOWD_Msk, 0u);
}

INLINE void NMI_OT_Int_En()
{
  Field_Mod32(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIOT_Pos, SCU_NMICON_NMIOT_Msk, 1u);
}

INLINE void NMI_OT_Int_Dis()
{
  Field_Mod32(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMIOT_Pos, SCU_NMICON_NMIOT_Msk, 0u);
}

INLINE void NMI_STOF_Int_En()
{
  Field_Mod32(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMISTOF_Pos, SCU_NMICON_NMISTOF_Msk, 1u);
}

INLINE void NMI_STOF_Int_Dis()
{
  Field_Mod32(&SCU->NMICON.reg, (uint8)SCU_NMICON_NMISTOF_Pos, SCU_NMICON_NMISTOF_Msk, 0u);
}

INLINE void NMI_WDT_Int_Clr()
{
  Field_Wrt32(&SCU->NMISRCLR.reg, (uint8)SCU_NMISRCLR_FNMIWDTC_Pos, SCU_NMISRCLR_FNMIWDTC_Msk, 1u);
}

INLINE void NMI_PLL_Int_Clr()
{
  Field_Wrt32(&SCU->NMISRCLR.reg, (uint8)SCU_NMISRCLR_FNMIPLLC_Pos, SCU_NMISRCLR_FNMIPLLC_Msk, 1u);
}

INLINE void NMI_OWD_Int_Clr()
{
  Field_Wrt32(&SCU->NMISRCLR.reg, (uint8)SCU_NMISRCLR_FNMIOWDC_Pos, SCU_NMISRCLR_FNMIOWDC_Msk, 1u);
}

INLINE void NMI_MAP_Int_Clr()
{
  Field_Wrt32(&SCU->NMISRCLR.reg, (uint8)SCU_NMISRCLR_FNMIMAPC_Pos, SCU_NMISRCLR_FNMIMAPC_Msk, 1u);
}

INLINE void NMI_STOF_En()
{
  Field_Wrt32(&SCU->STACK_OVF_CTRL.reg, (uint8)SCU_STACK_OVF_CTRL_STOF_EN_Pos, SCU_STACK_OVF_CTRL_STOF_EN_Msk, 1u);
}

INLINE void NMI_STOF_Dis()
{
  Field_Wrt32(&SCU->STACK_OVF_CTRL.reg, (uint8)SCU_STACK_OVF_CTRL_STOF_EN_Pos, SCU_STACK_OVF_CTRL_STOF_EN_Msk, 0u);
}

INLINE void NMI_STOF_Int_Clr()
{
  Field_Wrt32(&SCU->STACK_OVFCLR.reg, (uint8)SCU_STACK_OVFCLR_STOF_STSC_Pos, SCU_STACK_OVFCLR_STOF_STSC_Msk, 1u);
}

INLINE void Int_PORT2_Pend_Set()
{
  Field_Mod32(&CPU->NVIC_ISPR.reg, (uint8)CPU_NVIC_ISPR_Int_PORT2_Pos, CPU_NVIC_ISPR_Int_PORT2_Msk, 1u);
}

INLINE void Int_MON_Pend_Set()         
{
  Field_Mod32(&CPU->NVIC_ISPR.reg, (uint8)CPU_NVIC_ISPR_Int_MON_Pos, CPU_NVIC_ISPR_Int_MON_Msk, 1u);
}

INLINE void Int_DU_Pend_Set()          
{
  Field_Mod32(&CPU->NVIC_ISPR.reg, (uint8)CPU_NVIC_ISPR_Int_DU_Pos, CPU_NVIC_ISPR_Int_DU_Msk, 1u);
}

INLINE void Int_OPA_Pend_Set()
{
  Field_Mod32(&CPU->NVIC_ISPR.reg, (uint8)CPU_NVIC_ISPR_Int_OPA_Pos, CPU_NVIC_ISPR_Int_OPA_Msk, 1u);
}

INLINE void Int_HS_Pend_Set()
{
  Field_Mod32(&CPU->NVIC_ISPR.reg, (uint8)CPU_NVIC_ISPR_Int_HS_Pos, CPU_NVIC_ISPR_Int_HS_Msk, 1u);
}

INLINE void Int_BDRV_Pend_Set()
{
  Field_Mod32(&CPU->NVIC_ISPR.reg, (uint8)CPU_NVIC_ISPR_Int_BDRV_Pos, CPU_NVIC_ISPR_Int_BDRV_Msk, 1u);
}

INLINE void Int_CP_Pend_Set()
{
  Field_Mod32(&CPU->NVIC_ISPR.reg, (uint8)CPU_NVIC_ISPR_Int_CP_Pos, CPU_NVIC_ISPR_Int_CP_Msk, 1u);
}

INLINE void Int_MATHDIV_Pend_Set()
{
  Field_Mod32(&CPU->NVIC_ISPR.reg, (uint8)CPU_NVIC_ISPR_Int_MATHDIV_Pos, CPU_NVIC_ISPR_Int_MATHDIV_Msk, 1u);
}

INLINE void Int_WAKEUP_Pend_Set()
{
  Field_Mod32(&CPU->NVIC_ISPR.reg, (uint8)CPU_NVIC_ISPR_Int_WAKEUP_Pos, CPU_NVIC_ISPR_Int_WAKEUP_Msk, 1u);
}

INLINE void Int_EXINT1_Pend_Set()
{
  Field_Mod32(&CPU->NVIC_ISPR.reg, (uint8)CPU_NVIC_ISPR_Int_EXINT1_Pos, CPU_NVIC_ISPR_Int_EXINT1_Msk, 1u);
}

INLINE void Int_EXINT0_Pend_Set()
{
  Field_Mod32(&CPU->NVIC_ISPR.reg, (uint8)CPU_NVIC_ISPR_Int_EXINT0_Pos, CPU_NVIC_ISPR_Int_EXINT0_Msk, 1u);
}

INLINE void Int_UART2_Pend_Set()
{
  Field_Mod32(&CPU->NVIC_ISPR.reg, (uint8)CPU_NVIC_ISPR_Int_UART2_Pos, CPU_NVIC_ISPR_Int_UART2_Msk, 1u);
}

INLINE void Int_UART1_Pend_Set()
{
  Field_Mod32(&CPU->NVIC_ISPR.reg, (uint8)CPU_NVIC_ISPR_Int_UART1_Pos, CPU_NVIC_ISPR_Int_UART1_Msk, 1u);
}

INLINE void Int_SSC2_Pend_Set()
{
  Field_Mod32(&CPU->NVIC_ISPR.reg, (uint8)CPU_NVIC_ISPR_Int_SSC2_Pos, CPU_NVIC_ISPR_Int_SSC2_Msk, 1u);
}

INLINE void Int_SSC1_Pend_Set()
{
  Field_Mod32(&CPU->NVIC_ISPR.reg, (uint8)CPU_NVIC_ISPR_Int_SSC1_Pos, CPU_NVIC_ISPR_Int_SSC1_Msk, 1u);
}

INLINE void Int_CCU6SR3_Pend_Set()
{
  Field_Mod32(&CPU->NVIC_ISPR.reg, (uint8)CPU_NVIC_ISPR_Int_CCU6SR3_Pos, CPU_NVIC_ISPR_Int_CCU6SR3_Msk, 1u);
}

INLINE void Int_CCU6SR2_Pend_Set()
{
  Field_Mod32(&CPU->NVIC_ISPR.reg, (uint8)CPU_NVIC_ISPR_Int_CCU6SR2_Pos, CPU_NVIC_ISPR_Int_CCU6SR2_Msk, 1u);
}

INLINE void Int_CCU6SR1_Pend_Set()
{
  Field_Mod32(&CPU->NVIC_ISPR.reg, (uint8)CPU_NVIC_ISPR_Int_CCU6SR1_Pos, CPU_NVIC_ISPR_Int_CCU6SR1_Msk, 1u);
}

INLINE void Int_CCU6SR0_Pend_Set()
{
  Field_Mod32(&CPU->NVIC_ISPR.reg, (uint8)CPU_NVIC_ISPR_Int_CCU6SR0_Pos, CPU_NVIC_ISPR_Int_CCU6SR0_Msk, 1u);
}

INLINE void Int_ADC1_Pend_Set()
{
  Field_Mod32(&CPU->NVIC_ISPR.reg, (uint8)CPU_NVIC_ISPR_Int_ADC1_Pos, CPU_NVIC_ISPR_Int_ADC1_Msk, 1u);
}

INLINE void Int_ADC2_Pend_Set()
{
  Field_Mod32(&CPU->NVIC_ISPR.reg, (uint8)CPU_NVIC_ISPR_Int_ADC2_Pos, CPU_NVIC_ISPR_Int_ADC2_Msk, 1u);
}

INLINE void Int_GPT2_Pend_Set()
{
  Field_Mod32(&CPU->NVIC_ISPR.reg, (uint8)CPU_NVIC_ISPR_Int_GPT2_Pos, CPU_NVIC_ISPR_Int_GPT2_Msk, 1u);
}

INLINE void Int_GPT1_Pend_Set()
{
  Field_Mod32(&CPU->NVIC_ISPR.reg, (uint8)CPU_NVIC_ISPR_Int_GPT1_Pos, CPU_NVIC_ISPR_Int_GPT1_Msk, 1u);
}

INLINE void Int_PORT2_Pend_Clr()
{
  Field_Mod32(&CPU->NVIC_ICPR.reg, (uint8)CPU_NVIC_ICPR_Int_PORT2_Pos, CPU_NVIC_ICPR_Int_PORT2_Msk, 1u);
}

INLINE void Int_MON_Pend_Clr()         
{
  Field_Mod32(&CPU->NVIC_ICPR.reg, (uint8)CPU_NVIC_ICPR_Int_MON_Pos, CPU_NVIC_ICPR_Int_MON_Msk, 1u);
}

INLINE void Int_DU_Pend_Clr()          
{
  Field_Mod32(&CPU->NVIC_ICPR.reg, (uint8)CPU_NVIC_ICPR_Int_DU_Pos, CPU_NVIC_ICPR_Int_DU_Msk, 1u);
}

INLINE void Int_OPA_Pend_Clr()
{
  Field_Mod32(&CPU->NVIC_ICPR.reg, (uint8)CPU_NVIC_ICPR_Int_OPA_Pos, CPU_NVIC_ICPR_Int_OPA_Msk, 1u);
}

INLINE void Int_HS_Pend_Clr()
{
  Field_Mod32(&CPU->NVIC_ICPR.reg, (uint8)CPU_NVIC_ICPR_Int_HS_Pos, CPU_NVIC_ICPR_Int_HS_Msk, 1u);
}

INLINE void Int_BDRV_Pend_Clr()
{
  Field_Mod32(&CPU->NVIC_ICPR.reg, (uint8)CPU_NVIC_ICPR_Int_BDRV_Pos, CPU_NVIC_ICPR_Int_BDRV_Msk, 1u);
}

INLINE void Int_CP_Pend_Clr()
{
  Field_Mod32(&CPU->NVIC_ICPR.reg, (uint8)CPU_NVIC_ICPR_Int_CP_Pos, CPU_NVIC_ICPR_Int_CP_Msk, 1u);
}

INLINE void Int_MATHDIV_Pend_Clr()
{
  Field_Mod32(&CPU->NVIC_ICPR.reg, (uint8)CPU_NVIC_ICPR_Int_MATHDIV_Pos, CPU_NVIC_ICPR_Int_MATHDIV_Msk, 1u);
}

INLINE void Int_WAKEUP_Pend_Clr()
{
  Field_Mod32(&CPU->NVIC_ICPR.reg, (uint8)CPU_NVIC_ICPR_Int_WAKEUP_Pos, CPU_NVIC_ICPR_Int_WAKEUP_Msk, 1u);
}

INLINE void Int_EXINT1_Pend_Clr()
{
  Field_Mod32(&CPU->NVIC_ICPR.reg, (uint8)CPU_NVIC_ICPR_Int_EXINT1_Pos, CPU_NVIC_ICPR_Int_EXINT1_Msk, 1u);
}

INLINE void Int_EXINT0_Pend_Clr()
{
  Field_Mod32(&CPU->NVIC_ICPR.reg, (uint8)CPU_NVIC_ICPR_Int_EXINT0_Pos, CPU_NVIC_ICPR_Int_EXINT0_Msk, 1u);
}

INLINE void Int_UART2_Pend_Clr()
{
  Field_Mod32(&CPU->NVIC_ICPR.reg, (uint8)CPU_NVIC_ICPR_Int_UART2_Pos, CPU_NVIC_ICPR_Int_UART2_Msk, 1u);
}

INLINE void Int_UART1_Pend_Clr()
{
  Field_Mod32(&CPU->NVIC_ICPR.reg, (uint8)CPU_NVIC_ICPR_Int_UART1_Pos, CPU_NVIC_ICPR_Int_UART1_Msk, 1u);
}

INLINE void Int_SSC2_Pend_Clr()
{
  Field_Mod32(&CPU->NVIC_ICPR.reg, (uint8)CPU_NVIC_ICPR_Int_SSC2_Pos, CPU_NVIC_ICPR_Int_SSC2_Msk, 1u);
}

INLINE void Int_SSC1_Pend_Clr()
{
  Field_Mod32(&CPU->NVIC_ICPR.reg, (uint8)CPU_NVIC_ICPR_Int_SSC1_Pos, CPU_NVIC_ICPR_Int_SSC1_Msk, 1u);
}

INLINE void Int_CCU6SR3_Pend_Clr()
{
  Field_Mod32(&CPU->NVIC_ICPR.reg, (uint8)CPU_NVIC_ICPR_Int_CCU6SR3_Pos, CPU_NVIC_ICPR_Int_CCU6SR3_Msk, 1u);
}

INLINE void Int_CCU6SR2_Pend_Clr()
{
  Field_Mod32(&CPU->NVIC_ICPR.reg, (uint8)CPU_NVIC_ICPR_Int_CCU6SR2_Pos, CPU_NVIC_ICPR_Int_CCU6SR2_Msk, 1u);
}

INLINE void Int_CCU6SR1_Pend_Clr()
{
  Field_Mod32(&CPU->NVIC_ICPR.reg, (uint8)CPU_NVIC_ICPR_Int_CCU6SR1_Pos, CPU_NVIC_ICPR_Int_CCU6SR1_Msk, 1u);
}

INLINE void Int_CCU6SR0_Pend_Clr()
{
  Field_Mod32(&CPU->NVIC_ICPR.reg, (uint8)CPU_NVIC_ICPR_Int_CCU6SR0_Pos, CPU_NVIC_ICPR_Int_CCU6SR0_Msk, 1u);
}

INLINE void Int_ADC1_Pend_Clr()
{
  Field_Mod32(&CPU->NVIC_ICPR.reg, (uint8)CPU_NVIC_ICPR_Int_ADC1_Pos, CPU_NVIC_ICPR_Int_ADC1_Msk, 1u);
}

INLINE void Int_ADC2_Pend_Clr()
{
  Field_Mod32(&CPU->NVIC_ICPR.reg, (uint8)CPU_NVIC_ICPR_Int_ADC2_Pos, CPU_NVIC_ICPR_Int_ADC2_Msk, 1u);
}

INLINE void Int_GPT2_Pend_Clr()
{
  Field_Mod32(&CPU->NVIC_ICPR.reg, (uint8)CPU_NVIC_ICPR_Int_GPT2_Pos, CPU_NVIC_ICPR_Int_GPT2_Msk, 1u);
}

INLINE void Int_GPT1_Pend_Clr()
{
  Field_Mod32(&CPU->NVIC_ICPR.reg, (uint8)CPU_NVIC_ICPR_Int_GPT1_Pos, CPU_NVIC_ICPR_Int_GPT1_Msk, 1u);
}

INLINE void NMI_Pend_Set()
{
  Field_Mod32(&CPU->ICSR.reg, (uint8)CPU_ICSR_NMIPENDSET_Pos, CPU_ICSR_NMIPENDSET_Msk, 1u);
}

INLINE void PENDSV_Pend_Set()
{
  Field_Mod32(&CPU->ICSR.reg, (uint8)CPU_ICSR_PENDSVSET_Pos, CPU_ICSR_PENDSVSET_Msk, 1u);
}

INLINE void PENDSV_Pend_Clr()
{
  Field_Mod32(&CPU->ICSR.reg, (uint8)CPU_ICSR_PENDSVCLR_Pos, CPU_ICSR_PENDSVCLR_Msk, 1u);
}

INLINE void SysTick_Pend_Set()
{
  Field_Mod32(&CPU->ICSR.reg, (uint8)CPU_ICSR_PENDSTSET_Pos, CPU_ICSR_PENDSTSET_Msk, 1u);
}

INLINE void SysTick_Pend_Clr()
{
  Field_Mod32(&CPU->ICSR.reg, (uint8)CPU_ICSR_PENDSTCLR_Pos, CPU_ICSR_PENDSTCLR_Msk, 1u);
}

INLINE uint16 INT_Get_NMI_Status(void)
{
  return(u16_Field_Rd32(&SCU->NMISR.reg, (uint8)SCU_NMISR_FNMIWDT_Pos, SCU_NMISR_Msk));  
}

INLINE void INT_Clr_NMI_Status(uint8 Flags)
{
  Field_Wrt32(&SCU->NMISRCLR.reg, (uint8)SCU_NMISRCLR_FNMIWDTC_Pos, SCU_NMICLR_Msk, Flags);  
}

INLINE void INT_Enable_Global_Int(void)
{
  Global_Int_En();
}

INLINE void INT_Disable_Global_Int(void)
{
  Global_Int_Dis();
}

#endif
