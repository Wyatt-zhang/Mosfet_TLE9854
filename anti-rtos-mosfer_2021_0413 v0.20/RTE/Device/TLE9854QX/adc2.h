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
 * \file     adc2.h
 *
 * \brief    ADC2 low level access library
 *
 * \version  V0.3.3
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
** KC           Kay Claussen                                                  **
** BG           Blandine Guillot                                              **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V0.2.0: 2018-02-13, TS:   Initial version of revision history              **
** V0.3.0: 2018-06-27, KC:   ADC2_VS_OV_Int_Clr, ADC2_VS_UV_Int_Clr corrected **
**                           Calculation of voltage for CH3 and CH4 corrected **
** V0.3.1: 2018-10-17, TS:   FILT_UPLO_CTRL initialization added              **
** V0.3.2: 2019-01-28, TS:   __STATIC_INLINE changed to INLINE                **   
**                           Doxygen update                                   **
**                           Revision history moved from adc2.c to adc2.h     **
**                           ADC2_GetChResult updated (adding a condition)    **
** V0.3.3: 2020-03-02, BG:   Updated revision history format                  **
*******************************************************************************/

#ifndef ADC2_H
#define ADC2_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle985x.h"
#include "types.h"
#include "sfr_access.h"

/*******************************************************************************
**                        Global Constant Declarations                        **
*******************************************************************************/
/**\brief ADC2 reference voltage 1.21V */
#define ADC2_VREF (1.211F)

/**\brief ADC2 channel selection macro, channel 0 - VS */
#define ADC2_VS         (0)
/**\brief ADC2 channel selection macro, channel 1 - VSD */
#define ADC2_VSD        (1)
/**\brief ADC2 channel selection macro, channel 2 - VCP */
#define ADC2_VCP        (2)
/**\brief ADC2 channel selection macro, channel 3 - VDDEXT */
#define ADC2_VDDEXT     (3)
/**\brief ADC2 channel selection macro, channel 4 - VDDP */
#define ADC2_VDDP       (4)
/**\brief ADC2 channel selection macro, channel 5 - VBG */
#define ADC2_VBG        (5)
/**\brief ADC2 channel selection macro, channel 6 - VDDC */
#define ADC2_VDDC       (6)
/**\brief ADC2 channel selection macro, channel 7 - TEMP1 */
#define ADC2_TEMP1      (7)
/**\brief ADC2 channel selection macro, channel 8 - TEMP2 */
#define ADC2_TEMP2      (8)


/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/
/** \brief Initializes the ADC2 based on the Config Wizard configuration.
 *
 * \ingroup adc2_api
 */
void ADC2_Init(void);

/*******************************************************************************
**                        Inline Function Declarations                        **
*******************************************************************************/
/** \brief Returns the 10 bit wide result of the selected ADC2 channel
 * \brief Returns 0 if the selected channel number is greater than 8
 *
 * \param channel selected ADC2 channel number (0 to 8)
 * \return 10 bit wide result of the selected channel (FILT_OUT0 to FILT_OUT8)
 *
 * \brief <b>Example</b><br>
 * \brief This example returns the ADC2 Channel 4 result.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 data;
 *
 *     data = ADC2_GetChResult(ADC2_VDDP);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE uint16 ADC2_GetChResult(uint8 channel);

/** \brief Returns the Result in mV of the selected ADC2 Channels 0-6
 * \brief calculated based on attenuator conversion factor
 *
 * \return ADC2 result values in mV
 *
 * \brief <b>Example</b><br>
 * \brief This example returns the ADC2 Channel 5 result in Milli Volt (mV).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint16 data;
 *
 *     data = ADC2_GetChResult_mV(ADC2_VBG);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE uint16 ADC2_GetChResult_mV(uint8 channel);

/** \brief Returns the Result in degrees celsius of the selected ADC2 channels 7-8
 *
 * \return ADC2 result values in degrees celsius
 *
 * \brief <b>Example</b><br>
 * \brief This example returns the ADC2 Channel 7 result in degrees celsius.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     sint16 data;
 *
 *     data = ADC2_GetChResult_C(ADC2_TEMP1);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE sint16 ADC2_GetChResult_C(uint8 channel);

/** \brief Starts an ADC2 Conversion, for Software mode only.
 *
 * \brief <b>Example</b><br>
 * \brief This example starts an ADC2 conversion on channel 6 - VDDC.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC2_SW_Channel_Sel(ADC2_VDDC);
 *     ADC2_SOS_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC2_api
 */
INLINE void ADC2_SOS_Set(void);

/** \brief Selects ADC2 channel for the software conversion.
 *
 * \param channel ADC2 channel which should be measured
 *
 * \brief <b>Example</b><br>
 * \brief This example starts an ADC2 conversion on channel 6 - VDDC.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC2_SW_Channel_Sel(ADC2_VDDC);
 *     ADC2_SOS_Set();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC2_api
 */
INLINE void ADC2_SW_Channel_Sel(uint8 channel);

/** \brief Sets ADC2 maximum time in software mode.
 *
 * \param time maximum time
 *
 * \brief <b>Example</b><br>
 * \brief This example actives Software mode for 257 clock cycles.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC2_SW_Max_Time_Set(0xFF);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC2_api
 */
INLINE void ADC2_SW_Max_Time_Set(uint8 time);

/** \brief enables Exceptional interrupt measurement (EIM) Trigger Event.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables the Exceptional Interrupt Measurement for channel 4.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_EIM_En();
 *   ADC2_EIM_Channel_Set(ADC2_VDDP);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC2_api
 */
INLINE void ADC2_EIM_En(void);

/** \brief Disables Exceptional interrupt measurement (EIM) Trigger Event.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables the Exceptional Interrupt Measurement.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_EIM_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC2_api
 */
