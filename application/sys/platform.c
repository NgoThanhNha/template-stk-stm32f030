/**
 ******************************************************************************
 * @author: Nark
 * @date:   02/05/2024
 ******************************************************************************
**/

#include "platform.h"

#include "stm32f0xx.h"
#include "core_cm0.h"
#include "core_cmFunc.h"

#include "app_dbg.h"
#include "io_cfg.h"

#include "sys_cfg.h"

void enable_interrupts() {
	__enable_irq();
}

void disable_interrupts() {
	__disable_irq();
}

void fatal_error(const char* fatal_info, uint8_t fatal_id) {
    disable_interrupts();
    SYS_PRINT("\n");
    SYS_PRINT("************************ FATAL_ERROR ************************\n");
    SYS_PRINT("[FATAL_TYPE]: %s -> [FATAL_ID]: 0x%02X\n", fatal_info, fatal_id);
    SYS_PRINT("\n");
    while (1) {
        led_life_on();
        sys_ctrl_delay_ms(100);
        led_life_off();
        sys_ctrl_delay_ms(100); 
    }
}