/*******************************************************************************
* Copyright (c) 2020, JE
* All Rights Reserved.
* Dept.: APG Shared
* File: lin_transceiver.c
* Description:
* REQ IDs: 
* History:
* 2020-03-12,  Lei Yingjun
*******************************************************************************/


#include "lin_transceiver.h"


/****************************************************************************
 * Function: LIN_Enable_Transceiver
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
void LIN_Enable_Transceiver(void)
{
    do {
        LIN->CTRL.bit.MODE = 3u;
    } while (LIN->CTRL.bit.MODE_FB != 7u);
    PMU->LIN_WAKE_EN.bit.LIN_WAKE_EN = 0u;
}

/****************************************************************************
 * Function: LIN_Disable_Transceiver
 * Param<void>:
 * Return<void>:
 * REQ IDs:
 * Discription: 
 * Note: 
*****************************************************************************/
void LIN_Disable_Transceiver(void)
{
    do {
        LIN->CTRL.bit.MODE = 0u;
			} while (LIN->CTRL.bit.MODE_FB != 1u);
    PMU->LIN_WAKE_EN.bit.LIN_WAKE_EN = 1u;
}




