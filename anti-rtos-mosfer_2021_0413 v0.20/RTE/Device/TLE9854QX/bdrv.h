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
 * \file     bdrv.h
 *
 * \brief    Bridge Driver low level access library
 *
 * \version  V0.2.7
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
** KC           Kay Claussen                                                  **
** JO           Julia Ott                                                     **
** BG           Blandine Guillot                                              **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V0.2.0: 2018-02-13, TS:   Initial version of revision history              **
** V0.2.1: 2018-07-30, KC:   Registers added to BDRV_Init()                   **
** V0.2.2: 2018-10-22, TS:   BRDRV_CLK Register Initialization added          **
** V0.2.3: 2019-01-28, TS:   __STATIC_INLINE changed to INLINE                **
**                           Doxygen update                                   **
**                           Revision history moved from bdrv.c to bdrv.h     **
**                           BDRV_Diag_OpenLoad function updated              **
**                           BDRV_Off_Diagnosis and BDRV_Set_DSM_Threshold    **
**                           functions added                                  **
**                           New Mask macros used                             **
** V0.2.4: 2019-06-13, JO:   Corrected value of define BDRV_IRQ_CLR_BITS from **
**                           0xF0707070 to 0xF0707073 to clear all interrupts **
**                           In BDRV_Init: Set APCLK_SET after modifying      **
**                           SCU->BRDRV_CLK.reg to apply clock changes        **
** V0.2.5: 2019-08-30, AP:   In BDRV_Init: Keep the bootrom value for         **
**                           Charge Pump Output Voltage Trimming              **
** V0.2.6: 2019-09-03, JO:   Removed the functions for H-Bridge if a          **
**                           Half-Bridge device is selected                   **    
** V0.2.7: 2020-03-02, BG:   Updated revision history format                  **
*******************************************************************************/

#ifndef _BDR_H
#define _BDR_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle985x.h"
#include "types.h"
#include "sfr_access.h"
#include "tle_variants.h"

/*******************************************************************************
**                        Global Constant Declarations                        **
*******************************************************************************/
/**\brief BDRV Interrupt Enable Mask */
#define BDRV_IRQ_EN_BITS  0xD0505050u

/**\brief BDRV Interrupt Clear Mask */
#define BDRV_IRQ_CLR_BITS 0xF0707073u

/**\brief BDRV Compensation Trimming Mask */
#define BDRV_COMP_BITS 0x70700u

/**\brief BDRV Drain Source Interrupt Status Clear Mask */
#define BDRV_DS_STS_BITS   0x20202020

/*******************************************************************************
**                           Global Type Definitions                          **
*******************************************************************************/
 /** \enum TBdrv_Ch_LS_Cfg
  *  \brief This enum lists the Bridge Driver Low Side channel configuration.
  */
 typedef enum
 {
   Ch_LS_Off = 0u,  /**< \brief channel disabled                           */
   Ch_LS_En  = 1u,  /**< \brief channel enabled                            */
   Ch_LS_PWM = 3u,  /**< \brief channel enabled with PWM (CCU6 connection) */
   Ch_LS_On  = 5u   /**< \brief channel enabled and static on              */
 } TBdrv_Ch_LS_Cfg;

/** \enum TBdrv_Ch_Cfg
 *  \brief This enum lists the Bridge Driver High Side channel configuration.
 */
typedef enum
{
  Ch_Off = 0u,  /**< \brief channel disabled                                              */
  Ch_En  = 1u,  /**< \brief channel enabled                                               */
  Ch_PWM = 3u,  /**< \brief channel enabled with PWM (CCU6 connection)                    */
  Ch_On  = 5u,  /**< \brief channel enabled and static on                                 */
  Ch_DCS = 9u   /**< \brief channel enabled with Diag.-Current Source (only for HS1/HS2)  */
} TBdrv_Ch_Cfg;

/** \enum TBdrv_Ch
 *  \brief This enum lists the Bridge Driver channel configuration.
 */
typedef enum
{
  LS1 = 0u, /**< \brief Phase1 Low Side MOSFET  */
  LS2 = 1u, /**< \brief Phase2 Low Side MOSFET  */
  HS1 = 2u, /**< \brief Phase1 High Side MOSFET */
  HS2 = 3u  /**< \brief Phase2 High Side MOSFET */
} TBdrv_Ch;

