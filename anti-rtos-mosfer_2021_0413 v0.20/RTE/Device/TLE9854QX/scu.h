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
 * \file     scu.h
 *
 * \brief    System Control Unit low level access library
 *
 * \version  V0.2.5
 * \date     02. Mar 2020
 *
 * \note This file violates [MISRA 2012 Rule 2.2, required], [MISRA 2012 Rule 11.1, required], [MISRA 2012 Rule 11.4, advisory], [MISRA 2012 Rule 11.6, required], [MISRA 2012 Rule 2.5, advisory], [MISRA 2012 Rule 8.7, advisory]
 */

/*******************************************************************************
**                             Author(s) Identity                             **
********************************************************************************
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** TS           T&S                                                           **
** JO           Julia Ott                                                     **
** BG           Blandine Guillot                                              **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V0.2.0: 2018-02-13, TS:   Initial version of revision history              **
** V0.2.1: 2018-10-17, TS:   WDTREL, WDTWINB, WDTCON initialization corrected **
**                           MODPISEL3 initialization removed                 **
** V0.2.2: 2019-01-28, TS:   __STATIC_INLINE changed to INLINE                **
**                           Doxygen update                                   **
**                           Revision history moved from scu.c to scu.h       **
**                           SCU_EnterSleepMode, SCU_ClkInit,                 **
**                           SCU_EnterStopMode functions updated              **
**                           SCU_WDT_Start, SCU_WDT_Stop and SCU_WDT_Service  **
**                           functions added                                  **
**                           Added #ifndef UNIT_TESTING_LV2 condition in      **
**                           SCU_EnterSleepMode for testability               **
** V0.2.3: 2019-03-18, TS:   SCU_Init, SCU_ClkInit and SCU_EnterStopMode      **
**                           functions updated                                **
**                           SCU_WDT_Start, SCU_WDT_Stop, SCU_System_Clock_Sel**
**                           functions updated                                **
**                           VCO_BYP and OSC_DISC masks and initial values    **
**                           macros added                                     **
** V0.2.4: 2019-06-17, JO:   In SCU_ClkInit: Removed setting APCLK_SET to     **
**                           zero because this register is cleared by         **
**                           Hardware, updated comment                        **
**                           In SCU_Init: Removed unused initialization of    **
**                           SCU->MODPISEL3                                   **
**                           In SCU_EnterSleepMode: Set LIN to sleep mode     **
**                           only if the LIN module is enabled                **
** V0.2.5: 2020-03-02, BG:   Updated revision history format                  **
*******************************************************************************/

#ifndef SCU_H
#define SCU_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle985x.h"
#include "types.h"
#include "sfr_access.h"
#include "bootrom.h"

/*******************************************************************************
**                          Global Macro Definitions                          **
*******************************************************************************/
/**\brief  PASSWD Phrases, PASSWD Opened */
#define PASSWD_Open (0x98U)
/**\brief  PASSWD Phrases, PASSWD Closed */
#define PASSWD_Close (0xA8U)

/**\brief  NVM Protection indices, BOOT */
#define NVM_PASSWORD_BOOT (0U)
/**\brief  NVM Protection indices, CODE */
#define NVM_PASSWORD_CODE (1U)
/**\brief  NVM Protection indices, DATA */
#define NVM_PASSWORD_DATA  (2U)

/**\brief  NVM Protection actions, CLEAR ACTION */
#define PROTECTION_CLEAR  (1U)
/**\brief  NVM Protection actions, SET ACTION */
#define PROTECTION_SET    (0U)

/**\brief  PBA0 Clock Divider, DIV1 */
#define PBA0_Div_1  (0U)
/**\brief  PBA0 Clock Divider, DIV2 */
#define PBA0_Div_2  (1U)

/**\brief  VCO_BYP MASK */
#define VCO_BYP_Msk  (0x80008U)
/**\brief  VCO_BYP Initial Value */
#define VCO_BYP_0    (0x80000U)
/**\brief  OSC_DISC MASK */
#define OSC_DISC_Msk (0x40004U)
/**\brief  OSC_DISC Initial Value */
#define OSC_DISC_0   (0x40000U)

/*******************************************************************************
**                           Global Type Definitions                          **
*******************************************************************************/
/** \enum TScu_Mod
 *  \brief This enum lists the SCU Modules Configuration.
 */
