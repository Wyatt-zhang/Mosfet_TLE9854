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
 * \file     timer2x.h
 *
 * \brief    Timer2/Timer21 low level access library
 *
 * \version  V0.2.2
 * \date     02. Mar 2020
 *
 * \note This file violates [MISRA 2012 Rule 11.1, required], [MISRA 2012 Rule 11.4, advisory], [MISRA 2012 Rule 11.6, required], [MISRA 2012 Rule 8.7, advisory]
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
**                           Revision history moved from timer2x.c to         **
**                           timer2x.h                                        **
**                           Added handling in case of timer_interval_us      **
**                           value in invalid range                           **
**                           TIMER21_Select_T21EX function updated            **
** V0.2.2: 2020-03-02, BG:   Updated revision history format                  **
*******************************************************************************/

#ifndef TIMER2X_H
#define TIMER2X_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle985x.h"
#include "types.h"
#include "sfr_access.h"

/*******************************************************************************
**                           Global Type Definitions                          **
*******************************************************************************/
/** \enum TTIMER2_T2IN_Pxx
 *  \brief This enum lists the T2IN Inputs.
 */
typedef enum
{
  TIMER2_T2IN_P00 = 0u, /**< The input pin for T2_0 */
  TIMER2_T2IN_P27 = 1u, /**< The input pin for T2_1 */
  TIMER2_T2IN_P23 = 2u  /**< The input pin for T2_2 */
} TTIMER2_T2IN_Pxx;

/** \enum TTIMER2_T2EX_Pxx
 *  \brief This enum lists the T2EX Inputs.
 */
typedef enum
{
  TIMER2_T2EX_P22 = 0u,         /**< The input pin for T2EX_0 */
  TIMER2_T2EX_P01 = 1u,         /**< The input pin for T2EX_1 */
  TIMER2_T2EX_P23 = 2u,         /**< The input pin for T2EX_2 */
  TIMER2_T2EX_P21 = 3u,         /**< The input pin for T2EX_3 */
  TIMER2_T2EX_MON1 = 4u,        /**< The input pin for MON1 */
  TIMER2_T2EX_MON2 = 5u,        /**< The input pin for MON2 */
  TIMER2_T2EX_MON3 = 6u,        /**< The input pin for MON3 */
  TIMER2_T2EX_MON4 = 7u,        /**< The input pin for MON4 */
  TIMER2_T2EX_lin_rxd = 8u,     /**< The input pin for lin_rxd_i */
  TIMER2_T2EX_CC6_COUT60 = 10u, /**< The input pin for cc6_cout60 */
  TIMER2_T2EX_CC6_COUT61 = 11u, /**< The input pin for cc6_cout61 */
  TIMER2_T2EX_CC6_CH0 = 12u,    /**< The input pin for cc6_ch0 */
  TIMER2_T2EX_CC6_CH1 = 13u,    /**< The input pin for cc6_ch1 */
  TIMER2_T2EX_CC6_CH2 = 14u,    /**< The input pin for cc6_ch2 */
  TIMER2_T2EX_CC6_CH3 = 15u     /**< The input pin for cc6_ch3 */
} TTIMER2_T2EX_Pxx;

/** \enum TTIMER21_T21IN_Pxx
 *  \brief This enum lists the T21IN Inputs.
 */
typedef enum
{
  TIMER21_T21IN_P01 = 0u, /**< The input pin for T21_0 */
  TIMER21_T21IN_P12 = 1u, /**< The input pin for T21_1 */
  TIMER21_T21IN_P04 = 2u  /**< The input pin for T21_2 */
} TTIMER21_T21IN_Pxx;

/** \enum TTIMER21_T21EX_Pxx
 *  \brief This enum lists the T21EX Inputs.
 */
typedef enum
{
  TIMER21_T21EX_P02 = 0u,         /**< The input pin for T21EX_0 */
  TIMER21_T21EX_P14 = 1u,         /**< The input pin for T21EX_1 */
  TIMER21_T21EX_P05 = 2u,         /**< The input pin for T21EX_2 */
  TIMER21_T21EX_P11 = 3u,         /**< The input pin for T21EX_3 */
  TIMER21_T21EX_MON1 = 4u,        /**< The input pin for MON1 */
  TIMER21_T21EX_MON2 = 5u,        /**< The input pin for MON2 */
  TIMER21_T21EX_MON3 = 6u,        /**< The input pin for MON3 */
  TIMER21_T21EX_MON4 = 7u,        /**< The input pin for MON4 */
  TIMER21_T21EX_lin_rxd = 8u,     /**< The input pin for lin_rxd_i */
  TIMER21_T21EX_CC6_CH0 = 10u,    /**< The input pin for cc6_ch0 */
  TIMER21_T21EX_CC6_CH1 = 11u,    /**< The input pin for cc6_ch1 */
  TIMER21_T21EX_CC6_COUT60 = 12u, /**< The input pin for cc6_cout60 */
  TIMER21_T21EX_CC6_COUT61 = 13u, /**< The input pin for cc6_cout61 */
  TIMER21_T21EX_CC6_COUT62 = 14u, /**< The input pin for cc6_cout62 */
  TIMER21_T21EX_CC6_COUT63 = 15u  /**< The input pin for cc6_cout63 */  
} TTIMER21_T21EX_Pxx;

/** \enum TIMER2x_Clock_Prescaler
 *  \brief This enum lists TIMER2x Clock Prescaler Configuration.
 */
typedef enum
{
  TIMER2x_Clk_Div_1   = 0u, /**< Timer2x Input Clock Select: fsys */
  TIMER2x_Clk_Div_2   = 1u, /**< Timer2x Input Clock Select: fsys/2 */
  TIMER2x_Clk_Div_4   = 2u, /**< Timer2x Input Clock Select: fsys/4 */
  TIMER2x_Clk_Div_8   = 3u, /**< Timer2x Input Clock Select: fsys/8 */
  TIMER2x_Clk_Div_16  = 4u, /**< Timer2x Input Clock Select: fsys/16 */
  TIMER2x_Clk_Div_32  = 5u, /**< Timer2x Input Clock Select: fsys/32 */
  TIMER2x_Clk_Div_64  = 6u, /**< Timer2x Input Clock Select: fsys/64 */
  TIMER2x_Clk_Div_128 = 7u  /**< Timer2x Input Clock Select: fsys/128 */
} TIMER2x_Clock_Prescaler;

