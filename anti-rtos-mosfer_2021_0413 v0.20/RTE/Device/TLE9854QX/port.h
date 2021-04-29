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
 * \file     port.h
 *
 * \brief    Port/GPIO low level access library
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
**                           Revision history moved from port.c to port.h     **
**                           Temperature Compensation macros and function     **
**                           added                                            **
** V0.2.2: 2020-03-02, BG:   Updated revision history format                  **
*******************************************************************************/

#ifndef PORT_H
#define PORT_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle985x.h"
#include "types.h"
#include "sfr_access.h"
#include "cmsis_misra.h"

/*******************************************************************************
**                           Global Type Definitions                          **
*******************************************************************************/
/**\brief Port indices, Port P0*/
#define PORT_P0 (0U)
/**\brief Port indices, Port P1*/
#define PORT_P1 (1U)
/**\brief Port indices, Port P2*/
#define PORT_P2 (2U)

/**\brief Port actions, clear action*/
#define PORT_ACTION_CLEAR  (0U)
/**\brief Port actions, set action*/
#define PORT_ACTION_SET    (1U)
/**\brief Port actions, toggle action*/
#define PORT_ACTION_TOGGLE (2U)
/**\brief Port actions, input mode*/
#define PORT_ACTION_INPUT  (3U)
/**\brief Port actions, output mode*/
#define PORT_ACTION_OUTPUT (4U)

/**\brief Port Temperature Compensation Control, range 1: from -40°C to 0°C */
#define PORT_TCC_RANGE_1  (0U)
/**\brief Port Temperature Compensation Control, range 2: from 0°C to 40°C */
#define PORT_TCC_RANGE_2  (1U)
/**\brief Port Temperature Compensation Control, range 3: from 40°C to 80°C */
#define PORT_TCC_RANGE_3  (2U)
/**\brief Port Temperature Compensation Control, range 4: from 80°C to 150°C */
#define PORT_TCC_RANGE_4  (3U)

/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/
/** \brief Initializes the ports.
 *
 * \ingroup PORT_api
 */
void PORT_Init(void);

