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
 * \file     adc1.h
 *
 * \brief    ADC1 low level access library
 *
 * \version  V0.2.6
 * \date     02. Mar 2020
 *
 * \note This file violates [MISRA 2012 Rule 11.1, required], [MISRA 2012 Rule 11.4, advisory], [MISRA 2012 Rule 11.6, required], [MISRA 2012 Rule 2.5, advisory], [MISRA 2012 Rule 8.7, advisory]
 */

/*******************************************************************************
**                             Author(s) Identity                             **
********************************************************************************
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** DM           Daniel Mysliwitz                                              **
** KC           Kay Claussen                                                  **
** TS           T&S                                                           **
** JO           Julia Ott                                                     **
** BG           Blandine Guillot                                              **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V0.2.0: 2018-02-13, TS:   Initial version of version history               **
** V0.2.1: 2018-09-19, KC:   Register to be initialized added in ADC1_Init()  **
** V0.2.2: 2018-10-08, DM:   ADC1_CLK initialization added                    **
** V0.2.3: 2018-10-17, TS:   Calibration Unit Control Registers DCHTH1_4_LOWER**
**                           and DCHTH1_4_UPPER initialization added          **
** V0.2.4: 2019-01-28, TS:    __STATIC_INLINE changed to INLINE               **
**                           Doxygen update                                   **
**                           Revision history moved from adc1.c to adc1.h     **
**                           Functions ADC1_GetChResult, ADC1_GetChResult_mV, **
**                           ADC1_GetEIMResult, ADC1_GetEIMResult_mV,         **
**                           ADC1_GetSwModeResult, ADC1_GetSwModeResult_mV    **
**                           updated                                          **
** V0.2.5: 2018-02-13, JO:   Removed initialization of ADC1_CAL_CHx_y in      **
**                           ADC1_Init as these registers are initialized by  **
**                           the BootROM                                      **
** V0.2.6: 2020-03-02, BG:   Updated revision history format                  **
*******************************************************************************/

#ifndef ADC1_H
#define ADC1_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle985x.h"
#include "types.h"
#include "sfr_access.h"

/*******************************************************************************
**                        Global Constant Declarations                        **
*******************************************************************************/
/**\brief ADC1 Mode Selection macro, Software Mode */
#define SW_Mode   1u
/**\brief Mode Selection macro, Sequencer Mode */
#define SEQ_Mode  0u

/**\brief ADC1 Result Register macro, Overwrite Mode*/
#define OVERWRITE 0u
/**\brief ADC1 Result Register macro, Wait For Read Mode*/
#define WFR       1u

/**\brief ADC1 channel selection macro, channel 0 - VBAT_SENSE */
#define ADC1_CH0  (0)
/**\brief ADC1 channel selection macro, channel 1 - VS */
#define ADC1_CH1  (1)
/**\brief ADC1 channel selection macro, channel 2 - MON1 */
#define ADC1_CH2  (2)
/**\brief ADC1 channel selection macro, channel 3 - MON2 */
#define ADC1_CH3  (3)
/**\brief ADC1 channel selection macro, channel 4 - MON3 */
#define ADC1_CH4  (4)
/**\brief ADC1 channel selection macro, channel 5 - MON4 */
#define ADC1_CH5  (5)
/**\brief ADC1 channel selection macro, channel 6 - P2.0 */
#define ADC1_CH6  (6)
/**\brief ADC1 channel selection macro, channel 7 - P2.1 */
#define ADC1_CH7  (7)
/**\brief ADC1 channel selection macro, channel 8 - P2.2 */
#define ADC1_CH8  (8)
/**\brief ADC1 channel selection macro, channel 9 - P2.3 */
#define ADC1_CH9  (9)
/**\brief ADC1 channel selection macro, channel 12 - P2.7 */
#define ADC1_CH12 (12)
/**\brief ADC1 channel selection macro, channel 13 - CSA */
#define ADC1_CH13 (13)

/**\brief ADC1 channel selection macro, channel 0 - VBAT_SENSE */
#define ADC1_VBAT_SENSE ADC1_CH0
/**\brief ADC1 channel selection macro, channel 1 - VS */
#define ADC1_VS    ADC1_CH1
/**\brief ADC1 channel selection macro, channel 2 - MON1 */
#define ADC1_MON1  ADC1_CH2
/**\brief ADC1 channel selection macro, channel 3 - MON2 */
#define ADC1_MON2  ADC1_CH3
/**\brief ADC1 channel selection macro, channel 4 - MON3 */
#define ADC1_MON3  ADC1_CH4
/**\brief ADC1 channel selection macro, channel 5 - MON4 */
#define ADC1_MON4  ADC1_CH5
/**\brief ADC1 channel selection macro, channel 6 - P2.0 */
#define ADC1_P20   ADC1_CH6
/**\brief ADC1 channel selection macro, channel 7 - P2.1 */
#define ADC1_P21   ADC1_CH7
/**\brief ADC1 channel selection macro, channel 8 - P2.2 */
#define ADC1_P22   ADC1_CH8
/**\brief ADC1 channel selection macro, channel 9 - P2.3 */
#define ADC1_P23   ADC1_CH9
/**\brief ADC1 channel selection macro, channel 12 - P2.7 */
#define ADC1_P27   ADC1_CH12
/**\brief ADC1 channel selection macro, channel 13 - CSA */
#define ADC1_OPA   ADC1_CH13

/**\brief ADC1 Sequencer/ESM channel selection macro, channel 0 - VBAT_SENSE */
#define ADC1_MASK_CH0  (1u << 0u)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 1 - VS */
#define ADC1_MASK_CH1  (1u << 1u)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 2 - MON1 */
#define ADC1_MASK_CH2  (1u << 2u)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 3 - MON2 */
#define ADC1_MASK_CH3  (1u << 3u)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 4 - MON3 */
#define ADC1_MASK_CH4  (1u << 4u)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 5 - MON4 */
#define ADC1_MASK_CH5  (1u << 5u)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 6 - P2.0 */
#define ADC1_MASK_CH6  (1u << 6u)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 7 - P2.1 */
#define ADC1_MASK_CH7  (1u << 7u)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 8 - P2.2 */
#define ADC1_MASK_CH8  (1u << 8u)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 9 - P2.3 */
#define ADC1_MASK_CH9  (1u << 9u)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 12 - P2.7 */
#define ADC1_MASK_CH12 (1u << 12u)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 13 - CSA */
#define ADC1_MASK_CH13 (1u << 13u)

/**\brief ADC1 Sequencer/ESM channel selection macro, channel 0 - VBAT_SENSE */
#define ADC1_MASK_VBAT_SENSE (ADC1_MASK_CH0)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 1 - VS */
#define ADC1_MASK_VS         (ADC1_MASK_CH1)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 2 - MON1 */
#define ADC1_MASK_MON1       (ADC1_MASK_CH2)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 3 - MON2 */
#define ADC1_MASK_MON2       (ADC1_MASK_CH3)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 4 - MON3 */
#define ADC1_MASK_MON3       (ADC1_MASK_CH4)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 5 - MON4 */
#define ADC1_MASK_MON4       (ADC1_MASK_CH5)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 6 - P2.0 */
#define ADC1_MASK_P20        (ADC1_MASK_CH6)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 7 - P2.1 */
#define ADC1_MASK_P21        (ADC1_MASK_CH7)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 8 - P2.2 */
#define ADC1_MASK_P22        (ADC1_MASK_CH8)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 9 - P2.3 */
#define ADC1_MASK_P23        (ADC1_MASK_CH9)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 12 - P2.7 */
#define ADC1_MASK_P27        (ADC1_MASK_CH12)
/**\brief ADC1 Sequencer/ESM channel selection macro, channel 13 - CSA */
#define ADC1_MASK_OPA        (ADC1_MASK_CH13)

/**\brief ADC1 Overvoltage Measurement Mode macro, upper and lower voltage limit measurement */
#define ADC1_MMODE_0  0u
/**\brief ADC1 Overvoltage Measurement Mode macro, undervoltage limit measurement */
#define ADC1_MMODE_UV 1u
/**\brief ADC1 Overvoltage Measurement Mode macro, overvoltage limit measurement */
#define ADC1_MMODE_OV 2u

/**\brief ADC1 Lower Hysteresis Trigger Level macro, HYST OFF */
#define ADC1_HYST_OFF (0u)
/**\brief ADC1 Lower Hysteresis Trigger Level macro, HYST 4 */
#define ADC1_HYST_4   (1u)
/**\brief ADC1 Lower Hysteresis Trigger Level macro, HYST 8 */
#define ADC1_HYST_8   (2u)
/**\brief ADC1 Lower Hysteresis Trigger Level macro, HYST 16 */
#define ADC1_HYST_16  (3u)

/**\brief ADC1 Lower Counter Trigger Level macro, 1 Measurement*/
#define ADC1_CNT_1  (0u)
/**\brief ADC1 Lower Counter Trigger Level macro, 2 Measurements */
#define ADC1_CNT_2  (1u)
/**\brief ADC1 Lower Counter Trigger Level macro, 4 Measurements */
#define ADC1_CNT_4  (2u)
/**\brief ADC1 Lower Counter Trigger Level macro, 7 Measurements */
#define ADC1_CNT_7  (3u)

/**\brief ADC1 Soc Clock Jitter Status macro, 0n */
#define ADC1_Soc_Clk_Jitter_0    (0u)
/**\brief ADC1 Soc Clock Jitter Status macro, 3.5n */
#define ADC1_Soc_Clk_Jitter_3_5  (1u)
/**\brief ADC1 Soc Clock Jitter Status macro, 5.5n */
#define ADC1_Soc_Clk_Jitter_5_5  (2u)
/**\brief ADC1 Soc Clock Jitter Status macro, 8n */
#define ADC1_Soc_Clk_Jitter_8    (3u)

/**\brief ADC1 reference voltage 1.21V */
#define ADC1_VREF 1.21

/*******************************************************************************
**                           Global Type Definitions                          **
*******************************************************************************/
/** \enum TADC1_TRIGG_SEL
 *  \brief This enum lists the trigger select options for EIM and ESM
 */
typedef enum
{
  ADC1_Trigg_None      = 0, /**< no trigger source connected */
  ADC1_Trigg_CCU6_Ch3  = 1, /**< CCU6 Channel 3 (COUT63), rising edge */
  ADC1_Trigg_GPT12E_T6 = 2, /**< GPT12E Timer6, T6OUT */
  ADC1_Trigg_GPT12E_T3 = 3, /**< GPT12E Timer6, T3OUT */
  ADC1_Trigg_Timer2    = 4, /**< Timer2 output */
  ADC1_Trigg_Timer21   = 5  /**< Timer21 output */
} TADC1_TRIGG_SEL;

/** \enum TADC1_EIM_REP_CNT
 *  \brief This enum lists the EIM repeat count setting options
 *  \brief The number of measurements to be done until EIM interrupt is requested.
 */
typedef enum
{
  ADC1_1_Meas   = 0, /**< EIM irq every measurement */
  ADC1_2_Meas   = 1, /**< EIM irq every 2nd measurement */
  ADC1_4_Meas   = 2, /**< EIM irq every 4th measurement */
  ADC1_8_Meas   = 3, /**< EIM irq every 8th measurement */
  ADC1_16_Meas  = 4, /**< EIM irq every 16th measurement */
  ADC1_32_Meas  = 5, /**< EIM irq every 32nd measurement */
  ADC1_64_Meas  = 6, /**< EIM irq every 64th measurement */
  ADC1_128_Meas = 7  /**< EIM irq every 128th measurement */
} TADC1_EIM_REP_CNT;

/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/
/** \brief Initializes the ADC1 based on the Config Wizard configuration.
 *
 * \ingroup adc1_api
 */
void ADC1_Init(void);

/** \brief Gets ADC1 Channel Attenuator Factor multiplied by 1024.
 *
 * \param channel ADC1 channel number
 * \return attenuator factor multiplied by 1024
 *
 * \brief <b>Example</b><br>
 * \brief This example returns the ADC1 Channel 12 Attenuator Factor.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint32 fs;
 *
 *     ADC1_Power_On();
 *     fs = ADC1_GetChAttFactor(ADC1_CH12);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc1_api
 */
uint32 ADC1_GetChAttFactor(uint8 channel);