/*******************************************************************************
**                          Global Macro Definitions                          **
*******************************************************************************/
#define MIN_TIMER_INTERVAL_US 1u

/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/
/** \brief Initializes the Timer2 module.
 *
 * \ingroup timer2x_api
 */
void TIMER2_Init(void);

/** \brief Initializes the Timer21 module.
 *
 * \ingroup TIMER2x_api
 */
void TIMER21_Init(void);

/** \brief Initializes the TIMER2 in Reload Mode
 *
 * \param timer_interval_us timer interval in microseconds
 * \return true = setup done, false = setup failed
 *
 * \brief <b>Example</b><br>
 * \brief This example Initializes the TIMER2 in Reload Mode with timer equals to 5000 us.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     bool sts;  
 *  
 *     sts = TIMER2_Interval_Timer_Setup(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
bool TIMER2_Interval_Timer_Setup(uint32 timer_interval_us);

/** \brief Initializes the TIMER21 in Reload Mode
 *
 * \param timer_interval_us timer interval in microseconds
 * \return true = setup done, false = setup failed
 *
 * \brief <b>Example</b><br>
 * \brief This example Initializes the TIMER21 in Reload Mode with timer equals to 5000 us.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     bool sts;  
 *  
 *     sts = TIMER21_Interval_Timer_Setup(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
bool TIMER21_Interval_Timer_Setup(uint32 timer_interval_us);

/*******************************************************************************
**                        Inline Function Declarations                        **
*******************************************************************************/
/** \brief Enables TIMER2 clock prescaler.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables TIMER2 clock prescaler.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_Clk_Prescaler_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_Clk_Prescaler_En(void);

/** \brief Disables TIMER2 clock prescaler.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables TIMER2 clock prescaler.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_Clk_Prescaler_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_Clk_Prescaler_Dis(void);

/** \brief Sets TIMER2 clock prescaler.
 *
 * \param t2pre TIMER2 clock prescaler, see \link TIMER2x_Clock_Prescaler \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example sets TIMER2 clock prescaler to DIV2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_Clk_Prescaler_En();
 *     TIMER2_Clk_Prescaler_Sel((uint8)TIMER2x_Clk_Div_2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_Clk_Prescaler_Sel(uint8 t2pre);

/** \brief Reads TIMER2 clock prescaler.
 *
 * \return TIMER2 clock prescaler
 *
 * \brief <b>Example</b><br>
 * \brief This example reads TIMER2 clock prescaler.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 pre;
 *
 *     TIMER2_Clk_Prescaler_En();
 *     pre = TIMER2_Clk_Prescaler_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE uint8 TIMER2_Clk_Prescaler_Get(void);

/** \brief Reads TIMER2 Overflow Status.
 *
 * \return TIMER2 Overflow Status
 *
 * \brief <b>Example</b><br>
 * \brief This example checks the TIMER2 Overflow Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_Overflow_Int_En();
 *     if (TIMER2_Overflow_Sts() == 1)
 *     {
 *       TIMER2_TF2_CALLBACK();  
 *     }
 *     TIMER2_Overflow_Int_Clr();
 *     TIMER2_Overflow_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE uint8 TIMER2_Overflow_Sts(void);

/** \brief Reads TIMER2 External Status.
 *
 * \return TIMER2 External Status
 *
 * \brief <b>Example</b><br>
 * \brief This example checks the TIMER2 External Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_ExternalCtrl_En();
 *     if (TIMER2_External_Sts() == 1)
 *     {
 *       TIMER2_EXF2_CALLBACK();  
 *     }
 *     TIMER2_ExternalCtrl_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE uint8 TIMER2_External_Sts(void);

/** \brief Enables TIMER2 External Control.
 *
 * \brief <b>Example</b><br>
 * \brief This example checks the TIMER2 External Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_External_Int_En();  
 *     TIMER2_ExternalCtrl_En();
 *     if (TIMER2_External_Sts() == 1)
 *     {
 *       TIMER2_EXF2_CALLBACK();  
 *     }
 *     TIMER2_External_Int_Clr();
 *     TIMER2_ExternalCtrl_Dis();
 *     TIMER2_External_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_ExternalCtrl_En(void);

/** \brief Disables TIMER2 External Control.
 *
 * \brief <b>Example</b><br>
 * \brief This example reads TIMER2 External Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_ExternalCtrl_En();
 *     TIMER2_External_Sts();
 *     TIMER2_ExternalCtrl_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_ExternalCtrl_Dis(void);

/** \brief Sets Rising Edge to Capture/Reload Mode for TIMER2.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Rising Edge to Capture/Reload Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_Reload_Capture_RisingEdge_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_Reload_Capture_RisingEdge_Set(void);

/** \brief Sets Falling Edge to Capture/Reload Mode for TIMER2.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Falling Edge to Capture/Reload Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_Reload_Capture_FallingEdge_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_Reload_Capture_FallingEdge_Set(void);  

/** \brief Sets Rising Edge to External Start for TIMER2.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Rising Edge to External Start.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_ExtStart();  
 *     TIMER2_ExtStart_RisingEdge_Set();
 *     TIMER2_ExtStop();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_ExtStart_RisingEdge_Set(void);

/** \brief Sets Falling Edge to External Start for TIMER2.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Falling Edge to External Start.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_ExtStart();  
 *     TIMER2_ExtStart_FallingEdge_Set();
 *     TIMER2_ExtStop();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_ExtStart_FallingEdge_Set(void);

/** \brief Enables Up/Down Counter for TIMER2.
 *
 * \brief <b>Example</b><br>
 * \brief This example starts Up Counter once there is a logic 1 at pin T2EX which is configured to P2.2 .
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_UpDownCount_En();
 *     TIMER2_Select_T2EX(TIMER2_T2EX_P22);
 *     while(TIMER2_External_Sts() == (uint8)0)
 *     {
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_UpDownCount_En(void);

/** \brief Disables Up/Down Counter for TIMER2.
 *
 * \brief <b>Example</b><br>
 * \brief This example starts Up Counter once TR2 is set and External Control was disabled.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_ExternalCtrl_Dis();
 *     TIMER2_UpDownCount_Dis();
 *     TIMER2_Start();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_UpDownCount_Dis(void);

/** \brief Selects Capture Mode for TIMER2.
 *
 * \brief <b>Example</b><br>
 * \brief This example enters 16-bit Capture Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_ExternalCtrl_En();
 *     TIMER2_Mode_Capture_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_Mode_Capture_Set(void);

/** \brief Selects Reload Mode for TIMER2.
 *
 * \brief <b>Example</b><br>
 * \brief This example enters Auto-Reload Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_Mode_Reload_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_Mode_Reload_Set(void);

/** \brief Selects Mode Counter for TIMER2.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets the Mode Counter.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_Mode_Counter_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_Mode_Counter_Set(void);

/** \brief Selects Mode Timer for TIMER2.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets the Mode Timer.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_Mode_Timer_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_Mode_Timer_Set(void);

/** \brief Sets TIMER2 Value.
 *
 * \param t2 TIMER2 Value
 *
 * \brief <b>Example</b><br>
 * \brief This example sets TIMER2 Value to 5000 ticks.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_Value_Set(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_Value_Set(uint16 t2);

/** \brief Sets TIMER2 Reload Value.
 *
 * \param t2 TIMER2 Reload Value
 *
 * \brief <b>Example</b><br>
 * \brief This example sets TIMER2 Reload Value to 5000.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_Mode_Reload_Set();
 *     TIMER2_Reload_Value_Set(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_Reload_Value_Set(uint16 t2);

/** \brief Clears TIMER2 Overflow Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the TIMER2 Overflow Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_Overflow_Int_En();
 *     if (TIMER2_Overflow_Sts() == 1)
 *     {
 *       TIMER2_TF2_CALLBACK();
 *       TIMER2_Overflow_Int_Clr();
 *     }
 *     TIMER2_Overflow_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */  
