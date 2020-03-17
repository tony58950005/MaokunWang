/*
 * PushButtonLedToggle.cpp
 *
 *  Created on: Mar. 16, 2020
 *      Author: 59488
 */

#include "main.h"
#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include "PushButtonLedToggle.h"

PushButtonLedToggle::PushButtonLedToggle() {
	// TODO Auto-generated constructor stub
	bool flag=true;
	int LED_State=0;
	 if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) && flag)
		  {
			  HAL_Delay(5);//reduce the bounce
			  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
			  LED_State=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5);
			  flag = false;
		  }else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)== GPIO_PIN_RESET)
		  {
			  HAL_Delay(5);//reduce the bounce
			  flag=true;
		  }
}

PushButtonLedToggle::~PushButtonLedToggle() {
	// TODO Auto-generated destructor stub
}