INLINE void ADC2_EIM_Dis(void);

/** \brief Sets EIM channel for measurement.
 *
 * \param channel ADC2 channel to be measured
 *
 * \brief <b>Example</b><br>
 * \brief This example enables the Exceptional Interrupt Measurement for channel 4.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_EIM_En();
 *   ADC2_EIM_Channel_Set(ADC2_VDDP);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC2_api
 */
INLINE void ADC2_EIM_Channel_Set(uint8 channel);

/** \brief Selects Exceptional interrupt measurement (EIM) GPT12 Trigger.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects the Exceptional Interrupt Measurement GPT12 Trigger.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_EIM_T3_GPT12_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC2_api
 */
INLINE void ADC2_EIM_T3_GPT12_Sel(void);

/** \brief Selects Exceptional interrupt measurement (EIM) CP_clk Trigger.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects the Exceptional Interrupt Measurement CP_clk Trigger.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_EIM_CP_Clk_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup ADC2_api
 */
INLINE void ADC2_EIM_CP_Clk_Sel(void);

/** \brief Clears VS Overvoltage interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VS Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VS_OV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VS_OV_IS == 1u)
 *   {
 *     ADC2_VS_UP_CALLBACK();
 *     ADC2_VS_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VS_OV_Int_Clr(void);

/** \brief Clears VS Undervoltage interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VS Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VS_UV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VS_UV_IS == 1u)
 *   {
 *     ADC2_VS_LO_CALLBACK();
 *     ADC2_VS_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VS_UV_Int_Clr(void);

/** \brief Clears VDDP Overvoltage interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDP Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDP_OV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDD5V_OV_IS == 1u)
 *   {
 *     ADC2_VDDP_UP_CALLBACK();
 *     ADC2_VDDP_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDP_OV_Int_Clr(void);

/** \brief Clears VDDP Undervoltage interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDP Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDP_UV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDD5V_UV_IS == 1u)
 *   {
 *     ADC2_VDDP_LO_CALLBACK();
 *     ADC2_VDDP_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDP_UV_Int_Clr(void);

/** \brief Clears VDDC Overvoltage interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDC Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDC_OV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDD1V5_OV_IS == 1u)
 *   {
 *     ADC2_VDDC_UP_CALLBACK();
 *     ADC2_VDDC_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDC_OV_Int_Clr(void);

/** \brief Clears VDDC Undervoltage interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDC Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDC_UV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDD1V5_UV_IS == 1u)
 *   {
 *     ADC2_VDDC_LO_CALLBACK();
 *     ADC2_VDDC_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDC_UV_Int_Clr(void);

/** \brief Clears VDDEXT Overvoltage interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDEXT Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDEXT_OV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDDEXT_OV_IS == 1u)
 *   {
 *     ADC2_VDDEXT_UP_CALLBACK();
 *     ADC2_VDDEXT_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDEXT_OV_Int_Clr(void);

/** \brief Clears VDDEXT Undervoltage interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDEXT Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDEXT_UV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDDEXT_UV_IS == 1u)
 *   {
 *     ADC2_VDDEXT_LO_CALLBACK();
 *     ADC2_VDDEXT_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDEXT_UV_Int_Clr(void);

/** \brief Clears Driver Supply MU High interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Driver Supply MU High interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VSD_OV_Int_En();
 *   if (BDRV->CP_IRQS.bit.VSD_UPTH_IS == 1u)
 *   {
 *     ADC2_VSD_UP_CALLBACK();
 *     ADC2_VSD_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VSD_OV_Int_Clr(void);

/** \brief Clears Driver Supply MU Low interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Driver Supply MU Low interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VSD_UV_Int_En();
 *   if (BDRV->CP_IRQS.bit.VSD_LOTH_IS == 1u)
 *   {
 *     ADC2_VSD_LO_CALLBACK();
 *     ADC2_VSD_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VSD_UV_Int_Clr(void);

/** \brief Clears Charge Pump MU High interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Charge Pump MU High interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VCP_OV_Int_En();
 *   if (BDRV->CP_IRQS.bit.VCP_UPTH_IS == 1u)
 *   {
 *     ADC2_VCP_UP_CALLBACK();
 *     ADC2_VCP_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VCP_OV_Int_Clr(void);

/** \brief Clears Charge Pump MU Low interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Charge Pump MU Low interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VCP_UV_Int_En();
 *   if (BDRV->CP_IRQS.bit.VCP_LOTH_IS == 1u)
 *   {
 *     ADC2_VCP_LO_CALLBACK();
 *     ADC2_VCP_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VCP_UV_Int_Clr(void);

/** \brief Clears 8 Bit ADC2 Reference Overvoltage interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the 8 Bit ADC2 Reference Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VBG_OV_Int_En();
 *   if (SCUPM->SYS_IS.bit.VREF1V2_OV_IS == 1u)
 *   {
 *     ADC2_VBG_UP_CALLBACK();
 *     ADC2_VBG_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VBG_OV_Int_Clr(void);

/** \brief Clears 8 Bit ADC2 Reference Overvoltage interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the 8 Bit ADC2 Reference Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VBG_UV_Int_En();
 *   if (SCUPM->SYS_IS.bit.VREF1V2_UV_IS == 1u)
 *   {
 *     ADC2_VBG_LO_CALLBACK();
 *     ADC2_VBG_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VBG_UV_Int_Clr(void);

/** \brief Clears System Overtemperature Shutdown interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the System Overtemperature Shutdown interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_Temp_OT_Int_En();
 *   if (SCUPM->SYS_IS.bit.SYS_OT_IS == 1u)
 *   {
 *     ADC2_SYS_TEMP_UP_CALLBACK();
 *     ADC2_TEMP_OT_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_TEMP_OT_Int_Clr(void);

/** \brief Clears System Overtemperature Prewarning interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the System Overtemperature Prewarning interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_Temp_Warn_Int_En();
 *   if (SCUPM->SYS_IS.bit.SYS_OTWARN_IS == 1u)
 *   {
 *     ADC2_SYS_TEMP_LO_CALLBACK();
 *     ADC2_TEMP_WARN_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_TEMP_WARN_Int_Clr(void);

/** \brief Clears Charge Pump Over-temperature Warning interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Charge Pump Over-temperature Warning interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VCP_OTW_Int_En();
 *   if (BDRV->CP_IRQS.bit.VCP_OTW_IS == 1u)
 *   {
 *     ADC2_CP_TEMP_LO_CALLBACK();
 *     BDRV_VCP_OTW_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void BDRV_VCP_OTW_Int_Clr(void);

/** \brief Clears Charge Pump Over-temperature Shutdown interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Charge Pump Over-temperature Shutdown interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VCP_OTSD_Int_En();
 *   if (BDRV->CP_IRQS.bit.VCP_OTSD_IS == 1u)
 *   {
 *     ADC2_CP_TEMP_UP_CALLBACK();
 *     BDRV_VCP_OTSD_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void BDRV_VCP_OTSD_Int_Clr(void);

/** \brief Enables VS Overvoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VS Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VS_OV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VS_OV_IS == 1u)
 *   {
 *     ADC2_VS_UP_CALLBACK();
 *     ADC2_VS_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VS_OV_Int_En(void);

/** \brief Disables VS Overvoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VS Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VS_OV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VS_OV_IS == 1u)
 *   {
 *     ADC2_VS_UP_CALLBACK();
 *     ADC2_VS_OV_Int_Clr();
 *   }
 *   ADC2_VS_OV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VS_OV_Int_Dis(void);

/** \brief Enables VS Undervoltage interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VS Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VS_UV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VS_UV_IS == 1u)
 *   {
 *     ADC2_VS_LO_CALLBACK();
 *     ADC2_VS_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VS_UV_Int_En(void);

/** \brief Disables VS Undervoltage interrupt flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VS Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VS_UV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VS_UV_IS == 1u)
 *   {
 *     ADC2_VS_LO_CALLBACK();
 *     ADC2_VS_UV_Int_Clr();
 *   }
 *   ADC2_VS_UV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VS_UV_Int_Dis(void);

/** \brief Enables VDDP Overvoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDP Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDP_OV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDD5V_OV_IS == 1u)
 *   {
 *     ADC2_VDDP_UP_CALLBACK();
 *     ADC2_VDDP_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDP_OV_Int_En(void);

/** \brief Disables VDDP Overvoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDP Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDP_OV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDD5V_OV_IS == 1u)
 *   {
 *     ADC2_VDDP_UP_CALLBACK();
 *     ADC2_VDDP_OV_Int_Clr();
 *   }
 *   ADC2_VDDP_OV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDP_OV_Int_Dis(void);

/** \brief Enables VDDP Undervoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDP Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDP_UV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDD5V_UV_IS == 1u)
 *   {
 *     ADC2_VDDP_LO_CALLBACK();
 *     ADC2_VDDP_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDP_UV_Int_En(void);

/** \brief Disables VDDP Undervoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDP Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDP_UV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDD5V_UV_IS == 1u)
 *   {
 *     ADC2_VDDP_LO_CALLBACK();
 *     ADC2_VDDP_UV_Int_Clr();
 *   }
 *   ADC2_VDDP_UV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDP_UV_Int_Dis(void);

/** \brief Enables VDDC Overvoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDC Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDC_OV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDD1V5_OV_IS == 1u)
 *   {
 *     ADC2_VDDC_UP_CALLBACK();
 *     ADC2_VDDC_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDC_OV_Int_En(void);

/** \brief Disables VDDC Overvoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDC Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDC_OV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDD1V5_OV_IS == 1u)
 *   {
 *     ADC2_VDDC_UP_CALLBACK();
 *     ADC2_VDDC_OV_Int_Clr();
 *   }
 *   ADC2_VDDC_OV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDC_OV_Int_Dis(void);

/** \brief Enables VDDC Undervoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDC Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDC_UV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDD1V5_UV_IS == 1u)
 *   {
 *     ADC2_VDDC_LO_CALLBACK();
 *     ADC2_VDDC_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDC_UV_Int_En(void);

/** \brief Disables VDDC Undervoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDC Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDC_UV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDD1V5_UV_IS == 1u)
 *   {
 *     ADC2_VDDC_LO_CALLBACK();
 *     ADC2_VDDC_UV_Int_Clr();
 *   }
 *   ADC2_VDDC_UV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDC_UV_Int_Dis(void);

/** \brief Enables VDDEXT Overvoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDEXT Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDEXT_OV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDDEXT_OV_IS == 1u)
 *   {
 *     ADC2_VDDEXT_UP_CALLBACK();
 *     ADC2_VDDEXT_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDEXT_OV_Int_En(void);

/** \brief Disables VDDEXT Overvoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDEXT Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDEXT_OV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDDEXT_OV_IS == 1u)
 *   {
 *     ADC2_VDDEXT_UP_CALLBACK();
 *     ADC2_VDDEXT_OV_Int_Clr();
 *   }
 *   ADC2_VDDEXT_OV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDEXT_OV_Int_Dis(void);

/** \brief Enables VDDEXT Undervoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDEXT Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDEXT_UV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDDEXT_UV_IS == 1u)
 *   {
 *     ADC2_VDDEXT_LO_CALLBACK();
 *     ADC2_VDDEXT_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDEXT_UV_Int_En(void);

/** \brief Disables VDDEXT Undervoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the VDDEXT Undervoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VDDEXT_UV_Int_En();
 *   if (SCUPM->SYS_SUPPLY_IRQ_STS.bit.VDDEXT_UV_IS == 1u)
 *   {
 *     ADC2_VDDEXT_LO_CALLBACK();
 *     ADC2_VDDEXT_UV_Int_Clr();
 *   }
 *   ADC2_VDDEXT_UV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VDDEXT_UV_Int_Dis(void);

/** \brief Enables Driver Supply MU High interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Driver Supply MU High interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VSD_OV_Int_En();
 *   if (BDRV->CP_IRQS.bit.VSD_UPTH_IS == 1u)
 *   {
 *     ADC2_VSD_UP_CALLBACK();
 *     ADC2_VSD_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VSD_OV_Int_En(void);

/** \brief Disables Driver Supply MU High interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Driver Supply MU High interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VSD_OV_Int_En();
 *   if (BDRV->CP_IRQS.bit.VSD_UPTH_IS == 1u)
 *   {
 *     ADC2_VSD_UP_CALLBACK();
 *     ADC2_VSD_OV_Int_Clr();
 *   }
 *   ADC2_VSD_OV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VSD_OV_Int_Dis(void);

/** \brief Enables Driver Supply MU Low interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Driver Supply MU Low interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VSD_UV_Int_En();
 *   if (BDRV->CP_IRQS.bit.VSD_LOTH_IS == 1u)
 *   {
 *     ADC2_VSD_LO_CALLBACK();
 *     ADC2_VSD_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VSD_UV_Int_En(void);

/** \brief Disables Driver Supply MU Low interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Driver Supply MU Low interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VSD_UV_Int_En();
 *   if (BDRV->CP_IRQS.bit.VSD_LOTH_IS == 1u)
 *   {
 *     ADC2_VSD_LO_CALLBACK();
 *     ADC2_VSD_UV_Int_Clr();
 *   }
 *   ADC2_VSD_UV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VSD_UV_Int_Dis(void);

/** \brief Enables Charge Pump MU High interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Charge Pump MU High interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VCP_OV_Int_En();
 *   if (BDRV->CP_IRQS.bit.VCP_UPTH_IS == 1u)
 *   {
 *     ADC2_VCP_UP_CALLBACK();
 *     ADC2_VCP_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VCP_OV_Int_En(void);

/** \brief Disables Charge Pump MU High interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Charge Pump MU High interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VCP_OV_Int_En();
 *   if (BDRV->CP_IRQS.bit.VCP_UPTH_IS == 1u)
 *   {
 *     ADC2_VCP_UP_CALLBACK();
 *     ADC2_VCP_OV_Int_Clr();
 *   }
 *   ADC2_VCP_OV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VCP_OV_Int_Dis(void);

/** \brief Enables Charge Pump MU Low interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Charge Pump MU Low interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VCP_UV_Int_En();
 *   if (BDRV->CP_IRQS.bit.VCP_LOTH_IS == 1u)
 *   {
 *     ADC2_VCP_LO_CALLBACK();
 *     ADC2_VCP_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VCP_UV_Int_En(void);

/** \brief Disables Charge Pump MU Low interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Charge Pump MU Low interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VCP_UV_Int_En();
 *   if (BDRV->CP_IRQS.bit.VCP_LOTH_IS == 1u)
 *   {
 *     ADC2_VCP_LO_CALLBACK();
 *     ADC2_VCP_UV_Int_Clr();
 *   }
 *   ADC2_VCP_UV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VCP_UV_Int_Dis(void);

/** \brief Enables 8 Bit ADC2 Reference Overvoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the 8 Bit ADC2 Reference Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VBG_OV_Int_En();
 *   if (SCUPM->SYS_IS.bit.VREF1V2_OV_IS == 1u)
 *   {
 *     ADC2_VBG_UP_CALLBACK();
 *     ADC2_VBG_OV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VBG_OV_Int_En(void);

/** \brief Disables 8 Bit ADC2 Reference Overvoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the 8 Bit ADC2 Reference Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VBG_OV_Int_En();
 *   if (SCUPM->SYS_IS.bit.VREF1V2_OV_IS == 1u)
 *   {
 *     ADC2_VBG_UP_CALLBACK();
 *     ADC2_VBG_OV_Int_Clr();
 *   }
 *   ADC2_VBG_OV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VBG_OV_Int_Dis(void);

/** \brief Enables 8 Bit ADC2 Reference Overvoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the 8 Bit ADC2 Reference Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VBG_UV_Int_En();
 *   if (SCUPM->SYS_IS.bit.VREF1V2_UV_IS == 1u)
 *   {
 *     ADC2_VBG_LO_CALLBACK();
 *     ADC2_VBG_UV_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VBG_UV_Int_En(void);

/** \brief Disables 8 Bit ADC2 Reference Overvoltage interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the 8 Bit ADC2 Reference Overvoltage interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VBG_UV_Int_En();
 *   if (SCUPM->SYS_IS.bit.VREF1V2_UV_IS == 1u)
 *   {
 *     ADC2_VBG_LO_CALLBACK();
 *     ADC2_VBG_UV_Int_Clr();
 *   }
 *   ADC2_VBG_UV_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VBG_UV_Int_Dis(void);

/** \brief Enables System Overtemperature Shutdown interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the System Overtemperature Shutdown interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_Temp_OT_Int_En();
 *   if (SCUPM->SYS_IS.bit.SYS_OT_IS == 1u)
 *   {
 *     ADC2_SYS_TEMP_UP_CALLBACK();
 *     ADC2_TEMP_OT_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_Temp_OT_Int_En(void);

/** \brief Disables System Overtemperature Shutdown interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the System Overtemperature Shutdown interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_Temp_OT_Int_En();
 *   if (SCUPM->SYS_IS.bit.SYS_OT_IS == 1u)
 *   {
 *     ADC2_SYS_TEMP_UP_CALLBACK();
 *     ADC2_TEMP_OT_Int_Clr();
 *   }
 *   ADC2_Temp_OT_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_Temp_OT_Int_Dis(void);

/** \brief Enables System Overtemperature Prewarning interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the System Overtemperature Prewarning interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_Temp_Warn_Int_En();
 *   if (SCUPM->SYS_IS.bit.SYS_OTWARN_IS == 1u)
 *   {
 *     ADC2_SYS_TEMP_LO_CALLBACK();
 *     ADC2_TEMP_WARN_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_Temp_Warn_Int_En(void);

/** \brief Disables System Overtemperature Prewarning interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the System Overtemperature Prewarning interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_Temp_Warn_Int_En();
 *   if (SCUPM->SYS_IS.bit.SYS_OTWARN_IS == 1u)
 *   {
 *     ADC2_SYS_TEMP_LO_CALLBACK();
 *     ADC2_TEMP_WARN_Int_Clr();
 *   }
 *   ADC2_Temp_Warn_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_Temp_Warn_Int_Dis(void);

/** \brief Enables Charge Pump Over-temperature Warning interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Charge Pump Over-temperature Warning interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VCP_OTW_Int_En();
 *   if (BDRV->CP_IRQS.bit.VCP_OTW_IS == 1u)
 *   {
 *     ADC2_CP_TEMP_LO_CALLBACK();
 *     BDRV_VCP_OTW_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VCP_OTW_Int_En(void);

/** \brief Disables Charge Pump Over-temperature Warning interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Charge Pump Over-temperature Warning interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VCP_OTW_Int_En();
 *   if (BDRV->CP_IRQS.bit.VCP_OTW_IS == 1u)
 *   {
 *     ADC2_CP_TEMP_LO_CALLBACK();
 *     BDRV_VCP_OTW_Int_Clr();
 *   }
 *   ADC2_VCP_OTW_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VCP_OTW_Int_Dis(void);

/** \brief Enables Charge Pump Over-temperature Shutdown interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Charge Pump Over-temperature Shutdown interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VCP_OTSD_Int_En();
 *   if (BDRV->CP_IRQS.bit.VCP_OTSD_IS == 1u)
 *   {
 *     ADC2_CP_TEMP_UP_CALLBACK();
 *     BDRV_VCP_OTSD_Int_Clr();
 *   }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VCP_OTSD_Int_En(void);

/** \brief Disables Charge Pump Over-temperature Shutdown interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Charge Pump Over-temperature Shutdown interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   ADC2_VCP_OTSD_Int_En();
 *   if (BDRV->CP_IRQS.bit.VCP_OTSD_IS == 1u)
 *   {
 *     ADC2_CP_TEMP_UP_CALLBACK();
 *     BDRV_VCP_OTSD_Int_Clr();
 *   }
 *   ADC2_VCP_OTSD_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup adc2_api
 */
