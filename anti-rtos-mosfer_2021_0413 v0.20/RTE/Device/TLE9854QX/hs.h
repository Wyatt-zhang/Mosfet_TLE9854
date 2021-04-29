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
 * \file     hs.h
 *
 * \brief    High-Side Switch low level access library
 *
 * \version  V0.2.3
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
** V0.2.0: 2018-02-13, TS:   Initial version of revision history              **
** V0.2.1: 2018-10-17, TS:   PWMSRCSEL initialization added                   **
** V0.2.2: 2019-01-28, TS:   __STATIC_INLINE changed to INLINE                **
**                           Doxygen update                                   **
**                           Revision history moved from hs.c to hs.h         **
**                           New Mask Macros added                            **
** V0.2.3: 2020-03-02, BG:   Updated revision history format                  **
*******************************************************************************/

#ifndef HS_H
#define HS_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle985x.h"
#include "types.h"
#include "sfr_access.h"

/*******************************************************************************
**                        Global Constant Declarations                        **
*******************************************************************************/
/**\brief HS Interrupt Mask */
#define HS_IRQ_BITS 0x000000E0

/**\brief HS Interrupt Mask */
#define HS_CONF_MASK 0x0000000F

/*******************************************************************************
**                          Global Type Definitions                           **
*******************************************************************************/
/** \enum THs_HS1_Cfg
 *  \brief This enum lists the High Side channel configuration.
 */
typedef enum
{
  Ch_HS_Off = 0u,  /**< \brief channel disabled                               */
  Ch_HS_En  = 1u,  /**< \brief channel enabled                                */
  Ch_HS_PWM = 3u,  /**< \brief channel enabled with PWM (CCU6 connection)     */
  Ch_HS_On  = 5u,  /**< \brief channel enabled and static on                  */
  Ch_HS_Ol  = 9u   /**< \brief channel enabled and Open Load on               */
} THs_HS1_Cfg;

/** \enum THs_Sts
 *  \brief This enum lists the High Side channel configuration Mask Status.
 */
typedef enum
{
  HS_OT_ISC   = 0x00000020u, /**< \brief Over-Temperature interrupt Mask      */
  HS_OL_ISC   = 0x00000040u, /**< \brief Over-Load interrupt Mask             */
  HS_OC_ISC   = 0x00000080u, /**< \brief Over-Current interrupt Mask          */
  HS_OT_SC    = 0x00002000u, /**< \brief Over-Temperature Mask                */
  HS_OL_SC    = 0x00004000u  /**< \brief Over-Load Mask                       */
} THs_Sts;

/** \enum THs_Int
 *  \brief This enum lists the High Side channel Interrupt configuration.
 */
typedef enum
{
  HS_Int_Off = 0U,  /**< \brief all interrupts disable                        */
  HS_Int_OT = 1U,   /**< \brief Over-Temperature interrupt enable             */
  HS_Int_OL = 2U,   /**< \brief Over-Load interrupt enable                    */
  HS_Int_OC = 4U    /**< \brief Over-Current interrupt enable                 */
} THs_Int;

/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/
/** \brief Initializes the HS module.
 *
 * \ingroup hs_api
 */
void HS_Init(void);

/*******************************************************************************
**                        Inline Function Declarations                        **
*******************************************************************************/
/** \brief Clears High-Side Switch individual status flags
 *
 * \param Sts_Bit status bit to be cleared, see \link THs_Sts \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the HS1 Open Load Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   HS_HS1_OL_Int_En();
 *   if (HS->IRQS.bit.HS1_OL_IS == 1u)
 *   {
 *     HS_HS1_OL_CALLBACK();
 *     HS_Clr_Sts(HS_OL_ISC);
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup hs_api
 */
INLINE void HS_Clr_Sts(THs_Sts Sts_Bit);

/** \brief Sets High-Side Switch Interrupt Enable
 *
 * \param HS1_Int Interrupt selection, see \link THs_Int \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the HS1 Overcurrent interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   HS_Set_Int_Channel(Int_OC);
 *   if (HS->IRQS.bit.HS1_OC_IS == 1u)
 *   {
 *     HS_HS1_OC_CALLBACK();
 *     HS_HS1_OC_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup hs_api
 */
INLINE void HS_Set_Int_Channel(THs_Int HS1_Int);

/** \brief Sets the High-Side Switch in the desired state
 *
 * \param HS1_Cfg HS1 Configuration, see \link THs_HS1_Cfg \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example enables and configures the HS1 with PWM.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     HS_Set_Conf(Ch_HS_PWM);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup hs_api
 */