INLINE void TIMER2_Overflow_Int_Clr(void);

/** \brief Clears TIMER2 External Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the TIMER2 External Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_External_Int_En();  
 *     if (TIMER2_External_Sts() == 1)
 *     {
 *       TIMER2_EXF2_CALLBACK();
 *       TIMER2_External_Int_Clr();
 *     }
 *     TIMER2_External_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_External_Int_Clr(void);

/** \brief Enables TIMER2 Overflow Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the TIMER2 Overflow Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_Overflow_Int_En();
 *     if (TIMER2_Overflow_Sts() == 1)
 *     {
 *       TIMER2_TF2_CALLBACK();
 *       TIMER2_Overflow_Int_Clr();
 *     }
 *     TIMER2_Overflow_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_Overflow_Int_En(void);

/** \brief Disables TIMER2 Overflow Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the TIMER2 Overflow Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_Overflow_Int_En();
 *     if (TIMER2_Overflow_Sts() == 1)
 *     {
 *       TIMER2_TF2_CALLBACK();
 *       TIMER2_Overflow_Int_Clr();
 *     }
 *     TIMER2_Overflow_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_Overflow_Int_Dis(void);

/** \brief Enables TIMER2 External Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the TIMER2 External Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_External_Int_En();  
 *     if (TIMER2_External_Sts() == 1)
 *     {
 *       TIMER2_EXF2_CALLBACK();
 *       TIMER2_External_Int_Clr();
 *     }
 *     TIMER2_External_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_External_Int_En(void);

/** \brief Disables TIMER2 External Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the TIMER2 External Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_External_Int_En();  
 *     if (TIMER2_External_Sts() == 1)
 *     {
 *       TIMER2_EXF2_CALLBACK();
 *       TIMER2_External_Int_Clr();
 *     }
 *     TIMER2_External_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_External_Int_Dis(void);

/** \brief Enables TIMER21 clock prescaler.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables TIMER21 clock prescaler.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_Clk_Prescaler_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER21_Clk_Prescaler_En(void);

/** \brief Disables TIMER21 clock prescaler.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables TIMER21 clock prescaler.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_Clk_Prescaler_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER21_Clk_Prescaler_Dis(void);

/** \brief Sets TIMER21 clock prescaler.
 *
 * \param t21pre TIMER21 clock prescaler, see \link TIMER2x_Clock_Prescaler \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example sets TIMER21 clock prescaler to DIV2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_Clk_Prescaler_En();
 *     TIMER21_Clk_Prescaler_Sel((uint8)TIMER2x_Clk_Div_2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER21_Clk_Prescaler_Sel(uint8 t21pre);

/** \brief Reads TIMER21 clock prescaler.
 *
 * \return TIMER21 clock prescaler
 *
 * \brief <b>Example</b><br>
 * \brief This example reads TIMER21 clock prescaler.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 pre;
 *
 *     TIMER21_Clk_Prescaler_En();
 *     pre = TIMER21_Clk_Prescaler_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE uint8 TIMER21_Clk_Prescaler_Get(void);

/** \brief Reads TIMER21 Overflow Status.
 *
 * \return TIMER21 Overflow Status
 *
 * \brief <b>Example</b><br>
 * \brief This example checks the TIMER21 Overflow Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_Overflow_Int_En();
 *     if (TIMER21_Overflow_Sts() == 1)
 *     {
 *       TIMER21_TF2_CALLBACK();  
 *     }
 *     TIMER21_Overflow_Int_Clr();
 *     TIMER21_Overflow_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE uint8 TIMER21_Overflow_Sts(void);

/** \brief Reads TIMER21 External Status.
 *
 * \return TIMER21 External Status
 *
 * \brief <b>Example</b><br>
 * \brief This example checks the TIMER21 External Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_ExternalCtrl_En();
 *     if (TIMER21_External_Sts() == 1)
 *     {
 *       TIMER21_EXF2_CALLBACK();  
 *     }
 *     TIMER21_ExternalCtrl_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE uint8 TIMER21_External_Sts(void);

/** \brief Enables TIMER21 External Control.
 *
 * \brief <b>Example</b><br>
 * \brief This example checks the TIMER21 External Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_External_Int_En();  
 *     TIMER21_ExternalCtrl_En();
 *     if (TIMER21_External_Sts() == 1)
 *     {
 *       TIMER21_EXF2_CALLBACK();  
 *     }
 *     TIMER21_External_Int_Clr();
 *     TIMER21_ExternalCtrl_Dis();
 *     TIMER21_External_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER21_ExternalCtrl_En(void);

/** \brief Disables TIMER21 External Control.
 *
 * \brief <b>Example</b><br>
 * \brief This example reads TIMER21 External Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_ExternalCtrl_En();
 *     TIMER21_External_Sts();
 *     TIMER21_ExternalCtrl_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER21_ExternalCtrl_Dis(void);

/** \brief Sets Rising Edge to Capture/Reload Mode for TIMER21.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Rising Edge to Capture/Reload Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_Reload_Capture_RisingEdge_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER21_Reload_Capture_RisingEdge_Set(void);

/** \brief Sets Falling Edge to Capture/Reload Mode for TIMER21.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Falling Edge to Capture/Reload Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_Reload_Capture_FallingEdge_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER21_Reload_Capture_FallingEdge_Set(void);  

/** \brief Sets Rising Edge to External Start for TIMER21.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Rising Edge to External Start.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_ExtStart_RisingEdge_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER21_ExtStart_RisingEdge_Set(void);

/** \brief Sets Falling Edge to External Start for TIMER21.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Falling Edge to External Start.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_ExtStart_FallingEdge_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER21_ExtStart_FallingEdge_Set(void);

/** \brief Enables Up/Down Counter for TIMER21.
 *
 * \brief <b>Example</b><br>
 * \brief This example starts Up Counter once there is a logic 1 at pin T21EX which is configured to P0.2 .
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_UpDownCount_En();
 *     TIMER21_Select_T21EX(TIMER21_T21EX_P02);
 *     while(TIMER21_External_Sts() == (uint8)0)
 *     {
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER21_UpDownCount_En(void);

/** \brief Disables Up/Down Counter for TIMER21.
 *
 * \brief <b>Example</b><br>
 * \brief This example starts Up Counter once TR2 is set and External Control was disabled.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_ExternalCtrl_Dis();
 *     TIMER21_UpDownCount_Dis();
 *     TIMER21_Start();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER21_UpDownCount_Dis(void);

/** \brief Selects Capture Mode for TIMER21.
 *
 * \brief <b>Example</b><br>
 * \brief This example enters 16-bit Capture Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_ExternalCtrl_En();
 *     TIMER21_Mode_Capture_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER21_Mode_Capture_Set(void);

/** \brief Selects Reload Mode for TIMER21.
 *
 * \brief <b>Example</b><br>
 * \brief This example enters Auto-Reload Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_Mode_Reload_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER21_Mode_Reload_Set(void);

/** \brief Selects Mode Counter for TIMER21.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets the Mode Counter.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_Mode_Counter_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER21_Mode_Counter_Set(void);

/** \brief Selects Mode Timer for TIMER21.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets the Mode Timer.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_Mode_Timer_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER21_Mode_Timer_Set(void);

/** \brief Sets TIMER21 Value.
 *
 * \param t21 TIMER21 Value
 *
 * \brief <b>Example</b><br>
 * \brief This example sets TIMER21 Value to 5000.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_Value_Set(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER21_Value_Set(uint16 t21);

/** \brief Sets TIMER21 Reload Value.
 *
 * \param t21 TIMER21 Reload Value
 *
 * \brief <b>Example</b><br>
 * \brief This example sets TIMER21 Reload Value to 5000.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_Mode_Reload_Set();
 *     TIMER21_Reload_Value_Set(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER21_Reload_Value_Set(uint16 t21);

/** \brief Clears TIMER21 Overflow Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the TIMER21 Overflow Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_Overflow_Int_En();
 *     if (TIMER21_Overflow_Sts() == 1)
 *     {
 *       TIMER21_TF2_CALLBACK();
 *       TIMER21_Overflow_Int_Clr();
 *     }
 *     TIMER21_Overflow_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER21_Overflow_Int_Clr(void);

/** \brief Clears TIMER21 External Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the TIMER21 External Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_External_Int_En();  
 *     if (TIMER21_External_Sts() == 1)
 *     {
 *       TIMER21_EXF2_CALLBACK();
 *       TIMER21_External_Int_Clr();
 *     }
 *     TIMER21_External_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER21_External_Int_Clr(void);

/** \brief Enables TIMER21 Overflow Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the TIMER21 Overflow Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_Overflow_Int_En();
 *     if (TIMER21_Overflow_Sts() == 1)
 *     {
 *       TIMER21_TF2_CALLBACK();
 *       TIMER21_Overflow_Int_Clr();
 *     }
 *     TIMER21_Overflow_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER21_Overflow_Int_En(void);

/** \brief Disables TIMER21 Overflow Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the TIMER21 Overflow Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_Overflow_Int_En();
 *     if (TIMER21_Overflow_Sts() == 1)
 *     {
 *       TIMER21_TF2_CALLBACK();
 *       TIMER21_Overflow_Int_Clr();
 *     }
 *     TIMER21_Overflow_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER21_Overflow_Int_Dis(void);

/** \brief Enables TIMER21 External Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the TIMER21 External Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_External_Int_En();  
 *     if (TIMER21_External_Sts() == 1)
 *     {
 *       TIMER21_EXF2_CALLBACK();
 *       TIMER21_External_Int_Clr();
 *     }
 *     TIMER21_External_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER21_External_Int_En(void);

/** \brief Disables TIMER21 External Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the TIMER21 External Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_External_Int_En();  
 *     if (TIMER21_External_Sts() == 1)
 *     {
 *       TIMER21_EXF2_CALLBACK();
 *       TIMER21_External_Int_Clr();
 *     }
 *     TIMER21_External_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER21_External_Int_Dis(void);

/** \brief Starts the TIMER2 by software
 *
 * \brief <b>Example</b><br>
 * \brief This example starts the TIMER2 by software.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_Start();  
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_Start(void);

/** \brief Stops the TIMER2 by software
 *
 * \brief <b>Example</b><br>
 * \brief This example stops and reset TIMER2 by software.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_Stop();
 *     TIMER2_Clear_Count();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_Stop(void);

/** \brief Prepares TIMER2 to be started externally
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Rising Edge to External Start.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_ExtStart();  
 *     TIMER2_ExtStart_RisingEdge_Set();
 *     TIMER2_ExtStop();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_ExtStart(void);

/** \brief Disables TIMER2 to be started externally
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Rising Edge to External Start.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_ExtStart();  
 *     TIMER2_ExtStart_RisingEdge_Set();
 *     TIMER2_ExtStop();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_ExtStop(void);

/** \brief Reads the TIMER2 count value
 *
 * \return TIMER2 count value
 *
 * \brief <b>Example</b><br>
 * \brief This example reads the TIMER2 count value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 timer_ticks;
 *
 *     timer_ticks = TIMER2_Get_Count();  
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE uint16 TIMER2_Get_Count(void);

/** \brief Reads the TIMER2 capture value
 *
 * \return TIMER2 capture value
 *
 * \brief <b>Example</b><br>
 * \brief This example reads the TIMER2 capture value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 timer_ticks;
 *  
 *     timer_ticks = TIMER2_Get_Capture();  
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE uint16 TIMER2_Get_Capture(void);

/** \brief Clears the TIMER2 count value
 *
 * \brief <b>Example</b><br>
 * \brief This example stops and reset TIMER2 by software.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {  
 *     TIMER2_Stop();
 *     TIMER2_Clear_Count();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_Clear_Count(void);

/** \brief Sets TIMER2 reload value
 *
 * \param value reload value in ticks
 *
 * \brief <b>Example</b><br>
 * \brief This example sets TIMER2 Reload Value to 5000 ticks.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_Mode_Reload_Set();
 *     TIMER2_Set_Reload(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_Set_Reload(uint16 value);

/** \brief Sets TIMER2 T2IN Pin
 *
 * \param pinsel T2IN Pin select, see \link TTIMER2_T2IN_Pxx \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example sets TIMER2 Input to T2_1(P2.7).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_Select_T2IN(TIMER2_T2IN_P27);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_Select_T2IN(TTIMER2_T2IN_Pxx pinsel);

/** \brief Sets TIMER2 T2EX Pin
 *
 * \param pinsel T2EX Pin select, see \link TTIMER2_T2EX_Pxx \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example sets TIMER2 External Input to T2EX_0(P2.2).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER2_Select_T2EX(TIMER2_T2EX_P22);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER2_Select_T2EX(TTIMER2_T2EX_Pxx pinsel);

/** \brief Starts the TIMER21 by software
 *
 * \brief <b>Example</b><br>
 * \brief This example starts the TIMER21 by software.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_Start();  
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER21_api
 */
