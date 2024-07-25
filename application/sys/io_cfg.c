/**
 ******************************************************************************
 * @author: Nark
 * @date:   29/03/2024
 ******************************************************************************
**/

#include "io_cfg.h"

#include "stm32f0xx.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_usart.h"
#include "stm32f0xx_misc.h"
#include "stm32f0xx_i2c.h"
#include "stm32f0xx_tim.h"
#include "stm32f0xx_exti.h"
#include "stm32f0xx_syscfg.h"

void led_life_init() {
	GPIO_InitTypeDef    GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(LED_LIFE_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = LED_LIFE_IO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(LED_LIFE_IO_PORT, &GPIO_InitStructure);
}

void led_life_on() {
	GPIO_ResetBits(LED_LIFE_IO_PORT, LED_LIFE_IO_PIN);
}

void led_life_off() {
	GPIO_SetBits(LED_LIFE_IO_PORT, LED_LIFE_IO_PIN);
}

void usart1_init(uint32_t usart1_speed) {
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* enable clocks */
	RCC_AHBPeriphClockCmd(USART1_GPIO_CLOCK, ENABLE);
	RCC_APB2PeriphClockCmd(USART1_CLOCK, ENABLE);

	/* pin af config */
	GPIO_PinAFConfig(USART1_GPIO_PORT, GPIO_PinSource2, GPIO_AF_1);
	GPIO_PinAFConfig(USART1_GPIO_PORT, GPIO_PinSource3, GPIO_AF_1);

	/* gpio config */
	GPIO_InitStructure.GPIO_Pin = USART1_TX_PIN | USART1_RX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(USART1_GPIO_PORT, &GPIO_InitStructure);

	/* usart config */
	USART_InitStructure.USART_BaudRate = usart1_speed;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);

	/* USARTx interrupt config */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ClearITPendingBit(USART1, USART_IT_RXNE | USART_IT_TXE);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	/* enable uart*/
	USART_Cmd(USART1, ENABLE);

	/* enable interrupt */
	NVIC_SetPriority(USART1_IRQn, 0);
	NVIC_EnableIRQ(USART1_IRQn);
}

void usart1_put_char(uint8_t _char) {
	/* wait last transmission completed */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

	/* put transmission data */
	USART_SendData(USART1, (uint8_t)_char);

	/* wait transmission completed */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}

uint8_t usart1_get_char() {
	volatile uint8_t c;

	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);	
		c = (uint8_t)USART_ReceiveData(USART1);
	}

	return c;
}

void io_init() {
	/* led life init */
	led_life_init();
}