/** \brief Sets/clears/toggles a port pin in a safe way, i.e. with interrupt disable.
 *
 * \param PortPin Port and pin to change, e.g 0x12U for P1.2
 * \param Action PORT_ACTION_SET, PORT_ACTION_CLEAR or PORT_ACTION_TOGGLE
 *
 * \brief <b>Example</b><br>
 * \brief This example toggles the P1.2 .
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_ChangePin(0x12, PORT_ACTION_TOGGLE);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
void PORT_ChangePin(uint32 PortPin, uint32 Action);

/** \brief Reads a port pin.
 *
 * \param PortPin Port and pin to change, e.g 0x12U for P1.2
 * \return Port pin level (0U or 1U)
 *
 * \brief <b>Example</b><br>
 * \brief This example reads the status of P1.2 .
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint32 sts;
 *
 *     sts = PORT_ReadPin(0x12);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
uint8 PORT_ReadPin(uint32 PortPin);

/** \brief Reads a port.
 *
 * \param Port Port to read, e.g. 2U for Port 2
 * \return Port data (combination of 0Us and 1Us)
 *
 * \brief <b>Example</b><br>
 * \brief This example reads the status of Port2 .
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint32 sts;
 *
 *     sts = PORT_ReadPort(0x2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
uint8 PORT_ReadPort(uint32 Port);

/** \brief Change Alternative Settings.
 *
 * \param PortPin Port and pin to change, e.g 0x12U for P1.2
 * \param AltSel Alternative Settings Select
 *
 * \brief <b>Example</b><br>
 * \brief This example sets the P1.2 to Output and configures it to Normal GPIO.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P12_Output_Set();
 *     PORT_ChangePinAlt(0x12, 0u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
void PORT_ChangePinAlt(uint32 PortPin, uint8 AltSel);

/*******************************************************************************
**                        Inline Function Declarations                        **
*******************************************************************************/
/** \brief Sets Port P00 to Output.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P00 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P00_Output_Set();
 *     PORT_P00_Output_High_Set();
 *     PORT_P00_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P00_Output_Set(void);

/** \brief Sets Port P00 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P00 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P00_Input_Set();
 *     sts = PORT_P00_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P00_Input_Set(void);

/** \brief Sets Port P01 to Output.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P01 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P01_Output_Set();
 *     PORT_P01_Output_High_Set();
 *     PORT_P01_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P01_Output_Set(void);

/** \brief Sets Port P01 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P01 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P01_Input_Set();
 *     sts = PORT_P01_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P01_Input_Set(void);

/** \brief Sets Port P02 to Output.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P02 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P02_Output_Set();
 *     PORT_P02_Output_High_Set();
 *     PORT_P02_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P02_Output_Set(void);

/** \brief Sets Port P02 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P02 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P02_Input_Set();
 *     sts = PORT_P02_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P02_Input_Set(void);

/** \brief Sets Port P03 to Output.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P03 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P03_Output_Set();
 *     PORT_P03_Output_High_Set();
 *     PORT_P03_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P03_Output_Set(void);

/** \brief Sets Port P03 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P03 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P03_Input_Set();
 *     sts = PORT_P03_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P03_Input_Set(void);

/** \brief Sets Port P04 to Output.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P04 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P04_Output_Set();
 *     PORT_P04_Output_High_Set();
 *     PORT_P04_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P04_Output_Set(void);

/** \brief Sets Port P04 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P04 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P04_Input_Set();
 *     sts = PORT_P04_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P04_Input_Set(void);

/** \brief Sets Port P05 to Output.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P05 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P05_Output_Set();
 *     PORT_P05_Output_High_Set();
 *     PORT_P05_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P05_Output_Set(void);

/** \brief Sets Port P05 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P05 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P05_Input_Set();
 *     sts = PORT_P05_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P05_Input_Set(void);

/** \brief Sets Port P00 to High Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P00 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P00_Output_Set();
 *     PORT_P00_Output_High_Set();
 *     PORT_P00_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P00_Output_High_Set(void);

/** \brief Sets Port P00 to Low Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P00 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P00_Output_Set();
 *     PORT_P00_Output_Low_Set();
 *     PORT_P00_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P00_Output_Low_Set(void);

/** \brief Sets Port P00 to Toggle Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P00 as output, Toggle and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P00_Output_Set();
 *     PORT_P00_Output_Toggle_Set();
 *     PORT_P00_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P00_Output_Toggle_Set(void);

/** \brief Sets Port P01 to High Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P01 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P01_Output_Set();
 *     PORT_P01_Output_High_Set();
 *     PORT_P01_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P01_Output_High_Set(void);

/** \brief Sets Port P01 to Low Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P01 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P01_Output_Set();
 *     PORT_P01_Output_Low_Set();
 *     PORT_P01_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P01_Output_Low_Set(void);

/** \brief Sets Port P01 to Toggle Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P01 as output, Toggle and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P01_Output_Set();
 *     PORT_P01_Output_Toggle_Set();
 *     PORT_P01_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P01_Output_Toggle_Set(void);

/** \brief Sets Port P02 to High Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P02 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P02_Output_Set();
 *     PORT_P02_Output_High_Set();
 *     PORT_P02_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P02_Output_High_Set(void);

/** \brief Sets Port P02 to Low Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P02 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P02_Output_Set();
 *     PORT_P02_Output_Low_Set();
 *     PORT_P02_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P02_Output_Low_Set(void);

/** \brief Sets Port P02 to Toggle Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P02 as output, Toggle and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P02_Output_Set();
 *     PORT_P02_Output_Toggle_Set();
 *     PORT_P02_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P02_Output_Toggle_Set(void);

/** \brief Sets Port P03 to High Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P03 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P03_Output_Set();
 *     PORT_P03_Output_High_Set();
 *     PORT_P03_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P03_Output_High_Set(void);

/** \brief Sets Port P03 to Low Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P03 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P03_Output_Set();
 *     PORT_P03_Output_Low_Set();
 *     PORT_P03_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P03_Output_Low_Set(void);

/** \brief Sets Port P03 to Toggle Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P03 as output, Toggle and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P03_Output_Set();
 *     PORT_P03_Output_Toggle_Set();
 *     PORT_P03_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P03_Output_Toggle_Set(void);

/** \brief Sets Port P04 to High Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P04 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P04_Output_Set();
 *     PORT_P04_Output_High_Set();
 *     PORT_P04_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P04_Output_High_Set(void);

/** \brief Sets Port P04 to Low Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P04 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P04_Output_Set();
 *     PORT_P04_Output_Low_Set();
 *     PORT_P04_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P04_Output_Low_Set(void);

/** \brief Sets Port P04 to Toggle Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P04 as output, Toggle and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P04_Output_Set();
 *     PORT_P04_Output_Toggle_Set();
 *     PORT_P04_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P04_Output_Toggle_Set(void);

/** \brief Sets Port P05 to High Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P05 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P05_Output_Set();
 *     PORT_P05_Output_High_Set();
 *     PORT_P05_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P05_Output_High_Set(void);

/** \brief Sets Port P05 to Low Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P05 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P05_Output_Set();
 *     PORT_P05_Output_Low_Set();
 *     PORT_P05_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P05_Output_Low_Set(void);

/** \brief Sets Port P05 to Toggle Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P05 as output, Toggle and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P05_Output_Set();
 *     PORT_P05_Output_Toggle_Set();
 *     PORT_P05_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P05_Output_Toggle_Set(void);

/** \brief Reads Port P00 Status.
 *
 * \return P00 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P00 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P00_Input_Set();
 *     sts = PORT_P00_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P00_Get(void);

/** \brief Reads Port P01 Status.
 *
 * \return P01 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P01 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P01_Input_Set();
 *     sts = PORT_P01_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P01_Get(void);

/** \brief Reads Port P02 Status.
 *
 * \return P02 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P02 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P02_Input_Set();
 *     sts = PORT_P02_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P02_Get(void);

/** \brief Reads Port P03 Status.
 *
 * \return P03 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P03 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P03_Input_Set();
 *     sts = PORT_P03_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P03_Get(void);

/** \brief Reads Port P04 Status.
 *
 * \return P04 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P04 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P04_Input_Set();
 *     sts = PORT_P04_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P04_Get(void);

/** \brief Reads Port P05 Status.
 *
 * \return P05 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P05 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P05_Input_Set();
 *     sts = PORT_P05_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P05_Get(void);

/** \brief Enables Output OpenDrain for Port P00.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P00 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P00_Output_Set();
 *     PORT_P00_Output_Low_Set();
 *     PORT_P00_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P00_OpenDrain_En(void);

/** \brief Disables Output OpenDrain for Port P00.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P00 as output, Low and Normal Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P00_Output_Set();
 *     PORT_P00_Output_Low_Set();
 *     PORT_P00_OpenDrain_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P00_OpenDrain_Dis(void);

/** \brief Enables Output OpenDrain for Port P01.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P01 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P01_Output_Set();
 *     PORT_P01_Output_Low_Set();
 *     PORT_P01_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P01_OpenDrain_En(void);

/** \brief Disables Output OpenDrain for Port P01.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P01 as output, Low and Normal Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P01_Output_Set();
 *     PORT_P01_Output_Low_Set();
 *     PORT_P01_OpenDrain_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P01_OpenDrain_Dis(void);

/** \brief Enables Output OpenDrain for Port P02.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P02 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P02_Output_Set();
 *     PORT_P02_Output_Low_Set();
 *     PORT_P02_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P02_OpenDrain_En(void);

/** \brief Disables Output OpenDrain for Port P02.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P02 as output, Low and Normal Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P02_Output_Set();
 *     PORT_P02_Output_Low_Set();
 *     PORT_P02_OpenDrain_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P02_OpenDrain_Dis(void);

/** \brief Enables Output OpenDrain for Port P03.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P03 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P03_Output_Set();
 *     PORT_P03_Output_Low_Set();
 *     PORT_P03_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P03_OpenDrain_En(void);

/** \brief Disables Output OpenDrain for Port P03.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P03 as output, Low and Normal Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P03_Output_Set();
 *     PORT_P03_Output_Low_Set();
 *     PORT_P03_OpenDrain_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P03_OpenDrain_Dis(void);

/** \brief Enables Output OpenDrain for Port P04.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P04 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P04_Output_Set();
 *     PORT_P04_Output_Low_Set();
 *     PORT_P04_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P04_OpenDrain_En(void);

/** \brief Disables Output OpenDrain for Port P04.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P04 as output, Low and Normal Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P04_Output_Set();
 *     PORT_P04_Output_Low_Set();
 *     PORT_P04_OpenDrain_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P04_OpenDrain_Dis(void);

/** \brief Enables Output OpenDrain for Port P05.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P05 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P05_Output_Set();
 *     PORT_P05_Output_Low_Set();
 *     PORT_P05_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P05_OpenDrain_En(void);

/** \brief Disables Output OpenDrain for Port P05.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P05 as output, Low and Normal Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P05_Output_Set();
 *     PORT_P05_Output_Low_Set();
 *     PORT_P05_OpenDrain_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P05_OpenDrain_Dis(void);

/** \brief Enables PullUpDown for Port P00.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P00.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P00_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P00_PullUpDown_En(void);

/** \brief Disables PullUpDown for Port P00.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P00.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P00_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P00_PullUpDown_Dis(void);

/** \brief Enables PullUpDown for Port P01.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P01.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P01_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P01_PullUpDown_En(void);

/** \brief Disables PullUpDown for Port P01.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P01.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P01_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P01_PullUpDown_Dis(void);

/** \brief Enables PullUpDown for Port P02.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P02.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P02_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P02_PullUpDown_En(void);

/** \brief Disables PullUpDown for Port P02.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P02.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P02_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P02_PullUpDown_Dis(void);

/** \brief Enables PullUpDown for Port P03.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P03.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P03_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P03_PullUpDown_En(void);

/** \brief Disables PullUpDown for Port P03.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P03.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P03_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P03_PullUpDown_Dis(void);

/** \brief Enables PullUpDown for Port P04.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P04.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P04_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P04_PullUpDown_En(void);

/** \brief Disables PullUpDown for Port P04.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P04.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P04_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P04_PullUpDown_Dis(void);

/** \brief Enables PullUpDown for Port P05.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P05.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P05_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P05_PullUpDown_En(void);

/** \brief Disables PullUpDown for Port P05.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P05.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P05_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P05_PullUpDown_Dis(void);

/** \brief Sets PullUp for Port P00.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P00.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P00_PullUpDown_En();
 *     PORT_P00_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P00_PullUp_Set(void);

/** \brief Sets PullDown for Port P00.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P00.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P00_PullUpDown_En();
 *     PORT_P00_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P00_PullDown_Set(void);

/** \brief Sets PullUp for Port P01.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P01.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P01_PullUpDown_En();
 *     PORT_P01_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P01_PullUp_Set(void);

/** \brief Sets PullDown for Port P01.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P01.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P01_PullUpDown_En();
 *     PORT_P01_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P01_PullDown_Set(void);

/** \brief Sets PullUp for Port P02.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P02.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P02_PullUpDown_En();
 *     PORT_P02_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P02_PullUp_Set(void);

/** \brief Sets PullDown for Port P02.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P02.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P02_PullUpDown_En();
 *     PORT_P02_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P02_PullDown_Set(void);

/** \brief Sets PullUp for Port P03.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P03.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P03_PullUpDown_En();
 *     PORT_P03_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P03_PullUp_Set(void);

/** \brief Sets PullDown for Port P03.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P03.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P03_PullUpDown_En();
 *     PORT_P03_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P03_PullDown_Set(void);

/** \brief Sets PullUp for Port P04.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P04.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P04_PullUpDown_En();
 *     PORT_P04_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P04_PullUp_Set(void);

/** \brief Sets PullDown for Port P04.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P04.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P04_PullUpDown_En();
 *     PORT_P04_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P04_PullDown_Set(void);

/** \brief Sets PullUp for Port P05.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P05.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P05_PullUpDown_En();
 *     PORT_P05_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P05_PullUp_Set(void);

/** \brief Sets PullDown for Port P05.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P05.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P05_PullUpDown_En();
 *     PORT_P05_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P05_PullDown_Set(void);

/** \brief Selects P0.0 Port Driver Mode.
 *
 * \param mode Driver Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example sets P0.0 Port Driver Strong driver and soft edge mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P00_Driver_Mode_Sel(0x2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P00_Driver_Mode_Sel(uint8 mode);

/** \brief Selects P0.1 Port Driver Mode.
 *
 * \param mode Driver Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example sets P0.1 Port Driver Strong driver and soft edge mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P01_Driver_Mode_Sel(0x2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P01_Driver_Mode_Sel(uint8 mode);

/** \brief Selects P0.2 Port Driver Mode.
 *
 * \param mode Driver Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example sets P0.2 Port Driver Strong driver and soft edge mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P02_Driver_Mode_Sel(0x2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P02_Driver_Mode_Sel(uint8 mode);

/** \brief Selects P0.3 Port Driver Mode.
 *
 * \param mode Driver Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example sets P0.3 Port Driver Strong driver and soft edge mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P03_Driver_Mode_Sel(0x2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P03_Driver_Mode_Sel(uint8 mode);

/** \brief Selects P0.4 Port Driver Mode.
 *
 * \param mode Driver Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example sets P0.4 Port Driver Strong driver and soft edge mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P04_Driver_Mode_Sel(0x2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P04_Driver_Mode_Sel(uint8 mode);

/** \brief Selects P0.5 Port Driver Mode.
 *
 * \param mode Driver Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example sets P0.5 Port Driver Strong driver and soft edge mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P05_Driver_Mode_Sel(0x2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P05_Driver_Mode_Sel(uint8 mode);

/** \brief Sets Port P10 to Output.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P10 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P10_Output_Set();
 *     PORT_P10_Output_High_Set();
 *     PORT_P10_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P10_Output_Set(void);

/** \brief Sets Port P10 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P10 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P10_Input_Set();
 *     sts = PORT_P10_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P10_Input_Set(void);

/** \brief Sets Port P11 to Output.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P11 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P11_Output_Set();
 *     PORT_P11_Output_High_Set();
 *     PORT_P11_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P11_Output_Set(void);

/** \brief Sets Port P11 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P11 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P11_Input_Set();
 *     sts = PORT_P11_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P11_Input_Set(void);

/** \brief Sets Port P12 to Output.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P12 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P12_Output_Set();
 *     PORT_P12_Output_High_Set();
 *     PORT_P12_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P12_Output_Set(void);

/** \brief Sets Port P12 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P12 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P12_Input_Set();
 *     sts = PORT_P12_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P12_Input_Set(void);

/** \brief Sets Port P14 to Output.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P14 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P14_Output_Set();
 *     PORT_P14_Output_High_Set();
 *     PORT_P14_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P14_Output_Set(void);

/** \brief Sets Port P14 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P14 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P14_Input_Set();
 *     sts = PORT_P14_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P14_Input_Set(void);

/** \brief Sets Port P10 to High Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P10 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P10_Output_Set();
 *     PORT_P10_Output_High_Set();
 *     PORT_P10_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P10_Output_High_Set(void);

/** \brief Sets Port P10 to Low Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P10 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P10_Output_Set();
 *     PORT_P10_Output_Low_Set();
 *     PORT_P10_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P10_Output_Low_Set(void);

/** \brief Sets Port P10 to Toggle Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P10 as output, Toggle and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P10_Output_Set();
 *     PORT_P10_Output_Toggle_Set();
 *     PORT_P10_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P10_Output_Toggle_Set(void);

/** \brief Sets Port P11 to High Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P11 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P11_Output_Set();
 *     PORT_P11_Output_High_Set();
 *     PORT_P11_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P11_Output_High_Set(void);

/** \brief Sets Port P11 to Low Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P11 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P11_Output_Set();
 *     PORT_P11_Output_Low_Set();
 *     PORT_P11_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P11_Output_Low_Set(void);

/** \brief Sets Port P11 to Toggle Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P11 as output, Toggle and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P11_Output_Set();
 *     PORT_P11_Output_Toggle_Set();
 *     PORT_P11_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P11_Output_Toggle_Set(void);

/** \brief Sets Port P12 to High Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P12 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P12_Output_Set();
 *     PORT_P12_Output_High_Set();
 *     PORT_P12_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P12_Output_High_Set(void);

/** \brief Sets Port P12 to Low Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P12 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P12_Output_Set();
 *     PORT_P12_Output_Low_Set();
 *     PORT_P12_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P12_Output_Low_Set(void);

/** \brief Sets Port P12 to Toggle Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P12 as output, Toggle and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P12_Output_Set();
 *     PORT_P12_Output_Toggle_Set();
 *     PORT_P12_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P12_Output_Toggle_Set(void);

/** \brief Sets Port P14 to High Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P14 as output, High and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P14_Output_Set();
 *     PORT_P14_Output_High_Set();
 *     PORT_P14_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P14_Output_High_Set(void);

/** \brief Sets Port P14 to Low Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P14 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P14_Output_Set();
 *     PORT_P14_Output_Low_Set();
 *     PORT_P14_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P14_Output_Low_Set(void);

/** \brief Sets Port P14 to Toggle Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P14 as output, Toggle and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P14_Output_Set();
 *     PORT_P14_Output_Toggle_Set();
 *     PORT_P14_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P14_Output_Toggle_Set(void);

/** \brief Reads Port P10 Status.
 *
 * \return P10 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P10 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P10_Input_Set();
 *     sts = PORT_P10_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P10_Get(void);

/** \brief Reads Port P11 Status.
 *
 * \return P11 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P11 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P11_Input_Set();
 *     sts = PORT_P11_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P11_Get(void);

/** \brief Reads Port P12 Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P12 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P12_Input_Set();
 *     sts = PORT_P12_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P12_Get(void);

/** \brief Reads Port P14 Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P14 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P14_Input_Set();
 *     sts = PORT_P14_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P14_Get(void);

/** \brief Enables Output OpenDrain for Port P10.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P10 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P10_Output_Set();
 *     PORT_P10_Output_Low_Set();
 *     PORT_P10_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P10_OpenDrain_En(void);

/** \brief Disables Output OpenDrain for Port P10.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P10 as output, Low and Normal Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P10_Output_Set();
 *     PORT_P10_Output_Low_Set();
 *     PORT_P10_OpenDrain_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P10_OpenDrain_Dis(void);

/** \brief Enables Output OpenDrain for Port P11.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P11 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P11_Output_Set();
 *     PORT_P11_Output_Low_Set();
 *     PORT_P11_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P11_OpenDrain_En(void);

/** \brief Disables Output OpenDrain for Port P11.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P11 as output, Low and Normal Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P11_Output_Set();
 *     PORT_P11_Output_Low_Set();
 *     PORT_P11_OpenDrain_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P11_OpenDrain_Dis(void);

/** \brief Enables Output OpenDrain for Port P12.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P12 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P12_Output_Set();
 *     PORT_P12_Output_Low_Set();
 *     PORT_P12_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P12_OpenDrain_En(void);

/** \brief Disables Output OpenDrain for Port P12.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P12 as output, Low and Normal Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P12_Output_Set();
 *     PORT_P12_Output_Low_Set();
 *     PORT_P12_OpenDrain_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P12_OpenDrain_Dis(void);

/** \brief Enables Output OpenDrain for Port P14.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P14 as output, Low and Open-Drain.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P14_Output_Set();
 *     PORT_P14_Output_Low_Set();
 *     PORT_P14_OpenDrain_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P14_OpenDrain_En(void);

/** \brief Disables Output OpenDrain for Port P14.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P14 as output, Low and Normal Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P14_Output_Set();
 *     PORT_P14_Output_Low_Set();
 *     PORT_P14_OpenDrain_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P14_OpenDrain_Dis(void);

/** \brief Enables PullUpDown for Port P10.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P10.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P10_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P10_PullUpDown_En(void);

/** \brief Disables PullUpDown for Port P10.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P10.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P10_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P10_PullUpDown_Dis(void);

/** \brief Enables PullUpDown for Port P11.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P11.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P11_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P11_PullUpDown_En(void);

/** \brief Disables PullUpDown for Port P11.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P11.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P11_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P11_PullUpDown_Dis(void);

/** \brief Enables PullUpDown for Port P12.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P12.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P12_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P12_PullUpDown_En(void);

/** \brief Disables PullUpDown for Port P12.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P12.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P12_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P12_PullUpDown_Dis(void);

/** \brief Enables PullUpDown for Port P14.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P14.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P14_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P14_PullUpDown_En(void);

/** \brief Disables PullUpDown for Port P14.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P14.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P14_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P14_PullUpDown_Dis(void);

/** \brief Sets PullUp for Port P10.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P10.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P10_PullUpDown_En();
 *     PORT_P10_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P10_PullUp_Set(void);

/** \brief Sets PullDown for Port P10.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P10.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P10_PullUpDown_En();
 *     PORT_P10_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P10_PullDown_Set(void);

/** \brief Sets PullUp for Port P11.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P11.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P11_PullUpDown_En();
 *     PORT_P11_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P11_PullUp_Set(void);

/** \brief Sets PullDown for Port P11.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P11.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P11_PullUpDown_En();
 *     PORT_P11_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P11_PullDown_Set(void);

/** \brief Sets PullUp for Port P12.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P12.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P12_PullUpDown_En();
 *     PORT_P12_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P12_PullUp_Set(void);

/** \brief Sets PullDown for Port P12.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P12.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P12_PullUpDown_En();
 *     PORT_P12_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P12_PullDown_Set(void);

/** \brief Sets PullUp for Port P14.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P14.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P14_PullUpDown_En();
 *     PORT_P14_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P14_PullUp_Set(void);

/** \brief Sets PullDown for Port P14.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P14.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P14_PullUpDown_En();
 *     PORT_P14_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P14_PullDown_Set(void);

/** \brief Selects P1.0 Port Driver Mode.
 *
 * \param mode Driver Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example sets P1.0 Port Driver Strong driver and soft edge mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P10_Driver_Mode_Sel(0x2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P10_Driver_Mode_Sel(uint8 mode);

/** \brief Selects P1.1 Port Driver Mode.
 *
 * \param mode Driver Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example sets P1.1 Port Driver Strong driver and soft edge mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P11_Driver_Mode_Sel(0x2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P11_Driver_Mode_Sel(uint8 mode);

/** \brief Selects P1.2 Port Driver Mode.
 *
 * \param mode Driver Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example sets P1.2 Port Driver Strong driver and soft edge mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P12_Driver_Mode_Sel(0x2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P12_Driver_Mode_Sel(uint8 mode);

/** \brief Selects P1.4 Port Driver Mode.
 *
 * \param mode Driver Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example sets P1.4 Port Driver Strong driver and soft edge mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P14_Driver_Mode_Sel(0x2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P14_Driver_Mode_Sel(uint8 mode);

/** \brief Sets Port P20 to Disable.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets P20 to disable.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P20_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P20_Dis(void);

/** \brief Sets Port P20 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P20 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P20_Input_Set();
 *     sts = PORT_P20_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P20_Input_Set(void);

/** \brief Sets Port P21 to Disable.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets P21 to disable.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P21_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P21_Dis(void);

/** \brief Sets Port P21 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P21 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P21_Input_Set();
 *     sts = PORT_P21_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P21_Input_Set(void);

/** \brief Sets Port P22 to Disable.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets P22 to disable.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P22_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P22_Dis(void);

/** \brief Sets Port P22 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P22 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P22_Input_Set();
 *     sts = PORT_P22_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P22_Input_Set(void);

/** \brief Sets Port P23 to Disable.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets P23 to disable.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P23_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P23_Dis(void);

/** \brief Sets Port P23 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P23 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P23_Input_Set();
 *     sts = PORT_P23_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P23_Input_Set(void);

/** \brief Sets Port P27 to Disable.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets P27 to disable.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P27_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P27_Dis(void);

/** \brief Sets Port P27 to Input.
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P27 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P27_Input_Set();
 *     sts = PORT_P27_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P27_Input_Set(void);

/** \brief Reads Port P20 Status.
 *
 * \return P20 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P20 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P20_Input_Set();
 *     sts = PORT_P20_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P20_Get(void);

/** \brief Reads Port P21 Status.
 *
 * \return P21 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P21 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P21_Input_Set();
 *     sts = PORT_P21_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P21_Get(void);

/** \brief Reads Port P22 Status.
 *
 * \return P22 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P22 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P22_Input_Set();
 *     sts = PORT_P22_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P22_Get(void);

/** \brief Reads Port P23 Status.
 *
 * \return P23 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P23 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P23_Input_Set();
 *     sts = PORT_P23_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P23_Get(void);

/** \brief Reads Port P27 Status.
 *
 * \return P27 Status
 *
 * \brief <b>Example</b><br>
 * \brief This example configures P27 as input and reads the status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     PORT_P27_Input_Set();
 *     sts = PORT_P27_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE uint8 PORT_P27_Get(void);

/** \brief Enables PullUpDown for Port P20.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P20.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P20_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P20_PullUpDown_En(void);

/** \brief Disables PullUpDown for Port P20.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P20.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P20_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P20_PullUpDown_Dis(void);

/** \brief Enables PullUpDown for Port P21.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P21.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P21_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P21_PullUpDown_En(void);

/** \brief Disables PullUpDown for Port P21.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P21.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P21_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P21_PullUpDown_Dis(void);

/** \brief Enables PullUpDown for Port P22.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P22.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P22_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P22_PullUpDown_En(void);

/** \brief Disables PullUpDown for Port P22.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P22.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P22_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P22_PullUpDown_Dis(void);

/** \brief Enables PullUpDown for Port P23.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P23.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P23_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P23_PullUpDown_En(void);

/** \brief Disables PullUpDown for Port P23.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P23.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P23_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P23_PullUpDown_Dis(void);

/** \brief Enables PullUpDown for Port P27.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables PullUpDown for Port P27.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P27_PullUpDown_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P27_PullUpDown_En(void);

/** \brief Disables PullUpDown for Port P27.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables PullUpDown for Port P27.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P27_PullUpDown_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P27_PullUpDown_Dis(void);

/** \brief Sets PullUp for Port P20.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P20.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P20_PullUpDown_En();
 *     PORT_P20_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P20_PullUp_Set(void);

/** \brief Sets PullDown for Port P20.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P20.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P20_PullUpDown_En();
 *     PORT_P20_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P20_PullDown_Set(void);

/** \brief Sets PullUp for Port P21.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P21.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P21_PullUpDown_En();
 *     PORT_P21_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P21_PullUp_Set(void);

/** \brief Sets PullDown for Port P21.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P21.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P21_PullUpDown_En();
 *     PORT_P21_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P21_PullDown_Set(void);

/** \brief Sets PullUp for Port P22.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P22.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P22_PullUpDown_En();
 *     PORT_P22_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P22_PullUp_Set(void);

/** \brief Sets PullDown for Port P22.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P22.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P22_PullUpDown_En();
 *     PORT_P22_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P22_PullDown_Set(void);

/** \brief Sets PullUp for Port P23.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P23.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P23_PullUpDown_En();
 *     PORT_P23_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P23_PullUp_Set(void);

/** \brief Sets PullDown for Port P23.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P23.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P23_PullUpDown_En();
 *     PORT_P23_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P23_PullDown_Set(void);

/** \brief Sets PullUp for Port P27.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullUp for Port P27.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P27_PullUpDown_En();
 *     PORT_P27_PullUp_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P27_PullUp_Set(void);

/** \brief Sets PullDown for Port P27.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets PullDown for Port P27.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_P27_PullUpDown_En();
 *     PORT_P27_PullDown_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_P27_PullDown_Set(void);

/** \brief Selects Temperature Compensation range.
 *
 * \param range Temperature Compensation range
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Temperature Compensation to range 2 (from 0°C to 40°C).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     PORT_Temp_Comp_Sel(PORT_TCC_RANGE_2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup PORT_api
 */