#define BDRV_LS1_DS_ISC   BDRV_IRQCLR_LS1_DS_ISC_Msk    /**< \brief Low Side Driver 1 Drain Source Monitoring Interrupt Mask Status Clear in OFF-State  */
#define BDRV_LS1_DS_SC    BDRV_IRQCLR_LS1_DS_SC_Msk     /**< \brief Low Side Driver 1 Drain Source Monitoring Mask Status Clear in OFF-State            */
#define BDRV_LS1_OC_ISC   BDRV_IRQCLR_LS1_OC_ISC_Msk    /**< \brief External Low Side 1 FET Over-current Mask Status Clear                              */
#define BDRV_HS1_DS_ISC   BDRV_IRQCLR_HS1_DS_ISC_Msk    /**< \brief High Side Driver 1 Drain Source Monitoring Interrupt Mask Status Clear in OFF-State */
#define BDRV_HS1_DS_SC    BDRV_IRQCLR_HS1_DS_SC_Msk     /**< \brief High Side Driver 1 Drain Source Monitoring Mask Status Clear in OFF-State           */
#define BDRV_HS1_OC_ISC   BDRV_IRQCLR_HS1_OC_ISC_Msk    /**< \brief External High Side 1 FET Over-current Mask Status Clear                             */


#ifdef UC_FEATURE_HB2
#define BDRV_LS2_DS_ISC   BDRV_IRQCLR_LS2_DS_ISC_Msk    /**< \brief Low Side Driver 2 Drain Source Monitoring Interrupt Mask Status Clear in OFF-State  */
#define BDRV_LS2_DS_SC    BDRV_IRQCLR_LS2_DS_SC_Msk     /**< \brief Low Side Driver 2 Drain Source Monitoring Mask Status Clear in OFF-State            */
#define BDRV_LS2_OC_ISC   BDRV_IRQCLR_LS2_OC_ISC_Msk    /**< \brief External Low Side 2 FET Over-current Mask Status Clear                              */
#define BDRV_HS2_DS_ISC   BDRV_IRQCLR_HS2_DS_ISC_Msk    /**< \brief High Side Driver 2 Drain Source Monitoring Interrupt Mask Status Clear in OFF-State */
#define BDRV_HS2_DS_SC    BDRV_IRQCLR_HS2_DS_SC_Msk     /**< \brief High Side Driver 2 Drain Source Monitoring Mask Status Clear in OFF-State           */
#define BDRV_HS2_OC_ISC   BDRV_IRQCLR_HS2_OC_ISC_Msk    /**< \brief External High Side 2 FET Over-current Mask Status Clear                             */
#endif

#define BDRV_SEQ_ERR_ISC  BDRV_IRQCLR_SEQ_ERR_ISC_Msk    /**< \brief Driver Sequence Error Mask Status Clear                                             */

/** \enum TBDRV_Off_Diag_Sts
 *  \brief This enum lists the Bridge Driver Off Diagnosis Status configuration.
 */
typedef enum
{
  Ch_Ok = 0u,
  Ch_Short_to_Gnd = 1u,
  Ch_Short_to_VBat = 2u
} TBDRV_Off_Diag_Sts;

/** \struct TBDRV_Off_Diag
 *  \brief This struct lists the Bridge Driver Off Diagnosis Status Phases configuration.
 */
typedef struct
{
  bool GlobFailSts;
  TBDRV_Off_Diag_Sts Phase1;
  TBDRV_Off_Diag_Sts Phase2;
} TBDRV_Off_Diag;

/** \enum TBdrv_Ch_Int
 *  \brief This enum lists the Bridge Driver channel Interrupt configuration.
 */
typedef enum
{
  Int_Off   = 0U, /**< \brief all interrupts disable                         */
  Int_DS    = 1U, /**< \brief Drain-Source interrupt enable                  */
  Int_OC    = 2U, /**< \brief Over-Current interrupt enable                  */
  Int_DS_OC = 3U  /**< \brief Drain-Source and Over-Current interrupt enable */
} TBdrv_Ch_Int;

/** \enum TBdrv_DSM_Threshold
 *  \brief This enum lists the Drain-Source Voltage Threshold.
 */
typedef enum
{
  Threshold_0_125_V = 0U, /**< \brief Threshold 0 for VDS at 0.125 V */
  Threshold_0_25_V = 1U,  /**< \brief Threshold 1 for VDS at 0.25 V */
  Threshold_0_50_V = 2U,  /**< \brief Threshold 2 for VDS at 0.50 V */
  Threshold_0_75_V = 3U,  /**< \brief Threshold 3 for VDS at 0.75 V */
  Threshold_1_00_V = 4U,  /**< \brief Threshold 4 for VDS at 1.00 V */
  Threshold_1_25_V = 5U,  /**< \brief Threshold 5 for VDS at 1.25 V */
  Threshold_1_50_V = 6U,  /**< \brief Threshold 6 for VDS at 1.50 V */
  Threshold_1_75_V = 7U   /**< \brief Threshold 7 for VDS at 1.75 V */
} TBdrv_DSM_Threshold;

/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/
/** \brief Initializes the BridgeDriver based on the Config Wizard configuration
 *
 * \ingroup bdrv_api
 */
void BDRV_Init(void);