/** \brief Gets the 10-bit value of the ADC1 Result Register of the selected ADC1 channel and returns the validity info
 *  \note This function violates [MISRA Rule 45]
 *
 * \param channel channel number (defined in adc1.h)
 * \param[out] *pVar 10-bit ADC1 Result Value of the selected "channel number"
 * \retval true : the value of *pVar is valid (ValidFlag bit is set)
 * \retval false : the value of *pVar is invalid (ValidFlag bit is reset)
 *
 * \brief <b>Example</b><br>
 * \brief This example returns the ADC1 Channel 5 result in Milli Volt (mV).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     bool value_valid;
 *     uint16 var_mV;
 *     uint16 var;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     if (ADC1_GetChResult(&var, ADC1_CH5) == true)
 *     {
 *         value_valid = ADC1_GetChResult_mV(&var_mV, ADC1_CH5);
 *     }
 *
 *     return(value_valid);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
bool ADC1_GetChResult(uint16 * pVar, uint8 channel);

/** \brief Gets the 10-bit value of the ADC1 Result Register of the selected ADC1 channel in Millivolt (mV) and returns the validity info
 *
 * \param channel channel number (defined in adc1.h)
 * \param[out] pVar_mV 10-bit ADC1 Result Value of the selected channel number converted to Millivolt (mV)
 * \retval true : the value of *pVar_mV is valid
 * \retval false : the value of *pVar_mV is invalid
 *
 * \brief <b>Example</b><br>
 * \brief This example returns the ADC1 Channel 5 result in Milli Volt (mV).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     bool value_valid;
 *     uint16 var_mV;
 *     uint16 var;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     if (ADC1_GetChResult(&var, ADC1_CH5) == true)
 *     {
 *         value_valid = ADC1_GetChResult_mV(&var_mV, ADC1_CH5);
 *     }
 *
 *     return(value_valid);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
bool ADC1_GetChResult_mV(uint16 * pVar_mV, uint8 channel);

/** \brief Gets the 10-bit value of the ADC1 EIM Result Register and returns the validity info
 *
 * \param[out] *pVar = ADC value (10bit right aligned in 16 bit return value)
 * \retval true : the value of *pVar is valid (ValidFlag bit is set)
 * \retval false : the value of *pVar is invalid (ValidFlag bit is reset)
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, programs channel 8 (P2.2) and reads the result value in mV.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     bool value_valid;
 *     uint16 var_mV;
 *     uint16 var;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_SetEIMChannel( ADC1_P22 );
 *     if (ADC1_GetEIMResult(&var) == true)
 *     {
 *         value_valid = ADC1_GetEIMResult_mV(&var_mV);
 *     }
 *
 *     return(value_valid);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
bool ADC1_GetEIMResult(uint16 * pVar);

/** \brief Gets the value of the ADC1 EIM Result Register in Millivolt (mV) and returns the validity info
 *
 * \param[out] *pVar_mV ADC1 EIM Result Register value converted to Millivolt (mV)
 * \retval true : the value of *pVar_mV is valid
 * \retval false : the value of *pVar_mV is invalid
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, programs channel 8 (P2.2) and reads the result value in mV.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     bool value_valid;
 *     uint16 var_mV;
 *     uint16 var;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_SetEIMChannel( ADC1_P22 );
 *     if (ADC1_GetEIMResult(&var) == true)
 *     {
 *         value_valid = ADC1_GetEIMResult_mV(&var_mV);
 *     }
 *
 *     return(value_valid);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
bool ADC1_GetEIMResult_mV(uint16 * pVar_mV);

/*******************************************************************************
**                        Inline Function Declarations                        **
*******************************************************************************/
/** \brief Enables the ADC1 module.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables the ADC1 module.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Power_On(void);

/** \brief Disables the ADC1 module.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables the ADC1 module.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_Off();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Power_Off(void);

/** \brief Starts an ADC1 Offset Calibration, for Software mode only.
 *
 * \brief <b>Example</b><br>
 * \brief This example starts an ADC1 Offset Calibration.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Software_Mode_Sel();
 *     ADC1_SOOC_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_SOOC_Set(void);

/** \brief Starts an ADC1 Conversion, for Software mode only.
 *
 * \brief <b>Example</b><br>
 * \brief This example starts an ADC1 conversion on channel 6 - P2.0.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Software_Mode_Sel();
 *     ADC1_SW_Channel_Sel(ADC1_P20);
 *     ADC1_SOS_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_SOS_Set(void);

/** \brief Selects a channel for the software conversion.
 *
 * \param a channel which should be measured
 *
 * \brief <b>Example</b><br>
 * \brief This example starts an ADC1 conversion on channel 6 - P2.0.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Software_Mode_Sel();
 *     ADC1_SW_Channel_Sel(ADC1_P20);
 *     ADC1_SOS_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_SW_Channel_Sel(uint8 a);

/** \brief Reads the enabled channels for the software conversion.
 *
 * \return Channels Enabled for the software conversion
 *
 * \brief <b>Example</b><br>
 * \brief This example returns the ADC1 enabled Channel.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 var;
 *     bool value_valid;
 *
 *     ADC1_Power_On();
 *     ADC1_Software_Mode_Sel();
 *     value_valid = ADC1_GetChResult(&var, ADC1_SW_Channel_Read());
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint8 ADC1_SW_Channel_Read(void);

/** \brief Enables DPP1 Startup.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables DPP1 Startup.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_STRTUP_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_STRTUP_En(void);

/** \brief Disables DPP1 Startup.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables DPP1 Startup.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_STRTUP_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_STRTUP_Dis(void);

/** \brief Selects ADC1 Sequencer Mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Sequencer_Mode_Sel(void);

/** \brief Selects ADC1 Software Mode, measurements are performed on user request.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1, switches to Software Mode and starts an ADC1 conversion on channel 6 - P2.0
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Software_Mode_Sel();
 *     ADC1_SW_Channel_Sel( ADC1_P20 );
 *     ADC1_SOS_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Software_Mode_Sel(void);

/** \brief Reads the End-of-Conversion status.
 *
 * \retval 1 if conversion has ended
 * \retval 0 if conversion still ongoing
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode, starts a measurement and waits for it to be finished.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Software_Mode_Sel();
 *     ADC1_SW_Channel_Sel( ADC1_MON1 );
 *     ADC1_SOS_Set();
 *
 *     while ( ADC1_EOC_Sts() == 0 ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint8 ADC1_EOC_Sts(void);

/** \brief Reads the active status of the Exceptional Interrupt Measurement (EIM).
 *
 * \retval 1 EIM ongoing
 * \retval 0 no EIM active
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 module and EIM, switches to Sequencer Mode and reads the active status of the Exceptional Interrupt Measurement (EIM).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_EIM_En();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_EIM_Channel_Set( ADC1_MON1 );
 *
 *     while (ADC1_EIM_Active_Sts() == 0u)
 *     {
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint8 ADC1_EIM_Active_Sts(void);

/** \brief Reads the active status of the Exceptional Sequencer Measurement (ESM).
 *
 * \retval 1 ESM ongoing
 * \retval 0 no ESM active
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 module and ESM, switches to Sequencer Mode and reads the active status of the Exceptional Sequencer Measurement (ESM).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ESM_En();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_ESM_Channel_Set( ADC1_MASK_MON1 );
 *
 *     while (ADC1_ESM_Active_Sts() == 0u)
 *     {
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint8 ADC1_ESM_Active_Sts(void);

/** \brief Reads the currently active channel status in Sequencer Mode.
 *
 * \return uint8, number of the current sequence, values between 0..13
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode and reads the currently active channel 6 in Sequencer Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_P20 );
 *     while (ADC1_Current_Active_Sequence_Sts() & 0x6 != 0x6)
 *     {
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint8 ADC1_Current_Active_Sequence_Sts(void);

/** \brief Reads the currently active channel status.
 *
 * \return uint8, number of the current channel, values between 0..13
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode and reads the currently active channel 6.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Software_Mode_Sel();
 *     ADC1_SW_Channel_Sel( ADC1_P20 );
 *     ADC1_SOS_Set();
 *     while (ADC1_Current_Active_Channel_Sts() & 0x6 != 0x6)
 *     {
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint8 ADC1_Current_Active_Channel_Sts(void);

/** \brief Reads the ADC1 Sequencer Stop Signal for DPP Status.
 *
 * \retval 0 if DPP is Running.
 * \retval 1 if DPP is Stopped.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode and reads the DPP Stop Signal Status in Sequencer Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     while (ADC1_Sequencer_Stop_Signal_Sts() == 0)
 *     {
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint8 ADC1_Sequencer_Stop_Signal_Sts(void);

/** \brief Reads the Current Sequence that caused software mode.
 *
 * \return Current Sequence that caused software mode
 *
 * \brief <b>Example</b><br>
 * \brief This example reads the current sequence that caused software mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     ADC1_Power_On();
 *     sts = ADC1_Sequence_Feedback_Sts();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint8 ADC1_Sequence_Feedback_Sts(void);

/** \brief Sets Maximum Time in Software Mode.
 *
 * \param time Maximum Time
 *
 * \brief <b>Example</b><br>
 * \brief This example starts an ADC1 conversion on channel 6 - P2.0 after setting Maximum Time to 12.75us.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Software_Mode_Sel();
 *     ADC1_SW_Channel_Sel(ADC1_P20);
 *     ADC1_SW_Max_Time_Set(0xFF);
 *     ADC1_SOS_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_SW_Max_Time_Set(uint8 time);

/** \brief Defines the channels to be measured in Sequence 0, only valid in Sequencer Mode, see \link ADC1_Sequencer_Mode_Sel \endlink.
 *
 * \param mask_ch a bit mask of channels to be set for this sequence
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 3 (MON2) and channel 9 (P2.3).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_MON2 | ADC1_MASK_P23 );
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Sequence0_Set(uint16 mask_ch);

/** \brief Defines the channels to be measured in Sequence 1, only valid in Sequencer Mode, see \link ADC1_Sequencer_Mode_Sel \endlink.
 *
 * \param mask_ch a bit mask of channels to be set for this sequence
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 3 (MON2) and channel 9 (P2.3).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence1_Set( ADC1_MASK_MON2 | ADC1_MASK_P23 );
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Sequence1_Set(uint16 mask_ch);

/** \brief Defines the channels to be measured in Sequence 2, only valid in Sequencer Mode, see \link ADC1_Sequencer_Mode_Sel \endlink.
 *
 * \param mask_ch a bit mask of channels to be set for this sequence
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 3 (MON2) and channel 9 (P2.3).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence2_Set( ADC1_MASK_MON2 | ADC1_MASK_P23 );
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Sequence2_Set(uint16 mask_ch);

/** \brief Defines the channels to be measured in Sequence 3, only valid in Sequencer Mode, see \link ADC1_Sequencer_Mode_Sel \endlink.
 *
 * \param mask_ch a bit mask of channels to be set for this sequence
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 3 (MON2) and channel 9 (P2.3).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence3_Set( ADC1_MASK_MON2 | ADC1_MASK_P23 );
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Sequence3_Set(uint16 mask_ch);

/** \brief Defines the channels to be measured in Sequence 4, only valid in Sequencer Mode, see \link ADC1_Sequencer_Mode_Sel \endlink.
 *
 * \param mask_ch a bit mask of channels to be set for this sequence
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 3 (MON2) and channel 9 (P2.3).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence4_Set( ADC1_MASK_MON2 | ADC1_MASK_P23 );
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Sequence4_Set(uint16 mask_ch);

/** \brief Defines the channels to be measured in Sequence 5, only valid in Sequencer Mode, see \link ADC1_Sequencer_Mode_Sel \endlink.
 *
 * \param mask_ch a bit mask of channels to be set for this sequence
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 3 (MON2) and channel 9 (P2.3).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence5_Set( ADC1_MASK_MON2 | ADC1_MASK_P23 );
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Sequence5_Set(uint16 mask_ch);

/** \brief Defines the channels to be measured in Sequence 6, only valid in Sequencer Mode, see \link ADC1_Sequencer_Mode_Sel \endlink.
 *
 * \param mask_ch a bit mask of channels to be set for this sequence
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 3 (MON2) and channel 9 (P2.3).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence6_Set( ADC1_MASK_MON2 | ADC1_MASK_P23 );
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Sequence6_Set(uint16 mask_ch);

/** \brief Defines the channels to be measured in Sequence 7, only valid in Sequencer Mode, see \link ADC1_Sequencer_Mode_Sel \endlink.
 *
 * \param mask_ch a bit mask of channels to be set for this sequence
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 3 (MON2) and channel 9 (P2.3).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence7_Set( ADC1_MASK_MON2 | ADC1_MASK_P23 );
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Sequence7_Set(uint16 mask_ch);

/** \brief Defines the channels to be measured in Sequence 8, only valid in Sequencer Mode, see \link ADC1_Sequencer_Mode_Sel \endlink.
 *
 * \param mask_ch a bit mask of channels to be set for this sequence
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 3 (MON2) and channel 9 (P2.3).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence8_Set( ADC1_MASK_MON2 | ADC1_MASK_P23 );
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Sequence8_Set(uint16 mask_ch);

/** \brief Defines the channels to be measured in Sequence 9, only valid in Sequencer Mode, see \link ADC1_Sequencer_Mode_Sel \endlink.
 *
 * \param mask_ch a bit mask of channels to be set for this sequence
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 3 (MON2) and channel 9 (P2.3).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence9_Set( ADC1_MASK_MON2 | ADC1_MASK_P23 );
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Sequence9_Set(uint16 mask_ch);

/** \brief Defines the channels to be measured in Sequence 10, only valid in Sequencer Mode, see \link ADC1_Sequencer_Mode_Sel \endlink.
 *
 * \param mask_ch a bit mask of channels to be set for this sequence
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 3 (MON2) and channel 9 (P2.3).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence10_Set( ADC1_MASK_MON2 | ADC1_MASK_P23 );
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Sequence10_Set(uint16 mask_ch);

/** \brief Defines the channels to be measured in Sequence 11, only valid in Sequencer Mode, see \link ADC1_Sequencer_Mode_Sel \endlink.
 *
 * \param mask_ch a bit mask of channels to be set for this sequence
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 3 (MON2) and channel 9 (P2.3).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence11_Set( ADC1_MASK_MON2 | ADC1_MASK_P23 );
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Sequence11_Set(uint16 mask_ch);

/** \brief Defines the channels to be measured in Sequence 12, only valid in Sequencer Mode, see \link ADC1_Sequencer_Mode_Sel \endlink.
 *
 * \param mask_ch a bit mask of channels to be set for this sequence
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 3 (MON2) and channel 9 (P2.3).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence12_Set( ADC1_MASK_MON2 | ADC1_MASK_P23 );
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Sequence12_Set(uint16 mask_ch);

/** \brief Defines the channels to be measured in Sequence 13, only valid in Sequencer Mode, see \link ADC1_Sequencer_Mode_Sel \endlink.
 *
 * \param mask_ch a bit mask of channels to be set for this sequence
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 3 (MON2) and channel 9 (P2.3).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence13_Set( ADC1_MASK_MON2 | ADC1_MASK_P23 );
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Sequence13_Set(uint16 mask_ch);

/** \brief Reads the converted value from the channel 0 result register.
 *
 * \return 12-bit value, with left aligned 10-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 0 (VBAT_SENSE) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_VBAT_SENSE );
 *
 *     if (ADC1_GetChResValid(0) == 1u)
 *     {
 *         adc_result = ADC1_Ch0_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_Ch0_Result_Get(void);

/** \brief Reads the converted value from the channel 1 result register.
 *
 * \return 12-bit value, with left aligned 10-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 1 (VS) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_VS );
 *
 *     if (ADC1_GetChResValid(1) == 1u)
 *     {
 *         adc_result = ADC1_Ch1_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_Ch1_Result_Get(void);

/** \brief Reads the converted value from the channel 2 result register.
 *
 * \return 12-bit value, with left aligned 10-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 2 (MON1) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_MON1 );
 *
 *     if (ADC1_GetChResValid(2) == 1u)
 *     {
 *         adc_result = ADC1_Ch2_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_Ch2_Result_Get(void);

/** \brief Reads the converted value from the channel 3 result register.
 *
 * \return 12-bit value, with left aligned 10-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 3 (MON2) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_MON2 );
 *
 *     if (ADC1_GetChResValid(3) == 1u)
 *     {
 *         adc_result = ADC1_Ch3_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_Ch3_Result_Get(void);

/** \brief Reads the converted value from the channel 4 result register.
 *
 * \return 12-bit value, with left aligned 10-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 4 (MON3) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_MON3 );
 *
 *     if (ADC1_GetChResValid(4) == 1u)
 *     {
 *         adc_result = ADC1_Ch4_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_Ch4_Result_Get(void);

/** \brief Reads the converted value from the channel 5 result register.
 *
 * \return 12-bit value, with left aligned 10-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 5 (MON4) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_MON4 );
 *
 *     if (ADC1_GetChResValid(5) == 1u)
 *     {
 *         adc_result = ADC1_Ch5_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_Ch5_Result_Get(void);

/** \brief Reads the converted value from the channel 6 result register.
 *
 * \return 12-bit value, with left aligned 10-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 6 (P2.0) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P20 );
 *
 *     if (ADC1_GetChResValid(6) == 1u)
 *     {
 *         adc_result = ADC1_Ch6_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_Ch6_Result_Get(void);

/** \brief Reads the converted value from the channel 7 result register.
 *
 * \return 12-bit value, with left aligned 10-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 7 (P2.1) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P21 );
 *
 *     if (ADC1_GetChResValid(7) == 1u)
 *     {
 *         adc_result = ADC1_Ch7_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_Ch7_Result_Get(void);

/** \brief Reads the converted value from the channel 8 result register.
 *
 * \return 12-bit value, with left aligned 10-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 8 (P2.2) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P22 );
 *
 *     if (ADC1_GetChResValid(8) == 1u)
 *     {
 *         adc_result = ADC1_Ch8_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_Ch8_Result_Get(void);

/** \brief Reads the converted value from the channel 9 result register.
 *
 * \return 12-bit value, with left aligned 10-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 9 (P2.3) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P23 );
 *
 *     if (ADC1_GetChResValid(9) == 1u)
 *     {
 *         adc_result = ADC1_Ch9_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_Ch9_Result_Get(void);

/** \brief Reads the converted value from the channel 12 (P2.7) result register.
 *
 * \return 12-bit value, with left aligned 10-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 12 (P2.7) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P27 );
 *
 *     if (ADC1_GetChResValid(12) == 1u)
 *     {
 *         adc_result = ADC1_Ch12_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_Ch12_Result_Get(void);

/** \brief Reads the converted value from the channel 13 (CSA) result register.
 *
 * \return 12-bit value, with left aligned 10-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 13 (CSA) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_OPA );
 *
 *     if (ADC1_GetChResValid(13) == 1u)
 *     {
 *         adc_result = ADC1_Ch13_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_Ch13_Result_Get(void);

/** \brief Reads the converted value from the EIM result register.
 *
 * \return 12-bit value, with left aligned 10-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 2 (MON1) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_EIM_Channel_Set( ADC1_CH2 );
 *
 *     while (ADC1->FILT_OUTEIM.bit.VF_EIM == 0u)
 *     {
 *     }
 *
 *     adc_result = ADC1_EIM_Result_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_EIM_Result_Get(void);

/** \brief Reads ADC differential 1 output value.
 *
 * \return 12-bit value, with left aligned 10-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and DU1 and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_DU1_En();
 *
 *     while (ADC1->DIFFCH_OUT1.bit.DVF1 == 0u)
 *     {
 *     }
 *
 *     adc_result = ADC1_DU1_Result_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_DU1_Result_Get(void);

/** \brief Reads the converted value from the channel 0 result register.
 *
 * \return 12-bit value, with left aligned 10-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 0 (VBAT_SENSE) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_VBAT_SENSE );
 *
 *     if (ADC1_GetChResValid(0) == 1u)
 *     {
 *         adc_result = ADC1_VBAT_SENSE_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_VBAT_SENSE_Result_Get(void);

/** \brief Reads the converted value from the channel 1 result register.
 *
 * \return 12-bit value, with left aligned 10-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 1 (VS) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_VS );
 *
 *     if (ADC1_GetChResValid(1) == 1u)
 *     {
 *         adc_result = ADC1_VS_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_VS_Result_Get(void);

/** \brief Reads the converted value from the channel 2 result register.
 *
 * \return 12-bit value, with left aligned 10-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 2 (MON1) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_MON1 );
 *
 *     if (ADC1_GetChResValid(2) == 1u)
 *     {
 *         adc_result = ADC1_MON1_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_MON1_Result_Get(void);

/** \brief Reads the converted value from the channel 3 result register.
 *
 * \return 12-bit value, with left aligned 10-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 3 (MON2) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_MON2 );
 *
 *     if (ADC1_GetChResValid(3) == 1u)
 *     {
 *         adc_result = ADC1_MON2_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_MON2_Result_Get(void);

/** \brief Reads the converted value from the channel 4 result register.
 *
 * \return 12-bit value, with left aligned 10-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 4 (MON3) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_MON3 );
 *
 *     if (ADC1_GetChResValid(4) == 1u)
 *     {
 *         adc_result = ADC1_MON3_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_MON3_Result_Get(void);

/** \brief Reads the converted value from the channel 5 result register.
 *
 * \return 12-bit value, with left aligned 10-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 5 (MON4) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_MON4 );
 *
 *     if (ADC1_GetChResValid(5) == 1u)
 *     {
 *         adc_result = ADC1_MON4_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_MON4_Result_Get(void);

/** \brief Reads the converted value from the channel 6 result register.
 *
 * \return 12-bit value, with left aligned 10-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 6 (P2.0) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P20 );
 *
 *     if (ADC1_GetChResValid(6) == 1u)
 *     {
 *         adc_result = ADC1_P20_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_P20_Result_Get(void);

/** \brief Reads the converted value from the channel 7 result register.
 *
 * \return 12-bit value, with left aligned 10-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 7 (P2.1) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P21 );
 *
 *     if (ADC1_GetChResValid(7) == 1u)
 *     {
 *         adc_result = ADC1_P21_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_P21_Result_Get(void);

/** \brief Reads the converted value from the channel 8 result register.
 *
 * \return 12-bit value, with left aligned 10-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 8 (P2.2) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P22 );
 *
 *     if (ADC1_GetChResValid(8) == 1u)
 *     {
 *         adc_result = ADC1_P22_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_P22_Result_Get(void);

/** \brief Reads the converted value from the channel 9 result register.
 *
 * \return 12-bit value, with left aligned 10-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 9 (P2.3) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P23 );
 *
 *     if (ADC1_GetChResValid(9) == 1u)
 *     {
 *         adc_result = ADC1_P23_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_P23_Result_Get(void);

/** \brief Reads the converted value from the channel 12 result register.
 *
 * \return 12-bit value, with left aligned 10-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 12 (P2.7) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P27 );
 *
 *     if (ADC1_GetChResValid(12) == 1u)
 *     {
 *         adc_result = ADC1_P27_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_P27_Result_Get(void);

/** \brief Reads the converted value from the channel 13 result register.
 *
 * \return 12-bit value, with left aligned 10-bit result
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 13 (CSA) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_OPA );
 *
 *     if (ADC1_GetChResValid(13) == 1u)
 *     {
 *         adc_result = ADC1_OPA_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint16 ADC1_OPA_Result_Get(void);

/** \brief Sets the result register channel 0 to "wait for read".
 * \note A valid result will not be overwritten by a subsequent conversion until the result is read.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 0 (VBAT_SENSE) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_VBAT_SENSE );
 *     ADC1_Ch0_WaitForRead_Set();
 *
 *     if (ADC1_GetChResValid(0) == 1u)
 *     {
 *         adc_result = ADC1_VBAT_SENSE_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch0_WaitForRead_Set(void);

/** \brief Sets the result register channel 0 to "overwrite".
 * \note A valid result will be overwritten by a subsequent conversion, a previous unread conversion is lost.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 0 (VBAT_SENSE) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_VBAT_SENSE );
 *     ADC1_Ch0_Overwrite_Set();
 *
 *     if (ADC1_GetChResValid(0) == 1u)
 *     {
 *         adc_result = ADC1_VBAT_SENSE_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch0_Overwrite_Set(void);

/** \brief Sets the result register channel 1 to "wait for read".
 * \note A valid result will not be overwritten by a subsequent conversion until the result is read.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 1 (VS) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_VS );
 *     ADC1_Ch1_WaitForRead_Set();
 *
 *     if (ADC1_GetChResValid(1) == 1u)
 *     {
 *         adc_result = ADC1_VS_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch1_WaitForRead_Set(void);

/** \brief Sets the result register channel 1 to "overwrite".
 * \note A valid result will be overwritten by a subsequent conversion, a previous unread conversion is lost.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 1 (VS) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_VS );
 *     ADC1_Ch1_Overwrite_Set();
 *
 *     if (ADC1_GetChResValid(1) == 1u)
 *     {
 *         adc_result = ADC1_VS_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch1_Overwrite_Set(void);

/** \brief Sets the result register channel 2 to "wait for read".
 * \note A valid result will not be overwritten by a subsequent conversion until the result is read.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 2 (MON1) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_MON1 );
 *     ADC1_Ch2_WaitForRead_Set();
 *
 *     if (ADC1_GetChResValid(2) == 1u)
 *     {
 *         adc_result = ADC1_MON1_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch2_WaitForRead_Set(void);

/** \brief Sets the result register channel 2 to "overwrite".
 * \note A valid result will be overwritten by a subsequent conversion, a previous unread conversion is lost.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 2 (MON1) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_MON1 );
 *     ADC1_Ch2_Overwrite_Set();
 *
 *     if (ADC1_GetChResValid(2) == 1u)
 *     {
 *         adc_result = ADC1_MON1_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch2_Overwrite_Set(void);

/** \brief Sets the result register channel 3 to "wait for read".
 * \note A valid result will not be overwritten by a subsequent conversion until the result is read.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 3 (MON2) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_MON2 );
 *     ADC1_Ch3_WaitForRead_Set();
 *
 *     if (ADC1_GetChResValid(3) == 1u)
 *     {
 *         adc_result = ADC1_MON2_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch3_WaitForRead_Set(void);

/** \brief Sets the result register channel 3 to "overwrite".
 * \note A valid result will be overwritten by a subsequent conversion, a previous unread conversion is lost.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 3 (MON2) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_MON2 );
 *     ADC1_Ch3_Overwrite_Set();
 *
 *     if (ADC1_GetChResValid(3) == 1u)
 *     {
 *         adc_result = ADC1_MON2_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch3_Overwrite_Set(void);

/** \brief Sets the result register channel 4 to "wait for read".
 * \note A valid result will not be overwritten by a subsequent conversion until the result is read.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 4 (MON3) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_MON3 );
 *     ADC1_Ch4_WaitForRead_Set();
 *
 *     if (ADC1_GetChResValid(4) == 1u)
 *     {
 *         adc_result = ADC1_MON3_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch4_WaitForRead_Set(void);

/** \brief Sets the result register channel 4 to "overwrite".
 * \note A valid result will be overwritten by a subsequent conversion, a previous unread conversion is lost.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 4 (MON3) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_MON3 );
 *     ADC1_Ch4_Overwrite_Set();
 *
 *     if (ADC1_GetChResValid(4) == 1u)
 *     {
 *         adc_result = ADC1_MON3_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch4_Overwrite_Set(void);

/** \brief Sets the result register channel 5 to "wait for read".
 * \note A valid result will not be overwritten by a subsequent conversion until the result is read.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 5 (MON4) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_MON4 );
 *     ADC1_Ch5_WaitForRead_Set();
 *
 *     if (ADC1_GetChResValid(5) == 1u)
 *     {
 *         adc_result = ADC1_MON4_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch5_WaitForRead_Set(void);

/** \brief Sets the result register channel 5 to "overwrite".
 * \note A valid result will be overwritten by a subsequent conversion, a previous unread conversion is lost.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 5 (MON4) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_MON4 );
 *     ADC1_Ch5_Overwrite_Set();
 *
 *     if (ADC1_GetChResValid(5) == 1u)
 *     {
 *         adc_result = ADC1_MON4_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch5_Overwrite_Set(void);

/** \brief Sets the result register channel 6 to "wait for read".
 * \note A valid result will not be overwritten by a subsequent conversion until the result is read.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 6 (P2.0) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P20 );
 *     ADC1_Ch6_WaitForRead_Set();
 *
 *     if (ADC1_GetChResValid(6) == 1u)
 *     {
 *         adc_result = ADC1_P20_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch6_WaitForRead_Set(void);

/** \brief Sets the result register channel 6 to "overwrite".
 * \note A valid result will be overwritten by a subsequent conversion, a previous unread conversion is lost.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 6 (P2.0) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P20 );
 *     ADC1_Ch6_Overwrite_Set();
 *
 *     if (ADC1_GetChResValid(6) == 1u)
 *     {
 *         adc_result = ADC1_P20_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch6_Overwrite_Set(void);

/** \brief Sets the result register channel 7 to "wait for read".
 * \note A valid result will not be overwritten by a subsequent conversion until the result is read.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 7 (P2.1) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P21 );
 *     ADC1_Ch7_WaitForRead_Set();
 *
 *     if (ADC1_GetChResValid(7) == 1u)
 *     {
 *         adc_result = ADC1_P21_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch7_WaitForRead_Set(void);

/** \brief Sets the result register channel 7 to "overwrite".
 * \note A valid result will be overwritten by a subsequent conversion, a previous unread conversion is lost.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 7 (P2.1) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P21 );
 *     ADC1_Ch7_Overwrite_Set();
 *
 *     if (ADC1_GetChResValid(7) == 1u)
 *     {
 *         adc_result = ADC1_P21_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch7_Overwrite_Set(void);

/** \brief Sets the result register channel 8 to "wait for read".
 * \note A valid result will not be overwritten by a subsequent conversion until the result is read.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 8 (P2.2) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P22 );
 *     ADC1_Ch8_WaitForRead_Set();
 *
 *     if (ADC1_GetChResValid(8) == 1u)
 *     {
 *         adc_result = ADC1_P22_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch8_WaitForRead_Set(void);

/** \brief Sets the result register channel 8 to "overwrite".
 * \note A valid result will be overwritten by a subsequent conversion, a previous unread conversion is lost.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 8 (P2.2) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P22 );
 *     ADC1_Ch8_Overwrite_Set();
 *
 *     if (ADC1_GetChResValid(8) == 1u)
 *     {
 *         adc_result = ADC1_P22_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch8_Overwrite_Set(void);

/** \brief Sets the result register channel 9 to "wait for read".
 * \note A valid result will not be overwritten by a subsequent conversion until the result is read.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 9 (P2.3) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P23 );
 *     ADC1_Ch9_WaitForRead_Set();
 *
 *     if (ADC1_GetChResValid(9) == 1u)
 *     {
 *         adc_result = ADC1_P23_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch9_WaitForRead_Set(void);

/** \brief Sets the result register channel 9 to "overwrite".
 * \note A valid result will be overwritten by a subsequent conversion, a previous unread conversion is lost.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 9 (P2.3) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P23 );
 *     ADC1_Ch9_Overwrite_Set();
 *
 *     if (ADC1_GetChResValid(9) == 1u)
 *     {
 *         adc_result = ADC1_P23_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch9_Overwrite_Set(void);

/** \brief Sets the result register channel 12 to "wait for read".
 * \note A valid result will not be overwritten by a subsequent conversion until the result is read.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 12 (P2.7) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P27 );
 *     ADC1_Ch12_WaitForRead_Set();
 *
 *     if (ADC1_GetChResValid(12) == 1u)
 *     {
 *         adc_result = ADC1_P27_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch12_WaitForRead_Set(void);

/** \brief Sets the result register channel 12 to "overwrite".
 * \note A valid result will be overwritten by a subsequent conversion, a previous unread conversion is lost.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 12 (P2.7) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_P27 );
 *     ADC1_Ch12_Overwrite_Set();
 *
 *     if (ADC1_GetChResValid(12) == 1u)
 *     {
 *         adc_result = ADC1_P27_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch12_Overwrite_Set(void);

/** \brief Sets the result register channel 13 to "wait for read".
 * \note A valid result will not be overwritten by a subsequent conversion until the result is read.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 13 (CSA) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_OPA );
 *     ADC1_Ch13_WaitForRead_Set();
 *
 *     if (ADC1_GetChResValid(13) == 1u)
 *     {
 *         adc_result = ADC1_OPA_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch13_WaitForRead_Set(void);

/** \brief Sets the result register channel 13 to "overwrite".
 * \note A valid result will be overwritten by a subsequent conversion, a previous unread conversion is lost.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 13 (CSA) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_Sequence0_Set( ADC1_MASK_OPA );
 *     ADC1_Ch13_Overwrite_Set();
 *
 *     if (ADC1_GetChResValid(13) == 1u)
 *     {
 *         adc_result = ADC1_OPA_Result_Get();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch13_Overwrite_Set(void);

/** \brief Sets the result register DU1 to "wait for read".
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and DU1 and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_DU1_En();
 *     ADC1_DU1_WaitForRead_Set();
 *
 *     while (ADC1->DIFFCH_OUT1.bit.DVF1 == 0u)
 *     {
 *     }
 *
 *     adc_result = ADC1_DU1_Result_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_DU1_WaitForRead_Set(void);

/** \brief Sets the result register DU1 to "overwrite".
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and DU1 and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_DU1_En();
 *     ADC1_DU1_Overwrite_Set();
 *
 *     while (ADC1->DIFFCH_OUT1.bit.DVF1 == 0u)
 *     {
 *     }
 *
 *     adc_result = ADC1_DU1_Result_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_DU1_Overwrite_Set(void);

/** \brief Enables Exceptional interrupt measurement (EIM) Trigger Event.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Exceptional Interrupt Measurement (EIM).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_EIM_En();
 *     ADC1_EIM_Int_En();
 *     if (ADC1->IRQS_1.bit.EIM_IS == 1u)
 *     {
 *         ADC1_EIM_CALLBACK();
 *         ADC1_EIM_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_EIM_En(void);

/** \brief Disables Exceptional interrupt measurement (EIM) Trigger Event.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Exceptional Interrupt Measurement (EIM).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_EIM_En();
 *     ADC1_EIM_Int_En();
 *     if (ADC1->IRQS_1.bit.EIM_IS == 1u)
 *     {
 *         ADC1_EIM_CALLBACK();
 *         ADC1_EIM_Int_Clr();
 *     }
 *     ADC1_EIM_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_EIM_Dis(void);

/** \brief Enables Exceptional Sequence measurement (ESM) Trigger Event.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Exceptional Sequence Measurement (ESM).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_ESM_En();
 *     ADC1_ESM_Int_En();
 *     if (ADC1->IRQS_1.bit.ESM_IS == 1u)
 *     {
 *         ADC1_ESM_CALLBACK();
 *         ADC1_ESM_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_ESM_En(void);

/** \brief Disables Exceptional Sequence measurement (ESM) Trigger Event.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Exceptional Sequence Measurement (ESM).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_ESM_En();
 *     ADC1_ESM_Int_En();
 *     if (ADC1->IRQS_1.bit.ESM_IS == 1u)
 *     {
 *         ADC1_ESM_CALLBACK();
 *         ADC1_ESM_Int_Clr();
 *     }
 *     ADC1_ESM_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_ESM_Dis(void);

/** \brief Sets EIM channel for measurement.
 *
 * \param ch channel to be measured
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 2 (MON1) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_EIM_Channel_Set( ADC1_CH2 );
 *
 *     while (ADC1->FILT_OUTEIM.bit.VF_EIM == 0u)
 *     {
 *     }
 *
 *     adc_result = ADC1_EIM_Result_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_EIM_Channel_Set(uint8 ch);

/** \brief Sets channels in ESM sequence.
 *
 * \param mask_ch bit mask of channels to be measured
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1, switches to Sequencer Mode, programs channel 6 (P2.0), and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_ESM_Channel_Set( ADC1_MASK_P20 );
 *
 *     while (ADC1->FILT_OUT6.bit.VF6 == 0u)
 *     {
 *     }
 *
 *     adc_result = ADC1_P20_Result_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_ESM_Channel_Set(uint16 mask_ch);

/** \brief Reads EIM channel for measurement.
 *
 * \return EIM Channel Enabled
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, reads the corresponding Attenuator Factor of the EIM channel.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint32 fs;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     fs = ADC1_GetChAttFactor(ADC1_EIM_Channel_Read());
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint8 ADC1_EIM_Channel_Read(void);

/** \brief Enables Upper and Lower Threshold IIR Filter Post-Processing Channel 0.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 0 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch0_Filt_UpLo_En();
 *     ADC1_PP_Ch0_UP_Int_En();
 *     if (ADC1->IRQS_2.bit.PP_CH0_UP_IS == 1u)
 *     {
 *       ADC1_PP_CH0_UP_CALLBACK();
 *       ADC1_PP_Ch0_UP_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch0_Filt_UpLo_En(void);

/** \brief Enables Upper and Lower Threshold IIR Filter Post-Processing Channel 1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 1 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch1_Filt_UpLo_En();
 *     ADC1_PP_Ch1_UP_Int_En();
 *     if (ADC1->IRQS_2.bit.PP_CH1_UP_IS == 1u)
 *     {
 *         ADC1_PP_CH1_UP_CALLBACK();
 *         ADC1_PP_Ch1_UP_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch1_Filt_UpLo_En(void);

/** \brief Enables Upper and Lower Threshold IIR Filter Post-Processing Channel 2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 2 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch2_Filt_UpLo_En();
 *     ADC1_PP_Ch2_UP_Int_En();
 *     if (ADC1->IRQS_2.bit.PP_CH2_UP_IS == 1u)
 *     {
 *         ADC1_PP_CH2_UP_CALLBACK();
 *         ADC1_PP_Ch2_UP_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch2_Filt_UpLo_En(void);

/** \brief Enables Upper and Lower Threshold IIR Filter Post-Processing Channel 3.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 3 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch3_Filt_UpLo_En();
 *     ADC1_PP_Ch3_UP_Int_En();
 *     if (ADC1->IRQS_2.bit.PP_CH3_UP_IS == 1u)
 *     {
 *         ADC1_PP_CH3_UP_CALLBACK();
 *         ADC1_PP_Ch3_UP_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch3_Filt_UpLo_En(void);

/** \brief Enables Upper and Lower Threshold IIR Filter Post-Processing Channel 4.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 4 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch4_Filt_UpLo_En();
 *     ADC1_PP_Ch4_UP_Int_En();
 *     if (ADC1->IRQS_2.bit.PP_CH4_UP_IS == 1u)
 *     {
 *         ADC1_PP_CH4_UP_CALLBACK();
 *         ADC1_PP_Ch4_UP_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch4_Filt_UpLo_En(void);

/** \brief Enables Upper and Lower Threshold IIR Filter Post-Processing Channel 5.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 5 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch5_Filt_UpLo_En();
 *     ADC1_PP_Ch5_UP_Int_En();
 *     if (ADC1->IRQS_2.bit.PP_CH5_UP_IS == 1u)
 *     {
 *         ADC1_PP_CH5_UP_CALLBACK();
 *         ADC1_PP_Ch5_UP_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch5_Filt_UpLo_En(void);

/** \brief Enables Upper and Lower Threshold IIR Filter Post-Processing Channel 6.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 6 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch6_Filt_UpLo_En();
 *     ADC1_PP_Ch6_UP_Int_En();
 *     if (ADC1->IRQS_2.bit.PP_CH6_UP_IS == 1u)
 *     {
 *         ADC1_PP_CH6_UP_CALLBACK();
 *         ADC1_PP_Ch6_UP_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch6_Filt_UpLo_En(void);

/** \brief Enables Upper and Lower Threshold IIR Filter Post-Processing Channel 7.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 7 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch7_Filt_UpLo_En();
 *     ADC1_PP_Ch7_UP_Int_En();
 *     if (ADC1->IRQS_2.bit.PP_CH7_UP_IS == 1u)
 *     {
 *         ADC1_PP_CH7_UP_CALLBACK();
 *         ADC1_PP_Ch7_UP_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch7_Filt_UpLo_En(void);

/** \brief Disables Upper and Lower Threshold IIR Filter Post-Processing Channel 0.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 0 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch0_Filt_UpLo_En();
 *     ADC1_PP_Ch0_UP_Int_En();
 *     if (ADC1->IRQS_2.bit.PP_CH0_UP_IS == 1u)
 *     {
 *         ADC1_PP_CH0_UP_CALLBACK();
 *         ADC1_PP_Ch0_UP_Int_Clr();
 *     }
 *     ADC1_PP_Ch0_Filt_UpLo_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch0_Filt_UpLo_Dis(void);

/** \brief Disables Upper and Lower Threshold IIR Filter Post-Processing Channel 1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 1 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch1_Filt_UpLo_En();
 *     ADC1_PP_Ch1_UP_Int_En();
 *     if (ADC1->IRQS_2.bit.PP_CH1_UP_IS == 1u)
 *     {
 *         ADC1_PP_CH1_UP_CALLBACK();
 *         ADC1_PP_Ch1_UP_Int_Clr();
 *     }
 *     ADC1_PP_Ch1_Filt_UpLo_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch1_Filt_UpLo_Dis(void);

/** \brief Disables Upper and Lower Threshold IIR Filter Post-Processing Channel 2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 2 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch2_Filt_UpLo_En();
 *     ADC1_PP_Ch2_UP_Int_En();
 *     if (ADC1->IRQS_2.bit.PP_CH2_UP_IS == 1u)
 *     {
 *         ADC1_PP_CH2_UP_CALLBACK();
 *         ADC1_PP_Ch2_UP_Int_Clr();
 *     }
 *     ADC1_PP_Ch2_Filt_UpLo_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch2_Filt_UpLo_Dis(void);

/** \brief Disables Upper and Lower Threshold IIR Filter Post-Processing Channel 3.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 3 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch3_Filt_UpLo_En();
 *     ADC1_PP_Ch3_UP_Int_En();
 *     if (ADC1->IRQS_2.bit.PP_CH3_UP_IS == 1u)
 *     {
 *         ADC1_PP_CH3_UP_CALLBACK();
 *         ADC1_PP_Ch3_UP_Int_Clr();
 *     }
 *     ADC1_PP_Ch3_Filt_UpLo_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch3_Filt_UpLo_Dis(void);

/** \brief Disables Upper and Lower Threshold IIR Filter Post-Processing Channel 4.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 4 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch4_Filt_UpLo_En();
 *     ADC1_PP_Ch4_UP_Int_En();
 *     if (ADC1->IRQS_2.bit.PP_CH4_UP_IS == 1u)
 *     {
 *         ADC1_PP_CH4_UP_CALLBACK();
 *         ADC1_PP_Ch4_UP_Int_Clr();
 *     }
 *     ADC1_PP_Ch4_Filt_UpLo_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch4_Filt_UpLo_Dis(void);

/** \brief Disables Upper and Lower Threshold IIR Filter Post-Processing Channel 5.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 5 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch5_Filt_UpLo_En();
 *     ADC1_PP_Ch5_UP_Int_En();
 *     if (ADC1->IRQS_2.bit.PP_CH5_UP_IS == 1u)
 *     {
 *         ADC1_PP_CH5_UP_CALLBACK();
 *         ADC1_PP_Ch5_UP_Int_Clr();
 *     }
 *     ADC1_PP_Ch5_Filt_UpLo_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch5_Filt_UpLo_Dis(void);

/** \brief Disables Upper and Lower Threshold IIR Filter Post-Processing Channel 6.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 6 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch6_Filt_UpLo_En();
 *     ADC1_PP_Ch6_UP_Int_En();
 *     if (ADC1->IRQS_2.bit.PP_CH6_UP_IS == 1u)
 *     {
 *         ADC1_PP_CH6_UP_CALLBACK();
 *         ADC1_PP_Ch6_UP_Int_Clr();
 *     }
 *     ADC1_PP_Ch6_Filt_UpLo_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch6_Filt_UpLo_Dis(void);

/** \brief Disables Upper and Lower Threshold IIR Filter Post-Processing Channel 7.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 7 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch7_Filt_UpLo_En();
 *     ADC1_PP_Ch7_UP_Int_En();
 *     if (ADC1->IRQS_2.bit.PP_CH7_UP_IS == 1u)
 *     {
 *         ADC1_PP_CH7_UP_CALLBACK();
 *         ADC1_PP_Ch7_UP_Int_Clr();
 *     }
 *     ADC1_PP_Ch7_Filt_UpLo_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch7_Filt_UpLo_Dis(void);

/** \brief Clears ADC1 Differential Unit 1 (DU1) Lower Channel Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears ADC1 Differential Unit 1 (DU1) Lower Channel Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_DU1_En();
 *     ADC1_DU1_Lo_Sts_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_DU1_Lo_Sts_Clr(void);

/** \brief Clears ADC1 Differential Unit 1 (DU1) Upper Channel Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears ADC1 Differential Unit 1 (DU1) Upper Channel Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_DU1_En();
 *     ADC1_DU1_Up_Sts_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_DU1_Up_Sts_Clr(void);

/** \brief Enables ADC1 Differential Unit 1.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and DU1 and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_DU1_En();
 *     ADC1_DU1_Overwrite_Set();
 *
 *     while (ADC1->DIFFCH_OUT1.bit.DVF1 == 0u)
 *     {
 *     }
 *
 *     adc_result = ADC1_DU1_Result_Get();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_DU1_En(void);

/** \brief Disables ADC1 Differential Unit 1.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and DU1 and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_DU1_En();
 *     ADC1_DU1_Overwrite_Set();
 *
 *     while (ADC1->DIFFCH_OUT1.bit.DVF1 == 0u)
 *     {
 *     }
 *
 *     adc_result = ADC1_DU1_Result_Get();
 *     ADC1_DU1_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_DU1_Dis(void);

/** \brief Reads the Differential Unit 1 Negative Result Status.
 *
 * \return DU1 Negative Result Status; 0: DU1 positive result, 1: negative result
 *
 * \brief <b>Example</b><br>
 * \brief This example reads DU1 Result status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     sts = ADC1_DU1_Result_Neg_Sts();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE uint8 ADC1_DU1_Result_Neg_Sts(void);

/** \brief Selects ADC1 Post-Processing Channel 0 Measurement Mode.
 *
 * \param mmode Measurement Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 0 Measurement Mode to undervoltage limit measurement.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch0_Mode_Meas_Sel(ADC1_MMODE_UV);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch0_Mode_Meas_Sel(uint8 mmode);

/** \brief Selects ADC1 Post-Processing Channel 1 Measurement Mode.
 *
 * \param mmode Measurement Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 1 Measurement Mode to undervoltage limit measurement.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch1_Mode_Meas_Sel(ADC1_MMODE_UV);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch1_Mode_Meas_Sel(uint8 mmode);

/** \brief Selects ADC1 Post-Processing Channel 2 Measurement Mode.
 *
 * \param mmode Measurement Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 2 Measurement Mode to undervoltage limit measurement.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch2_Mode_Meas_Sel(ADC1_MMODE_UV);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch2_Mode_Meas_Sel(uint8 mmode);

/** \brief Selects ADC1 Post-Processing Channel 3 Measurement Mode.
 *
 * \param mmode Measurement Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 3 Measurement Mode to undervoltage limit measurement.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch3_Mode_Meas_Sel(ADC1_MMODE_UV);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch3_Mode_Meas_Sel(uint8 mmode);

/** \brief Selects ADC1 Post-Processing Channel 4 Measurement Mode.
 *
 * \param mmode Measurement Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 4 Measurement Mode to undervoltage limit measurement.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch4_Mode_Meas_Sel(ADC1_MMODE_UV);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch4_Mode_Meas_Sel(uint8 mmode);

/** \brief Selects ADC1 Post-Processing Channel 5 Measurement Mode.
 *
 * \param mmode Measurement Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 5 Measurement Mode to undervoltage limit measurement.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch5_Mode_Meas_Sel(ADC1_MMODE_UV);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch5_Mode_Meas_Sel(uint8 mmode);

/** \brief Selects ADC1 Post-Processing Channel 6 Measurement Mode.
 *
 * \param mmode Measurement Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 6 Measurement Mode to undervoltage limit measurement.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch6_Mode_Meas_Sel(ADC1_MMODE_UV);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch6_Mode_Meas_Sel(uint8 mmode);

/** \brief Selects ADC1 Post-Processing Channel 7 Measurement Mode.
 *
 * \param mmode Measurement Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 7 Measurement Mode to undervoltage limit measurement.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch7_Mode_Meas_Sel(ADC1_MMODE_UV);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch7_Mode_Meas_Sel(uint8 mmode);

/** \brief Selects ADC1 Differential Unit 1 Measurement Mode.
 *
 * \param mmode Measurement Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Differential Unit 1 Measurement Mode to undervoltage limit measurement.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_DU1_Mode_Meas_Sel(ADC1_MMODE_UV);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_DU1_Mode_Meas_Sel(uint8 mmode);

/** \brief Sets ADC1 Post-Processing Channel 0 Lower Trigger Level.
 *
 * \param trig_val Lower Trigger Level
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 0 Lower Trigger Level to Maximum value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch0_Lo_Th_Set(0xFF);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch0_Lo_Th_Set(uint8 trig_val);

/** \brief Sets ADC1 Post-Processing Channel 1 Lower Trigger Level.
 *
 * \param trig_val Lower Trigger Level
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 1 Lower Trigger Level to Maximum value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch1_Lo_Th_Set(0xFF);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch1_Lo_Th_Set(uint8 trig_val);

/** \brief Sets ADC1 Post-Processing Channel 2 Lower Trigger Level.
 *
 * \param trig_val Lower Trigger Level
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 2 Lower Trigger Level to Maximum value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch2_Lo_Th_Set(0xFF);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch2_Lo_Th_Set(uint8 trig_val);

/** \brief Sets ADC1 Post-Processing Channel 3 Lower Trigger Level.
 *
 * \param trig_val Lower Trigger Level
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 3 Lower Trigger Level to Maximum value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch3_Lo_Th_Set(0xFF);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch3_Lo_Th_Set(uint8 trig_val);

/** \brief Sets ADC1 Post-Processing Channel 4 Lower Trigger Level.
 *
 * \param trig_val Lower Trigger Level
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 4 Lower Trigger Level to Maximum value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch4_Lo_Th_Set(0xFF);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch4_Lo_Th_Set(uint8 trig_val);

/** \brief Sets ADC1 Post-Processing Channel 5 Lower Trigger Level.
 *
 * \param trig_val Lower Trigger Level
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 5 Lower Trigger Level to Maximum value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch5_Lo_Th_Set(0xFF);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch5_Lo_Th_Set(uint8 trig_val);

/** \brief Sets ADC1 Post-Processing Channel 6 Lower Trigger Level.
 *
 * \param trig_val Lower Trigger Level
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 6 Lower Trigger Level to Maximum value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch6_Lo_Th_Set(0xFF);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch6_Lo_Th_Set(uint8 trig_val);

/** \brief Sets ADC1 Post-Processing Channel 7 Lower Trigger Level.
 *
 * \param trig_val Lower Trigger Level
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 7 Lower Trigger Level to Maximum value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch7_Lo_Th_Set(0xFF);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch7_Lo_Th_Set(uint8 trig_val);

/** \brief Sets ADC1 Differential Unit 1 Lower Trigger Level.
 *
 * \param trig_val Lower Trigger Level
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Differential Unit 1 Lower Trigger Level to Maximum value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_DU1_Lo_Th_Set(0xFF);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_DU1_Lo_Th_Set(uint8 trig_val);

/** \brief Sets ADC1 Post-Processing Channel 0 Upper Trigger Level.
 *
 * \param trig_val Upper Trigger Level
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 0 Upper Trigger Level to Maximum value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch0_Up_Th_Set(0xFF);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch0_Up_Th_Set(uint8 trig_val);

/** \brief Sets ADC1 Post-Processing Channel 1 Upper Trigger Level.
 *
 * \param trig_val Upper Trigger Level
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 1 Upper Trigger Level to Maximum value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch1_Up_Th_Set(0xFF);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch1_Up_Th_Set(uint8 trig_val);

/** \brief Sets ADC1 Post-Processing Channel 2 Upper Trigger Level.
 *
 * \param trig_val Upper Trigger Level
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 2 Upper Trigger Level to Maximum value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch2_Up_Th_Set(0xFF);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch2_Up_Th_Set(uint8 trig_val);

/** \brief Sets ADC1 Post-Processing Channel 3 Upper Trigger Level.
 *
 * \param trig_val Upper Trigger Level
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 3 Upper Trigger Level to Maximum value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch3_Up_Th_Set(0xFF);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch3_Up_Th_Set(uint8 trig_val);

/** \brief Sets ADC1 Post-Processing Channel 4 Upper Trigger Level.
 *
 * \param trig_val Upper Trigger Level
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 4 Upper Trigger Level to Maximum value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch4_Up_Th_Set(0xFF);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch4_Up_Th_Set(uint8 trig_val);

/** \brief Sets ADC1 Post-Processing Channel 5 Upper Trigger Level.
 *
 * \param trig_val Upper Trigger Level
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 5 Upper Trigger Level to Maximum value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch5_Up_Th_Set(0xFF);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch5_Up_Th_Set(uint8 trig_val);

/** \brief Sets ADC1 Post-Processing Channel 6 Upper Trigger Level.
 *
 * \param trig_val Upper Trigger Level
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 6 Upper Trigger Level to Maximum value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch6_Up_Th_Set(0xFF);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch6_Up_Th_Set(uint8 trig_val);

/** \brief Sets ADC1 Post-Processing Channel 7 Upper Trigger Level.
 *
 * \param trig_val Upper Trigger Level
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 7 Upper Trigger Level to Maximum value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch7_Up_Th_Set(0xFF);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch7_Up_Th_Set(uint8 trig_val);

/** \brief Sets ADC1 Differential Unit 1 Upper Trigger Level.
 *
 * \param trig_val Upper Trigger Level
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Differential Unit 1 Upper Trigger Level to Maximum value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_DU1_Up_Th_Set(0xFF);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_DU1_Up_Th_Set(uint8 trig_val);

/** \brief Sets ADC1 Post-Processing Channel 0 Lower Hysteresis.
 *
 * \param hyst Lower Hysteresis
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 0 Lower Hysteresis to 8.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch0_Lo_Hyst_Set(ADC1_HYST_8);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch0_Lo_Hyst_Set(uint8 hyst);

/** \brief Sets ADC1 Post-Processing Channel 1 Lower Hysteresis.
 *
 * \param hyst Lower Hysteresis
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 1 Lower Hysteresis to 8.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch1_Lo_Hyst_Set(ADC1_HYST_8);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch1_Lo_Hyst_Set(uint8 hyst);

/** \brief Sets ADC1 Post-Processing Channel 2 Lower Hysteresis.
 *
 * \param hyst Lower Hysteresis
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 2 Lower Hysteresis to 8.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch2_Lo_Hyst_Set(ADC1_HYST_8);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch2_Lo_Hyst_Set(uint8 hyst);

/** \brief Sets ADC1 Post-Processing Channel 3 Lower Hysteresis.
 *
 * \param hyst Lower Hysteresis
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 3 Lower Hysteresis to 8.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch3_Lo_Hyst_Set(ADC1_HYST_8);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch3_Lo_Hyst_Set(uint8 hyst);

/** \brief Sets ADC1 Post-Processing Channel 4 Lower Hysteresis.
 *
 * \param hyst Lower Hysteresis
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 4 Lower Hysteresis to 8.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch4_Lo_Hyst_Set(ADC1_HYST_8);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch4_Lo_Hyst_Set(uint8 hyst);

/** \brief Sets ADC1 Post-Processing Channel 5 Lower Hysteresis.
 *
 * \param hyst Lower Hysteresis
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 5 Lower Hysteresis to 8.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch5_Lo_Hyst_Set(ADC1_HYST_8);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch5_Lo_Hyst_Set(uint8 hyst);

/** \brief Sets ADC1 Post-Processing Channel 6 Lower Hysteresis.
 *
 * \param hyst Lower Hysteresis
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 6 Lower Hysteresis to 8.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch6_Lo_Hyst_Set(ADC1_HYST_8);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch6_Lo_Hyst_Set(uint8 hyst);

/** \brief Sets ADC1 Post-Processing Channel 7 Lower Hysteresis.
 *
 * \param hyst Lower Hysteresis
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 7 Lower Hysteresis to 8.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch7_Lo_Hyst_Set(ADC1_HYST_8);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch7_Lo_Hyst_Set(uint8 hyst);

/** \brief Sets ADC1 Differential Unit 1 Lower Hysteresis.
 *
 * \param hyst Lower Hysteresis
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Differential Unit 1 Lower Hysteresis to 8.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_DU1_Lo_Hyst_Set(ADC1_HYST_8);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_DU1_Lo_Hyst_Set(uint8 hyst);

/** \brief Sets ADC1 Post-Processing Channel 0 Upper Hysteresis.
 *
 * \param hyst Upper Hysteresis
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 0 Upper Hysteresis to 4.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch0_Up_Hyst_Set(ADC1_HYST_4);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch0_Up_Hyst_Set(uint8 hyst);

/** \brief Sets ADC1 Post-Processing Channel 1 Upper Hysteresis.
 *
 * \param hyst Upper Hysteresis
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 1 Upper Hysteresis to 4.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch1_Up_Hyst_Set(ADC1_HYST_4);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch1_Up_Hyst_Set(uint8 hyst);

/** \brief Sets ADC1 Post-Processing Channel 2 Upper Hysteresis.
 *
 * \param hyst Upper Hysteresis
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 2 Upper Hysteresis to 4.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch2_Up_Hyst_Set(ADC1_HYST_4);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch2_Up_Hyst_Set(uint8 hyst);

/** \brief Sets ADC1 Post-Processing Channel 3 Upper Hysteresis.
 *
 * \param hyst Upper Hysteresis
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 3 Upper Hysteresis to 4.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch3_Up_Hyst_Set(ADC1_HYST_4);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch3_Up_Hyst_Set(uint8 hyst);

/** \brief Sets ADC1 Post-Processing Channel 4 Upper Hysteresis.
 *
 * \param hyst Upper Hysteresis
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 4 Upper Hysteresis to 4.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch4_Up_Hyst_Set(ADC1_HYST_4);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch4_Up_Hyst_Set(uint8 hyst);

/** \brief Sets ADC1 Post-Processing Channel 5 Upper Hysteresis.
 *
 * \param hyst Upper Hysteresis
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 5 Upper Hysteresis to 4.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch5_Up_Hyst_Set(ADC1_HYST_4);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch5_Up_Hyst_Set(uint8 hyst);

/** \brief Sets ADC1 Post-Processing Channel 6 Upper Hysteresis.
 *
 * \param hyst Upper Hysteresis
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 6 Upper Hysteresis to 4.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch6_Up_Hyst_Set(ADC1_HYST_4);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch6_Up_Hyst_Set(uint8 hyst);

/** \brief Sets ADC1 Post-Processing Channel 7 Upper Hysteresis.
 *
 * \param hyst Upper Hysteresis
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 7 Upper Hysteresis to 4.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch7_Up_Hyst_Set(ADC1_HYST_4);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch7_Up_Hyst_Set(uint8 hyst);

/** \brief Sets ADC1 Differential Unit 1 Upper Hysteresis.
 *
 * \param hyst Upper Hysteresis
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Differential Unit 1 Upper Hysteresis to 4.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_DU1_Up_Hyst_Set(ADC1_HYST_4);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_DU1_Up_Hyst_Set(uint8 hyst);

/** \brief Sets ADC1 Post-Processing Channel 0 Lower Timer Trigger.
 *
 * \param cnt Lower Timer Trigger
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 0 Lower Timer Trigger to 2 measurements.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch0_Lo_Cnt_Set(ADC1_CNT_2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch0_Lo_Cnt_Set(uint8 cnt);

/** \brief Sets ADC1 Post-Processing Channel 1 Lower Timer Trigger.
 *
 * \param cnt Lower Timer Trigger
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 1 Lower Timer Trigger to 2 measurements.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch1_Lo_Cnt_Set(ADC1_CNT_2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch1_Lo_Cnt_Set(uint8 cnt);

/** \brief Sets ADC1 Post-Processing Channel 2 Lower Timer Trigger.
 *
 * \param cnt Lower Timer Trigger
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 2 Lower Timer Trigger to 2 measurements.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch2_Lo_Cnt_Set(ADC1_CNT_2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch2_Lo_Cnt_Set(uint8 cnt);

/** \brief Sets ADC1 Post-Processing Channel 3 Lower Timer Trigger.
 *
 * \param cnt Lower Timer Trigger
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 3 Lower Timer Trigger to 2 measurements.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch3_Lo_Cnt_Set(ADC1_CNT_2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch3_Lo_Cnt_Set(uint8 cnt);

/** \brief Sets ADC1 Post-Processing Channel 4 Lower Timer Trigger.
 *
 * \param cnt Lower Timer Trigger
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 4 Lower Timer Trigger to 2 measurements.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch4_Lo_Cnt_Set(ADC1_CNT_2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch4_Lo_Cnt_Set(uint8 cnt);

/** \brief Sets ADC1 Post-Processing Channel 5 Lower Timer Trigger.
 *
 * \param cnt Lower Timer Trigger
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 5 Lower Timer Trigger to 2 measurements.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch5_Lo_Cnt_Set(ADC1_CNT_2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch5_Lo_Cnt_Set(uint8 cnt);

/** \brief Sets ADC1 Post-Processing Channel 6 Lower Timer Trigger.
 *
 * \param cnt Lower Timer Trigger
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 6 Lower Timer Trigger to 2 measurements.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch6_Lo_Cnt_Set(ADC1_CNT_2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch6_Lo_Cnt_Set(uint8 cnt);

/** \brief Sets ADC1 Post-Processing Channel 7 Lower Timer Trigger.
 *
 * \param cnt Lower Timer Trigger
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 7 Lower Timer Trigger to 2 measurements.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch7_Lo_Cnt_Set(ADC1_CNT_2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch7_Lo_Cnt_Set(uint8 cnt);

/** \brief Sets ADC1 Differential Unit 1 Lower Timer Trigger.
 *
 * \param cnt Lower Timer Trigger
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Differential Unit 1 Lower Timer Trigger to 2 measurements.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_DU1_Lo_Cnt_Set(ADC1_CNT_2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_DU1_Lo_Cnt_Set(uint8 cnt);

/** \brief Sets ADC1 Post-Processing Channel 0 Upper Timer Trigger.
 *
 * \param cnt Upper Timer Trigger
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 0 Upper Timer Trigger to 7 measurements.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch0_Up_Cnt_Set(ADC1_CNT_7);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch0_Up_Cnt_Set(uint8 cnt);

/** \brief Sets ADC1 Post-Processing Channel 1 Upper Timer Trigger.
 *
 * \param cnt Upper Timer Trigger
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 1 Upper Timer Trigger to 7 measurements.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch1_Up_Cnt_Set(ADC1_CNT_7);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch1_Up_Cnt_Set(uint8 cnt);

/** \brief Sets ADC1 Post-Processing Channel 2 Upper Timer Trigger.
 *
 * \param cnt Upper Timer Trigger
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 2 Upper Timer Trigger to 7 measurements.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch2_Up_Cnt_Set(ADC1_CNT_7);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch2_Up_Cnt_Set(uint8 cnt);

/** \brief Sets ADC1 Post-Processing Channel 3 Upper Timer Trigger.
 *
 * \param cnt Upper Timer Trigger
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 3 Upper Timer Trigger to 7 measurements.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch3_Up_Cnt_Set(ADC1_CNT_7);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch3_Up_Cnt_Set(uint8 cnt);

/** \brief Sets ADC1 Post-Processing Channel 4 Upper Timer Trigger.
 *
 * \param cnt Upper Timer Trigger
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 4 Upper Timer Trigger to 7 measurements.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch4_Up_Cnt_Set(ADC1_CNT_7);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch4_Up_Cnt_Set(uint8 cnt);

/** \brief Sets ADC1 Post-Processing Channel 5 Upper Timer Trigger.
 *
 * \param cnt Upper Timer Trigger
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 5 Upper Timer Trigger to 7 measurements.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch5_Up_Cnt_Set(ADC1_CNT_7);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch5_Up_Cnt_Set(uint8 cnt);

/** \brief Sets ADC1 Post-Processing Channel 6 Upper Timer Trigger.
 *
 * \param cnt Upper Timer Trigger
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 6 Upper Timer Trigger to 7 measurements.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch6_Up_Cnt_Set(ADC1_CNT_7);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch6_Up_Cnt_Set(uint8 cnt);

/** \brief Sets ADC1 Post-Processing Channel 7 Upper Timer Trigger.
 *
 * \param cnt Upper Timer Trigger
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Post-Processing Channel 7 Upper Timer Trigger to 7 measurements.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_PP_Ch7_Up_Cnt_Set(ADC1_CNT_7);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch7_Up_Cnt_Set(uint8 cnt);

/** \brief Sets ADC1 Differential Unit 1 Upper Timer Trigger.
 *
 * \param cnt Upper Timer Trigger
 *
 * \brief <b>Example</b><br>
 * \brief This example sets ADC1 Differential Unit 1 Upper Timer Trigger to 7 measurements.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_DU1_Up_Cnt_Set(ADC1_CNT_7);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_DU1_Up_Cnt_Set(uint8 cnt);

/** \brief Clears ADC1 IIR-Filter-Channel 0 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 0 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch0_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH0_IS == 1u)
 *   {
 *     ADC1_CH0_CALLBACK();
 *     ADC1_Ch0_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch0_Int_Clr(void);

/** \brief Clears ADC1 IIR-Filter-Channel 1 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 1 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch1_Int_En();
 *   if (ADC1->IRQS_1.bit.VS_IS == 1u)
 *   {
 *     ADC1_CH1_CALLBACK();
 *     ADC1_Ch1_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch1_Int_Clr(void);

/** \brief Clears ADC1 IIR-Filter-Channel 2 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 2 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch2_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH2_IS == 1u)
 *   {
 *     ADC1_CH2_CALLBACK();
 *     ADC1_Ch2_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch2_Int_Clr(void);

/** \brief Clears ADC1 IIR-Filter-Channel 3 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 3 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch3_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH3_IS == 1u)
 *   {
 *     ADC1_CH3_CALLBACK();
 *     ADC1_Ch3_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch3_Int_Clr(void);

/** \brief Clears ADC1 IIR-Filter-Channel 4 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 4 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch4_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH4_IS == 1u)
 *   {
 *     ADC1_CH4_CALLBACK();
 *     ADC1_Ch4_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch4_Int_Clr(void);

/** \brief Clears ADC1 IIR-Filter-Channel 5 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 5 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch5_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH5_IS == 1u)
 *   {
 *     ADC1_CH5_CALLBACK();
 *     ADC1_Ch5_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch5_Int_Clr(void);

/** \brief Clears ADC1 IIR-Filter-Channel 6 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 6 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch6_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH6_IS == 1u)
 *   {
 *     ADC1_CH6_CALLBACK();
 *     ADC1_Ch6_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch6_Int_Clr(void);

/** \brief Clears ADC1 IIR-Filter-Channel 7 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 7 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch7_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH7_IS == 1u)
 *   {
 *     ADC1_CH7_CALLBACK();
 *     ADC1_Ch7_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch7_Int_Clr(void);

/** \brief Clears ADC1 IIR-Filter-Channel 8 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 8 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch8_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH8_IS == 1u)
 *   {
 *     ADC1_CH8_CALLBACK();
 *     ADC1_Ch8_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch8_Int_Clr(void);

/** \brief Clears ADC1 IIR-Filter-Channel 9 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 9 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch9_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH9_IS == 1u)
 *   {
 *     ADC1_CH9_CALLBACK();
 *     ADC1_Ch9_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch9_Int_Clr(void);

/** \brief Clears ADC1 IIR-Filter-Channel 12 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 12 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch12_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH12_IS == 1u)
 *   {
 *     ADC1_CH12_CALLBACK();
 *     ADC1_Ch12_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch12_Int_Clr(void);

/** \brief Clears ADC1 IIR-Filter-Channel 13 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 13 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch13_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH13_IS == 1u)
 *   {
 *     ADC1_CH13_CALLBACK();
 *     ADC1_Ch13_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch13_Int_Clr(void);

/** \brief Clears Exceptional Interrupt Measurement (EIM) flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Exceptional Interrupt Measurement (EIM).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_EIM_En();
 *   ADC1_EIM_Int_En();
 *   if (ADC1->IRQS_1.bit.EIM_IS == 1u)
 *   {
 *     ADC1_EIM_CALLBACK();
 *     ADC1_EIM_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_EIM_Int_Clr(void);

/** \brief Clears Exceptional Sequence Measurement (ESM) flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Exceptional Sequence Measurement (ESM).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_ESM_Int_En();
 *   if (ADC1->IRQS_1.bit.ESM_IS == 1u)
 *   {
 *     ADC1_ESM_CALLBACK();
 *     ADC1_ESM_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_ESM_Int_Clr(void);

/** \brief Clears Differential Unit 1 upper Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Differential Unit 1 upper Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_DU1UP_Int_En();
 *   if (ADC1->IRQS_1.bit.DU1UP_IS == 1u)
 *   {
 *     ADC1_DU1UP_CALLBACK();
 *     ADC1_DU1UP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_DU1UP_Int_Clr(void);

/** \brief Clears Differential Unit 1 lower Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Differential Unit 1 lower Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_DU1LO_Int_En();
 *   if (ADC1->IRQS_1.bit.DU1LO_IS == 1u)
 *   {
 *     ADC1_DU1LO_CALLBACK();
 *     ADC1_DU1LO_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_DU1LO_Int_Clr(void);

/** \brief Enables ADC1 IIR-Filter-Channel 0 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 0 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch0_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH0_IS == 1u)
 *   {
 *     ADC1_CH0_CALLBACK();
 *     ADC1_Ch0_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch0_Int_En(void);

/** \brief Disables ADC1 IIR-Filter-Channel 0 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 0 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch0_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH0_IS == 1u)
 *   {
 *     ADC1_CH0_CALLBACK();
 *     ADC1_Ch0_Int_Clr();
 *   }
 *   ADC1_Ch0_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch0_Int_Dis(void);

/** \brief Enables ADC1 IIR-Filter-Channel 1 Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 1 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch1_Int_En();
 *   if (ADC1->IRQS_1.bit.VS_IS == 1u)
 *   {
 *     ADC1_CH1_CALLBACK();
 *     ADC1_Ch1_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch1_Int_En(void);

/** \brief Disables ADC1 IIR-Filter-Channel 1 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 1 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch1_Int_En();
 *   if (ADC1->IRQS_1.bit.VS_IS == 1u)
 *   {
 *     ADC1_CH1_CALLBACK();
 *     ADC1_Ch1_Int_Clr();
 *   }
 *   ADC1_Ch1_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch1_Int_Dis(void);

/** \brief Enables ADC1 IIR-Filter-Channel 2 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 2 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch2_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH2_IS == 1u)
 *   {
 *     ADC1_CH2_CALLBACK();
 *     ADC1_Ch2_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch2_Int_En(void);

/** \brief Disables ADC1 IIR-Filter-Channel 2 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 2 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch2_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH2_IS == 1u)
 *   {
 *     ADC1_CH2_CALLBACK();
 *     ADC1_Ch2_Int_Clr();
 *   }
 *   ADC1_Ch2_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch2_Int_Dis(void);

/** \brief Enables ADC1 IIR-Filter-Channel 3 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 3 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch3_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH3_IS == 1u)
 *   {
 *     ADC1_CH3_CALLBACK();
 *     ADC1_Ch3_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch3_Int_En(void);

/** \brief Disables ADC1 IIR-Filter-Channel 3 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 3 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch3_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH3_IS == 1u)
 *   {
 *     ADC1_CH3_CALLBACK();
 *     ADC1_Ch3_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch3_Int_Dis(void);

/** \brief Enables ADC1 IIR-Filter-Channel 4 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 4 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch4_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH4_IS == 1u)
 *   {
 *     ADC1_CH4_CALLBACK();
 *     ADC1_Ch4_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch4_Int_En(void);

/** \brief Disables ADC1 IIR-Filter-Channel 4 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 4 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch4_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH4_IS == 1u)
 *   {
 *     ADC1_CH4_CALLBACK();
 *     ADC1_Ch4_Int_Clr();
 *   }
 *   ADC1_Ch4_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch4_Int_Dis(void);

/** \brief Enables ADC1 IIR-Filter-Channel 5 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 5 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch5_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH5_IS == 1u)
 *   {
 *     ADC1_CH5_CALLBACK();
 *     ADC1_Ch5_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch5_Int_En(void);

/** \brief Disables ADC1 IIR-Filter-Channel 5 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 5 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch5_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH5_IS == 1u)
 *   {
 *     ADC1_CH5_CALLBACK();
 *     ADC1_Ch5_Int_Clr();
 *   }
 *   ADC1_Ch5_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch5_Int_Dis(void);

/** \brief Enables ADC1 IIR-Filter-Channel 6 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 6 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch6_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH6_IS == 1u)
 *   {
 *     ADC1_CH6_CALLBACK();
 *     ADC1_Ch6_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch6_Int_En(void);

/** \brief Disables ADC1 IIR-Filter-Channel 6 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 6 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch6_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH6_IS == 1u)
 *   {
 *     ADC1_CH6_CALLBACK();
 *     ADC1_Ch6_Int_Clr();
 *   }
 *   ADC1_Ch6_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch6_Int_Dis(void);

/** \brief Enables ADC1 IIR-Filter-Channel 7 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 7 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch7_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH7_IS == 1u)
 *   {
 *     ADC1_CH7_CALLBACK();
 *     ADC1_Ch7_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch7_Int_En(void);

/** \brief Disables ADC1 IIR-Filter-Channel 7 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 7 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch7_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH7_IS == 1u)
 *   {
 *     ADC1_CH7_CALLBACK();
 *     ADC1_Ch7_Int_Clr();
 *   }
 *   ADC1_Ch7_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch7_Int_Dis(void);

/** \brief Enables ADC1 IIR-Filter-Channel 8 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 8 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch8_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH8_IS == 1u)
 *   {
 *     ADC1_CH8_CALLBACK();
 *     ADC1_Ch8_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch8_Int_En(void);

/** \brief Disables ADC1 IIR-Filter-Channel 8 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 8 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch8_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH8_IS == 1u)
 *   {
 *     ADC1_CH8_CALLBACK();
 *     ADC1_Ch8_Int_Clr();
 *   }
 *   ADC1_Ch8_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch8_Int_Dis(void);

/** \brief Enables ADC1 IIR-Filter-Channel 9 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 9 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch9_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH9_IS == 1u)
 *   {
 *     ADC1_CH9_CALLBACK();
 *     ADC1_Ch9_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch9_Int_En(void);

/** \brief Disables ADC1 IIR-Filter-Channel 9 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 9 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch9_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH9_IS == 1u)
 *   {
 *     ADC1_CH9_CALLBACK();
 *     ADC1_Ch9_Int_Clr();
 *   }
 *   ADC1_Ch9_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch9_Int_Dis(void);

/** \brief Enables ADC1 IIR-Filter-Channel 12 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 12 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch12_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH12_IS == 1u)
 *   {
 *     ADC1_CH12_CALLBACK();
 *     ADC1_Ch12_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch12_Int_En(void);

/** \brief Disables ADC1 IIR-Filter-Channel 12 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 12 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch12_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH12_IS == 1u)
 *   {
 *     ADC1_CH12_CALLBACK();
 *     ADC1_Ch12_Int_Clr();
 *   }
 *   ADC1_Ch12_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch12_Int_Dis(void);

/** \brief Enables ADC1 IIR-Filter-Channel 13 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 13 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch13_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH13_IS == 1u)
 *   {
 *     ADC1_CH13_CALLBACK();
 *     ADC1_Ch13_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch13_Int_En(void);

/** \brief Disables ADC1 IIR-Filter-Channel 13 Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 IIR-Filter-Channel 13 Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Ch13_Int_En();
 *   if (ADC1->IRQS_1.bit.IIR_CH13_IS == 1u)
 *   {
 *     ADC1_CH13_CALLBACK();
 *     ADC1_Ch13_Int_Clr();
 *   }
 *   ADC1_Ch13_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Ch13_Int_Dis(void);

/** \brief Enables Exceptional Interrupt Measurement (EIM).
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Exceptional Interrupt Measurement (EIM).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_EIM_En();
 *   ADC1_EIM_Int_En();
 *   if (ADC1->IRQS_1.bit.EIM_IS == 1u)
 *   {
 *     ADC1_EIM_CALLBACK();
 *     ADC1_EIM_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_EIM_Int_En(void);

/** \brief Disables Exceptional Interrupt Measurement (EIM).
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Exceptional Interrupt Measurement (EIM).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_EIM_En();
 *   ADC1_EIM_Int_En();
 *   if (ADC1->IRQS_1.bit.EIM_IS == 1u)
 *   {
 *     ADC1_EIM_CALLBACK();
 *     ADC1_EIM_Int_Clr();
 *   }
 *   ADC1_EIM_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_EIM_Int_Dis(void);

/** \brief Enables Exceptional Sequence Measurement (ESM).
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Exceptional Sequence Measurement (ESM).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_ESM_Int_En();
 *   if (ADC1->IRQS_1.bit.ESM_IS == 1u)
 *   {
 *     ADC1_ESM_CALLBACK();
 *     ADC1_ESM_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_ESM_Int_En(void);

/** \brief Disables Exceptional Sequence Measurement (ESM).
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Exceptional Sequence Measurement (ESM).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_ESM_Int_En();
 *   if (ADC1->IRQS_1.bit.ESM_IS == 1u)
 *   {
 *     ADC1_ESM_CALLBACK();
 *     ADC1_ESM_Int_Clr();
 *   }
 *   ADC1_ESM_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_ESM_Int_Dis(void);

/** \brief Enables Differential Unit 1 upper Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Differential Unit 1 upper Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_DU1UP_Int_En();
 *   if (ADC1->IRQS_1.bit.DU1UP_IS == 1u)
 *   {
 *     ADC1_DU1UP_CALLBACK();
 *     ADC1_DU1UP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_DU1UP_Int_En(void);

/** \brief Disables Differential Unit 1 upper Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Differential Unit 1 upper Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_DU1UP_Int_En();
 *   if (ADC1->IRQS_1.bit.DU1UP_IS == 1u)
 *   {
 *     ADC1_DU1UP_CALLBACK();
 *     ADC1_DU1UP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_DU1UP_Int_Dis(void);

/** \brief Enables Differential Unit 1 lower Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Differential Unit 1 lower Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_DU1LO_Int_En();
 *   if (ADC1->IRQS_1.bit.DU1LO_IS == 1u)
 *   {
 *     ADC1_DU1LO_CALLBACK();
 *     ADC1_DU1LO_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_DU1LO_Int_En(void);

/** \brief Disables Differential Unit 1 lower Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Differential Unit 1 lower Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_DU1LO_Int_En();
 *   if (ADC1->IRQS_1.bit.DU1LO_IS == 1u)
 *   {
 *     ADC1_DU1LO_CALLBACK();
 *     ADC1_DU1LO_Int_Clr();
 *   }
 *   ADC1_DU1LO_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_DU1LO_Int_Dis(void);

/** \brief Clears ADC1 Post-Processing-Channel 0 Upper Threshold Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 0 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch0_UP_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH0_UP_IS == 1u)
 *   {
 *     ADC1_PP_CH0_UP_CALLBACK();
 *     ADC1_PP_Ch0_UP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch0_UP_Int_Clr(void);

/** \brief Clears ADC1 Post-Processing-Channel 0 Lower Threshold Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 0 Lower Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch0_LO_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH0_LO_IS == 1u)
 *   {
 *     ADC1_PP_CH0_LO_CALLBACK();
 *     ADC1_PP_Ch0_LO_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch0_LO_Int_Clr(void);

/** \brief Clears ADC1 Post-Processing-Channel 1 Upper Threshold Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 1 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch1_UP_Int_En();
 *   if (ADC1->IRQS_2.bit.VS_UP_IS == 1u)
 *   {
 *     ADC1_PP_CH1_UP_CALLBACK();
 *     ADC1_PP_Ch1_UP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch1_UP_Int_Clr(void);

/** \brief Clears ADC1 Post-Processing-Channel 1 Lower Threshold Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 1 Lower Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch1_LO_Int_En();
 *   if (ADC1->IRQS_2.bit.VS_LO_IS == 1u)
 *   {
 *     ADC1_PP_CH1_LO_CALLBACK();
 *     ADC1_PP_Ch1_LO_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch1_LO_Int_Clr(void);

/** \brief Clears ADC1 Post-Processing-Channel 2 Upper Threshold Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 2 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch2_UP_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH2_UP_IS == 1u)
 *   {
 *     ADC1_PP_CH2_UP_CALLBACK();
 *     ADC1_PP_Ch2_UP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch2_UP_Int_Clr(void);

/** \brief Clears ADC1 Post-Processing-Channel 2 Lower Threshold Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 2 Lower Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch2_LO_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH2_LO_IS == 1u)
 *   {
 *     ADC1_PP_CH2_LO_CALLBACK();
 *     ADC1_PP_Ch2_LO_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch2_LO_Int_Clr(void);

/** \brief Clears ADC1 Post-Processing-Channel 3 Upper Threshold Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 3 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch3_UP_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH3_UP_IS == 1u)
 *   {
 *     ADC1_PP_CH3_UP_CALLBACK();
 *     ADC1_PP_Ch3_UP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch3_UP_Int_Clr(void);

/** \brief Clears ADC1 Post-Processing-Channel 3 Lower Threshold Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 3 Lower Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch3_LO_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH3_LO_IS == 1u)
 *   {
 *     ADC1_PP_CH3_LO_CALLBACK();
 *     ADC1_PP_Ch3_LO_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch3_LO_Int_Clr(void);

/** \brief Clears ADC1 Post-Processing-Channel 4 Upper Threshold Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 4 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch4_UP_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH4_UP_IS == 1u)
 *   {
 *     ADC1_PP_CH4_UP_CALLBACK();
 *     ADC1_PP_Ch4_UP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch4_UP_Int_Clr(void);

/** \brief Clears ADC1 Post-Processing-Channel 4 Lower Threshold Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 4 Lower Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch4_LO_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH4_LO_IS == 1u)
 *   {
 *     ADC1_PP_CH4_LO_CALLBACK();
 *     ADC1_PP_Ch4_LO_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch4_LO_Int_Clr(void);

/** \brief Clears ADC1 Post-Processing-Channel 5 Upper Threshold Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 5 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch5_UP_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH5_UP_IS == 1u)
 *   {
 *     ADC1_PP_CH5_UP_CALLBACK();
 *     ADC1_PP_Ch5_UP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch5_UP_Int_Clr(void);

/** \brief Clears ADC1 Post-Processing-Channel 5 Lower Threshold Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 5 Lower Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch5_LO_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH5_LO_IS == 1u)
 *   {
 *     ADC1_PP_CH5_LO_CALLBACK();
 *     ADC1_PP_Ch5_LO_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch5_LO_Int_Clr(void);

/** \brief Clears ADC1 Post-Processing-Channel 6 Upper Threshold Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 6 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch6_UP_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH6_UP_IS == 1u)
 *   {
 *     ADC1_PP_CH6_UP_CALLBACK();
 *     ADC1_PP_Ch6_UP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch6_UP_Int_Clr(void);

/** \brief Clears ADC1 Post-Processing-Channel 6 Lower Threshold Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 6 Lower Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch6_LO_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH6_LO_IS == 1u)
 *   {
 *     ADC1_PP_CH6_LO_CALLBACK();
 *     ADC1_PP_Ch6_LO_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch6_LO_Int_Clr(void);

/** \brief Clears ADC1 Post-Processing-Channel 7 Upper Threshold Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 7 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch7_UP_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH7_UP_IS == 1u)
 *   {
 *     ADC1_PP_CH7_UP_CALLBACK();
 *     ADC1_PP_Ch7_UP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch7_UP_Int_Clr(void);

/** \brief Clears ADC1 Post-Processing-Channel 7 Lower Threshold Interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 7 Lower Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch7_LO_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH7_LO_IS == 1u)
 *   {
 *     ADC1_PP_CH7_LO_CALLBACK();
 *     ADC1_PP_Ch7_LO_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch7_LO_Int_Clr(void);

/** \brief Enables ADC1 Post-Processing-Channel 0 Upper Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 0 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch0_UP_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH0_UP_IS == 1u)
 *   {
 *     ADC1_PP_CH0_UP_CALLBACK();
 *     ADC1_PP_Ch0_UP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch0_UP_Int_En(void);

/** \brief Disables ADC1 Post-Processing-Channel 0 Upper Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 0 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch0_UP_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH0_UP_IS == 1u)
 *   {
 *     ADC1_PP_CH0_UP_CALLBACK();
 *     ADC1_PP_Ch0_UP_Int_Clr();
 *   }
 *   ADC1_PP_Ch0_UP_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch0_UP_Int_Dis(void);

/** \brief Enables ADC1 Post-Processing-Channel 0 Lower Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 0 Lower Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch0_LO_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH0_LO_IS == 1u)
 *   {
 *     ADC1_PP_CH0_LO_CALLBACK();
 *     ADC1_PP_Ch0_LO_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch0_LO_Int_En(void);

/** \brief Disables ADC1 Post-Processing-Channel 0 Lower Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 0 Lower Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch0_LO_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH0_LO_IS == 1u)
 *   {
 *     ADC1_PP_CH0_LO_CALLBACK();
 *     ADC1_PP_Ch0_LO_Int_Clr();
 *   }
 *   ADC1_PP_Ch0_LO_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch0_LO_Int_Dis(void);

/** \brief Enables ADC1 Post-Processing-Channel 1 Upper Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 1 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch1_UP_Int_En();
 *   if (ADC1->IRQS_2.bit.VS_UP_IS == 1u)
 *   {
 *     ADC1_PP_CH1_UP_CALLBACK();
 *     ADC1_PP_Ch1_UP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch1_UP_Int_En(void);

/** \brief Disables ADC1 Post-Processing-Channel 1 Upper Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 1 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch1_UP_Int_En();
 *   if (ADC1->IRQS_2.bit.VS_UP_IS == 1u)
 *   {
 *     ADC1_PP_CH1_UP_CALLBACK();
 *     ADC1_PP_Ch1_UP_Int_Clr();
 *   }
 *   ADC1_PP_Ch1_UP_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch1_UP_Int_Dis(void);

/** \brief Enables ADC1 Post-Processing-Channel 1 Lower Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 1 Lower Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch1_LO_Int_En();
 *   if (ADC1->IRQS_2.bit.VS_LO_IS == 1u)
 *   {
 *     ADC1_PP_CH1_LO_CALLBACK();
 *     ADC1_PP_Ch1_LO_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch1_LO_Int_En(void);

/** \brief Disables ADC1 Post-Processing-Channel 1 Lower Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 1 Lower Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch1_LO_Int_En();
 *   if (ADC1->IRQS_2.bit.VS_LO_IS == 1u)
 *   {
 *     ADC1_PP_CH1_LO_CALLBACK();
 *     ADC1_PP_Ch1_LO_Int_Clr();
 *   }
 *   ADC1_PP_Ch1_LO_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch1_LO_Int_Dis(void);

/** \brief Enables ADC1 Post-Processing-Channel 2 Upper Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 2 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch2_UP_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH2_UP_IS == 1u)
 *   {
 *     ADC1_PP_CH2_UP_CALLBACK();
 *     ADC1_PP_Ch2_UP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch2_UP_Int_En(void);

/** \brief Disables ADC1 Post-Processing-Channel 2 Upper Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 2 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch2_UP_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH2_UP_IS == 1u)
 *   {
 *     ADC1_PP_CH2_UP_CALLBACK();
 *     ADC1_PP_Ch2_UP_Int_Clr();
 *   }
 *   ADC1_PP_Ch2_UP_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch2_UP_Int_Dis(void);

/** \brief Enables ADC1 Post-Processing-Channel 2 Lower Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 2 Lower Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch2_LO_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH2_LO_IS == 1u)
 *   {
 *     ADC1_PP_CH2_LO_CALLBACK();
 *     ADC1_PP_Ch2_LO_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch2_LO_Int_En(void);

/** \brief Disables ADC1 Post-Processing-Channel 2 Lower Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 2 Lower Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch2_LO_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH2_LO_IS == 1u)
 *   {
 *     ADC1_PP_CH2_LO_CALLBACK();
 *     ADC1_PP_Ch2_LO_Int_Clr();
 *   }
 *   ADC1_PP_Ch2_LO_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch2_LO_Int_Dis(void);

/** \brief Enables ADC1 Post-Processing-Channel 3 Upper Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 3 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch3_UP_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH3_UP_IS == 1u)
 *   {
 *     ADC1_PP_CH3_UP_CALLBACK();
 *     ADC1_PP_Ch3_UP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch3_UP_Int_En(void);

/** \brief Disables ADC1 Post-Processing-Channel 3 Upper Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 3 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch3_UP_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH3_UP_IS == 1u)
 *   {
 *     ADC1_PP_CH3_UP_CALLBACK();
 *     ADC1_PP_Ch3_UP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch3_UP_Int_Dis(void);

/** \brief Enables ADC1 Post-Processing-Channel 3 Lower Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 3 Lower Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch3_LO_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH3_LO_IS == 1u)
 *   {
 *     ADC1_PP_CH3_LO_CALLBACK();
 *     ADC1_PP_Ch3_LO_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch3_LO_Int_En(void);

/** \brief Disables ADC1 Post-Processing-Channel 3 Lower Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 3 Lower Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch3_LO_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH3_LO_IS == 1u)
 *   {
 *     ADC1_PP_CH3_LO_CALLBACK();
 *     ADC1_PP_Ch3_LO_Int_Clr();
 *   }
 *   ADC1_PP_Ch3_LO_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch3_LO_Int_Dis(void);

/** \brief Enables ADC1 Post-Processing-Channel 4 Upper Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 4 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch4_UP_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH4_UP_IS == 1u)
 *   {
 *     ADC1_PP_CH4_UP_CALLBACK();
 *     ADC1_PP_Ch4_UP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch4_UP_Int_En(void);

/** \brief Disables ADC1 Post-Processing-Channel 4 Upper Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 4 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch4_UP_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH4_UP_IS == 1u)
 *   {
 *     ADC1_PP_CH4_UP_CALLBACK();
 *     ADC1_PP_Ch4_UP_Int_Clr();
 *   }
 *   ADC1_PP_Ch4_UP_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch4_UP_Int_Dis(void);

/** \brief Enables ADC1 Post-Processing-Channel 4 Lower Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 4 Lower Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch4_LO_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH4_LO_IS == 1u)
 *   {
 *     ADC1_PP_CH4_LO_CALLBACK();
 *     ADC1_PP_Ch4_LO_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch4_LO_Int_En(void);

/** \brief Disables ADC1 Post-Processing-Channel 4 Lower Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 4 Lower Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch4_LO_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH4_LO_IS == 1u)
 *   {
 *     ADC1_PP_CH4_LO_CALLBACK();
 *     ADC1_PP_Ch4_LO_Int_Clr();
 *   }
 *   ADC1_PP_Ch4_LO_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch4_LO_Int_Dis(void);

/** \brief Enables ADC1 Post-Processing-Channel 5 Upper Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 5 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch5_UP_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH5_UP_IS == 1u)
 *   {
 *     ADC1_PP_CH5_UP_CALLBACK();
 *     ADC1_PP_Ch5_UP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch5_UP_Int_En(void);

/** \brief Disables ADC1 Post-Processing-Channel 5 Upper Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 5 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch5_UP_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH5_UP_IS == 1u)
 *   {
 *     ADC1_PP_CH5_UP_CALLBACK();
 *     ADC1_PP_Ch5_UP_Int_Clr();
 *   }
 *   ADC1_PP_Ch5_UP_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch5_UP_Int_Dis(void);

/** \brief Enables ADC1 Post-Processing-Channel 5 Lower Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 5 Lower Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch5_LO_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH5_LO_IS == 1u)
 *   {
 *     ADC1_PP_CH5_LO_CALLBACK();
 *     ADC1_PP_Ch5_LO_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch5_LO_Int_En(void);

/** \brief Disables ADC1 Post-Processing-Channel 5 Lower Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 5 Lower Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch5_LO_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH5_LO_IS == 1u)
 *   {
 *     ADC1_PP_CH5_LO_CALLBACK();
 *     ADC1_PP_Ch5_LO_Int_Clr();
 *   }
 *   ADC1_PP_Ch5_LO_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch5_LO_Int_Dis(void);

/** \brief Enables ADC1 Post-Processing-Channel 6 Upper Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 6 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch6_UP_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH6_UP_IS == 1u)
 *   {
 *     ADC1_PP_CH6_UP_CALLBACK();
 *     ADC1_PP_Ch6_UP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch6_UP_Int_En(void);

/** \brief Disables ADC1 Post-Processing-Channel 6 Upper Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 6 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch6_UP_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH6_UP_IS == 1u)
 *   {
 *     ADC1_PP_CH6_UP_CALLBACK();
 *     ADC1_PP_Ch6_UP_Int_Clr();
 *   }
 *   ADC1_PP_Ch6_UP_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch6_UP_Int_Dis(void);

/** \brief Enables ADC1 Post-Processing-Channel 6 Lower Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 6 Lower Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch6_LO_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH6_LO_IS == 1u)
 *   {
 *     ADC1_PP_CH6_LO_CALLBACK();
 *     ADC1_PP_Ch6_LO_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch6_LO_Int_En(void);

/** \brief Disables ADC1 Post-Processing-Channel 6 Lower Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 6 Lower Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch6_LO_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH6_LO_IS == 1u)
 *   {
 *     ADC1_PP_CH6_LO_CALLBACK();
 *     ADC1_PP_Ch6_LO_Int_Clr();
 *   }
 *   ADC1_PP_Ch6_LO_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch6_LO_Int_Dis(void);

/** \brief Enables ADC1 Post-Processing-Channel 7 Upper Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 7 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch7_UP_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH7_UP_IS == 1u)
 *   {
 *     ADC1_PP_CH7_UP_CALLBACK();
 *     ADC1_PP_Ch7_UP_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch7_UP_Int_En(void);

/** \brief Disables ADC1 Post-Processing-Channel 7 Upper Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 7 Upper Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch7_UP_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH7_UP_IS == 1u)
 *   {
 *     ADC1_PP_CH7_UP_CALLBACK();
 *     ADC1_PP_Ch7_UP_Int_Clr();
 *   }
 *   ADC1_PP_Ch7_UP_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch7_UP_Int_Dis(void);

/** \brief Enables ADC1 Post-Processing-Channel 7 Lower Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 7 Lower Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch7_LO_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH7_LO_IS == 1u)
 *   {
 *     ADC1_PP_CH7_LO_CALLBACK();
 *     ADC1_PP_Ch7_LO_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch7_LO_Int_En(void);

/** \brief Disables ADC1 Post-Processing-Channel 7 Lower Threshold Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the ADC1 Post-Processing-Channel 7 Lower Threshold Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_PP_Ch7_LO_Int_En();
 *   if (ADC1->IRQS_2.bit.PP_CH7_LO_IS == 1u)
 *   {
 *     ADC1_PP_CH7_LO_CALLBACK();
 *     ADC1_PP_Ch7_LO_Int_Clr();
 *   }
 *   ADC1_PP_Ch7_LO_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_PP_Ch7_LO_Int_Dis(void);

/** \brief Sets the Value of the Offset Calibration.
 *
 * \param value Offset Calibration Value
 *
 * \brief <b>Example</b><br>
 * \brief This example sets the Value of the Offset Calibration to Maximum Value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Offset_Calib_Set(0x1F);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Offset_Calib_Set(uint8 value);

/** \brief Sets the Value of the Offset Shift.
 *
 * \param value Offset Shift Value
 *
 * \brief <b>Example</b><br>
 * \brief This example sets the Value of the Offset Shift to Maximum Value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Offset_Shift_Set(0x7);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Offset_Shift_Set(uint8 value);

/** \brief Enables Sigma Delta Feedback Loop.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Sigma Delta Feedback Loop.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Power_On();
 *   ADC1_Sig_Del_feed_Loop_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Sig_Del_feed_Loop_En(void);

/** \brief Sets Soc Clock Jitter.
 *
 * \param clk Soc Clock Jitter
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Soc Clock Jitter to 8n.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC1_Power_On();
 *   ADC1_Soc_Clk_Jitter_Set(ADC1_Soc_Clk_Jitter_8);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_Soc_Clk_Jitter_Set(uint8 clk);

/** \brief Sets ADC1 EIM channel.
 *
 * \param channel channel number to be converted
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode, and programs channel 2 (MON1) and reads the result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 adc_result;
 *
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_SetEIMChannel( ADC1_CH2 );
 *
 *     while (ADC1->FILT_OUTEIM.bit.VF_EIM == 0u)
 *     {
 *     }
 *
 *     adc_result = ADC1_EIM_Result_Get();
 *
 *     return(adc_result);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_SetEIMChannel(uint8 channel);

/** \brief Selects a channel for the software conversion.
 *
 * \param channel channel which should be measured
 *
 * \brief <b>Example</b><br>
 * \brief This example starts an ADC1 conversion on channel 6 - P2.0.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_SetSwMode_Channel(ADC1_P20);
 *     ADC1_SOS_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_SetSwMode_Channel(uint8 channel);

/** \brief Starts ADC1 Software Mode conversion
 *
 * \param channel ADC1 channel number
 *
 * \brief This example enables ADC and starts Software Mode conversion for channel 6.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_SetSosSwMode(ADC1_P20);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_SetSosSwMode(uint8 channel);

/** \brief Gets ADC1 Software Mode End Of Conversion Status
 *
 * \retval true conversion done
 * \retval false conversion ongoing
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode, starts a measurement and waits for it to be finished.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Software_Mode_Sel();
 *     ADC1_Sequencer_Mode_Sel( ADC1_MON1 );
 *     ADC1_SOS_Set();
 *
 *     while ( ADC1_GetEocSwMode() != true ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE bool ADC1_GetEocSwMode(void);

/** \brief Selects ADC1 EIM Trigger
 *
 * \param trigsel Trigger select, see \link TADC1_TRIGG_SEL \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and sets EIM Trigger to Timer2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_EIM_Trigger_Select(ADC1_Trigg_Timer2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_EIM_Trigger_Select(TADC1_TRIGG_SEL trigsel);

/** \brief Sets ADC1 EIM Repeat Counter
 *
 * \param repcnt repeat counter for EIM measurement, see \link TADC1_EIM_REP_CNT \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and sets EIM Repeat Counter to 4 Measures.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_EIM_Repeat_Counter_Set(ADC1_4_Meas);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_EIM_Repeat_Counter_Set(TADC1_EIM_REP_CNT repcnt);

/** \brief Sets ADC1 ESM Trigger Selection
 *
 * \param trigsel Trigger select, see \link TADC1_TRIGG_SEL \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and sets ESM Trigger Selection to Timer2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_ESM_Trigger_Select(ADC1_Trigg_Timer2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE void ADC1_ESM_Trigger_Select(TADC1_TRIGG_SEL trigsel);

/** \brief Checks EndOfConversion ready (Software Mode)
 *
 * \retval true conversion done
 * \retval false conversion ongoing
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Software Mode and checks if EndOfConversion is ready.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Software_Mode_Sel();
 *     ADC1_Sequencer_Mode_Sel( ADC1_MON1 );
 *     ADC1_SOS_Set();
 *
 *     while ( ADC1_isEndOfConversion() != true ) {}
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE bool ADC1_isEndOfConversion(void);

/** \brief Checks Exceptional Interrupt Mode active
 *
 * \retval true EIM mode is active
 * \retval false EIM mode is not active
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode and checks if the Exceptional Interrupt Measurement (EIM) is active.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_EIM_Channel_Set( ADC1_CH2 );
 *
 *     while (ADC1_isEIMactive() == false)
 *     {
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE bool ADC1_isEIMactive(void);

/** \brief Checks Exceptional Sequencer Mode active
 *
 * \retval true ESM mode is active
 * \retval false ESM mode is not active
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 and switches to Sequencer Mode and checks if Exceptional Sequencer Measurement (ESM) is ready.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Sequencer_Mode_Sel();
 *     ADC1_ESM_Channel_Set( ADC1_MASK_MON1 );
 *
 *     while (ADC1_isESMactive() == false)
 *     {
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC1_api
 */
