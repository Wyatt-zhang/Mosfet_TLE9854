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
 * \file     uart.h
 *
 * \brief    UART low level access library
 *
 * \version  V0.2.4
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
** V0.2.1: 2018-07-30, KC:   Conditional compiling in UARTx_Init removed      **
** V0.2.2: 2019-01-28, TS:   Revision history moved from uart.c to uart.h     **
**                           __STATIC_INLINE replaced by INLINE               **
**                           Doxygen update                                   **
**                           Ranges added for UART1_BaudRate_Set and          **
**                           UART2_BaudRate_Set                               **
**                           Implementation of stdout_putchar, stdin_getchar  **
**                           adapted for UART1 and UART2 so that they follow  **
**                           the same procedure                               **
**                           UART1_BaudRate_Value_Set,                        **
**                           UART1_Fractional_Divider_Value_Set,              **
**                           UART2_BaudRate_Value_Set and                     **
**                           UART2_Fractional_Divider_Value_Set added         **
** V0.2.3: 2019-06-13, JO:   Corrected ranges for UART1_BaudRate_Set and      **
**                           UART2_BaudRate_Set                               **
** V0.2.4: 2020-03-02, BG:   Updated revision history format                  **
*******************************************************************************/

#ifndef UART_H
#define UART_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle985x.h"
#include "sfr_access.h"
#include "uart_defines.h"
#include "types.h"

/*******************************************************************************
**                           Global Type Definitions                          **
*******************************************************************************/
/** \struct TUart
 *  \brief This struct lists parameter (clock) of UART1/UART2.
 */
typedef struct
{
  uint32 clock;
} TUart;

/*******************************************************************************
**                        Global Function Declarations                        **
*******************************************************************************/
/** \brief Initializes the UART1 module.
 *
 * \ingroup uart_api
 */
void UART1_Init(void);

/** \brief Initializes the UART2 module.
 *
 * \ingroup uart_api
 */
void UART2_Init(void);

/** \brief Sets the baudrate for UART1.
 *
 * \param baudrate baudrate, e.g. 19200, or 115200; range: 1221 to 5000000 (a value out of this range will not be applied)
 *
 * \brief <b>Example</b><br>
 * \brief This example sets UART1 BAUDRATE to 19200.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART1_BaudRate_Set(19200);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
void UART1_BaudRate_Set(uint32 baudrate);

/** \brief Sets the baudrate for UART2.
 *
 * \param baudrate baudrate, e.g. 19200, or 115200; range: 1221 to 5000000 (a value out of this range will not be applied)
 *
 * \brief <b>Example</b><br>
 * \brief This example sets UART1 BAUDRATE to 115200.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART2_BaudRate_Set(115200);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
void UART2_BaudRate_Set(uint32 baudrate);

#if ((UART1_STD_EN == 1u) || (UART2_STD_EN == 1u))
/** \brief Sends a character via UART1/2.
 *
 * \param Char Character to send
 * \return Sent character
 *
 * \ingroup uart_api
 */
sint32 stdout_putchar(sint32 Char);

/** \brief Receives a character via UART1/2.
 *
 * \return Received character
 *
 * \ingroup uart_api
 */
sint32 stdin_getchar(void);
void ttywrch(int ch);
#endif /* ((UART1_STD_EN == 1) || (UART2_STD_EN == 1)) */

