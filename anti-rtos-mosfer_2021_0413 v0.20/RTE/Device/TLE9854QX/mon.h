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
 * \file     mon.h
 *
 * \brief    High Voltage Monitor Input low level access library
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
** BG           Blandine Guillot                                              **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V0.2.0: 2018-02-13, TS:   Initial version of revision history              **
** V0.2.2: 2019-01-28, TS:   __STATIC_INLINE changed to INLINE                **
**                           Doxygen update                                   **
**                           Revision history moved from mon.c to mon.h       **
**                           EXINT MONx Pos and Mask macros added             **
** V0.2.3: 2020-03-02, BG:   Updated revision history format                  **
*******************************************************************************/
 
#ifndef MON_H
#define MON_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle985x.h"
#include "types.h"
#include "sfr_access.h"

/*******************************************************************************
**                          Global Macro Definitions                          **
*******************************************************************************/
/**\brief MONx Status Flag mask, MON1 LOW STATUS*/
#define MON1_STATUS_LOW  (0U)
/**\brief MONx Status Flag mask, MON1 HIGH STATUS*/
#define MON1_STATUS_HIGH (1U)
/**\brief MONx Status Flag mask, MON2 LOW STATUS*/
#define MON2_STATUS_LOW  (0U)
/**\brief MONx Status Flag mask, MON2 HIGH STATUS*/
#define MON2_STATUS_HIGH (1U)
/**\brief MONx Status Flag mask, MON3 LOW STATUS*/
#define MON3_STATUS_LOW  (0U)
/**\brief MONx Status Flag mask, MON3 HIGH STATUS*/
#define MON3_STATUS_HIGH (1U)
/**\brief MONx Status Flag mask, MON4 LOW STATUS*/
#define MON4_STATUS_LOW  (0U)
/**\brief MONx Status Flag mask, MON4 HIGH STATUS*/
#define MON4_STATUS_HIGH (1U)

/**\brief External Interrupt MON1 Rising Edge Bit Position*/
#define SCU_EXICON1_MON1_RE_Pos (0UL)
/**\brief External Interrupt MON1 Rising Edge Bit Mask*/
#define SCU_EXICON1_MON1_RE_Msk (0x01UL)
/**\brief External Interrupt MON1 Falling Edge Bit Position*/
#define SCU_EXICON1_MON1_FE_Pos (1UL)
/**\brief External Interrupt MON1 Falling Edge Bit Mask*/
#define SCU_EXICON1_MON1_FE_Msk (0x02UL)
/**\brief External Interrupt MON2 Rising Edge Bit Position*/
#define SCU_EXICON1_MON2_RE_Pos (2UL)
/**\brief External Interrupt MON2 Rising Edge Bit Mask*/
#define SCU_EXICON1_MON2_RE_Msk (0x04UL)
/**\brief External Interrupt MON2 Falling Edge Bit Position*/
#define SCU_EXICON1_MON2_FE_Pos (3UL)
/**\brief External Interrupt MON2 Falling Edge Bit Mask*/
#define SCU_EXICON1_MON2_FE_Msk (0x08UL)
/**\brief External Interrupt MON3 Rising Edge Bit Position*/
#define SCU_EXICON1_MON3_RE_Pos (4UL)
/**\brief External Interrupt MON3 Rising Edge Bit Mask*/
#define SCU_EXICON1_MON3_RE_Msk (0x10UL)
/**\brief External Interrupt MON3 Falling Edge Bit Position*/
#define SCU_EXICON1_MON3_FE_Pos (5UL)
/**\brief External Interrupt MON3 Falling Edge Bit Mask*/
#define SCU_EXICON1_MON3_FE_Msk (0x20UL)
/**\brief External Interrupt MON4 Rising Edge Bit Position*/
#define SCU_EXICON1_MON4_RE_Pos (6UL)
/**\brief External Interrupt MON4 Rising Edge Bit Mask*/
#define SCU_EXICON1_MON4_RE_Msk (0x40UL)
/**\brief External Interrupt MON4 Falling Edge Bit Position*/
#define SCU_EXICON1_MON4_FE_Pos (7UL)
/**\brief External Interrupt MON4 Falling Edge Bit Mask*/
#define SCU_EXICON1_MON4_FE_Msk (0x80UL)

/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/
/** \brief Initializes the MONx module.
 *
 * \ingroup mon_api
 */
void MONx_Init(void);