INLINE bool ADC1_isESMactive(void);


/*******************************************************************************
**                         Inline Function Definitions                        **
*******************************************************************************/
INLINE void ADC1_Power_On()
{
  Field_Mod32(&ADC1->CTRL_STS.reg, (uint8)ADC1_CTRL_STS_PD_N_Pos, ADC1_CTRL_STS_PD_N_Msk, 1u);
}

INLINE void ADC1_Power_Off()
{
  Field_Mod32(&ADC1->CTRL_STS.reg, (uint8)ADC1_CTRL_STS_PD_N_Pos, ADC1_CTRL_STS_PD_N_Msk, 0u);
}

INLINE void ADC1_SOOC_Set()
{
  Field_Mod32(&ADC1->CTRL_STS.reg, (uint8)ADC1_CTRL_STS_SOOC_Pos, ADC1_CTRL_STS_SOOC_Msk, 1u);
}

INLINE void ADC1_SOS_Set()
{
  Field_Mod32(&ADC1->CTRL_STS.reg, (uint8)ADC1_CTRL_STS_SOS_Pos, ADC1_CTRL_STS_SOS_Msk, 1u);
}

INLINE void ADC1_SW_Channel_Sel(uint8 a)
{
  Field_Mod32(&ADC1->CTRL_STS.reg, (uint8)ADC1_CTRL_STS_SW_CH_SEL_Pos, ADC1_CTRL_STS_SW_CH_SEL_Msk, a);
}