INLINE void TIMER21_Start(void);

/** \brief Stops the TIMER21 by software
 *
 * \brief <b>Example</b><br>
 * \brief This example stops and reset TIMER21 by software.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_Stop();
 *     TIMER21_Clear_Count();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER21_api
 */
INLINE void TIMER21_Stop(void);

/** \brief Prepares TIMER21 to be started externally
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Rising Edge to External Start.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_ExtStart();  
 *     TIMER21_ExtStart_RisingEdge_Set();
 *     TIMER21_ExtStop();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER21_api
 */
INLINE void TIMER21_ExtStart(void);

/** \brief Disables TIMER21 to be started externally
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Rising Edge to External Start.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_ExtStart();  
 *     TIMER21_ExtStart_RisingEdge_Set();
 *     TIMER21_ExtStop();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER21_api
 */
INLINE void TIMER21_ExtStop(void);

/** \brief Reads the TIMER21 count value
 *
 * \return TIMER21 count value
 *
 * \brief <b>Example</b><br>
 * \brief This example reads the TIMER21 count value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 timer_ticks;
 *
 *     timer_ticks = TIMER21_Get_Count();  
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER21_api
 */
INLINE uint16 TIMER21_Get_Count(void);

/** \brief Reads the TIMER21 capture value
 *
 * \return TIMER21 capture value
 *
 * \brief <b>Example</b><br>
 * \brief This example reads the TIMER21 capture value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 timer_ticks;
 *  
 *     timer_ticks = TIMER21_Get_Capture();  
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE uint16 TIMER21_Get_Capture(void);

/** \brief Clears the TIMER21 count value
 *
 * \brief <b>Example</b><br>
 * \brief This example stops and reset TIMER21 by software.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {  
 *     TIMER21_Stop();
 *     TIMER21_Clear_Count();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER21_Clear_Count(void);

/** \brief Sets TIMER21 reload value
 *
 * \param value reload value in ticks
 *
 * \brief <b>Example</b><br>
 * \brief This example sets TIMER21 Reload Value to 5000 ticks.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_Mode_Reload_Set();
 *     TIMER21_Set_Reload(0x1388);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER21_Set_Reload(uint16 value);

/** \brief Sets TIMER21 T21IN Pin
 *
 * \param pinsel T21IN Pin select, see \link TTIMER21_T21IN_Pxx \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example sets TIMER2 Input to T21_1(P1.2).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_Select_T21IN(TIMER21_T21IN_P12);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER21_Select_T21IN(TTIMER21_T21IN_Pxx pinsel);

/** \brief Sets TIMER21 T21EX Pin
 *
 * \param pinsel T21EX Pin select, see \link TTIMER21_T21EX_Pxx \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example sets TIMER2 External Input to T21EX_0(P0.2).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     TIMER21_Select_T21EX(TIMER21_T21EX_P02);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup TIMER2x_api
 */