INLINE void PORT_Temp_Comp_Sel(uint8 range);

/*******************************************************************************
**                         Inline Function Definitions                        **
*******************************************************************************/
INLINE void PORT_P00_Output_Set()
{
  Field_Mod32(&PORT->P0_DIR.reg, (uint8)PORT_P0_DIR_PP0_Pos, PORT_P0_DIR_PP0_Msk, 1u);
}

INLINE void PORT_P00_Input_Set()
{
  Field_Mod32(&PORT->P0_DIR.reg, (uint8)PORT_P0_DIR_PP0_Pos, PORT_P0_DIR_PP0_Msk, 0u);
}

INLINE void PORT_P01_Output_Set()
{
  Field_Mod32(&PORT->P0_DIR.reg, (uint8)PORT_P0_DIR_PP1_Pos, PORT_P0_DIR_PP1_Msk, 1u);
}

INLINE void PORT_P01_Input_Set()
{
  Field_Mod32(&PORT->P0_DIR.reg, (uint8)PORT_P0_DIR_PP1_Pos, PORT_P0_DIR_PP1_Msk, 0u);
}

INLINE void PORT_P02_Output_Set()
{
  Field_Mod32(&PORT->P0_DIR.reg, (uint8)PORT_P0_DIR_PP2_Pos, PORT_P0_DIR_PP2_Msk, 1u);
}