INLINE void ADC2_VCP_OTSD_Int_Dis(void);


/*******************************************************************************
**                         Inline Function Definitions                        **
*******************************************************************************/
INLINE uint16 ADC2_GetChResult(uint8 channel)
{
  uint16 Var;
  uint32 addr;
  
  if((uint8)ADC2_TEMP2 >= channel)
  {  
    addr = (uint32)&ADC2->FILT_OUT0.reg;
    addr += (uint32)channel * 4u;
    Var = u16_Field_Rd32((uint32*)addr, (uint8)ADC2_FILT_OUT0_OUT_CH0_Pos, ADC2_FILT_OUT0_OUT_CH0_Msk);

  }
  else
  {
    Var = 0;
  }

  return (Var);
}

INLINE uint16 ADC2_GetChResult_mV(uint8 channel)
{
  uint16 var;
  uint32 fs = 0u;
  uint16 res;
  
  var = ADC2_GetChResult(channel);
  if (channel < 2u)
  {
    /* 1.211 * 1000 / 0.039 / 1024 * 1024 */
    fs = 31051;                  /* ch0+1 in mV */
  }
  else if (channel < 3u)
  {
    /* 1.211 * 1000 / 0.023 */
    fs = 52652;                   /* ch2 in mV */
  }
  else if (channel < 5u)
  {
    /* 1.211 * 1000 / 0.195 */
    fs = 6210;                   /* ch3+4 in mV */
  }
  else if (channel < 7u)
  {
    /* 1.211 * 1000 / 0.75 */
    fs = 1615;                   /* ch5+6 in mV */
  }
  else
  {
    res = 0u;                /* invalid channel */
  }
  
  /* Calculate mV = var * fs / 1024 */
  if (var > 0u)
  {
    res = (uint16)((uint32)((uint32)(var * fs) - (uint32)(fs / 2u)) / (uint16)1024u); /* calculate voltage in mV */;
  }
  else
  {
    res = 0u; /* calculate voltage in mV */;
  }
  return(res);
}

