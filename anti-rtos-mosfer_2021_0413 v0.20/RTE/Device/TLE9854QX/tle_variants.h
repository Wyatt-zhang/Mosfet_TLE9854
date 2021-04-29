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
 * \file     tle_variants.h
 *
 * \brief    Device specific memory layout defines
 *
 * \version  V0.1.2
 * \date     02. Mar 2020
 *
 *  \note This file violates [MISRA 2012 Rule 2.5, advisory]
 */

/*******************************************************************************
**                             Author(s) Identity                             **
********************************************************************************
**                                                                            **
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** DM           Daniel Mysliwitz                                              **
** JO           Julia Ott                                                     **
** BG           Blandine Guillot                                              **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V0.1.0: 2018-12-10, DM:   Initial version                                  **
** V0.1.1: 2018-12-10, JO:   Added devices TLE9850QX, TLE9852QX, TLE9854QXW   **
**                           Added define UC_FEATURE_HB2 where needed         **
** V0.1.2: 2020-03-02, BG:   Updated revision history format                  **
*******************************************************************************/


#ifndef _TLE_VARIANTS_H
#define _TLE_VARIANTS_H

/* Family definitions  */
#define TLE98      (98)

/* Series definitions  */
#define TLE984     (984)
#define TLE985     (985)
#define TLE986     (986)
#define TLE987     (987)

/* Device definitions  */
#define TLE9851    (9851)
#define TLE9853    (9853)
#define TLE9854    (9854)
#define TLE9855    (9855)

/* Package definitions */
#define BGA144     (1)
#define LQFP144    (2)
#define LQFP100    (3)
#define BGA64      (4)
#define LQFP64     (5)
#define VQFN48     (6)
#define TSSOP38    (7)
#define TSSOP28    (8)
#define TSSOP16    (9) 
#define VQFN24     (10)
#define VQFN40     (11)

#if defined(TLE9850QX)
#define UC_FAMILY       TLE98
#define UC_SERIES       TLE985
#define UC_DEVICE       TLE9850
#define UC_PACKAGE      VQFN48
#define UC_FLASH        (48UL)
#define ProgFlashSize   (0xB000U)
#define RAMSize         (0x1000U)

#elif defined(TLE9851QXW)
#define UC_FAMILY       TLE98
#define UC_SERIES       TLE985
#define UC_DEVICE       TLE9851
#define UC_PACKAGE      VQFN48
#define UC_FLASH        (64UL)
#define ProgFlashSize   (0xF000U)
#define RAMSize         (0x1000U)

#elif defined(TLE9852QX)
#define UC_FAMILY       TLE98
#define UC_SERIES       TLE985
#define UC_DEVICE       TLE9853
#define UC_PACKAGE      VQFN48
#define UC_FLASH        (48UL)
#define UC_FEATURE_HB2
#define ProgFlashSize   (0xB000U)
#define RAMSize         (0x1000U)

#elif defined(TLE9853QX)
#define UC_FAMILY       TLE98
#define UC_SERIES       TLE985
#define UC_DEVICE       TLE9853
#define UC_PACKAGE      VQFN48
#define UC_FLASH        (48UL)
#define UC_FEATURE_HB2
#define ProgFlashSize   (0xB000U)
#define RAMSize         (0x1000U)

#elif defined(TLE9854QX)
#define UC_FAMILY       TLE98
#define UC_SERIES       TLE985
#define UC_DEVICE       TLE9854
#define UC_PACKAGE      VQFN48
#define UC_FLASH        (64UL)
#define UC_FEATURE_HB2
#define ProgFlashSize   (0xF000U)
#define RAMSize         (0x1000U)

#elif defined(TLE9854QXW)
#define UC_FAMILY       TLE98
#define UC_SERIES       TLE985
#define UC_DEVICE       TLE9854
#define UC_PACKAGE      VQFN48
#define UC_FLASH        (64UL)
#define UC_FEATURE_HB2
#define ProgFlashSize   (0xF000U)
#define RAMSize         (0x1000U)

#elif defined(TLE9855QX)
#define UC_FAMILY       TLE98
#define UC_SERIES       TLE985
#define UC_DEVICE       TLE9855
#define UC_PACKAGE      VQFN48
#define UC_FLASH        (96UL)
#define UC_FEATURE_HB2
#define ProgFlashSize   (0x17000U)
#define RAMSize         (0x1000U)

#elif defined(TLE9851QXW_int)
#define UC_FAMILY       TLE98
#define UC_SERIES       TLE985
#define UC_DEVICE       TLE9851
#define UC_PACKAGE      VQFN48
#define UC_FLASH        (64UL)
#define UC_intern
#define ProgFlashSize   (0xF000U)
#define RAMSize         (0x1000U)

#elif defined(TLE9853QX_int)
#define UC_FAMILY       TLE98
#define UC_SERIES       TLE985
#define UC_DEVICE       TLE9853
#define UC_PACKAGE      VQFN48
#define UC_FLASH        (48UL)
#define UC_intern
#define UC_FEATURE_HB2
#define ProgFlashSize   (0xB000U)
#define RAMSize         (0x1000U)

#elif defined(TLE9854QX_int)
#define UC_FAMILY       TLE98
#define UC_SERIES       TLE985
#define UC_DEVICE       TLE9854
#define UC_PACKAGE      VQFN48
#define UC_FLASH        (64UL)
#define UC_intern
#define UC_FEATURE_HB2
#define ProgFlashSize   (0xF000U)
#define RAMSize         (0x1000U)

#elif defined(TLE9855QX_int)
#define UC_FAMILY       TLE98
#define UC_SERIES       TLE985
#define UC_DEVICE       TLE9855
#define UC_PACKAGE      VQFN48
#define UC_FLASH        (96UL)
#define UC_intern
#define UC_FEATURE_HB2
#define ProgFlashSize   (0x17000U)
#define RAMSize         (0x1000U)

#else
#error "tle_device.h: device not supported"
#endif 	    
/*----------------------------------------------------------------------------
  Define Memory
 *----------------------------------------------------------------------------*/
#define ProgFlashStart  (0x11000000U)      /* Start Address of the flash      */
#define DataFlashStart  (ProgFlashStart + ProgFlashSize)
#define DataFlashSize   (0x1000U)          /* 4KB Data Flash                  */
#define RAMStart        (0x18000000UL)     /* Start Address of the SRAM       */

#if (UC_SERIES == 985)
  #include "TLE985x.h"
#endif

#endif