typedef enum
{
  Mod_ADC1 = 0x00,     /**< SCU Modules Select: ADC1 */
  Mod_SSC1 = 0x01,     /**< SCU Modules Select: SSC1 */
  Mod_CCU = 0x02,      /**< SCU Modules Select: CCU6 */
  Mod_Timer2 = 0x03,   /**< SCU Modules Select: Timer2 */
  Mod_GPT12 = 0x04,    /**< SCU Modules Select: GPT12 */
  Mod_SSC2 = 0x08,     /**< SCU Modules Select: SSC2 */
  Mod_Timer21 = 0x0A   /**< SCU Modules Select: Timer21 */
} TScu_Mod;

/** \enum TSCU_System_Clock
 *  \brief This enum lists the SCU System Clock Sources.
 */
typedef enum
{
  SCU_System_Clock_PLL    = 0, /**< SCU System Clock Source Select: PLL */
  SCU_System_Clock_Osc    = 1, /**< SCU System Clock Source Select: OSC */
  SCU_System_Clock_LP_CLK = 2, /**< SCU System Clock Source Select: LP Clock */
  SCU_System_Clock_IntOsc = 3  /**< SCU System Clock Source Select: Int Clock */
} TSCU_System_Clock;

/** \enum TSCU_Osc_Source
 *  \brief This enum lists the SCU Oscillator Sources.
 */
typedef enum
{
  SCU_Osc_Source_Int_Sync  = 0, /**< SCU Oscillator Source Select: PLL internal oscillator is selected synchronously as fR */
  SCU_Osc_Source_XTAL      = 1, /**< SCU Oscillator Source Select: XTAL is selected synchronously as fR */
  SCU_Osc_Source_Int_Async = 3  /**< SCU Oscillator Source Select: PLL internal oscillator is selected asynchronously as fR */
} TSCU_Osc_Source;

/** \enum TSCU_VTOR
 *  \brief This enum lists the SCU Vector Table Relocation.
 */
typedef enum
{
  SCU_VTOR_ROM   = 0, /**< SCU Vector Table Relocation: ROM */
  SCU_VTOR_RAM   = 1, /**< SCU Vector Table Relocation: RAM */
  SCU_VTOR_CBSL  = 2, /**< SCU Vector Table Relocation: CBSL */
  SCU_VTOR_UCODE = 3  /**< SCU Vector Table Relocation: UCODE */
} TSCU_VTOR;

/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/
/** \brief Initializes the SCU module.
 *
 * \ingroup scu_api
 */
void SCU_Init(void);

/** \brief Initializes the system clocks.
 *
 * \ingroup scu_api
 */
void SCU_ClkInit(void);

/** \brief Sets the device into Sleep Mode
 * \note This function violates [MISRA 2012 Rule 2.2, required]
 *
 * performed steps:
 * Set LIN to sleep mode,
 * clear Main wake status and Wake Source MON Input,
 * stop WDT1 and trigger a short open window,
 * disable interrupts
 * set Sleep Mode Enable flag in Power Mode Control Register 0,
 * execute the WFE instruction twice to exter sleep mode
 *
 * \brief <b>Example</b><br>
 * \brief This example Sets the device into Sleep Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SCU_EnterSleepMode();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */
void SCU_EnterSleepMode(void);

/** \brief Sets the device into Stop Mode
 * \note This function violates [MISRA 2012 Rule 2.2, required]
 *
 * performed steps:
 * clear Main wake status and Wake Source MON Input,
 * stop WDT1 and trigger a short open window,
 * disable interrupts
 * select LP_CLK as sys clk for a defined state,
 * select OSC_PLL async,
 * set Sleep Mode Enable flag in Power Mode Control Register 0,
 * execute the WFE instruction twice to exter sleep mode
 * + in case TLE985X doesn't wake up with a reset:
 * reset PLL locking in PLL Control Register,
 * wait until PLL is locked,
 * switch back fSYS (was set to LP_CLK before),
 * enable interrupts,
 * initialize WDT1
 *
 * \brief <b>Example</b><br>
 * \brief This example Sets the device into Stop Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SCU_EnterStopMode();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */
void SCU_EnterStopMode(void);

/** \brief Sets the Write/Read Protection for the Code/Data Flash
 *
 * \param Protection BOOT/CODE/DATA, see \link NVM_PASSWORD_SEGMENT_t \endlink
 * \param Action CLEAR/SET
 * \return ERR_LOG_SUCCESS or error code, see \link BOOTROM_RETURN_CODE_t \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example writes Protection for the Code Flash.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SCU_ChangeNVMProtection(NVM_PASSWORD_CODE, PROTECTION_SET);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */
