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

bool ClassUartTest::sendMessage(uint8_t* buffer, uint16_t bufferLength, uint32_t timeout)
{
	return (HAL_UART_Transmit(&huart, buffer, bufferLength, timeout) == HAL_OK);
}

bool ClassUartTest::receiveMessage(uint8_t* buffer, uint16_t bufferLength, uint32_t timeout)
{
	return (HAL_UART_Receive(&huart, buffer, bufferLength, timeout) == HAL_OK);
}


