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
 * \file     pmu.h
 *
 * \brief    Power Management Unit low level access library
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
** V0.2.1: 2019-01-28, TS:    __STATIC_INLINE changed to INLINE               **
**                            Doxygen update                                  **
**                            Revision history moved from pmu.c to pmu.h      **
**                            PMU Reset Mask macro added                      **
**                            PMU_VDDEXT_On function updated                  **
**                            PMU_VDDEXT_OT_Int_Clr, PMU_VDDEXT_UV_Int_Clr,   **
**                            PMU_VDDEXT_OT_Clr and PMU_VDDEXT_Error_Clear    **
**                            functions updated                               **
** V0.2.2: 2020-03-02, BG:   Updated revision history format                  **
*******************************************************************************/

#ifndef PMU_H
#define PMU_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle985x.h"
#include "types.h"
#include "sfr_access.h"

/*******************************************************************************
**                          Global Macro Definitions                          **
*******************************************************************************/
/**\brief PMU Reset Status Flag Mask, Lockup-Reset Flag*/
#define PMU_RESET_STS_LOCKUP   (0x0400u)
/**\brief PMU Reset Status Flag Mask, Soft-Reset Flag*/
#define PMU_RESET_STS_PMU_SOFT (0x0200u)
/**\brief PMU Reset Status Flag Mask, Internal Watchdog Reset Flag*/
#define PMU_RESET_STS_IntWDT   (0x0100u)
/**\brief PMU Reset Status Flag Mask, Power-On Reset Flag*/
#define PMU_RESET_STS_POR      (0x0080u)
/**\brief PMU Reset Status Flag Mask, PIN-Reset Flag*/
#define PMU_RESET_STS_PIN      (0x0040u)
/**\brief PMU Reset Status Flag Mask, External Watchdog (WDT1) Reset Flag*/
#define PMU_RESET_STS_WDT1     (0x0020u)
/**\brief PMU Reset Status Flag Mask, Clock Watchdog (CLKWDT) Reset Flag*/
#define PMU_RESET_STS_ClkWDT   (0x0010u)
/**\brief PMU Reset Status Flag Mask, Low Priority Resets*/
#define PMU_RESET_STS_LPR      (0x0008u)
/**\brief PMU Reset Status Flag Mask, Flag which indicates a reset caused by Sleep-Exit*/
#define PMU_RESET_STS_SLEEP    (0x0004u)
/**\brief PMU Reset Status Flag Mask, Flag which indicates a reset caused by Stop-Exit*/
#define PMU_RESET_STS_WAKE     (0x0002u)
/**\brief PMU Reset Status Flag Mask, Flag which indicates a reset caused by a System Fail reported in the corresponding Fail Register*/
#define PMU_RESET_STS_SYS_FAIL (0x0001u)

/**\brief PMU VDDEXT Status Flag Mask, VDDEXT Supply Overtemperature Status clear*/
#define PMU_VDDEXT_OT_SC        (0x2000u)
/**\brief PMU VDDEXT Status Flag Mask, VDDEXT Supply Undervoltage Interrupt Status clear*/
#define PMU_VDDEXT_UV_ISC       (0x1000u)
/**\brief PMU VDDEXT Status Flag Mask, VDDEXT Supply Overtemperature Interrupt Status clear*/
#define PMU_VDDEXT_OT_ISC       (0x0800u)
/**\brief PMU VDDEXT Status Flag Mask, VDDEXT Supply Stable*/
#define PMU_VDDEXT_STABLE       (0x0080u)
/**\brief PMU VDDEXT Status Flag Mask, VDDEXT Supply Overtemperature*/
#define PMU_VDDEXT_OVERTEMP     (0x0040u)
/**\brief PMU VDDEXT Status Flag Mask, VDDEXT Supply Overtemperature Status*/
#define PMU_VDDEXT_OVERTEMPST   (0x0020u)
/**\brief PMU VDDEXT Status Flag Mask, VDDEXT Supply Undervoltage Interrupt Status*/
#define PMU_VDDEXT_UNDERVOLT    (0x0010u)
/**\brief PMU VDDEXT Status Flag Mask, VDDEXT Supply OverTemperature Interrupt Status*/
#define PMU_VDDEXT_OVERTEMPIN   (0x0008u)
/**\brief PMU VDDEXT Status Flag Mask, Enabling of VDDEXT Supply status information as interrupt source*/
#define PMU_VDDEXT_IE           (0x0004u)
/**\brief PMU VDDEXT Status Flag Mask, VDDEXT Supply for Cyclic Sense Enable*/
#define PMU_VDDEXT_CYC_EN       (0x0002u)
/**\brief PMU VDDEXT Status Flag Mask, VDDEXT Supply Enable*/
#define PMU_VDDEXT_ENABLE       (0x0001u)