/** \brief Reads out the MONx Status
 *
 * \param Monx MONx status flag
 *
 * \brief <b>Example</b><br>
 * \brief This example reads MON4 Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 status;
 *
 *     MON4_En();
 *     status = MONx_Get_Status(4u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
uint8 MONx_Get_Status(uint8 Monx);

/** \brief Debounces the MONx input and reads the logical input value
 *
 * \param Monx MONx status flag
 * \param MonActiveState Expected active state of the MONx input
 *
 * \result Active State after debouncing MONx
 *
 * \brief <b>Example</b><br>
 * \brief This example Debounces the MON2 input to Low Level and reads the logical input value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 stat;
 *
 *     MON2_En();
 *     stat = MONx_Debounce(2u,0u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
uint8 MONx_Debounce(uint8 Monx,uint8 MonActiveState);

/*******************************************************************************
**                        Inline Function Declarations                        **
*******************************************************************************/
/** \brief Clears MON1 on rising edge interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON1 on rising edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON1_Int_En();  
 *   MON1_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON1R == (uint8)1)
 *   {
 *     MON1_RISING_CALLBACK();
 *     MON1_Rising_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON1_Rising_Edge_Int_Clr(void);

/** \brief Clears MON1 on falling edge interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON1 on falling edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON1_Int_En();  
 *   MON1_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON1F == (uint8)1)
 *   {
 *     MON1_FALLING_CALLBACK();
 *     MON1_Falling_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON1_Falling_Edge_Int_Clr(void);

/** \brief Clears MON2 on rising edge interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON2 on rising edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON2_Int_En();  
 *   MON2_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON2R == (uint8)1)
 *   {
 *     MON2_RISING_CALLBACK();
 *     MON2_Rising_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON2_Rising_Edge_Int_Clr(void);

/** \brief Clears MON2 on falling edge interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON2 on falling edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON2_Int_En();  
 *   MON2_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON2F == (uint8)1)
 *   {
 *     MON2_FALLING_CALLBACK();
 *     MON2_Falling_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON2_Falling_Edge_Int_Clr(void);

/** \brief Clears MON3 on rising edge interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON3 on rising edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON3_Int_En();  
 *   MON3_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON3R == (uint8)1)
 *   {
 *     MON3_RISING_CALLBACK();
 *     MON3_Rising_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON3_Rising_Edge_Int_Clr(void);

/** \brief Clears MON3 on falling edge interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON3 on falling edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON3_Int_En();  
 *   MON3_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON3F == (uint8)1)
 *   {
 *     MON3_FALLING_CALLBACK();
 *     MON3_Falling_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON3_Falling_Edge_Int_Clr(void);

/** \brief Clears MON4 on rising edge interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON4 on rising edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON4_Int_En();  
 *   MON4_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON4R == (uint8)1)
 *   {
 *     MON4_RISING_CALLBACK();
 *     MON4_Rising_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON4_Rising_Edge_Int_Clr(void);

/** \brief Clears MON4 on falling edge interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON4 on falling edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON4_Int_En();  
 *   MON4_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON4F == (uint8)1)
 *   {
 *     MON4_FALLING_CALLBACK();
 *     MON4_Falling_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON4_Falling_Edge_Int_Clr(void);

/** \brief Enables MON1 on rising edge interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON1 on rising edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON1_Int_En();  
 *   MON1_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON1R == (uint8)1)
 *   {
 *     MON1_RISING_CALLBACK();
 *     MON1_Rising_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON1_Rising_Edge_Int_En(void);

/** \brief Disables MON1 on rising edge interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON1 on rising edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON1_Int_En();  
 *   MON1_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON1R == (uint8)1)
 *   {
 *     MON1_RISING_CALLBACK();
 *     MON1_Rising_Edge_Int_Clr();
 *   }
 *   MON1_Rising_Edge_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON1_Rising_Edge_Int_Dis(void);

/** \brief Enables MON1 on falling edge interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON1 on falling edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON1_Int_En();  
 *   MON1_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON1F == (uint8)1)
 *   {
 *     MON1_FALLING_CALLBACK();
 *     MON1_Falling_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON1_Falling_Edge_Int_En(void);

/** \brief Disables MON1 on falling edge interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON1 on falling edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON1_Int_En();  
 *   MON1_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON1F == (uint8)1)
 *   {
 *     MON1_FALLING_CALLBACK();
 *     MON1_Falling_Edge_Int_Clr();
 *   }
 *   MON1_Falling_Edge_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON1_Falling_Edge_Int_Dis(void);

/** \brief Enables MON2 on rising edge interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON2 on rising edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON2_Int_En();  
 *   MON2_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON2R == (uint8)1)
 *   {
 *     MON2_RISING_CALLBACK();
 *     MON2_Rising_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON2_Rising_Edge_Int_En(void);

/** \brief Disables MON2 on rising edge interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON2 on rising edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON2_Int_En();    
 *   MON2_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON2R == (uint8)1)
 *   {
 *     MON2_RISING_CALLBACK();
 *     MON2_Rising_Edge_Int_Clr();
 *   }
 *   MON2_Rising_Edge_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON2_Rising_Edge_Int_Dis(void);

/** \brief Enables MON2 on falling edge interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON2 on falling edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON2_Int_En();    
 *   MON2_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON2F == (uint8)1)
 *   {
 *     MON2_FALLING_CALLBACK();
 *     MON2_Falling_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON2_Falling_Edge_Int_En(void);

/** \brief Disables MON2 on falling edge interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON2 on falling edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON2_Int_En();    
 *   MON2_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON2F == (uint8)1)
 *   {
 *     MON2_FALLING_CALLBACK();
 *     MON2_Falling_Edge_Int_Clr();
 *   }
 *   MON2_Falling_Edge_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON2_Falling_Edge_Int_Dis(void);

/** \brief Enables MON3 on rising edge interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON3 on rising edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON3_Int_En();      
 *   MON3_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON3R == (uint8)1)
 *   {
 *     MON3_RISING_CALLBACK();
 *     MON3_Rising_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON3_Rising_Edge_Int_En(void);

/** \brief Disables MON3 on rising edge interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON3 on rising edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON3_Int_En();    
 *   MON3_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON3R == (uint8)1)
 *   {
 *     MON3_RISING_CALLBACK();
 *     MON3_Rising_Edge_Int_Clr();
 *   }
 *   MON3_Rising_Edge_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON3_Rising_Edge_Int_Dis(void);

/** \brief Enables MON3 on falling edge interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON3 on falling edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON3_Int_En();  
 *   MON3_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON3F == (uint8)1)
 *   {
 *     MON3_FALLING_CALLBACK();
 *     MON3_Falling_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON3_Falling_Edge_Int_En(void);

/** \brief Disables MON3 on falling edge interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON3 on falling edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON3_Int_En();  
 *   MON3_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON3F == (uint8)1)
 *   {
 *     MON3_FALLING_CALLBACK();
 *     MON3_Falling_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON3_Falling_Edge_Int_Dis(void);

/** \brief Enables MON4 on rising edge interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON4 on rising edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON4_Int_En();  
 *   MON4_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON4R == (uint8)1)
 *   {
 *     MON4_RISING_CALLBACK();
 *     MON4_Rising_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON4_Rising_Edge_Int_En(void);

/** \brief Disables MON4 on rising edge interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON4 on rising edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON4_Int_En();     
 *   MON4_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON4R == (uint8)1)
 *   {
 *     MON4_RISING_CALLBACK();
 *     MON4_Rising_Edge_Int_Clr();
 *   }
 *   MON4_Rising_Edge_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON4_Rising_Edge_Int_Dis(void);

/** \brief Enables MON4 on falling edge interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON4 on falling edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON4_Int_En();     
 *   MON4_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON4F == (uint8)1)
 *   {
 *     MON4_FALLING_CALLBACK();
 *     MON4_Falling_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON4_Falling_Edge_Int_En(void);

/** \brief Disables MON4 on falling edge interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON4 on falling edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON4_Int_En();     
 *   MON4_Falling_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON4F == (uint8)1)
 *   {
 *     MON4_FALLING_CALLBACK();
 *     MON4_Falling_Edge_Int_Clr();
 *   }
 *   MON4_Falling_Edge_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON4_Falling_Edge_Int_Dis(void);

/** \brief Reads MON1 Status.
 *
 * \return MON1 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example reads MON1 Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 status;
 *
 *     status = MON1_Sts();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE uint8 MON1_Sts(void);

/** \brief Enables PullUp for MON1.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUp for MON1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON1_En();  
 *     MON1_PullUp_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON1_PullUp_En(void);

/** \brief Disables PullUp for MON1.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUp for MON1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON1_En();  
 *     MON1_PullUp_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON1_PullUp_Dis(void);

/** \brief Enables PullDown for MON1.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullDown for MON1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON1_En();  
 *     MON1_PullDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON1_PullDown_En(void);

/** \brief Disables PullDown for MON1.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullDown for MON1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON1_En();  
 *     MON1_PullDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON1_PullDown_Dis(void);

/** \brief Enables Cycle Sense for MON1.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Cycle Sense for MON1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON1_En();  
 *     MON1_CycSense_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON1_CycSense_En(void);

/** \brief Disables Cycle Sense for MON1.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Cycle Sense for MON1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON1_En();  
 *     MON1_CycSense_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON1_CycSense_Dis(void);

/** \brief Enables Wake-up on Rising Edge for MON1.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Wake-up on Rising Edge for MON1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON1_En();  
 *     MON1_WakeOnRise_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON1_WakeOnRise_En(void);

/** \brief Disables Wake-up on Rising Edge for MON1.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Wake-up on Rising Edge for MON1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON1_En();  
 *     MON1_WakeOnRise_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON1_WakeOnRise_Dis(void);

/** \brief Enables Wake-up on Falling Edge for MON1.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Wake-up on Falling Edge for MON1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON1_En();  
 *     MON1_WakeOnFall_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON1_WakeOnFall_En(void);

/** \brief Disables Wake-up on Falling Edge for MON1.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Wake-up on Falling Edge for MON1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON1_En();  
 *     MON1_WakeOnFall_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON1_WakeOnFall_Dis(void);

/** \brief Enables MON1.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Wake-up on Falling Edge for MON1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON1_En();  
 *     MON1_WakeOnFall_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON1_En(void);

/** \brief Disables MON1.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables MON1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON1_Dis();  
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON1_Dis(void);

/** \brief Reads MON2 Status.
 *
 * \return MON2 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example reads MON2 Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 status;
 *
 *     status = MON2_Sts();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE uint8 MON2_Sts(void);

/** \brief Enables PullUp for MON2.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUp for MON2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON2_En();  
 *     MON2_PullUp_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON2_PullUp_En(void);

/** \brief Disables PullUp for MON2.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUp for MON2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON2_En();  
 *     MON2_PullUp_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON2_PullUp_Dis(void);

/** \brief Enables PullDown for MON2.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullDown for MON2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON2_En();  
 *     MON2_PullDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON2_PullDown_En(void);

/** \brief Disables PullDown for MON2.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullDown for MON2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON2_En();  
 *     MON2_PullDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON2_PullDown_Dis(void);

/** \brief Enables Cycle Sense for MON2.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Cycle Sense for MON2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON2_En();  
 *     MON2_CycSense_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON2_CycSense_En(void);

/** \brief Disables Cycle Sense for MON2.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Cycle Sense for MON2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON2_En();  
 *     MON2_CycSense_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON2_CycSense_Dis(void);

/** \brief Enables Wake-up on Rising Edge for MON2.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Wake-up on Rising Edge for MON2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON2_En();  
 *     MON2_WakeOnRise_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON2_WakeOnRise_En(void);

/** \brief Disables Wake-up on Rising Edge for MON2.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Wake-up on Rising Edge for MON2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON2_En();  
 *     MON2_WakeOnRise_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON2_WakeOnRise_Dis(void);

/** \brief Enables Wake-up on Falling Edge for MON2.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Wake-up on Falling Edge for MON2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON2_En();  
 *     MON2_WakeOnFall_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON2_WakeOnFall_En(void);

/** \brief Disables Wake-up on Falling Edge for MON2.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Wake-up on Falling Edge for MON2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON2_En();  
 *     MON2_WakeOnFall_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON2_WakeOnFall_Dis(void);

/** \brief Enables MON2.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUp for MON2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON2_En();  
 *     MON2_PullUp_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON2_En(void);

/** \brief Disables MON2.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables MON2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON2_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON2_Dis(void);

/** \brief Reads MON3 Status.
 *
 * \return MON3 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example reads MON3 Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 status;
 *
 *     status = MON3_Sts();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE uint8 MON3_Sts(void);

/** \brief Enables PullUp for MON3.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUp for MON3.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON3_En();  
 *     MON3_PullUp_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON3_PullUp_En(void);

/** \brief Disables PullUp for MON3.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUp for MON3.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON3_En();  
 *     MON3_PullUp_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON3_PullUp_Dis(void);

/** \brief Enables PullDown for MON3.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullDown for MON3.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON3_En();  
 *     MON3_PullDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON3_PullDown_En(void);

/** \brief Disables PullDown for MON3.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullDown for MON3.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON3_En();  
 *     MON3_PullDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON3_PullDown_Dis(void);

/** \brief Enables Cycle Sense for MON3.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Cycle Sense for MON3.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON3_En();  
 *     MON3_CycSense_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON3_CycSense_En(void);

/** \brief Disables Cycle Sense for MON3.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Cycle Sense for MON3.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON3_En();  
 *     MON3_CycSense_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON3_CycSense_Dis(void);

/** \brief Enables Wake-up on Rising Edge for MON3.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Wake-up on Rising Edge for MON3.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON3_En();  
 *     MON3_WakeOnRise_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON3_WakeOnRise_En(void);

/** \brief Disables Wake-up on Rising Edge for MON3.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Wake-up on Rising Edge for MON3.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON3_En();  
 *     MON3_WakeOnRise_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON3_WakeOnRise_Dis(void);

/** \brief Enables Wake-up on Falling Edge for MON3.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Wake-up on Falling Edge for MON3.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON3_En();  
 *     MON3_WakeOnFall_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON3_WakeOnFall_En(void);

/** \brief Disables Wake-up on Falling Edge for MON3.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Wake-up on Falling Edge for MON3.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON3_En();  
 *     MON3_WakeOnFall_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON3_WakeOnFall_Dis(void);

/** \brief Enables MON3.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Cycle Sense for MON3.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON3_En();  
 *     MON3_CycSense_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON3_En(void);

/** \brief Disables MON3.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables MON3.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON3_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON3_Dis(void);

/** \brief Reads MON4 Status.
 *
 * \return MON4 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example reads MON4 Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 status;
 *
 *     status = MON4_Sts();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE uint8 MON4_Sts(void);

/** \brief Enables PullUp for MON4.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUp for MON4.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON4_En();  
 *     MON4_PullUp_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON4_PullUp_En(void);

/** \brief Disables PullUp for MON4.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUp for MON4.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON4_En();  
 *     MON4_PullUp_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON4_PullUp_Dis(void);

/** \brief Enables PullDown for MON4.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullDown for MON4.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON4_En();  
 *     MON4_PullDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON4_PullDown_En(void);

/** \brief Disables PullDown for MON4.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullDown for MON4.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON4_En();  
 *     MON4_PullDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON4_PullDown_Dis(void);

/** \brief Enables Cycle Sense for MON4.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Cycle Sense for MON4.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON4_En();  
 *     MON4_CycSense_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON4_CycSense_En(void);

/** \brief Disables Cycle Sense for MON4.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Cycle Sense for MON4.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON4_En();  
 *     MON4_CycSense_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON4_CycSense_Dis(void);

/** \brief Enables Wake-up on Rising Edge for MON4.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Wake-up on Rising Edge for MON4.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON4_En();  
 *     MON4_WakeOnRise_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON4_WakeOnRise_En(void);

/** \brief Disables Wake-up on Rising Edge for MON4.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Wake-up on Rising Edge for MON4.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON4_En();  
 *     MON4_WakeOnRise_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON4_WakeOnRise_Dis(void);

/** \brief Enables Wake-up on Falling Edge for MON4.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Wake-up on Falling Edge for MON4.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON4_En();  
 *     MON4_WakeOnFall_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON4_WakeOnFall_En(void);

/** \brief Disables Wake-up on Falling Edge for MON4.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Wake-up on Falling Edge for MON4.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON4_En();  
 *     MON4_WakeOnFall_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON4_WakeOnFall_Dis(void);

/** \brief Enables MON4.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullDown for MON4.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON4_En();  
 *     MON4_PullDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON4_En(void);

/** \brief Disables MON4.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables MON4.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MON4_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON4_Dis(void);

/** \brief Enables MON1 interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON1 on rising edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON1_Int_En();   
 *   MON1_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON1R == (uint8)1)
 *   {
 *     MON1_RISING_CALLBACK();
 *     MON1_Rising_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON1_Int_En(void);

/** \brief Enables MON2 interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON2 on rising edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON2_Int_En();  
 *   MON2_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON2R == (uint8)1)
 *   {
 *     MON2_RISING_CALLBACK();
 *     MON2_Rising_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON2_Int_En(void);

/** \brief Enables MON3 interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON3 on rising edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON3_Int_En();   
 *   MON3_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON3R == (uint8)1)
 *   {
 *     MON3_RISING_CALLBACK();
 *     MON3_Rising_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON3_Int_En(void);

/** \brief Enables MON4 interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON4 on rising edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON4_Int_En();   
 *   MON4_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON4R == (uint8)1)
 *   {
 *     MON4_RISING_CALLBACK();
 *     MON4_Rising_Edge_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON4_Int_En(void);

/** \brief Disables MON1 interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON1 on rising edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON1_Int_En();   
 *   MON1_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON1R == (uint8)1)
 *   {
 *     MON1_RISING_CALLBACK();
 *     MON1_Rising_Edge_Int_Clr();
 *   }
 *   MON1_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON1_Int_Dis(void);

/** \brief Disables MON2 interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON2 on rising edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON2_Int_En();  
 *   MON2_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON2R == (uint8)1)
 *   {
 *     MON2_RISING_CALLBACK();
 *     MON2_Rising_Edge_Int_Clr();
 *   }
 *   MON2_Int_Dis();  
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON2_Int_Dis(void);

/** \brief Disables MON3 interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON3 on rising edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON3_Int_En();   
 *   MON3_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON3R == (uint8)1)
 *   {
 *     MON3_RISING_CALLBACK();
 *     MON3_Rising_Edge_Int_Clr();
 *   }
 *   MON3_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON3_Int_Dis(void);

/** \brief Disables MON4 interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the MON4 on rising edge interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   MON4_Int_En();   
 *   MON4_Rising_Edge_Int_En();
 *   if ((uint8)SCU->IRCON1.bit.MON4R == (uint8)1)
 *   {
 *     MON4_RISING_CALLBACK();
 *     MON4_Rising_Edge_Int_Clr();
 *   }
 *   MON4_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup mon_api
 */