INLINE void PORT_P02_Input_Set()
{
  Field_Mod32(&PORT->P0_DIR.reg, (uint8)PORT_P0_DIR_PP2_Pos, PORT_P0_DIR_PP2_Msk, 0u);
}

INLINE void PORT_P03_Output_Set()
{
  Field_Mod32(&PORT->P0_DIR.reg, (uint8)PORT_P0_DIR_PP3_Pos, PORT_P0_DIR_PP3_Msk, 1u);
}

INLINE void PORT_P03_Input_Set()
{
  Field_Mod32(&PORT->P0_DIR.reg, (uint8)PORT_P0_DIR_PP3_Pos, PORT_P0_DIR_PP3_Msk, 0u);
}

INLINE void PORT_P04_Output_Set()
{
  Field_Mod32(&PORT->P0_DIR.reg, (uint8)PORT_P0_DIR_PP4_Pos, PORT_P0_DIR_PP4_Msk, 1u);
}

INLINE void PORT_P04_Input_Set()
{
  Field_Mod32(&PORT->P0_DIR.reg, (uint8)PORT_P0_DIR_PP4_Pos, PORT_P0_DIR_PP4_Msk, 0u);
}

INLINE void PORT_P05_Output_Set()
{
  Field_Mod32(&PORT->P0_DIR.reg, (uint8)PORT_P0_DIR_PP5_Pos, PORT_P0_DIR_PP5_Msk, 1u);
}

INLINE void PORT_P05_Input_Set()
{
  Field_Mod32(&PORT->P0_DIR.reg, (uint8)PORT_P0_DIR_PP5_Pos, PORT_P0_DIR_PP5_Msk, 0u);
}

INLINE void PORT_P00_Output_High_Set()
{
  Field_Mod32(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_PP0_Pos, PORT_P0_DATA_PP0_Msk, 1u);
}