INLINE uint8 ADC1_SW_Channel_Read()
{
  return(u8_Field_Rd32(&ADC1->CTRL_STS.reg, (uint8)ADC1_CTRL_STS_SW_CH_SEL_Pos, ADC1_CTRL_STS_SW_CH_SEL_Msk));
}

INLINE void ADC1_STRTUP_En()
{
  Field_Mod32(&ADC1->CTRL_STS.reg, (uint8)ADC1_CTRL_STS_STRTUP_DIS_Pos, ADC1_CTRL_STS_STRTUP_DIS_Msk, 0u);
}

INLINE void ADC1_STRTUP_Dis()
{
  Field_Mod32(&ADC1->CTRL_STS.reg, (uint8)ADC1_CTRL_STS_STRTUP_DIS_Pos, ADC1_CTRL_STS_STRTUP_DIS_Msk, 1u);
}

INLINE void ADC1_Sequencer_Mode_Sel()
{
  Field_Mod32(&ADC1->CTRL3.reg, (uint8)ADC1_CTRL3_SW_MODE_Pos, ADC1_CTRL3_SW_MODE_Msk, SEQ_Mode);
}

INLINE void ADC1_Software_Mode_Sel()
{
  Field_Mod32(&ADC1->CTRL3.reg, (uint8)ADC1_CTRL3_SW_MODE_Pos, ADC1_CTRL3_SW_MODE_Msk, SW_Mode);
}

