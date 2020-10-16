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

PWM::PWM()
{
	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};

	__HAL_RCC_TIM10_CLK_ENABLE();
	htim.Instance = TIM10;

	if (HAL_TIM_Base_DeInit(&htim) != HAL_OK)
	{
		Error_Handler(PWMError);
	}

	htim.Init.Prescaler = 83;
	htim.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim.Init.Period = 20000;
	htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim.Init.RepetitionCounter = 0;
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

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 1500;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	if(HAL_TIM_PWM_ConfigChannel(&htim, &sConfigOC, TIM_CHANNEL_1)!=HAL_OK)
	{
		Error_Handler(PWMError);
	}

	if (HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_1)!=HAL_OK)
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
		//NowState=PWMError;
		return false;
	}
}

