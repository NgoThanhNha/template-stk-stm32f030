
/**
 ******************************************************************************
 * @author: Nark
 * @date:   29/03/2024
 ******************************************************************************
**/

#ifndef __SYSTEM_IRQ_H__
#define __SYSTEM_IRQ_H__

#ifdef __cplusplus
 extern "C" {
#endif 

extern void nmi_handler();
extern void hardfault_handler();
extern void mem_manage_handler();
extern void bus_fault_handler();
extern void usage_fault_handler();
extern void svc_handler();
extern void pendsv_handler();
extern void system_tick_handler();

extern void wwdg_irq_handler();
extern void rtc_irq_handler();
extern void flash_irq_handler();
extern void rcc_irq_handler();
extern void exti0_1_irq_handler();
extern void exti2_3_irq_handler();
extern void exti3_irq_handler();
extern void exti4_15_irq_handler();
extern void dma1_channel1_irq_handler();
extern void dma1_channel2_3_irq_handler();
extern void dma1_channel4_5_irq_handler();
extern void adc_irq_handler();
extern void tim1_brk_up_trg_com_irq_handler();
extern void tim1_cc_irq_handler();
extern void tim3_irq_handler();
extern void lptim1_irq_handler();
extern void tim14_irq_handler();
extern void tim16_irq_handler();
extern void tim17_irq_handler();
extern void i2c1_irq_handler();
extern void spi1_irq_handler();
extern void usart1_irq_handler();

extern volatile uint16_t encoder_value;

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_IRQ_H__ */