#ifdef UC_FEATURE_HB2
/** \brief Sets the bridge in the desired state. For each of the four drivers the state can be defined.
 * \brief In order to operate a 2phase motor all the four driver stages have to be configured to Ch_PWM/.
 *
 * \param LS1_Cfg Low Side Driver 1 Configuration, see \link TBdrv_Ch_LS_Cfg \endlink
 * \param HS1_Cfg High Side Driver 1 Configuration, see \link TBdrv_Ch_Cfg \endlink
 * \param LS2_Cfg Low Side Driver 2 Configuration, see \link TBdrv_Ch_LS_Cfg \endlink
 * \param HS2_Cfg High Side Driver 2 Configuration, see \link TBdrv_Ch_Cfg \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example configures BDRV Bridge channels HS1,HS2,LS1 and LS2 to be enabled with PWM.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     BDRV_Set_Bridge(Ch_LS_PWM, Ch_PWM, Ch_LS_PWM, Ch_PWM);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
void BDRV_Set_Bridge(TBdrv_Ch_LS_Cfg LS1_Cfg,
                     TBdrv_Ch_Cfg HS1_Cfg,
                     TBdrv_Ch_LS_Cfg LS2_Cfg,
                     TBdrv_Ch_Cfg HS2_Cfg);
#else
/** \brief Sets the bridge in the desired state. For each of the four drivers the state can be defined.
 *
 * \param LS1_Cfg Low Side Driver 1 Configuration, see \link TBdrv_Ch_LS_Cfg \endlink
 * \param HS1_Cfg High Side Driver 1 Configuration, see \link TBdrv_Ch_Cfg \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example configures BDRV Bridge channels HS1 and HS2 to be enabled with PWM.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     BDRV_Set_Bridge(Ch_LS_PWM, Ch_PWM);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
void BDRV_Set_Bridge(TBdrv_Ch_LS_Cfg LS1_Cfg,
                     TBdrv_Ch_Cfg HS1_Cfg);  
#endif
/** \brief sets an individual driver of the BridgeDriver in the desired state
 *
 * \param BDRV_Ch selects the channel for which the configuration should be set, see \link TBdrv_Ch \endlink
 * \param Ch_Cfg selects the mode of operation for that channel, see \link TBdrv_Ch_Cfg \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example configures BDRV Bridge channel HS1 to be enabled with PWM.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     BDRV_Set_Channel(HS1, Ch_PWM);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
void BDRV_Set_Channel(TBdrv_Ch BDRV_Ch, TBdrv_Ch_Cfg Ch_Cfg);

/** \brief Clears individual status flags and interrupt status flags of the BridgeDriver
 *
 * \param Sts_Bit status bit to be cleared
 *
 * \brief <b>Example</b><br>
 * \brief This example clears BDRV HS2/LS2 Over-Current interrupt flag.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     BDRV_Clr_Sts(BDRV_LS2_OC_ISC | BDRV_HS2_OC_ISC);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
void BDRV_Clr_Sts(uint32 Sts_Bit);

/** \brief Sets Interrupt Enable for the individual MOSFETs
 *
 * \param BDRV_Ch Channel selection, see \link TBdrv_Ch \endlink
 * \param Ch_Int selection for the desired interrupt to be enabled, see \link TBdrv_Ch_Int \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example enables BDRV HS1 Over-Current Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     BDRV_Set_Int_Channel(HS1, Int_OC);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
void BDRV_Set_Int_Channel(TBdrv_Ch BDRV_Ch, TBdrv_Ch_Int Ch_Int);

/** \brief Sets the Voltage Threshold for Drain-Source Monitoring of external FETs
 *
 * \param BDRV_Threshold selection for the desired voltage threshold, see \link TBdrv_DSM_Threshold \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example sets the Voltage Threshold for Drain-Source Monitoring to 1,5V
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     BDRV_Set_DSM_Threshold(Threshold_1_50_V);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
void BDRV_Set_DSM_Threshold(TBdrv_DSM_Threshold BDRV_Threshold);

/** \brief Sets Gain for Low/High Side Charge Current Compensation
 *
 * \param gain_hs High Side gain selection
 * \param gain_ls Low Side gain selection
 *
 * \brief <b>Example</b><br>
 * \brief This example sets gain_1 for High and Low Sides Charge Current Compensation.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_Set_Channel_Comp(1u, 1u);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
void BDRV_Set_Channel_Comp(uint8 gain_hs, uint8 gain_ls);

#ifdef UC_FEATURE_HB2
/** \brief Detects whether a motor is connected
 *
 * \retval true no motor detected
 * \retval false motor connected
 *
 * \brief <b>Example</b><br>
 * \brief This example disables all BDRV channels when Open Load is detected.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     if (BDRV_Diag_OpenLoad() == true)
 *     {
 *         BDRV_Set_Channel(LS1, Ch_Off);
 *         BDRV_Set_Channel(LS2, Ch_Off);
 *         BDRV_Set_Channel(HS1, Ch_Off);
 *         BDRV_Set_Channel(HS2, Ch_Off);
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
bool BDRV_Diag_OpenLoad(void);
#endif

#ifdef UC_FEATURE_HB2
/** \brief Off-diagnosis
 * \brief Detects a short of the phases either to Gnd or to Vbat
 *
 * \retval true any short detected
 * \retval false no short
 *
 * \brief <b>Example</b><br>
 * \brief This example disables all BDRV channels when a short is detected.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     if (BDRV_Off_Diagnosis() == true)
 *     {
 *         BDRV_Set_Channel(LS1, Ch_Off);
 *         BDRV_Set_Channel(LS2, Ch_Off);
 *         BDRV_Set_Channel(HS1, Ch_Off);
 *         BDRV_Set_Channel(HS2, Ch_Off);
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
TBDRV_Off_Diag BDRV_Off_Diagnosis(void);
#endif 

/*******************************************************************************
**                        Inline Function Declarations                        **
*******************************************************************************/
/** \brief Clears Driver Sequence Error interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Driver Sequence Error interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_SEQ_ERR_Int_En();
 *   if (BDRV->IRQS.bit.SEQ_ERR_IS == 1u)
 *   {
 *     BDRV_SEQ_ERR_CALLBACK();
 *     BDRV_SEQ_ERR_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_SEQ_ERR_Int_Clr(void);

#ifdef UC_FEATURE_HB2
/** \brief Clears External High Side 2 FET Over-current interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External High Side 2 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS2_OC_Int_En();
 *   if (BDRV->IRQS.bit.HS2_OC_IS == 1u)
 *   {
 *     BDRV_HS2_OC_CALLBACK();
 *     BDRV_HS2_OC_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS2_OC_Int_Clr(void);

/** \brief Clears High Side Driver 2 Drain Source Monitoring status flag in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example checks High Side Driver 2 Drain Source Monitoring status in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   if (BDRV->IRQS.bit.HS2_DS_STS == 1u)
 *   {
 *     BDRV_HS2_DS_SC_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS2_DS_SC_Clr(void);

/** \brief Clears High Side Driver 2 Drain Source Monitoring status flag in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the High Side Driver 2 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS2_DS_Int_En();
 *   if (BDRV->IRQS.bit.HS2_DS_IS == 1u)
 *   {
 *     BDRV_HS2_DS_CALLBACK();
 *     BDRV_HS2_DS_Int_Clr();
 *   }
 *   BDRV_HS2_DS_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS2_DS_Int_Clr(void);
#endif

/** \brief Clears External High Side 1 FET Over-current interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External High Side 1 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS1_OC_Int_En();
 *   if (BDRV->IRQS.bit.HS1_OC_IS == 1u)
 *   {
 *     BDRV_HS1_OC_CALLBACK();
 *     BDRV_HS1_OC_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS1_OC_Int_Clr(void);

/** \brief Clears High Side Driver 1 Drain Source Monitoring status flag in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example checks the High Side Driver 1 Drain Source Monitoring status in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   if (BDRV->IRQS.bit.HS1_DS_STS == 1u)
 *   {
 *     BDRV_HS1_DS_SC_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS1_DS_SC_Clr(void);

/** \brief Clears High Side Driver 1 Drain Source Monitoring interrupt flag in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the High Side Driver 1 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS1_DS_Int_En();
 *   if (BDRV->IRQS.bit.HS1_DS_IS == 1u)
 *   {
 *     BDRV_HS1_DS_CALLBACK();
 *     BDRV_HS1_DS_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS1_DS_Int_Clr(void);

#ifdef UC_FEATURE_HB2
/** \brief Clears External Low Side 2 FET Over-current interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Low Side 2 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS2_OC_Int_En();
 *   if (BDRV->IRQS.bit.LS2_OC_IS == 1u)
 *   {
 *     BDRV_LS2_OC_CALLBACK();
 *     BDRV_LS2_OC_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS2_OC_Int_Clr(void);

/** \brief Clears Low Side Driver 2 Drain Source Monitoring status flag in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example checks the Low Side Driver 2 Drain Source Monitoring status in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   if (BDRV->IRQS.bit.LS2_DS_STS == 1u)
 *   {
 *     BDRV_LS2_DS_SC_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS2_DS_SC_Clr(void);

/** \brief Clears Low Side Driver 2 Drain Source Monitoring interrupt flag in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Low Side Driver 2 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS2_DS_Int_En();
 *   if (BDRV->IRQS.bit.LS2_DS_IS == 1u)
 *   {
 *     BDRV_LS2_DS_CALLBACK();
 *     BDRV_LS2_DS_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS2_DS_Int_Clr(void);
#endif

/** \brief Clears External Low Side 1 FET Over-current interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Low Side 1 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS1_OC_Int_En();
 *   if (BDRV->IRQS.bit.LS1_OC_IS == 1u)
 *   {
 *     BDRV_LS1_OC_CALLBACK();
 *     BDRV_LS1_OC_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS1_OC_Int_Clr(void);

/** \brief Clears Low Side Driver 1 Drain Source Monitoring status flag in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example checks the Low Side Driver 1 Drain Source Monitoring status in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   if (BDRV->IRQS.bit.LS1_DS_STS == 1u)
 *   {
 *     BDRV_LS1_DS_SC_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS1_DS_SC_Clr(void);

/** \brief Clears Low Side Driver 1 Drain Source Monitoring interrupt flag in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Low Side Driver 1 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS1_DS_Int_En();
 *   if (BDRV->IRQS.bit.LS1_DS_IS == 1u)
 *   {
 *     BDRV_LS1_DS_CALLBACK();
 *     BDRV_LS1_DS_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS1_DS_Int_Clr(void);

/** \brief Clears Charge Pump Low interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Charge Pump Low interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_VCP_LO_Int_En();
 *   if (BDRV->IRQS.bit.VCP_LOTH2_IS == 1u)
 *   {
 *     BDRV_VCP_LO_CALLBACK();
 *     BDRV_VCP_LO_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_VCP_LO_Int_Clr(void);

/** \brief Enables Driver Sequence Error interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Driver Sequence Error interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_SEQ_ERR_Int_En();
 *   if (BDRV->IRQS.bit.SEQ_ERR_IS == 1u)
 *   {
 *     BDRV_SEQ_ERR_CALLBACK();
 *     BDRV_SEQ_ERR_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_SEQ_ERR_Int_En(void);

/** \brief Disables Driver Sequence Error interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Driver Sequence Error interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_SEQ_ERR_Int_En();
 *   if (BDRV->IRQS.bit.SEQ_ERR_IS == 1u)
 *   {
 *     BDRV_SEQ_ERR_CALLBACK();
 *     BDRV_SEQ_ERR_Int_Clr();
 *   }
 *   BDRV_SEQ_ERR_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_SEQ_ERR_Int_Dis(void);

/** \brief Enables External High Side 1 FET Over-current interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External High Side 1 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS1_OC_Int_En();
 *   if (BDRV->IRQS.bit.HS1_OC_IS == 1u)
 *   {
 *     BDRV_HS1_OC_CALLBACK();
 *     BDRV_HS1_OC_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS1_OC_Int_En(void);

/** \brief Disables External High Side 1 FET Over-current interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External High Side 1 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS1_OC_Int_En();
 *   if (BDRV->IRQS.bit.HS1_OC_IS == 1u)
 *   {
 *     BDRV_HS1_OC_CALLBACK();
 *     BDRV_HS1_OC_Int_Clr();
 *   }
 *   BDRV_HS1_OC_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS1_OC_Int_Dis(void);

/** \brief Enables External Low Side 1 FET Over-current interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Low Side 1 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS1_OC_Int_En();
 *   if (BDRV->IRQS.bit.LS1_OC_IS == 1u)
 *   {
 *     BDRV_LS1_OC_CALLBACK();
 *     BDRV_LS1_OC_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS1_OC_Int_En(void);

/** \brief Disables External Low Side 1 FET Over-current interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Low Side 1 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS1_OC_Int_En();
 *   if (BDRV->IRQS.bit.LS1_OC_IS == 1u)
 *   {
 *     BDRV_LS1_OC_CALLBACK();
 *     BDRV_LS1_OC_Int_Clr();
 *   }
 *   BDRV_LS1_OC_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS1_OC_Int_Dis(void);

#ifdef UC_FEATURE_HB2
/** \brief Enables External High Side 2 FET Over-current interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External High Side 2 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS2_OC_Int_En();
 *   if (BDRV->IRQS.bit.HS2_OC_IS == 1u)
 *   {
 *     BDRV_HS2_OC_CALLBACK();
 *     BDRV_HS2_OC_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS2_OC_Int_En(void);

/** \brief Disables External High Side 2 FET Over-current interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External High Side 2 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS2_OC_Int_En();
 *   if (BDRV->IRQS.bit.HS2_OC_IS == 1u)
 *   {
 *     BDRV_HS2_OC_CALLBACK();
 *     BDRV_HS2_OC_Int_Clr();
 *   }
 *   BDRV_HS2_OC_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS2_OC_Int_Dis(void);

/** \brief Enables External Low Side 2 FET Over-current interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Low Side 2 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS2_OC_Int_En();
 *   if (BDRV->IRQS.bit.LS2_OC_IS == 1u)
 *   {
 *     BDRV_LS2_OC_CALLBACK();
 *     BDRV_LS2_OC_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS2_OC_Int_En(void);

/** \brief Disables External Low Side 2 FET Over-current interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the External Low Side 2 FET Over-current interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS2_OC_Int_En();
 *   if (BDRV->IRQS.bit.LS2_OC_IS == 1u)
 *   {
 *     BDRV_LS2_OC_CALLBACK();
 *     BDRV_LS2_OC_Int_Clr();
 *   }
 *   BDRV_LS2_OC_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS2_OC_Int_Dis(void);
#endif

/** \brief Enables High Side Driver 1 Drain Source Monitoring interrupt in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the High Side Driver 1 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS1_DS_Int_En();
 *   if (BDRV->IRQS.bit.HS1_DS_IS == 1u)
 *   {
 *     BDRV_HS1_DS_CALLBACK();
 *     BDRV_HS1_DS_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS1_DS_Int_En(void);

/** \brief Disables High Side Driver 1 Drain Source Monitoring interrupt in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the High Side Driver 1 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS1_DS_Int_En();
 *   if (BDRV->IRQS.bit.HS1_DS_IS == 1u)
 *   {
 *     BDRV_HS1_DS_CALLBACK();
 *     BDRV_HS1_DS_Int_Clr();
 *   }
 *   BDRV_HS1_DS_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS1_DS_Int_Dis(void);

/** \brief Enables Low Side Driver 1 Drain Source Monitoring interrupt in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Low Side Driver 1 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS1_DS_Int_En();
 *   if (BDRV->IRQS.bit.LS1_DS_IS == 1u)
 *   {
 *     BDRV_LS1_DS_CALLBACK();
 *     BDRV_LS1_DS_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS1_DS_Int_En(void);

/** \brief Disables Low Side Driver 1 Drain Source Monitoring interrupt in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Low Side Driver 1 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS1_DS_Int_En();
 *   if (BDRV->IRQS.bit.LS1_DS_IS == 1u)
 *   {
 *     BDRV_LS1_DS_CALLBACK();
 *     BDRV_LS1_DS_Int_Clr();
 *   }
 *   BDRV_LS1_DS_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS1_DS_Int_Dis(void);

#ifdef UC_FEATURE_HB2
/** \brief Enables High Side Driver 2 Drain Source Monitoring interrupt in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the High Side Driver 2 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS2_DS_Int_En();
 *   if (BDRV->IRQS.bit.HS2_DS_IS == 1u)
 *   {
 *     BDRV_HS2_DS_CALLBACK();
 *     BDRV_HS2_DS_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS2_DS_Int_En(void);

/** \brief Disables High Side Driver 2 Drain Source Monitoring interrupt in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the High Side Driver 2 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_HS2_DS_Int_En();
 *   if (BDRV->IRQS.bit.HS2_DS_IS == 1u)
 *   {
 *     BDRV_HS2_DS_CALLBACK();
 *     BDRV_HS2_DS_Int_Clr();
 *   }
 *   BDRV_HS2_DS_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_HS2_DS_Int_Dis(void);

/** \brief Enables Low Side Driver 2 Drain Source Monitoring interrupt in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Low Side Driver 2 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS2_DS_Int_En();
 *   if (BDRV->IRQS.bit.LS2_DS_IS == 1u)
 *   {
 *     BDRV_LS2_DS_CALLBACK();
 *     BDRV_LS2_DS_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS2_DS_Int_En(void);

/** \brief Disables Low Side Driver 2 Drain Source Monitoring interrupt in OFF-State.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Low Side Driver 2 Drain Source Monitoring interrupt in OFF-State.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_LS2_DS_Int_En();
 *   if (BDRV->IRQS.bit.LS2_DS_IS == 1u)
 *   {
 *     BDRV_LS2_DS_CALLBACK();
 *     BDRV_LS2_DS_Int_Clr();
 *   }
 *   BDRV_LS2_DS_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_LS2_DS_Int_Dis(void);
#endif

/** \brief Enables Charge Pump Low interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Charge Pump Low interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_VCP_LO_Int_En();
 *   if (BDRV->IRQS.bit.VCP_LOTH2_IS == 1u)
 *   {
 *     BDRV_VCP_LO_CALLBACK();
 *     BDRV_VCP_LO_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_VCP_LO_Int_En(void);

/** \brief Disables Charge Pump Low interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Charge Pump Low interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   BDRV_VCP_LO_Int_En();
 *   if (BDRV->IRQS.bit.VCP_LOTH2_IS == 1u)
 *   {
 *     BDRV_VCP_LO_CALLBACK();
 *     BDRV_VCP_LO_Int_Clr();
 *   }
 *   BDRV_VCP_LO_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bdrv_api
 */