INLINE sint16 ADC2_GetChResult_C(uint8 channel)
{
  uint16 var;
  sint16 res;

  var = ADC2_GetChResult(channel);

  if ((6u < channel) && (channel < 9u))
  {
    /* Calculate temperature in °C = (var*131-69662) / 256 */
    res = (sint16)((((sint32)((sint32)(131) * (sint32)var)) - (sint32)69662) / (sint16)256);    
  }
  else
  {
    res = 0;                /* invalid channel */
  }
  return(res);
}

INLINE void ADC2_SOS_Set()
{
  Field_Mod32(&ADC2->CTRL_STS.reg, (uint8)ADC2_CTRL_STS_SOS_Pos, ADC2_CTRL_STS_SOS_Msk, 1u);
}

INLINE void ADC2_SW_Channel_Sel(uint8 channel)
{
  Field_Mod32(&ADC2->CTRL_STS.reg, (uint8)ADC2_CTRL_STS_IN_MUX_SEL_Pos, ADC2_CTRL_STS_IN_MUX_SEL_Msk, channel);
}

INLINE void ADC2_SW_Max_Time_Set(uint8 time)       
{
  Field_Wrt32(&ADC2->MAX_TIME.reg, (uint8)ADC2_MAX_TIME_MAX_TIME_Pos, ADC2_MAX_TIME_MAX_TIME_Msk, time);
}

