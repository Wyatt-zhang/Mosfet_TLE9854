/*
 ***********************************************************************************************************************
 *
 * Copyright (c) 2017, Infineon Technologies AG
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
 * \file     bootrom.h
 *
 * \brief    BootROM low level access library
 *
 * \version  V0.2.2
 * \date     02. Mar 2020
 *
 *  \note This file violates [MISRA 2012 Rule 2.5, advisory], [MISRA 2012 Rule 8.7, advisory]
 */

/*******************************************************************************
**                             Author(s) Identity                             **
********************************************************************************
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** DM           Daniel Mysliwitz                                              **
** BG           Blandine Guillot                                              **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V0.2.0: 2017-07-07, DM:   Initial version of revision history              **
** V0.2.1: 2019-02-07, DM:   BOOTROM_RETURN_CODE_t cleanup                    **
** V0.2.2: 2020-03-02, BG:   Updated revision history format                  **
*******************************************************************************/

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#ifndef _BOOTROM_H
#define _BOOTROM_H

#include "tle985x.h"
#include "types.h"
#include "sfr_access.h"

/*******************************************************************************
**                          Global Macro Definitions                          **
*******************************************************************************/

/** \brief A flash page contains 128 bytes
 */
#define FlashPageSize                (128U)

/** \brief A flash sector contains 32 flash pages, 4096 bytes in total
 */
#define FlashSectorSize              (4096U)

/*******************************************************************************
** Entry points into the BootROM                                              **
*******************************************************************************/
#define addr_user_nvm_protect_clear             (0x000000a1u)
#define addr_user_nvm_protect_set               (0x000000a3u)
#define addr_user_nvm_protect_get               (0x000000a5u)
#define addr_user_cid_get                       (0x000000a7u)
#define addr_user_nvm_ecc_events_get            (0x000000a9u)
#define addr_user_nvm_ecc_check                 (0x000000abu)
#define addr_user_nac_get                       (0x000000adu)
#define addr_user_nac_set                       (0x000000afu)
#define addr_user_nad_get                       (0x000000b1u)
#define addr_user_nad_set                       (0x000000b3u)
#define addr_user_nvm_100tp_read                (0x000000b5u)
#define addr_user_nvm_100tp_write               (0x000000b7u)
#define addr_user_nvm_config_get                (0x000000b9u)
#define addr_user_nvm_page_erase                (0x000000bbu)
#define addr_user_nvm_page_erase_branch         (0x000000bdu)
#define addr_user_nvm_ready_poll                (0x000000bfu)
#define addr_user_nvm_sector_erase              (0x000000c1u)
#define addr_user_nvm_write                     (0x000000c3u)
#define addr_user_nvm_write_branch              (0x000000c5u)
#define addr_user_ram_mbist                     (0x000000c7u)
#define addr_user_version_read                  (0x000000c9u)
#define addr_user_nvm_mapram_init               (0x000000cbu)
#define addr_user_nvm_clk_factor_set            (0x000000cdu)
#define addr_user_vbg_temperature_get           (0x000000cfu)
#define addr_user_nvm_page_verify               (0x000000d3u)
#define addr_user_nvm_page_erase_verify         (0x000000d5u)
#define addr_user_nvm_sector_erase_verify       (0x000000d7u)
#define addr_user_nvm_mapram_recover            (0x000000d9u)
#define addr_user_nvm_service_algorithm         (0x000000ddu)
#define addr_user_nvm_page_checksum_check       (0x000000dfu)
#define addr_user_nvm_100tp_erase               (0x000000e1u)
#define addr_user_adc1_offset_calibration       (0x000000e3u)
#define addr_user_nvm_password_set              (0x000000e5u)
#define addr_user_nvm_write_fast                (0x000000e7u)
#define addr_user_nvm_write_fast_retry          (0x000000e9u)
#define addr_user_nvm_write_fast_abort          (0x000000ebu)

/*******************************************************************************
** Error Code Selection enum                                               **
*******************************************************************************/
/** \enum BOOTROM_RETURN_CODE_t
 *  \brief This enum defines the Error codes
 */