/**\brief PMU Reset Status Flag Mask */
#define PMU_RESET_MASK       (0x7FFu)

/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/
/** \brief Initializes the PMU module.
 *
 * \ingroup pmu_api
 */
void PMU_Init(void);

/** \brief Turns VDDEXT on.
 *
 * \retval TRUE VDDEXT was turned on
 * \retval FALSE VDDEXT is off, was not turned on
 *
 * \brief <b>Example</b><br>
 * \brief This example switches VDDEXT on and waits until VDDEXT is in stable condition.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   while (PMU_VDDEXT_On() == false)
 *   {
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
bool PMU_VDDEXT_On(void);

/*******************************************************************************
**                        Inline Function Declarations                        **
*******************************************************************************/
/** \brief Enables of VDDEXT Supply status information as interrupt source.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDEXT Supply OverTemperature interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PMU_VDDEXT_Int_En();
 *   if ((uint8)PMU->VDDEXT_CTRL.bit.VDDEXT_OT_IS == (uint8)1)
 *   {
 *     PMU_VDDEXT_OT_CALLBACK();
 *     PMU_VDDEXT_OT_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PMU_VDDEXT_Int_En(void);

/** \brief Disables of VDDEXT Supply status information as interrupt source.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDEXT Supply OverTemperature interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PMU_VDDEXT_Int_En();
 *   if ((uint8)PMU->VDDEXT_CTRL.bit.VDDEXT_OT_IS == (uint8)1)
 *   {
 *     PMU_VDDEXT_OT_CALLBACK();
 *     PMU_VDDEXT_OT_Int_Clr();
 *   }
 *   PMU_VDDEXT_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PMU_VDDEXT_Int_Dis(void);

/** \brief Enables of VDDC status information as interrupt source.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Overvoltage at VDDC regulator interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PMU_VDDC_Int_En();
 *   if ((uint8)PMU->SUPPLY_STS.bit.PMU_1V5_OVERVOLT == (uint8)1)
 *   {
 *     PMU_VDDC_OV_CALLBACK();
 *     PMU_VDDC_OV_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PMU_VDDC_Int_En(void);

/** \brief Disables of VDDC status information as interrupt source.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Overvoltage at VDDC regulator interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PMU_VDDC_Int_En();
 *   if ((uint8)PMU->SUPPLY_STS.bit.PMU_1V5_OVERVOLT == (uint8)1)
 *   {
 *     PMU_VDDC_OV_CALLBACK();
 *     PMU_VDDC_OV_Clr();
 *   }
 *   PMU_VDDC_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PMU_VDDC_Int_Dis(void);

/** \brief Enables of VDDP status information as interrupt source.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Overvoltage at VDDP regulator interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PMU_VDDP_Int_En();
 *   if ((uint8)PMU->SUPPLY_STS.bit.PMU_5V_OVERVOLT == (uint8)1)
 *   {
 *     PMU_VDDP_OV_CALLBACK();
 *     PMU_VDDP_OV_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PMU_VDDP_Int_En(void);

/** \brief Disables of VDDP status information as interrupt source.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Overvoltage at VDDP regulator interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PMU_VDDP_Int_En();
 *   if ((uint8)PMU->SUPPLY_STS.bit.PMU_5V_OVERVOLT == (uint8)1)
 *   {
 *     PMU_VDDP_OV_CALLBACK();
 *     PMU_VDDP_OV_Clr();
 *   }
 *   PMU_VDDP_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PMU_VDDP_Int_Dis(void);

/** \brief Enables PMU Overtemperature Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the PMU Overtemperature Interrupt
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PMU_OT_Int_En();
 *   if (u1_Field_Rd32(&PMU->SUPPLY_STS.reg, (uint8)PMU_SUPPLY_STS_PMU_OVERTEMP_Pos, PMU_SUPPLY_STS_PMU_OVERTEMP_Msk) == (uint8)1)
 *   {
 *     PMU_PMU_OT_CALLBACK();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PMU_OT_Int_En(void);

/** \brief Disables PMU Overtemperature Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the PMU Overtemperature Interrupt
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PMU_OT_Int_En();
 *   if (u1_Field_Rd32(&PMU->SUPPLY_STS.reg, (uint8)PMU_SUPPLY_STS_PMU_OVERTEMP_Pos, PMU_SUPPLY_STS_PMU_OVERTEMP_Msk) == (uint8)1)
 *   {
 *     PMU_PMU_OT_CALLBACK();
 *   }
 *   PMU_OT_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PMU_OT_Int_Dis(void);

/** \brief Clears VDDEXT Supply OverTemperature interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDEXT Supply OverTemperature interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PMU_VDDEXT_Int_En();
 *   if ((uint8)PMU->VDDEXT_CTRL.bit.VDDEXT_OT_IS == (uint8)1)
 *   {
 *     PMU_VDDEXT_OT_CALLBACK();
 *     PMU_VDDEXT_OT_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PMU_VDDEXT_OT_Int_Clr(void);

/** \brief Clears VDDEXT Supply Undervoltage interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDEXT Supply Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PMU_VDDEXT_Int_En();
 *   if ((uint8)PMU->VDDEXT_CTRL.bit.VDDEXT_UV_IS == (uint8)1)
 *   {
 *     PMU_VDDEXT_UV_CALLBACK();
 *     PMU_VDDEXT_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PMU_VDDEXT_UV_Int_Clr(void);

/** \brief Clears VDDEXT Supply Overvoltage Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears the VDDEXT Supply Overvoltage Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PMU_VDDEXT_OT_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PMU_VDDEXT_OT_Clr(void);

/** \brief Clears Overvoltage at VDDC regulator flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Overvoltage at VDDC regulator interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PMU_VDDC_Int_En();
 *   if ((uint8)PMU->SUPPLY_STS.bit.PMU_1V5_OVERVOLT == (uint8)1)
 *   {
 *     PMU_VDDC_OV_CALLBACK();
 *     PMU_VDDC_OV_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PMU_VDDC_OV_Clr(void);

/** \brief Clears Overload at VDDC regulator flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Overload at VDDC regulator interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PMU_VDDC_Int_En();
 *   if ((uint8)PMU->SUPPLY_STS.bit.PMU_1V5_OVERLOAD == (uint8)1)
 *   {
 *     PMU_VDDC_OL_CALLBACK();
 *     PMU_VDDC_OL_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PMU_VDDC_OL_Clr(void);

/** \brief Clears Overvoltage at VDDP regulator flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Overvoltage at VDDP regulator interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PMU_VDDP_Int_En();
 *   if ((uint8)PMU->SUPPLY_STS.bit.PMU_5V_OVERVOLT == (uint8)1)
 *   {
 *     PMU_VDDP_OV_CALLBACK();
 *     PMU_VDDP_OV_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PMU_VDDP_OV_Clr(void);

/** \brief Clears Overload at VDDP regulator flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Overload at VDDP regulator interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PMU_VDDP_Int_En();
 *   if ((uint8)PMU->SUPPLY_STS.bit.PMU_5V_OVERLOAD == (uint8)1)
 *   {
 *     PMU_VDDP_OL_CALLBACK();
 *     PMU_VDDP_OL_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PMU_VDDP_OL_Clr(void);


/** \brief Clears Overtemperature Status flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the PMU Overtemperature interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   if ((uint8)PMU->SUPPLY_STS.bit.PMU_OVERTEMP == (uint8)1)
 *   {
 *     PMU_PMU_OT_CALLBACK();
 *     PMU_PMU_OT_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PMU_PMU_OT_Clr(void);
  
/** \brief Enables Wakeup Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Wakeup Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   WAKEUP_Int_En();
 *   if ((uint8)SCU->IRCON5.bit.WAKEUP == (uint8)1)
 *   {
 *     PMU_WAKEUP_CALLBACK();
 *     WAKEUP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void WAKEUP_Int_En(void);

/** \brief Disables Wakeup Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Wakeup Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   WAKEUP_Int_En();
 *   if ((uint8)SCU->IRCON5.bit.WAKEUP == (uint8)1)
 *   {
 *     PMU_WAKEUP_CALLBACK();
 *     WAKEUP_Int_Clr();
 *   }
 *   WAKEUP_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void WAKEUP_Int_Dis(void);

/** \brief Clears Wakeup Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Wakeup Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   WAKEUP_Int_En();
 *   if ((uint8)SCU->IRCON5.bit.WAKEUP == (uint8)1)
 *   {
 *     PMU_WAKEUP_CALLBACK();
 *     WAKEUP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void WAKEUP_Int_Clr(void);

/** \brief Enables Loss of Clock Reset.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Loss of Clock Reset.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PCU_CLK_Loss_Rst_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PCU_CLK_Loss_Rst_En(void);

/** \brief Disables Loss of Clock Reset.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Loss of Clock Reset.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PCU_CLK_Loss_Rst_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PCU_CLK_Loss_Rst_Dis(void);

/** \brief Enables Clock Watchdog Reset.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Clock Watchdog Reset.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PCU_CLKWDT_Rst_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PCU_CLKWDT_Rst_En(void);

/** \brief Disables Clock Watchdog Reset.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Clock Watchdog Reset.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PCU_CLKWDT_Rst_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PCU_CLKWDT_Rst_Dis(void);

/** \brief Enables System Loss of Clock Shutdown.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables System Loss of Clock Shutdown.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PCU_CLK_Loss_SD_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PCU_CLK_Loss_SD_En(void);

/** \brief Disables System Loss of Clock Shutdown.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables System Loss of Clock Shutdown.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PCU_CLK_Loss_SD_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PCU_CLK_Loss_SD_Dis(void);

/** \brief Enables System Overtemperature Warning Power Switches Shutdown.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables System Overtemperature Warning Power Switches Shutdown.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PCU_SYS_OTWARN_PS_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PCU_SYS_OTWARN_PS_En(void);

/** \brief Disables System Overtemperature Warning Power Switches Shutdown.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables System Overtemperature Warning Power Switches Shutdown.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PCU_SYS_OTWARN_PS_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PCU_SYS_OTWARN_PS_Dis(void);

/** \brief Enables VS Overvoltage Shutdown for peripherals.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables VS Overvoltage Shutdown for peripherals.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PCU_SYS_VS_OV_SLM_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PCU_SYS_VS_OV_SLM_En(void);

/** \brief Disables VS Overvoltage Shutdown for peripherals.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables VS Overvoltage Shutdown for peripherals.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PCU_SYS_VS_OV_SLM_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PCU_SYS_VS_OV_SLM_Dis(void);

/** \brief Enables VS Undervoltage Shutdown for peripherals.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables VS Undervoltage Shutdown for peripherals.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PCU_SYS_VS_UV_SLM_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PCU_SYS_VS_UV_SLM_En(void);

/** \brief Disables VS Undervoltage Shutdown for peripherals.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables VS Undervoltage Shutdown for peripherals.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PCU_SYS_VS_UV_SLM_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PCU_SYS_VS_UV_SLM_Dis(void);

/** \brief Enables LIN Module VS Undervoltage Transmitter Shutdown.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables LIN Module VS Undervoltage Transmitter Shutdown.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PCU_LIN_VS_UV_SD_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PCU_LIN_VS_UV_SD_En(void);

/** \brief Disables LIN Module VS Undervoltage Transmitter Shutdown.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables LIN Module VS Undervoltage Transmitter Shutdown.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PCU_LIN_VS_UV_SD_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PCU_LIN_VS_UV_SD_Dis(void);

/** \brief Enables LIN Tx and HS Switch off.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables LIN Tx and HS Switch off.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PCU_FAIL_PS_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PCU_FAIL_PS_En(void);

/** \brief Disables LIN Tx and HS Switch off.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables LIN Tx and HS Switch off.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PCU_FAIL_PS_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PCU_FAIL_PS_Dis(void);

/** \brief Enables Power Modules Clock Watchdog Shutdown.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Power Modules Clock Watchdog Shutdown.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PCU_CLKWDT_SD_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PCU_CLKWDT_SD_En(void);

/** \brief Disables Power Modules Clock Watchdog Shutdown.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Power Modules Clock Watchdog Shutdown.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PCU_CLKWDT_SD_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PCU_CLKWDT_SD_Dis(void);

/** \brief Reads out the Reset Status register
 *
 * \return combination of reset status bits
 *
 * \brief <b>Example</b><br>
 * \brief This example checks and clears Reset Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   if (PMU_Get_Reset_Status() != (uint16)0)
 *   {
 *     PMU_Clear_Reset_Status();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE uint16 PMU_Get_Reset_Status(void);

/** \brief Clears the Reset Status register
 *
 * \brief <b>Example</b><br>
 * \brief This example checks and clears Reset Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   if (PMU_Get_Reset_Status() != (uint16)0)
 *   {
 *     PMU_Clear_Reset_Status();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PMU_Clear_Reset_Status(void);

/** \brief Switches VDDEXT off and reads the stability Status of VDDEXT
 *
 * \retval 0 VDDEXT not in stable condition
 * \retval 1 VDDEXT in stable condition
 *
 * \brief <b>Example</b><br>
 * \brief This example switches VDDEXT off and waits until VDDEXT is in stable condition.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   while (PMU_VDDEXT_Off() == (uint8)0)
 *   {
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE uint8 PMU_VDDEXT_Off(void);

/** \brief Clears VDDEXT Error Flags
 *
 * \param ErrorFlagMask VDDEXT Error Flags Mask
 *
 * \brief <b>Example</b><br>
 * \brief This example clears VDDEXT Supply Undervoltage Interrupt flag.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PMU_VDDEXT_Error_Clear(PMU_VDDEXT_UV_ISC);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PMU_VDDEXT_Error_Clear(uint16 ErrorFlagMask);

/** \brief Sets the given bits in the PMU->VDDEXT_CTRL register
 *
 * \param FlagMask VDDEXT Flags Mask
 *
 * \brief <b>Example</b><br>
 * \brief This example enables VVDDEXT Supply status information as interrupt source.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   PMU_VDDEXT_Set(PMU_VDDEXT_ENABLE);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup pmu_api
 */