/*******************************************************************************
**                        Inline Function Declarations                        **
*******************************************************************************/
/** \brief Reads the receive interrupt flag for UART1.
 *
 * \return Receive Interrupt Flag Status
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART1_Receiver_En();
 *     UART1_BaudRate_Set(19200);
 *     if (UART1_RX_Sts() == 1u)
 *     {
 *       ch = UART1_Get_Byte();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE uint8 UART1_RX_Sts(void);

/** \brief Reads the transmit interrupt flag for UART1.
 *
 * \return Transmit Interrupt Flag Status
 *
 * \brief <b>Example</b><br>
 * \brief This example sends "A" via UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART1_BaudRate_Set(19200);
 *     if (UART1_TX_Sts() == 1u)
 *     {
 *       UART1_Send_Byte(0x41);
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE uint8 UART1_TX_Sts(void);

/** \brief Reads the receive interrupt flag for UART2.
 *
 * \return Receive Interrupt Flag Status
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART2_Receiver_En();
 *     UART2_BaudRate_Set(19200);
 *     if (UART2_RX_Sts() == 1u)
 *     {
 *       ch = UART2_Get_Byte();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE uint8 UART2_RX_Sts(void);

/** \brief Reads the transmit interrupt flag for UART2.
 *
 * \return Transmit Interrupt Flag Status
 *
 * \brief <b>Example</b><br>
 * \brief This example sends "A" via UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART2_BaudRate_Set(19200);
 *     if (UART2_TX_Sts() == 1u)
 *     {
 *       UART2_Send_Byte(0x41);
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE uint8 UART2_TX_Sts(void);

/** \brief Enables Receiver of Serial Port (UART1).
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART1_Receiver_En();
 *     UART1_BaudRate_Set(19200);
 *     if (UART1_isByteReceived() == TRUE)
 *     {
 *       ch = UART1_Get_Byte();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART1_Receiver_En(void);

/** \brief Disables Receiver of Serial Port (UART1).
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART1_Receiver_En();
 *     UART1_BaudRate_Set(19200);
 *     if (UART1_isByteReceived() == TRUE)
 *     {
 *       ch = UART1_Get_Byte();
 *     }
 *     UART1_Receiver_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART1_Receiver_Dis(void);

/** \brief Enables Baud-rate generator (UART1).
 * \note Setting new Baud-rate value must be when BaudRateGen is disabled.
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART1 (baudrate is equal to 19200 when frequency is equal to 40MHz).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART1_Receiver_En();
 *     UART1_BaudRateGen_Dis();
 *     UART1_BaudRate_Value_Set(130);
 *     UART1_Fractional_Divider_Value_Set(7);
 *     UART1_BaudRateGen_En();
 *     if (UART1_isByteReceived() == TRUE)
 *     {
 *       ch = UART1_Get_Byte();
 *     }
 *     UART1_Receiver_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART1_BaudRateGen_En(void);

/** \brief Disables Baud-rate generator (UART1).
 * \note Setting new Baud-rate value must be when BaudRateGen is disabled.
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART1 (baudrate is equal to 19200 when frequency is equal to 40MHz).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART1_Receiver_En();
 *     UART1_BaudRateGen_Dis();
 *     UART1_BaudRate_Value_Set(130);
 *     UART1_Fractional_Divider_Value_Set(7);
 *     UART1_BaudRateGen_En();
 *     if (UART1_isByteReceived() == TRUE)
 *     {
 *       ch = UART1_Get_Byte();
 *     }
 *     UART1_Receiver_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART1_BaudRateGen_Dis(void);

/** \brief Enables Receiver of Serial Port (UART2).
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART2_Receiver_En();
 *     UART2_BaudRate_Set(19200);
 *     if (UART2_isByteReceived() == TRUE)
 *     {
 *       ch = UART2_Get_Byte();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_Receiver_En(void);

/** \brief Disables Receiver of Serial Port (UART2).
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART2_Receiver_En();
 *     UART2_BaudRate_Set(19200);
 *     if (UART2_isByteReceived() == TRUE)
 *     {
 *       ch = UART2_Get_Byte();
 *     }
 *     UART2_Receiver_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_Receiver_Dis(void);

/** \brief Enables Baud-rate generator (UART2).
 * \note Setting new Baud-rate value must be when BaudRateGen is disabled.
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART2 (baudrate is equal to 19200 when frequency is equeal to 40MHz).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART2_Receiver_En();
 *     UART2_BaudRateGen_En();
 *     UART2_BaudRate_Value_Set(130);
 *     UART2_Fractional_Divider_Value_Set(7);
 *     UART2_BaudRateGen_Dis();
 *     if (UART2_isByteReceived() == TRUE)
 *     {
 *       ch = UART2_Get_Byte();
 *     }
 *     UART2_Receiver_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_BaudRateGen_En(void);

/** \brief Disables Baud-rate generator (UART2).
 * \note Setting new Baud-rate value must be when BaudRateGen is disabled.
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART2 (baudrate is equal to 19200 when frequency is equeal to 40MHz).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART2_Receiver_En();
 *     UART2_BaudRateGen_En();
 *     UART2_BaudRate_Value_Set(130);
 *     UART2_Fractional_Divider_Value_Set(7);
 *     UART2_BaudRateGen_Dis();
 *     if (UART2_isByteReceived() == TRUE)
 *     {
 *       ch = UART2_Get_Byte();
 *     }
 *     UART2_Receiver_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_BaudRateGen_Dis(void);

/** \brief Clears receive interrupt flag for UART1.
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART1_Receiver_En();
 *     UART1_BaudRate_Set(19200);
 *     if (UART1_isByteReceived() == TRUE)
 *     {
 *       ch = UART1_Buffer_Get();
 *       UART1_RX_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART1_RX_Int_Clr(void);

/** \brief Clears transmit interrupt flag for UART1.
 *
 * \brief <b>Example</b><br>
 * \brief This example sends "A" via UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART1_BaudRate_Set(19200);
 *     if (UART1_isByteTransmitted() == TRUE)
 *     {
 *       UART1_Buffer_Set(0x41);
 *       UART1_TX_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART1_TX_Int_Clr(void);

/** \brief Clears receive interrupt flag for UART2.
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART2_Receiver_En();
 *     UART2_BaudRate_Set(19200);
 *     if (UART2_isByteReceived() == TRUE)
 *     {
 *       ch = UART2_Buffer_Get();
 *       UART2_RX_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_RX_Int_Clr(void);

/** \brief Clears transmit interrupt flag for UART2.
 *
 * \brief <b>Example</b><br>
 * \brief This example sends "A" via UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART2_BaudRate_Set(19200);
 *     if (UART2_isByteTransmitted() == TRUE)
 *     {
 *       UART2_Buffer_Set(0x41);
 *       UART2_TX_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_TX_Int_Clr(void);

/** \brief Enables receive interrupt for UART1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the receive interrupt for UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART1_RX_Int_En();
 *     if (UART1_RX_Sts() == 1u)
 *     {
 *       UART1_RX_CALLBACK();
 *       UART1_RX_Int_Clr();
 *     }  
 *     UART1_RX_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART1_RX_Int_En(void);

/** \brief Disables receive interrupt for UART1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the receive interrupt for UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART1_RX_Int_En();
 *     if (UART1_RX_Sts() == 1u)
 *     {
 *       UART1_RX_CALLBACK();
 *       UART1_RX_Int_Clr();
 *     }  
 *     UART1_RX_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART1_RX_Int_Dis(void);

/** \brief Enables transmit interrupt for UART1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the transmit interrupt for UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART1_TX_Int_En();
 *     if (UART1_TX_Sts() == 1u)
 *     {
 *       UART1_TX_CALLBACK();
 *       UART1_TX_Int_Clr();
 *     }  
 *     UART1_TX_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART1_TX_Int_En(void);

/** \brief Disables transmit interrupt for UART1.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the transmit interrupt for UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART1_TX_Int_En();
 *     if (UART1_TX_Sts() == 1u)
 *     {
 *       UART1_TX_CALLBACK();
 *       UART1_TX_Int_Clr();
 *     }  
 *     UART1_TX_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART1_TX_Int_Dis(void);

/** \brief Enables receive interrupt for UART2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the receive interrupt for UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART2_RX_Int_En();
 *     if (UART2_RX_Sts() == 1u)
 *     {
 *       UART2_RX_CALLBACK();
 *       UART2_RX_Int_Clr();
 *     }  
 *     UART2_RX_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_RX_Int_En(void);

/** \brief Disables receive interrupt for UART2.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the receive interrupt for UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART2_RX_Int_En();
 *     if (UART2_RX_Sts() == 1u)
 *     {
 *       UART2_RX_CALLBACK();
 *       UART2_RX_Int_Clr();
 *     }  
 *     UART2_RX_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_RX_Int_Dis(void);

/** \brief Enables transmit interrupt for UART2.
 *
 * \brief <b>Example</b><br>
 * \brief This example the transmit interrupt for UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART2_TX_Int_En();
 *     if (UART2_TX_Sts() == 1u)
 *     {
 *       UART2_TX_CALLBACK();
 *       UART2_TX_Int_Clr();
 *     }  
 *     UART2_TX_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_TX_Int_En(void);

/** \brief Disables transmit interrupt for UART2.
 *
 * \brief <b>Example</b><br>
 * \brief This example the transmit interrupt for UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART2_TX_Int_En();
 *     if (UART2_TX_Sts() == 1u)
 *     {
 *       UART2_TX_CALLBACK();
 *       UART2_TX_Int_Clr();
 *     }  
 *     UART2_TX_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_TX_Int_Dis(void);

/** \brief Enables EXINT2 interrupt for UART2.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables/disables EXINT2 falling interrupt for UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART2_EXINT2_Int_En();
 *     EXINT2_Falling_Edge_Int_En();
 *     if ((uint8)SCU->IRCON0.bit.EXINT2F == (uint8)1)
 *     {
 *       EXINT2_FALLING_CALLBACK();
 *       EXINT2_Falling_Edge_Int_Clr();
 *     }
 *     UART2_EXINT2_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_EXINT2_Int_En(void);

/** \brief Disables EXINT2 interrupt for UART2.
 *
 * \brief <b>Example</b><br>
 * \brief This example enables/disables EXINT2 falling interrupt for UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART2_EXINT2_Int_En();
 *     EXINT2_Falling_Edge_Int_En();
 *     if ((uint8)SCU->IRCON0.bit.EXINT2F == (uint8)1)
 *     {
 *       EXINT2_FALLING_CALLBACK();
 *       EXINT2_Falling_Edge_Int_Clr();
 *     }  
 *     UART2_EXINT2_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_EXINT2_Int_Dis(void);

/** \brief Clears the UART1 Transmit interrupt and sends a Byte via UART1.
 *
 * \param c Byte to send
 *
 * \brief <b>Example</b><br>
 * \brief This example sends "A" via UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART1_BaudRate_Set(19200);
 *     if (UART1_isByteTransmitted() == TRUE)
 *     {
 *       UART1_Send_Byte(0x41);
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART1_Send_Byte(uint8 c);

/** \brief Sends a Byte via UART1.
 *
 * \param c Byte to send
 *
 * \brief <b>Example</b><br>
 * \brief This example sends "A" via UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART1_BaudRate_Set(19200);
 *     if (UART1_isByteTransmitted() == TRUE)
 *     {
 *       UART1_Buffer_Set(0x41);
 *       UART1_TX_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART1_Buffer_Set(uint8 c);

/** \brief Clears the UART1 receive interrupt and returns the UART1 buffer.
 *
 * \return Received Byte
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART1_Receiver_En();
 *     UART1_BaudRate_Set(19200);
 *     if (UART1_isByteReceived() == TRUE)
 *     {
 *       ch = UART1_Get_Byte();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE uint8 UART1_Get_Byte(void);

/** \brief Reads UART1 Buffer.
 *
 * \return Received Byte
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART1_Receiver_En();
 *     UART1_BaudRate_Set(19200);
 *     if (UART1_isByteReceived() == TRUE)
 *     {
 *       ch = UART1_Buffer_Get();
 *       UART1_RX_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE uint8 UART1_Buffer_Get(void);

/** \brief Checks if UART1 is receiving Byte or not.
 *
 * \retval TRUE a byte was received
 * \retval FALSE no byte was received
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART1_Receiver_En();
 *     UART1_BaudRate_Set(19200);
 *     if (UART1_isByteReceived() == TRUE)
 *     {
 *       ch = UART1_Get_Byte();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE bool UART1_isByteReceived(void);

/** \brief Checks if UART1 is transmitting Byte or not.
 *
 * \retval TRUE a byte was transmitted
 * \retval FALSE no byte was transmitted
 *
 * \brief <b>Example</b><br>
 * \brief This example sends "A" via UART1.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART1_BaudRate_Set(19200);
 *     if (UART1_isByteTransmitted() == TRUE)
 *     {
 *       UART1_Send_Byte(0x41);
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE bool UART1_isByteTransmitted(void);

/** \brief Clears the UART2 Transmit interrupt and sends a Byte via UART2.
 *
 * \param c Byte to send
 *
 * \brief <b>Example</b><br>
 * \brief This example sends "A" via UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART2_BaudRate_Set(19200);
 *     if (UART2_isByteTransmitted() == TRUE)
 *     {
 *       UART2_Send_Byte(0x41);
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_Send_Byte(uint8 c);

/** \brief Sends a Byte via UART2.
 *
 * \param c Byte to send
 *
 * \brief <b>Example</b><br>
 * \brief This example sends "A" via UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART2_BaudRate_Set(19200);
 *     if (UART2_isByteTransmitted() == TRUE)
 *     {
 *       UART2_Buffer_Set(0x41);
 *       UART2_TX_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_Buffer_Set(uint8 c);

/** \brief Clears the UART2 receive interrupt and returns the UART2 buffer.
 *
 * \return Received Byte
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART2_Receiver_En();
 *     UART2_BaudRate_Set(19200);
 *     if (UART2_isByteReceived() == TRUE)
 *     {
 *       ch = UART2_Get_Byte();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE uint8 UART2_Get_Byte(void);

/** \brief Reads UART2 Buffer.
 *
 * \return Received Byte
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART2_Receiver_En();
 *     UART2_BaudRate_Set(19200);
 *     if (UART2_isByteReceived() == TRUE)
 *     {
 *       ch = UART2_Buffer_Get();
 *       UART2_RX_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE uint8 UART2_Buffer_Get(void);

/** \brief Checks if UART2 is receiving Byte or not.
 *
 * \retval TRUE a byte was received
 * \retval FALSE no byte was receive
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART2_Receiver_En();
 *     UART2_BaudRate_Set(19200);
 *     if (UART2_isByteReceived() == TRUE)
 *     {
 *       ch = UART2_Get_Byte();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE bool UART2_isByteReceived(void);

/** \brief Checks if UART2 is transmitting Byte or not.
 *
 * \retval TRUE a byte was transmitted
 * \retval FALSE no byte was transmitted
 *
 * \brief <b>Example</b><br>
 * \brief This example sends "A" via UART2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     UART2_BaudRate_Set(19200);
 *     if (UART2_isByteTransmitted() == TRUE)
 *     {
 *       UART2_Send_Byte(0x41);
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE bool UART2_isByteTransmitted(void);

/** \brief Writes the baudrate timer register (UART1).
 * \note Setting new Baud-rate value must be when BaudRateGen is disabled.
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART1 (baud-rate is equal to 19200 when frequency is equal to 40MHz).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART1_Receiver_En();
 *     UART1_BaudRateGen_Dis();
 *     UART1_BaudRate_Value_Set(130);
 *     UART1_Fractional_Divider_Value_Set(7);
 *     UART1_BaudRateGen_En();
 *     if (UART1_isByteReceived() == TRUE)
 *     {
 *       ch = UART1_Get_Byte();
 *     }
 *     UART1_Receiver_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART1_BaudRate_Value_Set(uint16 br_val);

/** \brief Writes the Fractional Divider register (UART1).
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART1 (baud-rate is equal to 19200 when frequency is equal to 40MHz).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART1_Receiver_En();
 *     UART1_BaudRateGen_Dis();
 *     UART1_BaudRate_Value_Set(130);
 *     UART1_Fractional_Divider_Value_Set(7);
 *     UART1_BaudRateGen_En();
 *     if (UART1_isByteReceived() == TRUE)
 *     {
 *       ch = UART1_Get_Byte();
 *     }
 *     UART1_Receiver_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART1_Fractional_Divider_Value_Set(uint8 FD_val);

/** \brief Writes the baudrate timer register (UART2).
 * \note Setting new Baud-rate value must be when BaudRateGen is disabled.
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART2 (baud-rate is equal to 19200 when frequency is equal to 40MHz).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART2_Receiver_En();
 *     UART2_BaudRateGen_Dis();
 *     UART2_BaudRate_Value_Set(130);
 *     UART2_Fractional_Divider_Value_Set(7);
 *     UART2_BaudRateGen_En();
 *     if (UART2_isByteReceived() == TRUE)
 *     {
 *       ch = UART2_Get_Byte();
 *     }
 *     UART2_Receiver_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_BaudRate_Value_Set(uint16 br_val);

/** \brief Writes the Fractional Divider register (UART2).
 *
 * \brief <b>Example</b><br>
 * \brief This example receives a Byte via UART2 (baud-rate is equal to 19200 when frequency is equal to 40MHz).
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 ch;
 *
 *     UART2_Receiver_En();
 *     UART2_BaudRateGen_Dis();
 *     UART2_BaudRate_Value_Set(130);
 *     UART2_Fractional_Divider_Value_Set(7);
 *     UART2_BaudRateGen_En();
 *     if (UART2_isByteReceived() == TRUE)
 *     {
 *       ch = UART2_Get_Byte();
 *     }
 *     UART2_Receiver_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup uart_api
 */