int32_t SCU_ChangeNVMProtection(NVM_PASSWORD_SEGMENT_t Protection, uint8 Action);

/*******************************************************************************
**                        Inline Function Declarations                        **
*******************************************************************************/
/** \brief Disables a given peripheral module
 *
 * \param Module SCU Modules, see \link TScu_Mod \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example disables ADC1 Module.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SCU_Disable_Module(Mod_ADC1);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */
INLINE void SCU_Disable_Module(TScu_Mod Module);

/** \brief Enables a given peripheral module
 *
 * \param Module SCU Modules, see \link TScu_Mod \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example enables ADC1 Module.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SCU_Enable_Module(Mod_ADC1);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */
INLINE void SCU_Enable_Module(TScu_Mod Module);

/** \brief Starts the Watchdog of SCU-DM in the Watchdog Timer Control Register
 * The written bit is protected by the Bit Protection Register of SCU.
 *
 * \brief <b>Example</b><br>
 * \brief This example starts the internal Watchdog and services the internal Watchdog.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SCU_WDT_Start();
 *   SCU_WDT_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */
INLINE void SCU_WDT_Start(void);

/** \brief Stops the Watchdog of SCU-DM in the Watchdog Timer Control Register
 * The written bit is protected by the Bit Protection Register of SCU.
 *
 * \brief <b>Example</b><br>
 * \brief This example stops the internal Watchdog.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SCU_WDT_Stop();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */
INLINE void SCU_WDT_Stop(void);

/** \brief Services the Watchdog of SCU-DM in the Watchdog Timer Control Register
 *
 * \brief <b>Example</b><br>
 * \brief This example starts the internal Watchdog and services the internal Watchdog.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SCU_WDT_Start();
 *   SCU_WDT_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */
INLINE void SCU_WDT_Service(void);

/** \brief Opens the bit protection by writing PASSWD_Open to the Bit Protection Register
 *
 * \brief <b>Example</b><br>
 * \brief This example opens the PASSWD Register protection scheme.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SCU_OpenPASSWD();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */
INLINE void SCU_OpenPASSWD(void);

/** \brief Closes the bit protection by writing PASSWD_Close to the Bit Protection Register
 *
 * \brief <b>Example</b><br>
 * \brief This example closes the PASSWD Register protection scheme.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SCU_ClosePASSWD();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */
INLINE void SCU_ClosePASSWD(void);

/** \brief Sets PBA0 Clock Divider.
 *
 * \param div PBA0 Clock Divider: 0 if div1, 1 if div2
 *
 * \brief <b>Example</b><br>
 * \brief This example sets The PBA0 Clock Divider to 2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SCU_Sel_PBA0_Clk_Div_Sel(PBA0_Div_2);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */
INLINE void SCU_Sel_PBA0_Clk_Div_Sel(uint8 div);

/** \brief Selects a Vector Table Bypass Mode.
 *
 * \param a Vector Table Bypass Mode, see \link TSCU_VTOR \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example configures the VTOR to be remapped to RAM.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SCU_VTOR_Sel(SCU_VTOR_RAM);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */
INLINE void SCU_VTOR_Sel(TSCU_VTOR a);

/** \brief Selects a System Clock.
 *
 * \param a System Clock, see \link TSCU_System_Clock \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example sets The PLL clock output signal to fPLL.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SCU_OpenPASSWD();
 *   SCU_System_Clock_Sel(SCU_System_Clock_PLL);
 *   SCU_ClosePASSWD();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */
INLINE void SCU_System_Clock_Sel(TSCU_System_Clock a);

/** \brief Selects an Oscillator Source.
 *
 * \param a Oscillator Source, see \link TSCU_Osc_Source \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example selects XTAL synchronously as fR.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SCU_Osc_Source_Sel(SCU_Osc_Source_XTAL);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */
INLINE void SCU_Osc_Source_Sel(TSCU_Osc_Source a);

/** \brief Clears Analog Peripherals Clock 1 Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Analog Peripherals Clock 1 Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SCU_APCLK1_Sts_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */
INLINE void SCU_APCLK1_Sts_Clr(void);

