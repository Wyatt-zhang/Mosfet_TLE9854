 /*******************************************************************************
* Copyright (c) 2015, JE
* All Rights Reserved.
* Dept.: APG Shared
* File: lin_diagnostic_service.h
* Description:
* REQ IDs: 
* History:
* 2015-09-07,  Lei Yingjun
*******************************************************************************/

#ifndef LIN_DIAGNOSTIC_SERVICE_H
#define LIN_DIAGNOSTIC_SERVICE_H

#include "lin_protocol.h"


#define POSITIVE_RESPONSE (0x40u)
#define NEGATIVE_RESPONSE (0x7Fu)

#define UDS_GET_POSITIVE_RESPONSE(server_id)         (POSITIVE_RESPONSE + (server_id))


#define UDS_SUB_FUNCITON_PARAMETER_MASK (0x7Fu)

#define UDS_GET_SUB_FUNCTION_INDICATION_BIT(sub_function_byte) (l_bool)(((sub_function_byte) >> 7u) & 0x01u)


/*********** UDS COMMAND MACRO ***********/

#define DIAG_10      (0x10)
#define DIAG_11      (0x11)
#define DIAG_27      (0x27)
#define DIAG_28      (0x28)
#define DIAG_3E      (0x3E)
#define DIAG_85      (0x85)
#define DIAG_22      (0x22)
#define DIAG_2E      (0x2E)
#define DIAG_19      (0x19)
#define DIAG_14      (0x14)
#define DIAG_31      (0x31)
#define DIAG_2F      (0x2F)
#define DIAG_34      (0x34)
#define DIAG_35      (0x35)
#define DIAG_36      (0x36)
#define DIAG_37      (0x37)

#define DIAG_B0      (0xB0)
#define DIAG_B1      (0xB1)
#define DIAG_B2      (0xB2)
#define DIAG_B3      (0xB3)
#define DIAG_B4      (0xB4)
#define DIAG_B5      (0xB5)
#define DIAG_B6      (0xB6)
#define DIAG_B7      (0xB7)

/***** min length of each service ******/

#define DIA_10_MIN_LEN      (0x02u)
#define DIA_11_MIN_LEN      (0x02u)
#define DIA_27_MIN_LEN      (0x02u)
#define DIA_28_MIN_LEN      (0x03u)
#define DIA_3E_MIN_LEN      (0x02u)
#define DIA_85_MIN_LEN      (0x02u)

#define DIA_22_MIN_LEN      (0x03u)
#define DIA_2E_MIN_LEN      (0x04u)

#define DIA_14_MIN_LEN      (0x04u) /* 3 Bytes DTC */
#define DIA_19_MIN_LEN      (0x02u)

#define DIA_31_MIN_LEN      (0x04u)

#define DIA_2F_MIN_LEN      (0x04u)


/*********** negative response codes ************/

#define RSP_NO_NEGATIVE_STATE                                  (0x00u)
#define RSP_GENERAL_REJECT                                     (0x10u)
#define RSP_SERVICE_NOT_SUPPORT                                (0x11u)
#define RSP_SUBFUNCTION_NOT_SUPPORTED                          (0x12u)
#define RSP_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT         (0x13u)
#define RSP_RESPONSE_TOO_LONG                                  (0x14u)
#define RSP_BUSY_REPEAT_REQUEST                                (0x21u)
#define RSP_CONDITIONS_NOT_CORRECT                             (0x22u)
#define RSP_REQUEST_SEQUENCE_ERROR                             (0x24u)
#define RSP_NO_RESPONSE_FROM_SUBNET_COMPONENT                  (0x25u)
#define RSP_FAILURE_PREVENTS_EXECUTION_OF_REQUESTED_ACTION     (0x26u)
#define RSP_REQUEST_OUT_OF_RANGE                               (0x31u)
#define RSP_SECURITY_ACCESS_DENIED                             (0x33u)
#define RSP_INVALID_KEY                                        (0x35u)
#define RSP_EXCEED_NUMBER_OF_ATTEMPTS                          (0x36u)
#define RSP_REQUIRED_TIME_DELAY_NOT_EXPIRED                    (0x37u)
#define RSP_DOWNLOAD_NOT_ACCEPTED                              (0x40u)
#define RSP_IMPROPER_DOWNLOAD_TYPE                             (0x41u)
#define RSP_CANT_DOWNLOAD_TO_SPECIFIE_DADDRESS                 (0x42u)
#define RSP_CANT_DOWNLOAD_NUMBER_OF_BYTES_REQUESTED            (0x43u)
#define RSP_UPLOAD_DOWNLOAD_NOT_ACCEPTED                       (0x70u)
#define RSP_TRANSFER_SUSPENDED                                 (0x71u)
#define RSP_GENERAL_PROGRAMMING_FAILURE                        (0x72u)
#define RSP_WRONG_BLOCK_SEQUENCE_COUNTER                       (0x73u)
#define RSP_SUB_FUNCTION_NOT_SUPPORTED_IN_ACTIVE_SESSION       (0x7Eu)
#define RSP_SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION            (0x7Fu)