INLINE void HS_Set_Conf(THs_HS1_Cfg HS1_Cfg);

/** \brief Clears HS1 Overtemperature interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears HS1 Overtemperature interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   HS_HS1_OT_Int_En();
 *   if (HS->IRQS.bit.HS1_OT_IS == 1u)
 *   {
 *     HS_HS1_OT_CALLBACK();
 *     HS_HS1_OT_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup hs_api
 */
INLINE void HS_HS1_OT_Int_Clr(void);

/** \brief Clears HS1 Open Load interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the HS1 Open Load interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   HS_HS1_OL_Int_En();
 *   if (HS->IRQS.bit.HS1_OL_IS == 1u)
 *   {
 *     HS_HS1_OL_CALLBACK();
 *     HS_HS1_OL_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup hs_api
 */
INLINE void HS_HS1_OL_Int_Clr(void);

/** \brief Clears HS1 Overcurrent interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the HS1 Overcurrent interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   HS_HS1_OC_Int_En();
 *   if (HS->IRQS.bit.HS1_OC_IS == 1u)
 *   {
 *     HS_HS1_OC_CALLBACK();
 *     HS_HS1_OC_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup hs_api
 */
INLINE void HS_HS1_OC_Int_Clr(void);

/** \brief Clears HS1 Overtemperature Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears HS1 Overtemperature Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   if (HS->IRQS.bit.HS1_OT_STS == 1u)
 *   {
 *     HS_HS1_OT_SC_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup hs_api
 */
INLINE void HS_HS1_OT_SC_Clr(void);

/** \brief Clears HS1 Open Load Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears HS1 Open Load Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   if (HS->IRQS.bit.HS1_OL_STS == 1u)
 *   {
 *     HS_HS1_OL_SC_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup hs_api
 */
INLINE void HS_HS1_OL_SC_Clr(void);

/** \brief Enables HS1 Overtemperature interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the HS1 Overtemperature interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   HS_HS1_OT_Int_En();
 *   if (HS->IRQS.bit.HS1_OT_IS == 1u)
 *   {
 *     HS_HS1_OT_CALLBACK();
 *     HS_HS1_OT_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup hs_api
 */
INLINE void HS_HS1_OT_Int_En(void);

/** \brief Disables HS1 Overtemperature interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the HS1 Overtemperature interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   HS_HS1_OT_Int_En();
 *   if (HS->IRQS.bit.HS1_OT_IS == 1u)
 *   {
 *     HS_HS1_OT_CALLBACK();
 *     HS_HS1_OT_Int_Clr();
 *   }
 *   HS_HS1_OT_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup hs_api
 */
INLINE void HS_HS1_OT_Int_Dis(void);

/** \brief Enables HS1 Open Load interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the HS1 Open Load interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   HS_HS1_OL_Int_En();
 *   if (HS->IRQS.bit.HS1_OL_IS == 1u)
 *   {
 *     HS_HS1_OL_CALLBACK();
 *     HS_HS1_OL_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup hs_api
 */
INLINE void HS_HS1_OL_Int_En(void);

/** \brief Disables HS1 Open Load interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the HS1 Open Load interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   HS_HS1_OL_Int_En();
 *   if (HS->IRQS.bit.HS1_OL_IS == 1u)
 *   {
 *     HS_HS1_OL_CALLBACK();
 *     HS_HS1_OL_Int_Clr();
 *   }
 *   HS_HS1_OL_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup hs_api
 */
INLINE void HS_HS1_OL_Int_Dis(void);

/** \brief Enables HS1 Overcurrent interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the HS1 Overcurrent interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   HS_HS1_OC_Int_En();
 *   if (HS->IRQS.bit.HS1_OC_IS == 1u)
 *   {
 *     HS_HS1_OC_CALLBACK();
 *     HS_HS1_OC_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup hs_api
 */
INLINE void HS_HS1_OC_Int_En(void);

/** \brief Disables HS1 Overcurrent interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the HS1 Overcurrent interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   HS_HS1_OC_Int_En();
 *   if (HS->IRQS.bit.HS1_OC_IS == 1u)
 *   {
 *     HS_HS1_OC_CALLBACK();
 *     HS_HS1_OC_Int_Clr();
 *   }
 *   HS_HS1_OC_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup hs_api
 */
INLINE void HS_HS1_OC_Int_Dis(void);

