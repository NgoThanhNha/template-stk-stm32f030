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

#include "console.h"

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

	RCC_AHBPeriphClockCmd(USART1_GPIO_CLOCK, ENABLE);
	GPIO_PinAFConfig(USART1_GPIO_PORT, GPIO_PinSource2, GPIO_AF_1);
	GPIO_PinAFConfig(USART1_GPIO_PORT, GPIO_PinSource3, GPIO_AF_1);

	GPIO_InitStructure.GPIO_Pin = USART1_TX_PIN | USART1_RX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(USART1_GPIO_PORT, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(USART1_CLOCK, ENABLE);
	USART_InitStructure.USART_BaudRate = usart1_speed;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);

	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ClearITPendingBit(USART1, USART_IT_RXNE | USART_IT_TXE);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	USART_Cmd(USART1, ENABLE);

	NVIC_SetPriority(USART1_IRQn, 0);
	NVIC_EnableIRQ(USART1_IRQn);
}

void usart1_put_char(uint8_t _char) {

	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

	/* put transmission data */
	USART_SendData(USART1, (uint8_t)_char);

	/* wait transmission completed */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);

}

uint8_t usart1_get_char() {
	volatile uint8_t c;

	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
		c = (uint8_t)USART_ReceiveData(USART1);
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}

	return c;
}

void i2c_init() {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Pin = IR_SENSOR_SCL_PIN | IR_SENSOR_SDA_PIN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;

	RCC_AHBPeriphClockCmd(IR_SENSOR_GPIO_CLOCK, ENABLE);
	GPIO_Init(IR_SENSOR_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(IR_SENSOR_GPIO_PORT, GPIO_PinSource9, GPIO_AF_4);
	GPIO_PinAFConfig(IR_SENSOR_GPIO_PORT, GPIO_PinSource10, GPIO_AF_4);

	/* configure the i2c1 clock source */
	RCC_I2CCLKConfig(RCC_I2C1CLK_SYSCLK);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

	I2C_InitTypeDef I2C_InitStructure;
	I2C_DeInit(I2C1);
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;			
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;			
	I2C_InitStructure.I2C_Ack = I2C_Ack_Disable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_AnalogFilter = I2C_AnalogFilter_Enable;
	I2C_InitStructure.I2C_DigitalFilter = 0;
	/* 400kHz at 48Mhz */
	I2C_InitStructure.I2C_Timing = 0x50330309;

	/* i2c1 init & enable */
	I2C_Init(I2C1, &I2C_InitStructure);				
	I2C_Cmd(I2C1, ENABLE);

	while (I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));
}

int i2c_read(uint8_t device_addr, uint8_t reg_addr, uint8_t *data, int length) {
	unsigned int timeout;
	
	/* test on BUSY flag */
	timeout = 10000;
	while(I2C_GetFlagStatus(I2C1, I2C_ISR_BUSY) != RESET) {
		if(timeout-- == 0)
			return -1;
	}

	/* configure slave address, nbytes, reload, end mode and start or stop generation */
	I2C_TransferHandling(I2C1, device_addr, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);

	/* wait until TXIS flag is set */
  	timeout = 10000;
	while(I2C_GetFlagStatus(I2C1, I2C_ISR_TXIS) == RESET) {
		if(timeout-- == 0)
			return -1;
	}

	/* send register address */
	I2C_SendData(I2C1, (uint8_t)reg_addr);

	/* wait until TC flag is set */
	timeout = 10000;
	while(I2C_GetFlagStatus(I2C1, I2C_ISR_TC) == RESET) {
		if(timeout-- == 0)
			return -1;
	}

	/* configure slave address, nbytes, reload, end mode and start or stop generation */
	I2C_TransferHandling(I2C1, device_addr, length, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);

	for (int rx_data_index = 0; rx_data_index < length; rx_data_index++) {
		timeout = 10000;
		while(I2C_GetFlagStatus(I2C1, I2C_ISR_RXNE) == RESET) {
			if(timeout-- == 0)
				return -1;
		}
		data[rx_data_index] = I2C_ReceiveData(I2C1);
	}

	/* wait until STOPF flag is set */
	timeout = 10000;
	while(I2C_GetFlagStatus(I2C1, I2C_ISR_STOPF) == RESET) {
		if(timeout-- == 0)
			return -1;
	}

	/* clear STOPF flag */
	I2C_ClearFlag(I2C1, I2C_ICR_STOPCF);
	return 0;
}

int i2c_write(uint8_t device_addr, uint8_t reg_addr, uint8_t *data, int length) {
	unsigned int timeout;

	/* test on BUSY flag */
	timeout = 10000;
	while(I2C_GetFlagStatus(I2C1, I2C_ISR_BUSY) != RESET) {
		if(timeout-- == 0)
			return -1;
	}

	I2C_TransferHandling(I2C1, device_addr, 1, I2C_Reload_Mode, I2C_Generate_Start_Write);

	/* wait until TXIS flag is set */
  	timeout = 10000;
	while(I2C_GetFlagStatus(I2C1, I2C_ISR_TXIS) == RESET) {
		if(timeout-- == 0)
			return -1;
	}

	/* send register address */
	I2C_SendData(I2C1, (uint8_t)reg_addr);

	/* wait until TCR flag is set */
	timeout = 10000;
	while(I2C_GetFlagStatus(I2C1, I2C_ISR_TCR) == RESET) {
		if(timeout-- == 0)
			return -1;
	}

	I2C_TransferHandling(I2C1, device_addr, length, I2C_AutoEnd_Mode, I2C_No_StartStop);

	for (int tx_data_index = 0; tx_data_index < length; tx_data_index++) {
		timeout = 10000;
		while(I2C_GetFlagStatus(I2C1, I2C_ISR_TXIS) == RESET) {
			if(timeout-- == 0)
				return -1;
		}
		I2C_SendData(I2C1, data[tx_data_index]);
	}

	/* wait until STOPF flag is set */
	timeout = 10000;
	while(I2C_GetFlagStatus(I2C1, I2C_ISR_STOPF) == RESET) {
		if(timeout-- == 0)
			return -1;
	}

	/* clear STOPF flag */
	I2C_ClearFlag(I2C1, I2C_ICR_STOPCF);
	return 0;
}


void io_init() {
	/* led life init */
	led_life_init();

	/* i2c init */
	i2c_init();
}


