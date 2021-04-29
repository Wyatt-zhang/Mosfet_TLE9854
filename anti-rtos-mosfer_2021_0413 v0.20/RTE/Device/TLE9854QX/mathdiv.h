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
 * \file     mathdiv.h
 *
 * \brief    MATH DIV low level access library
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
** KC           Kay Claussen                                                  **
** TS           T&S                                                           **
** BG           Blandine Guillot                                              **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V0.2.0: 2018-02-13, TS:   Initial version of revision history              **
** V0.2.1: 2018-09-20, KC:   Initialization order of register changed         **
** V0.2.2: 2019-01-28, TS:   __STATIC_INLINE changed to INLINE                **
**                           Doxygen update                                   **
**                           Revision history moved from math.c to math.h     **
** V0.2.3: 2020-03-02, BG:   Updated revision history format                  **
*******************************************************************************/

#ifndef MATH_H
#define MATH_H

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle985x.h"
#include "types.h"
#include "sfr_access.h"

/*******************************************************************************
**                          Global Type Definitions                           **
*******************************************************************************/
/** \enum TMath_Sus_Cfg
 *  \brief This enum lists the MATH Suspend Mode
 */
typedef enum
{
  Ch_MATH_Sus_Off   = 0u,    /**< \brief Suspend disabled                       */
  Ch_MATH_Sus_Hard  = 1u,    /**< \brief Hard Suspend                           */
  Ch_MATH_Sus_Soft  = 2u     /**< \brief Soft Suspend                           */
} TMath_Sus_Cfg;

/** \enum TMath_Chain_Cfg
 *  \brief This enum lists the MATH Chain Configuration
 */
typedef enum
{
  Ch_MATH_Chain_Off  = 0u,   /**< \brief No result chaining is selected      */
  Ch_MATH_Chain_QUOT = 1u,   /**< \brief QUOT register is the selected source   */
  Ch_MATH_Chain_RMD  = 2u    /**< \brief RMD register is the selected source    */
} TMath_Chain_Cfg;

/** \enum TMath_DIVMode_Cfg
 *  \brief This enum lists the MATH Division Configuation
 */
typedef enum
{
  Ch_MATH_DIVMode_32_32  = 0u,   /**< \brief 32-bit divide by 32-bit            */
  Ch_MATH_DIVMode_32_16  = 1u,   /**< \brief 32-bit divide by 16-bit            */
  Ch_MATH_DIVMode_16_16  = 2u    /**< \brief 16-bit divide by 16-bit            */
} TMath_DIVMode_Cfg;

/** \enum TMath_STMode_Cfg
 *  \brief This enum lists the MATH Start MOde Configuation
 */
typedef enum
{
  Ch_MATH_STMode_Auto   = 0u,   /**< \brief Start Automatically                 */
  Ch_MATH_STMode_Manual = 1u    /**< \brief Start Manually                      */
} TMath_STMode_Cfg;


/*******************************************************************************
**                       Global Function Declarations                         **
*******************************************************************************/
/** \brief Initializes the math divider module.
 *
 * \ingroup math_api
 */
void MATH_Init(void);

/*******************************************************************************
**                       Inline Function Declarations                         **
*******************************************************************************/
/** \brief Starts the division operation.
 *
 * \brief <b>Example</b><br>
 * \brief This example starts the calculation of the division operation when it is configured manually.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MATH_STMODE_Set(Ch_MATH_STMode_Manual);
 *     MATH_DIV_START();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup math_api
 */
INLINE void MATH_DIV_START(void);

/** \brief Reads the Busy Indication.
 *
 * \return Busy Indication
 *
 * \brief <b>Example</b><br>
 * \brief This example waits until finishing the division operation.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MATH_DIV_START();  
 *     while (MATH_BSY_Sts() == 1u);
 *     {
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup math_api
 */
INLINE uint8 MATH_BSY_Sts(void);

