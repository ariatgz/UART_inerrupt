/*
 * msp.c
 *
 *  Created on: Dec 18, 2024
 *      Author: ariat
 */
#include "main.h"


void HAL_MspInit(void)
{
  //low level inits.
	// set up the priority grouping of the arm cortex mx

	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	// enable the required system exceptions of the arm

	SCB->SHCSR  |= 0x7 <<16; // usg fault, memory fault enabled

	// set up the priority for exceptions
	HAL_NVIC_SetPriority( MemoryManagement_IRQn,0,0);
	HAL_NVIC_SetPriority( BusFault_IRQn,0,0);
	HAL_NVIC_SetPriority( UsageFault_IRQn,0,0);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart){

	GPIO_InitTypeDef gpio_uart;

	//low level inints
	// enable the clock
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	//pin muxing config
		gpio_uart.Pin = GPIO_PIN_2;
		gpio_uart.Mode = GPIO_MODE_AF_PP;
		gpio_uart.Pull = GPIO_PULLUP;
		gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
		gpio_uart.Alternate = GPIO_AF7_USART2; //UART_Tx
		HAL_GPIO_Init(GPIOA, &gpio_uart);

		gpio_uart.Pin = GPIO_PIN_3;
		HAL_GPIO_Init(GPIOA, &gpio_uart);

	// enable IRQ and set the priority (NVIC Settings)
		HAL_NVIC_EnableIRQ(USART2_IRQn);
		HAL_NVIC_SetPriority(USART2_IRQn, 15, 0);

}