INLINE void BDRV_VCP_LO_Int_Dis(void);

/*******************************************************************************
**                         Inline Function Definitions                        **
*******************************************************************************/
INLINE void BDRV_SEQ_ERR_Int_Clr()
{
  Field_Wrt32(&BDRV->IRQCLR.reg, (uint8)BDRV_IRQCLR_SEQ_ERR_ISC_Pos, BDRV_IRQCLR_SEQ_ERR_ISC_Msk, 1u);
}

#ifdef UC_FEATURE_HB2
INLINE void BDRV_HS2_OC_Int_Clr()
{
  Field_Wrt32(&BDRV->IRQCLR.reg, (uint8)BDRV_IRQCLR_HS2_OC_ISC_Pos, BDRV_IRQCLR_HS2_OC_ISC_Msk, 1u);
}

INLINE void BDRV_HS2_DS_SC_Clr()
{
  Field_Wrt32(&BDRV->IRQCLR.reg, (uint8)BDRV_IRQCLR_HS2_DS_SC_Pos, BDRV_IRQCLR_HS2_DS_SC_Msk, 1u);
}

INLINE void BDRV_HS2_DS_Int_Clr()
{
  Field_Wrt32(&BDRV->IRQCLR.reg, (uint8)BDRV_IRQCLR_HS2_DS_ISC_Pos, BDRV_IRQCLR_HS2_DS_ISC_Msk, 1u);
}
#endif