INLINE void PORT_P00_Output_Low_Set()
{
  Field_Mod32(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_PP0_Pos, PORT_P0_DATA_PP0_Msk, 0u);
}

INLINE void PORT_P00_Output_Toggle_Set()
{
  Field_Inv32(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_PP0_Msk);
}

INLINE void PORT_P01_Output_High_Set()
{
  Field_Mod32(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_PP1_Pos, PORT_P0_DATA_PP1_Msk, 1u);
}

INLINE void PORT_P01_Output_Low_Set()
{
  Field_Mod32(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_PP1_Pos, PORT_P0_DATA_PP1_Msk, 0u);
}

INLINE void PORT_P01_Output_Toggle_Set()
{
  Field_Inv32(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_PP1_Msk);
}

INLINE void PORT_P02_Output_High_Set()
{
  Field_Mod32(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_PP2_Pos, PORT_P0_DATA_PP2_Msk, 1u);
}

INLINE void PORT_P02_Output_Low_Set()
{
  Field_Mod32(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_PP2_Pos, PORT_P0_DATA_PP2_Msk, 0u);
}

INLINE void PORT_P02_Output_Toggle_Set()
{
  Field_Inv32(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_PP2_Msk);
}

INLINE void PORT_P03_Output_High_Set()
{
  Field_Mod32(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_PP3_Pos, PORT_P0_DATA_PP3_Msk, 1u);
}

INLINE void PORT_P03_Output_Low_Set()
{
  Field_Mod32(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_PP3_Pos, PORT_P0_DATA_PP3_Msk, 0u);
}

INLINE void PORT_P03_Output_Toggle_Set()
{
  Field_Inv32(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_PP3_Msk);
}

INLINE void PORT_P04_Output_High_Set()
{
  Field_Mod32(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_PP4_Pos, PORT_P0_DATA_PP4_Msk, 1u);
}

INLINE void PORT_P04_Output_Low_Set()
{
  Field_Mod32(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_PP4_Pos, PORT_P0_DATA_PP4_Msk, 0u);
}

INLINE void PORT_P04_Output_Toggle_Set()
{
  Field_Inv32(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_PP4_Msk);
}

INLINE void PORT_P05_Output_High_Set()
{
  Field_Mod32(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_PP5_Pos, PORT_P0_DATA_PP5_Msk, 1u);
}

INLINE void PORT_P05_Output_Low_Set()
{
  Field_Mod32(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_PP5_Pos, PORT_P0_DATA_PP5_Msk, 0u);
}

INLINE void PORT_P05_Output_Toggle_Set()
{
  Field_Inv32(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_PP5_Msk);
}

INLINE uint8 PORT_P00_Get()
{
  return(u1_Field_Rd32(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_PP0_Pos, PORT_P0_DATA_PP0_Msk));
}

INLINE uint8 PORT_P01_Get()
{
  return(u1_Field_Rd32(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_PP1_Pos, PORT_P0_DATA_PP1_Msk));
}

INLINE uint8 PORT_P02_Get()
{
  return(u1_Field_Rd32(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_PP2_Pos, PORT_P0_DATA_PP2_Msk));
}

INLINE uint8 PORT_P03_Get()
{
  return(u1_Field_Rd32(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_PP3_Pos, PORT_P0_DATA_PP3_Msk));
}

INLINE uint8 PORT_P04_Get()
{
  return(u1_Field_Rd32(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_PP4_Pos, PORT_P0_DATA_PP4_Msk));
}

INLINE uint8 PORT_P05_Get()
{
  return(u1_Field_Rd32(&PORT->P0_DATA.reg, (uint8)PORT_P0_DATA_PP5_Pos, PORT_P0_DATA_PP5_Msk));
}

INLINE void PORT_P00_OpenDrain_En()
{
  Field_Mod32(&PORT->P0_OD.reg, (uint8)PORT_P0_OD_PP0_Pos, PORT_P0_OD_PP0_Msk, 1u);
}

INLINE void PORT_P00_OpenDrain_Dis()
{
  Field_Mod32(&PORT->P0_OD.reg, (uint8)PORT_P0_OD_PP0_Pos, PORT_P0_OD_PP0_Msk, 0u);
}

INLINE void PORT_P01_OpenDrain_En()
{
  Field_Mod32(&PORT->P0_OD.reg, (uint8)PORT_P0_OD_PP1_Pos, PORT_P0_OD_PP1_Msk, 1u);
}

INLINE void PORT_P01_OpenDrain_Dis()
{
  Field_Mod32(&PORT->P0_OD.reg, (uint8)PORT_P0_OD_PP1_Pos, PORT_P0_OD_PP1_Msk, 0u);
}

INLINE void PORT_P02_OpenDrain_En()
{
  Field_Mod32(&PORT->P0_OD.reg, (uint8)PORT_P0_OD_PP2_Pos, PORT_P0_OD_PP2_Msk, 1u);
}

INLINE void PORT_P02_OpenDrain_Dis()
{
  Field_Mod32(&PORT->P0_OD.reg, (uint8)PORT_P0_OD_PP2_Pos, PORT_P0_OD_PP2_Msk, 0u);
}

INLINE void PORT_P03_OpenDrain_En()
{
  Field_Mod32(&PORT->P0_OD.reg, (uint8)PORT_P0_OD_PP3_Pos, PORT_P0_OD_PP3_Msk, 1u);
}

INLINE void PORT_P03_OpenDrain_Dis()
{
  Field_Mod32(&PORT->P0_OD.reg, (uint8)PORT_P0_OD_PP3_Pos, PORT_P0_OD_PP3_Msk, 0u);
}

INLINE void PORT_P04_OpenDrain_En()
{
  Field_Mod32(&PORT->P0_OD.reg, (uint8)PORT_P0_OD_PP4_Pos, PORT_P0_OD_PP4_Msk, 1u);
}

INLINE void PORT_P04_OpenDrain_Dis()
{
  Field_Mod32(&PORT->P0_OD.reg, (uint8)PORT_P0_OD_PP4_Pos, PORT_P0_OD_PP4_Msk, 0u);
}

INLINE void PORT_P05_OpenDrain_En()
{
  Field_Mod32(&PORT->P0_OD.reg, (uint8)PORT_P0_OD_PP5_Pos, PORT_P0_OD_PP5_Msk, 1u);
}

INLINE void PORT_P05_OpenDrain_Dis()
{
  Field_Mod32(&PORT->P0_OD.reg, (uint8)PORT_P0_OD_PP5_Pos, PORT_P0_OD_PP5_Msk, 0u);
}

INLINE void PORT_P00_PullUpDown_En()
{
  Field_Mod32(&PORT->P0_PUDEN.reg, (uint8)PORT_P0_PUDEN_PP0_Pos, PORT_P0_PUDEN_PP0_Msk, 1u);
}

INLINE void PORT_P00_PullUpDown_Dis()
{
  Field_Mod32(&PORT->P0_PUDEN.reg, (uint8)PORT_P0_PUDEN_PP0_Pos, PORT_P0_PUDEN_PP0_Msk, 0u);
}

INLINE void PORT_P01_PullUpDown_En()
{
  Field_Mod32(&PORT->P0_PUDEN.reg, (uint8)PORT_P0_PUDEN_PP1_Pos, PORT_P0_PUDEN_PP1_Msk, 1u);
}

INLINE void PORT_P01_PullUpDown_Dis()
{
  Field_Mod32(&PORT->P0_PUDEN.reg, (uint8)PORT_P0_PUDEN_PP1_Pos, PORT_P0_PUDEN_PP1_Msk, 0u);
}

INLINE void PORT_P02_PullUpDown_En()
{
  Field_Mod32(&PORT->P0_PUDEN.reg, (uint8)PORT_P0_PUDEN_PP2_Pos, PORT_P0_PUDEN_PP2_Msk, 1u);
}

INLINE void PORT_P02_PullUpDown_Dis()
{
  Field_Mod32(&PORT->P0_PUDEN.reg, (uint8)PORT_P0_PUDEN_PP2_Pos, PORT_P0_PUDEN_PP2_Msk, 0u);
}

INLINE void PORT_P03_PullUpDown_En()
{
  Field_Mod32(&PORT->P0_PUDEN.reg, (uint8)PORT_P0_PUDEN_PP3_Pos, PORT_P0_PUDEN_PP3_Msk, 1u);
}

INLINE void PORT_P03_PullUpDown_Dis()
{
  Field_Mod32(&PORT->P0_PUDEN.reg, (uint8)PORT_P0_PUDEN_PP3_Pos, PORT_P0_PUDEN_PP3_Msk, 0u);
}

INLINE void PORT_P04_PullUpDown_En()
{
  Field_Mod32(&PORT->P0_PUDEN.reg, (uint8)PORT_P0_PUDEN_PP4_Pos, PORT_P0_PUDEN_PP4_Msk, 1u);
}

