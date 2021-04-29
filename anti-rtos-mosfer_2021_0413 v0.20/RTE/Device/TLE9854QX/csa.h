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
 * \file     csa.h
 *
 * \brief    Current Sense Amplifier low level access library
 *
 * \version  V0.2.2
 * \date     02. Mar 2020
 *
 * \note This file violates [MISRA 2012 Rule 11.1, required], [MISRA 2012 Rule 11.4, advisory], [MISRA 2012 Rule 11.6, required]
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
** V0.2.0: 2018-02-13, TS:   Initial version                                  **
** V0.2.1: 2019-01-28, TS:   __STATIC_INLINE changed to INLINE                **
**                           Doxygen update                                   **
**                           Revision history moved from csa.c to csa.h       **
** V0.2.2: 2020-03-02, BG:   Updated revision history format                  **
*******************************************************************************/

#ifndef CSA_H
#define CSA_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle985x.h"
#include "types.h"
#include "sfr_access.h"

/*******************************************************************************
**                        Global Constant Declarations                        **
*******************************************************************************/
/** \enum TCSA_Gain
 *  \brief This enum lists the CSA Gain Settings.
 */
typedef enum
{
  CSA_GAIN_10  = 0, /**< Operational Amplifier Gain Factor 10 */
  CSA_GAIN_20  = 1, /**< Operational Amplifier Gain Factor 20 */
  CSA_GAIN_40  = 2, /**< Operational Amplifier Gain Factor 40 */
  CSA_GAIN_60  = 3  /**< Operational Amplifier Gain Factor 60 */
} TCSA_Gain;

/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/
/** \brief Initializes the CSA module.
 *
 * \ingroup csa_api
 */
void CSA_Init(void);

/*******************************************************************************
**                        Inline Function Declarations                        **
*******************************************************************************/
/** \brief Switches on CSA.
 *
 * \brief <b>Example</b><br>
 * \brief This example switches on CSA.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CSA_Power_On();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup csa_api
 */
INLINE void CSA_Power_On(void);

/** \brief Switches off CSA.
 *
 * \brief <b>Example</b><br>
 * \brief This example switches off CSA.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CSA_Power_Off();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup csa_api
 */
INLINE void CSA_Power_Off(void);

/** \brief Sets CSA Gain value.
 *
 * \param gain Gain setting, see \link TCSA_Gain \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example configures CSA Gain value to 40.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CSA_Set_Gain(CSA_GAIN_40);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup csa_api
 */
INLINE void CSA_Set_Gain(TCSA_Gain gain);

/*******************************************************************************
**                         Inline Function Definitions                        **
*******************************************************************************/
INLINE void CSA_Power_On()
{
  Field_Mod32(&MF->CSA_CTRL.reg, (uint8)MF_CSA_CTRL_CSA_EN_Pos, MF_CSA_CTRL_CSA_EN_Msk, 1u);
}

INLINE void CSA_Power_Off()
{
  Field_Mod32(&MF->CSA_CTRL.reg, (uint8)MF_CSA_CTRL_CSA_EN_Pos, MF_CSA_CTRL_CSA_EN_Msk, 0u);
}

INLINE void CSA_Set_Gain(TCSA_Gain gain)
{
  Field_Mod32(&MF->CSA_CTRL.reg, (uint8)MF_CSA_CTRL_CSA_GAIN_Pos, MF_CSA_CTRL_CSA_GAIN_Msk, (uint32)gain);
}

#endif