INLINE void PMU_VDDEXT_Set(uint16 FlagMask);

/*******************************************************************************
**                         Inline Function Definitions                        **
*******************************************************************************/
INLINE void PMU_VDDEXT_Int_En()
{
  Field_Mod32(&PMU->VDDEXT_CTRL.reg, (uint8)PMU_VDDEXT_CTRL_VDDEXT_FAIL_EN_Pos, PMU_VDDEXT_CTRL_VDDEXT_FAIL_EN_Msk, 1u);
}

INLINE void PMU_VDDEXT_Int_Dis()
{
  Field_Mod32(&PMU->VDDEXT_CTRL.reg, (uint8)PMU_VDDEXT_CTRL_VDDEXT_FAIL_EN_Pos, PMU_VDDEXT_CTRL_VDDEXT_FAIL_EN_Msk, 0u);
}

INLINE void PMU_VDDC_Int_En()
{
  Field_Mod32(&PMU->SUPPLY_STS.reg, (uint8)PMU_SUPPLY_STS_PMU_1V5_FAIL_EN_Pos, PMU_SUPPLY_STS_PMU_1V5_FAIL_EN_Msk, 1u);
}

INLINE void PMU_VDDC_Int_Dis()
{
  Field_Mod32(&PMU->SUPPLY_STS.reg, (uint8)PMU_SUPPLY_STS_PMU_1V5_FAIL_EN_Pos, PMU_SUPPLY_STS_PMU_1V5_FAIL_EN_Msk, 0u);
}

