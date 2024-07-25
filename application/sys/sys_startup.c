/**
 ******************************************************************************
 * @author: Nark
 * @date:   01/04/2024
 ******************************************************************************
**/

#include "sys_startup.h"

#include "task.h"
#include "message.h"

#include "system_stm32f0xx.h"
#include "sys_irq.h"
#include "sys_cfg.h"

#include "app.h"
#include "io_cfg.h"

#include "platform.h"
#include "led.h"

/* define the addresses of data and bss sections */
extern uint32_t _sidata, _sdata, _edata, _sbss, _ebss, _estack;
extern void (*__preinit_array_start[])();
extern void (*__preinit_array_end[])();
extern void (*__init_array_start[])();
extern void (*__init_array_end[])();

/* reset handler */
void reset_handler(void) {
    /* call the system init function */
    SystemInit();

    uint32_t *src, *dest;

    /*****************************************************************************/
    /* copy the data segment initializers from flash to SRAM
    ******************************************************************************/
    /* pointer start address in flash */
    src = &_sidata;

    /* pointer start address in sram */
    dest = &_sdata;

    while (dest < &_edata) {
        *dest++ = *src++;
    }

    /* zero fill to .bss section */
    dest = &_sbss;
    while (dest < &_ebss) {
        *dest++ = 0;
    }

    /* fill stack section */
    sys_stack_fill();

    /*****************************************************************************/
    /* system config
    ******************************************************************************/
    sys_cfg_tick();
    sys_cfg_console();

    volatile unsigned i, cnt;
    
	/* invoke all static constructors */
	cnt = __preinit_array_end - __preinit_array_start;
	for (i = 0; i < cnt; i++)
		__preinit_array_start[i]();

	cnt = __init_array_end - __init_array_start;
	for (i = 0; i < cnt; i++)
		__init_array_start[i]();

    /* usart1 init */
	usart1_init(CONSOLE_BAUDRATE);

    /* io init */
    io_init();    

    /* led init */
    led_init_func(&led_life, led_life_on, led_life_off, 10);
    led_blink_set(&led_life, 1000);

    /* system update info */
    sys_ctrl_show_info();
    
    /* go to the main application */
    main_app();
}

/* PY32F030xx cortex-M0+ processor exception vector table */
__attribute__((section(".isr_vector"))) void (*const g_pfnVectors[])(void) = {
    /* system interrupt */
    (void (*)(void))&_estack,                       // Stack pointer
    reset_handler,                                  // Reset Handler
    nmi_handler,                                    // NMI Handler
    hardfault_handler,                              // Hard Fault Handler
    mem_manage_handler,                             // MemManage Handler
    bus_fault_handler,                              // BusFault Handler
    usage_fault_handler,                            // UsageFault Handler
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
    svc_handler,                                    // SVCall Handler
    0,                                              // Debug Monitor Handler
    0,                                              // Reserved
    pendsv_handler,                                 // PendSV Handler
    system_tick_handler,                            // SysTick Handler

    /* external interrupt */
    default_handler,                                // Window WatchDog
    0,                                              // Reserved 
    default_handler,                                // RTC through EXTI Line
    default_handler,                                // FLASH
    default_handler,                                // RCC
    default_handler,                                // EXTI Line 0 and 1
    default_handler,                                // EXTI Line 2 and 3 
    default_handler,
    0,                                              // EXTI Line 4 to 15
    default_handler,                                // DMA1 Channel 1
    default_handler,                                // DMA1 Channel 2 and Channel 3
    default_handler,                                // DMA1 Channel 4 and Channel 5
    default_handler,                                // ADC
    default_handler,                                // TIM1 Break, Update, Trigger and Commutation
    default_handler,                                // TIM1 Capture Compare
    0,                                              // Reserved
    default_handler,                                // TIM3
    0,                                              // Reserved
    0,                                              // Reserved
    default_handler,                                // TIM14
    0,                                              // Reserved
    default_handler,                                // TIM16
    default_handler,                                // TIM17
    default_handler,                                // I2C1
    0,                                              // Reserved
    default_handler,                                // SPI1
    0,                                              // Reserved
    usart1_irq_handler,                             // USART1
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
};