INLINE void MON4_Int_Dis(void);

/*******************************************************************************
**                         Inline Function Definitions                        **
*******************************************************************************/
INLINE void MON1_Rising_Edge_Int_Clr()
{
  Field_Wrt32(&SCU->IRCON1CLR.reg, (uint8)SCU_IRCON1CLR_MON1RC_Pos, SCU_IRCON1CLR_MON1RC_Msk, 1u);
}

INLINE void MON1_Falling_Edge_Int_Clr()
{
  Field_Wrt32(&SCU->IRCON1CLR.reg, (uint8)SCU_IRCON1CLR_MON1FC_Pos, SCU_IRCON1CLR_MON1FC_Msk, 1u);
}

INLINE void MON2_Rising_Edge_Int_Clr()
{
  Field_Wrt32(&SCU->IRCON1CLR.reg, (uint8)SCU_IRCON1CLR_MON2RC_Pos, SCU_IRCON1CLR_MON2RC_Msk, 1u);
}

INLINE void MON2_Falling_Edge_Int_Clr()
{
  Field_Wrt32(&SCU->IRCON1CLR.reg, (uint8)SCU_IRCON1CLR_MON2FC_Pos, SCU_IRCON1CLR_MON2FC_Msk, 1u);
}

INLINE void MON3_Rising_Edge_Int_Clr()
{
  Field_Wrt32(&SCU->IRCON1CLR.reg, (uint8)SCU_IRCON1CLR_MON3RC_Pos, SCU_IRCON1CLR_MON3RC_Msk, 1u);
}