INLINE void PMU_VDDP_Int_En()
{
  Field_Mod32(&PMU->SUPPLY_STS.reg, (uint8)PMU_SUPPLY_STS_PMU_5V_FAIL_EN_Pos, PMU_SUPPLY_STS_PMU_5V_FAIL_EN_Msk, 1u);
}

INLINE void PMU_VDDP_Int_Dis()
{
  Field_Mod32(&PMU->SUPPLY_STS.reg, (uint8)PMU_SUPPLY_STS_PMU_5V_FAIL_EN_Pos, PMU_SUPPLY_STS_PMU_5V_FAIL_EN_Msk, 0u);
}

INLINE void PMU_OT_Int_En()    
{
  Field_Mod32(&PMU->OT_CTRL.reg, (uint8)PMU_OT_CTRL_PMU_OT_INT_EN_Pos, PMU_OT_CTRL_PMU_OT_INT_EN_Msk, 1u);
}

INLINE void PMU_OT_Int_Dis()  
{
  Field_Mod32(&PMU->OT_CTRL.reg, (uint8)PMU_OT_CTRL_PMU_OT_INT_EN_Pos, PMU_OT_CTRL_PMU_OT_INT_EN_Msk, 0u);
}

INLINE void PMU_VDDEXT_OT_Int_Clr()
{
  Field_Mod32(&PMU->VDDEXT_CTRL.reg, (uint8)PMU_VDDEXT_CTRL_VDDEXT_OT_ISC_Pos, PMU_VDDEXT_CTRL_VDDEXT_OT_ISC_Msk, 1u);  
}