INLINE void BDRV_HS1_OC_Int_Clr()
{
  Field_Wrt32(&BDRV->IRQCLR.reg, (uint8)BDRV_IRQCLR_HS1_OC_ISC_Pos, BDRV_IRQCLR_HS1_OC_ISC_Msk, 1u);
}

INLINE void BDRV_HS1_DS_SC_Clr()
{
  Field_Wrt32(&BDRV->IRQCLR.reg, (uint8)BDRV_IRQCLR_HS1_DS_SC_Pos, BDRV_IRQCLR_HS1_DS_SC_Msk, 1u);
}

INLINE void BDRV_HS1_DS_Int_Clr()
{
  Field_Wrt32(&BDRV->IRQCLR.reg, (uint8)BDRV_IRQCLR_HS1_DS_ISC_Pos, BDRV_IRQCLR_HS1_DS_ISC_Msk, 1u);
}

#ifdef UC_FEATURE_HB2
INLINE void BDRV_LS2_OC_Int_Clr()
{
  Field_Wrt32(&BDRV->IRQCLR.reg, (uint8)BDRV_IRQCLR_LS2_OC_ISC_Pos, BDRV_IRQCLR_LS2_OC_ISC_Msk, 1u);
}

INLINE void BDRV_LS2_DS_SC_Clr()
{
  Field_Wrt32(&BDRV->IRQCLR.reg, (uint8)BDRV_IRQCLR_LS2_DS_SC_Pos, BDRV_IRQCLR_LS2_DS_SC_Msk, 1u);
}

