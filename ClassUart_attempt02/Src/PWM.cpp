/*
 * PWM.cpp
 *
 *  Created on: 2020. ápr. 16.
 *      Author: Nagy Ákos
 */

#include "PWM.h"
#include "main.h"

PWM::PWM(TIM_HandleTypeDef htim)
{
	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};

	htim.Instance = TIM2;
	htim.Init.Prescaler = 84;
	htim.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim.Init.Period = 1000;
	htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim) != HAL_OK)
	{
		Error_Handler();
	}

	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}

	if (HAL_TIM_PWM_Init(&htim) != HAL_OK)
	{
		Error_Handler();
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}

	//TODO: Initialize the PWM channel using HAL_TIM_PWM_ConfigChannel function and the variable sConfigOC.
}

bool PWM::setPWM(uint8_t percent)
{
	//TODO: Implement this task using a HAL function
}