INLINE void ADC2_EIM_En()
{
  Field_Mod32(&ADC2->CHx_EIM.reg, (uint8)ADC2_CHx_EIM_EN_Pos, ADC2_CHx_EIM_EN_Msk, 1u);
}

INLINE void ADC2_EIM_Dis()
{
  Field_Mod32(&ADC2->CHx_EIM.reg, (uint8)ADC2_CHx_EIM_EN_Pos, ADC2_CHx_EIM_EN_Msk, 0u);
}

INLINE void ADC2_EIM_Channel_Set(uint8 channel)
{
  Field_Mod32(&ADC2->CHx_EIM.reg, (uint8)ADC2_CHx_EIM_CHx_SEL_Pos, ADC2_CHx_EIM_CHx_SEL_Msk, channel);
}

INLINE void ADC2_EIM_T3_GPT12_Sel()
{
  Field_Mod32(&ADC2->CHx_EIM.reg, (uint8)ADC2_CHx_EIM_SEL_Pos, ADC2_CHx_EIM_SEL_Msk, 0u);
}

INLINE void ADC2_EIM_CP_Clk_Sel()
{
  Field_Mod32(&ADC2->CHx_EIM.reg, (uint8)ADC2_CHx_EIM_SEL_Pos, ADC2_CHx_EIM_SEL_Msk, 1u);
}