INLINE void PORT_P04_PullUpDown_Dis()
{
  Field_Mod32(&PORT->P0_PUDEN.reg, (uint8)PORT_P0_PUDEN_PP4_Pos, PORT_P0_PUDEN_PP4_Msk, 0u);
}

INLINE void PORT_P05_PullUpDown_En()
{
  Field_Mod32(&PORT->P0_PUDEN.reg, (uint8)PORT_P0_PUDEN_PP5_Pos, PORT_P0_PUDEN_PP5_Msk, 1u);
}

INLINE void PORT_P05_PullUpDown_Dis()
{
  Field_Mod32(&PORT->P0_PUDEN.reg, (uint8)PORT_P0_PUDEN_PP5_Pos, PORT_P0_PUDEN_PP5_Msk, 0u);
}

INLINE void PORT_P00_PullUp_Set()
{
  Field_Mod32(&PORT->P0_PUDSEL.reg, (uint8)PORT_P0_PUDSEL_PP0_Pos, PORT_P0_PUDSEL_PP0_Msk, 1u);
}

INLINE void PORT_P00_PullDown_Set()
{
  Field_Mod32(&PORT->P0_PUDSEL.reg, (uint8)PORT_P0_PUDSEL_PP0_Pos, PORT_P0_PUDSEL_PP0_Msk, 0u);
}

INLINE void PORT_P01_PullUp_Set()
{
  Field_Mod32(&PORT->P0_PUDSEL.reg, (uint8)PORT_P0_PUDSEL_PP1_Pos, PORT_P0_PUDSEL_PP1_Msk, 1u);
}

INLINE void PORT_P01_PullDown_Set()
{
  Field_Mod32(&PORT->P0_PUDSEL.reg, (uint8)PORT_P0_PUDSEL_PP1_Pos, PORT_P0_PUDSEL_PP1_Msk, 0u);
}

INLINE void PORT_P02_PullUp_Set()
{
  Field_Mod32(&PORT->P0_PUDSEL.reg, (uint8)PORT_P0_PUDSEL_PP2_Pos, PORT_P0_PUDSEL_PP2_Msk, 1u);
}

INLINE void PORT_P02_PullDown_Set()
{
  Field_Mod32(&PORT->P0_PUDSEL.reg, (uint8)PORT_P0_PUDSEL_PP2_Pos, PORT_P0_PUDSEL_PP2_Msk, 0u);
}

INLINE void PORT_P03_PullUp_Set()
{
  Field_Mod32(&PORT->P0_PUDSEL.reg, (uint8)PORT_P0_PUDSEL_PP3_Pos, PORT_P0_PUDSEL_PP3_Msk, 1u);
}

INLINE void PORT_P03_PullDown_Set()
{
  Field_Mod32(&PORT->P0_PUDSEL.reg, (uint8)PORT_P0_PUDSEL_PP3_Pos, PORT_P0_PUDSEL_PP3_Msk, 0u);
}

INLINE void PORT_P04_PullUp_Set()
{
  Field_Mod32(&PORT->P0_PUDSEL.reg, (uint8)PORT_P0_PUDSEL_PP4_Pos, PORT_P0_PUDSEL_PP4_Msk, 1u);
}

INLINE void PORT_P04_PullDown_Set()
{
  Field_Mod32(&PORT->P0_PUDSEL.reg, (uint8)PORT_P0_PUDSEL_PP4_Pos, PORT_P0_PUDSEL_PP4_Msk, 0u);
}

INLINE void PORT_P05_PullUp_Set()
{
  Field_Mod32(&PORT->P0_PUDSEL.reg, (uint8)PORT_P0_PUDSEL_PP5_Pos, PORT_P0_PUDSEL_PP5_Msk, 1u);
}

INLINE void PORT_P05_PullDown_Set()
{
  Field_Mod32(&PORT->P0_PUDSEL.reg, (uint8)PORT_P0_PUDSEL_PP5_Pos, PORT_P0_PUDSEL_PP5_Msk, 0u);
}

INLINE void PORT_P00_Driver_Mode_Sel(uint8 mode)
{
  Field_Mod32(&SCU->P0_POCON0.reg, (uint8)SCU_P0_POCON0_P0_PDM0_Pos, SCU_P0_POCON0_P0_PDM0_Msk, mode);
}

INLINE void PORT_P01_Driver_Mode_Sel(uint8 mode)
{
  Field_Mod32(&SCU->P0_POCON0.reg, (uint8)SCU_P0_POCON0_P0_PDM1_Pos, SCU_P0_POCON0_P0_PDM1_Msk, mode);
}

INLINE void PORT_P02_Driver_Mode_Sel(uint8 mode)
{
  Field_Mod32(&SCU->P0_POCON0.reg, (uint8)SCU_P0_POCON0_P0_PDM2_Pos, SCU_P0_POCON0_P0_PDM2_Msk, mode);
}

INLINE void PORT_P03_Driver_Mode_Sel(uint8 mode)
{
  Field_Mod32(&SCU->P0_POCON0.reg, (uint8)SCU_P0_POCON0_P0_PDM3_Pos, SCU_P0_POCON0_P0_PDM3_Msk, mode);
}

INLINE void PORT_P04_Driver_Mode_Sel(uint8 mode)
{
  Field_Mod32(&SCU->P0_POCON0.reg, (uint8)SCU_P0_POCON0_P0_PDM4_Pos, SCU_P0_POCON0_P0_PDM4_Msk, mode);
}

INLINE void PORT_P05_Driver_Mode_Sel(uint8 mode)
{
  Field_Mod32(&SCU->P0_POCON0.reg, (uint8)SCU_P0_POCON0_P0_PDM5_Pos, SCU_P0_POCON0_P0_PDM5_Msk, mode);
}

INLINE void PORT_P10_Output_Set()
{
  Field_Mod32(&PORT->P1_DIR.reg, (uint8)PORT_P1_DIR_PP0_Pos, PORT_P1_DIR_PP0_Msk, 1u);
}

INLINE void PORT_P10_Input_Set()
{
  Field_Mod32(&PORT->P1_DIR.reg, (uint8)PORT_P1_DIR_PP0_Pos, PORT_P1_DIR_PP0_Msk, 0u);
}

INLINE void PORT_P11_Output_Set()
{
  Field_Mod32(&PORT->P1_DIR.reg, (uint8)PORT_P1_DIR_PP1_Pos, PORT_P1_DIR_PP1_Msk, 1u);
}

INLINE void PORT_P11_Input_Set()
{
  Field_Mod32(&PORT->P1_DIR.reg, (uint8)PORT_P1_DIR_PP1_Pos, PORT_P1_DIR_PP1_Msk, 0u);
}

INLINE void PORT_P12_Output_Set()
{
  Field_Mod32(&PORT->P1_DIR.reg, (uint8)PORT_P1_DIR_PP2_Pos, PORT_P1_DIR_PP2_Msk, 1u);
}

INLINE void PORT_P12_Input_Set()
{
  Field_Mod32(&PORT->P1_DIR.reg, (uint8)PORT_P1_DIR_PP2_Pos, PORT_P1_DIR_PP2_Msk, 0u);
}

INLINE void PORT_P14_Output_Set()
{
  Field_Mod32(&PORT->P1_DIR.reg, (uint8)PORT_P1_DIR_PP4_Pos, PORT_P1_DIR_PP4_Msk, 1u);
}

INLINE void PORT_P14_Input_Set()
{
  Field_Mod32(&PORT->P1_DIR.reg, (uint8)PORT_P1_DIR_PP4_Pos, PORT_P1_DIR_PP4_Msk, 0u);
}

INLINE void PORT_P10_Output_High_Set()
{
  Field_Mod32(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_PP0_Pos, PORT_P1_DATA_PP0_Msk, 1u);
}

INLINE void PORT_P10_Output_Low_Set()
{
  Field_Mod32(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_PP0_Pos, PORT_P1_DATA_PP0_Msk, 0u);
}

INLINE void PORT_P10_Output_Toggle_Set()
{
  Field_Inv32(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_PP0_Msk);
}

INLINE void PORT_P11_Output_High_Set()
{
  Field_Mod32(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_PP1_Pos, PORT_P1_DATA_PP1_Msk, 1u);
}

INLINE void PORT_P11_Output_Low_Set()
{
  Field_Mod32(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_PP1_Pos, PORT_P1_DATA_PP1_Msk, 0u);
}

INLINE void PORT_P11_Output_Toggle_Set()
{
  Field_Inv32(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_PP1_Msk);
}

INLINE void PORT_P12_Output_High_Set()
{
  Field_Mod32(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_PP2_Pos, PORT_P1_DATA_PP2_Msk, 1u);
}

INLINE void PORT_P12_Output_Low_Set()
{
  Field_Mod32(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_PP2_Pos, PORT_P1_DATA_PP2_Msk, 0u);
}