INLINE void TIMER21_Select_T21EX(TTIMER21_T21EX_Pxx pinsel);

/*******************************************************************************
**                         Inline Function Definitions                        **
*******************************************************************************/
INLINE void TIMER2_Clk_Prescaler_En()
{
  Field_Mod32(&TIMER2->MOD.reg, (uint8)TIMER2_MOD_PREN_Pos, TIMER2_MOD_PREN_Msk, 1u);
}

INLINE void TIMER2_Clk_Prescaler_Dis()
{
  Field_Mod32(&TIMER2->MOD.reg, (uint8)TIMER2_MOD_PREN_Pos, TIMER2_MOD_PREN_Msk, 0u);
}

INLINE void TIMER2_Clk_Prescaler_Sel(uint8 t2pre)
{
  Field_Mod32(&TIMER2->MOD.reg, (uint8)TIMER2_MOD_T2PRE_Pos, TIMER2_MOD_T2PRE_Msk, (uint32)t2pre);
}

INLINE uint8 TIMER2_Clk_Prescaler_Get()
{
  return(u8_Field_Rd32(&TIMER2->MOD.reg, (uint8)TIMER2_MOD_T2PRE_Pos, TIMER2_MOD_T2PRE_Msk));
}

INLINE uint8 TIMER2_Overflow_Sts()
{
  return(u1_Field_Rd32(&TIMER2->CON.reg, (uint8)TIMER2_CON_TF2_Pos, TIMER2_CON_TF2_Msk));
}

