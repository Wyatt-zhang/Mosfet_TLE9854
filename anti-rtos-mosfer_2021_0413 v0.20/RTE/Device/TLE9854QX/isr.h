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
 * \file     isr.h
 *
 * \brief    Interrupt Service Routines low level access library
 *
 * \version  V0.2.3
 * \date     02. Mar 2020
 *
 *  \note This file violates [MISRA 2012 Rule 12.2, required], [MISRA 2012 Rule 8.7, advisory]
 */

/*******************************************************************************
**                             Author(s) Identity                             **
********************************************************************************
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** KC           Kay Claussen                                                  **
** TS           T&S                                                           **
** BG           Blandine Guillot                                              **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V0.2.0: 2018-02-13, TS:   Initial version of revision history              **
** V0.2.1: 2018-08-28, KC:   CP input volt. low thresh. interrupt corrected   **
** V0.2.2: 2019-01-28, TS:   __STATIC_INLINE changed to INLINE                **
**                           Doxygen update                                   **
**                           Revision history moved from isr.c to isr.h       **
**                           CSA_IRQHandler, MONx_IRQHandler, PORT2_IRQHandler**
**                           updated                                          **
** V0.2.3: 2020-03-02, BG:   Updated revision history format                  **
*******************************************************************************/

#ifndef ISR_H
#define ISR_H

/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/
/** \brief The GPT1_IRQHandler checks which interrupt caused the call of the node handler 0
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * GPT1_IRQHandler is responsible for:
 * GPT1 T2 INT, GPT1 T3 INT, GPT1 T4 INT
 *
 * \ingroup isr_api
 */
void GPT1_IRQHandler(void);

/** \brief The GPT2_IRQHandler checks which interrupt caused the call of the node handler 1
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * GPT2_IRQHandler is responsible for:
 * GPT2 T5 INT, GPT2 T6 INT, GPT2 CAPREL INT
 *
 * \ingroup isr_api
 */
void GPT2_IRQHandler(void);

/** \brief The ADC2_IRQHandler checks which interrupt caused the call of the node handler 2
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * ADC2_IRQHandler is responsible for:
 * ADC2 VBG UP INT, ADC2 VBG LO INT
 *
 * \ingroup isr_api
 */
void ADC2_IRQHandler(void);

/** \brief The ADC1_IRQHandler checks which interrupt caused the call of the node handler 3
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * ADC1_IRQHandler is responsible for:
 * ADC1 CH0 INT, ADC1 CH1 INT, ADC1 CH2 INT, ADC1 CH3 INT,
 * ADC1 CH4 INT, ADC1 CH5 INT, ADC1 CH6 INT, ADC1 CH7 INT,
 * ADC1 CH8 INT, ADC1 CH9 INT, ADC1 CH12 INT, ADC1 CH13 INT,
 * ADC1 EIM INT, ADC1 ESM INT
 *
 * \ingroup isr_api
 */
void ADC1_IRQHandler(void);

/** \brief The SSU6SR0_IRQHandler checks which interrupt caused the call of the node handler 4
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * SSU6SR0_IRQHandler is responsible for:
 * CCU6 CH0 CMR INT, CCU6 CH0CMF INT, CCU6 CH1 CMR INT, CCU6 CH1CMF INT,
 * CCU6 CH2 CMR INT, CCU6 CH2CMF INT, CCU6 T12 OM INT, CCU6 T12PM INT
 * CCU6 T13 CM INT, CCU6 T13PM INT, CCU6 TRAP INT, CCU6 WHE INT,
 * CCU6 CHE INT, CCU6 MCM STR INT
 *
 * \ingroup isr_api
 */
void CCU6SR0_IRQHandler(void);

/** \brief The SSU6SR1_IRQHandler checks which interrupt caused the call of the node handler 5
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * SSU6SR1_IRQHandler is responsible for:
 * CCU6 CH0 CMR INT, CCU6 CH0CMF INT, CCU6 CH1 CMR INT, CCU6 CH1CMF INT,
 * CCU6 CH2 CMR INT, CCU6 CH2CMF INT, CCU6 T12 OM INT, CCU6 T12PM INT
 * CCU6 T13 CM INT, CCU6 T13PM INT, CCU6 TRAP INT, CCU6 WHE INT,
 * CCU6 CHE INT, CCU6 MCM STR INT
 *
 * \ingroup isr_api
 */
void CCU6SR1_IRQHandler(void);

/** \brief The SSU6SR2_IRQHandler checks which interrupt caused the call of the node handler 6
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * SSU6SR2_IRQHandler is responsible for:
 * CCU6 CH0 CMR INT, CCU6 CH0CMF INT, CCU6 CH1 CMR INT, CCU6 CH1CMF INT,
 * CCU6 CH2 CMR INT, CCU6 CH2CMF INT, CCU6 T12 OM INT, CCU6 T12PM INT
 * CCU6 T13 CM INT, CCU6 T13PM INT, CCU6 TRAP INT, CCU6 WHE INT,
 * CCU6 CHE INT, CCU6 MCM STR INT
 *
 * \ingroup isr_api
 */