typedef enum
{
    ERR_LOG_SUCCESS                                              = 0,   /**< Successful execution, no error occured */
    ERR_LOG_ERROR                                                = -1,  /**< Standard Error */
    ERR_LOG_CODE_NVM_SEGMENT_READ_PROTECTED                      = -3,  /**< Trying to read from a NVM segment that is read protected */
    ERR_LOG_CODE_MEM_READWRITE_PARAMS_INVALID                    = -4,  /**< Invalid parameters to RAM/NVM/NVM_CS read/write command */
    ERR_LOG_CODE_NVM_IS_READ_PROTECTED                           = -6,  /**< BSL message is not allowed access when NVM is read protected on any region */
    ERR_LOG_CODE_NVM_ERASE_PARAMS_INVALID                        = -7,  /**< Invalid BSL parameters to NVM erase command */
    ERR_LOG_CODE_INVALID_CUSTOMER_CONFIG_CBSL_SIZE               = -8,  /**< Specified customer configured CBSL size is invalid */
    ERR_LOG_CODE_CUSTOMER_CONFIG_CBSL_PROGRAMMED_OR_READ_ERR     = -9,  /**< Customer configured CBSL size already programmed or read error */
    ERR_LOG_CODE_NVM_CODE_PROGRAMMED                             = -10, /**< Customer configured CBSL size can't be changed when code is present in NVM */
    ERR_LOG_CODE_MEM_ADDR_RANGE_INVALID                          = -25, /**< Memory address range is invalid */
    ERR_LOG_CODE_ECC2READ_ERROR                                  = -26, /**< ECC2READ error generated when reading NVM data */
    ERR_LOG_CODE_NVM_WRITE_FAST_WRONG_MODE                       = -27, /**< NVM is not in fast write mode */
    ERR_LOG_CODE_NVM_WRITE_FAST_MAPRAM_UPDATE_FAIL_AND_VER_ERROR = -28, /**< 2 or more bit errors detected in NVM page when verifying NVM data during fast write retry and mapRAM update failed */
    ERR_LOG_CODE_NVM_WRITE_FAST_VER_ERROR                        = -29, /**< 2 or more bit errors detected in NVM page when verifying NVM data during fast write retry */
    ERR_LOG_CODE_NVM_SEMAPHORE_RESERVED                          = -30, /**< NVM semaphore already reserved */
    ERR_LOG_CODE_NVM_PAGE_IS_MAPPED                              = -32, /**< NVM erase page/sector verify: Page is mapped / not erased */
    ERR_LOG_CODE_NVM_SPARE_PAGE_IS_NOT_MAPPED                    = -33, /**< NVM erase page verify: Spare page is not mapped */
    ERR_LOG_CODE_NVM_FAST_PROG_NOT_ALLOWED                       = -34, /**< Fast programming option not allowed for used NVM page */
    ERR_LOG_CODE_NVM_VER_ERROR                                   = -35, /**< 2 or more bit errors detected in NVM page when verifying NVM data */
    ERR_LOG_CODE_NVM_PROG_MAPRAM_INIT_FAIL                       = -36, /**< NVM mapRAM update failed after mapped page programming or after execution of DH */
    ERR_LOG_CODE_NVM_PROG_VERIFY_MAPRAM_INIT_FAIL                = -37, /**< NVM programming and mapRAM init update failed after mapped page programming */
    ERR_LOG_CODE_NVM_ECC2_MAPBLOCK_ERROR                         = -38, /**< ECC2 mapBlock error generated while reading from a NVM page */
    ERR_LOG_CODE_NVM_MAPRAM_UNKNOWN_TYPE_USAGE                   = -39, /**< MAPRAM physical page number for a given logical sector/page is larger than the number of physical pages in a sector */
    ERR_LOG_CODE_NVM_ECC2_MAPRAM_ERROR                           = -40, /**< ECC2 mapRAM error generated while reading mapRAM */
    ERR_LOG_CODE_NVM_PAGE_NOT_MAPPED                             = -41, /**< NVM page is not mapped */
    ERR_LOG_CODE_NVM_INIT_MAPRAM_SECTOR                          = -42, /**< Mapped page has double mapping or ECC2 error when trying to init mapRAM */
    ERR_LOG_CODE_NVM_MAPRAM_MANUAL_SPARE_PAGE_FAILED             = -43, /**< NVM manual spare page selection failed as part of mapRAM update */
    ERR_LOG_CODE_ACCESS_AB_MODE_ERROR                            = -44, /**< Error when setting the assembly buffer to mode 1 or 2 */
    ERR_LOG_CODE_NVM_ECC2_DATA_ERROR                             = -45, /**< ECC2 data error generated while reading from a NVM page */
    ERR_LOG_CODE_ADDRESS_RANGE_CROSSING_PAGE_BOUNDARY            = -46, /**< Attempt to access NVM address range which is crossing NVM page boundary */
    ERR_LOG_CODE_100TP_WRITE_COUNT_EXCEEDED                      = -47, /**< NVM 100TP page write count was exceeded */
    ERR_LOG_CODE_100TP_PAGE_INVALID                              = -48, /**< Attempt to access NVM 100TP page address outside of the valid range */
    ERR_LOG_CODE_NVM_100TP_PAGE_CNT_ERROR                        = -49, /**< NVM 100TP page write counter contains ECC2 error. Value hardcoded according to documentation */
    ERR_LOG_CODE_MBIST_FAILED                                    = -63, /**< MBIST test detected an error */
    ERR_LOG_CODE_MBIST_TIMEOUT                                   = -64, /**< MBIST test failed due to timeout */
    ERR_LOG_CODE_USER_INVALID_NVM_PAGE_NUMBER                    = -65, /**< Invalid NVM page number */
    ERR_LOG_CODE_NAC_VALUE_INVALID                               = -67, /**< NAC value out of range in user_nac_set() */
    ERR_LOG_CODE_MBIST_RAM_RANGE_INVALID                         = -68, /**< user_ram_mbist() RAM range for MBIST is invalid */
    ERR_LOG_CODE_PARAM_LENGTH                                    = -69, /**< user_version_read() the provided length parameter is to small to store the information. */
    ERR_LOG_CODE_USER_NO_NVM_MAPPED_SECTOR                       = -71, /**< NVM has no configured mapped sectors */
    ERR_LOG_CODE_USER_NVM_SEGMENT_INVALID                        = -72, /**< Provided NVM segment is invalid */
    ERR_LOG_CODE_SINGLE_ECC_EVENT_OCCURRED                       = -73, /**< user_ecc_events_get()/user_ecc_get() single ECC event has occurred */
    ERR_LOG_CODE_DOUBLE_ECC_EVENT_OCCURRED                       = -74, /**< user_ecc_events_get()/user_ecc_get() double ECC event has occurred */
    ERR_LOG_CODE_SINGLE_AND_DOUBLE_ECC_EVENT_OCCURRED            = -75, /**< user_ecc_events_get()/user_ecc_get() single and double ECC events have occurred */
    ERR_LOG_CODE_PARAM_INVALID                                   = -76, /**< user_nvm_write/branch(): data parameter is invalid */
    ERR_LOG_CODE_USER_PROTECT_NVM_WRITE_PROTECTED                = -77, /**< Operation not allowed when NVM is write protected */
    ERR_LOG_CODE_USER_POINTER_RAM_RANGE_INVALID                  = -78, /**< Provided pointer doesn't point to a valid RAM range */
    ERR_LOG_CODE_USER_NVM_SEGMENT_CONFIG_MISMATCH                = -79, /**< NVM segment does not match the current configured NVM region type */
    ERR_LOG_CODE_NVM_IS_BUSY                                     = -80, /**< NVM is busy doing another operation */
    ERR_LOG_CODE_USER_PROTECT_PWD_INVALID                        = -81, /**< user_protect_password_set() provided password not valid */
    ERR_LOG_CODE_USER_PROTECT_PWD_EXISTS                         = -82, /**< nvm_protect_password_set() segment password already exists when trying to set a new one in */
    ERR_LOG_CODE_NO_PASSWORD_EXISTS                              = -83, /**< Password clear: No password installed when trying to clear password */
    ERR_LOG_CODE_USER_PROTECT_WRONG_PASSWORD                     = -84  /**< user_nvm_protect_set(), user_nvm_protect_clear(): wrong password given */
} BOOTROM_RETURN_CODE_t;


/*******************************************************************************
** NVM protection password segment enum                                    **
*******************************************************************************/
/** \enum NVM_PASSWORD_SEGMENT_t
 *  \brief This enum defines the NVM protection password segment
 */
typedef enum
{
    NVM_PASSWORD_SEGMENT_BOOT = 0,     /**< NVM password for customer segment, used for customer bootloader */
    NVM_PASSWORD_SEGMENT_CODE = 1,     /**< NVM password for customer code segment, which is not used by the customer bootloader */
    NVM_PASSWORD_SEGMENT_DATA = 2,     /**< NVM password for customer data mapped segment */
    NVM_PASSWORD_SEGMENT_DATA_LINEAR, /**< NVM password for customer data linear segment */
    NVM_PASSWORD_SEGMENT_LAST       /**< Can be ignored and should not be used */
} NVM_PASSWORD_SEGMENT_t;

typedef void(* user_callback_t) (void);

/*******************************************************************************
** VBG Temperature selection enum                                             **
*******************************************************************************/
/** \enum VBG_TEMP_SELECT_t
 *  \brief This enum defines the VBG Temperature selection.
 */
typedef enum
{
    VBG_TEMP_HOT, /**< VBG Hot Temperature */
    VBG_TEMP_COLD /**< VBG Cold Temperature */
} VBG_TEMP_SELECT_t;

/*******************************************************************************
**                         Global Function Definitions                        **
*******************************************************************************/
/* In case of unit testing, these functions are stubbed. 
 * Unit test is performed with Tessy; tessy doesn't interpret the function definitions 
 * which include the pointers to bootROM as functions,
 * so the function definitions are added here for unit testing only */
#ifdef UNIT_TESTING_LV2
extern int32_t  user_nvm_write_fast_retry(void);
extern int32_t  user_nvm_write_fast_abort(void);
extern int32_t  user_adc1_offset_calibration(void);
extern int32_t  user_nvm_page_checksum_check(uint32_t page_no);
extern int32_t  user_nvm_service_algorithm(uint32_t *sa_result);
extern int32_t  user_nvm_mapram_recover(void);
extern int32_t  user_nvm_mapram_init(void);
extern int32_t  user_nvm_ecc_events_get(uint32_t *pNVM_Addr);
extern int32_t  user_nvm_ecc_check(void);
extern int32_t  user_nac_get(uint8_t *nac_value);
extern int32_t  user_nac_set(uint8_t nac);
extern int32_t  user_nad_get(uint8_t *nad_value);
extern int32_t  user_nad_set(uint8_t nad);
extern int32_t  user_nvm_100tp_read(uint32_t page_num, uint32_t offset, void *data, uint32_t count);
extern int32_t  user_nvm_100tp_write(uint32_t page_num, uint32_t offset, const void *data, uint32_t count);
extern int32_t  user_nvm_100tp_erase(uint32_t page_num);
extern uint32_t  user_nvm_protect_get(NVM_PASSWORD_SEGMENT_t segment);
extern int32_t  user_nvm_protect_set(uint32_t password, NVM_PASSWORD_SEGMENT_t segment);
extern int32_t  user_nvm_protect_clear(uint32_t password, NVM_PASSWORD_SEGMENT_t segment);
extern int32_t  user_nvm_password_set(uint32_t password, NVM_PASSWORD_SEGMENT_t segment);
extern bool     user_nvm_ready_poll(void);
extern int32_t  user_nvm_page_erase(uint32_t address);
extern int32_t  user_nvm_page_erase_branch(uint32_t address, user_callback_t branch_address);
extern int32_t  user_nvm_sector_erase(uint32_t address);
extern int32_t  user_nvm_write(uint32_t address, const void *data, uint32_t count, uint32_t options);
extern int32_t  user_nvm_write_fast(uint32_t address, const void *data, uint32_t count);
extern int32_t  user_nvm_write_branch(uint32_t address, const void *data, uint32_t count, uint32_t options, user_callback_t branch_address);
extern int32_t  user_ram_mbist(uint32_t start_address, uint32_t end_address);
extern void     user_nvm_clk_factor_set(uint8_t clk_factor);
extern int32_t  user_vbg_temperature_get(VBG_TEMP_SELECT_t temp_select, uint32_t *temperature);
extern int32_t  user_nvm_page_verify(uint32_t address);
extern int32_t  user_nvm_page_erase_verify(uint32_t address);
extern int32_t  user_nvm_sector_erase_verify(uint32_t address);