INLINE void PMU_VDDEXT_UV_Int_Clr()
{
  Field_Mod32(&PMU->VDDEXT_CTRL.reg, (uint8)PMU_VDDEXT_CTRL_VDDEXT_UV_ISC_Pos, PMU_VDDEXT_CTRL_VDDEXT_UV_ISC_Msk, 1u);  
}

INLINE void PMU_VDDEXT_OT_Clr()
{
  Field_Mod32(&PMU->VDDEXT_CTRL.reg, (uint8)PMU_VDDEXT_CTRL_VDDEXT_OT_SC_Pos, PMU_VDDEXT_CTRL_VDDEXT_OT_SC_Msk, 1u);
}

INLINE void PMU_VDDC_OV_Clr()
{
  Field_Mod32(&PMU->SUPPLY_STS.reg, (uint8)PMU_SUPPLY_STS_PMU_1V5_OVERVOLT_SC_Pos, PMU_SUPPLY_STS_PMU_1V5_OVERVOLT_SC_Msk, 1u);  
}

INLINE void PMU_VDDC_OL_Clr()
{
  Field_Mod32(&PMU->SUPPLY_STS.reg, (uint8)PMU_SUPPLY_STS_PMU_1V5_OVERLOAD_SC_Pos, PMU_SUPPLY_STS_PMU_1V5_OVERLOAD_SC_Msk, 1u);  
}