INLINE uint8 TIMER2_External_Sts()
{
  return(u1_Field_Rd32(&TIMER2->CON.reg, (uint8)TIMER2_CON_EXF2_Pos, TIMER2_CON_EXF2_Msk));
}

INLINE void TIMER2_ExternalCtrl_En()
{
  Field_Mod32(&TIMER2->CON.reg, (uint8)TIMER2_CON_EXEN2_Pos, TIMER2_CON_EXEN2_Msk, 1u);
}

INLINE void TIMER2_ExternalCtrl_Dis()
{
  Field_Mod32(&TIMER2->CON.reg, (uint8)TIMER2_CON_EXEN2_Pos, TIMER2_CON_EXEN2_Msk, 0u);
}

INLINE void TIMER2_Reload_Capture_RisingEdge_Set()
{
  Field_Mod32(&TIMER2->MOD.reg, (uint8)TIMER2_MOD_EDGESEL_Pos, TIMER2_MOD_EDGESEL_Msk, 1u);
}

INLINE void TIMER2_Reload_Capture_FallingEdge_Set()                                    
{
  Field_Mod32(&TIMER2->MOD.reg, (uint8)TIMER2_MOD_EDGESEL_Pos, TIMER2_MOD_EDGESEL_Msk, 0u);
}

INLINE void TIMER2_ExtStart_RisingEdge_Set()
{
  Field_Mod32(&TIMER2->MOD.reg, (uint8)TIMER2_MOD_T2REGS_Pos, TIMER2_MOD_T2REGS_Msk, 1u);
}

INLINE void TIMER2_ExtStart_FallingEdge_Set()
{
  Field_Mod32(&TIMER2->MOD.reg, (uint8)TIMER2_MOD_T2REGS_Pos, TIMER2_MOD_T2REGS_Msk, 0u);
}

INLINE void TIMER2_UpDownCount_En()
{
  Field_Mod32(&TIMER2->MOD.reg, (uint8)TIMER2_MOD_DCEN_Pos, TIMER2_MOD_DCEN_Msk, 1u);
}
  
INLINE void TIMER2_UpDownCount_Dis()
{
  Field_Mod32(&TIMER2->MOD.reg, (uint8)TIMER2_MOD_DCEN_Pos, TIMER2_MOD_DCEN_Msk, 0u);
}

INLINE void TIMER2_Mode_Capture_Set()
{
  Field_Mod32(&TIMER2->CON.reg, (uint8)TIMER2_CON_CP_RL2_Pos, TIMER2_CON_CP_RL2_Msk, 1u);
}

INLINE void TIMER2_Mode_Reload_Set()
{
  Field_Mod32(&TIMER2->CON.reg, (uint8)TIMER2_CON_CP_RL2_Pos, TIMER2_CON_CP_RL2_Msk, 0u);
}

INLINE void TIMER2_Mode_Counter_Set()
{
  Field_Mod32(&TIMER2->CON.reg, (uint8)TIMER2_CON_C_T2_Pos, TIMER2_CON_C_T2_Msk, 1u);
}

INLINE void TIMER2_Mode_Timer_Set()
{
  Field_Mod32(&TIMER2->CON.reg, (uint8)TIMER2_CON_C_T2_Pos, TIMER2_CON_C_T2_Msk, 0u);
}

INLINE void TIMER2_Value_Set(uint16 t2)
{
  Field_Wrt32(&TIMER2->CNT.reg, (uint8)TIMER2_CNT_T2L_Pos, TIMER2_CNT_T2H_Msk | TIMER2_CNT_T2L_Msk, t2);
}

INLINE void TIMER2_Reload_Value_Set(uint16 t2)
{
  Field_Wrt32(&TIMER2->RC.reg, (uint8)TIMER2_RC_RCL2_Pos, TIMER2_RC_RCH2_Msk | TIMER2_RC_RCL2_Msk, t2);
}

INLINE void TIMER2_Overflow_Int_Clr()
{
  Field_Wrt32(&TIMER2->ICLR.reg, (uint8)TIMER2_ICLR_TF2CLR_Pos, TIMER2_ICLR_TF2CLR_Msk, 1u);
}

INLINE void TIMER2_External_Int_Clr()
{
  Field_Wrt32(&TIMER2->ICLR.reg, (uint8)TIMER2_ICLR_EXF2CLR_Pos, TIMER2_ICLR_EXF2CLR_Msk, 1u);
}

INLINE void TIMER2_Overflow_Int_En()
{
  Field_Mod32(&TIMER2->CON1.reg, (uint8)TIMER2_CON1_TF2EN_Pos, TIMER2_CON1_TF2EN_Msk, 1u);
}

INLINE void TIMER2_Overflow_Int_Dis()
{
  Field_Mod32(&TIMER2->CON1.reg, (uint8)TIMER2_CON1_TF2EN_Pos, TIMER2_CON1_TF2EN_Msk, 0u);
}