INLINE void ADC2_VS_OV_Int_Clr()
{
  Field_Wrt32(&SCUPM->SYS_SUPPLY_IRQ_CLR.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CLR_VS_OV_ISC_Pos, SCUPM_SYS_SUPPLY_IRQ_CLR_VS_OV_ISC_Msk, 1u);
}

INLINE void ADC2_VS_UV_Int_Clr()
{
  Field_Wrt32(&SCUPM->SYS_SUPPLY_IRQ_CLR.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CLR_VS_UV_ISC_Pos, SCUPM_SYS_SUPPLY_IRQ_CLR_VS_UV_ISC_Msk, 1u);
}

INLINE void ADC2_VDDP_OV_Int_Clr()
{
  Field_Wrt32(&SCUPM->SYS_SUPPLY_IRQ_CLR.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CLR_VDD5V_OV_ISC_Pos, SCUPM_SYS_SUPPLY_IRQ_CLR_VDD5V_OV_ISC_Msk, 1u);
}

INLINE void ADC2_VDDP_UV_Int_Clr()
{
  Field_Wrt32(&SCUPM->SYS_SUPPLY_IRQ_CLR.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CLR_VDD5V_UV_ISC_Pos, SCUPM_SYS_SUPPLY_IRQ_CLR_VDD5V_UV_ISC_Msk, 1u);
}

INLINE void ADC2_VDDC_OV_Int_Clr()
{
  Field_Wrt32(&SCUPM->SYS_SUPPLY_IRQ_CLR.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CLR_VDD1V5_OV_ISC_Pos, SCUPM_SYS_SUPPLY_IRQ_CLR_VDD1V5_OV_ISC_Msk, 1u);
}

INLINE void ADC2_VDDC_UV_Int_Clr()
{
  Field_Wrt32(&SCUPM->SYS_SUPPLY_IRQ_CLR.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CLR_VDD1V5_UV_ISC_Pos, SCUPM_SYS_SUPPLY_IRQ_CLR_VDD1V5_UV_ISC_Msk, 1u);
}

INLINE void ADC2_VDDEXT_OV_Int_Clr()
{
  Field_Wrt32(&SCUPM->SYS_SUPPLY_IRQ_CLR.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CLR_VDDEXT_OV_ISC_Pos, SCUPM_SYS_SUPPLY_IRQ_CLR_VDDEXT_OV_ISC_Msk, 1u);
}

INLINE void ADC2_VDDEXT_UV_Int_Clr()
{
  Field_Wrt32(&SCUPM->SYS_SUPPLY_IRQ_CLR.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CLR_VDDEXT_UV_ISC_Pos, SCUPM_SYS_SUPPLY_IRQ_CLR_VDDEXT_UV_ISC_Msk, 1u);
}

INLINE void ADC2_VSD_OV_Int_Clr()
{
  Field_Wrt32(&BDRV->CP_IRQCLR.reg, (uint8)BDRV_CP_IRQCLR_VSD_UPTH_ISC_Pos, BDRV_CP_IRQCLR_VSD_UPTH_ISC_Msk, 1u);
}

INLINE void ADC2_VSD_UV_Int_Clr()
{
  Field_Wrt32(&BDRV->CP_IRQCLR.reg, (uint8)BDRV_CP_IRQCLR_VSD_LOTH_ISC_Pos, BDRV_CP_IRQCLR_VSD_LOTH_ISC_Msk, 1u);
}