INLINE void UART2_Fractional_Divider_Value_Set(uint8 FD_val);
  
/*******************************************************************************
**                         Inline Function Definitions                        **
*******************************************************************************/
INLINE void UART1_Receiver_En()
{
  Field_Mod32(&UART1->SCON.reg, (uint8)UART1_SCON_REN_Pos, UART1_SCON_REN_Msk, 1u);
}

INLINE void UART1_Receiver_Dis()
{
  Field_Mod32(&UART1->SCON.reg, (uint8)UART1_SCON_REN_Pos, UART1_SCON_REN_Msk, 0u);
}

INLINE void UART2_Receiver_En()
{
  Field_Mod32(&UART2->SCON.reg, (uint8)UART2_SCON_REN_Pos, UART2_SCON_REN_Msk, 1u);
}

INLINE void UART2_Receiver_Dis()
{
  Field_Mod32(&UART2->SCON.reg, (uint8)UART2_SCON_REN_Pos, UART2_SCON_REN_Msk, 0u);
}

INLINE uint8 UART1_RX_Sts()
{
  return(u1_Field_Rd32(&UART1->SCON.reg, (uint8)UART1_SCON_RI_Pos, UART1_SCON_RI_Msk));
}

INLINE bool UART1_isByteReceived(void)
{
  bool bRes = false;
  if (UART1_RX_Sts() == (uint8)1)
  {
    bRes = true;
  }
  return (bRes);
}

