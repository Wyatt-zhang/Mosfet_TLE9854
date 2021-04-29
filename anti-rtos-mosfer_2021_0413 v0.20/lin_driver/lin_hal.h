/*******************************************************************************
* Copyright (c) 2015, JE
* All Rights Reserved.
* Dept.: APG Shared
* File: lin_hal.h
* Description:
* REQ IDs: 
* History:
* 2020-03-12,  Lei Yingjun
*******************************************************************************/

#ifndef LIN_HAL_H
#define LIN_HAL_H


#include "TLE985x.h"
#include "lin_protocol.h"


 //#define    TLE984x 
 #define  TLE985x 
 

 /* All UART control and access registers*/
 #define LIN_UART_BUFFER       (UART1->SBUF.bit.VAL)
 #define LIN_UART_CONTROL      (UART1->SCON.reg)
 #define LIN_UART_MODE0        (UART1->SCON.bit.SM0)
 #define LIN_UART_MODE1        (UART1->SCON.bit.SM1)
 #define LIN_UART_RUN          (UART1->SCON.bit.REN)
 #define LIN_UART_9BITREC      (UART1->SCON.bit.RB8)
 #define LIN_UART_9BITTRANS    (UART1->SCON.bit.TB8)

 #define LIN_UART_BCON_PRE     (SCU->BCON1.bit.BR1_PRE)
 #define LIN_UART_BCON_FDSEL   (SCU->BGL1.bit.BG1_FD_SEL)
 #define LIN_UART_BCON_BG      (SCU->BG1.reg)
 #define LIN_UART_BCON_RUN     (SCU->BCON1.bit.BR1_R)

 #define LIN_UART_IR_SET_EN    (CPU->NVIC_ISER.bit.Int_UART1)
 #define LIN_UART_IR_PENDING   (CPU->NVIC_ISPR.bit.Int_UART1)
 #define LIN_UART_IR_PRIO      (CPU->NVIC_IPR2.bit.PRI_UART1)
 #define LIN_UART_IR_RIEN      (SCU->MODIEN2.bit.RIEN1)
 #define LIN_UART_IR_TIEN      (SCU->MODIEN2.bit.TIEN1)

 #define LIN_UART_STATUS       (SCU->LINST.reg)
 #define LIN_UART_CLR_STATUS   (SCU->LINSCLR.reg)
 #define LIN_UART_BR_SYN_DET   (SCU->LINST.bit.BGSEL)
 #define LIN_UART_BR_DIS       (SCU->LINST.bit.BRDIS)
 #define LIN_UART_SYNEN        (SCU->LINST.bit.SYNEN)
 #define LIN_UART_CLR_BRK      (SCU->LINSCLR.bit.BRKC)
 #define LIN_UART_CLR_EOFSYN   (SCU->LINSCLR.bit.EOFSYNC)
 #define LIN_UART_CLR_ERRSYN   (SCU->LINSCLR.bit.ERRSYNC)

 #define LIN_UART_IRQ_NR         (INTISR10_IRQn)


 #ifdef AUTOBAUD_ENABLED
		/* Timer 2 is needed for baudrate synchronization when using UART 1 */
		#define LIN_TIMER_PRE         (TIMER2->MOD.bit.T2PRE)
		#define LIN_TIMER_PRE_EN      (TIMER2->MOD.bit.PREN)
		#define LIN_TIMER_COUNTER_EN  (TIMER2->MOD.bit.DCEN)
		#define LIN_TIMER_EDGE_SELECT (TIMER2->MOD.bit.T2REGS)
		#define LIN_TIMER_EXT_START   (TIMER2->MOD.bit.T2RHEN)
		#define LIN_TIMER_CAP_REL     (TIMER2->CON.bit.CP_RL2)
		#define LIN_TIMER_T_C_SEL     (TIMER2->CON.bit.C_T2)
		#define LIN_TIMER_EXT_EN      (TIMER2->CON.bit.EXEN2)
		#define LIN_TIMER_RUN         (TIMER2->CON.bit.TR2)
		#define LIN_TIMER_EXT_IR_EN   (TIMER2->CON1.bit.EXF2EN)
		#define LIN_TIMER_INT_IR_EN   (TIMER2->CON1.bit.TF2EN)
		#define LIN_TIMER_HIGH        (TIMER2->CNT.bit.T2H)
		#define LIN_TIMER_LOW         (TIMER2->CNT.bit.T2L)
		#define LIN_TIMER_CAP_H       (TIMER2->RC.bit.RCH2)
		#define LIN_TIMER_CAP_L       (TIMER2->RC.bit.RCL2)
	#ifdef TLE985x
		#define LIN_TIMER_MODPISEL    (SCU->MODPISEL.reg)
		#define LIN_TIMER_MODPISEL1   (SCU->MODPISEL1.reg)
		#define LIN_TIMER_MODPISEL2   (SCU->MODPISEL2.reg)
	#elif defined TLE984x
		#define LIN_TIMER_EXCON       (SCU->MODPISEL1.bit.T2EXCON)
		#define LIN_TIMER_EXIS        (SCU->MODPISEL2.bit.T2EXIS)
	#endif //end of TLE985x
 #endif /* end #ifdef AUTOBAUD_ENABLED */


#define LINST_MASK_SYNBRK       0x38u
#define LINST_FLAG_EOFSYN       0x18u
#define LINST_FLAG_ERRSYN       0x20u
#define LINST_FLAG_BRK          0x10u


#define        BRG_PRE       ((l_u8)0)
#define        BRG_VAL       ((l_u16)130)		/* calculated by 40MHz */
#define        BRG_FD_SEL    ((l_u8)7)
#define        BG_SEL        ((l_u8)0)
#define        LIN_UART1
#define        LIN_INTERRUPT_PRIORITY  ((l_u8)3)


#define        LIN_AUTOBAUD_TIMEOUT    (7u)

#define        MIN_BDREG	(125)	/* caculateed by 20kbps */
#define        MAX_BDREG	(625)	/* caculateed by 4kbps */

/******************************** Functions **********************************/


extern void lin_sci_init(void);
extern void lin_sci_deinit(void);
extern void lin_sci_tx_wake_up(void);
extern void lin_goto_idle_state(void);
extern void lin_goto_sleep_mode(void);
extern void lin_sci_rx_response(l_u8  msg_length);
extern void lin_sci_tx_response(l_u8  msg_length);
extern void lin_sci_timeout(void);
extern void lin_sci_rx_isr(void);




#endif  /*End of LIN_HAL_H */
/*--------EOF--------*/