INLINE uint8 ADC1_EOC_Sts()
{
  return(u1_Field_Rd32  (&ADC1->CTRL_STS.reg, (uint8)ADC1_CTRL_STS_EOC_Pos, ADC1_CTRL_STS_EOC_Msk));
}

INLINE uint8 ADC1_EIM_Active_Sts()
{
  return(u1_Field_Rd32  (&ADC1->SQ_FB.reg, (uint8)ADC1_SQ_FB_EIM_ACTIVE_Pos, ADC1_SQ_FB_EIM_ACTIVE_Msk));
}

INLINE uint8 ADC1_ESM_Active_Sts()
{
  return(u1_Field_Rd32  (&ADC1->SQ_FB.reg, (uint8)ADC1_SQ_FB_ESM_ACTIVE_Pos, ADC1_SQ_FB_ESM_ACTIVE_Msk));
}

INLINE uint8 ADC1_Current_Active_Sequence_Sts()
{
  return(u8_Field_Rd32  (&ADC1->SQ_FB.reg, (uint8)ADC1_SQ_FB_SQx_Pos, ADC1_SQ_FB_SQx_Msk));
}

INLINE uint8 ADC1_Current_Active_Channel_Sts()
{
  return(u8_Field_Rd32  (&ADC1->SQ_FB.reg, (uint8)ADC1_SQ_FB_CHx_Pos, ADC1_SQ_FB_CHx_Msk));
}