INLINE void BDRV_LS2_DS_Int_Clr()
{
  Field_Wrt32(&BDRV->IRQCLR.reg, (uint8)BDRV_IRQCLR_LS2_DS_ISC_Pos, BDRV_IRQCLR_LS2_DS_ISC_Msk, 1u);
}
#endif

INLINE void BDRV_LS1_OC_Int_Clr()
{
  Field_Wrt32(&BDRV->IRQCLR.reg, (uint8)BDRV_IRQCLR_LS1_OC_ISC_Pos, BDRV_IRQCLR_LS1_OC_ISC_Msk, 1u);
}

INLINE void BDRV_LS1_DS_SC_Clr()
{
  Field_Wrt32(&BDRV->IRQCLR.reg, (uint8)BDRV_IRQCLR_LS1_DS_SC_Pos, BDRV_IRQCLR_LS1_DS_SC_Msk, 1u);
}

INLINE void BDRV_LS1_DS_Int_Clr()
{
  Field_Wrt32(&BDRV->IRQCLR.reg, (uint8)BDRV_IRQCLR_LS1_DS_ISC_Pos, BDRV_IRQCLR_LS1_DS_ISC_Msk, 1u);
}

INLINE void BDRV_VCP_LO_Int_Clr()
{
  Field_Wrt32(&BDRV->CP_IRQCLR.reg, (uint8)BDRV_CP_IRQCLR_VCP_LOTH2_ISC_Pos, BDRV_CP_IRQCLR_VCP_LOTH2_ISC_Msk, 1u);
}