INLINE uint8 UART1_TX_Sts()
{
  return(u1_Field_Rd32(&UART1->SCON.reg, (uint8)UART1_SCON_TI_Pos, UART1_SCON_TI_Msk));
}

INLINE bool UART1_isByteTransmitted()
{
  bool bRes = false;
  if (UART1_TX_Sts() == (uint8)1)
  {
    bRes = true;
  }
  return (bRes);
}

INLINE uint8 UART2_RX_Sts()
{
  return(u1_Field_Rd32(&UART2->SCON.reg, (uint8)UART2_SCON_RI_Pos, UART2_SCON_RI_Msk));
}

INLINE bool UART2_isByteReceived(void)
{
  bool bRes = false;
  if (UART2_RX_Sts() == (uint8)1)
  {
    bRes = true;
  }
  return (bRes);
}

INLINE uint8 UART2_TX_Sts()
{
  return(u1_Field_Rd32(&UART2->SCON.reg, (uint8)UART2_SCON_TI_Pos, UART2_SCON_TI_Msk));
}

INLINE bool UART2_isByteTransmitted()
{
  bool bRes = false;
  if (UART2_TX_Sts() == (uint8)1)
  {
    bRes = true;
  }
  return (bRes);
}

INLINE uint8 UART1_Buffer_Get()
{
  return(u8_Field_Rd32(&UART1->SBUF.reg, (uint8)UART1_SBUF_VAL_Pos, UART1_SBUF_VAL_Msk));
}

