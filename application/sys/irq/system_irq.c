
/**
 ******************************************************************************
 * @author: Nark
 * @date:   29/03/2024
 ******************************************************************************
**/

#include "stm32f0xx.h"
#include "stm32f0xx_tim.h"
#include "stm32f0xx_exti.h"
#include "system_irq.h"
#include "io_cfg.h"

#include "timer.h"

#include "platform.h"
#include "console.h"
#include "hard_timer.h"

#include "task_polling.h"

void nmi_handler() {
	FATAL("SYSTEM", 0x01);
}

void hardfault_handler() {
	FATAL("SYSTEM", 0x02);
}

void mem_manage_handler() {
	FATAL("SYSTEM", 0x03);
}

void bus_fault_handler() {
	FATAL("SYSTEM", 0x04);
}

void usage_fault_handler() {
	FATAL("SYSTEM", 0x05);
}

void svc_handler() {

}

void pendsv_handler() {

}

void wwdg_irq_handler() {

}

void rtc_irq_handler() {

}

void flash_irq_handler() {

}

void rcc_irq_handler() {

}

void exti0_1_irq_handler() {

}


void exti2_3_irq_handler() {

}

void exti3_irq_handler() {
}

void exti4_15_irq_handler() {

}

void dma1_channel1_irq_handler() {

}

void dma1_channel2_3_irq_handler() {

}

void dma1_channel4_5_irq_handler() {

}

void adc_irq_handler() {

}

void tim1_brk_up_trg_com_irq_handler() {

}

void tim1_cc_irq_handler() {

}

void tim3_irq_handler() {

}

void lptim1_irq_handler() {

}

void tim14_irq_handler() {

}

void tim16_irq_handler() {

}

void tim17_irq_handler() {

}

void i2c1_irq_handler() {

}

void spi1_irq_handler() {

}

void system_tick_handler() {
	timer_tick(1);
	system_tick_delay_counter++;
	task_polling_handler();
}

void usart1_irq_handler() {

}
