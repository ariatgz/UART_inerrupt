/*
 * main.c
 *
 *  Created on: Dec 18, 2024
 *      Author: ariat
 */

#include "main.h"
#include"string.h"

#define TRUE 1
#define FALSE 0

void SystemClockConfig(void);
void UART2_Init(void);
void Error_handler(void);
uint8_t convert_to_capital(uint8_t data);

UART_HandleTypeDef huart2;

char *user = "The application is running\r\n";

uint8_t dataBuffer[100];
uint8_t rcvd_data;
uint32_t count = 0;
uint8_t reception_complete = FALSE;

int main(void){

	HAL_Init();
	SystemClockConfig();
	UART2_Init();

	HAL_UART_Transmit(&huart2, (uint8_t *)user, (uint16_t)strlen(user), HAL_MAX_DELAY);


	while(reception_complete != TRUE){
		HAL_UART_Receive_IT(&huart2, &rcvd_data, 1);
	}


	while(1);



	return 0;
}

uint8_t convert_to_capital(uint8_t data){

	if(data >= 'a' && data <= 'z'){
		data -= 32;
	}

	return data;
}

void UART2_Init(){

	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength =  UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	if(HAL_UART_Init(&huart2)!= HAL_OK ){

		Error_handler();
	}
}

void Error_handler(void){

}
void SystemClockConfig(void){


}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){

	if(rcvd_data == '\r'){

		reception_complete = TRUE;
		dataBuffer[count++] = '\r';
		HAL_UART_Transmit(&huart2, dataBuffer, count, HAL_MAX_DELAY);

	}else{
		dataBuffer[count++] = rcvd_data;
	}


}