INLINE uint8 UART1_Get_Byte()
{
  UART1_RX_Int_Clr();
  return(UART1_Buffer_Get());
}

INLINE void UART1_Buffer_Set(uint8 c)
{
  Field_Wrt32(&UART1->SBUF.reg, (uint8)UART1_SBUF_VAL_Pos, UART1_SBUF_VAL_Msk,(uint32)c);
}

INLINE void UART1_Send_Byte(uint8 c)
{
  UART1_TX_Int_Clr();
  UART1_Buffer_Set(c);
}

INLINE uint8 UART2_Buffer_Get()
{
  return(u8_Field_Rd32(&UART2->SBUF.reg, (uint8)UART2_SBUF_VAL_Pos, UART2_SBUF_VAL_Msk));
}

INLINE uint8 UART2_Get_Byte()
{
  UART2_RX_Int_Clr();
  return(UART2_Buffer_Get());
}

INLINE void UART2_Buffer_Set(uint8 c)
{
  Field_Wrt32(&UART2->SBUF.reg, (uint8)UART2_SBUF_VAL_Pos, UART2_SBUF_VAL_Msk,(uint32)c);
}

INLINE void UART2_Send_Byte(uint8 c)
{
  UART2_TX_Int_Clr();
  UART2_Buffer_Set(c);
}

