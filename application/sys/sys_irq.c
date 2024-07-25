
/**
 ******************************************************************************
 * @author: Nark
 * @date:   29/03/2024
 ******************************************************************************
**/

#include "sys_irq.h"

#include "stm32f0xx.h"
#include "stm32f0xx_tim.h"
#include "stm32f0xx_exti.h"

#include "timer.h"

#include "platform.h"

#include "io_cfg.h"
#include "app.h"
#include "app_dbg.h"
#include "task_list.h"
#include "task_shell.h"

/* counter of milliseconds since the application run */
volatile uint32_t millis_current;

void default_handler() {
	FATAL("SYSTEM", 0x01);
}

void nmi_handler() {
	FATAL("SYSTEM", 0x02);
}

void hardfault_handler() {
	FATAL("SYSTEM", 0x03);
}

void mem_manage_handler() {
	FATAL("SYSTEM", 0x04);
}

void bus_fault_handler() {
	FATAL("SYSTEM", 0x05);
}

void usage_fault_handler() {
	FATAL("SYSTEM", 0x06);
}

void svc_handler() {

}

void pendsv_handler() {

}

void system_tick_handler() {
	static uint32_t div_counter = 0;

	/* increasing millis counter */
	millis_current++;

	/* kernel tick */
	timer_tick(1);

	if (div_counter == 10) {
		div_counter = 0;
	}

	switch (div_counter) {
	case 0:
		sys_irq_timer_10ms();
		break;

	default:
		break;
	}

	div_counter++;
}

uint32_t sys_ctrl_millis() {
	volatile uint32_t ret;
	ENTRY_CRITICAL();
	ret = millis_current;
	EXIT_CRITICAL();
	return ret;
}

void usart1_irq_handler() {
	sys_irq_shell();
}
