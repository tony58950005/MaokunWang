/*
 * ADC.cpp
 *
 *  Created on: 2020年9月18日
 *      Author: 59488
 */

#include <ADCClass.h>
#include "main.h"
#include "stm32f4xx_hal.h"

ADCClass::ADCClass()
{
	__HAL_RCC_ADC3_CLK_ENABLE();

	hadc.Instance = ADC3;
	hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	hadc.Init.Resolution = ADC_RESOLUTION_12B;
	hadc.Init.ScanConvMode = DISABLE;
	hadc.Init.ContinuousConvMode = DISABLE;
	hadc.Init.DiscontinuousConvMode = DISABLE;
	hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1;
	hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc.Init.NbrOfConversion = 1;
	hadc.Init.DMAContinuousRequests = DISABLE;
	hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	if (HAL_ADC_Init(&hadc) != HAL_OK) {
		Error_Handler(ADCError);
	}
}

float ADCClass::getAnalogValue(uint8_t sensorIndex)
{
	ADC_ChannelConfTypeDef myADCchannel;

	//Config selected channel
	myADCchannel.Rank = 1;
	myADCchannel.Offset = 0;
	myADCchannel.SamplingTime = ADC_SAMPLETIME_28CYCLES;
	switch (sensorIndex)
	{
		case 0:
			myADCchannel.Channel = ADC_CHANNEL_10;
			break;

		case 1:
			myADCchannel.Channel = ADC_CHANNEL_11;
			break;

		case 2:
			myADCchannel.Channel = ADC_CHANNEL_12;
			break;

		default:
			Error_Handler(ADCError);
			break;
	}
	HAL_ADC_ConfigChannel(&hadc, &myADCchannel);

	if (HAL_ADC_Start(&hadc) != HAL_OK)
	{
		Error_Handler(ADCError);
	}

	if (HAL_ADC_PollForConversion(&hadc, 100) != HAL_OK)
	{
		Error_Handler(ADCError);
	}

	uint32_t analogValue_voltage = HAL_ADC_GetValue(&hadc);
	float val = 3300.0f * analogValue_voltage / 4095;

	return val;
}