INLINE void UART2_BaudRateGen_En()
{
  Field_Mod32(&SCU->BCON2.reg, (uint8)SCU_BCON2_BR2_R_Pos, SCU_BCON2_BR2_R_Msk, 1u);
}

INLINE void UART2_BaudRateGen_Dis()
{
  Field_Mod32(&SCU->BCON2.reg, (uint8)SCU_BCON2_BR2_R_Pos, SCU_BCON2_BR2_R_Msk, 0u);
}

INLINE void UART1_BaudRateGen_En()
{
  Field_Mod32(&SCU->BCON1.reg, (uint8)SCU_BCON1_BR1_R_Pos, SCU_BCON1_BR1_R_Msk, 1u);
}

INLINE void UART1_BaudRateGen_Dis()
{
  Field_Mod32(&SCU->BCON1.reg, (uint8)SCU_BCON1_BR1_R_Pos, SCU_BCON1_BR1_R_Msk, 0u);
}

INLINE void UART1_RX_Int_Clr()
{
  Field_Wrt32(&UART1->SCONCLR.reg, (uint8)UART1_SCONCLR_RICLR_Pos, UART1_SCONCLR_RICLR_Msk, 1u);
}

INLINE void UART1_TX_Int_Clr()
{
  Field_Wrt32(&UART1->SCONCLR.reg, (uint8)UART1_SCONCLR_TICLR_Pos, UART1_SCONCLR_TICLR_Msk, 1u);
}

