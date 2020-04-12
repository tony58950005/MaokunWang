/*
 * ClassUartTest.cpp
 *
 *  Created on: Mar. 22, 2020
 *      Author: 59488
 */

#include "ClassUartTest.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include "usart.h"
#include "string.h"
#include "main.h"
ClassUartTest::ClassUartTest(UART_HandleTypeDef h) :
	huart(h)
{
	if (HAL_UART_Init(&huart) != HAL_OK)
	{
		Error_Handler();
	}
}

bool ClassUartTest::sendMessage(uint8_t* buffer, uint32_t bufferLength, uint32_t timeout)
{
	//TODO: Implement this function using HAL_UART_Transmit
		HAL_UART_Transmit(&huart, buffer, bufferLength, timeout);
	//TODO-AKOS: Check the return type of HAL_UART_Transmit


	//Does the HAL_UART_Transmit function use interrupt?Ans:No
	//Return, when transmit is succeeded
}

bool ClassUartTest::receiveMessage(uint8_t* buffer, uint32_t bufferLength, uint32_t timeout)
{
	//TODO: Implement this function using HAL_UART_Receive
	while (HAL_UART_Receive_IT(&huart2, buffer, bufferLength) != HAL_OK)
	{
		HAL_Delay(10);
	}
	HAL_UART_Receive_IT(&huart, buffer, timeout);
	//Does the HAL_UART_Receive function use interrupt for the receiving?Ans:No
	//Return, when receive is succeeded
}