/** \brief Clears Analog Peripherals Clock 2 Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Analog Peripherals Clock 2 Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SCU_APCLK2_Sts_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */         
INLINE void SCU_APCLK2_Sts_Clr(void);

/** \brief Clears Analog Peripherals Clock 3 Status.
 *
 * \brief <b>Example</b><br>
 * \brief This example clears Analog Peripherals Clock 3 Status.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SCU_APCLK3_Sts_Clr();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */        
INLINE void SCU_APCLK3_Sts_Clr(void);     

/** \brief Enables Clock Watchdog.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables Clock Watchdog.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SCUPM_CLKWDT_PD_N_En();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */  
INLINE void SCUPM_CLKWDT_PD_N_En(void);

/** \brief Disables Clock Watchdog.
 *
 * \brief <b>Example</b><br>
 * \brief This example disables Clock Watchdog.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SCUPM_CLKWDT_PD_N_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */    
INLINE void SCUPM_CLKWDT_PD_N_Dis(void);

/** \brief Sets Analog Module Clock 1 Upper Limit Threshold.
 *
 * \param thld Upper Limit Threshold
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Analog Module Clock 1 Upper Limit Threshold to Maximum value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SCUPM_AMCLK1_UP_TH_Set(0x3F);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */
INLINE void SCUPM_AMCLK1_UP_TH_Set(uint8 thld);

/** \brief Sets Analog Module Clock 1 Upper Hysteresis.
 *
 * \param hyst Upper Hysteresis
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Analog Module Clock 1 Upper Hysteresis to Maximum value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SCUPM_AMCLK1_UP_HYS_Set(0x3);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */
INLINE void SCUPM_AMCLK1_UP_HYS_Set(uint8 hyst);

/** \brief Sets Analog Module Clock 1 Lower Limit Threshold.
 *
 * \param thld Lower Limit Threshold
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Analog Module Clock 1 Lower Limit Threshold to Maximum value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SCUPM_AMCLK1_LOW_TH_Set(0x3F);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */
INLINE void SCUPM_AMCLK1_LOW_TH_Set(uint8 thld);

/** \brief Sets Analog Module Clock 1 Lower Hysteresis.
 *
 * \param hyst Lower Hysteresis
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Analog Module Clock 1 Lower Hysteresis to Maximum value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SCUPM_AMCLK1_LOW_HYS_Set(0x3);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */
INLINE void SCUPM_AMCLK1_LOW_HYS_Set(uint8 hyst);

/** \brief Sets Analog Module Clock 2 Upper Limit Threshold.
 *
 * \param thld Upper Limit Threshold
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Analog Module Clock 2 Upper Limit Threshold to Maximum value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SCUPM_AMCLK2_UP_TH_Set(0x3F);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */
INLINE void SCUPM_AMCLK2_UP_TH_Set(uint8 thld);

/** \brief Sets Analog Module Clock 2 Upper Hysteresis.
 *
 * \param hyst Upper Hysteresis
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Analog Module Clock 2 Upper Hysteresis to Maximum value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SCUPM_AMCLK2_UP_HYS_Set(0x3);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */
INLINE void SCUPM_AMCLK2_UP_HYS_Set(uint8 hyst);

/** \brief Sets Analog Module Clock 2 Lower Limit Threshold.
 *
 * \param thld Lower Limit Threshold
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Analog Module Clock 2 Lower Limit Threshold to Maximum value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SCUPM_AMCLK2_LOW_TH_Set(0x3F);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */
INLINE void SCUPM_AMCLK2_LOW_TH_Set(uint8 thld);

/** \brief Sets Analog Module Clock 2 Lower Hysteresis.
 *
 * \param hyst Lower Hysteresis
 *
 * \brief <b>Example</b><br>
 * \brief This example sets Analog Module Clock 2 Lower Hysteresis to Maximum value.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   SCUPM_AMCLK2_LOW_HYS_Set(0x3);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */
INLINE void SCUPM_AMCLK2_LOW_HYS_Set(uint8 hyst);

/** \brief Selects low power deep sleep mode.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects low power deep sleep mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CPU_DeepSleep_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */
INLINE void CPU_DeepSleep_Sel(void);

/** \brief Selects entering sleep or deep sleep on exit.
 *
 * \brief <b>Example</b><br>
 * \brief This example selects entering deep sleep on exit.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *   CPU_DeepSleep_Sel();  
 *   CPU_SleepOnExit_Sel();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup scu_api
 */  