INLINE void MON3_Falling_Edge_Int_Clr()
{
  Field_Wrt32(&SCU->IRCON1CLR.reg, (uint8)SCU_IRCON1CLR_MON3FC_Pos, SCU_IRCON1CLR_MON3FC_Msk, 1u);
}

INLINE void MON4_Rising_Edge_Int_Clr()
{
  Field_Wrt32(&SCU->IRCON1CLR.reg, (uint8)SCU_IRCON1CLR_MON4RC_Pos, SCU_IRCON1CLR_MON4RC_Msk, 1u);
}

INLINE void MON4_Falling_Edge_Int_Clr()
{
  Field_Wrt32(&SCU->IRCON1CLR.reg, (uint8)SCU_IRCON1CLR_MON4FC_Pos, SCU_IRCON1CLR_MON4FC_Msk, 1u);
}

INLINE void MON1_Rising_Edge_Int_En()
{
  Field_Mod32(&SCU->EXICON1.reg, (uint8)SCU_EXICON1_MON1_RE_Pos, SCU_EXICON1_MON1_RE_Msk, 1u);
}

INLINE void MON1_Rising_Edge_Int_Dis()
{
  Field_Mod32(&SCU->EXICON1.reg, (uint8)SCU_EXICON1_MON1_RE_Pos, SCU_EXICON1_MON1_RE_Msk, 0u);
}

