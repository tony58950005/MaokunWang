/*
 * SpeedMeasurement.cpp
 *
 *  Created on: 2020年11月2日
 *      Author: 59488
 */

#include <SpeedMeasurement.h>
#include "main.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
SpeedMeasurement::SpeedMeasurement()
{
	TIM_Encoder_InitTypeDef sConfig = {0};

	__HAL_RCC_TIM2_CLK_ENABLE();

	htim.Instance = TIM2;
	htim.Init.Prescaler = 0x0;
	htim.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim.Init.Period = 0xFFFFFFFF;
	htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim.Init.RepetitionCounter = 0;

	if (HAL_TIM_Base_Init(&htim) != HAL_OK)
	{
		Error_Handler(SpeedMeasurementError);
	}

	sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
	sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
	sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
	sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
	sConfig.IC1Filter = 0;
	sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
	sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
	sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
	sConfig.IC2Filter = 0;
	if (HAL_TIM_Encoder_Init(&htim, &sConfig) != HAL_OK)
	{
		Error_Handler(SpeedMeasurementError);
	}

	HAL_TIM_Encoder_Start(&htim, TIM_CHANNEL_ALL);

	prevCounter = 0;
}

uint32_t SpeedMeasurement::getDiffCount()
{
	int32_t current = __HAL_TIM_GET_COUNTER(&htim);
	int32_t diff = current - prevCounter;
	prevCounter = current;
	return diff;
}


/*function: calculate the speed of rotation
 * input param: uint8_t *LeftSpeed, uint8_t *rightSpeed
 * return: void
 * calculate the linear speed of the rotation, positive/negative, speed=value*1000(unit: mm/s)
 * the changed value of the encoder(converted into distance in straight line) * 200s(5ms for one count),
 * and get m/s*1000 converted into integers
 * the number of duty cycle for one rotation
 * left: ???? e.g. 1000
 * right: ???? e.g. 1000
 * the radius of the wheel: e.g. 0.003m
 * the perimeter:2*pi*r
 * the distance for one duty cycle
 * 	left:2*pi*0.003/1000
 * 	right:2*pi*0.003/1000
 *
 */