INLINE void PORT_P12_Output_Toggle_Set()
{
  Field_Inv32(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_PP2_Msk);
}

INLINE void PORT_P14_Output_High_Set()
{
  Field_Mod32(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_PP4_Pos, PORT_P1_DATA_PP4_Msk, 1u);
}

INLINE void PORT_P14_Output_Low_Set()
{
  Field_Mod32(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_PP4_Pos, PORT_P1_DATA_PP4_Msk, 0u);
}

INLINE void PORT_P14_Output_Toggle_Set()
{
  Field_Inv32(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_PP4_Msk);
}

INLINE uint8 PORT_P10_Get()
{
  return(u1_Field_Rd32(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_PP0_Pos, PORT_P1_DATA_PP0_Msk));
}

INLINE uint8 PORT_P11_Get()
{
  return(u1_Field_Rd32(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_PP1_Pos, PORT_P1_DATA_PP1_Msk));
}

INLINE uint8 PORT_P12_Get()
{
  return(u1_Field_Rd32(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_PP2_Pos, PORT_P1_DATA_PP2_Msk));
}

INLINE uint8 PORT_P14_Get()
{
  return(u1_Field_Rd32(&PORT->P1_DATA.reg, (uint8)PORT_P1_DATA_PP4_Pos, PORT_P1_DATA_PP4_Msk));
}

INLINE void PORT_P10_OpenDrain_En()
{
  Field_Mod32(&PORT->P1_OD.reg, (uint8)PORT_P1_OD_PP0_Pos, PORT_P1_OD_PP0_Msk, 1u);
}

INLINE void PORT_P10_OpenDrain_Dis()
{
  Field_Mod32(&PORT->P1_OD.reg, (uint8)PORT_P1_OD_PP0_Pos, PORT_P1_OD_PP0_Msk, 0u);
}

INLINE void PORT_P11_OpenDrain_En()
{
  Field_Mod32(&PORT->P1_OD.reg, (uint8)PORT_P1_OD_PP1_Pos, PORT_P1_OD_PP1_Msk, 1u);
}

INLINE void PORT_P11_OpenDrain_Dis()
{
  Field_Mod32(&PORT->P1_OD.reg, (uint8)PORT_P1_OD_PP1_Pos, PORT_P1_OD_PP1_Msk, 0u);
}

INLINE void PORT_P12_OpenDrain_En()
{
  Field_Mod32(&PORT->P1_OD.reg, (uint8)PORT_P1_OD_PP2_Pos, PORT_P1_OD_PP2_Msk, 1u);
}

INLINE void PORT_P12_OpenDrain_Dis()
{
  Field_Mod32(&PORT->P1_OD.reg, (uint8)PORT_P1_OD_PP2_Pos, PORT_P1_OD_PP2_Msk, 0u);
}

INLINE void PORT_P14_OpenDrain_En()
{
  Field_Mod32(&PORT->P1_OD.reg, (uint8)PORT_P1_OD_PP4_Pos, PORT_P1_OD_PP4_Msk, 1u);
}

INLINE void PORT_P14_OpenDrain_Dis()
{
  Field_Mod32(&PORT->P1_OD.reg, (uint8)PORT_P1_OD_PP4_Pos, PORT_P1_OD_PP4_Msk, 0u);
}

INLINE void PORT_P10_PullUpDown_En()
{
  Field_Mod32(&PORT->P1_PUDEN.reg, (uint8)PORT_P1_PUDEN_PP0_Pos, PORT_P1_PUDEN_PP0_Msk, 1u);
}

INLINE void PORT_P10_PullUpDown_Dis()
{
  Field_Mod32(&PORT->P1_PUDEN.reg, (uint8)PORT_P1_PUDEN_PP0_Pos, PORT_P1_PUDEN_PP0_Msk, 0u);
}

INLINE void PORT_P11_PullUpDown_En()
{
  Field_Mod32(&PORT->P1_PUDEN.reg, (uint8)PORT_P1_PUDEN_PP1_Pos, PORT_P1_PUDEN_PP1_Msk, 1u);
}

INLINE void PORT_P11_PullUpDown_Dis()
{
  Field_Mod32(&PORT->P1_PUDEN.reg, (uint8)PORT_P1_PUDEN_PP1_Pos, PORT_P1_PUDEN_PP1_Msk, 0u);
}

INLINE void PORT_P12_PullUpDown_En()
{
  Field_Mod32(&PORT->P1_PUDEN.reg, (uint8)PORT_P1_PUDEN_PP2_Pos, PORT_P1_PUDEN_PP2_Msk, 1u);
}

INLINE void PORT_P12_PullUpDown_Dis()
{
  Field_Mod32(&PORT->P1_PUDEN.reg, (uint8)PORT_P1_PUDEN_PP2_Pos, PORT_P1_PUDEN_PP2_Msk, 0u);
}

INLINE void PORT_P14_PullUpDown_En()
{
  Field_Mod32(&PORT->P1_PUDEN.reg, (uint8)PORT_P1_PUDEN_PP4_Pos, PORT_P1_PUDEN_PP4_Msk, 1u);
}

INLINE void PORT_P14_PullUpDown_Dis()
{
  Field_Mod32(&PORT->P1_PUDEN.reg, (uint8)PORT_P1_PUDEN_PP4_Pos, PORT_P1_PUDEN_PP4_Msk, 0u);
}

INLINE void PORT_P10_PullUp_Set()
{
  Field_Mod32(&PORT->P1_PUDSEL.reg, (uint8)PORT_P1_PUDSEL_PP0_Pos, PORT_P1_PUDSEL_PP0_Msk, 1u);
}

INLINE void PORT_P10_PullDown_Set()
{
  Field_Mod32(&PORT->P1_PUDSEL.reg, (uint8)PORT_P1_PUDSEL_PP0_Pos, PORT_P1_PUDSEL_PP0_Msk, 0u);
}

INLINE void PORT_P11_PullUp_Set()
{
  Field_Mod32(&PORT->P1_PUDSEL.reg, (uint8)PORT_P1_PUDSEL_PP1_Pos, PORT_P1_PUDSEL_PP1_Msk, 1u);
}

INLINE void PORT_P11_PullDown_Set()
{
  Field_Mod32(&PORT->P1_PUDSEL.reg, (uint8)PORT_P1_PUDSEL_PP1_Pos, PORT_P1_PUDSEL_PP1_Msk, 0u);
}

INLINE void PORT_P12_PullUp_Set()
{
  Field_Mod32(&PORT->P1_PUDSEL.reg, (uint8)PORT_P1_PUDSEL_PP2_Pos, PORT_P1_PUDSEL_PP2_Msk, 1u);
}

INLINE void PORT_P12_PullDown_Set()
{
  Field_Mod32(&PORT->P1_PUDSEL.reg, (uint8)PORT_P1_PUDSEL_PP2_Pos, PORT_P1_PUDSEL_PP2_Msk, 0u);
}

INLINE void PORT_P14_PullUp_Set()
{
  Field_Mod32(&PORT->P1_PUDSEL.reg, (uint8)PORT_P1_PUDSEL_PP4_Pos, PORT_P1_PUDSEL_PP4_Msk, 1u);
}

INLINE void PORT_P14_PullDown_Set()
{
  Field_Mod32(&PORT->P1_PUDSEL.reg, (uint8)PORT_P1_PUDSEL_PP4_Pos, PORT_P1_PUDSEL_PP4_Msk, 0u);
}

INLINE void PORT_P10_Driver_Mode_Sel(uint8 mode)
{
  Field_Mod32(&SCU->P1_POCON0.reg, (uint8)SCU_P1_POCON0_P1_PDM0_Pos, SCU_P1_POCON0_P1_PDM0_Msk, mode);
}

INLINE void PORT_P11_Driver_Mode_Sel(uint8 mode)
{
  Field_Mod32(&SCU->P1_POCON0.reg, (uint8)SCU_P1_POCON0_P1_PDM1_Pos, SCU_P1_POCON0_P1_PDM1_Msk, mode);
}

INLINE void PORT_P12_Driver_Mode_Sel(uint8 mode)
{
  Field_Mod32(&SCU->P1_POCON0.reg, (uint8)SCU_P1_POCON0_P1_PDM2_Pos, SCU_P1_POCON0_P1_PDM2_Msk, mode);
}

INLINE void PORT_P14_Driver_Mode_Sel(uint8 mode)
{
  Field_Mod32(&SCU->P1_POCON0.reg, (uint8)SCU_P1_POCON0_P1_PDM4_Pos, SCU_P1_POCON0_P1_PDM4_Msk, mode);
}

INLINE void PORT_P20_Dis()
{
  Field_Mod32(&PORT->P2_DIR.reg, (uint8)PORT_P2_DIR_PP0_Pos, PORT_P2_DIR_PP0_Msk, 1u);
}