/** \brief Clears the Divider End of Calculation Event Flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Divider End of Calculation Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MATH_DIVEOC_Int_En();
 *     if ((uint8)MATH->EVFR.bit.DIVEOC == (uint8)1)
 *     {
 *      MATH_DIVEOC_CALLBACK();
 *      MATH_DIVEOC_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup math_api
 */
INLINE void MATH_DIVEOC_Int_Clr(void);

/** \brief Clears the Divider Error Event Flag.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Divider Error Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MATH_DIVERR_Int_En();
 *     if ((uint8)MATH->EVFR.bit.DIVERR == (uint8)1)
 *     {
 *      MATH_DIVERR_CALLBACK();
 *      MATH_DIVERR_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup math_api
 */
INLINE void MATH_DIVERR_Int_Clr(void);

/** \brief Enables the Divider End of Calculation Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Divider End of Calculation Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MATH_DIVEOC_Int_En();
 *     if ((uint8)MATH->EVFR.bit.DIVEOC == (uint8)1)
 *     {
 *      MATH_DIVEOC_CALLBACK();
 *      MATH_DIVEOC_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup math_api
 */
INLINE void MATH_DIVEOC_Int_En(void);

/** \brief Disables the Divider End of Calculation Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Divider End of Calculation Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MATH_DIVEOC_Int_En();
 *     if ((uint8)MATH->EVFR.bit.DIVEOC == (uint8)1)
 *     {
 *      MATH_DIVEOC_CALLBACK();
 *      MATH_DIVEOC_Int_Clr();
 *     }
 *     MATH_DIVEOC_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup math_api
 */
INLINE void MATH_DIVEOC_Int_Dis(void);

/** \brief Enables the Divider Error Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Divider Error Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MATH_DIVERR_Int_En();
 *     if ((uint8)MATH->EVFR.bit.DIVERR == (uint8)1)
 *     {
 *      MATH_DIVERR_CALLBACK();
 *      MATH_DIVERR_Int_Clr();
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup math_api
 */
INLINE void MATH_DIVERR_Int_En(void);

/** \brief Disables the Divider Error Interrupt.
 *
 * \brief <b>Example</b><br>
 * \brief This example treats the Divider Error Interrupt.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MATH_DIVERR_Int_En();
 *     if ((uint8)MATH->EVFR.bit.DIVERR == (uint8)1)
 *     {
 *      MATH_DIVERR_CALLBACK();
 *      MATH_DIVERR_Int_Clr();
 *     }
 *     MATH_DIVERR_Int_Dis();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup math_api
 */
INLINE void MATH_DIVERR_Int_Dis(void);  

/** \brief Sets the Suspend Configuration
 *
 * \param MATH_SUS_Cfg MATH Suspend Configuration, see \link TMath_Sus_Cfg \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example configures the Suspend Mode to hard suspend.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MATH_Suspend_Conf(Ch_MATH_Sus_Hard);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup math_api
 */
INLINE void MATH_Suspend_Conf(TMath_Sus_Cfg MATH_SUS_Cfg);

/** \brief Sets the Divisor Chaining
 *
 * \param MATH_CHAIN_Cfg MATH Divisor Chaining Configuration, see \link TMath_Chain_Cfg \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example selects the QUOT register as Divisor Register Result Chaining.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MATH_DVS_Chain(Ch_MATH_Chain_QUOT);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup math_api
 */
INLINE void MATH_DVS_Chain(TMath_Chain_Cfg MATH_CHAIN_Cfg);

/** \brief Sets the Dividend Chaining
 *
 * \param MATH_CHAIN_Cfg MATH Divisor Chaining Configuration, see \link TMath_Chain_Cfg \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example selects the RMD register as Dividend Register Result Chaining.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MATH_DVD_Chain(Ch_MATH_Chain_RMD);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup math_api
 */
INLINE void MATH_DVD_Chain(TMath_Chain_Cfg MATH_CHAIN_Cfg);