INLINE void MON1_Falling_Edge_Int_En()
{
  Field_Mod32(&SCU->EXICON1.reg, (uint8)SCU_EXICON1_MON1_FE_Pos, SCU_EXICON1_MON1_FE_Msk, 1u);
}

INLINE void MON1_Falling_Edge_Int_Dis()
{
  Field_Mod32(&SCU->EXICON1.reg, (uint8)SCU_EXICON1_MON1_FE_Pos, SCU_EXICON1_MON1_FE_Msk, 0u);
}

INLINE void MON2_Rising_Edge_Int_En()
{
  Field_Mod32(&SCU->EXICON1.reg, (uint8)SCU_EXICON1_MON2_RE_Pos, SCU_EXICON1_MON2_RE_Msk, 1u);
}

INLINE void MON2_Rising_Edge_Int_Dis()
{
  Field_Mod32(&SCU->EXICON1.reg, (uint8)SCU_EXICON1_MON2_RE_Pos, SCU_EXICON1_MON2_RE_Msk, 0u);
}

INLINE void MON2_Falling_Edge_Int_En()
{
  Field_Mod32(&SCU->EXICON1.reg, (uint8)SCU_EXICON1_MON2_FE_Pos, SCU_EXICON1_MON2_FE_Msk, 1u);
}