INLINE void ADC2_VCP_OV_Int_Clr()
{
  Field_Wrt32(&BDRV->CP_IRQCLR.reg, (uint8)BDRV_CP_IRQCLR_VCP_UPTH_ISC_Pos, BDRV_CP_IRQCLR_VCP_UPTH_ISC_Msk, 1u);
}

INLINE void ADC2_VCP_UV_Int_Clr()
{
  Field_Wrt32(&BDRV->CP_IRQCLR.reg, (uint8)BDRV_CP_IRQCLR_VCP_LOTH1_ISC_Pos, BDRV_CP_IRQCLR_VCP_LOTH1_ISC_Msk, 1u);
}

INLINE void ADC2_VBG_OV_Int_Clr()
{
  Field_Wrt32(&SCUPM->SYS_ISCLR.reg, (uint8)SCUPM_SYS_ISCLR_VREF1V2_OV_ISC_Pos, SCUPM_SYS_ISCLR_VREF1V2_OV_ISC_Msk, 1u);
}

INLINE void ADC2_VBG_UV_Int_Clr()
{
  Field_Wrt32(&SCUPM->SYS_ISCLR.reg, (uint8)SCUPM_SYS_ISCLR_VREF1V2_UV_ISC_Pos, SCUPM_SYS_ISCLR_VREF1V2_UV_ISC_Msk, 1u);
}

INLINE void ADC2_TEMP_OT_Int_Clr()
{
  Field_Wrt32(&SCUPM->SYS_ISCLR.reg, (uint8)SCUPM_SYS_ISCLR_SYS_OT_ISC_Pos, SCUPM_SYS_ISCLR_SYS_OT_ISC_Msk, 1u);
}

INLINE void ADC2_TEMP_WARN_Int_Clr()
{
  Field_Wrt32(&SCUPM->SYS_ISCLR.reg, (uint8)SCUPM_SYS_ISCLR_SYS_OTWARN_ISC_Pos, SCUPM_SYS_ISCLR_SYS_OTWARN_ISC_Msk, 1u);
}

INLINE void BDRV_VCP_OTW_Int_Clr()
{
  Field_Wrt32(&BDRV->CP_IRQCLR.reg, (uint8)BDRV_CP_IRQCLR_VCP_OTW_ISC_Pos, BDRV_CP_IRQCLR_VCP_OTW_ISC_Msk, 1u);
}

INLINE void BDRV_VCP_OTSD_Int_Clr()
{
  Field_Wrt32(&BDRV->CP_IRQCLR.reg, (uint8)BDRV_CP_IRQCLR_VCP_OTSD_ISC_Pos, BDRV_CP_IRQCLR_VCP_OTSD_ISC_Msk, 1u);
}

INLINE void ADC2_VS_OV_Int_En()
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CTRL_VS_OV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VS_OV_IE_Msk, 1u);
}

INLINE void ADC2_VS_OV_Int_Dis()
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CTRL_VS_OV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VS_OV_IE_Msk, 0u);
}

INLINE void ADC2_VS_UV_Int_En()
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CTRL_VS_UV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VS_UV_IE_Msk, 1u);
}

INLINE void ADC2_VS_UV_Int_Dis()
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CTRL_VS_UV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VS_UV_IE_Msk, 0u);
}

INLINE void ADC2_VDDP_OV_Int_En()
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD5V_OV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD5V_OV_IE_Msk, 1u);
}

INLINE void ADC2_VDDP_OV_Int_Dis()
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD5V_OV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD5V_OV_IE_Msk, 0u);
}

INLINE void ADC2_VDDP_UV_Int_En()
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD5V_UV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD5V_UV_IE_Msk, 1u);
}

INLINE void ADC2_VDDP_UV_Int_Dis()
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD5V_UV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD5V_UV_IE_Msk, 0u);
}

INLINE void ADC2_VDDC_OV_Int_En()
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD1V5_OV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD1V5_OV_IE_Msk, 1u);
}

INLINE void ADC2_VDDC_OV_Int_Dis()
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD1V5_OV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD1V5_OV_IE_Msk, 0u);
}

INLINE void ADC2_VDDC_UV_Int_En()
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD1V5_UV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD1V5_UV_IE_Msk, 1u);
}

INLINE void ADC2_VDDC_UV_Int_Dis()
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD1V5_UV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDD1V5_UV_IE_Msk, 0u);
}

INLINE void ADC2_VDDEXT_OV_Int_En()
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CTRL_VDDEXT_OV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDDEXT_OV_IE_Msk, 1u);
}

INLINE void ADC2_VDDEXT_OV_Int_Dis()
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CTRL_VDDEXT_OV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDDEXT_OV_IE_Msk, 0u);
}

INLINE void ADC2_VDDEXT_UV_Int_En()
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CTRL_VDDEXT_UV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDDEXT_UV_IE_Msk, 1u);
}

INLINE void ADC2_VDDEXT_UV_Int_Dis()
{
  Field_Mod32(&SCUPM->SYS_SUPPLY_IRQ_CTRL.reg, (uint8)SCUPM_SYS_SUPPLY_IRQ_CTRL_VDDEXT_UV_IE_Pos, SCUPM_SYS_SUPPLY_IRQ_CTRL_VDDEXT_UV_IE_Msk, 0u);
}

INLINE void ADC2_VSD_OV_Int_En()
{
  Field_Mod32(&BDRV->CP_IRQEN.reg, (uint8)BDRV_CP_IRQEN_VSD_UPTH_IEN_Pos, BDRV_CP_IRQEN_VSD_UPTH_IEN_Msk, 1u);
}

