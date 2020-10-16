/*
 * ADC.h
 *
 *  Created on: 2020年9月18日
 *      Author: 59488
 */

#ifndef ADC_H_
#define ADC_H_
//#include "stm32f4xx_hal_conf.h"
#include "main.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"


class ADCClass {
	public:
		ADCClass();
		float     getAnalogValue(uint8_t sensorIndex);
	private:
		ADC_HandleTypeDef hadc;
};

#endif /* ADC_H_ */