INLINE void MON2_Falling_Edge_Int_Dis()
{
  Field_Mod32(&SCU->EXICON1.reg, (uint8)SCU_EXICON1_MON2_FE_Pos, SCU_EXICON1_MON2_FE_Msk, 0u);
}

INLINE void MON3_Rising_Edge_Int_En()
{
  Field_Mod32(&SCU->EXICON1.reg, (uint8)SCU_EXICON1_MON3_RE_Pos, SCU_EXICON1_MON3_RE_Msk, 1u);
}

INLINE void MON3_Rising_Edge_Int_Dis()
{
  Field_Mod32(&SCU->EXICON1.reg, (uint8)SCU_EXICON1_MON3_RE_Pos, SCU_EXICON1_MON3_RE_Msk, 0u);
}

INLINE void MON3_Falling_Edge_Int_En()
{
  Field_Mod32(&SCU->EXICON1.reg, (uint8)SCU_EXICON1_MON3_FE_Pos, SCU_EXICON1_MON3_FE_Msk, 1u);
}

INLINE void MON3_Falling_Edge_Int_Dis()
{
  Field_Mod32(&SCU->EXICON1.reg, (uint8)SCU_EXICON1_MON3_FE_Pos, SCU_EXICON1_MON3_FE_Msk, 0u);
}

INLINE void MON4_Rising_Edge_Int_En()
{
  Field_Mod32(&SCU->EXICON1.reg, (uint8)SCU_EXICON1_MON4_RE_Pos, SCU_EXICON1_MON4_RE_Msk, 1u);
}

INLINE void MON4_Rising_Edge_Int_Dis()
{
  Field_Mod32(&SCU->EXICON1.reg, (uint8)SCU_EXICON1_MON4_RE_Pos, SCU_EXICON1_MON4_RE_Msk, 0u);
}

INLINE void MON4_Falling_Edge_Int_En()
{
  Field_Mod32(&SCU->EXICON1.reg, (uint8)SCU_EXICON1_MON4_FE_Pos, SCU_EXICON1_MON4_FE_Msk, 1u);
}