void CCU6SR2_IRQHandler(void);

/** \brief The SSU6SR3_IRQHandler checks which interrupt caused the call of the node handler 7
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * SSU6SR3_IRQHandler is responsible for:
 * CCU6 CH0 CMR INT, CCU6 CH0CMF INT, CCU6 CH1 CMR INT, CCU6 CH1CMF INT,
 * CCU6 CH2 CMR INT, CCU6 CH2CMF INT, CCU6 T12 OM INT, CCU6 T12PM INT
 * CCU6 T13 CM INT, CCU6 T13PM INT, CCU6 TRAP INT, CCU6 WHE INT,
 * CCU6 CHE INT, CCU6 MCM STR INT
 *
 * \ingroup isr_api
 */
void CCU6SR3_IRQHandler(void);

/** \brief The SSC1_IRQHandler checks which interrupt caused the call of the node handler 8
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * SSC1_IRQHandler is responsible for:
 * SSC1 RX INT, SSC1 TX INT, SSC1 ERR INT
 *
 * \ingroup isr_api
 */
void SSC1_IRQHandler(void);

/** \brief The SSC2_IRQHandler checks which interrupt caused the call of the node handler 9
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * SSC2_IRQHandler is responsible for:
 * SSC2 RX INT, SSC2 TX INT, SSC2 ERR INT
 *
 * \ingroup isr_api
 */
void SSC2_IRQHandler(void);

/** \brief The UART1_IRQHandler checks which interrupt caused the call of the node handler 10
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * UART1_IRQHandler is responsible for:
 * UART1 RX INT, UART1 TX INT,
 * TIMER2 EXF2 INT, TIMER2 TF2 INT,
 * LIN EOF INT, LIN ERR INT,
 * LIN OC INT, LIN OT INT, LIN TMOUT INT, LIN M SM ERR INT
 *
 * \ingroup isr_api
 */
void UART1_IRQHandler(void);

/** \brief The UART2_IRQHandler checks which interrupt caused the call of the node handler 11
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * UART2_IRQHandler is responsible for:
 * UART2 RX INT, UART2 TX INT,
 * TIMER21 EXF2 INT, TIMER21 TF2 INT,
 * SCU EXINT2 RISING INT, SCU EXINT2 FALLING INT
 *
 * \ingroup isr_api
 */
void UART2_IRQHandler(void);

/** \brief The EXINT0_IRQHandler checks which interrupt caused the call of the node handler 12
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * EXINT0_IRQHandler is responsible for:
 * SCU EXINT0 RISING INT, SCU EXINT0 FALLING INT,
 *
 * \ingroup isr_api
 */
void EXINT0_IRQHandler(void);

/** \brief The EXINT1_IRQHandler checks which interrupt caused the call of the node handler 13
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * EXINT1_IRQHandler is responsible for:
 * SCU EXINT1 RISING INT, SCU EXINT1 FALLING INT,
 *
 * \ingroup isr_api
 */
void EXINT1_IRQHandler(void);

/** \brief The WAKEUP_IRQHandler checks which interrupt caused the call of the node handler 14
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * WAKEUP_IRQHandler is responsible for:
 * PMU WAKEUP INT
 *
 * \ingroup isr_api
 */
void WAKEUP_IRQHandler(void);

/** \brief The DIV_IRQHandler checks which interrupt caused the call of the node handler 15
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * DIV_IRQHandler is responsible for:
 * MATH DIVERR INT, MATH DIVEOC INT
 *
 * \ingroup isr_api
 */
void DIV_IRQHandler(void);

/** \brief The CP_IRQHandler checks which interrupt caused the call of the node handler 17
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * CP_IRQHandler is responsible for:
 * ADC2 VSD UP INT, ADC2 VSD LO INT, ADC2 VCP UP INT, ADC2 VCP LO INT,
 * ADC2 CP TEMP UP INT, ADC2 CP TEMP LO INT, BDRV VCP LO2 INT
 *
 * \ingroup isr_api
 */
void CP_IRQHandler(void);

/** \brief The BDRV_IRQHandler checks which interrupt caused the call of the node handler 18
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * BDRV_IRQHandler is responsible for:
 * BDRV HS1 OC INT, BDRV LS1 OC INT,
 * BDRV HS2 OC INT, BDRV LS2 OC INT,
 * BDRV HS1 DS INT, BDRV LS1 DS INT,
 * BDRV HS2 DS INT, BDRV LS2 DS INT,
 * BDRV SEQ ERR INT
 *
 * \ingroup isr_api
 */
void BDRV_IRQHandler(void);