INLINE void CPU_SleepOnExit_Sel(void);

/*******************************************************************************
**                         Inline Function Definitions                        **
*******************************************************************************/
INLINE void SCU_Disable_Module(TScu_Mod Module)
{
  Field_Mod32(&SCU->PMCON.reg, (uint8)Module, (uint32)1u << (uint8)Module, 1u);  
}

INLINE void SCU_Enable_Module(TScu_Mod Module)
{
  Field_Mod32(&SCU->PMCON.reg, (uint8)Module, (uint32)1u << (uint8)Module, 0u);  
}

INLINE void SCU_WDT_Start(void)
{
  SCU_OpenPASSWD();	
  Field_Mod32(&SCU->WDTCON.reg, (uint8)SCU_WDTCON_WDTEN_Pos, SCU_WDTCON_WDTEN_Msk, 1u);
	SCU_ClosePASSWD();
}

INLINE void SCU_WDT_Stop(void)
{
  SCU_OpenPASSWD();	
  Field_Mod32(&SCU->WDTCON.reg, (uint8)SCU_WDTCON_WDTEN_Pos, SCU_WDTCON_WDTEN_Msk, 0u);
	SCU_ClosePASSWD();
}

INLINE void SCU_WDT_Service(void)
{
  Field_Mod32(&SCU->WDTCON.reg, (uint8)SCU_WDTCON_WDTRS_Pos, SCU_WDTCON_WDTRS_Msk, 1u);
}

INLINE void SCU_OpenPASSWD(void)
{
  Field_Wrt32all(&SCU->PASSWD.reg, (uint8)PASSWD_Open);  
}

INLINE void SCU_ClosePASSWD(void)
{
  Field_Wrt32all(&SCU->PASSWD.reg, (uint8)PASSWD_Close);
}

INLINE void SCU_Sel_PBA0_Clk_Div_Sel(uint8 div)
{
  SCU_OpenPASSWD();
  Field_Wrt32(&SCU->CMCON2.reg, (uint8)SCU_CMCON2_PBA0CLKREL_Pos, SCU_CMCON2_PBA0CLKREL_Msk, div);
  SCU_ClosePASSWD();  
}

INLINE void SCU_VTOR_Sel(TSCU_VTOR a)
{
  SCU_OpenPASSWD();
  Field_Wrt32(&SCU->VTOR.reg, (uint8)SCU_VTOR_VTOR_BYP_Pos, SCU_VTOR_VTOR_BYP_Msk, (uint32)a);
  SCU_ClosePASSWD();
}

INLINE void SCU_System_Clock_Sel(TSCU_System_Clock a)
{
  SCU_OpenPASSWD();	
  Field_Mod32(&SCU->SYSCON0.reg, (uint8)SCU_SYSCON0_SYSCLKSEL_Pos, SCU_SYSCON0_SYSCLKSEL_Msk, (uint32)a);
  SCU_ClosePASSWD();	
}

INLINE void SCU_Osc_Source_Sel(TSCU_Osc_Source a)
{
  SCU_OpenPASSWD();  
  Field_Mod32(&SCU->OSC_CON.reg, (uint8)SCU_OSC_CON_OSCSS_Pos, SCU_OSC_CON_OSCSS_Msk, (uint32)a);
  SCU_ClosePASSWD();  
}

INLINE void SCU_APCLK1_Sts_Clr()         
{
  Field_Wrt32(&SCU->APCLK_SCLR.reg, (uint8)SCU_APCLK_SCLR_APCLK1SCLR_Pos, SCU_APCLK_SCLR_APCLK1SCLR_Msk, 1);
}

INLINE void SCU_APCLK2_Sts_Clr()                     
{
  Field_Wrt32(&SCU->APCLK_SCLR.reg, (uint8)SCU_APCLK_SCLR_APCLK2SCLR_Pos, SCU_APCLK_SCLR_APCLK2SCLR_Msk, 1);
}

INLINE void SCU_APCLK3_Sts_Clr()                     
{
  Field_Wrt32(&SCU->APCLK_SCLR.reg, (uint8)SCU_APCLK_SCLR_APCLK3SCLR_Pos, SCU_APCLK_SCLR_APCLK3SCLR_Msk, 1);
}

