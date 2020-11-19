/*
 * PWM.cpp
 *
 *  Created on: 2020. ápr. 16.
 *      Author: Nagy Ákos
 */

#include "PWM.h"
#include "main.h"
#include"stm32f4xx_hal_tim.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stdint.h"

PWM::PWM(TIM_TypeDef* timer, TIM_Base_InitTypeDef timerInit, TIM_OC_InitTypeDef ocInit, uint32_t Channel)
{
	TIM_ClockConfigTypeDef sClockSourceConfig = {0};

	htim.Instance = timer;
	if (HAL_TIM_Base_DeInit(&htim) != HAL_OK)
	{
		Error_Handler(PWMError);
	}

	htim.Init = timerInit;
	if (HAL_TIM_Base_Init(&htim) != HAL_OK)
	{
		Error_Handler(PWMError);
	}

	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler(PWMError);
	}

	if (HAL_TIM_PWM_Init(&htim) != HAL_OK)
	{
		Error_Handler(PWMError);
	}

	if(HAL_TIM_PWM_ConfigChannel(&htim, &ocInit, Channel)!=HAL_OK)
	{
		Error_Handler(PWMError);
	}

	if (HAL_TIM_PWM_Start(&htim, Channel)!=HAL_OK)
	{
		Error_Handler(PWMError);
	}
}

bool PWM::setPWM(float percent)
{
	if(percent <= 100)
	{
		uint32_t pulse = percent * htim.Init.Period / 100;
		__HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_1, pulse);
		return true;
	}else
	{
		Error_Handler(PWMError);
		return false;
	}
}

bool PWM::steeringServoInit()	//TODO: The PWM.cpp is a general PWM class, you put a specific instance here. Don't do that. You can create the servo PWM in the high level comm class.
{
	TIM_Base_InitTypeDef servoInit;
	servoInit.Prescaler = 83;
	servoInit.CounterMode = TIM_COUNTERMODE_UP;
	servoInit.Period = 20000;
	servoInit.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	servoInit.RepetitionCounter = 0;

	TIM_OC_InitTypeDef sConfigOC = {0};
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 1500;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	PWM servoPWM(TIM10, servoInit, sConfigOC, TIM_CHANNEL_1);

	//return servoPWM;
}