INLINE void PORT_P20_Input_Set()
{
  Field_Mod32(&PORT->P2_DIR.reg, (uint8)PORT_P2_DIR_PP0_Pos, PORT_P2_DIR_PP0_Msk, 0u);
}

INLINE void PORT_P21_Dis()
{
  Field_Mod32(&PORT->P2_DIR.reg, (uint8)PORT_P2_DIR_PP1_Pos, PORT_P2_DIR_PP1_Msk, 1u);
}

INLINE void PORT_P21_Input_Set()
{
  Field_Mod32(&PORT->P2_DIR.reg, (uint8)PORT_P2_DIR_PP1_Pos, PORT_P2_DIR_PP1_Msk, 0u);
}

INLINE void PORT_P22_Dis()
{
  Field_Mod32(&PORT->P2_DIR.reg, (uint8)PORT_P2_DIR_PP2_Pos, PORT_P2_DIR_PP2_Msk, 1u);
}

INLINE void PORT_P22_Input_Set()
{
  Field_Mod32(&PORT->P2_DIR.reg, (uint8)PORT_P2_DIR_PP2_Pos, PORT_P2_DIR_PP2_Msk, 0u);
}

INLINE void PORT_P23_Dis()
{
  Field_Mod32(&PORT->P2_DIR.reg, (uint8)PORT_P2_DIR_PP3_Pos, PORT_P2_DIR_PP3_Msk, 1u);
}

INLINE void PORT_P23_Input_Set()
{
  Field_Mod32(&PORT->P2_DIR.reg, (uint8)PORT_P2_DIR_PP3_Pos, PORT_P2_DIR_PP3_Msk, 0u);
}

INLINE void PORT_P27_Dis()
{
  Field_Mod32(&PORT->P2_DIR.reg, (uint8)PORT_P2_DIR_PP7_Pos, PORT_P2_DIR_PP7_Msk, 1u);
}

INLINE void PORT_P27_Input_Set()
{
  Field_Mod32(&PORT->P2_DIR.reg, (uint8)PORT_P2_DIR_PP7_Pos, PORT_P2_DIR_PP7_Msk, 0u);
}

INLINE uint8 PORT_P20_Get()
{
  return(u1_Field_Rd32(&PORT->P2_DATA.reg, (uint8)PORT_P2_DATA_PP0_Pos, PORT_P2_DATA_PP0_Msk));
}

INLINE uint8 PORT_P21_Get()
{
  return(u1_Field_Rd32(&PORT->P2_DATA.reg, (uint8)PORT_P2_DATA_PP1_Pos, PORT_P2_DATA_PP1_Msk));
}

INLINE uint8 PORT_P22_Get()
{
  return(u1_Field_Rd32(&PORT->P2_DATA.reg, (uint8)PORT_P2_DATA_PP2_Pos, PORT_P2_DATA_PP2_Msk));
}

INLINE uint8 PORT_P23_Get()
{
  return(u1_Field_Rd32(&PORT->P2_DATA.reg, (uint8)PORT_P2_DATA_PP3_Pos, PORT_P2_DATA_PP3_Msk));
}

INLINE uint8 PORT_P27_Get()
{
  return(u1_Field_Rd32(&PORT->P2_DATA.reg, (uint8)PORT_P2_DATA_PP7_Pos, PORT_P2_DATA_PP7_Msk));
}

INLINE void PORT_P20_PullUpDown_En()
{
  Field_Mod32(&PORT->P2_PUDEN.reg, (uint8)PORT_P2_PUDEN_PP0_Pos, PORT_P2_PUDEN_PP0_Msk, 1u);
}

INLINE void PORT_P20_PullUpDown_Dis()
{
  Field_Mod32(&PORT->P2_PUDEN.reg, (uint8)PORT_P2_PUDEN_PP0_Pos, PORT_P2_PUDEN_PP0_Msk, 0u);
}

INLINE void PORT_P21_PullUpDown_En()
{
  Field_Mod32(&PORT->P2_PUDEN.reg, (uint8)PORT_P2_PUDEN_PP1_Pos, PORT_P2_PUDEN_PP1_Msk, 1u);
}

INLINE void PORT_P21_PullUpDown_Dis()
{
  Field_Mod32(&PORT->P2_PUDEN.reg, (uint8)PORT_P2_PUDEN_PP1_Pos, PORT_P2_PUDEN_PP1_Msk, 0u);
}

INLINE void PORT_P22_PullUpDown_En()
{
  Field_Mod32(&PORT->P2_PUDEN.reg, (uint8)PORT_P2_PUDEN_PP2_Pos, PORT_P2_PUDEN_PP2_Msk, 1u);
}

INLINE void PORT_P22_PullUpDown_Dis()
{
  Field_Mod32(&PORT->P2_PUDEN.reg, (uint8)PORT_P2_PUDEN_PP2_Pos, PORT_P2_PUDEN_PP2_Msk, 0u);
}

INLINE void PORT_P23_PullUpDown_En()
{
  Field_Mod32(&PORT->P2_PUDEN.reg, (uint8)PORT_P2_PUDEN_PP3_Pos, PORT_P2_PUDEN_PP3_Msk, 1u);
}

INLINE void PORT_P23_PullUpDown_Dis()
{
  Field_Mod32(&PORT->P2_PUDEN.reg, (uint8)PORT_P2_PUDEN_PP3_Pos, PORT_P2_PUDEN_PP3_Msk, 0u);
}

INLINE void PORT_P27_PullUpDown_En()
{
  Field_Mod32(&PORT->P2_PUDEN.reg, (uint8)PORT_P2_PUDEN_PP7_Pos, PORT_P2_PUDEN_PP7_Msk, 1u);
}

INLINE void PORT_P27_PullUpDown_Dis()
{
  Field_Mod32(&PORT->P2_PUDEN.reg, (uint8)PORT_P2_PUDEN_PP7_Pos, PORT_P2_PUDEN_PP7_Msk, 0u);
}

INLINE void PORT_P20_PullUp_Set()
{
  Field_Mod32(&PORT->P2_PUDSEL.reg, (uint8)PORT_P2_PUDSEL_PP0_Pos, PORT_P2_PUDSEL_PP0_Msk, 1u);
}

INLINE void PORT_P20_PullDown_Set()
{
  Field_Mod32(&PORT->P2_PUDSEL.reg, (uint8)PORT_P2_PUDSEL_PP0_Pos, PORT_P2_PUDSEL_PP0_Msk, 0u);
}

INLINE void PORT_P21_PullUp_Set()
{
  Field_Mod32(&PORT->P2_PUDSEL.reg, (uint8)PORT_P2_PUDSEL_PP1_Pos, PORT_P2_PUDSEL_PP1_Msk, 1u);
}

INLINE void PORT_P21_PullDown_Set()
{
  Field_Mod32(&PORT->P2_PUDSEL.reg, (uint8)PORT_P2_PUDSEL_PP1_Pos, PORT_P2_PUDSEL_PP1_Msk, 0u);
}

INLINE void PORT_P22_PullUp_Set()
{
  Field_Mod32(&PORT->P2_PUDSEL.reg, (uint8)PORT_P2_PUDSEL_PP2_Pos, PORT_P2_PUDSEL_PP2_Msk, 1u);
}

INLINE void PORT_P22_PullDown_Set()
{
  Field_Mod32(&PORT->P2_PUDSEL.reg, (uint8)PORT_P2_PUDSEL_PP2_Pos, PORT_P2_PUDSEL_PP2_Msk, 0u);
}

INLINE void PORT_P23_PullUp_Set()
{
  Field_Mod32(&PORT->P2_PUDSEL.reg, (uint8)PORT_P2_PUDSEL_PP3_Pos, PORT_P2_PUDSEL_PP3_Msk, 1u);
}

INLINE void PORT_P23_PullDown_Set()
{
  Field_Mod32(&PORT->P2_PUDSEL.reg, (uint8)PORT_P2_PUDSEL_PP3_Pos, PORT_P2_PUDSEL_PP3_Msk, 0u);
}

INLINE void PORT_P27_PullUp_Set()
{
  Field_Mod32(&PORT->P2_PUDSEL.reg, (uint8)PORT_P2_PUDSEL_PP7_Pos, PORT_P2_PUDSEL_PP7_Msk, 1u);
}

INLINE void PORT_P27_PullDown_Set()
{
  Field_Mod32(&PORT->P2_PUDSEL.reg, (uint8)PORT_P2_PUDSEL_PP7_Pos, PORT_P2_PUDSEL_PP7_Msk, 0u);
}

INLINE void PORT_Temp_Comp_Sel(uint8 range)
{
  Field_Wrt32(&SCU->TCCR.reg, (uint8)SCU_TCCR_TCC_Pos, SCU_TCCR_TCC_Msk, range);
}  

#endif /* PORT_H */