INLINE void SCUPM_CLKWDT_PD_N_En()                      
{
  Field_Wrt32(&SCUPM->AMCLK_CTRL.reg, (uint8)SCUPM_AMCLK_CTRL_CLKWDT_PD_N_Pos, SCUPM_AMCLK_CTRL_CLKWDT_PD_N_Msk, 1);
}

INLINE void SCUPM_CLKWDT_PD_N_Dis()                      
{
  Field_Wrt32(&SCUPM->AMCLK_CTRL.reg, (uint8)SCUPM_AMCLK_CTRL_CLKWDT_PD_N_Pos, SCUPM_AMCLK_CTRL_CLKWDT_PD_N_Msk, 0);
}

INLINE void SCUPM_AMCLK1_UP_TH_Set(uint8 thld)                 
{
  Field_Mod32(&SCUPM->AMCLK_TH_HYS.reg, (uint8)SCUPM_AMCLK_TH_HYS_AMCLK1_UP_TH_Pos, SCUPM_AMCLK_TH_HYS_AMCLK1_UP_TH_Msk, thld);
}

INLINE void SCUPM_AMCLK1_UP_HYS_Set(uint8 hyst)                
{
  Field_Mod32(&SCUPM->AMCLK_TH_HYS.reg, (uint8)SCUPM_AMCLK_TH_HYS_AMCLK1_UP_HYS_Pos, SCUPM_AMCLK_TH_HYS_AMCLK1_UP_HYS_Msk, hyst);
}

INLINE void SCUPM_AMCLK1_LOW_TH_Set(uint8 thld)                
{
  Field_Mod32(&SCUPM->AMCLK_TH_HYS.reg, (uint8)SCUPM_AMCLK_TH_HYS_AMCLK1_LOW_TH_Pos, SCUPM_AMCLK_TH_HYS_AMCLK1_LOW_TH_Msk, thld);
}

INLINE void SCUPM_AMCLK1_LOW_HYS_Set(uint8 hyst)               
{
  Field_Mod32(&SCUPM->AMCLK_TH_HYS.reg, (uint8)SCUPM_AMCLK_TH_HYS_AMCLK1_LOW_HYS_Pos, SCUPM_AMCLK_TH_HYS_AMCLK1_LOW_HYS_Msk, hyst);
}

INLINE void SCUPM_AMCLK2_UP_TH_Set(uint8 thld)                 
{
  Field_Mod32(&SCUPM->AMCLK_TH_HYS.reg, (uint8)SCUPM_AMCLK_TH_HYS_AMCLK2_UP_TH_Pos, SCUPM_AMCLK_TH_HYS_AMCLK2_UP_TH_Msk, thld);
}

INLINE void SCUPM_AMCLK2_UP_HYS_Set(uint8 hyst)                
{
  Field_Mod32(&SCUPM->AMCLK_TH_HYS.reg, (uint8)SCUPM_AMCLK_TH_HYS_AMCLK2_UP_HYS_Pos, SCUPM_AMCLK_TH_HYS_AMCLK2_UP_HYS_Msk, hyst);
}

INLINE void SCUPM_AMCLK2_LOW_TH_Set(uint8 thld)                
{
  Field_Mod32(&SCUPM->AMCLK_TH_HYS.reg, (uint8)SCUPM_AMCLK_TH_HYS_AMCLK2_LOW_TH_Pos, SCUPM_AMCLK_TH_HYS_AMCLK2_LOW_TH_Msk, thld);
}

INLINE void SCUPM_AMCLK2_LOW_HYS_Set(uint8 hyst)               
{
  Field_Mod32(&SCUPM->AMCLK_TH_HYS.reg, (uint8)SCUPM_AMCLK_TH_HYS_AMCLK2_LOW_HYS_Pos, SCUPM_AMCLK_TH_HYS_AMCLK2_LOW_HYS_Msk, hyst);
}

INLINE void CPU_DeepSleep_Sel()                          
{
  Field_Mod32(&CPU->SCR.reg, (uint8)CPU_SCR_SLEEPDEEP_Pos, CPU_SCR_SLEEPDEEP_Msk, 1);
}

INLINE void CPU_SleepOnExit_Sel()                        
{
  Field_Mod32(&CPU->SCR.reg, (uint8)CPU_SCR_SLEEPONEXIT_Pos, CPU_SCR_SLEEPONEXIT_Msk, 1);
}

#endif
