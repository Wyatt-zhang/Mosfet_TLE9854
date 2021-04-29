/*******************************************************************************
* Copyright (c) 2015, JE
* All Rights Reserved.
* Dept.: APG Shared
* File: lin_config.c
* Description:
* REQ IDs: 
* History:
* 2015-08-07,  Lei Yingjun
*******************************************************************************/

#include "lin_config.h"
#include "lin_il.h"



lin_word_status_t lin_word_status;

l_bool lin_goto_sleep_flg = 0;  /*有睡眠命令过来*/

l_bool lin_mute_flg = 0;    /* no LIN communication for 5s ，总线上命令消失5s */

l_u8 lin_driver_response_buffer[9] = { 0 };





static l_u8 lin_frame_ctr_buf[8] = { 0 };              /* control frame */

static l_u8 lin_frame_st_buf[8] = { 0 };         /* status frame */



//诊断帧的两个缓冲区数组 0x3c 0x3d

//主机请求帧
 static l_u8 lin_frame_request_buf[8] = { 0 };    /* master request */
//从机应答帧
 static l_u8 lin_frame_response_buf[8] = {0};     /* slave response */

 
 
 
//帧ID
//对哪些帧做出反应
l_u8 lin_frame_cfg_id[LIN_NUM_OF_FRAMES] = {0x1C, 0x31, 0x3C, 0x3D};





/*结构体数组对象
**** 规定了每个帧的信息
*/

/*以下的订阅节点和发布节点都是从slave 视角来看的*/
const lin_frame_config_t lin_frame_cfg_array[LIN_NUM_OF_FRAMES] =
{
/*LIN_FRAME_CTR*/             {LIN_FRM_UNCONDITIONAL, LIN_RES_SUB, 8, lin_frame_ctr_buf, frame_unpack_ctr},

/*LIN_FRAME_ST*/              {LIN_FRM_UNCONDITIONAL, LIN_RES_PUB, 8, lin_frame_st_buf, frame_pack_st},

/*LIN_FRAME_MASTER_REQUEST*/  {LIN_FRM_DIAGNOSTIC, LIN_RES_SUB, 8, lin_frame_request_buf, frame_do_nothing},

/*LIN_FRAME_SlAVE_RESPONSE*/  {LIN_FRM_DIAGNOSTIC, LIN_RES_PUB, 8, lin_frame_response_buf, frame_do_nothing},
};





#if 0
typedef struct LIN_FRAME_BUF_CFG_T
{
   lin_frame_state_t msg_st;
   l_u16 period;// /* [10ms] */
   l_u16 tick;
}lin_frame_buf_cfg_t;

#endif

lin_frame_buf_cfg_t lin_frame_buf_array[LIN_NUM_OF_FRAMES] =
{
/*LIN_FRAME_CTR*/    	      {0, 50, 0},

/*LIN_FRAME_ST*/    	      {0, 0, 0},

/*LIN_FRAME_MASTER_REQUEST*/  {0, 0, 0},

/*LIN_FRAME_SlAVE_RESPONSE*/  {0, 0, 0},
};



/************ LIN Frame timeout ************/
l_u16 lin_frame_timeout_val[8] =  {4, 5, 6, 7, 7, 8, 9, 10};

const l_u16 lin_frame_timeout_val_19200[8] =  {4, 5, 6, 7, 7, 8, 9, 10};
const l_u16 lin_frame_timeout_val_9600[8] =  {8, 10, 11, 13, 14, 16, 17, 19};
const l_u16 lin_frame_timeout_val_4800[8] =  {16, 19, 22, 25, 28, 31, 34, 37};


/************* Node Attribute ***************/
   
static l_u8 lin_configured_NAD = 0x6A;       /* configured_NAD ，节点地址 */ 
static l_u8 lin_initial_NAD = 0x6A;    /* initial_NAD */ 
lin_product_id_t product_id = {0x0004, 0x0005, 0x06};      /* {<supplier_id>,<function_id>,<variant>} */ 



/********************************************************************************
 * Function: get_configured_nad
 * Param<void>:
 * Return<>:
 * REQ IDs:
 * Discription:
 * Note:
*********************************************************************************/
l_u8 get_configured_nad(void)
{
    return(lin_configured_NAD); 
}

void set_configured_nad(l_u8 nad)
{
    lin_configured_NAD = nad; 
}

/********************************************************************************
 * Function: get_configured_nad
 * Param<void>:
 * Return<>:
 * REQ IDs:
 * Discription:
 * Note:
*********************************************************************************/
l_u8 get_initial_nad(void)
{
    return(lin_initial_NAD); 
}

void set_initial_nad(l_u8 nad)
{
    lin_initial_NAD = nad; 
}