INLINE void TIMER2_External_Int_En()
{
  Field_Mod32(&TIMER2->CON1.reg, (uint8)TIMER2_CON1_EXF2EN_Pos, TIMER2_CON1_EXF2EN_Msk, 1u);
}

INLINE void TIMER2_External_Int_Dis()
{
  Field_Mod32(&TIMER2->CON1.reg, (uint8)TIMER2_CON1_EXF2EN_Pos, TIMER2_CON1_EXF2EN_Msk, 0u);
}

INLINE void TIMER21_Clk_Prescaler_En()
{
  Field_Mod32(&TIMER21->MOD.reg, (uint8)TIMER21_MOD_PREN_Pos, TIMER21_MOD_PREN_Msk, 1u);
}

INLINE void TIMER21_Clk_Prescaler_Dis()
{
  Field_Mod32(&TIMER21->MOD.reg, (uint8)TIMER21_MOD_PREN_Pos, TIMER21_MOD_PREN_Msk, 0u);
}

INLINE void TIMER21_Clk_Prescaler_Sel(uint8 t21pre)
{
  Field_Mod32(&TIMER21->MOD.reg, (uint8)TIMER21_MOD_T2PRE_Pos, TIMER21_MOD_T2PRE_Msk, (uint32)t21pre);
}

INLINE uint8 TIMER21_Clk_Prescaler_Get()
{
  return(u8_Field_Rd32(&TIMER21->MOD.reg, (uint8)TIMER21_MOD_T2PRE_Pos, TIMER21_MOD_T2PRE_Msk));
}

INLINE uint8 TIMER21_Overflow_Sts()
{
  return(u1_Field_Rd32(&TIMER21->CON.reg, (uint8)TIMER21_CON_TF2_Pos, TIMER21_CON_TF2_Msk));
}

INLINE uint8 TIMER21_External_Sts()
{
  return(u1_Field_Rd32(&TIMER21->CON.reg, (uint8)TIMER21_CON_EXF2_Pos, TIMER21_CON_EXF2_Msk));
}

INLINE void TIMER21_ExternalCtrl_En()
{
  Field_Mod32(&TIMER21->CON.reg, (uint8)TIMER21_CON_EXEN2_Pos, TIMER21_CON_EXEN2_Msk, 1u);
}

INLINE void TIMER21_ExternalCtrl_Dis()
{
  Field_Mod32(&TIMER21->CON.reg, (uint8)TIMER21_CON_EXEN2_Pos, TIMER21_CON_EXEN2_Msk, 0u);
}

INLINE void TIMER21_Reload_Capture_RisingEdge_Set()                                  
{
  Field_Mod32(&TIMER21->MOD.reg, (uint8)TIMER21_MOD_EDGESEL_Pos, TIMER21_MOD_EDGESEL_Msk, 1u);
}

INLINE void TIMER21_Reload_Capture_FallingEdge_Set()                                      
{
  Field_Mod32(&TIMER21->MOD.reg, (uint8)TIMER21_MOD_EDGESEL_Pos, TIMER21_MOD_EDGESEL_Msk, 0u);
}

INLINE void TIMER21_ExtStart_RisingEdge_Set()
{
  Field_Mod32(&TIMER21->MOD.reg, (uint8)TIMER21_MOD_T2REGS_Pos, TIMER21_MOD_T2REGS_Msk, 1u);
}

INLINE void TIMER21_ExtStart_FallingEdge_Set()
{
  Field_Mod32(&TIMER21->MOD.reg, (uint8)TIMER21_MOD_T2REGS_Pos, TIMER21_MOD_T2REGS_Msk, 0u);
}

INLINE void TIMER21_UpDownCount_En()
{
  Field_Mod32(&TIMER21->MOD.reg, (uint8)TIMER21_MOD_DCEN_Pos, TIMER21_MOD_DCEN_Msk, 1u);
}

INLINE void TIMER21_UpDownCount_Dis()
{
  Field_Mod32(&TIMER21->MOD.reg, (uint8)TIMER21_MOD_DCEN_Pos, TIMER21_MOD_DCEN_Msk, 0u);
}

INLINE void TIMER21_Mode_Capture_Set()
{
  Field_Mod32(&TIMER21->CON.reg, (uint8)TIMER21_CON_CP_RL2_Pos, TIMER21_CON_CP_RL2_Msk, 1u);
}

INLINE void TIMER21_Mode_Reload_Set()
{
  Field_Mod32(&TIMER21->CON.reg, (uint8)TIMER21_CON_CP_RL2_Pos, TIMER21_CON_CP_RL2_Msk, 0u);
}

INLINE void TIMER21_Mode_Counter_Set()
{
  Field_Mod32(&TIMER21->CON.reg, (uint8)TIMER21_CON_C_T2_Pos, TIMER21_CON_C_T2_Msk, 1u);
}

INLINE void TIMER21_Mode_Timer_Set()
{
  Field_Mod32(&TIMER21->CON.reg, (uint8)TIMER21_CON_C_T2_Pos, TIMER21_CON_C_T2_Msk, 0u);
}

INLINE void TIMER21_Value_Set(uint16 t21)
{
  Field_Wrt32(&TIMER21->CNT.reg, (uint8)TIMER21_CNT_T2L_Pos, TIMER21_CNT_T2H_Msk | TIMER21_CNT_T2L_Msk, t21);
}

INLINE void TIMER21_Reload_Value_Set(uint16 t21)
{
  Field_Wrt32(&TIMER21->RC.reg, (uint8)TIMER21_RC_RCL2_Pos, TIMER21_RC_RCH2_Msk | TIMER21_RC_RCL2_Msk, t21);
}

INLINE void TIMER21_Overflow_Int_Clr()
{
  Field_Wrt32(&TIMER21->ICLR.reg, (uint8)TIMER21_ICLR_TF2CLR_Pos, TIMER21_ICLR_TF2CLR_Msk, 1u);
}

INLINE void TIMER21_External_Int_Clr()
{
  Field_Wrt32(&TIMER21->ICLR.reg, (uint8)TIMER21_ICLR_EXF2CLR_Pos, TIMER21_ICLR_EXF2CLR_Msk, 1u);
}