INLINE void BDRV_SEQ_ERR_Int_En()
{
  Field_Mod32(&BDRV->IRQEN.reg, (uint8)BDRV_IRQEN_SEQ_ERR_IEN_Pos, BDRV_IRQEN_SEQ_ERR_IEN_Msk, 1u);
}

INLINE void BDRV_SEQ_ERR_Int_Dis()
{
  Field_Mod32(&BDRV->IRQEN.reg, (uint8)BDRV_IRQEN_SEQ_ERR_IEN_Pos, BDRV_IRQEN_SEQ_ERR_IEN_Msk, 0u);
}

INLINE void BDRV_HS1_OC_Int_En()
{
  Field_Mod32(&BDRV->IRQEN.reg, (uint8)BDRV_IRQEN_HS1_OC_IEN_Pos, BDRV_IRQEN_HS1_OC_IEN_Msk, 1u);
}

INLINE void BDRV_HS1_OC_Int_Dis()
{
  Field_Mod32(&BDRV->IRQEN.reg, (uint8)BDRV_IRQEN_HS1_OC_IEN_Pos, BDRV_IRQEN_HS1_OC_IEN_Msk, 0u);
}

INLINE void BDRV_LS1_OC_Int_En()
{
  Field_Mod32(&BDRV->IRQEN.reg, (uint8)BDRV_IRQEN_LS1_OC_IEN_Pos, BDRV_IRQEN_LS1_OC_IEN_Msk, 1u);
}

