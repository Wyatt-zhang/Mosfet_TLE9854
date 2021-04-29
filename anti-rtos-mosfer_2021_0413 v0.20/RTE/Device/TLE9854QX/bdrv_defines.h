/**
 * @cond
 ***********************************************************************************************************************
 *
 * Copyright (c) 2018, Infineon Technologies AG
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
#ifndef BDRV_DEFINES_H
#define BDRV_DEFINES_H

/* XML Version 1.1.0 */
#define BDRV_XML_VERSION (10100)

#define BDRV_CPCLKDIS_En (0x0) /*decimal 0*/

#define BDRV_CP_CLK (0xFA) /*decimal 250*/

#define BDRV_CP_CLK_CTRL (0xD21F) /*decimal 53791*/

#define BDRV_CP_CLK_SRC (0x1312D00) /*decimal 20000000*/

#define BDRV_CP_CTRL (0x30001) /*decimal 196609*/

#define BDRV_CP_IRQEN (0x0) /*decimal 0*/

#define BDRV_CTRL2 (0x0) /*decimal 0*/

#define BDRV_CTRL3 (0x30000) /*decimal 196608*/

#define BDRV_IGATECLMPOFFC (0x707) /*decimal 1799*/

#define BDRV_IGATECLMPONC (0x707) /*decimal 1799*/

#define BDRV_IRQEN (0x0) /*decimal 0*/

#define BDRV_LO_DITH (210.53)

#define BDRV_LO_DITH_FREQ (0xD1) /*decimal 209*/

#define BDRV_OFFSEQHB1IC (0x2) /*decimal 2*/

#define BDRV_OFFSEQHB1TC (0x3020206) /*decimal 50463238*/

#define BDRV_OFFSEQHB1TC_HB1_T1OFF_Value (0x15E) /*decimal 350*/

#define BDRV_OFFSEQHB1TC_HB1_T2OFF_Value (0x96) /*decimal 150*/

#define BDRV_OFFSEQHB1TC_HB1_T3OFF_Value (0x96) /*decimal 150*/

#define BDRV_OFFSEQHB1TC_HB1_T4OFF_Value (0xC8) /*decimal 200*/

#define BDRV_OFFSEQHB2IC (0x0) /*decimal 0*/

#define BDRV_OFFSEQHB2TC (0x3020206) /*decimal 50463238*/

#define BDRV_OFFSEQHB2TC_HB2_T1OFF_Value (0x15E) /*decimal 350*/

#define BDRV_OFFSEQHB2TC_HB2_T2OFF_Value (0x96) /*decimal 150*/

#define BDRV_OFFSEQHB2TC_HB2_T3OFF_Value (0x96) /*decimal 150*/

#define BDRV_OFFSEQHB2TC_HB2_T4OFF_Value (0xC8) /*decimal 200*/

#define BDRV_ONSEQHB1IC (0x20030302) /*decimal 537068290*/

#define BDRV_ONSEQHB1TC (0x3020206) /*decimal 50463238*/

#define BDRV_ONSEQHB1TC_HB1_T1ON_Value (0x15E) /*decimal 350*/

#define BDRV_ONSEQHB1TC_HB1_T2ON_Value (0x96) /*decimal 150*/

#define BDRV_ONSEQHB1TC_HB1_T3ON_Value (0x96) /*decimal 150*/

#define BDRV_ONSEQHB1TC_HB1_T4ON_Value (0xC8) /*decimal 200*/

#define BDRV_ONSEQHB2IC (0x0) /*decimal 0*/

#define BDRV_ONSEQHB2TC (0x3020206) /*decimal 50463238*/

#define BDRV_ONSEQHB2TC_HB2_T1ON_Value (0x15E) /*decimal 350*/

#define BDRV_ONSEQHB2TC_HB2_T2ON_Value (0x96) /*decimal 150*/

#define BDRV_ONSEQHB2TC_HB2_T3ON_Value (0x96) /*decimal 150*/

#define BDRV_ONSEQHB2TC_HB2_T4ON_Value (0xC8) /*decimal 200*/

#define BDRV_OUT_VOLT (0x0) /*decimal 0*/

#define BDRV_PWMSRCSEL (0x8001A) /*decimal 524314*/

#define BDRV_SEQAFHB1CD (0x4040) /*decimal 16448*/

#define BDRV_SEQAFHB1CD_HB1_AF_OFF_Value (0xCB2) /*decimal 3250*/

#define BDRV_SEQAFHB1CD_HB1_AF_ON_Value (0xCB2) /*decimal 3250*/

#define BDRV_SEQAFHB1IC (0x200020) /*decimal 2097184*/

#define BDRV_SEQAFHB2CD (0x4040) /*decimal 16448*/

#define BDRV_SEQAFHB2CD_HB2_AF_OFF_Value (0xCB2) /*decimal 3250*/

#define BDRV_SEQAFHB2CD_HB2_AF_ON_Value (0xCB2) /*decimal 3250*/

#define BDRV_SEQAFHB2IC (0x200020) /*decimal 2097184*/

#define BDRV_SEQMAP (0x0) /*decimal 0*/

#define BDRV_TRIM_DRVx (0x3040101) /*decimal 50594049*/

#define BDRV_UP_DITH (243.9)

#define BDRV_UP_DITH_FREQ (0xF3) /*decimal 243*/

#define SCU_BDRV_CLK (0x14) /*decimal 20*/

#define SCU_BRDRV_CLK (0x901) /*decimal 2305*/

#define SCU_BRDRV_TFILT_CLK (0x4) /*decimal 4*/

#endif /* BDRV_DEFINES_H */
