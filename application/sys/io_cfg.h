/**
 ******************************************************************************
 * @author: Nark
 * @date:   29/03/2024
 ******************************************************************************
**/

#ifndef __IO_CFG_H__
#define __IO_CFG_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>

/******************************************************************************
* led life io pin map
*******************************************************************************/
#define LED_LIFE_IO_PORT                (GPIOA)
#define LED_LIFE_IO_PIN                 (GPIO_Pin_4)
#define LED_LIFE_IO_CLOCK               (RCC_AHBPeriph_GPIOA)

/******************************************************************************
* usart1 io pin map
*******************************************************************************/
#define USART1_GPIO_PORT                (GPIOA)
#define USART1_GPIO_CLOCK               (RCC_AHBPeriph_GPIOA)
#define USART1_CLOCK                    (RCC_APB2Periph_USART1)
#define USART1_TX_PIN                   (GPIO_Pin_2)
#define USART1_RX_PIN                   (GPIO_Pin_3)

/* led life functions */
extern void led_life_on();
extern void led_life_off();

/* usart1 functions */
extern void usart1_init(uint32_t usart1_speed);
extern void usart1_put_char(uint8_t _char);
extern uint8_t usart1_get_char();

/* io initialize */
extern void io_init();

#ifdef __cplusplus
}
#endif

#endif /* __IO_CFG_H__ */