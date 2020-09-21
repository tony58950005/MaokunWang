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

ADCClass::ADCClass(ADC_HandleTypeDef h):
    hadc1(h)
{
	//ADC_CommonInitTypeDef ADC_CommonInitStructure;
	 ADC_ChannelConfTypeDef sConfig;
	if (HAL_ADC_Init(&hadc1) != HAL_OK)
	{
		Error_Handler();
	}

	  //hadc1.ADC_Mode = ADC_Mode_Independent;
	  hadc1.Instance = ADC1;
	  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	  hadc1.Init.ScanConvMode = ENABLE;
	  hadc1.Init.ContinuousConvMode =ENABLE;
	  hadc1.Init.DiscontinuousConvMode = DISABLE;
	  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	  hadc1.Init.NbrOfConversion = 3;
	  hadc1.Init.DMAContinuousRequests = DISABLE;
	  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	  if (HAL_ADC_Init(&hadc1) != HAL_OK)
	  {
	    Error_Handler();
	  }

	  /**Configure for the selected ADC regular channel to be converted.
	  */
	  sConfig.Channel = ADC_CHANNEL_6;
	  sConfig.Rank = 6;
	  sConfig.SamplingTime = ADC_SAMPLETIME_144CYCLES;
	  HAL_ADC_ConfigChannel(&hadc1, &sConfig);
	  sConfig.Channel = ADC_CHANNEL_7;
	  HAL_ADC_ConfigChannel(&hadc1, &sConfig);
	  sConfig.Channel = ADC_CHANNEL_9;
	  HAL_ADC_ConfigChannel(&hadc1, &sConfig);
	 /* ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_480Cycles );
	  ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_480Cycles );
	  ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 3, ADC_SampleTime_480Cycles );*/

	 // ADC_DMACmd(ADC1, ENABLE);
	    /* Enable ADC1 */
	 // ADC_Cmd(ADC1, ENABLE);
	     /* Enable ADC1 reset calibaration register */
	 // ADC_ResetCalibration(ADC1);
	    /* Start ADC1 calibaration */
	 // ADC_StartCalibration(ADC1);
	    /* Check the end of ADC1 calibration */
	 // while(ADC_GetCalibrationStatus(ADC1));
	  if (HAL_ADC_ConfigChannel(&hadc1, &ADC1) != HAL_OK)
	  {
	  	    Error_Handler();
	  }
}



