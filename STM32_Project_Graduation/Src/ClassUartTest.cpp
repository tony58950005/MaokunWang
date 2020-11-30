/*
 * ClassUartTest.cpp
 *
 *  Created on: Mar. 22, 2020
 *      Author: 59488
 */

#include "ClassUartTest.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include "string.h"
#include "main.h"

ClassUartTest::ClassUartTest(UART_HandleTypeDef h) :
	huart(h)
{
	__HAL_RCC_USART1_CLK_ENABLE();

	huart.Instance = USART1;
	huart.Init.BaudRate = 115200;
	huart.Init.WordLength = UART_WORDLENGTH_8B;
	huart.Init.StopBits = UART_STOPBITS_1;
	huart.Init.Parity = UART_PARITY_NONE;
	huart.Init.Mode = UART_MODE_TX_RX;
	huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart.Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_UART_Init(&huart) != HAL_OK)
	{
		Error_Handler(UartError);
	}
}

bool ClassUartTest::sendMessage(uint8_t* buffer, uint16_t bufferLength, uint32_t timeout)
{
	int count = 0;
	for (int i = 0; i < bufferLength; i++) {
		if (buffer[i] != '\0') {
			count++;
		} else {
			break;
		}
	}
	return (HAL_UART_Transmit(&huart, buffer, count, timeout) == HAL_OK);
}

bool ClassUartTest::receiveMessage(uint8_t* buffer, uint16_t bufferLength, uint32_t timeout)
{
	return (HAL_UART_Receive(&huart, buffer, bufferLength, timeout) == HAL_OK);
}

//bool ClassUartTest::sendMessageWithout0(uint8_t* buffer, uint16_t bufferLength, uint32_t timeout){
//	int count=0;
//	for(int i=0; i<bufferLength;i++){
//		if(buffer[i]!='\0'){
//			count++;
//		}else{
//			break;
//		}
//	}
//	return (HAL_UART_Transmit(&huart, buffer, count, timeout) == HAL_OK);
//}
//TODO: change uart.sendMessage to send only until \0 character. Use only one argument for uart.sendMessage.