INLINE void PMU_VDDP_OV_Clr()
{
  Field_Mod32(&PMU->SUPPLY_STS.reg, (uint8)PMU_SUPPLY_STS_PMU_5V_OVERVOLT_SC_Pos, PMU_SUPPLY_STS_PMU_5V_OVERVOLT_SC_Msk, 1u);  
}

INLINE void PMU_VDDP_OL_Clr()
{
  Field_Mod32(&PMU->SUPPLY_STS.reg, (uint8)PMU_SUPPLY_STS_PMU_5V_OVERLOAD_SC_Pos, PMU_SUPPLY_STS_PMU_5V_OVERLOAD_SC_Msk, 1u);  
}

INLINE void PMU_PMU_OT_Clr()
{
  Field_Mod32(&PMU->SUPPLY_STS.reg, (uint8)PMU_SUPPLY_STS_PMU_OVERTEMP_SC_Pos, PMU_SUPPLY_STS_PMU_OVERTEMP_SC_Msk, 1u);  
}

INLINE void WAKEUP_Int_En()
{
  Field_Wrt32(&SCU->WAKECON.reg, (uint8)SCU_WAKECON_WAKEUPEN_Pos, SCU_WAKECON_WAKEUPEN_Msk, 1u);
}

INLINE void WAKEUP_Int_Dis()
{
  Field_Wrt32(&SCU->WAKECON.reg, (uint8)SCU_WAKECON_WAKEUPEN_Pos, SCU_WAKECON_WAKEUPEN_Msk, 0u);
}

