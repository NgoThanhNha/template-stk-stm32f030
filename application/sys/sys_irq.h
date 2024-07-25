
/**
 ******************************************************************************
 * @author: Nark
 * @date:   29/03/2024
 ******************************************************************************
**/

#ifndef __SYS_IRQ_H__
#define __SYS_IRQ_H__

#ifdef __cplusplus
 extern "C" {
#endif 

#include <stdint.h>

/* system interrupts */
extern void default_handler();
extern void nmi_handler();
extern void hardfault_handler();
extern void mem_manage_handler();
extern void bus_fault_handler();
extern void usage_fault_handler();
extern void svc_handler();
extern void pendsv_handler();
extern void system_tick_handler();

/* external interrupts */
extern void usart1_irq_handler();

/* system control function */
extern uint32_t sys_ctrl_millis();

#ifdef __cplusplus
}
#endif

#endif /* __SYS_IRQ_H__ */
