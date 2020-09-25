/*
 * ADC.cpp
 *
 *  Created on: 2020年9月18日
 *      Author: 59488
 */

#include <ADCClass.h>
#include "main.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f446xx.h"

ADCClass::ADCClass(ADC_HandleTypeDef h) :
	hadc1(h)
{
	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	hadc1.Init.ScanConvMode = ENABLE;
	hadc1.Init.ContinuousConvMode = ENABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 3;
	hadc1.Init.DMAContinuousRequests = DISABLE;
	hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
	if (HAL_ADC_Init(&hadc1) != HAL_OK) {
		Error_Handler();
	}
	/**Configure for the selected ADC regular channel to be converted.
	 */

	myADCchannel.Channel = ADC_CHANNEL_10;
	myADCchannel.Rank = 1;
	myADCchannel.SamplingTime = ADC_SAMPLETIME_144CYCLES;
	HAL_ADC_ConfigChannel(&hadc1, &myADCchannel);

	myADCchannel.Channel = ADC_CHANNEL_11;
	myADCchannel.Rank = 2;
	myADCchannel.SamplingTime = ADC_SAMPLETIME_144CYCLES;
	HAL_ADC_ConfigChannel(&hadc1, &myADCchannel);

	myADCchannel.Channel = ADC_CHANNEL_12;
	myADCchannel.Rank = 3;
	myADCchannel.SamplingTime = ADC_SAMPLETIME_144CYCLES;
	HAL_ADC_ConfigChannel(&hadc1, &myADCchannel);
}

//TODO: Create a function, which returns back the measures voltages