INLINE void BDRV_LS1_OC_Int_Dis()
{
  Field_Mod32(&BDRV->IRQEN.reg, (uint8)BDRV_IRQEN_LS1_OC_IEN_Pos, BDRV_IRQEN_LS1_OC_IEN_Msk, 0u);
}

#ifdef UC_FEATURE_HB2
INLINE void BDRV_HS2_OC_Int_En()
{
  Field_Mod32(&BDRV->IRQEN.reg, (uint8)BDRV_IRQEN_HS2_OC_IEN_Pos, BDRV_IRQEN_HS2_OC_IEN_Msk, 1u);
}

INLINE void BDRV_HS2_OC_Int_Dis()
{
  Field_Mod32(&BDRV->IRQEN.reg, (uint8)BDRV_IRQEN_HS2_OC_IEN_Pos, BDRV_IRQEN_HS2_OC_IEN_Msk, 0u);
}

INLINE void BDRV_LS2_OC_Int_En()
{
  Field_Mod32(&BDRV->IRQEN.reg, (uint8)BDRV_IRQEN_LS2_OC_IEN_Pos, BDRV_IRQEN_LS2_OC_IEN_Msk, 1u);
}

INLINE void BDRV_LS2_OC_Int_Dis()
{
  Field_Mod32(&BDRV->IRQEN.reg, (uint8)BDRV_IRQEN_LS2_OC_IEN_Pos, BDRV_IRQEN_LS2_OC_IEN_Msk, 0u);
}
#endif

INLINE void BDRV_HS1_DS_Int_En()
{
  Field_Mod32(&BDRV->IRQEN.reg, (uint8)BDRV_IRQEN_HS1_DS_IEN_Pos, BDRV_IRQEN_HS1_DS_IEN_Msk, 1u);
}

INLINE void BDRV_HS1_DS_Int_Dis()
{
  Field_Mod32(&BDRV->IRQEN.reg, (uint8)BDRV_IRQEN_HS1_DS_IEN_Pos, BDRV_IRQEN_HS1_DS_IEN_Msk, 0u);
}

INLINE void BDRV_LS1_DS_Int_En()
{
  Field_Mod32(&BDRV->IRQEN.reg, (uint8)BDRV_IRQEN_LS1_DS_IEN_Pos, BDRV_IRQEN_LS1_DS_IEN_Msk, 1u);
}

INLINE void BDRV_LS1_DS_Int_Dis()
{
  Field_Mod32(&BDRV->IRQEN.reg, (uint8)BDRV_IRQEN_LS1_DS_IEN_Pos, BDRV_IRQEN_LS1_DS_IEN_Msk, 0u);
}

#ifdef UC_FEATURE_HB2
INLINE void BDRV_HS2_DS_Int_En()
{
  Field_Mod32(&BDRV->IRQEN.reg, (uint8)BDRV_IRQEN_HS2_DS_IEN_Pos, BDRV_IRQEN_HS2_DS_IEN_Msk, 1u);
}

INLINE void BDRV_HS2_DS_Int_Dis()
{
  Field_Mod32(&BDRV->IRQEN.reg, (uint8)BDRV_IRQEN_HS2_DS_IEN_Pos, BDRV_IRQEN_HS2_DS_IEN_Msk, 0u);
}

INLINE void BDRV_LS2_DS_Int_En()
{
  Field_Mod32(&BDRV->IRQEN.reg, (uint8)BDRV_IRQEN_LS2_DS_IEN_Pos, BDRV_IRQEN_LS2_DS_IEN_Msk, 1u);
}

INLINE void BDRV_LS2_DS_Int_Dis()
{
  Field_Mod32(&BDRV->IRQEN.reg, (uint8)BDRV_IRQEN_LS2_DS_IEN_Pos, BDRV_IRQEN_LS2_DS_IEN_Msk, 0u);
}
#endif

INLINE void BDRV_VCP_LO_Int_En()
{
  Field_Mod32(&BDRV->CP_IRQEN.reg, (uint8)BDRV_CP_IRQEN_VCP_LOTH2_IEN_Pos, BDRV_CP_IRQEN_VCP_LOTH2_IEN_Msk, 1u);
}

INLINE void BDRV_VCP_LO_Int_Dis()
{
  Field_Mod32(&BDRV->CP_IRQEN.reg, (uint8)BDRV_CP_IRQEN_VCP_LOTH2_IEN_Pos, BDRV_CP_IRQEN_VCP_LOTH2_IEN_Msk, 0u);
}

#endif
