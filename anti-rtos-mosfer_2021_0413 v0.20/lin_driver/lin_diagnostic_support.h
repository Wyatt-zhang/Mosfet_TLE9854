/*******************************************************************************
* Copyright (c) 2015, JE
* All Rights Reserved.
* Dept.: APG Shared
* File: lin_diagnostic_support.c
* Description:
* REQ IDs: 
* History:
* 2015-09-07,  Lei Yingjun
*******************************************************************************/

#ifndef LIN_DIAGNOSTIC_SUPPORT_H
#define LIN_DIAGNOSTIC_SUPPORT_H


#include "lin_protocol.h"



#define DATA_READ_ONLY   0
#define DATA_RAM_WRITE   1   /* RAM DATA, will lost after power off */
#define DATA_DFLASH_RW   2
#define DATA_WRITE_ONCE  3


#define UDS_ACCESS_DELAY_FLAG    (0xA7)
#define UDS_ACCESS_UNDELAY_FLAG  (0xFF)

#define UDS_NO_PROG_REQUEST      (0xFF)
#define UDS_PROG_REQUEST_PENDING (0x00)



#define UDS_SESSION_GET_MODIFY_CODE(uds_mode_cur, uds_mode_to)    (((uds_mode_cur) << (0x08u)) | (uds_mode_to))
#define UDS_SESSION_STD_TO_STD   (0x0101u)
#define UDS_SESSION_STD_TO_PROG  (0x0102u)
#define UDS_SESSION_STD_TO_EOL   (0x0103u)
#define UDS_SESSION_EOL_TO_STD   (0x0301u)
#define UDS_SESSION_EOL_TO_PROG  (0x0302u)
#define UDS_SESSION_EOL_TO_EOL   (0x0303u)
#define UDS_SESSION_PROG_TO_PROG (0x0202u)

#define UDS_SESSION_STD_TO_CODE   (0x0141u)
#define UDS_SESSION_EOL_TO_CODE   (0x0341u)
#define UDS_SESSION_CODE_TO_STD   (0x4101u)
#define UDS_SESSION_CODE_TO_EOL   (0x4103u)
#define UDS_SESSION_CODE_TO_CODE   (0x4141u)

#define UDS_SESSION_PROG_TO_STD  (0x0201u)
#define UDS_SESSION_PROG_TO_EOL  (0x0203u)


#define UDS_RESET_ACTIVE_DELAY       (20)     /*[5ms], 100ms, Max: 65535 */
#define UDS_SECURITY_MAX_TIME        (2000u)  /* [5ms], 10 sec, Max: 65535 */
#define UDS_SESSION_MAX_TIME         (1000u)  /* [5ms], 5 sec */
#define UDS_INVALID_ACCESS_MAX_TIMES 2
#define UDS_RECEIVE_VALID_REQUEST()  uds_session_remain_time  = UDS_SESSION_MAX_TIME


#define ROUTINE_FAILED   0x00
#define ROUTINE_COMPLETE 0x01
#define ROUTINE_RUNNING  0x02

/*********** typedefs ************/

typedef enum UDS_MODE_T
{
    UDS_SESSION_STD = 1u,
    UDS_SESSION_PROG,
    UDS_SESSION_EOL
}uds_mode_t;


typedef enum UDS_ACCESS_LEVEL_T
{
    UDS_ACCESS_LEVEL_1 = 0,
    UDS_ACCESS_LEVEL_2,
    UDS_ACCESS_LEVEL_MAX
}uds_access_level_t;

typedef enum UDS_SECURE_ST_T
{
   UDS_UNLOCKED_ALL = 0,
   UDS_LOCKED_L1
}uds_secure_st_t;

#define UDS_ACCESS_NO_LOCK 0
#define UDS_LOCKED_ALL     UDS_LOCKED_L1


typedef struct ID_DATA_T
{
    l_u16 dt_id; /* 0100 - EFFF and F010 - F0FF for vehicleManufacturerSpecific */
    l_u8 *p_data;
    l_u8 dlc;
    l_u8 rt_mode; /* Access type : DATA_READ_ONLY or DATA_READ_WRITE */
}id_data_t;


typedef struct __LocalRoutineType__
{
    l_bool locked;
    l_u16 RoutineId;
    l_bool (* pInitRoutine)  (void);
    l_u8 (* pLocalRoutine) (void);
}LocalRoutineType;


typedef struct __LocalRoutineDataType__
{
    l_u32 data1;
    l_u32 data2;
}LocalRoutineDataType;


typedef enum __LocalRoutineState__
{
   LR_IDLE = 0,
   LR_RUNNING,
   LR_ABORTED,
   LR_FAILED,
   LR_COMPLETE
}LocalRoutineState;


/******************************** Variable **********************************/

#define LOCAL_ROUTINE_COUNT 1
extern const LocalRoutineType Local_Routines[LOCAL_ROUTINE_COUNT];

extern LocalRoutineState Local_Routine_State[LOCAL_ROUTINE_COUNT];





/******************************** Functions **********************************/

extern l_bool get_reset_request_flg(void);
extern void put_reset_request_flg(l_bool reset_flg);

extern void diag_transmit_response_msg(l_u16 data_length, l_u8 *data_buffer);
extern void diag_negative_response(l_u8 service, l_u8 response_code);
extern void diag_response_pending(l_u8 service);
extern void diag_no_response(void);

extern uds_mode_t uds_get_session(void);
extern uds_secure_st_t uds_get_secure_status(void);

extern l_u8 uds_set_diagnostic_mode(uds_mode_t uds_mode_type);

extern void uds_ecu_reset(void);



#endif   /*End of LIN_DIAGNOSTIC_SUPPORT_H */
/*--------EOF--------*/