INLINE void TIMER21_Overflow_Int_En()
{
  Field_Mod32(&TIMER21->CON1.reg, (uint8)TIMER21_CON1_TF2EN_Pos, TIMER21_CON1_TF2EN_Msk, 1u);
}

INLINE void TIMER21_Overflow_Int_Dis()
{
  Field_Mod32(&TIMER21->CON1.reg, (uint8)TIMER21_CON1_TF2EN_Pos, TIMER21_CON1_TF2EN_Msk, 0u);
}

INLINE void TIMER21_External_Int_En()
{
  Field_Mod32(&TIMER21->CON1.reg, (uint8)TIMER21_CON1_EXF2EN_Pos, TIMER21_CON1_EXF2EN_Msk, 1u);
}

INLINE void TIMER21_External_Int_Dis()
{
  Field_Mod32(&TIMER21->CON1.reg, (uint8)TIMER21_CON1_EXF2EN_Pos, TIMER21_CON1_EXF2EN_Msk, 0u);
}

INLINE void TIMER2_Start(void)
{
  Field_Mod32(&TIMER2->CON.reg, (uint8)TIMER2_CON_TR2_Pos, TIMER2_CON_TR2_Msk, 1u);
}

INLINE void TIMER2_Stop(void)
{
  Field_Mod32(&TIMER2->CON.reg, (uint8)TIMER2_CON_TR2_Pos, TIMER2_CON_TR2_Msk, 0u);  
}

INLINE void TIMER2_ExtStart(void)
{
  Field_Mod32(&TIMER2->MOD.reg, (uint8)TIMER2_MOD_T2RHEN_Pos, TIMER2_MOD_T2RHEN_Msk, 1u);  
}

INLINE void TIMER2_ExtStop(void)
{
  Field_Mod32(&TIMER2->MOD.reg, (uint8)TIMER2_MOD_T2RHEN_Pos, TIMER2_MOD_T2RHEN_Msk, 0u);  
}

INLINE uint16 TIMER2_Get_Count(void)
{
  return(u16_Field_Rd32(&TIMER2->CNT.reg, (uint8)0x00, 0xFFFF));  
}

INLINE uint16 TIMER2_Get_Capture(void)
{
  return(u16_Field_Rd32(&TIMER2->RC.reg, (uint8)0x00, 0xFFFF));  
}

INLINE void TIMER2_Clear_Count(void)
{
  Field_Clr32(&TIMER2->CNT.reg, (uint32)0xFFFF);  
}

INLINE void TIMER2_Set_Reload(uint16 value)
{
  Field_Wrt32(&TIMER2->RC.reg, (uint8)0x00, 0xFFFF, (uint16)value);    
}

INLINE void TIMER2_Select_T2IN(TTIMER2_T2IN_Pxx pinsel)
{
  Field_Mod32(&SCU->MODPISEL2.reg, (uint8)SCU_MODPISEL2_T2IS_Pos, SCU_MODPISEL2_T2IS_Msk, (uint32)pinsel);    
}

INLINE void TIMER2_Select_T2EX(TTIMER2_T2EX_Pxx pinsel)
{
    Field_Mod32(&SCU->MODPISEL2.reg, (uint8)SCU_MODPISEL2_T2EXIS_Pos, SCU_MODPISEL2_T2EXIS_Msk, ((uint32)pinsel & 0x3u));
    Field_Mod32(&SCU->MODPISEL2.reg, (uint8)SCU_MODPISEL2_T2EXISCNF_Pos, SCU_MODPISEL2_T2EXISCNF_Msk, (((uint32)pinsel & 0xCu) >> 2u));
}

INLINE void TIMER21_Start(void)
{
  Field_Mod32(&TIMER21->CON.reg, (uint8)TIMER21_CON_TR2_Pos, TIMER21_CON_TR2_Msk, 1u);  
}

INLINE void TIMER21_Stop(void)
{
  Field_Mod32(&TIMER21->CON.reg, (uint8)TIMER21_CON_TR2_Pos, TIMER21_CON_TR2_Msk, 0u);  
}

INLINE void TIMER21_ExtStart(void)
{
  Field_Mod32(&TIMER21->MOD.reg, (uint8)TIMER21_MOD_T2RHEN_Pos, TIMER21_MOD_T2RHEN_Msk, 1u);  
}

INLINE void TIMER21_ExtStop(void)
{
  Field_Mod32(&TIMER21->MOD.reg, (uint8)TIMER21_MOD_T2RHEN_Pos, TIMER21_MOD_T2RHEN_Msk, 0u);  
}

INLINE uint16 TIMER21_Get_Count(void)
{
  return(u16_Field_Rd32(&TIMER21->CNT.reg, (uint8)0x00, 0xFFFF));  
}

INLINE uint16 TIMER21_Get_Capture(void)
{
  return(u16_Field_Rd32(&TIMER21->RC.reg, (uint8)0x00, 0xFFFF));    
}

INLINE void TIMER21_Clear_Count(void)
{
  Field_Clr32(&TIMER21->CNT.reg, (uint32)0xFFFF);    
}

INLINE void TIMER21_Set_Reload(uint16 value)
{
  Field_Wrt32(&TIMER21->RC.reg, (uint8)0x00, 0xFFFF, (uint16)value);  
}

INLINE void TIMER21_Select_T21IN(TTIMER21_T21IN_Pxx pinsel)
{
  Field_Mod32(&SCU->MODPISEL2.reg, (uint8)SCU_MODPISEL2_T21IS_Pos, SCU_MODPISEL2_T21IS_Msk, (uint32)pinsel);    
}

INLINE void TIMER21_Select_T21EX(TTIMER21_T21EX_Pxx pinsel)
{
    Field_Mod32(&SCU->MODPISEL2.reg, (uint8)SCU_MODPISEL2_T21EXIS_Pos, SCU_MODPISEL2_T21EXIS_Msk, ((uint32)pinsel & 0x3u));
    Field_Mod32(&SCU->MODPISEL2.reg, (uint8)SCU_MODPISEL2_T21EXISCNF_Pos, SCU_MODPISEL2_T21EXISCNF_Msk, (((uint32)pinsel & 0xCu) >> 2u));    
}

#endif