INLINE void MON4_Falling_Edge_Int_Dis()
{
  Field_Mod32(&SCU->EXICON1.reg, (uint8)SCU_EXICON1_MON4_FE_Pos, SCU_EXICON1_MON4_FE_Msk, 0u);
}

INLINE uint8 MON1_Sts()
{
  return(u1_Field_Rd32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON1_STS_Pos, PMU_MON_CNF1_MON1_STS_Msk));
}

INLINE void MON1_PullUp_En()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON1_PU_Pos, PMU_MON_CNF1_MON1_PU_Msk, 1u);
}

INLINE void MON1_PullUp_Dis()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON1_PU_Pos, PMU_MON_CNF1_MON1_PU_Msk, 0u);
}

INLINE void MON1_PullDown_En()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON1_PD_Pos, PMU_MON_CNF1_MON1_PD_Msk, 1u);
}

INLINE void MON1_PullDown_Dis()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON1_PD_Pos, PMU_MON_CNF1_MON1_PD_Msk, 0u);
}

INLINE void MON1_CycSense_En()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON1_CYC_Pos, PMU_MON_CNF1_MON1_CYC_Msk, 1u);
}

INLINE void MON1_CycSense_Dis()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON1_CYC_Pos, PMU_MON_CNF1_MON1_CYC_Msk, 0u);
}

INLINE void MON1_WakeOnRise_En()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON1_RISE_Pos, PMU_MON_CNF1_MON1_RISE_Msk, 1u);
}

INLINE void MON1_WakeOnRise_Dis()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON1_RISE_Pos, PMU_MON_CNF1_MON1_RISE_Msk, 0u);
}

INLINE void MON1_WakeOnFall_En()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON1_FALL_Pos, PMU_MON_CNF1_MON1_FALL_Msk, 1u);
}

INLINE void MON1_WakeOnFall_Dis()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON1_FALL_Pos, PMU_MON_CNF1_MON1_FALL_Msk, 0u);
}

INLINE void MON1_En()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON1_EN_Pos, PMU_MON_CNF1_MON1_EN_Msk, 1u);
}

INLINE void MON1_Dis()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON1_EN_Pos, PMU_MON_CNF1_MON1_EN_Msk, 0u);
}

INLINE uint8 MON2_Sts()
{
  return(u1_Field_Rd32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON2_STS_Pos, PMU_MON_CNF1_MON2_STS_Msk));
}

INLINE void MON2_PullUp_En()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON2_PU_Pos, PMU_MON_CNF1_MON2_PU_Msk, 1u);
}

INLINE void MON2_PullUp_Dis()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON2_PU_Pos, PMU_MON_CNF1_MON2_PU_Msk, 0u);
}

INLINE void MON2_PullDown_En()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON2_PD_Pos, PMU_MON_CNF1_MON2_PD_Msk, 1u);
}

INLINE void MON2_PullDown_Dis()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON2_PD_Pos, PMU_MON_CNF1_MON2_PD_Msk, 0u);
}

INLINE void MON2_CycSense_En()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON2_CYC_Pos, PMU_MON_CNF1_MON2_CYC_Msk, 1u);
}

INLINE void MON2_CycSense_Dis()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON2_CYC_Pos, PMU_MON_CNF1_MON2_CYC_Msk, 0u);
}

INLINE void MON2_WakeOnRise_En()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON2_RISE_Pos, PMU_MON_CNF1_MON2_RISE_Msk, 1u);
}

INLINE void MON2_WakeOnRise_Dis()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON2_RISE_Pos, PMU_MON_CNF1_MON2_RISE_Msk, 0u);
}

INLINE void MON2_WakeOnFall_En()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON2_FALL_Pos, PMU_MON_CNF1_MON2_FALL_Msk, 1u);
}

INLINE void MON2_WakeOnFall_Dis()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON2_FALL_Pos, PMU_MON_CNF1_MON2_FALL_Msk, 0u);
}

INLINE void MON2_En()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON2_EN_Pos, PMU_MON_CNF1_MON2_EN_Msk, 1u);
}

INLINE void MON2_Dis()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON2_EN_Pos, PMU_MON_CNF1_MON2_EN_Msk, 0u);
}

INLINE uint8 MON3_Sts()
{
  return(u1_Field_Rd32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON3_STS_Pos, PMU_MON_CNF1_MON3_STS_Msk));
}

INLINE void MON3_PullUp_En()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON3_PU_Pos, PMU_MON_CNF1_MON3_PU_Msk, 1u);
}

INLINE void MON3_PullUp_Dis()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON3_PU_Pos, PMU_MON_CNF1_MON3_PU_Msk, 0u);
}

INLINE void MON3_PullDown_En()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON3_PD_Pos, PMU_MON_CNF1_MON3_PD_Msk, 1u);
}

INLINE void MON3_PullDown_Dis()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON3_PD_Pos, PMU_MON_CNF1_MON3_PD_Msk, 0u);
}

INLINE void MON3_CycSense_En()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON3_CYC_Pos, PMU_MON_CNF1_MON3_CYC_Msk, 1u);
}