INLINE void UART2_RX_Int_Clr()
{
  Field_Wrt32(&UART2->SCONCLR.reg, (uint8)UART2_SCONCLR_RICLR_Pos, UART2_SCONCLR_RICLR_Msk, 1u);
}

INLINE void UART2_TX_Int_Clr()
{
  Field_Wrt32(&UART2->SCONCLR.reg, (uint8)UART2_SCONCLR_TICLR_Pos, UART2_SCONCLR_TICLR_Msk, 1u);
}

INLINE void UART1_RX_Int_En()
{
  Field_Mod32(&SCU->MODIEN2.reg, (uint8)SCU_MODIEN2_RIEN1_Pos, SCU_MODIEN2_RIEN1_Msk, 1u);
}

INLINE void UART1_RX_Int_Dis()
{
  Field_Mod32(&SCU->MODIEN2.reg, (uint8)SCU_MODIEN2_RIEN1_Pos, SCU_MODIEN2_RIEN1_Msk, 0u);
}

INLINE void UART1_TX_Int_En()
{
  Field_Mod32(&SCU->MODIEN2.reg, (uint8)SCU_MODIEN2_TIEN1_Pos, SCU_MODIEN2_TIEN1_Msk, 1u);
}

INLINE void UART1_TX_Int_Dis()
{
  Field_Mod32(&SCU->MODIEN2.reg, (uint8)SCU_MODIEN2_TIEN1_Pos, SCU_MODIEN2_TIEN1_Msk, 0u);
}

