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


/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "bootrom.h"

/*******************************************************************************
**                         Global Function Definitions                        **
*******************************************************************************/

/*******************************************************************************
** BootROM User Function declaration                                          **
*******************************************************************************/
#ifndef UNIT_TESTING_LV2
int32_t  (*const user_nvm_write_fast_retry)(void) = (int32_t  (*)(void)) addr_user_nvm_write_fast_retry;
int32_t  (*const user_nvm_write_fast_abort)(void) = (int32_t  (*)(void)) addr_user_nvm_write_fast_abort;
int32_t  (*const user_adc1_offset_calibration)(void) = (int32_t  (*)(void)) addr_user_adc1_offset_calibration;
int32_t  (*const user_nvm_page_checksum_check)(uint32_t page_no) = (int32_t  (*)(uint32_t page_no)) addr_user_nvm_page_checksum_check;
int32_t  (*const user_nvm_service_algorithm)(uint32_t *sa_result) = (int32_t  (*)(uint32_t *sa_result)) addr_user_nvm_service_algorithm;
int32_t  (*const user_nvm_mapram_recover)(void) = (int32_t  (*)(void)) addr_user_nvm_mapram_recover;
int32_t  (*const user_nvm_mapram_init)(void) = (int32_t  (*)(void)) addr_user_nvm_mapram_init;
int32_t  (*const user_nvm_ecc_events_get)(uint32_t *pNVM_Addr) = (int32_t  (*)(uint32_t *pNVM_Addr)) addr_user_nvm_ecc_events_get;
int32_t  (*const user_nvm_ecc_check)(void) = (int32_t  (*)(void)) addr_user_nvm_ecc_check;
int32_t  (*const user_nac_get)(uint8_t *nac_value) = (int32_t  (*)(uint8_t *nac_value)) addr_user_nac_get;
int32_t  (*const user_nac_set)(uint8_t nac) = (int32_t  (*)(uint8_t nac)) addr_user_nac_set;
int32_t  (*const user_nad_get)(uint8_t *nad_value) = (int32_t  (*)(uint8_t *nad_value)) addr_user_nad_get;
int32_t  (*const user_nad_set)(uint8_t nad) = (int32_t  (*)(uint8_t nad)) addr_user_nad_set;
int32_t  (*const user_nvm_100tp_read)(uint32_t page_num, uint32_t offset, void *data, uint32_t count) = (int32_t  (*)(uint32_t page_num, uint32_t offset, void *data, uint32_t count)) addr_user_nvm_100tp_read;
int32_t  (*const user_nvm_100tp_write)(uint32_t page_num, uint32_t offset, const void *data, uint32_t count) = (int32_t  (*)(uint32_t page_num, uint32_t offset, const void *data, uint32_t count)) addr_user_nvm_100tp_write;
int32_t  (*const user_nvm_100tp_erase)(uint32_t page_num) = (int32_t  (*)(uint32_t page_num)) addr_user_nvm_100tp_erase;
uint32_t (*const user_nvm_protect_get)(NVM_PASSWORD_SEGMENT_t segment) = (uint32_t  (*)(NVM_PASSWORD_SEGMENT_t segment)) addr_user_nvm_protect_get;
int32_t  (*const user_nvm_protect_set)(uint32_t password, NVM_PASSWORD_SEGMENT_t segment) = (int32_t  (*)(uint32_t password, NVM_PASSWORD_SEGMENT_t segment)) addr_user_nvm_protect_set;
int32_t  (*const user_nvm_protect_clear)(uint32_t password, NVM_PASSWORD_SEGMENT_t segment) = (int32_t  (*)(uint32_t password, NVM_PASSWORD_SEGMENT_t segment)) addr_user_nvm_protect_clear;
int32_t  (*const user_nvm_password_set)(uint32_t password, NVM_PASSWORD_SEGMENT_t segment) = (int32_t  (*)(uint32_t password, NVM_PASSWORD_SEGMENT_t segment)) addr_user_nvm_password_set;
bool     (*const user_nvm_ready_poll)(void) = (bool     (*)(void)) addr_user_nvm_ready_poll;
int32_t  (*const user_nvm_page_erase)(uint32_t address) = (int32_t  (*)(uint32_t address)) addr_user_nvm_page_erase;
int32_t  (*const user_nvm_page_erase_branch)(uint32_t address, user_callback_t branch_address) = (int32_t  (*)(uint32_t address, user_callback_t branch_address)) addr_user_nvm_page_erase_branch;
int32_t  (*const user_nvm_sector_erase)(uint32_t address) = (int32_t  (*)(uint32_t address)) addr_user_nvm_sector_erase;
int32_t  (*const user_nvm_write)(uint32_t address, const void *data, uint32_t count, uint32_t options) = (int32_t  (*)(uint32_t address, const void *data, uint32_t count, uint32_t options)) addr_user_nvm_write;
int32_t  (*const user_nvm_write_fast)(uint32_t address, const void *data, uint32_t count) = (int32_t  (*)(uint32_t address, const void *data, uint32_t count)) addr_user_nvm_write_fast;
int32_t  (*const user_nvm_write_branch)(uint32_t address, const void *data, uint32_t count, uint32_t options, user_callback_t branch_address) = (int32_t  (*)(uint32_t address, const void *data, uint32_t count, uint32_t options, user_callback_t branch_address)) addr_user_nvm_write_branch;
int32_t  (*const user_ram_mbist)(uint32_t start_address, uint32_t end_address) = (int32_t  (*)(uint32_t start_address, uint32_t end_address)) addr_user_ram_mbist;
void     (*const user_nvm_clk_factor_set)(uint8_t clk_factor) = (void     (*)(uint8_t clk_factor)) addr_user_nvm_clk_factor_set;
int32_t  (*const user_vbg_temperature_get)(VBG_TEMP_SELECT_t temp_select, uint32_t *temperature) = (int32_t  (*)(VBG_TEMP_SELECT_t temp_select, uint32_t *temperature)) addr_user_vbg_temperature_get;
int32_t  (*const user_nvm_page_verify)(uint32_t address) = (int32_t  (*)(uint32_t address)) addr_user_nvm_page_verify;
int32_t  (*const user_nvm_page_erase_verify)(uint32_t address) = (int32_t  (*)(uint32_t address)) addr_user_nvm_page_erase_verify;
int32_t  (*const user_nvm_sector_erase_verify)(uint32_t address) = (int32_t  (*)(uint32_t address)) addr_user_nvm_sector_erase_verify;
#endif /* UNIT_TESTING_LV2 */