/*******************************************************************************
**                         Inline Function Definitions                        **
*******************************************************************************/
INLINE void HS_Set_Int_Channel(THs_Int HS1_Int)
{
  /* set HS1_Int */
  Field_Mod32(&HS->IRQEN.reg, (uint8)HS_IRQEN_HS1_OT_IEN_Pos, ((uint32)HS1_Int << (uint8)5), (uint32)HS1_Int);

  /* enable HS interrupt node */
  if (u16_Field_Rd32(&HS->IRQEN.reg, (uint8)(uint32)HS_IRQEN_HS1_OT_IEN_Pos, (uint32)HS_IRQ_BITS) != (uint16)0u)
  {
    Field_Mod32(&CPU->NVIC_ISER.reg, (uint8)CPU_NVIC_ISER_Int_HS_Pos, CPU_NVIC_ISER_Int_HS_Msk, 1u);
  }
}

INLINE void HS_Clr_Sts(THs_Sts Sts_Bit)
{
  Field_Wrt32all(&HS->IRQCLR.reg, (uint32)Sts_Bit);
  /* add an extra clear access in order to ensure the clear of           */
  /* the status flags is executed before the status flags are read again */
  Field_Wrt32all(&HS->IRQCLR.reg, (uint32)0);
}

INLINE void HS_Set_Conf(THs_HS1_Cfg HS1_Cfg)
{
  Field_Mod32(&HS->CTRL.reg, (uint8)HS_CTRL_HS1_EN_Pos, HS_CONF_MASK, (uint8)HS1_Cfg);
}

INLINE void HS_HS1_OT_Int_Clr()
{
  Field_Wrt32(&HS->IRQCLR.reg, (uint8)HS_IRQCLR_HS1_OT_ISC_Pos, HS_IRQCLR_HS1_OT_ISC_Msk, 1u);
}

INLINE void HS_HS1_OL_Int_Clr()
{
  Field_Wrt32(&HS->IRQCLR.reg, (uint8)HS_IRQCLR_HS1_OL_ISC_Pos, HS_IRQCLR_HS1_OL_ISC_Msk, 1u);
}

INLINE void HS_HS1_OC_Int_Clr()
{
  Field_Wrt32(&HS->IRQCLR.reg, (uint8)HS_IRQCLR_HS1_OC_ISC_Pos, HS_IRQCLR_HS1_OC_ISC_Msk, 1u);
}

INLINE void HS_HS1_OT_SC_Clr()
{
  Field_Wrt32(&HS->IRQCLR.reg, (uint8)HS_IRQCLR_HS1_OT_SC_Pos, HS_IRQCLR_HS1_OT_SC_Msk, 1u);
}

INLINE void HS_HS1_OL_SC_Clr()
{
  Field_Wrt32(&HS->IRQCLR.reg, (uint8)HS_IRQCLR_HS1_OL_SC_Pos, HS_IRQCLR_HS1_OL_SC_Msk, 1u);
}

INLINE void HS_HS1_OT_Int_En()
{
  Field_Mod32(&HS->IRQEN.reg, (uint8)HS_IRQEN_HS1_OT_IEN_Pos, HS_IRQEN_HS1_OT_IEN_Msk, 1u);
}

INLINE void HS_HS1_OT_Int_Dis()
{
  Field_Mod32(&HS->IRQEN.reg, (uint8)HS_IRQEN_HS1_OT_IEN_Pos, HS_IRQEN_HS1_OT_IEN_Msk, 0u);
}

INLINE void HS_HS1_OL_Int_En()
{
  Field_Mod32(&HS->IRQEN.reg, (uint8)HS_IRQEN_HS1_OL_IEN_Pos, HS_IRQEN_HS1_OL_IEN_Msk, 1u);
}

INLINE void HS_HS1_OL_Int_Dis()
{
  Field_Mod32(&HS->IRQEN.reg, (uint8)HS_IRQEN_HS1_OL_IEN_Pos, HS_IRQEN_HS1_OL_IEN_Msk, 0u);
}

INLINE void HS_HS1_OC_Int_En()
{
  Field_Mod32(&HS->IRQEN.reg, (uint8)HS_IRQEN_HS1_OC_IEN_Pos, HS_IRQEN_HS1_OC_IEN_Msk, 1u);
}

INLINE void HS_HS1_OC_Int_Dis()
{
  Field_Mod32(&HS->IRQEN.reg, (uint8)HS_IRQEN_HS1_OC_IEN_Pos, HS_IRQEN_HS1_OC_IEN_Msk, 0u);
}

#endif