INLINE void WAKEUP_Int_Clr()
{
  Field_Wrt32(&SCU->IRCON5CLR.reg, (uint8)SCU_IRCON5CLR_WAKEUPC_Pos, SCU_IRCON5CLR_WAKEUPC_Msk, 1u);
}

INLINE void PCU_CLK_Loss_Rst_En()
{
  Field_Mod32(&SCUPM->PCU_CTRL_STS.reg, (uint8)SCUPM_PCU_CTRL_STS_CLKLOSS_RES_SD_DIS_Pos, SCUPM_PCU_CTRL_STS_CLKLOSS_RES_SD_DIS_Msk, 0u);
}

INLINE void PCU_CLK_Loss_Rst_Dis()
{
  Field_Mod32(&SCUPM->PCU_CTRL_STS.reg, (uint8)SCUPM_PCU_CTRL_STS_CLKLOSS_RES_SD_DIS_Pos, SCUPM_PCU_CTRL_STS_CLKLOSS_RES_SD_DIS_Msk, 1u);
}

INLINE void PCU_CLKWDT_Rst_En()
{
  Field_Mod32(&SCUPM->PCU_CTRL_STS.reg, (uint8)SCUPM_PCU_CTRL_STS_CLKWDT_RES_SD_DIS_Pos, SCUPM_PCU_CTRL_STS_CLKWDT_RES_SD_DIS_Msk, 0u);
}

INLINE void PCU_CLKWDT_Rst_Dis()
{
  Field_Mod32(&SCUPM->PCU_CTRL_STS.reg, (uint8)SCUPM_PCU_CTRL_STS_CLKWDT_RES_SD_DIS_Pos, SCUPM_PCU_CTRL_STS_CLKWDT_RES_SD_DIS_Msk, 1u);
}

INLINE void PCU_CLK_Loss_SD_En()
{
  Field_Mod32(&SCUPM->PCU_CTRL_STS.reg, (uint8)SCUPM_PCU_CTRL_STS_CLKLOSS_SD_DIS_Pos, SCUPM_PCU_CTRL_STS_CLKLOSS_SD_DIS_Msk, 0u);
}

INLINE void PCU_CLK_Loss_SD_Dis()
{
  Field_Mod32(&SCUPM->PCU_CTRL_STS.reg, (uint8)SCUPM_PCU_CTRL_STS_CLKLOSS_SD_DIS_Pos, SCUPM_PCU_CTRL_STS_CLKLOSS_SD_DIS_Msk, 1u);
}

INLINE void PCU_SYS_OTWARN_PS_En()
{
  Field_Mod32(&SCUPM->PCU_CTRL_STS.reg, (uint8)SCUPM_PCU_CTRL_STS_SYS_OTWARN_PS_DIS_Pos, SCUPM_PCU_CTRL_STS_SYS_OTWARN_PS_DIS_Msk, 0u);
}

INLINE void PCU_SYS_OTWARN_PS_Dis()
{
  Field_Mod32(&SCUPM->PCU_CTRL_STS.reg, (uint8)SCUPM_PCU_CTRL_STS_SYS_OTWARN_PS_DIS_Pos, SCUPM_PCU_CTRL_STS_SYS_OTWARN_PS_DIS_Msk, 1u);
}

INLINE void PCU_SYS_VS_OV_SLM_En()
{
  Field_Mod32(&SCUPM->PCU_CTRL_STS.reg, (uint8)SCUPM_PCU_CTRL_STS_SYS_VS_OV_SLM_DIS_Pos, SCUPM_PCU_CTRL_STS_SYS_VS_OV_SLM_DIS_Msk, 0u);
}

INLINE void PCU_SYS_VS_OV_SLM_Dis()
{
  Field_Mod32(&SCUPM->PCU_CTRL_STS.reg, (uint8)SCUPM_PCU_CTRL_STS_SYS_VS_OV_SLM_DIS_Pos, SCUPM_PCU_CTRL_STS_SYS_VS_OV_SLM_DIS_Msk, 1u);
}

INLINE void PCU_SYS_VS_UV_SLM_En()
{
  Field_Mod32(&SCUPM->PCU_CTRL_STS.reg, (uint8)SCUPM_PCU_CTRL_STS_SYS_VS_UV_SLM_DIS_Pos, SCUPM_PCU_CTRL_STS_SYS_VS_UV_SLM_DIS_Msk, 0u);
}