INLINE uint8 ADC1_Sequencer_Stop_Signal_Sts()
{
  return(u1_Field_Rd32  (&ADC1->SQ_FB.reg, (uint8)ADC1_SQ_FB_SQ_STOP_Pos, ADC1_SQ_FB_SQ_STOP_Msk));
}

INLINE uint8 ADC1_Sequence_Feedback_Sts()
{
  return(u8_Field_Rd32  (&ADC1->SQ_FB.reg, (uint8)ADC1_SQ_FB_SQ_FB_Pos, ADC1_SQ_FB_SQ_FB_Msk));
}

INLINE void ADC1_SW_Max_Time_Set(uint8 time)
{
  Field_Wrt32(&ADC1->MAX_TIME.reg, (uint8)ADC1_MAX_TIME_MAX_TIME_Pos, ADC1_MAX_TIME_MAX_TIME_Msk, time);
}

INLINE void ADC1_Sequence0_Set(uint16 mask_ch)
{
  Field_Mod32(&ADC1->SQ0_1.reg, (uint8)ADC1_SQ0_1_SQ0_Pos, ADC1_SQ0_1_SQ0_Msk, (mask_ch));
}

INLINE void ADC1_Sequence1_Set(uint16 mask_ch)
{
  Field_Mod32(&ADC1->SQ0_1.reg, (uint8)ADC1_SQ0_1_SQ1_Pos, ADC1_SQ0_1_SQ1_Msk, (mask_ch));
}

INLINE void ADC1_Sequence2_Set(uint16 mask_ch)
{
  Field_Mod32(&ADC1->SQ2_3.reg, (uint8)ADC1_SQ2_3_SQ2_Pos, ADC1_SQ2_3_SQ2_Msk, (mask_ch));
}

INLINE void ADC1_Sequence3_Set(uint16 mask_ch)
{
  Field_Mod32(&ADC1->SQ2_3.reg, (uint8)ADC1_SQ2_3_SQ3_Pos, ADC1_SQ2_3_SQ3_Msk, (mask_ch));
}

INLINE void ADC1_Sequence4_Set(uint16 mask_ch)
{
  Field_Mod32(&ADC1->SQ4_5.reg, (uint8)ADC1_SQ4_5_SQ4_Pos, ADC1_SQ4_5_SQ4_Msk, (mask_ch));
}

INLINE void ADC1_Sequence5_Set(uint16 mask_ch)
{
  Field_Mod32(&ADC1->SQ4_5.reg, (uint8)ADC1_SQ4_5_SQ5_Pos, ADC1_SQ4_5_SQ5_Msk, (mask_ch));
}

INLINE void ADC1_Sequence6_Set(uint16 mask_ch)
{
  Field_Mod32(&ADC1->SQ6_7.reg, (uint8)ADC1_SQ6_7_SQ6_Pos, ADC1_SQ6_7_SQ6_Msk, (mask_ch));
}

INLINE void ADC1_Sequence7_Set(uint16 mask_ch)
{
  Field_Mod32(&ADC1->SQ6_7.reg, (uint8)ADC1_SQ6_7_SQ7_Pos, ADC1_SQ6_7_SQ7_Msk, (mask_ch));
}

INLINE void ADC1_Sequence8_Set(uint16 mask_ch)
{
  Field_Mod32(&ADC1->SQ8_9.reg, (uint8)ADC1_SQ8_9_SQ8_Pos, ADC1_SQ8_9_SQ8_Msk, (mask_ch));
}

INLINE void ADC1_Sequence9_Set(uint16 mask_ch)
{
  Field_Mod32(&ADC1->SQ8_9.reg, (uint8)ADC1_SQ8_9_SQ9_Pos, ADC1_SQ8_9_SQ9_Msk, (mask_ch));
}

INLINE void ADC1_Sequence10_Set(uint16 mask_ch)
{
  Field_Mod32(&ADC1->SQ10_11.reg, (uint8)ADC1_SQ10_11_SQ10_Pos, ADC1_SQ10_11_SQ10_Msk, (mask_ch));
}

INLINE void ADC1_Sequence11_Set(uint16 mask_ch)
{
  Field_Mod32(&ADC1->SQ10_11.reg, (uint8)ADC1_SQ10_11_SQ11_Pos, ADC1_SQ10_11_SQ11_Msk, (mask_ch));
}

INLINE void ADC1_Sequence12_Set(uint16 mask_ch)
{
  Field_Mod32(&ADC1->SQ12_13.reg, (uint8)ADC1_SQ12_13_SQ12_Pos, ADC1_SQ12_13_SQ12_Msk, (mask_ch));
}

INLINE void ADC1_Sequence13_Set(uint16 mask_ch)
{
  Field_Mod32(&ADC1->SQ12_13.reg, (uint8)ADC1_SQ12_13_SQ13_Pos, ADC1_SQ12_13_SQ13_Msk, (mask_ch));
}

INLINE uint16 ADC1_Ch0_Result_Get()
{
  return(u16_Field_Rd32 (&ADC1->FILT_OUT0.reg, (uint8)ADC1_FILT_OUT0_FILT_OUT_CH0_Pos, ADC1_FILT_OUT0_FILT_OUT_CH0_Msk));
}

INLINE uint16 ADC1_Ch1_Result_Get()
{
  return(u16_Field_Rd32 (&ADC1->FILT_OUT1.reg, (uint8)ADC1_FILT_OUT1_FILT_OUT_CH1_Pos, ADC1_FILT_OUT1_FILT_OUT_CH1_Msk));
}

INLINE uint16 ADC1_Ch2_Result_Get()
{
  return(u16_Field_Rd32 (&ADC1->FILT_OUT2.reg, (uint8)ADC1_FILT_OUT2_FILT_OUT_CH2_Pos, ADC1_FILT_OUT2_FILT_OUT_CH2_Msk));
}

INLINE uint16 ADC1_Ch3_Result_Get()
{
  return(u16_Field_Rd32 (&ADC1->FILT_OUT3.reg, (uint8)ADC1_FILT_OUT3_FILT_OUT_CH3_Pos, ADC1_FILT_OUT3_FILT_OUT_CH3_Msk));
}

INLINE uint16 ADC1_Ch4_Result_Get()
{
  return(u16_Field_Rd32 (&ADC1->FILT_OUT4.reg, (uint8)ADC1_FILT_OUT4_FILT_OUT_CH4_Pos, ADC1_FILT_OUT4_FILT_OUT_CH4_Msk));
}

INLINE uint16 ADC1_Ch5_Result_Get()
{
  return(u16_Field_Rd32 (&ADC1->FILT_OUT5.reg, (uint8)ADC1_FILT_OUT5_FILT_OUT_CH5_Pos, ADC1_FILT_OUT5_FILT_OUT_CH5_Msk));
}

INLINE uint16 ADC1_Ch6_Result_Get()
{
  return(u16_Field_Rd32 (&ADC1->FILT_OUT6.reg, (uint8)ADC1_FILT_OUT6_FILT_OUT_CH6_Pos, ADC1_FILT_OUT6_FILT_OUT_CH6_Msk));
}

INLINE uint16 ADC1_Ch7_Result_Get()
{
  return(u16_Field_Rd32 (&ADC1->FILT_OUT7.reg, (uint8)ADC1_FILT_OUT7_FILT_OUT_CH7_Pos, ADC1_FILT_OUT7_FILT_OUT_CH7_Msk));
}

INLINE uint16 ADC1_Ch8_Result_Get()
{
  return(u16_Field_Rd32 (&ADC1->FILT_OUT8.reg, (uint8)ADC1_FILT_OUT8_FILT_OUT_CH8_Pos, ADC1_FILT_OUT8_FILT_OUT_CH8_Msk));
}

INLINE uint16 ADC1_Ch9_Result_Get()
{
  return(u16_Field_Rd32 (&ADC1->FILT_OUT9.reg, (uint8)ADC1_FILT_OUT9_FILT_OUT_CH9_Pos, ADC1_FILT_OUT9_FILT_OUT_CH9_Msk));
}

INLINE uint16 ADC1_Ch12_Result_Get()
{
  return(u16_Field_Rd32 (&ADC1->FILT_OUT12.reg, (uint8)ADC1_FILT_OUT12_FILT_OUT_CH12_Pos, ADC1_FILT_OUT12_FILT_OUT_CH12_Msk));
}

INLINE uint16 ADC1_Ch13_Result_Get()
{
  return(u16_Field_Rd32 (&ADC1->FILT_OUT13.reg, (uint8)ADC1_FILT_OUT13_FILT_OUT_CH13_Pos, ADC1_FILT_OUT13_FILT_OUT_CH13_Msk));
}

INLINE uint16 ADC1_EIM_Result_Get()
{
  return(u16_Field_Rd32 (&ADC1->FILT_OUTEIM.reg, (uint8)ADC1_FILT_OUTEIM_FILT_OUT_EIM_Pos, ADC1_FILT_OUTEIM_FILT_OUT_EIM_Msk));
}

INLINE uint16 ADC1_DU1_Result_Get()
{
  return(u16_Field_Rd32 (&ADC1->DIFFCH_OUT1.reg, (uint8)ADC1_DIFFCH_OUT1_DCH1_Pos, ADC1_DIFFCH_OUT1_DCH1_Msk));
}

INLINE uint16 ADC1_VBAT_SENSE_Result_Get()
{
  return(ADC1_Ch0_Result_Get());
}

INLINE uint16 ADC1_VS_Result_Get()
{
  return(ADC1_Ch1_Result_Get());
}

INLINE uint16 ADC1_MON1_Result_Get()
{
  return(ADC1_Ch2_Result_Get());
}

INLINE uint16 ADC1_MON2_Result_Get()
{
  return(ADC1_Ch3_Result_Get());
}

INLINE uint16 ADC1_MON3_Result_Get()
{
  return(ADC1_Ch4_Result_Get());
}

INLINE uint16 ADC1_MON4_Result_Get()
{
  return(ADC1_Ch5_Result_Get());
}

INLINE uint16 ADC1_P20_Result_Get()
{
  return(ADC1_Ch6_Result_Get());
}

INLINE uint16 ADC1_P21_Result_Get()
{
  return(ADC1_Ch7_Result_Get());
}

INLINE uint16 ADC1_P22_Result_Get()
{
  return(ADC1_Ch8_Result_Get());
}

INLINE uint16 ADC1_P23_Result_Get()
{
  return(ADC1_Ch9_Result_Get());
}

INLINE uint16 ADC1_P27_Result_Get()
{
  return(ADC1_Ch12_Result_Get());
}

INLINE uint16 ADC1_OPA_Result_Get()
{
  return(ADC1_Ch13_Result_Get());
}

INLINE void ADC1_Ch0_WaitForRead_Set()
{
  Field_Mod32(&ADC1->FILT_OUT0.reg, (uint8)ADC1_FILT_OUT0_WFR0_Pos, ADC1_FILT_OUT0_WFR0_Msk, WFR);
}

INLINE void ADC1_Ch0_Overwrite_Set()
{
  Field_Mod32(&ADC1->FILT_OUT0.reg, (uint8)ADC1_FILT_OUT0_WFR0_Pos, ADC1_FILT_OUT0_WFR0_Msk, OVERWRITE);
}

INLINE void ADC1_Ch1_WaitForRead_Set()
{
  Field_Mod32(&ADC1->FILT_OUT1.reg, (uint8)ADC1_FILT_OUT1_WFR1_Pos, ADC1_FILT_OUT1_WFR1_Msk, WFR);
}

INLINE void ADC1_Ch1_Overwrite_Set()
{
  Field_Mod32(&ADC1->FILT_OUT1.reg, (uint8)ADC1_FILT_OUT1_WFR1_Pos, ADC1_FILT_OUT1_WFR1_Msk, OVERWRITE);
}

INLINE void ADC1_Ch2_WaitForRead_Set()
{
  Field_Mod32(&ADC1->FILT_OUT2.reg, (uint8)ADC1_FILT_OUT2_WFR2_Pos, ADC1_FILT_OUT2_WFR2_Msk, WFR);
}

INLINE void ADC1_Ch2_Overwrite_Set()
{
  Field_Mod32(&ADC1->FILT_OUT2.reg, (uint8)ADC1_FILT_OUT2_WFR2_Pos, ADC1_FILT_OUT2_WFR2_Msk, OVERWRITE);
}

INLINE void ADC1_Ch3_WaitForRead_Set()
{
  Field_Mod32(&ADC1->FILT_OUT3.reg, (uint8)ADC1_FILT_OUT3_WFR3_Pos, ADC1_FILT_OUT3_WFR3_Msk, WFR);
}

INLINE void ADC1_Ch3_Overwrite_Set()
{
  Field_Mod32(&ADC1->FILT_OUT3.reg, (uint8)ADC1_FILT_OUT3_WFR3_Pos, ADC1_FILT_OUT3_WFR3_Msk, OVERWRITE);
}

INLINE void ADC1_Ch4_WaitForRead_Set()
{
  Field_Mod32(&ADC1->FILT_OUT4.reg, (uint8)ADC1_FILT_OUT4_WFR4_Pos, ADC1_FILT_OUT4_WFR4_Msk, WFR);
}

INLINE void ADC1_Ch4_Overwrite_Set()
{
  Field_Mod32(&ADC1->FILT_OUT4.reg, (uint8)ADC1_FILT_OUT4_WFR4_Pos, ADC1_FILT_OUT4_WFR4_Msk, OVERWRITE);
}

INLINE void ADC1_Ch5_WaitForRead_Set()
{
  Field_Mod32(&ADC1->FILT_OUT5.reg, (uint8)ADC1_FILT_OUT5_WFR5_Pos, ADC1_FILT_OUT5_WFR5_Msk, WFR);
}

INLINE void ADC1_Ch5_Overwrite_Set()
{
  Field_Mod32(&ADC1->FILT_OUT5.reg, (uint8)ADC1_FILT_OUT5_WFR5_Pos, ADC1_FILT_OUT5_WFR5_Msk, OVERWRITE);
}

INLINE void ADC1_Ch6_WaitForRead_Set()
{
  Field_Mod32(&ADC1->FILT_OUT6.reg, (uint8)ADC1_FILT_OUT6_WFR6_Pos, ADC1_FILT_OUT6_WFR6_Msk, WFR);
}

INLINE void ADC1_Ch6_Overwrite_Set()
{
  Field_Mod32(&ADC1->FILT_OUT6.reg, (uint8)ADC1_FILT_OUT6_WFR6_Pos, ADC1_FILT_OUT6_WFR6_Msk, OVERWRITE);
}

INLINE void ADC1_Ch7_WaitForRead_Set()
{
  Field_Mod32(&ADC1->FILT_OUT7.reg, (uint8)ADC1_FILT_OUT7_WFR7_Pos, ADC1_FILT_OUT7_WFR7_Msk, WFR);
}

INLINE void ADC1_Ch7_Overwrite_Set()
{
  Field_Mod32(&ADC1->FILT_OUT7.reg, (uint8)ADC1_FILT_OUT7_WFR7_Pos, ADC1_FILT_OUT7_WFR7_Msk, OVERWRITE);
}

INLINE void ADC1_Ch8_WaitForRead_Set()
{
  Field_Mod32(&ADC1->FILT_OUT8.reg, (uint8)ADC1_FILT_OUT8_WFR8_Pos, ADC1_FILT_OUT8_WFR8_Msk, WFR);
}

INLINE void ADC1_Ch8_Overwrite_Set()
{
  Field_Mod32(&ADC1->FILT_OUT8.reg, (uint8)ADC1_FILT_OUT8_WFR8_Pos, ADC1_FILT_OUT8_WFR8_Msk, OVERWRITE);
}

INLINE void ADC1_Ch9_WaitForRead_Set()
{
  Field_Mod32(&ADC1->FILT_OUT9.reg, (uint8)ADC1_FILT_OUT9_WFR9_Pos, ADC1_FILT_OUT9_WFR9_Msk, WFR);
}

INLINE void ADC1_Ch9_Overwrite_Set()
{
  Field_Mod32(&ADC1->FILT_OUT9.reg, (uint8)ADC1_FILT_OUT9_WFR9_Pos, ADC1_FILT_OUT9_WFR9_Msk, OVERWRITE);
}

INLINE void ADC1_Ch12_WaitForRead_Set()
{
  Field_Mod32(&ADC1->FILT_OUT12.reg, (uint8)ADC1_FILT_OUT12_WFR12_Pos, ADC1_FILT_OUT12_WFR12_Msk, WFR);
}

INLINE void ADC1_Ch12_Overwrite_Set()
{
  Field_Mod32(&ADC1->FILT_OUT12.reg, (uint8)ADC1_FILT_OUT12_WFR12_Pos, ADC1_FILT_OUT12_WFR12_Msk, OVERWRITE);
}

INLINE void ADC1_Ch13_WaitForRead_Set()
{
  Field_Mod32(&ADC1->FILT_OUT13.reg, (uint8)ADC1_FILT_OUT13_WFR13_Pos, ADC1_FILT_OUT13_WFR13_Msk, WFR);
}

INLINE void ADC1_Ch13_Overwrite_Set()
{
  Field_Mod32(&ADC1->FILT_OUT13.reg, (uint8)ADC1_FILT_OUT13_WFR13_Pos, ADC1_FILT_OUT13_WFR13_Msk, OVERWRITE);
}

INLINE void ADC1_DU1_WaitForRead_Set()
{
  Field_Mod32(&ADC1->DIFFCH_OUT1.reg, (uint8)ADC1_DIFFCH_OUT1_DWFR1_Pos, ADC1_DIFFCH_OUT1_DWFR1_Msk, WFR);
}

INLINE void ADC1_DU1_Overwrite_Set()
{
  Field_Mod32(&ADC1->DIFFCH_OUT1.reg, (uint8)ADC1_DIFFCH_OUT1_DWFR1_Pos, ADC1_DIFFCH_OUT1_DWFR1_Msk, OVERWRITE);
}

INLINE void ADC1_EIM_En()
{
  Field_Mod32(&ADC1->CHx_EIM.reg, (uint8)ADC1_CHx_EIM_EIM_EN_Pos, ADC1_CHx_EIM_EIM_EN_Msk, 1u);
}

INLINE void ADC1_EIM_Dis()
{
  Field_Mod32(&ADC1->CHx_EIM.reg, (uint8)ADC1_CHx_EIM_EIM_EN_Pos, ADC1_CHx_EIM_EIM_EN_Msk, 0u);
}

INLINE void ADC1_ESM_En()
{
  Field_Mod32(&ADC1->CHx_ESM.reg, (uint8)ADC1_CHx_ESM_ESM_EN_Pos, ADC1_CHx_ESM_ESM_EN_Msk, 1u);
}

INLINE void ADC1_ESM_Dis()
{
  Field_Mod32(&ADC1->CHx_ESM.reg, (uint8)ADC1_CHx_ESM_ESM_EN_Pos, ADC1_CHx_ESM_ESM_EN_Msk, 0u);
}

INLINE void ADC1_EIM_Channel_Set(uint8 ch)
{
  Field_Mod32(&ADC1->CHx_EIM.reg, (uint8)ADC1_CHx_EIM_EIM_CHx_Pos, ADC1_CHx_EIM_EIM_CHx_Msk, ch);
}

INLINE void ADC1_ESM_Channel_Set(uint16 mask_ch)
{
  Field_Mod32(&ADC1->CHx_ESM.reg, (uint8)ADC1_CHx_ESM_ESM_0_Pos, ADC1_CHx_ESM_ESM_0_Msk, (mask_ch));
}

INLINE uint8 ADC1_EIM_Channel_Read()
{
  return(u8_Field_Rd32(&ADC1->CHx_EIM.reg, (uint8)ADC1_CHx_EIM_EIM_CHx_Pos, ADC1_CHx_EIM_EIM_CHx_Msk));
}

INLINE void ADC1_PP_Ch0_Filt_UpLo_En()
{
  Field_Mod32(&ADC1->FILT_UPLO_CTRL.reg, (uint8)ADC1_FILT_UPLO_CTRL_FUL_PP_CH0_EN_Pos, ADC1_FILT_UPLO_CTRL_FUL_PP_CH0_EN_Msk, 1u);
}

INLINE void ADC1_PP_Ch1_Filt_UpLo_En()
{
  Field_Mod32(&ADC1->FILT_UPLO_CTRL.reg, (uint8)ADC1_FILT_UPLO_CTRL_FUL_PP_CH1_EN_Pos, ADC1_FILT_UPLO_CTRL_FUL_PP_CH1_EN_Msk, 1u);
}

INLINE void ADC1_PP_Ch2_Filt_UpLo_En()
{
  Field_Mod32(&ADC1->FILT_UPLO_CTRL.reg, (uint8)ADC1_FILT_UPLO_CTRL_FUL_PP_CH2_EN_Pos, ADC1_FILT_UPLO_CTRL_FUL_PP_CH2_EN_Msk, 1u);
}

INLINE void ADC1_PP_Ch3_Filt_UpLo_En()
{
  Field_Mod32(&ADC1->FILT_UPLO_CTRL.reg, (uint8)ADC1_FILT_UPLO_CTRL_FUL_PP_CH3_EN_Pos, ADC1_FILT_UPLO_CTRL_FUL_PP_CH3_EN_Msk, 1u);
}

INLINE void ADC1_PP_Ch4_Filt_UpLo_En()
{
  Field_Mod32(&ADC1->FILT_UPLO_CTRL.reg, (uint8)ADC1_FILT_UPLO_CTRL_FUL_PP_CH4_EN_Pos, ADC1_FILT_UPLO_CTRL_FUL_PP_CH4_EN_Msk, 1u);
}

INLINE void ADC1_PP_Ch5_Filt_UpLo_En()
{
  Field_Mod32(&ADC1->FILT_UPLO_CTRL.reg, (uint8)ADC1_FILT_UPLO_CTRL_FUL_PP_CH5_EN_Pos, ADC1_FILT_UPLO_CTRL_FUL_PP_CH5_EN_Msk, 1u);
}

INLINE void ADC1_PP_Ch6_Filt_UpLo_En()
{
  Field_Mod32(&ADC1->FILT_UPLO_CTRL.reg, (uint8)ADC1_FILT_UPLO_CTRL_FUL_PP_CH6_EN_Pos, ADC1_FILT_UPLO_CTRL_FUL_PP_CH6_EN_Msk, 1u);
}

