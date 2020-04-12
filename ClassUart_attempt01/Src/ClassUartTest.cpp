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



	//Does the HAL_UART_Transmit function use interrupt?Ans:No
	//Return, when transmit is succeeded
}

bool ClassUartTest::receiveMessage(uint8_t* buffer, uint32_t bufferLength, uint32_t timeout)
{
	//TODO: Implement this function using HAL_UART_Receive
	if(buffer[0]=='c')
	{
		HAL_UART_Receive_IT(&huart, buffer, timeout);
		return true;
	}
	//Does the HAL_UART_Receive function use interrupt for the receiving?Ans:Yes
	//Return, when receive is succeeded
}

 void ClassUartTest::HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart,uint8_t* buffer, uint32_t bufferLength, uint32_t timeout)
{
  /* Prevent unused argument(s) compilation warning */
  //UNUSED(huart);
  sendMessage(buffer, bufferLength, timeout);
  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
  HAL_Delay(500);
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_UART_RxCpltCallback could be implemented in the user file
   */
}



