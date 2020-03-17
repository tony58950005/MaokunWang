/*
 * ledOn.cpp
 *
 *  Created on: Mar. 17, 2020
 *      Author: 59488
 */

#include "ledOn.h"
#include "stm32f4xx.h"
#include "main.h"

ledOn::ledOn() {
	// TODO Auto-generated constructor stub
	bool flag=true;
	//int LED_State=0;
	while(1)
	{
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) && flag)
	{
				  HAL_Delay(5);//reduce the bounce
				  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
				 // LED_State=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5);
				  flag = false;
	}else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)== GPIO_PIN_RESET)
	{
				  HAL_Delay(5);//reduce the bounce
				  flag=true;
	}
	}
}

ledOn::~ledOn() {
	// TODO Auto-generated destructor stub
}