INLINE void MON3_CycSense_Dis()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON3_CYC_Pos, PMU_MON_CNF1_MON3_CYC_Msk, 0u);
}

INLINE void MON3_WakeOnRise_En()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON3_RISE_Pos, PMU_MON_CNF1_MON3_RISE_Msk, 1u);
}

INLINE void MON3_WakeOnRise_Dis()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON3_RISE_Pos, PMU_MON_CNF1_MON3_RISE_Msk, 0u);
}

INLINE void MON3_WakeOnFall_En()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON3_FALL_Pos, PMU_MON_CNF1_MON3_FALL_Msk, 1u);
}

INLINE void MON3_WakeOnFall_Dis()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON3_FALL_Pos, PMU_MON_CNF1_MON3_FALL_Msk, 0u);
}

INLINE void MON3_En()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON3_EN_Pos, PMU_MON_CNF1_MON3_EN_Msk, 1u);
}

INLINE void MON3_Dis()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON3_EN_Pos, PMU_MON_CNF1_MON3_EN_Msk, 0u);
}

INLINE uint8 MON4_Sts()
{
  return(u1_Field_Rd32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON4_STS_Pos, PMU_MON_CNF1_MON4_STS_Msk));
}

INLINE void MON4_PullUp_En()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON4_PU_Pos, PMU_MON_CNF1_MON4_PU_Msk, 1u);
}

INLINE void MON4_PullUp_Dis()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON4_PU_Pos, PMU_MON_CNF1_MON4_PU_Msk, 0u);
}

INLINE void MON4_PullDown_En()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON4_PD_Pos, PMU_MON_CNF1_MON4_PD_Msk, 1u);
}

INLINE void MON4_PullDown_Dis()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON4_PD_Pos, PMU_MON_CNF1_MON4_PD_Msk, 0u);
}

INLINE void MON4_CycSense_En()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON4_CYC_Pos, PMU_MON_CNF1_MON4_CYC_Msk, 1u);
}

INLINE void MON4_CycSense_Dis()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON4_CYC_Pos, PMU_MON_CNF1_MON4_CYC_Msk, 0u);
}

INLINE void MON4_WakeOnRise_En()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON4_RISE_Pos, PMU_MON_CNF1_MON4_RISE_Msk, 1u);
}

INLINE void MON4_WakeOnRise_Dis()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON4_RISE_Pos, PMU_MON_CNF1_MON4_RISE_Msk, 0u);
}

INLINE void MON4_WakeOnFall_En()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON4_FALL_Pos, PMU_MON_CNF1_MON4_FALL_Msk, 1u);
}

INLINE void MON4_WakeOnFall_Dis()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON4_FALL_Pos, PMU_MON_CNF1_MON4_FALL_Msk, 0u);
}

INLINE void MON4_En()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON4_EN_Pos, PMU_MON_CNF1_MON4_EN_Msk, 1u);
}

INLINE void MON4_Dis()
{
  Field_Mod32(&PMU->MON_CNF1.reg, (uint8)PMU_MON_CNF1_MON4_EN_Pos, PMU_MON_CNF1_MON4_EN_Msk, 0u);
}

INLINE void MON1_Int_En(void)
{
  Field_Mod32(&SCU->MONIEN.reg, (uint8)SCU_MONIEN_MON1IE_Pos, SCU_MONIEN_MON1IE_Msk, 1u);
}

INLINE void MON2_Int_En(void)
{
  Field_Mod32(&SCU->MONIEN.reg, (uint8)SCU_MONIEN_MON2IE_Pos, SCU_MONIEN_MON2IE_Msk, 1u);
}

INLINE void MON3_Int_En(void)
{
  Field_Mod32(&SCU->MONIEN.reg, (uint8)SCU_MONIEN_MON3IE_Pos, SCU_MONIEN_MON3IE_Msk, 1u);
}

INLINE void MON4_Int_En(void)
{
  Field_Mod32(&SCU->MONIEN.reg, (uint8)SCU_MONIEN_MON4IE_Pos, SCU_MONIEN_MON4IE_Msk, 1u);
}

INLINE void MON1_Int_Dis(void)
{
  Field_Mod32(&SCU->MONIEN.reg, (uint8)SCU_MONIEN_MON1IE_Pos, SCU_MONIEN_MON1IE_Msk, 0u);
}

INLINE void MON2_Int_Dis(void)
{
  Field_Mod32(&SCU->MONIEN.reg, (uint8)SCU_MONIEN_MON2IE_Pos, SCU_MONIEN_MON2IE_Msk, 0u);
}

INLINE void MON3_Int_Dis(void)
{
  Field_Mod32(&SCU->MONIEN.reg, (uint8)SCU_MONIEN_MON3IE_Pos, SCU_MONIEN_MON3IE_Msk, 0u);
}

INLINE void MON4_Int_Dis(void)
{
  Field_Mod32(&SCU->MONIEN.reg, (uint8)SCU_MONIEN_MON4IE_Pos, SCU_MONIEN_MON4IE_Msk, 0u);
}

#endif