INLINE void ADC2_VSD_OV_Int_Dis()
{
  Field_Mod32(&BDRV->CP_IRQEN.reg, (uint8)BDRV_CP_IRQEN_VSD_UPTH_IEN_Pos, BDRV_CP_IRQEN_VSD_UPTH_IEN_Msk, 0u);
}

INLINE void ADC2_VSD_UV_Int_En()
{
  Field_Mod32(&BDRV->CP_IRQEN.reg, (uint8)BDRV_CP_IRQEN_VSD_LOTH_IEN_Pos, BDRV_CP_IRQEN_VSD_LOTH_IEN_Msk, 1u);
}

INLINE void ADC2_VSD_UV_Int_Dis()
{
  Field_Mod32(&BDRV->CP_IRQEN.reg, (uint8)BDRV_CP_IRQEN_VSD_LOTH_IEN_Pos, BDRV_CP_IRQEN_VSD_LOTH_IEN_Msk, 0u);
}

INLINE void ADC2_VCP_OV_Int_En()
{
  Field_Mod32(&BDRV->CP_IRQEN.reg, (uint8)BDRV_CP_IRQEN_VCP_UPTH_IEN_Pos, BDRV_CP_IRQEN_VCP_UPTH_IEN_Msk, 1u);
}

INLINE void ADC2_VCP_OV_Int_Dis()
{
  Field_Mod32(&BDRV->CP_IRQEN.reg, (uint8)BDRV_CP_IRQEN_VCP_UPTH_IEN_Pos, BDRV_CP_IRQEN_VCP_UPTH_IEN_Msk, 0u);
}

INLINE void ADC2_VCP_UV_Int_En()
{
  Field_Mod32(&BDRV->CP_IRQEN.reg, (uint8)BDRV_CP_IRQEN_VCP_LOTH1_IEN_Pos, BDRV_CP_IRQEN_VCP_LOTH1_IEN_Msk, 1u);
}

INLINE void ADC2_VCP_UV_Int_Dis()
{
  Field_Mod32(&BDRV->CP_IRQEN.reg, (uint8)BDRV_CP_IRQEN_VCP_LOTH1_IEN_Pos, BDRV_CP_IRQEN_VCP_LOTH1_IEN_Msk, 0u);
}

INLINE void ADC2_VBG_OV_Int_En()
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, (uint8)SCUPM_SYS_IRQ_CTRL_VREF1V2_OV_IE_Pos, SCUPM_SYS_IRQ_CTRL_VREF1V2_OV_IE_Msk, 1u);
}

INLINE void ADC2_VBG_OV_Int_Dis()
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, (uint8)SCUPM_SYS_IRQ_CTRL_VREF1V2_OV_IE_Pos, SCUPM_SYS_IRQ_CTRL_VREF1V2_OV_IE_Msk, 0u);
}

INLINE void ADC2_VBG_UV_Int_En()
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, (uint8)SCUPM_SYS_IRQ_CTRL_VREF1V2_UV_IE_Pos, SCUPM_SYS_IRQ_CTRL_VREF1V2_UV_IE_Msk, 1u);
}

INLINE void ADC2_VBG_UV_Int_Dis()
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, (uint8)SCUPM_SYS_IRQ_CTRL_VREF1V2_UV_IE_Pos, SCUPM_SYS_IRQ_CTRL_VREF1V2_UV_IE_Msk, 0u);
}

INLINE void ADC2_Temp_OT_Int_En()
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, (uint8)SCUPM_SYS_IRQ_CTRL_SYS_OT_IE_Pos, SCUPM_SYS_IRQ_CTRL_SYS_OT_IE_Msk, 1u);
}

INLINE void ADC2_Temp_OT_Int_Dis()
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, (uint8)SCUPM_SYS_IRQ_CTRL_SYS_OT_IE_Pos, SCUPM_SYS_IRQ_CTRL_SYS_OT_IE_Msk, 0u);
}

INLINE void ADC2_Temp_Warn_Int_En()
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, (uint8)SCUPM_SYS_IRQ_CTRL_SYS_OTWARN_IE_Pos, SCUPM_SYS_IRQ_CTRL_SYS_OTWARN_IE_Msk, 1u);
}

INLINE void ADC2_Temp_Warn_Int_Dis()
{
  Field_Mod32(&SCUPM->SYS_IRQ_CTRL.reg, (uint8)SCUPM_SYS_IRQ_CTRL_SYS_OTWARN_IE_Pos, SCUPM_SYS_IRQ_CTRL_SYS_OTWARN_IE_Msk, 0u);
}

INLINE void ADC2_VCP_OTW_Int_En()
{
  Field_Mod32(&BDRV->CP_IRQEN.reg, (uint8)BDRV_CP_IRQEN_VCP_OTW_IEN_Pos, BDRV_CP_IRQEN_VCP_OTW_IEN_Msk, 1u);
}

INLINE void ADC2_VCP_OTW_Int_Dis()
{
  Field_Mod32(&BDRV->CP_IRQEN.reg, (uint8)BDRV_CP_IRQEN_VCP_OTW_IEN_Pos, BDRV_CP_IRQEN_VCP_OTW_IEN_Msk, 0u);
}

INLINE void ADC2_VCP_OTSD_Int_En()
{
  Field_Mod32(&BDRV->CP_IRQEN.reg, (uint8)BDRV_CP_IRQEN_VCP_OTSD_IEN_Pos, BDRV_CP_IRQEN_VCP_OTSD_IEN_Msk, 1u);
}

INLINE void ADC2_VCP_OTSD_Int_Dis()
{
  Field_Mod32(&BDRV->CP_IRQEN.reg, (uint8)BDRV_CP_IRQEN_VCP_OTSD_IEN_Pos, BDRV_CP_IRQEN_VCP_OTSD_IEN_Msk, 0u);
}

#endif