/** \brief Sets the Divisor Value
 *
 * \param VALUE Divisor Value
 *
 * \brief <b>Example</b><br>
 * \brief This example configures DVD and DVS to calculate the division operation 25/5 and checks the QUOT and RMD values.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MATH_DVD_Set(25);
 *     while (MATH_DVS_Read() != 25)
 *     {
 *     }
 *     MATH_DVS_Set(5);
 *     while (MATH_DVD_Read() != 5)
 *     {
 *     }
 *     if ((MATH_QUOT_Read() == 5) && (MATH_RMD_Read() == 0));
 *     {
 *         //Correct QUOT and RMD values
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup math_api
 */
INLINE void MATH_DVS_Set(uint32 VALUE);

/** \brief Sets the Dividend Value
 *
 * \param VALUE Dividend Value
 *
 * \brief <b>Example</b><br>
 * \brief This example configures DVD and DVS to calculate the division operation 25/5 and checks the QUOT and RMD values.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MATH_DVD_Set(25);
 *     while (MATH_DVS_Read() != 25)
 *     {
 *     }
 *     MATH_DVS_Set(5);
 *     while (MATH_DVD_Read() != 5)
 *     {
 *     }
 *     if ((MATH_QUOT_Read() == 5) && (MATH_RMD_Read() == 0));
 *     {
 *         //Correct QUOT and RMD values
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup math_api
 */
INLINE void MATH_DVD_Set(uint32 VALUE);

/** \brief Reads the Divisor Value
 *
 * \return Divisor Value
 *
 * \brief <b>Example</b><br>
 * \brief This example configures DVD and DVS to calculate the division operation 25/5 and checks the QUOT and RMD values.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MATH_DVD_Set(25);
 *     while (MATH_DVS_Read() != 25)
 *     {
 *     }
 *     MATH_DVS_Set(5);
 *     while (MATH_DVD_Read() != 5)
 *     {
 *     }
 *     if ((MATH_QUOT_Read() == 5) && (MATH_RMD_Read() == 0));
 *     {
 *         //Correct QUOT and RMD values
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup math_api
 */
INLINE uint32 MATH_DVS_Read(void);

/** \brief Reads the Dividend Value
 *
 * \return Dividend Value
 *
 * \brief <b>Example</b><br>
 * \brief This example configures DVD and DVS to calculate the division operation 25/5 and checks the QUOT and RMD values.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MATH_DVD_Set(25);
 *     while (MATH_DVS_Read() != 25)
 *     {
 *     }
 *     MATH_DVS_Set(5);
 *     while (MATH_DVD_Read() != 5)
 *     {
 *     }
 *     if ((MATH_QUOT_Read() == 5) && (MATH_RMD_Read() == 0));
 *     {
 *         //Correct QUOT and RMD values
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup math_api
 */
INLINE uint32 MATH_DVD_Read(void);

/** \brief Reads the Quotient Value
 *
 * \return Quotient Value
 *
 * \brief <b>Example</b><br>
 * \brief This example configures DVD and DVS to calculate the division operation 25/5 and checks the QUOT and RMD values.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MATH_DVD_Set(25);
 *     while (MATH_DVS_Read() != 25)
 *     {
 *     }
 *     MATH_DVS_Set(5);
 *     while (MATH_DVD_Read() != 5)
 *     {
 *     }
 *     if ((MATH_QUOT_Read() == 5) && (MATH_RMD_Read() == 0));
 *     {
 *         //Correct QUOT and RMD values
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup math_api
 */
INLINE uint32 MATH_QUOT_Read(void);

/** \brief Reads the Remainder Value
 *
 * \return Remainder Value
 *
 * \brief <b>Example</b><br>
 * \brief This example configures DVD and DVS to calculate the division operation 25/5 and checks the QUOT and RMD values.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MATH_DVD_Set(25);
 *     while (MATH_DVS_Read() != 25)
 *     {
 *     }
 *     MATH_DVS_Set(5);
 *     while (MATH_DVD_Read() != 5)
 *     {
 *     }
 *     if ((MATH_QUOT_Read() == 5) && (MATH_RMD_Read() == 0));
 *     {
 *         //Correct QUOT and RMD values
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup math_api
 */
