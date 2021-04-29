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
 * \file     wdt1.h
 *
 * \brief    Window Watchdog 1 low level access library
 *
 * \version  V0.2.2
 * \date     02. Mar 2020
 *
 * \note This file violates [MISRA 2012 Rule 11.1, required], [MISRA 2012 Rule 11.4, advisory], [MISRA 2012 Rule 11.6, required], [MISRA 2012 Rule 2.5, advisory], [MISRA 2012 Rule 8.7, advisory]
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
**                           Revision history moved from wdt1.c to wdt1.h     **
**                           Systick_Value_Get, Systick_ReloadValue_Get,      **
**                           SysTick_ReloadValue_Set functions added          **
**                           WDT1_Init splitted to WDT1_Init and SysTick_Init **
**                           Delay_us updated to allow delays >=1000us        **
** V0.2.2: 2020-03-02, BG:   Updated revision history format                  **
*******************************************************************************/

#ifndef _WDT1_H
#define _WDT1_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle985x.h"
#include "types.h"
#include "sfr_access.h"

/*******************************************************************************
**                       External Variable Declarations                       **
*******************************************************************************/
extern uint32 WD_Counter;

/*******************************************************************************
**                          Global Macro Definitions                          **
*******************************************************************************/
#define One_us ((uint32)SCU_FSYS / 1000000u)
#define SysTickRL ((sint32)SCU_FSYS / (sint32)SysTickFreq)

/*******************************************************************************
**                        Global Constant Declarations                        **
*******************************************************************************/
/**\brief SysTick 1kHz*/
#define SysTickFreq     1000u

/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/
/** \brief Performs the initial service of the WDT1 (closes the long open window).
 *\brief Resets the \link WD_Counter \endlink to '0'.
 *
 * \ingroup wdt1_api
 */
void WDT1_Init(void);

/** \brief Initializes the SysTick timer to 1ms interval
 *\brief and enables the SysTick interrupt.
 *
 * \ingroup wdt1_api
 */
void SysTick_Init(void);

/** \brief Stops the service of WDT1 by stopping the SysTick timer.
 *
 *\warning Handle this function with care, as a WDT1 itself will not be stopped,
 *\warning just the service of it is stopped. This might lead to device resets.
 *
 * \brief <b>Example</b><br>
 * \brief This example stops the WDT1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     WDT1_Stop();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup wdt1_api
 */
void WDT1_Stop(void);

/** \brief Services the WDT1 in the open window.
 *
 * \retval TRUE WDT1 serviced
 * \retval FALSE WDT1 was not serviced (not in open window)
 *
 * \brief <b>Example</b><br>
 * \brief This example services the WDT1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup wdt1_api
 */
bool WDT1_Service(void);

/** \brief Triggers a short-window (~30ms) of the WDT1.
 *
 * \param NoOfSOW number of consecutive Short open windows allowed
 *
 * \brief <b>Example</b><br>
 * \brief This example sets one successive Short Open Window to be allowed and triggers a SOW.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     WDT1_SOW_Service(1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup wdt1_api
 */
void WDT1_SOW_Service(uint32 NoOfSOW);

/** \brief Delays the regular program execution by a given number of Microseconds
 * \brief the function returns if the given time has elapsed
 * \brief smaller Microsecond delay times are getting falsen by the execution time
 * \brief of the function itself
 *
 * \warning Handle this function with care, as WDT1/WDT will not be serviced during the delay time.
 * \warning The user has to take care of WDT1/WDT service by himself.
 *
 * \param delay_time_us Delay time in Microseconds (max. < 1000us)
 *
 * \brief <b>Example</b><br>
 * \brief This example sets a delay of 100 us.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     Delay_us(100);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup wdt1_api
 */
void Delay_us(uint32 delay_time_us);

/*******************************************************************************
**                        Inline Function Declarations                        **
*******************************************************************************/
/** \brief Increments the WDT1 Window Counter
 *
 * \brief <b>Example</b><br>
 * \brief This example increments the WDT1 Window Counter.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     WDT1_Window_Count();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup wdt1_api
 */
INLINE void WDT1_Window_Count(void);

/** \brief returns the current SysTick timer count value
 *
 * \return current SysTick timer count value
 *
 * \brief <b>Example</b><br>
 * \brief This example reads the current SysTick timer count value
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint32 val;
 *
 *     val = Systick_Value_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup wdt1_api
 */
INLINE uint32 Systick_Value_Get(void);

/** \brief returns the current SysTick reload value
 *
 * \return current SysTick reload value
 *
 * \brief <b>Example</b><br>
 * \brief This example reads the current SysTick reload value
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint32 val;
 *
 *     val = Systick_ReloadValue_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup wdt1_api
 */
INLINE uint32 Systick_ReloadValue_Get(void);

/** \brief sets the SysTick Reload value
 *
 * \param val reload value for SysTick timer
 *
 * \brief <b>Example</b><br>
 * \brief This example sets the current SysTick reload to Max value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     SysTick_ReloadValue_Set(0xFFFFFF);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup wdt1_api
 */
INLINE void SysTick_ReloadValue_Set(uint32 val);

/*******************************************************************************
**                         Inline Function Definitions                        **
*******************************************************************************/
INLINE void WDT1_Window_Count()
{
  WD_Counter++;
}

INLINE uint32 Systick_Value_Get(void)
{
  return(u32_Field_Rd32(&CPU->SYSTICK_CVR.reg, (uint8)CPU_SYSTICK_CVR_CURRENT_Pos, CPU_SYSTICK_CVR_CURRENT_Msk));
}

INLINE uint32 Systick_ReloadValue_Get(void)
{
  return(u32_Field_Rd32(&CPU->SYSTICK_RVR.reg, (uint8)CPU_SYSTICK_RVR_RELOAD_Pos, CPU_SYSTICK_RVR_RELOAD_Msk));
}

INLINE void SysTick_ReloadValue_Set(uint32 val)
{
  Field_Wrt32(&CPU->SYSTICK_RVR.reg, (uint8)CPU_SYSTICK_RVR_RELOAD_Pos, CPU_SYSTICK_RVR_RELOAD_Msk, val);
}

#endif