INLINE void ADC1_PP_Ch7_Filt_UpLo_En()
{
  Field_Mod32(&ADC1->FILT_UPLO_CTRL.reg, (uint8)ADC1_FILT_UPLO_CTRL_FUL_PP_CH7_EN_Pos, ADC1_FILT_UPLO_CTRL_FUL_PP_CH7_EN_Msk, 1u);
}

INLINE void ADC1_PP_Ch0_Filt_UpLo_Dis()
{
  Field_Mod32(&ADC1->FILT_UPLO_CTRL.reg, (uint8)ADC1_FILT_UPLO_CTRL_FUL_PP_CH0_EN_Pos, ADC1_FILT_UPLO_CTRL_FUL_PP_CH0_EN_Msk, 0u);
}

INLINE void ADC1_PP_Ch1_Filt_UpLo_Dis()
{
  Field_Mod32(&ADC1->FILT_UPLO_CTRL.reg, (uint8)ADC1_FILT_UPLO_CTRL_FUL_PP_CH1_EN_Pos, ADC1_FILT_UPLO_CTRL_FUL_PP_CH1_EN_Msk, 0u);
}

INLINE void ADC1_PP_Ch2_Filt_UpLo_Dis()
{
  Field_Mod32(&ADC1->FILT_UPLO_CTRL.reg, (uint8)ADC1_FILT_UPLO_CTRL_FUL_PP_CH2_EN_Pos, ADC1_FILT_UPLO_CTRL_FUL_PP_CH2_EN_Msk, 0u);
}

INLINE void ADC1_PP_Ch3_Filt_UpLo_Dis()
{
  Field_Mod32(&ADC1->FILT_UPLO_CTRL.reg, (uint8)ADC1_FILT_UPLO_CTRL_FUL_PP_CH3_EN_Pos, ADC1_FILT_UPLO_CTRL_FUL_PP_CH3_EN_Msk, 0u);
}

INLINE void ADC1_PP_Ch4_Filt_UpLo_Dis()
{
  Field_Mod32(&ADC1->FILT_UPLO_CTRL.reg, (uint8)ADC1_FILT_UPLO_CTRL_FUL_PP_CH4_EN_Pos, ADC1_FILT_UPLO_CTRL_FUL_PP_CH4_EN_Msk, 0u);
}

INLINE void ADC1_PP_Ch5_Filt_UpLo_Dis()
{
  Field_Mod32(&ADC1->FILT_UPLO_CTRL.reg, (uint8)ADC1_FILT_UPLO_CTRL_FUL_PP_CH5_EN_Pos, ADC1_FILT_UPLO_CTRL_FUL_PP_CH5_EN_Msk, 0u);
}

INLINE void ADC1_PP_Ch6_Filt_UpLo_Dis()
{
  Field_Mod32(&ADC1->FILT_UPLO_CTRL.reg, (uint8)ADC1_FILT_UPLO_CTRL_FUL_PP_CH6_EN_Pos, ADC1_FILT_UPLO_CTRL_FUL_PP_CH6_EN_Msk, 0u);
}

INLINE void ADC1_PP_Ch7_Filt_UpLo_Dis()
{
  Field_Mod32(&ADC1->FILT_UPLO_CTRL.reg, (uint8)ADC1_FILT_UPLO_CTRL_FUL_PP_CH7_EN_Pos, ADC1_FILT_UPLO_CTRL_FUL_PP_CH7_EN_Msk, 0u);
}

INLINE void ADC1_DU1_Lo_Sts_Clr()
{
  Field_Wrt32(&ADC1->STSCLR_1.reg, (uint8)ADC1_STSCLR_1_DU1LO_SC_Pos, ADC1_STSCLR_1_DU1LO_SC_Msk, 1u);
}

INLINE void ADC1_DU1_Up_Sts_Clr()
{
  Field_Wrt32(&ADC1->STSCLR_1.reg, (uint8)ADC1_STSCLR_1_DU1UP_SC_Pos, ADC1_STSCLR_1_DU1UP_SC_Msk, 1u);
}

INLINE void ADC1_DU1_En()
{
  Field_Mod32(&ADC1->DUIN_SEL.reg, (uint8)ADC1_DUIN_SEL_DU1_EN_Pos, ADC1_DUIN_SEL_DU1_EN_Msk, 1u);
}

INLINE void ADC1_DU1_Dis()
{
  Field_Mod32(&ADC1->DUIN_SEL.reg, (uint8)ADC1_DUIN_SEL_DU1_EN_Pos, ADC1_DUIN_SEL_DU1_EN_Msk, 0u);
}

INLINE uint8 ADC1_DU1_Result_Neg_Sts()
{
  return(u1_Field_Rd32(&ADC1->DUIN_SEL.reg, (uint8)ADC1_DUIN_SEL_DU1RES_NEG_Pos, ADC1_DUIN_SEL_DU1RES_NEG_Msk));
}

INLINE void ADC1_PP_Ch0_Mode_Meas_Sel(uint8 mmode)
{
  Field_Mod32(&ADC1->MMODE0_7.reg, (uint8)ADC1_MMODE0_7_MMODE_0_Pos, ADC1_MMODE0_7_MMODE_0_Msk, mmode);
}

INLINE void ADC1_PP_Ch1_Mode_Meas_Sel(uint8 mmode)
{
  Field_Mod32(&ADC1->MMODE0_7.reg, (uint8)ADC1_MMODE0_7_MMODE_1_Pos, ADC1_MMODE0_7_MMODE_1_Msk, mmode);
}

INLINE void ADC1_PP_Ch2_Mode_Meas_Sel(uint8 mmode)
{
  Field_Mod32(&ADC1->MMODE0_7.reg, (uint8)ADC1_MMODE0_7_MMODE_2_Pos, ADC1_MMODE0_7_MMODE_2_Msk, mmode);
}

INLINE void ADC1_PP_Ch3_Mode_Meas_Sel(uint8 mmode)
{
  Field_Mod32(&ADC1->MMODE0_7.reg, (uint8)ADC1_MMODE0_7_MMODE_3_Pos, ADC1_MMODE0_7_MMODE_3_Msk, mmode);
}

INLINE void ADC1_PP_Ch4_Mode_Meas_Sel(uint8 mmode)
{
  Field_Mod32(&ADC1->MMODE0_7.reg, (uint8)ADC1_MMODE0_7_MMODE_4_Pos, ADC1_MMODE0_7_MMODE_4_Msk, mmode);
}

INLINE void ADC1_PP_Ch5_Mode_Meas_Sel(uint8 mmode)
{
  Field_Mod32(&ADC1->MMODE0_7.reg, (uint8)ADC1_MMODE0_7_MMODE_5_Pos, ADC1_MMODE0_7_MMODE_5_Msk, mmode);
}

INLINE void ADC1_PP_Ch6_Mode_Meas_Sel(uint8 mmode)
{
  Field_Mod32(&ADC1->MMODE0_7.reg, (uint8)ADC1_MMODE0_7_MMODE_6_Pos, ADC1_MMODE0_7_MMODE_6_Msk, mmode);
}

INLINE void ADC1_PP_Ch7_Mode_Meas_Sel(uint8 mmode)
{
  Field_Mod32(&ADC1->MMODE0_7.reg, (uint8)ADC1_MMODE0_7_MMODE_7_Pos, ADC1_MMODE0_7_MMODE_7_Msk, mmode);
}

INLINE void ADC1_DU1_Mode_Meas_Sel(uint8 mmode)
{
  Field_Mod32(&ADC1->MMODE0_7.reg, (uint8)ADC1_MMODE0_7_MMODE_D1_Pos, ADC1_MMODE0_7_MMODE_D1_Msk, mmode);
}

INLINE void ADC1_PP_Ch0_Lo_Th_Set(uint8 trig_val)
{
  Field_Mod32(&ADC1->TH0_3_LOWER.reg, (uint8)ADC1_TH0_3_LOWER_PP_CH0_LOW_Pos, ADC1_TH0_3_LOWER_PP_CH0_LOW_Msk, trig_val);
}

INLINE void ADC1_PP_Ch1_Lo_Th_Set(uint8 trig_val)
{
  Field_Mod32(&ADC1->TH0_3_LOWER.reg, (uint8)ADC1_TH0_3_LOWER_PP_CH1_LOW_Pos, ADC1_TH0_3_LOWER_PP_CH1_LOW_Msk, trig_val);
}

INLINE void ADC1_PP_Ch2_Lo_Th_Set(uint8 trig_val)
{
  Field_Mod32(&ADC1->TH0_3_LOWER.reg, (uint8)ADC1_TH0_3_LOWER_PP_CH2_LOW_Pos, ADC1_TH0_3_LOWER_PP_CH2_LOW_Msk, trig_val);
}

INLINE void ADC1_PP_Ch3_Lo_Th_Set(uint8 trig_val)
{
  Field_Mod32(&ADC1->TH0_3_LOWER.reg, (uint8)ADC1_TH0_3_LOWER_PP_CH3_LOW_Pos, ADC1_TH0_3_LOWER_PP_CH3_LOW_Msk, trig_val);
}

INLINE void ADC1_PP_Ch4_Lo_Th_Set(uint8 trig_val)
{
  Field_Mod32(&ADC1->TH4_7_LOWER.reg, (uint8)ADC1_TH4_7_LOWER_PP_CH4_LOW_Pos, ADC1_TH4_7_LOWER_PP_CH4_LOW_Msk, trig_val);
}

INLINE void ADC1_PP_Ch5_Lo_Th_Set(uint8 trig_val)
{
  Field_Mod32(&ADC1->TH4_7_LOWER.reg, (uint8)ADC1_TH4_7_LOWER_PP_CH5_LOW_Pos, ADC1_TH4_7_LOWER_PP_CH5_LOW_Msk, trig_val);
}

INLINE void ADC1_PP_Ch6_Lo_Th_Set(uint8 trig_val)
{
  Field_Mod32(&ADC1->TH4_7_LOWER.reg, (uint8)ADC1_TH4_7_LOWER_PP_CH6_LOW_Pos, ADC1_TH4_7_LOWER_PP_CH6_LOW_Msk, trig_val);
}

INLINE void ADC1_PP_Ch7_Lo_Th_Set(uint8 trig_val)
{
  Field_Mod32(&ADC1->TH4_7_LOWER.reg, (uint8)ADC1_TH4_7_LOWER_PP_CH7_LOW_Pos, ADC1_TH4_7_LOWER_PP_CH7_LOW_Msk, trig_val);
}

INLINE void ADC1_DU1_Lo_Th_Set(uint8 trig_val)
{
  Field_Wrt32(&ADC1->DCHTH1_4_LOWER.reg, (uint8)ADC1_DCHTH1_4_LOWER_DCH1_LOW_Pos, ADC1_DCHTH1_4_LOWER_DCH1_LOW_Msk, trig_val);
}

INLINE void ADC1_PP_Ch0_Up_Th_Set(uint8 trig_val)
{
  Field_Mod32(&ADC1->TH0_3_UPPER.reg, (uint8)ADC1_TH0_3_UPPER_PP_CH0_UP_Pos, ADC1_TH0_3_UPPER_PP_CH0_UP_Msk, trig_val);
}

INLINE void ADC1_PP_Ch1_Up_Th_Set(uint8 trig_val)
{
  Field_Mod32(&ADC1->TH0_3_UPPER.reg, (uint8)ADC1_TH0_3_UPPER_PP_CH1_UP_Pos, ADC1_TH0_3_UPPER_PP_CH1_UP_Msk, trig_val);
}

INLINE void ADC1_PP_Ch2_Up_Th_Set(uint8 trig_val)
{
  Field_Mod32(&ADC1->TH0_3_UPPER.reg, (uint8)ADC1_TH0_3_UPPER_PP_CH2_UP_Pos, ADC1_TH0_3_UPPER_PP_CH2_UP_Msk, trig_val);
}

INLINE void ADC1_PP_Ch3_Up_Th_Set(uint8 trig_val)
{
  Field_Mod32(&ADC1->TH0_3_UPPER.reg, (uint8)ADC1_TH0_3_UPPER_PP_CH3_UP_Pos, ADC1_TH0_3_UPPER_PP_CH3_UP_Msk, trig_val);
}

INLINE void ADC1_PP_Ch4_Up_Th_Set(uint8 trig_val)
{
  Field_Mod32(&ADC1->TH4_7_UPPER.reg, (uint8)ADC1_TH4_7_UPPER_PP_CH4_UP_Pos, ADC1_TH4_7_UPPER_PP_CH4_UP_Msk, trig_val);
}

INLINE void ADC1_PP_Ch5_Up_Th_Set(uint8 trig_val)
{
  Field_Mod32(&ADC1->TH4_7_UPPER.reg, (uint8)ADC1_TH4_7_UPPER_PP_CH5_UP_Pos, ADC1_TH4_7_UPPER_PP_CH5_UP_Msk, trig_val);
}

INLINE void ADC1_PP_Ch6_Up_Th_Set(uint8 trig_val)
{
  Field_Mod32(&ADC1->TH4_7_UPPER.reg, (uint8)ADC1_TH4_7_UPPER_PP_CH6_UP_Pos, ADC1_TH4_7_UPPER_PP_CH6_UP_Msk, trig_val);
}

INLINE void ADC1_PP_Ch7_Up_Th_Set(uint8 trig_val)
{
  Field_Mod32(&ADC1->TH4_7_UPPER.reg, (uint8)ADC1_TH4_7_UPPER_PP_CH7_UP_Pos, ADC1_TH4_7_UPPER_PP_CH7_UP_Msk, trig_val);
}

INLINE void ADC1_DU1_Up_Th_Set(uint8 trig_val)
{
  Field_Wrt32(&ADC1->DCHTH1_4_UPPER.reg, (uint8)ADC1_DCHTH1_4_UPPER_DCH1_UP_Pos, ADC1_DCHTH1_4_UPPER_DCH1_UP_Msk, trig_val);
}

INLINE void ADC1_PP_Ch0_Lo_Hyst_Set(uint8 hyst)
{
  Field_Mod32(&ADC1->CNT0_3_LOWER.reg, (uint8)ADC1_CNT0_3_LOWER_HYST_LO_PP0_Pos, ADC1_CNT0_3_LOWER_HYST_LO_PP0_Msk, hyst);
}

INLINE void ADC1_PP_Ch1_Lo_Hyst_Set(uint8 hyst)
{
  Field_Mod32(&ADC1->CNT0_3_LOWER.reg, (uint8)ADC1_CNT0_3_LOWER_HYST_LO_PP1_Pos, ADC1_CNT0_3_LOWER_HYST_LO_PP1_Msk, hyst);
}

INLINE void ADC1_PP_Ch2_Lo_Hyst_Set(uint8 hyst)
{
  Field_Mod32(&ADC1->CNT0_3_LOWER.reg, (uint8)ADC1_CNT0_3_LOWER_HYST_LO_PP2_Pos, ADC1_CNT0_3_LOWER_HYST_LO_PP2_Msk, hyst);
}

INLINE void ADC1_PP_Ch3_Lo_Hyst_Set(uint8 hyst)
{
  Field_Mod32(&ADC1->CNT0_3_LOWER.reg, (uint8)ADC1_CNT0_3_LOWER_HYST_LO_PP3_Pos, ADC1_CNT0_3_LOWER_HYST_LO_PP3_Msk, hyst);
}

INLINE void ADC1_PP_Ch4_Lo_Hyst_Set(uint8 hyst)
{
  Field_Mod32(&ADC1->CNT4_7_LOWER.reg, (uint8)ADC1_CNT4_7_LOWER_HYST_LO_PP4_Pos, ADC1_CNT4_7_LOWER_HYST_LO_PP4_Msk, hyst);
}

INLINE void ADC1_PP_Ch5_Lo_Hyst_Set(uint8 hyst)
{
  Field_Mod32(&ADC1->CNT4_7_LOWER.reg, (uint8)ADC1_CNT4_7_LOWER_HYST_LO_PP5_Pos, ADC1_CNT4_7_LOWER_HYST_LO_PP5_Msk, hyst);
}

INLINE void ADC1_PP_Ch6_Lo_Hyst_Set(uint8 hyst)
{
  Field_Mod32(&ADC1->CNT4_7_LOWER.reg, (uint8)ADC1_CNT4_7_LOWER_HYST_LO_PP6_Pos, ADC1_CNT4_7_LOWER_HYST_LO_PP6_Msk, hyst);
}

INLINE void ADC1_PP_Ch7_Lo_Hyst_Set(uint8 hyst)
{
  Field_Mod32(&ADC1->CNT4_7_LOWER.reg, (uint8)ADC1_CNT4_7_LOWER_HYST_LO_PP7_Pos, ADC1_CNT4_7_LOWER_HYST_LO_PP7_Msk, hyst);
}

INLINE void ADC1_DU1_Lo_Hyst_Set(uint8 hyst)
{
  Field_Mod32(&ADC1->DCHCNT1_4_LOWER.reg, (uint8)ADC1_DCHCNT1_4_LOWER_HYST_LO_DCH1_Pos, ADC1_DCHCNT1_4_LOWER_HYST_LO_DCH1_Msk, hyst);
}

INLINE void ADC1_PP_Ch0_Up_Hyst_Set(uint8 hyst)
{
  Field_Mod32(&ADC1->CNT0_3_UPPER.reg, (uint8)ADC1_CNT0_3_UPPER_HYST_UP_PP0_Pos, ADC1_CNT0_3_UPPER_HYST_UP_PP0_Msk, hyst);
}

INLINE void ADC1_PP_Ch1_Up_Hyst_Set(uint8 hyst)
{
  Field_Mod32(&ADC1->CNT0_3_UPPER.reg, (uint8)ADC1_CNT0_3_UPPER_HYST_UP_PP1_Pos, ADC1_CNT0_3_UPPER_HYST_UP_PP1_Msk, hyst);
}

INLINE void ADC1_PP_Ch2_Up_Hyst_Set(uint8 hyst)
{
  Field_Mod32(&ADC1->CNT0_3_UPPER.reg, (uint8)ADC1_CNT0_3_UPPER_HYST_UP_PP2_Pos, ADC1_CNT0_3_UPPER_HYST_UP_PP2_Msk, hyst);
}

INLINE void ADC1_PP_Ch3_Up_Hyst_Set(uint8 hyst)
{
  Field_Mod32(&ADC1->CNT0_3_UPPER.reg, (uint8)ADC1_CNT0_3_UPPER_HYST_UP_PP3_Pos, ADC1_CNT0_3_UPPER_HYST_UP_PP3_Msk, hyst);
}

INLINE void ADC1_PP_Ch4_Up_Hyst_Set(uint8 hyst)
{
  Field_Mod32(&ADC1->CNT4_7_UPPER.reg, (uint8)ADC1_CNT4_7_UPPER_HYST_UP_PP4_Pos, ADC1_CNT4_7_UPPER_HYST_UP_PP4_Msk, hyst);
}

INLINE void ADC1_PP_Ch5_Up_Hyst_Set(uint8 hyst)
{
  Field_Mod32(&ADC1->CNT4_7_UPPER.reg, (uint8)ADC1_CNT4_7_UPPER_HYST_UP_PP5_Pos, ADC1_CNT4_7_UPPER_HYST_UP_PP5_Msk, hyst);
}

INLINE void ADC1_PP_Ch6_Up_Hyst_Set(uint8 hyst)
{
  Field_Mod32(&ADC1->CNT4_7_UPPER.reg, (uint8)ADC1_CNT4_7_UPPER_HYST_UP_PP6_Pos, ADC1_CNT4_7_UPPER_HYST_UP_PP6_Msk, hyst);
}

INLINE void ADC1_PP_Ch7_Up_Hyst_Set(uint8 hyst)
{
  Field_Mod32(&ADC1->CNT4_7_UPPER.reg, (uint8)ADC1_CNT4_7_UPPER_HYST_UP_PP7_Pos, ADC1_CNT4_7_UPPER_HYST_UP_PP7_Msk, hyst);
}

INLINE void ADC1_DU1_Up_Hyst_Set(uint8 hyst)
{
  Field_Mod32(&ADC1->DCHCNT1_4_UPPER.reg, (uint8)ADC1_DCHCNT1_4_UPPER_HYST_UP_DCH1_Pos, ADC1_DCHCNT1_4_UPPER_HYST_UP_DCH1_Msk, hyst);
}

INLINE void ADC1_PP_Ch0_Lo_Cnt_Set(uint8 cnt)
{
  Field_Mod32(&ADC1->CNT0_3_LOWER.reg, (uint8)ADC1_CNT0_3_LOWER_CNT_LO_PP0_Pos, ADC1_CNT0_3_LOWER_CNT_LO_PP0_Msk, cnt);
}

INLINE void ADC1_PP_Ch1_Lo_Cnt_Set(uint8 cnt)
{
  Field_Mod32(&ADC1->CNT0_3_LOWER.reg, (uint8)ADC1_CNT0_3_LOWER_CNT_LO_PP1_Pos, ADC1_CNT0_3_LOWER_CNT_LO_PP1_Msk, cnt);
}

INLINE void ADC1_PP_Ch2_Lo_Cnt_Set(uint8 cnt)
{
  Field_Mod32(&ADC1->CNT0_3_LOWER.reg, (uint8)ADC1_CNT0_3_LOWER_CNT_LO_PP2_Pos, ADC1_CNT0_3_LOWER_CNT_LO_PP2_Msk, cnt);
}

INLINE void ADC1_PP_Ch3_Lo_Cnt_Set(uint8 cnt)
{
  Field_Mod32(&ADC1->CNT0_3_LOWER.reg, (uint8)ADC1_CNT0_3_LOWER_CNT_LO_PP3_Pos, ADC1_CNT0_3_LOWER_CNT_LO_PP3_Msk, cnt);
}

INLINE void ADC1_PP_Ch4_Lo_Cnt_Set(uint8 cnt)
{
  Field_Mod32(&ADC1->CNT4_7_LOWER.reg, (uint8)ADC1_CNT4_7_LOWER_CNT_LO_PP4_Pos, ADC1_CNT4_7_LOWER_CNT_LO_PP4_Msk, cnt);
}

INLINE void ADC1_PP_Ch5_Lo_Cnt_Set(uint8 cnt)
{
  Field_Mod32(&ADC1->CNT4_7_LOWER.reg, (uint8)ADC1_CNT4_7_LOWER_CNT_LO_PP5_Pos, ADC1_CNT4_7_LOWER_CNT_LO_PP5_Msk, cnt);
}

INLINE void ADC1_PP_Ch6_Lo_Cnt_Set(uint8 cnt)
{
  Field_Mod32(&ADC1->CNT4_7_LOWER.reg, (uint8)ADC1_CNT4_7_LOWER_CNT_LO_PP6_Pos, ADC1_CNT4_7_LOWER_CNT_LO_PP6_Msk, cnt);
}

INLINE void ADC1_PP_Ch7_Lo_Cnt_Set(uint8 cnt)
{
  Field_Mod32(&ADC1->CNT4_7_LOWER.reg, (uint8)ADC1_CNT4_7_LOWER_CNT_LO_PP7_Pos, ADC1_CNT4_7_LOWER_CNT_LO_PP7_Msk, cnt);
}

INLINE void ADC1_DU1_Lo_Cnt_Set(uint8 cnt)
{
  Field_Mod32(&ADC1->DCHCNT1_4_LOWER.reg, (uint8)ADC1_DCHCNT1_4_LOWER_CNT_LO_DCH1_Pos, ADC1_DCHCNT1_4_LOWER_CNT_LO_DCH1_Msk, cnt);
}