INLINE uint32 MATH_RMD_Read(void);

/** \brief Sets the Division Mode
 *
 * \param MATH_DIVMODE_Cfg MATH Division Mode Configuration, see \link TMath_DIVMode_Cfg \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example selects the the 16-16 Division Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MATH_DIVMODE_Set(Ch_MATH_DIVMode_16_16);
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup math_api
 */
INLINE void MATH_DIVMODE_Set(TMath_DIVMode_Cfg MATH_DIVMODE_Cfg);

/** \brief Sets the Start Mode
 *
 * \param MATH_STMODE_Cfg MATH Start Mode Configuration, see \link TMath_STMode_Cfg \endlink
 *
 * \brief <b>Example</b><br>
 * \brief This example starts the calculation of the division operation when it is configured manually.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MATH_STMODE_Set(Ch_MATH_STMode_Manual);
 *     while (MATH_STMODE_Read() != 1)
 *     {
 *     }
 *     MATH_DIV_START();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup math_api
 */
INLINE void MATH_STMODE_Set(TMath_STMode_Cfg MATH_STMODE_Cfg);

/** \brief Reads the Division Mode.
 *
 * \return Division Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example reads the Division Mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 sts;
 *
 *     sts = MATH_DIVMODE_Read();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup math_api
 */
INLINE uint8 MATH_DIVMODE_Read(void);

/** \brief Reads the Start Mode
 *
 * \return Start Mode
 *
 * \brief <b>Example</b><br>
 * \brief This example starts the calculation of the division operation when it is configured manually.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     MATH_STMODE_Set(Ch_MATH_STMode_Manual);
 *     while (MATH_STMODE_Read() != 1)
 *     {
 *     }
 *     MATH_DIV_START();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup math_api
 */
INLINE uint8 MATH_STMODE_Read(void);

/*******************************************************************************
**                        Inline Function Definitions                         **
*******************************************************************************/
INLINE void MATH_DIV_START()
{
  Field_Mod32(&MATH->DIVCON.reg, (uint8)MATH_DIVCON_ST_Pos, MATH_DIVCON_ST_Msk, 1u);
}

INLINE uint8 MATH_BSY_Sts()
{
  return(u1_Field_Rd32(&MATH->DIVST.reg, (uint8)MATH_DIVST_BSY_Pos, MATH_DIVST_BSY_Msk));
}

INLINE void MATH_DIVEOC_Int_Clr()
{
  Field_Wrt32(&MATH->EVFCR.reg, (uint8)MATH_EVFCR_DIVEOCC_Pos, MATH_EVFCR_DIVEOCC_Msk, 1u);
}

INLINE void MATH_DIVERR_Int_Clr()
{
  Field_Wrt32(&MATH->EVFCR.reg, (uint8)MATH_EVFCR_DIVERRC_Pos, MATH_EVFCR_DIVERRC_Msk, 1u);
}

INLINE void MATH_DIVEOC_Int_En()
{
  Field_Mod32(&MATH->EVIER.reg, (uint8)MATH_EVIER_DIVEOCIEN_Pos, MATH_EVIER_DIVEOCIEN_Msk, 1u);
}

INLINE void MATH_DIVEOC_Int_Dis()
{
  Field_Mod32(&MATH->EVIER.reg, (uint8)MATH_EVIER_DIVEOCIEN_Pos, MATH_EVIER_DIVEOCIEN_Msk, 0u);
}

INLINE void MATH_DIVERR_Int_En()
{
  Field_Mod32(&MATH->EVIER.reg, (uint8)MATH_EVIER_DIVERRIEN_Pos, MATH_EVIER_DIVERRIEN_Msk, 1u);
}

