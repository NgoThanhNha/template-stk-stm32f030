/**
 ******************************************************************************
 * @author: Nark
 * @date:   01/04/2024
 ******************************************************************************
**/

#include "stk_startup.h"

#include "stk.h"
#include "message.h"

#include "system_stm32f0xx.h"
#include "system_irq.h"

#include "app.h"
#include "io_cfg.h"

#include "platform.h"
#include "console.h"

/* define the addresses of data and bss sections */
extern uint32_t _sidata, _sdata, _edata, _sbss, _ebss, _estack;
extern void (*__preinit_array_start[])();
extern void (*__preinit_array_end[])();
extern void (*__init_array_start[])();
extern void (*__init_array_end[])();

static void sys_banner();

/* reset handler */
void reset_handler(void) {
    /* call the system init function */
    SystemInit();

    uint32_t *src, *dest;

    /*------------------------------------------------------------------*/
    /*      copy the data segment initializers from flash to SRAM       */
    /*------------------------------------------------------------------*/
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

    volatile unsigned i, cnt;
    
	/* invoke all static constructors */
	cnt = __preinit_array_end - __preinit_array_start;
	for (i = 0; i < cnt; i++)
		__preinit_array_start[i]();

	cnt = __init_array_end - __init_array_start;
	for (i = 0; i < cnt; i++)
		__init_array_start[i]();

    /* usart1 init */
	usart1_init(CONSOLE_SPEED);

    /* console init */
    console_init();

    /* system banner */
    sys_banner();
    
    /* go to the main application */
    main_app();
}

/* PY32F030xx cortex-M0+ processor exception vector table */
__attribute__((section(".isr_vector"))) void (*const g_pfnVectors[])(void) = {
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

    wwdg_irq_handler,                               // Window WatchDog
    0,                                              // Reserved 
    rtc_irq_handler,                                // RTC through EXTI Line
    flash_irq_handler,                              // FLASH
    rcc_irq_handler,                                // RCC
    exti0_1_irq_handler,                            // EXTI Line 0 and 1
    exti2_3_irq_handler,                            // EXTI Line 2 and 3 
    exti4_15_irq_handler,
    0,                                              // EXTI Line 4 to 15
    dma1_channel1_irq_handler,                      // DMA1 Channel 1
    dma1_channel2_3_irq_handler,                    // DMA1 Channel 2 and Channel 3
    dma1_channel4_5_irq_handler,                    // DMA1 Channel 4 and Channel 5
    adc_irq_handler,                                // ADC
    tim1_brk_up_trg_com_irq_handler,                // TIM1 Break, Update, Trigger and Commutation
    tim1_cc_irq_handler,                            // TIM1 Capture Compare
    0,                                              // Reserved
    tim3_irq_handler,                               // TIM3
    0,                                              // Reserved
    0,                                              // Reserved
    tim14_irq_handler,                              // TIM14
    0,                                              // Reserved
    tim16_irq_handler,                              // TIM16
    tim17_irq_handler,                              // TIM17
    i2c1_irq_handler,                               // I2C1
    0,                                              // Reserved
    spi1_irq_handler,                               // SPI1
    0,                                              // Reserved
    usart1_irq_handler,                             // USART1
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
};

void sys_banner() {
    SYS_PRINT("\n");
    SYS_PRINT(" ___  ____  _  _ \n");
    SYS_PRINT("/ __)(_  _)( )/ )\n");
    SYS_PRINT("\\__ \\  )(  (   (\n");
    SYS_PRINT("(___/ (__) (_)\\_)\n");
    SYS_PRINT("\n");
    SYS_PRINT("Kernel version: %s\n", STK_VERSION);
}