INLINE void ADC1_PP_Ch0_Up_Cnt_Set(uint8 cnt)
{
  Field_Mod32(&ADC1->CNT0_3_UPPER.reg, (uint8)ADC1_CNT0_3_UPPER_CNT_UP_PP0_Pos, ADC1_CNT0_3_UPPER_CNT_UP_PP0_Msk, cnt);
}

INLINE void ADC1_PP_Ch1_Up_Cnt_Set(uint8 cnt)
{
  Field_Mod32(&ADC1->CNT0_3_UPPER.reg, (uint8)ADC1_CNT0_3_UPPER_CNT_UP_PP1_Pos, ADC1_CNT0_3_UPPER_CNT_UP_PP1_Msk, cnt);
}

INLINE void ADC1_PP_Ch2_Up_Cnt_Set(uint8 cnt)
{
  Field_Mod32(&ADC1->CNT0_3_UPPER.reg, (uint8)ADC1_CNT0_3_UPPER_CNT_UP_PP2_Pos, ADC1_CNT0_3_UPPER_CNT_UP_PP2_Msk, cnt);
}

INLINE void ADC1_PP_Ch3_Up_Cnt_Set(uint8 cnt)
{
  Field_Mod32(&ADC1->CNT0_3_UPPER.reg, (uint8)ADC1_CNT0_3_UPPER_CNT_UP_PP3_Pos, ADC1_CNT0_3_UPPER_CNT_UP_PP3_Msk, cnt);
}

INLINE void ADC1_PP_Ch4_Up_Cnt_Set(uint8 cnt)
{
  Field_Mod32(&ADC1->CNT4_7_UPPER.reg, (uint8)ADC1_CNT4_7_UPPER_CNT_UP_PP4_Pos, ADC1_CNT4_7_UPPER_CNT_UP_PP4_Msk, cnt);
}

INLINE void ADC1_PP_Ch5_Up_Cnt_Set(uint8 cnt)
{
  Field_Mod32(&ADC1->CNT4_7_UPPER.reg, (uint8)ADC1_CNT4_7_UPPER_CNT_UP_PP5_Pos, ADC1_CNT4_7_UPPER_CNT_UP_PP5_Msk, cnt);
}

INLINE void ADC1_PP_Ch6_Up_Cnt_Set(uint8 cnt)
{
  Field_Mod32(&ADC1->CNT4_7_UPPER.reg, (uint8)ADC1_CNT4_7_UPPER_CNT_UP_PP6_Pos, ADC1_CNT4_7_UPPER_CNT_UP_PP6_Msk, cnt);
}

INLINE void ADC1_PP_Ch7_Up_Cnt_Set(uint8 cnt)
{
  Field_Mod32(&ADC1->CNT4_7_UPPER.reg, (uint8)ADC1_CNT4_7_UPPER_CNT_UP_PP7_Pos, ADC1_CNT4_7_UPPER_CNT_UP_PP7_Msk, cnt);
}

INLINE void ADC1_DU1_Up_Cnt_Set(uint8 cnt)
{
  Field_Mod32(&ADC1->DCHCNT1_4_UPPER.reg, (uint8)ADC1_DCHCNT1_4_UPPER_CNT_UP_DCH1_Pos, ADC1_DCHCNT1_4_UPPER_CNT_UP_DCH1_Msk, cnt);
}

INLINE void ADC1_Ch0_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_1.reg, (uint8)ADC1_IRQCLR_1_IIR_CH0_ISC_Pos, ADC1_IRQCLR_1_IIR_CH0_ISC_Msk, 1u);
}

INLINE void ADC1_Ch1_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_1.reg, (uint8)ADC1_IRQCLR_1_VS_ISC_Pos, ADC1_IRQCLR_1_VS_ISC_Msk, 1u);
}

INLINE void ADC1_Ch2_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_1.reg, (uint8)ADC1_IRQCLR_1_IIR_CH2_ISC_Pos, ADC1_IRQCLR_1_IIR_CH2_ISC_Msk, 1u);
}

INLINE void ADC1_Ch3_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_1.reg, (uint8)ADC1_IRQCLR_1_IIR_CH3_ISC_Pos, ADC1_IRQCLR_1_IIR_CH3_ISC_Msk, 1u);
}

INLINE void ADC1_Ch4_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_1.reg, (uint8)ADC1_IRQCLR_1_IIR_CH4_ISC_Pos, ADC1_IRQCLR_1_IIR_CH4_ISC_Msk, 1u);
}

INLINE void ADC1_Ch5_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_1.reg, (uint8)ADC1_IRQCLR_1_IIR_CH5_ISC_Pos, ADC1_IRQCLR_1_IIR_CH5_ISC_Msk, 1u);
}

INLINE void ADC1_Ch6_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_1.reg, (uint8)ADC1_IRQCLR_1_IIR_CH6_ISC_Pos, ADC1_IRQCLR_1_IIR_CH6_ISC_Msk, 1u);
}

INLINE void ADC1_Ch7_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_1.reg, (uint8)ADC1_IRQCLR_1_IIR_CH7_ISC_Pos, ADC1_IRQCLR_1_IIR_CH7_ISC_Msk, 1u);
}

INLINE void ADC1_Ch8_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_1.reg, (uint8)ADC1_IRQCLR_1_IIR_CH8_ISC_Pos, ADC1_IRQCLR_1_IIR_CH8_ISC_Msk, 1u);
}

INLINE void ADC1_Ch9_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_1.reg, (uint8)ADC1_IRQCLR_1_IIR_CH9_ISC_Pos, ADC1_IRQCLR_1_IIR_CH9_ISC_Msk, 1u);
}

INLINE void ADC1_Ch12_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_1.reg, (uint8)ADC1_IRQCLR_1_IIR_CH12_ISC_Pos, ADC1_IRQCLR_1_IIR_CH12_ISC_Msk, 1u);
}

INLINE void ADC1_Ch13_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_1.reg, (uint8)ADC1_IRQCLR_1_IIR_CH13_ISC_Pos, ADC1_IRQCLR_1_IIR_CH13_ISC_Msk, 1u);
}

INLINE void ADC1_EIM_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_1.reg, (uint8)ADC1_IRQCLR_1_EIM_ISC_Pos, ADC1_IRQCLR_1_EIM_ISC_Msk, 1u);
}

INLINE void ADC1_ESM_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_1.reg, (uint8)ADC1_IRQCLR_1_ESM_ISC_Pos, ADC1_IRQCLR_1_ESM_ISC_Msk, 1u);
}

INLINE void ADC1_DU1UP_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_1.reg, (uint8)ADC1_IRQCLR_1_DU1UP_ISC_Pos, ADC1_IRQCLR_1_DU1UP_ISC_Msk, 1u);
}

INLINE void ADC1_DU1LO_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_1.reg, (uint8)ADC1_IRQCLR_1_DU1LO_ISC_Pos, ADC1_IRQCLR_1_DU1LO_ISC_Msk, 1u);
}

INLINE void ADC1_Ch0_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH0_IEN_Pos, ADC1_IRQEN_1_IIR_CH0_IEN_Msk, 1u);
}

INLINE void ADC1_Ch0_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH0_IEN_Pos, ADC1_IRQEN_1_IIR_CH0_IEN_Msk, 0u);
}

INLINE void ADC1_Ch1_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_VS_IEN_Pos, ADC1_IRQEN_1_VS_IEN_Msk, 1u);
}

INLINE void ADC1_Ch1_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_VS_IEN_Pos, ADC1_IRQEN_1_VS_IEN_Msk, 0u);
}

INLINE void ADC1_Ch2_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH2_IEN_Pos, ADC1_IRQEN_1_IIR_CH2_IEN_Msk, 1u);
}

INLINE void ADC1_Ch2_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH2_IEN_Pos, ADC1_IRQEN_1_IIR_CH2_IEN_Msk, 0u);
}

INLINE void ADC1_Ch3_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH3_IEN_Pos, ADC1_IRQEN_1_IIR_CH3_IEN_Msk, 1u);
}

INLINE void ADC1_Ch3_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH3_IEN_Pos, ADC1_IRQEN_1_IIR_CH3_IEN_Msk, 0u);
}

INLINE void ADC1_Ch4_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH4_IEN_Pos, ADC1_IRQEN_1_IIR_CH4_IEN_Msk, 1u);
}

INLINE void ADC1_Ch4_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH4_IEN_Pos, ADC1_IRQEN_1_IIR_CH4_IEN_Msk, 0u);
}

INLINE void ADC1_Ch5_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH5_IEN_Pos, ADC1_IRQEN_1_IIR_CH5_IEN_Msk, 1u);
}

INLINE void ADC1_Ch5_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH5_IEN_Pos, ADC1_IRQEN_1_IIR_CH5_IEN_Msk, 0u);
}

INLINE void ADC1_Ch6_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH6_IEN_Pos, ADC1_IRQEN_1_IIR_CH6_IEN_Msk, 1u);
}

INLINE void ADC1_Ch6_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH6_IEN_Pos, ADC1_IRQEN_1_IIR_CH6_IEN_Msk, 0u);
}

INLINE void ADC1_Ch7_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH7_IEN_Pos, ADC1_IRQEN_1_IIR_CH7_IEN_Msk, 1u);
}

INLINE void ADC1_Ch7_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH7_IEN_Pos, ADC1_IRQEN_1_IIR_CH7_IEN_Msk, 0u);
}

INLINE void ADC1_Ch8_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH8_IEN_Pos, ADC1_IRQEN_1_IIR_CH8_IEN_Msk, 1u);
}

INLINE void ADC1_Ch8_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH8_IEN_Pos, ADC1_IRQEN_1_IIR_CH8_IEN_Msk, 0u);
}

INLINE void ADC1_Ch9_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH9_IEN_Pos, ADC1_IRQEN_1_IIR_CH9_IEN_Msk, 1u);
}

INLINE void ADC1_Ch9_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH9_IEN_Pos, ADC1_IRQEN_1_IIR_CH9_IEN_Msk, 0u);
}

INLINE void ADC1_Ch12_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH12_IEN_Pos, ADC1_IRQEN_1_IIR_CH12_IEN_Msk, 1u);
}

INLINE void ADC1_Ch12_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH12_IEN_Pos, ADC1_IRQEN_1_IIR_CH12_IEN_Msk, 0u);
}

INLINE void ADC1_Ch13_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH13_IEN_Pos, ADC1_IRQEN_1_IIR_CH13_IEN_Msk, 1u);
}

INLINE void ADC1_Ch13_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_IIR_CH13_IEN_Pos, ADC1_IRQEN_1_IIR_CH13_IEN_Msk, 0u);
}

INLINE void ADC1_EIM_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_EIM_IEN_Pos, ADC1_IRQEN_1_EIM_IEN_Msk, 1u);
}

INLINE void ADC1_EIM_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_EIM_IEN_Pos, ADC1_IRQEN_1_EIM_IEN_Msk, 0u);
}

INLINE void ADC1_ESM_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_ESM_IEN_Pos, ADC1_IRQEN_1_ESM_IEN_Msk, 1u);
}

INLINE void ADC1_ESM_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_ESM_IEN_Pos, ADC1_IRQEN_1_ESM_IEN_Msk, 0u);
}

INLINE void ADC1_DU1UP_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_DU1UP_IEN_Pos, ADC1_IRQEN_1_DU1UP_IEN_Msk, 1u);
}

INLINE void ADC1_DU1UP_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_DU1UP_IEN_Pos, ADC1_IRQEN_1_DU1UP_IEN_Msk, 0u);
}

INLINE void ADC1_DU1LO_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_DU1LO_IEN_Pos, ADC1_IRQEN_1_DU1LO_IEN_Msk, 1u);
}

INLINE void ADC1_DU1LO_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_1.reg, (uint8)ADC1_IRQEN_1_DU1LO_IEN_Pos, ADC1_IRQEN_1_DU1LO_IEN_Msk, 0u);
}

INLINE void ADC1_PP_Ch0_UP_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_2.reg, (uint8)ADC1_IRQCLR_2_PP_CH0_UP_ISC_Pos, ADC1_IRQCLR_2_PP_CH0_UP_ISC_Msk, 1u);
}

INLINE void ADC1_PP_Ch0_LO_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_2.reg, (uint8)ADC1_IRQCLR_2_PP_CH0_LO_ISC_Pos, ADC1_IRQCLR_2_PP_CH0_LO_ISC_Msk, 1u);
}

INLINE void ADC1_PP_Ch1_UP_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_2.reg, (uint8)ADC1_IRQCLR_2_VS_UP_ISC_Pos, ADC1_IRQCLR_2_VS_UP_ISC_Msk, 1u);
}

INLINE void ADC1_PP_Ch1_LO_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_2.reg, (uint8)ADC1_IRQCLR_2_VS_LO_ISC_Pos, ADC1_IRQCLR_2_VS_LO_ISC_Msk, 1u);
}

INLINE void ADC1_PP_Ch2_UP_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_2.reg, (uint8)ADC1_IRQCLR_2_PP_CH2_UP_ISC_Pos, ADC1_IRQCLR_2_PP_CH2_UP_ISC_Msk, 1u);
}

INLINE void ADC1_PP_Ch2_LO_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_2.reg, (uint8)ADC1_IRQCLR_2_PP_CH2_LO_ISC_Pos, ADC1_IRQCLR_2_PP_CH2_LO_ISC_Msk, 1u);
}

INLINE void ADC1_PP_Ch3_UP_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_2.reg, (uint8)ADC1_IRQCLR_2_PP_CH3_UP_ISC_Pos, ADC1_IRQCLR_2_PP_CH3_UP_ISC_Msk, 1u);
}

INLINE void ADC1_PP_Ch3_LO_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_2.reg, (uint8)ADC1_IRQCLR_2_PP_CH3_LO_ISC_Pos, ADC1_IRQCLR_2_PP_CH3_LO_ISC_Msk, 1u);
}

INLINE void ADC1_PP_Ch4_UP_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_2.reg, (uint8)ADC1_IRQCLR_2_PP_CH4_UP_ISC_Pos, ADC1_IRQCLR_2_PP_CH4_UP_ISC_Msk, 1u);
}

INLINE void ADC1_PP_Ch4_LO_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_2.reg, (uint8)ADC1_IRQCLR_2_PP_CH4_LO_ISC_Pos, ADC1_IRQCLR_2_PP_CH4_LO_ISC_Msk, 1u);
}

INLINE void ADC1_PP_Ch5_UP_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_2.reg, (uint8)ADC1_IRQCLR_2_PP_CH5_UP_ISC_Pos, ADC1_IRQCLR_2_PP_CH5_UP_ISC_Msk, 1u);
}

INLINE void ADC1_PP_Ch5_LO_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_2.reg, (uint8)ADC1_IRQCLR_2_PP_CH5_LO_ISC_Pos, ADC1_IRQCLR_2_PP_CH5_LO_ISC_Msk, 1u);
}

INLINE void ADC1_PP_Ch6_UP_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_2.reg, (uint8)ADC1_IRQCLR_2_PP_CH6_UP_ISC_Pos, ADC1_IRQCLR_2_PP_CH6_UP_ISC_Msk, 1u);
}

INLINE void ADC1_PP_Ch6_LO_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_2.reg, (uint8)ADC1_IRQCLR_2_PP_CH6_LO_ISC_Pos, ADC1_IRQCLR_2_PP_CH6_LO_ISC_Msk, 1u);
}

INLINE void ADC1_PP_Ch7_UP_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_2.reg, (uint8)ADC1_IRQCLR_2_PP_CH7_UP_ISC_Pos, ADC1_IRQCLR_2_PP_CH7_UP_ISC_Msk, 1u);
}

INLINE void ADC1_PP_Ch7_LO_Int_Clr()
{
  Field_Wrt32(&ADC1->IRQCLR_2.reg, (uint8)ADC1_IRQCLR_2_PP_CH7_LO_ISC_Pos, ADC1_IRQCLR_2_PP_CH7_LO_ISC_Msk, 1u);
}

INLINE void ADC1_PP_Ch0_UP_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH0_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH0_UP_IEN_Msk, 1u);
}

INLINE void ADC1_PP_Ch0_UP_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH0_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH0_UP_IEN_Msk, 0u);
}

INLINE void ADC1_PP_Ch0_LO_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH0_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH0_LO_IEN_Msk, 1u);
}

INLINE void ADC1_PP_Ch0_LO_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH0_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH0_LO_IEN_Msk, 0u);
}

INLINE void ADC1_PP_Ch1_UP_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_VS_UP_IEN_Pos, ADC1_IRQEN_2_VS_UP_IEN_Msk, 1u);
}

INLINE void ADC1_PP_Ch1_UP_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_VS_UP_IEN_Pos, ADC1_IRQEN_2_VS_UP_IEN_Msk, 0u);
}

INLINE void ADC1_PP_Ch1_LO_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_VS_LO_IEN_Pos, ADC1_IRQEN_2_VS_LO_IEN_Msk, 1u);
}

INLINE void ADC1_PP_Ch1_LO_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_VS_LO_IEN_Pos, ADC1_IRQEN_2_VS_LO_IEN_Msk, 0u);
}

INLINE void ADC1_PP_Ch2_UP_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH2_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH2_UP_IEN_Msk, 1u);
}

INLINE void ADC1_PP_Ch2_UP_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH2_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH2_UP_IEN_Msk, 0u);
}

INLINE void ADC1_PP_Ch2_LO_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH2_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH2_LO_IEN_Msk, 1u);
}

INLINE void ADC1_PP_Ch2_LO_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH2_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH2_LO_IEN_Msk, 0u);
}

INLINE void ADC1_PP_Ch3_UP_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH3_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH3_UP_IEN_Msk, 1u);
}

INLINE void ADC1_PP_Ch3_UP_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH3_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH3_UP_IEN_Msk, 0u);
}

INLINE void ADC1_PP_Ch3_LO_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH3_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH3_LO_IEN_Msk, 1u);
}

INLINE void ADC1_PP_Ch3_LO_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH3_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH3_LO_IEN_Msk, 0u);
}

INLINE void ADC1_PP_Ch4_UP_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH4_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH4_UP_IEN_Msk, 1u);
}

INLINE void ADC1_PP_Ch4_UP_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH4_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH4_UP_IEN_Msk, 0u);
}

INLINE void ADC1_PP_Ch4_LO_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH4_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH4_LO_IEN_Msk, 1u);
}

INLINE void ADC1_PP_Ch4_LO_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH4_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH4_LO_IEN_Msk, 0u);
}

INLINE void ADC1_PP_Ch5_UP_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH5_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH5_UP_IEN_Msk, 1u);
}

INLINE void ADC1_PP_Ch5_UP_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH5_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH5_UP_IEN_Msk, 0u);
}

INLINE void ADC1_PP_Ch5_LO_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH5_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH5_LO_IEN_Msk, 1u);
}

INLINE void ADC1_PP_Ch5_LO_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH5_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH5_LO_IEN_Msk, 0u);
}

INLINE void ADC1_PP_Ch6_UP_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH6_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH6_UP_IEN_Msk, 1u);
}

INLINE void ADC1_PP_Ch6_UP_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH6_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH6_UP_IEN_Msk, 0u);
}

INLINE void ADC1_PP_Ch6_LO_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH6_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH6_LO_IEN_Msk, 1u);
}

INLINE void ADC1_PP_Ch6_LO_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH6_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH6_LO_IEN_Msk, 0u);
}

INLINE void ADC1_PP_Ch7_UP_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH7_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH7_UP_IEN_Msk, 1u);
}

INLINE void ADC1_PP_Ch7_UP_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH7_UP_IEN_Pos, ADC1_IRQEN_2_PP_CH7_UP_IEN_Msk, 0u);
}

INLINE void ADC1_PP_Ch7_LO_Int_En()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH7_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH7_LO_IEN_Msk, 1u);
}

INLINE void ADC1_PP_Ch7_LO_Int_Dis()
{
  Field_Mod32(&ADC1->IRQEN_2.reg, (uint8)ADC1_IRQEN_2_PP_CH7_LO_IEN_Pos, ADC1_IRQEN_2_PP_CH7_LO_IEN_Msk, 0u);
}

INLINE void ADC1_Offset_Calib_Set(uint8 value)
{
  Field_Mod32(&ADC1->OFFSETCALIB.reg, (uint8)ADC1_OFFSETCALIB_OFFSET_DAC_Pos, ADC1_OFFSETCALIB_OFFSET_DAC_Msk, value);
}

INLINE void ADC1_Offset_Shift_Set(uint8 value)
{
  Field_Mod32(&ADC1->OFFSETCALIB.reg, (uint8)ADC1_OFFSETCALIB_OFFSET_SHIFT_Pos, ADC1_OFFSETCALIB_OFFSET_SHIFT_Msk, value);
}

INLINE void ADC1_Sig_Del_feed_Loop_En()
{
  Field_Mod32(&ADC1->STATUS.reg, (uint8)ADC1_STATUS_SD_FEEDB_ON_Pos, ADC1_STATUS_SD_FEEDB_ON_Msk, 1u);
}

INLINE void ADC1_Soc_Clk_Jitter_Set(uint8 clk)
{
  Field_Mod32(&ADC1->STATUS.reg, (uint8)ADC1_STATUS_SOC_JITTER_Pos, ADC1_STATUS_SOC_JITTER_Msk, clk);
}

INLINE void ADC1_SetEIMChannel(uint8 channel)
{
  ADC1_EIM_Channel_Set(channel);
}

INLINE void ADC1_SetSwMode_Channel(uint8 channel)
{
  ADC1_SW_Channel_Sel(channel);
}

INLINE void ADC1_SetSosSwMode(uint8 channel)
{
  ADC1_SW_Channel_Sel(channel);
  ADC1_SOS_Set();
}

INLINE bool ADC1_GetEocSwMode()
{
  bool res = false;

  if (ADC1_EOC_Sts() == (uint8)1)
  {
    res = true;
  }
  return (res);
}

INLINE void ADC1_EIM_Trigger_Select(TADC1_TRIGG_SEL trigsel)
{
  Field_Mod32(&ADC1->CHx_EIM.reg, (uint8)ADC1_CHx_EIM_ADC1_EIM_TRIG_SEL_Pos, ADC1_CHx_EIM_ADC1_EIM_TRIG_SEL_Msk, (uint8)trigsel);
}

INLINE void ADC1_EIM_Repeat_Counter_Set(TADC1_EIM_REP_CNT repcnt)
{
  Field_Mod32(&ADC1->CHx_EIM.reg, (uint8)ADC1_CHx_EIM_EIM_REP_Pos, ADC1_CHx_EIM_EIM_REP_Msk, (uint8)repcnt);
}

INLINE void ADC1_ESM_Trigger_Select(TADC1_TRIGG_SEL trigsel)
{
  Field_Mod32(&ADC1->CHx_ESM.reg, (uint8)ADC1_CHx_ESM_ADC1_ESM_TRIG_SEL_Pos, ADC1_CHx_ESM_ADC1_ESM_TRIG_SEL_Msk, (uint8)trigsel);
}

INLINE bool ADC1_isEndOfConversion()
{
  bool res = false;

  if (ADC1_EOC_Sts() == (uint8)1)
  {
    res = true;
  }
  return (res);
}

INLINE bool ADC1_isEIMactive()
{
  bool res = false;

  if (ADC1_EIM_Active_Sts() == (uint8)1)
  {
    res = true;
  }
  return (res);
}

INLINE bool ADC1_isESMactive()
{
  bool res = false;

  if (ADC1_ESM_Active_Sts() == (uint8)1)
  {
    res = true;
  }
  return (res);
}

#endif /* ADC1_H */