INLINE void MATH_DIVERR_Int_Dis()
{
  Field_Mod32(&MATH->EVIER.reg, (uint8)MATH_EVIER_DIVERRIEN_Pos, MATH_EVIER_DIVERRIEN_Msk, 0u);
}

INLINE void MATH_Suspend_Conf(TMath_Sus_Cfg MATH_SUS_Cfg)
{
  Field_Mod32(&MATH->GLBCON.reg, (uint8)MATH_GLBCON_SUSCFG_Pos, MATH_GLBCON_SUSCFG_Msk, (uint8)MATH_SUS_Cfg);  
}

INLINE void MATH_DVS_Chain(TMath_Chain_Cfg MATH_CHAIN_Cfg)
{
  Field_Mod32(&MATH->GLBCON.reg, (uint8)MATH_GLBCON_DVSRC_Pos, MATH_GLBCON_DVSRC_Msk, (uint8)MATH_CHAIN_Cfg);  
}

INLINE void MATH_DVD_Chain(TMath_Chain_Cfg MATH_CHAIN_Cfg)
{
  Field_Mod32(&MATH->GLBCON.reg, (uint8)MATH_GLBCON_DVDRC_Pos, MATH_GLBCON_DVDRC_Msk, (uint8)MATH_CHAIN_Cfg);    
}

INLINE void MATH_DVS_Set(uint32 VALUE)
{
  Field_Wrt32(&MATH->DVS.reg, (uint8)MATH_DVS_VAL_Pos, MATH_DVS_VAL_Msk, VALUE);    
}

INLINE void MATH_DVD_Set(uint32 VALUE)
{
  Field_Wrt32(&MATH->DVD.reg, (uint8)MATH_DVD_VAL_Pos, MATH_DVD_VAL_Msk, VALUE);    
}

INLINE uint32 MATH_DVS_Read(void)
{
  return(u32_Field_Rd32(&MATH->DVS.reg, (uint8)MATH_DVS_VAL_Pos, MATH_DVS_VAL_Msk));  
}

INLINE uint32 MATH_DVD_Read(void)
{
  return(u32_Field_Rd32(&MATH->DVD.reg, (uint8)MATH_DVD_VAL_Pos, MATH_DVD_VAL_Msk));    
}

INLINE uint32 MATH_QUOT_Read(void)
{
  return(u32_Field_Rd32(&MATH->QUOT.reg, (uint8)MATH_QUOT_VAL_Pos, MATH_QUOT_VAL_Msk));    
}

INLINE uint32 MATH_RMD_Read(void)
{
  return(u32_Field_Rd32(&MATH->RMD.reg, (uint8)MATH_RMD_VAL_Pos, MATH_RMD_VAL_Msk));    
}

INLINE void MATH_DIVMODE_Set(TMath_DIVMode_Cfg MATH_DIVMODE_Cfg)
{
  Field_Mod32(&MATH->DIVCON.reg, (uint8)MATH_DIVCON_DIVMODE_Pos, MATH_DIVCON_DIVMODE_Msk, (uint8)MATH_DIVMODE_Cfg);    
}

INLINE void MATH_STMODE_Set(TMath_STMode_Cfg MATH_STMODE_Cfg)
{
  Field_Mod32(&MATH->DIVCON.reg, (uint8)MATH_DIVCON_STMODE_Pos, MATH_DIVCON_STMODE_Msk, (uint8)MATH_STMODE_Cfg);    
}

INLINE uint8 MATH_DIVMODE_Read(void)
{
  return(u8_Field_Rd32(&MATH->DIVCON.reg, (uint8)MATH_DIVCON_DIVMODE_Pos, MATH_DIVCON_DIVMODE_Msk));    
}

INLINE uint8 MATH_STMODE_Read(void)
{
  return(u1_Field_Rd32(&MATH->DIVCON.reg, (uint8)MATH_DIVCON_STMODE_Pos, MATH_DIVCON_STMODE_Msk));    
}

#endif