#else
/** \brief This function can be called to retry a NVM fast write operation.
 * \note It can only be called when the previous fast write operation has standard verify error ERR_LOG_CODE_NVM_VER_ERROR.
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_CODE_NVM_WRITE_FAST_WRONG_MODE
 * \retval ERR_LOG_CODE_NVM_VER_ERROR
 * \retval ERR_LOG_CODE_NVM_PROG_MAPRAM_INIT_FAIL
 * \retval ERR_LOG_CODE_NVM_PROG_VERIFY_MAPRAM_INIT_FAIL
 * \retval ERR_LOG_CODE_NVM_WRITE_FAST_VER_ERROR
 * \retval ERR_LOG_CODE_NVM_WRITE_FAST_MAPRAM_UPDATE_FAIL_AND_VER_ERROR
 *
 * \brief <b>Example</b><br>
 * \brief This example performs a retry of the Fast Write Operation.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 page_data[128];
 *     uint8 i;
 *
 *     for ( i = 0; i < FlashPageSize; i++)
 *     {
 *         page_data[i] = i;
 *     }
 *
 *     WDT1_SOW_Service(1u);
 *
 *     if ( user_nvm_write_fast(DataFlashStart, &page_data, FlashPageSize) == ERR_LOG_CODE_NVM_VER_ERROR)
 *     {
 *         if (user_nvm_write_fast_retry() == ERR_LOG_SUCCESS)
 *         {
 *             // Fast Write Operation has been executed successfully
 *         }
 *         else if (user_nvm_write_fast_retry() == ERR_LOG_CODE_NVM_WRITE_FAST_WRONG_MODE)
 *         {
 *             // Fast Write is not started or the previous operation already pass
 *         }
 *         else
 *         {
 *             // Fast Write Operation is rejected
 *         }
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_nvm_write_fast_retry)(void);

/** \brief This function can be called to terminate a NVM fast write operation.
 * \note It can only be called when the previous fast write operation has standard verify error ERR_LOG_CODE_NVM_VER_ERROR.
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_CODE_NVM_WRITE_FAST_WRONG_MODE
 * \retval ERR_LOG_CODE_NVM_MAPRAM_MANUAL_SPARE_PAGE_FAILED
 *
 * \brief <b>Example</b><br>
 * \brief This example performs an abort of the Fast Write Operation.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 page_data[128];
 *     uint8 i;
 *
 *     for ( i = 0; i < FlashPageSize; i++)
 *     {
 *         page_data[i] = i;
 *     }
 *
 *     WDT1_SOW_Service(1u);
 *
 *     if ( user_nvm_write_fast(DataFlashStart, &page_data, FlashPageSize) == ERR_LOG_CODE_NVM_VER_ERROR)
 *     {
 *         if (user_nvm_write_fast_abort() == ERR_LOG_SUCCESS)
 *         {
 *             // Fast Write Abort Operation has been executed successfully
 *         }
 *         else if (user_nvm_write_fast_abort() == ERR_LOG_CODE_NVM_WRITE_FAST_WRONG_MODE)
 *         {
 *             // Fast Write is not started or the previous operation already pass
 *         }
 *         else
 *         {
 *             // Fast Write Abort Operation is rejected
 *         }
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_nvm_write_fast_abort)(void);

/** \brief This function will perform ADC1 core calibration in software mode.
 * \note It updates ADC1_OFFSETCALIB register if the calibration algorithm is executed successfully.
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_ERROR
 *
 * \brief <b>Example</b><br>
 * \brief This example performs ADC1 core calibration in software mode.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     ADC1_Power_On();
 *     ADC1_Software_Mode_Sel();
 *     WDT1_SOW_Service(1u);
 *
 *     if (user_adc1_offset_calibration() == ERR_LOG_SUCCESS)
 *     {  
 *         // ADC1 core calibration Operation has been executed successfully
 *     }
 *     else
 *     {  
 *         // Proper Calibration Value can not be found
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_adc1_offset_calibration)(void);

/** \brief This function will perform a checksum check on the specified NVM page.
 * \note It rejects with an error in case the NVM page is out of range.
 *
 * \param page_no Page to check, which is one of the 100TP pages (0..7) or NVM CS page containing BSL (startup) settings (8).
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_CODE_USER_INVALID_NVM_PAGE_NUMBER
 * \retval ERR_LOG_CODE_CS_PAGE_CHECKSUM
 * \retval ERR_LOG_CODE_CS_PAGE_ECC2READ
 * \retval ERR_LOG_CODE_NVM_SEMAPHORE_RESERVED
 *
 * \brief <b>Example</b><br>
 * \brief This example performs a checksum check on the first NVM page.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     WDT1_SOW_Service(1u);
 *
 *     if (user_nvm_page_checksum_check(0) == ERR_LOG_SUCCESS)
 *     {  
 *         // checksum check Operation has been executed successfully
 *     }
 *     else
 *     {  
 *         // checksum check Operation returns a negative error code
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_nvm_page_checksum_check)(uint32_t page_no);

/** \brief This function will run service algorithm on a mapped NVM sector.
 * \note Only if a mappd sector is configured, NVM SA will be executed.
 *
 * \param *sa_result Pointer where to store the result of the NVM SA run.
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_CODE_NVM_SEMAPHORE_RESERVED
 * \retval ERR_LOG_CODE_USER_POINTER_RAM_RANGE_INVALID
 * \retval ERR_LOG_CODE_USER_PROTECT_NVM_WRITE_PROTECTED
 * \retval ERR_LOG_CODE_USER_NO_NVM_MAPPED_SECTOR
 *
 * \brief <b>Example</b><br>
 * \brief This example performs a NVM SA Operation.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint32 sa_res;
 *
 *     WDT1_SOW_Service(1u);
 *
 *     if (user_nvm_service_algorithm(&sa_res) == ERR_LOG_SUCCESS)
 *     {  
 *         // NVM SA Operation has been executed successfully
 *     }
 *     else
 *     {  
 *         // NVM SA Operation returns a negative error code
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_nvm_service_algorithm)(uint32_t *sa_result);

/** \brief This function will manually do mapRAM initialization by extracting mapping info on good mapped pages.
 * \note It can be called if NVM SA fails repairing a corrupted mapped data sector.
 *
 * \return Positive number (including 0 = ERR_LOG_SUCCESS) or other BOOTROM Negative Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval Positive_Number
 * \retval ERR_LOG_CODE_NVM_SEMAPHORE_RESERVED
 * \retval ERR_LOG_CODE_USER_NO_NVM_MAPPED_SECTOR
 * \retval ERR_LOG_CODE_NVM_ECC2_MAPRAM_ERROR
 *
 * \brief <b>Example</b><br>
 * \brief This example performs a MAPRAM Recover Operation if NVM SA Operation fails repairing a corrupted mapped data sector.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint32 sa_res;
 *
 *     WDT1_SOW_Service(1u);
 *
 *     if ( user_nvm_service_algorithm(&sa_res) == ERR_LOG_CODE_USER_NO_NVM_MAPPED_SECTOR)
 *     {
 *         if (user_nvm_mapram_recover() == ERR_LOG_SUCCESS)
 *         {
 *             // MAPRAM Recover Operation has been executed successfully
 *         }
 *         else
 *         {
 *             // MAPRAM Recover Operation is rejected
 *         }
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_nvm_mapram_recover)(void);

/** \brief This function triggers NVM FSM mapRAM update sequence from mapped sector.
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_CODE_NVM_SEMAPHORE_RESERVED
 * \retval ERR_LOG_CODE_NVM_INIT_MAPRAM_SECTOR
 * \retval ERR_LOG_CODE_USER_NO_NVM_MAPPED_SECTOR
 *
 * \brief <b>Example</b><br>
 * \brief This example triggers NVM FSM mapRAM update sequence from mapped sector.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     WDT1_SOW_Service(1u);
 *
 *     if (user_nvm_mapram_init() == ERR_LOG_SUCCESS)
 *     {  
 *         // MAPRAM Init Operation has been executed successfully
 *     }
 *     else
 *     {  
 *         // MAPRAM Init Operation returns a negative error code
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_nvm_mapram_init)(void);

// extern int32_t  (*const user_cid_get)(uint32_t *customer_id);

/** \brief This function checks if any single or double ECC events have occurred during runtime.
 * \brief It reports any single or double ECC event coming from NVM.
 *
 * \param *pNVM_Addr Pointer where to store the ECC2 failing NVM address. This pointer stays untouched in case no NVM ECC2 errors was detected.
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_CODE_USER_POINTER_RAM_RANGE_INVALID
 * \retval ERR_LOG_CODE_NVM_SEMAPHORE_RESERVED
 * \retval ERR_LOG_CODE_SINGLE_ECC_EVENT_OCCURRED
 * \retval ERR_LOG_CODE_DOUBLE_ECC_EVENT_OCCURRED
 * \retval ERR_LOG_CODE_SINGLE_AND_DOUBLE_ECC_EVENT_OCCURRED
 *
 * \brief <b>Example</b><br>
 * \brief This example checks if any single or double ECC events have occurred during runtime.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint32 fail_addr;
 *  
 *     WDT1_SOW_Service(1u);
 *
 *     if (user_nvm_ecc_events_get(&fail_addr) == ERR_LOG_SUCCESS)
 *     {  
 *         // No single or double ECC event have occurred
 *     }
 *     else
 *     {  
 *         // Single/Double ECC Check Operation returns a negative error code
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_nvm_ecc_events_get)(uint32_t *pNVM_Addr);

/** \brief This function checks for single and double ECC checking over the entire NVM on all NVM linear and NVM non-linear sectors.
 * \note Any existing ECC errors are cleared before the read starts.
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_CODE_NVM_SEMAPHORE_RESERVED
 * \retval ERR_LOG_CODE_SINGLE_ECC_EVENT_OCCURRED
 * \retval ERR_LOG_CODE_DOUBLE_ECC_EVENT_OCCURRED
 * \retval ERR_LOG_CODE_SINGLE_AND_DOUBLE_ECC_EVENT_OCCURRED
 * \retval ERR_LOG_CODE_NVM_SEGMENT_READ_PROTECTED
 *
 * \brief <b>Example</b><br>
 * \brief This example checks for single and double ECC checking over the entire NVM on all NVM linear and NVM non-linear sectors.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     WDT1_SOW_Service(1u);
 *
 *     if (user_nvm_ecc_check() == ERR_LOG_SUCCESS)
 *     {  
 *         // No single or double ECC event have occurred
 *     }
 *     else
 *     {  
 *         // Single/Double ECC Check Operation returns a negative error code
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_nvm_ecc_check)(void);

/** \brief This function reads out the NAC value that is currently configured in the non volatile device configuration memory.
 *
 * \param *nac_value Pointer where to store the BSL NAC value read from the device configuration sector.
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_CODE_USER_POINTER_RAM_RANGE_INVALID
 *
 * \brief <b>Example</b><br>
 * \brief This example reads out the NAC value that is currently configured.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 nac_val;
 *  
 *     WDT1_SOW_Service(1u);
 *
 *     if (user_nac_get(&nac_val) == ERR_LOG_SUCCESS)
 *     {  
 *         // NAC Value Read Operation has been executed successfully
 *     }
 *     else
 *     {  
 *         // Provided pointer doesn't point to a valid RAM range
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_nac_get)(uint8_t *nac_value);

/** \brief This function configures the NAC value in the non volatile device configuration memory.
 * \note It rejects with an error in case the NVM code segment is write protected or NAC value is out of valid range [0, 2-28, 255].
 *
 * \param nac NAC value to be stored in the device configuration memory.
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_CODE_NVM_CONFIG_SECTOR_WRITE_PROTECTED
 * \retval ERR_LOG_CODE_NVM_SEMAPHORE_RESERVED
 * \retval ERR_LOG_CODE_ACCESS_AB_MODE_ERROR
 * \retval ERR_LOG_CODE_NAC_VALUE_INVALID
 * \retval ERR_LOG_CODE_NVM_ECC2_DATA_ERROR
 * \retval ERR_LOG_CODE_NVM_VER_ERROR
 *
 * \brief <b>Example</b><br>
 * \brief This example performs NAC Value Set Operation.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 nac_val;
 *  
 *     WDT1_SOW_Service(1u);
 *
 *     if (user_nac_set(nac_val) == ERR_LOG_SUCCESS)
 *     {  
 *         // NAC Value Set Operation has been executed successfully
 *     }
 *     else
 *     {  
 *         // NAC Value Set Operation returns a negative error code
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_nac_set)(uint8_t nac);

/** \brief This function reads out the FASTLIN NAD value that is currently configured in the non volatile device configuration memory.
 *
 * \param *nad_value Pointer where to store the BSL nad value read from the device configuration sector.
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_CODE_USER_POINTER_RAM_RANGE_INVALID
 *
 * \brief <b>Example</b><br>
 * \brief This example reads out the FASTLIN NAD value that is currently configured.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 nad_val;
 *  
 *     WDT1_SOW_Service(1u);
 *
 *     if (user_nad_get(&nad_val) == ERR_LOG_SUCCESS)
 *     {  
 *         // FASTLIN NAD Value Read Operation has been executed successfully
 *     }
 *     else
 *     {  
 *         // Provided pointer doesn't point to a valid RAM range
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_nad_get)(uint8_t *nad_value);

/** \brief This function configures the FASTLIN NAD value in the non volatile device configuration memory.
 * \note It rejects with an error in case the NVM code segment is write protected.
 *
 * \param nad FASTLIN NAD value to be stored in the device configuration memory. Valid range is from 0x00-0xFF.
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_CODE_NVM_CONFIG_SECTOR_WRITE_PROTECTED
 * \retval ERR_LOG_CODE_NVM_SEMAPHORE_RESERVED
 * \retval ERR_LOG_CODE_ACCESS_AB_MODE_ERROR
 * \retval ERR_LOG_CODE_NVM_ECC2_DATA_ERROR
 * \retval ERR_LOG_CODE_NVM_VER_ERROR
 *
 * \brief <b>Example</b><br>
 * \brief This example performs NAD Value Set Operation.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 nad_val;
 *  
 *     WDT1_SOW_Service(1u);
 *
 *     if (user_nad_set(nad_val) == ERR_LOG_SUCCESS)
 *     {  
 *         // FASTLIN NAD Value Set Operation has been executed successfully
 *     }
 *     else
 *     {  
 *         // FASTLIN NAD Value Set Operation returns a negative error code
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_nad_set)(uint8_t nad);

/** \brief This function reads data from the customer accessible configuration pages (100TP).
 * \note Invalid parameters (page number out of range, offset plus count larger than page boundary, count is 0) returns an error, and no read operation is performed.
 *
 * \param page_num Page number where to read from. Valid range: 0 to 7.
 * \param offset Byte offset inside the selected page address, where to start reading from.
 * \param *data Data pointer where to store the data read. Pointer plus valid count must be within valid RAM range or an error code is returned.
 * \param count Amount of data bytes to read. If count is zero, there is no operation performed and an error code is returned.
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_CODE_USER_POINTER_RAM_RANGE_INVALID
 * \retval ERR_LOG_CODE_100TP_PAGE_INVALID
 * \retval ERR_LOG_CODE_NVM_SEMAPHORE_RESERVED
 *
 * \brief <b>Example</b><br>
 * \brief This example performs a complete read of the first 100TP page.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint32 data;
 *     uint8 i;
 *
 *     WDT1_SOW_Service(1u);
 *
 *     for ( i = 0; i < FlashPageSize; i++)
 *     {
 *         if ( user_nvm_100tp_read(0, i, &data, FlashPageSize) == ERR_LOG_SUCCESS)
 *         {
 *               // 100TP Read Operation has been executed successfully
 *         }
 *         else
 *         {  
 *              // 100TP Read Operation returns a negative error code
 *         }   
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_nvm_100tp_read)(uint32_t page_num, uint32_t offset, void *data, uint32_t count);

/** \brief This function writes data to the customer accessible configuration pages (100TP).
 * \note Any invalid parameters (page number out of range, offset plus count larger than page boundary, count is 0) returns an error, and no write operation is performed.
 *
 * \param page_num Page number where to write to. Valid range: 0 to 7.
 * \param offset Byte offset inside the selected page address, where to start writing. Maximum is 126 bytes.
 * \param *data Data pointer where to read the data to write. Pointer plus valid count must be within valid RAM range or an error code is returned.
 * \param count Amount of data bytes to write. If count is zero, there is no write operation performed and an error code is returned. Maximum is 126 bytes.
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_CODE_USER_POINTER_RAM_RANGE_INVALID
 * \retval ERR_LOG_CODE_NVM_CONFIG_SECTOR_WRITE_PROTECTED
 * \retval ERR_LOG_CODE_100TP_PAGE_INVALID
 * \retval ERR_LOG_CODE_100TP_WRITE_COUNT_EXCEEDED
 * \retval ERR_LOG_CODE_NVM_VER_ERROR
 * \retval ERR_LOG_CODE_NVM_SEMAPHORE_RESERVED
 * \retval ERR_LOG_CODE_ACCESS_AB_MODE_ERROR
 * \retval ERR_LOG_CODE_NVM_ECC2_DATA_ERROR
 * \retval ERR_LOG_CODE_ECC2READ_ERROR
 *
 * \brief <b>Example</b><br>
 * \brief This example performs a complete write of the first 100TP page.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint32 data;
 *     uint8 i;
 *
 *     WDT1_SOW_Service(1u);
 *
 *     for ( i = 0; i < FlashPageSize; i++)
 *     {
 *         if ( user_nvm_100tp_write(0, i, &data, FlashPageSize) == ERR_LOG_SUCCESS)
 *         {
 *              // 100TP Write Operation has been executed successfully
 *         }
 *         else
 *         {  
 *             // 100TP Write Operation returns a negative error code
 *         }   
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_nvm_100tp_write)(uint32_t page_num, uint32_t offset, const void *data, uint32_t count);

/** \brief This function erases all data in one of the 100TP NVM pages preserving the write counter.
 * \note The erase operation is not executed in case the NVM code segment write protection is set and a dedicated protection error is returned.
 *
 * \param page_num 100TP page number to erase. Valid range: 0 to 7.
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_CODE_NVM_100TP_PAGE_CNT_ERROR
 * \retval ERR_LOG_CODE_100TP_PAGE_INVALID
 * \retval ERR_LOG_CODE_NVM_CONFIG_SECTOR_WRITE_PROTECTED
 * \retval ERR_LOG_CODE_NVM_SEMAPHORE_RESERVED
 * \retval ERR_LOG_CODE_ACCESS_AB_MODE_ERROR
 * \retval ERR_LOG_CODE_NVM_VER_ERROR
 * \retval ERR_LOG_CODE_100TP_WRITE_COUNT_EXCEEDED
 *
 * \brief <b>Example</b><br>
 * \brief This example performs a complete erase of the first 100TP page.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     WDT1_SOW_Service(1u);
 *
 *     if (user_nvm_100tp_erase(0) == ERR_LOG_SUCCESS)
 *     {  
 *         // 100TP Erase Operation has been executed successfully
 *     }
 *     else if (user_nvm_100tp_erase(0) == ERR_LOG_CODE_NVM_100TP_PAGE_CNT_ERROR)
 *     {  
 *         // Page is erased OK but ECC2 error was detected while reading write counter
 *     }
 *     else
 *     {  
 *         // 100TP Erase Operation has been rejected
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_nvm_100tp_erase)(uint32_t page_num);

/** \brief This function checks for the hardware current applied NVM protection status.
 *
 * \param segment Which NVM segment to retrieve the current password protection status (see \link NVM_PASSWORD_SEGMENT_t \endlink)
 *
 * \retval 0x00000000 : Protection disabled
 * \retval 0x80000000 : Read protection enabled
 * \retval 0x40000000 : Write protection enabled
 * \retval 0xC0000000 : Read and write protection enabled
 * \retval 0xFFFFFFFF : Segment not recognized.
 *
 * \brief <b>Example</b><br>
 * \brief This example checks the NVM protection status for customer data mapped segment.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     WDT1_SOW_Service(1u);
 *
 *     if (user_nvm_protect_get(NVM_PASSWORD_SEGMENT_DATA) == 0x00000000)
 *     {  
 *         // Protection disabled
 *     }
 *     else if (user_nvm_protect_get(NVM_PASSWORD_SEGMENT_DATA) == 0x80000000)
 *     {  
 *         // Read protection enabled
 *     }
 *     else if (user_nvm_protect_get(NVM_PASSWORD_SEGMENT_DATA) == 0x40000000)
 *     {  
 *         // Write protection enabled
 *     }
 *     else if (user_nvm_protect_get(NVM_PASSWORD_SEGMENT_DATA) == 0xC0000000)
 *     {  
 *         // Read and write protection enabled
 *     }
 *     else
 *     {  
 *         // Segment not recognized
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern uint32_t (*const user_nvm_protect_get)(NVM_PASSWORD_SEGMENT_t segment);

/** \brief This function sets write protection for any NVM region individually, except CBSL.
 * \note A valid password must be provided in case any valid NVM protection password is installed for this region.
 * \note Set bit 30 of the password parameter to disable write protection.
 * \note The bits (0...29) of the password parameter shall match the password installed.
 * \note Bit 31 (read protection) is ignored/not supported.
 *
 * \param password Protection password to apply on the given segment
 * \param segment Segment which should be password protected (see \link NVM_PASSWORD_SEGMENT_t \endlink)
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_CODE_USER_NVM_SEGMENT_INVALID
 * \retval ERR_LOG_CODE_NVM_SEMAPHORE_RESERVED
 * \retval ERR_LOG_CODE_USER_PROTECT_WRONG_PASSWORD
 * \retval ERR_LOG_CODE_USER_NVM_SEGMENT_CONFIG_MISMATCH
 * \retval ERR_LOG_CODE_ECC2READ_ERROR
 *
 * \brief <b>Example</b><br>
 * \brief This example sets write protection with a password installed before and equals to 0x40000000 (Write protection enabled with password equals to 0x0) for customer data mapped segment.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     WDT1_SOW_Service(1u);
 *
 *     if (user_nvm_protect_set(0x40000000, NVM_PASSWORD_SEGMENT_DATA) == ERR_LOG_SUCCESS)
 *     {  
 *         // Write Protection Set Operation has been executed successfully, Password could be successfully applied.
 *     }
 *     else
 *     {  
 *         // Write Protection Set Operation returns a negative error code
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_nvm_protect_set)(uint32_t password, NVM_PASSWORD_SEGMENT_t segment);

/** \brief This function clears write protection for any NVM region individually, except CBSL.
 * \note A valid password must be provided in case any valid NVM protection password is installed for this region.
 * \note Set bit 30 of the password parameter to disable write protection.
 * \note The bits (0...29) of the password parameter shall match the password installed.
 * \note Bit 31 (read protection) is ignored/not supported.
 *
 * \param password Protection password to apply on the given segment
 * \param segment Segment which should be password protected (see \link NVM_PASSWORD_SEGMENT_t \endlink)
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_CODE_USER_NVM_SEGMENT_INVALID
 * \retval ERR_LOG_CODE_NVM_SEMAPHORE_RESERVED
 * \retval ERR_LOG_CODE_USER_PROTECT_WRONG_PASSWORD
 * \retval ERR_LOG_CODE_USER_NVM_SEGMENT_CONFIG_MISMATCH
 * \retval ERR_LOG_CODE_ECC2READ_ERROR
 *
 * \brief <b>Example</b><br>
 * \brief This example clears write protection with a password installed before and equals to 0x40000000 (Write protection enabled with password equals to 0x0) for customer data mapped segment.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     WDT1_SOW_Service(1u);
 *
 *     if (user_nvm_protect_clear(0x40000000, NVM_PASSWORD_SEGMENT_DATA) == ERR_LOG_SUCCESS)
 *     {  
 *         // Write Protection Clear Operation has been executed successfully, Password could be successfully applied
 *     }
 *     else
 *     {  
 *         // Write Protection Clear Operation returns a negative error code
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_nvm_protect_clear)(uint32_t password, NVM_PASSWORD_SEGMENT_t segment);

/** \brief This function sets password for NVM region individually.
 * \note The password parameter consists of a 30-bit password (bit 0...29) and two additional protection bits (bit 30: write protection + bit 31: read protection).
 * \note A valid password must be different from 0x3FFFFFFF and 0x00000000 (bit 0...29).
 *
 * \param password Protection password to apply on the given segment
 * \param segment Segment which should be password protected (see \link NVM_PASSWORD_SEGMENT_t \endlink)
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_CODE_USER_NVM_SEGMENT_INVALID
 * \retval ERR_LOG_CODE_USER_PROTECT_PWD_INVALID
 * \retval ERR_LOG_CODE_NVM_SEMAPHORE_RESERVED
 * \retval ERR_LOG_CODE_ACCESS_AB_MODE_ERROR
 * \retval ERR_LOG_CODE_NVM_ECC2_DATA_ERROR
 * \retval ERR_LOG_CODE_NVM_VER_ERROR
 * \retval ERR_LOG_CODE_USER_PROTECT_PWD_EXISTS
 * \retval ERR_LOG_CODE_USER_NVM_SEGMENT_CONFIG_MISMATCH
 * \retval ERR_LOG_CODE_ECC2READ_ERROR
 *
 * \brief <b>Example</b><br>
 * \brief This example sets password to 0x40000001 (Write protection enabled with password equals to 0x1) for customer data mapped segment.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     WDT1_SOW_Service(1u);
 *
 *     if (user_nvm_password_set(0x40000001, NVM_PASSWORD_SEGMENT_DATA) == ERR_LOG_SUCCESS)
 *     {  
 *         // Password Set Operation has been executed successfully, Password could be successfully applied
 *     }
 *     else
 *     {  
 *         // Password Set Operation returns a negative error code
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_nvm_password_set)(uint32_t password, NVM_PASSWORD_SEGMENT_t segment);

/** \brief This function checks for the readiness of the NVM module.
 * \note It is called within the NVM programming or erase branch callback operation.
 *
 * \retval True : The requested NVM operation is already finished
 * \retval False : The requested NVM operation is not finished
 *
 * \brief <b>Example</b><br>
 * \brief This example checks for the readiness of the NVM module within the NVM programming.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 page_data[128];
 *     uint8 i;
 *
 *     for ( i = 0; i < FlashPageSize; i++)
 *     {
 *         page_data[i] = i;
 *     }
 *
 *     WDT1_SOW_Service(1u);
 *
 *     user_nvm_write_branch(DataFlashStart, &page_data, FlashPageSize, 0, &RAM_Branch_Function);
 *
 *     if (user_nvm_ready_poll() == true)
 *     {  
 *         // NVM operation is already finished
 *     }
 *     else
 *     {  
 *         // NVM operation is not finished
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern bool     (*const user_nvm_ready_poll)(void);

/** \brief This function erases a given NVM page (address).
 * \note In case of an unsused (new) page in non-linear sector, the function does nothing and returns success.
 * \note In case of erasing a page in linear sector, the function should always perform the erase.
 *
 * \param address Address of the NVM page to erase. Non-aligned address is accepted. Range is 0x11000000 + device NVM size.
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_CODE_MEM_ADDR_RANGE_INVALID
 * \retval ERR_LOG_CODE_USER_PROTECT_NVM_WRITE_PROTECTED
 * \retval ERR_LOG_CODE_NVM_SEMAPHORE_RESERVED
 * \retval ERR_LOG_CODE_NVM_ECC2_MAPRAM_ERROR
 * \retval ERR_LOG_CODE_ACCESS_AB_MODE_ERROR
 *
 * \brief <b>Example</b><br>
 * \brief This example performs a page erase of the first data flash page.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     WDT1_SOW_Service(1u);
 *
 *     if (user_nvm_page_erase(DataFlashStart) == ERR_LOG_SUCCESS)
 *     {  
 *         // NVM Page Erase Operation has been executed successfully
 *     }
 *     else
 *     {  
 *         // NVM Page Erase Operation returns a negative error code
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_nvm_page_erase)(uint32_t address);

/** \brief This function erases a given NVM page (address) and branches to an address (branch_address) for code execution during the NVM operation.
 * \note It rejects with an error in case the accessed NVM page is write protected.
 *
 * \param address Address of the NVM page to erase. Non-aligned address is accepted. Range is 0x11000000 + device NVM size.
 * \param branch_address Function callback address where to jump while waiting for the NVM module to finish the erase operation (see \link user_callback_t \endlink)
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_CODE_MEM_ADDR_RANGE_INVALID
 * \retval ERR_LOG_CODE_USER_POINTER_RAM_RANGE_INVALID
 * \retval ERR_LOG_CODE_USER_PROTECT_NVM_WRITE_PROTECTED
 * \retval ERR_LOG_CODE_NVM_SEMAPHORE_RESERVED
 * \retval ERR_LOG_CODE_NVM_ECC2_MAPRAM_ERROR
 * \retval ERR_LOG_CODE_ACCESS_AB_MODE_ERROR
 *
 * \brief <b>Example</b><br>
 * \brief This example performs a page erase of the first data flash page and branches to RAM_Branch_Function address.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     WDT1_SOW_Service(1u);
 *
 *     if (user_nvm_page_erase_branch(DataFlashStart, &RAM_Branch_Function) == ERR_LOG_SUCCESS)
 *     {  
 *         // NVM Page Erase/Branch Operation has been executed successfully
 *     }
 *     else
 *     {  
 *         // NVM Page Erase/Branch Operation returns a negative error code
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_nvm_page_erase_branch)(uint32_t address, user_callback_t branch_address);

/** \brief This function erases the NVM sector-wise.
 * \note It rejects with an error in case the NVM region the address belongs to is write protected.
 *
 * \param address Address of the NVM sector to erase. Non-aligned address is accepted. Range is 0x11000000 + device NVM size.
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_CODE_MEM_ADDR_RANGE_INVALID
 * \retval ERR_LOG_CODE_USER_PROTECT_NVM_WRITE_PROTECTED
 * \retval ERR_LOG_CODE_NVM_SEMAPHORE_RESERVED
 * \retval ERR_LOG_CODE_NVM_INIT_MAPRAM_SECTOR
 * \retval ERR_LOG_CODE_ACCESS_AB_MODE_ERROR
 *
 * \brief <b>Example</b><br>
 * \brief This example erases the data flash sector.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     WDT1_SOW_Service(1u);
 *
 *     if (user_nvm_sector_erase(DataFlashStart) == ERR_LOG_SUCCESS)
 *     {  
 *         // NVM Sector Erase Operation has been executed successfully
 *     }
 *     else
 *     {  
 *         // NVM Sector Erase Operation returns a negative error code
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_nvm_sector_erase)(uint32_t address);

/** \brief This function programs the NVM. It operates on the user NVM, as well as on the user data NVM.
 * \note It shall write a number of bytes (count) from the source (data) to the NVM location (address) with the programming options (options).
 *
 * \param address NVM address where to program the data. Range is 0x11000000 + device NVM size.
 * \param *data Pointer to the data where to read the programming data. Pointer must be within valid RAM range or an error code is returned.
 * \param count Amount of bytes to program. Range from 1-128 bytes.
 * \param options NVM programming options.
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_CODE_PARAM_INVALID
 * \retval ERR_LOG_CODE_USER_POINTER_RAM_RANGE_INVALID
 * \retval ERR_LOG_CODE_ADDRESS_RANGE_CROSSING_PAGE_BOUNDARY
 * \retval ERR_LOG_CODE_MEM_READWRITE_PARAMS_INVALID
 * \retval ERR_LOG_CODE_MEM_ADDR_RANGE_INVALID
 * \retval ERR_LOG_CODE_USER_PROTECT_NVM_WRITE_PROTECTED
 * \retval ERR_LOG_CODE_NVM_SEMAPHORE_RESERVED
 * \retval ERR_LOG_CODE_ACCESS_AB_MODE_ERROR
 * \retval ERR_LOG_CODE_NVM_MAPRAM_UNKNOWN_TYPE_USAGE
 * \retval ERR_LOG_CODE_NVM_ECC2_MAPBLOCK_ERROR
 * \retval ERR_LOG_CODE_NVM_ECC2_DATA_ERROR
 * \retval ERR_LOG_CODE_NVM_ECC2_MAPRAM_ERROR
 * \retval ERR_LOG_CODE_NVM_VER_ERROR
 * \retval ERR_LOG_CODE_NVM_PROG_MAPRAM_INIT_FAIL
 * \retval ERR_LOG_CODE_NVM_PROG_VERIFY_MAPRAM_INIT_FAIL
 *
 * \brief <b>Example</b><br>
 * \brief This example fills an array of 128 bytes and then it will be programmed to the first page.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 page_data[128];
 *     uint8 i;
 *
 *     for ( i = 0; i < FlashPageSize; i++)
 *     {
 *         page_data[i] = i;
 *     }
 *
 *     WDT1_SOW_Service(1);
 *
 *     if (user_nvm_write(DataFlashStart, &page_data, FlashPageSize, 0) == ERR_LOG_SUCCESS)
 *     {  
 *         // NVM Write Operation has been executed successfully
 *     }
 *     else
 *     {  
 *         // NVM Write Operation returns a negative error code
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_nvm_write)(uint32_t address, const void *data, uint32_t count, uint32_t options);

/** \brief This function programs the NVM faster than normal.
 * \note It shall write a number of bytes (count) from the source (data) to the NVM location (address).
 *
 * \param address NVM address where to program the data. Range is 0x11000000 + device NVM size.
 * \param *data Pointer to the data where to read the programming data. Pointer must be within valid RAM range or an error code is returned.
 * \param count Amount of bytes to program. Range from 1-128 bytes.
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_CODE_PARAM_INVALID
 * \retval ERR_LOG_CODE_USER_POINTER_RAM_RANGE_INVALID
 * \retval ERR_LOG_CODE_ADDRESS_RANGE_CROSSING_PAGE_BOUNDARY
 * \retval ERR_LOG_CODE_MEM_READWRITE_PARAMS_INVALID
 * \retval ERR_LOG_CODE_MEM_ADDR_RANGE_INVALID
 * \retval ERR_LOG_CODE_USER_PROTECT_NVM_WRITE_PROTECTED
 * \retval ERR_LOG_CODE_NVM_SEMAPHORE_RESERVED
 * \retval ERR_LOG_CODE_ACCESS_AB_MODE_ERROR
 * \retval ERR_LOG_CODE_NVM_MAPRAM_UNKNOWN_TYPE_USAGE
 * \retval ERR_LOG_CODE_NVM_ECC2_MAPBLOCK_ERROR
 * \retval ERR_LOG_CODE_NVM_ECC2_MAPRAM_ERROR
 * \retval ERR_LOG_CODE_NVM_VER_ERROR
 * \retval ERR_LOG_CODE_NVM_PROG_MAPRAM_INIT_FAIL
 * \retval ERR_LOG_CODE_NVM_FAST_PROG_NOT_ALLOWED
 *
 * \brief <b>Example</b><br>
 * \brief This example fills an array of 128 bytes and then it will be programmed to the first page faster than normal.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
*      uint8 page_data[128];
 *     uint8 i;
 *
 *     for ( i = 0; i < FlashPageSize; i++)
 *     {
 *         page_data[i] = i;
 *     }
 *
 *     WDT1_SOW_Service(1u);
 *
 *     if ( user_nvm_write_fast(DataFlashStart, &page_data, FlashPageSize) == ERR_LOG_SUCCESS)
 *     {
 *         // Fast Write Operation has been executed successfully
 *     }
 *     else if ( user_nvm_write_fast(DataFlashStart, &page_data, FlashPageSize) == ERR_LOG_CODE_NVM_VER_ERROR)
 *     {  
 *         // A retry can be issued by calling user_nvm_write_fast_retry
 *     }
 *     else
 *     {  
 *         // Fast Write Operation has been rejected
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_nvm_write_fast)(uint32_t address, const void *data, uint32_t count);

/** \brief This function programs the NVM. It operates on the user NVM, as well as on the user data NVM.
 * \brief During the NVM operation the program execution branches to a given SRAM location (branch_address) and continues code execution from there.
 * \note It shall write a number of bytes (count) from the source (data) to the NVM location (address) with the programming options (options).
 *
 * \param address NVM address where to program the data. Range is 0x11000000 + device NVM size.
 * \param *data Pointer to the data where to read the programming data. Pointer must be within valid RAM range or an error code is returned.
 * \param count Amount of bytes to program. Range from 1-128 bytes.
 * \param options NVM programming options.
 * \param branch_address Function callback address where to jump while waiting for the NVM module to finish the program operation (see \link user_callback_t \endlink)
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_CODE_PARAM_INVALID
 * \retval ERR_LOG_CODE_USER_POINTER_RAM_RANGE_INVALID
 * \retval ERR_LOG_CODE_ADDRESS_RANGE_CROSSING_PAGE_BOUNDARY
 * \retval ERR_LOG_CODE_MEM_READWRITE_PARAMS_INVALID
 * \retval ERR_LOG_CODE_MEM_ADDR_RANGE_INVALID
 * \retval ERR_LOG_CODE_USER_PROTECT_NVM_WRITE_PROTECTED
 * \retval ERR_LOG_CODE_NVM_SEMAPHORE_RESERVED
 * \retval ERR_LOG_CODE_ACCESS_AB_MODE_ERROR
 * \retval ERR_LOG_CODE_NVM_MAPRAM_UNKNOWN_TYPE_USAGE
 * \retval ERR_LOG_CODE_NVM_ECC2_MAPBLOCK_ERROR
 * \retval ERR_LOG_CODE_NVM_ECC2_DATA_ERROR
 * \retval ERR_LOG_CODE_NVM_ECC2_MAPRAM_ERROR
 * \retval ERR_LOG_CODE_NVM_VER_ERROR
 * \retval ERR_LOG_CODE_NVM_PROG_MAPRAM_INIT_FAIL
 * \retval ERR_LOG_CODE_NVM_PROG_VERIFY_MAPRAM_INIT_FAIL
 *
 * \brief <b>Example</b><br>
 * \brief This example fills an array of 128 bytes and then during the programming to the first page it branches to RAM_Branch_Function address.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint8 page_data[128];
 *     uint8 i;
 *
 *     for ( i = 0; i < FlashPageSize; i++)
 *     {
 *         page_data[i] = i;
 *     }
 *
 *     WDT1_SOW_Service(1u);
 *
 *     if ( user_nvm_write_branch(DataFlashStart, &page_data, FlashPageSize, 0, &RAM_Branch_Function) == ERR_LOG_SUCCESS)
 *     {
 *         // Fast Write Branch Operation has been executed successfully
 *     }
 *     else
 *     {  
 *         // Fast Write Branch Operation returns a negative error code
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_nvm_write_branch)(uint32_t address, const void *data, uint32_t count, uint32_t options, user_callback_t branch_address);

/** \brief This function performs a MBIST on the integrated SRAM.
 * \note The function rejects the call in case the parameter exceeds the RAM address range.
 *
 * \param start_address RAM memory address where to start the MBIST test.
 * \param end_address RAM memory address till where to perform the MBIST test.
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_CODE_MBIST_RAM_RANGE_INVALID
 * \retval ERR_LOG_CODE_MBIST_FAILED
 * \retval ERR_LOG_CODE_MBIST_TIMEOUT
 *
 * \brief <b>Example</b><br>
 * \brief This example performs a MBIST over the first half of the RAM.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     WDT1_SOW_Service(1u);
 *
 *     if (user_ram_mbist(0, (uint32)(RAMSize >> 1u)) == ERR_LOG_SUCCESS)
 *     {  
 *         // MBIST Operation has been executed successfully
 *     }
 *     else
 *     {  
 *         // MBIST Operation returns a negative error code
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_ram_mbist)(uint32_t start_address, uint32_t end_address);

// extern int32_t  (*const user_version_read)(void *data, uint32_t length);

/** \brief This function sets the SCU_SYSCON0.NVMCLKFAC divider.
 *
 * \param clk_factor value is shifted and set to the corresponding bit fields of the register.
 *
 * \brief <b>Example</b><br>
 * \brief This example sets the clock divider to div 2, fsys/2.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     WDT1_SOW_Service(1u);
 *
 *     user_nvm_clk_factor_set(1u);
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern void     (*const user_nvm_clk_factor_set)(uint8_t clk_factor);

/** \brief This function returns the V bandgap temperature hot or cold.
 * \note The customer can do temperature compensation in software based on these values, as the VBG is the reference for the ADC.
 *
 * \param temp_select Selects the temperature to read (see \link VBG_TEMP_SELECT_t \endlink)
 * \param *temperature Pointer where to store the temperature value read from the device configuration sector.
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_CODE_USER_POINTER_RAM_RANGE_INVALID
 * \retval ERR_LOG_CODE_USERAPI_INVALID_VBG_TEMP_SELECT
 *
 * \brief <b>Example</b><br>
 * \brief This example reads the VBG Hot Temperature.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     uint32 temp_val;
 *
 *     WDT1_SOW_Service(1u);
 *
 *     if (user_vbg_temperature_get(VBG_TEMP_HOT, &temp_val) == ERR_LOG_SUCCESS)
 *     {  
 *         // VBG Temperature Read Operation has been executed successfully
 *     }
 *     else
 *     {  
 *         // VBG Temperature Read Operation returns a negative error code
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_vbg_temperature_get)(VBG_TEMP_SELECT_t temp_select, uint32_t *temperature);

/** \brief This function reads the physical page content into the NVM assembly buffer using Normal Read Margins.
 * \brief The content of the assembly buffer is then used to check the physical page content by using the hardread margins erase and written.
 * \note It rejects with an error in case the accessed NVM page belongs to a write protected region.
 *
 * \param address Address of the NVM page to check. Non-aligned address is accepted. Range is 0x11000000 + device NVM size.
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_CODE_USER_PROTECT_NVM_WRITE_PROTECTED
 * \retval ERR_LOG_CODE_NVM_SEMAPHORE_RESERVED
 * \retval ERR_LOG_CODE_MEM_ADDR_RANGE_INVALID
 * \retval ERR_LOG_CODE_NVM_VER_ERROR
 * \retval ERR_LOG_CODE_NVM_PAGE_NOT_MAPPED
 * \retval ERR_LOG_CODE_ACCESS_AB_MODE_ERROR
 * \retval ERR_LOG_CODE_NVM_ECC2_MAPRAM_ERROR
 * \retval ERR_LOG_CODE_NVM_ECC2_DATA_ERROR
 * \retval ERR_LOG_CODE_NVM_ECC2_MAPBLOCK_ERROR
 *
 * \brief <b>Example</b><br>
 * \brief This example verifies the data integrity of the 1st page of the data flash sector.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     WDT1_SOW_Service(1u);
 *
 *     if (user_nvm_page_verify(DataFlashStart) == ERR_LOG_SUCCESS)
 *     {  
 *         // NVM Page Verify Operation has been executed successfully
 *     }
 *     else
 *     {  
 *         // NVM Page Verify Operation returns a negative error code
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_nvm_page_verify)(uint32_t address);

/** \brief This function verifies with HardRead Erased margin on a page to check that all bits are erased.
 * \note It rejects with an error in case the accessed NVM page belongs to a write protected region.
 *
 * \param address Address of the NVM page to check. Non-aligned address is accepted. Range is 0x11000000 + device NVM size.
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_CODE_USER_PROTECT_NVM_WRITE_PROTECTED
 * \retval ERR_LOG_CODE_NVM_SEMAPHORE_RESERVED
 * \retval ERR_LOG_CODE_MEM_ADDR_RANGE_INVALID
 * \retval ERR_LOG_CODE_NVM_PAGE_IS_MAPPED
 * \retval ERR_LOG_CODE_NVM_SPARE_PAGE_IS_NOT_MAPPED
 * \retval ERR_LOG_CODE_NVM_VER_ERROR
 * \retval ERR_LOG_CODE_ACCESS_AB_MODE_ERROR
 * \retval ERR_LOG_CODE_NVM_ECC2_MAPRAM_ERROR
 *
 * \brief <b>Example</b><br>
 * \brief This example verifies the erased state of the 1st Page of the data flash sector.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     WDT1_SOW_Service(1u);
 *
 *     if (user_nvm_page_erase_verify(DataFlashStart) == ERR_LOG_SUCCESS)
 *     {  
 *         // NVM Page Erase Verify Operation has been executed successfully
 *     }
 *     else
 *     {  
 *         // NVM Page Erase Verify Operation returns a negative error code
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_nvm_page_erase_verify)(uint32_t address);

/** \brief This function performs a page-by-page erase check for a full sector. Each page is checked against Hardread- Margin-Erased.
 * \note It rejects with an error in case the accessed NVM page belongs to a write protected region.
 *
 * \param address Address of the NVM sector to check. Non-aligned address is accepted, as the used sector range will be the sector where the address belongs.
 *
 * \return BOOTROM Return Codes (see \link BOOTROM_RETURN_CODE_t \endlink)
 * \retval ERR_LOG_SUCCESS
 * \retval ERR_LOG_CODE_USER_PROTECT_NVM_WRITE_PROTECTED
 * \retval ERR_LOG_CODE_NVM_SEMAPHORE_RESERVED
 * \retval ERR_LOG_CODE_MEM_ADDR_RANGE_INVALID
 * \retval ERR_LOG_CODE_NVM_PAGE_IS_MAPPED
 * \retval ERR_LOG_CODE_NVM_VER_ERROR
 * \retval ERR_LOG_CODE_ACCESS_AB_MODE_ERROR
 * \retval ERR_LOG_CODE_NVM_ECC2_MAPRAM_ERROR
 *
 * \brief <b>Example</b><br>
 * \brief This example verifies the erased state of the data flash sector.
 * ~~~~~~~~~~~~~~~{.c}
 * void Example_Function(void)
 * {
 *     WDT1_SOW_Service(1u);
 *
 *     if (user_nvm_sector_erase_verify(DataFlashStart) == ERR_LOG_SUCCESS)
 *     {  
 *         // NVM Page Erase Verify Operation has been executed successfully
 *     }
 *     else
 *     {  
 *         // NVM Page Erase Verify Operation returns a negative error code
 *     }
 *
 *     (void)WDT1_Service();
 * }
 * ~~~~~~~~~~~~~~~
 * \ingroup bootrom_api
 */
extern int32_t  (*const user_nvm_sector_erase_verify)(uint32_t address);


#endif /* UNIT_TESTING_LV2 */
#endif /* _BOOTROM_H */