INLINE void UART2_RX_Int_En()
{
  Field_Mod32(&SCU->MODIEN2.reg, (uint8)SCU_MODIEN2_RIEN2_Pos, SCU_MODIEN2_RIEN2_Msk, 1u);
}

INLINE void UART2_RX_Int_Dis()
{
  Field_Mod32(&SCU->MODIEN2.reg, (uint8)SCU_MODIEN2_RIEN2_Pos, SCU_MODIEN2_RIEN2_Msk, 0u);
}

INLINE void UART2_TX_Int_En()
{
  Field_Mod32(&SCU->MODIEN2.reg, (uint8)SCU_MODIEN2_TIEN2_Pos, SCU_MODIEN2_TIEN2_Msk, 1u);
}

INLINE void UART2_TX_Int_Dis()
{
  Field_Mod32(&SCU->MODIEN2.reg, (uint8)SCU_MODIEN2_TIEN2_Pos, SCU_MODIEN2_TIEN2_Msk, 0u);
}

INLINE void UART2_EXINT2_Int_En()
{
  Field_Mod32(&SCU->MODIEN2.reg, (uint8)SCU_MODIEN2_EXINT2_EN_Pos, SCU_MODIEN2_EXINT2_EN_Msk, 1u);
}

INLINE void UART2_EXINT2_Int_Dis()
{
  Field_Mod32(&SCU->MODIEN2.reg, (uint8)SCU_MODIEN2_EXINT2_EN_Pos, SCU_MODIEN2_EXINT2_EN_Msk, 0u);
}

INLINE void UART1_BaudRate_Value_Set(uint16 br_val)
{
  Field_Mod32(&SCU->BG1.reg, (uint8)SCU_BG1_BG1_BR_VALUE_Pos, SCU_BG1_BG1_BR_VALUE_Msk, br_val);  
}

INLINE void UART1_Fractional_Divider_Value_Set(uint8 FD_val)
{
  Field_Wrt32(&SCU->BGL1.reg, (uint8)SCU_BGL1_BG1_FD_SEL_Pos, SCU_BGL1_BG1_FD_SEL_Msk, FD_val);
}

INLINE void UART2_BaudRate_Value_Set(uint16 br_val)
{
  Field_Mod32(&SCU->BG2.reg, (uint8)SCU_BG2_BG2_BR_VALUE_Pos, SCU_BG2_BG2_BR_VALUE_Msk, br_val);  
}

INLINE void UART2_Fractional_Divider_Value_Set(uint8 FD_val)
{
  Field_Wrt32(&SCU->BGL2.reg, (uint8)SCU_BGL2_BG2_FD_SEL_Pos, SCU_BGL2_BG2_FD_SEL_Msk, FD_val);
}
#endif