/** \brief The HS_IRQHandler checks which interrupt caused the call of the node handler 19
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * HS_IRQHandler is responsible for:
 * HS HS1 OT INT, HS HS1 OL INT, HS HS1 OC INT
 *
 * \ingroup isr_api
 */
void HS_IRQHandler(void);

/** \brief The CSA_IRQHandler checks which interrupt caused the call of the node handler 20
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * ADC1 Post processing channel must be linked to interupt node 20.
 * CSA_IRQHandler is responsible for:
 * ADC1 PP CH2 UP INT, ADC1 PP CH2 LO INT, ADC1 PP CH3 UP INT, ADC1 PP CH3 LO INT,
 * ADC1 PP CH4 UP INT, ADC1 PP CH4 LO INT, ADC1 PP CH5 UP INT, ADC1 PP CH5 LO INT,
 * ADC1 PP CH6 UP INT, ADC1 PP CH6 LO INT, ADC1 PP CH7 UP INT, ADC1 PP CH7 LO INT
 *
 * \ingroup isr_api
 */
void CSA_IRQHandler(void);

/** \brief The DU1_IRQHandler checks which interrupt caused the call of the node handler 21
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * DU1_IRQHandler is responsible for:
 * ADC1 DU1UP INT, ADC1 DU1LO INT
 *
 * \ingroup isr_api
 */
void DU1_IRQHandler(void);

/** \brief The MONx_IRQHandler checks which interrupt caused the call of the node handler 22
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * ADC1 Post processing channel is linked to interupt node 22 (for ADC1 PP Channel interrupts).
 * MONx_IRQHandler is responsible for:
 * MON1 RISING INT, MON1 FALLING INT,
 * MON2 RISING INT, MON2 FALLING INT,
 * MON3 RISING INT, MON3 FALLING INT,
 * MON4 RISING INT, MON4 FALLING INT,
 * ADC1 PP CH2 UP INT, ADC1 PP CH2 LO INT, ADC1 PP CH3 UP INT, ADC1 PP CH3 LO INT,
 * ADC1 PP CH4 UP INT, ADC1 PP CH4 LO INT, ADC1 PP CH5 UP INT, ADC1 PP CH5 LO INT,
 * ADC1 PP CH6 UP INT, ADC1 PP CH6 LO INT, ADC1 PP CH7 UP INT, ADC1 PP CH7 LO INT
 *
 * \ingroup isr_api
 */
void MONx_IRQHandler(void);

/** \brief The PORT2_IRQHandler checks which interrupt caused the call of the node handler 23
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * ADC1 Post processing channels must be linked to interupt node 23.
 * PORT2_IRQHandler is responsible for:
 * ADC1 PP CH2 UP INT, ADC1 PP CH2 LO INT, ADC1 PP CH3 UP INT, ADC1 PP CH3 LO INT,
 * ADC1 PP CH4 UP INT, ADC1 PP CH4 LO INT, ADC1 PP CH5 UP INT, ADC1 PP CH5 LO INT,
 * ADC1 PP CH6 UP INT, ADC1 PP CH6 LO INT, ADC1 PP CH7 UP INT, ADC1 PP CH7 LO INT
 *
 * \ingroup isr_api
 */
void PORT2_IRQHandler(void);

/** \brief The NMI_Handler checks which interrupt caused the call of the node handler NMI
 * (interrupt enabled and status bit indicates that this interrupt occurred).
 * Then it calls the corresponding interrupt handler and clears the interrupt status bit.
 * NMI_Handler is responsible for:
 * SCU NMI WDT INT, SCU NMI PLL INT, SCU NMI STOF INT,
 * SCU NMI OWD INT, SCU NMI MAP INT,
 * SCU ECC RAM DB INT, SCU ECC NVM DB INT,
 * ADC2 SYS TEMP UP INT,  ADC2 SYS TEMP LO INT,
 * ADC2 VS UP INT, ADC2 VS LO INT,
 * ADC2 VDDC UP INT, ADC2 VDDC LO INT,
 * ADC2 VDDP UP INT, ADC2 VDDP LO INT,
 * PMU VDDEXT UV INT, PMU VDDEXT OT INT,
 * PMU VDDC OV INT, PMU VDDC OL INT,
 * PMU VDDP OV INT, PMU VDDP OL INT,
 * PMU PMU OT INT,
 * ADC2 VDDEXT UP INT, ADC2 VDDEXT LO INT,
 * ADC1 PP CH0 UP INT, ADC1 PP CH0 LO INT, ADC1 PP CH1 UP INT, ADC1 PP CH1 LO INT,
 *
 * \ingroup isr_api
 */
void NMI_Handler(void);

/** \brief The HardFault_Handler handles the HardFault exception
 *
 * \ingroup isr_api
 */
void HardFault_Handler(void);

/** \brief The SysTick_Handler handles the SysTick exception
 *
 * \ingroup isr_api
 */
void SysTick_Handler(void);

#endif