INLINE void PCU_SYS_VS_UV_SLM_Dis()
{
  Field_Mod32(&SCUPM->PCU_CTRL_STS.reg, (uint8)SCUPM_PCU_CTRL_STS_SYS_VS_UV_SLM_DIS_Pos, SCUPM_PCU_CTRL_STS_SYS_VS_UV_SLM_DIS_Msk, 1u);
}

INLINE void PCU_LIN_VS_UV_SD_En()
{
  Field_Mod32(&SCUPM->PCU_CTRL_STS.reg, (uint8)SCUPM_PCU_CTRL_STS_LIN_VS_UV_SD_DIS_Pos, SCUPM_PCU_CTRL_STS_LIN_VS_UV_SD_DIS_Msk, 0u);
}

INLINE void PCU_LIN_VS_UV_SD_Dis()
{
  Field_Mod32(&SCUPM->PCU_CTRL_STS.reg, (uint8)SCUPM_PCU_CTRL_STS_LIN_VS_UV_SD_DIS_Pos, SCUPM_PCU_CTRL_STS_LIN_VS_UV_SD_DIS_Msk, 1u);
}

INLINE void PCU_FAIL_PS_En()
{
  Field_Mod32(&SCUPM->PCU_CTRL_STS.reg, (uint8)SCUPM_PCU_CTRL_STS_FAIL_PS_DIS_Pos, SCUPM_PCU_CTRL_STS_FAIL_PS_DIS_Msk, 0u);
}

INLINE void PCU_FAIL_PS_Dis()
{
  Field_Mod32(&SCUPM->PCU_CTRL_STS.reg, (uint8)SCUPM_PCU_CTRL_STS_FAIL_PS_DIS_Pos, SCUPM_PCU_CTRL_STS_FAIL_PS_DIS_Msk, 1u);
}

INLINE void PCU_CLKWDT_SD_En()
{
  Field_Mod32(&SCUPM->PCU_CTRL_STS.reg, (uint8)SCUPM_PCU_CTRL_STS_CLKWDT_SD_DIS_Pos, SCUPM_PCU_CTRL_STS_CLKWDT_SD_DIS_Msk, 0u);
}

INLINE void PCU_CLKWDT_SD_Dis()
{
  Field_Mod32(&SCUPM->PCU_CTRL_STS.reg, (uint8)SCUPM_PCU_CTRL_STS_CLKWDT_SD_DIS_Pos, SCUPM_PCU_CTRL_STS_CLKWDT_SD_DIS_Msk, 1u);
}

INLINE uint16 PMU_Get_Reset_Status(void)
{
  return(u16_Field_Rd32(&PMU->RESET_STS.reg, (uint8)PMU_RESET_STS_SYS_FAIL_Pos, PMU_RESET_MASK));
}

INLINE void PMU_Clear_Reset_Status(void)
{
  Field_Clr32(&PMU->RESET_STS.reg, (uint32)PMU_RESET_MASK);  
}

INLINE uint8 PMU_VDDEXT_Off(void)
{
  Field_Mod32(&PMU->VDDEXT_CTRL.reg, (uint8)PMU_VDDEXT_CTRL_VDDEXT_ENABLE_Pos, PMU_VDDEXT_CTRL_VDDEXT_ENABLE_Msk, 0u);  
  
  return(u1_Field_Rd32(&PMU->VDDEXT_CTRL.reg, (uint8)PMU_VDDEXT_CTRL_VDDEXT_STABLE_Pos, PMU_VDDEXT_CTRL_VDDEXT_STABLE_Msk));    
}

INLINE void PMU_VDDEXT_Error_Clear(uint16 ErrorFlagMask)
{
  Field_Clr32(&PMU->VDDEXT_CTRL.reg, (uint32)ErrorFlagMask);  
}

INLINE void PMU_VDDEXT_Set(uint16 FlagMask)
{
  Field_Mod32(&PMU->VDDEXT_CTRL.reg, (uint8)PMU_VDDEXT_CTRL_VDDEXT_ENABLE_Pos, FlagMask, FlagMask);  
}

#endif