/********* uds service related macros **********/

/* 0x11 ECUReset */
#define UDS_ECU_HARDWARE_RESET                    (0x01u)
#define UDS_ECU_KEY_OFFON_RESET                   (0x02u)
#define UDS_ECU_SOFTWARE_RESET                    (0x03u)

/* 0x27 SecurityAccess */
#define UDS_SECURITY_REQUEST_SEED                 (0x01u)
#define UDS_SECURITY_REQUEST_SEED_LEVEL_1         (0x01u)
#define UDS_SECURITY_RECEIVE_KEY_LEVEL_1          (0x02u)
#define UDS_SECURITY_REQUEST_SEED_LEVEL_2         (0x03u)
#define UDS_SECURITY_RECEIVE_KEY_LEVEL_2          (0x04u)
#define UDS_SECURITY_BUFFER_LENGTH                (0x06u)
#define UDS_SECURITY_SEED_LENGTH                  (0x04u)
#define UDS_SECURITY_KEY_LENGTH                   (0x04u)

/* 0x14 ClearDiagnosticInformation */
#define UDS_CLEAR_EMISSIONS_RELATED_SYS           (0x000000uL)
#define UDS_CLAEL_ALL_DTC                         (0xFFFFFF)

/* Ox19  ReadDTCInfromation */
#define DTC_FORMAT_ID_15031    (0x00u)
#define DTC_FORAMT_ID_14229    (0x01u)
#define DTC_FORAMT_ID_J1939    (0x02u)
#define DTC_FORAMT_ID_11992    (0x03u)

#define UDS_reportNumberOfDTCByStatusMask          (0x01u)
#define UDS_reportDTCByStatusMask                  (0x02u)
#define UDS_reportDTCSnapshotIdentification        (0x03u)
#define UDS_reportDTCSnapshotRecordByDTCNumber     (0x04u)
#define UDS_reportDTCSnapshotRecordByRecordNumber  (0x05u)
#define UDS_reportDTCExtendedDataRecordByDTCNumber (0x06u)
#define UDS_reportNumberOfDTCBySeverityMaskRecord  (0x07u)
#define UDS_reportDTCBySeverityMaskRecord          (0x08u)
#define UDS_reportSeverityInformationOfDTC         (0x09u)
#define UDS_reportSupportedDTC                     (0x0Au)
#define UDS_reportFirstTestFailedDTC               (0x0Bu)
#define UDS_reportFirstConfirmedDTC                (0x0Cu)
#define UDS_reportMostRecentTestFailedDTC          (0x0Du)


#define DTC_STATUS_AVAI_MASK (0xFFu) 


/* 0x28 CommunicationControl */
#define UDS_CC_MODE_EN_ALL  (0x00)
#define UDS_CC_MODE_DIS_TX  (0x01)
#define UDS_CC_MODE_DIS_RX  (0x02)
#define UDS_CC_MODE_DIS_ALL (0x03)
#define UDS_CC_TYPE_NORMAL  (0x01)
#define UDS_CC_TYPE_NM      (0x02)
#define UDS_CC_TYPE_NR_NM   (0x03)

/* 0x85 ControlDTCSetting */
#define DTC_SETTING_ON      (0x01u)
#define DTC_SETTING_OFF     (0x02u)

/* 0x31 RoutineControl */
#define UDS_START_ROUTINE                   (0x01u)
#define UDS_STOP_ROUTINE                    (0x02u)
#define UDS_REQUEST_ROUTINERESULTS          (0x03u)

#define DIA_31_NOT_ACTIVATED                (0x00u)
#define DIA_31_IN_PROGRESS                  (0x01u)
#define DIA_31_TERMINATED_OK                (0x02u)
#define DIA_31_TERMINATED_NOT_OK            (0x03u)

/* 0x2F  InputOutputControl */
#define UDS_2F_Return_Control_To_ECU        (0x00u)
#define UDS_2F_Return_To_Default            (0x01u)
#define UDS_2F_Freeze_Current_State         (0x02u)
#define UDS_2F_Short_Term_Adjustmet         (0x03u)




/******************************** Variable **********************************/





/******************************** Functions **********************************/

extern l_u8 get_response_nad(void);

extern void lin_diag_request_dispose(l_u8 request_nad);






#endif   /*End of LIN_DIAGNOSTIC_SERVICE_H */
/*--------EOF--------*/

