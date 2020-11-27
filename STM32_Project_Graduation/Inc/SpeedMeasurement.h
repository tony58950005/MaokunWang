/*
 * SpeedMeasurement.h
 *
 *  Created on: 2020年11月2日
 *      Author: 59488
 */

#ifndef SPEEDMEASUREMENT_H_
#define SPEEDMEASUREMENT_H_
#include "main.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

class SpeedMeasurement {
public:
	SpeedMeasurement();
	uint32_t getDiffCount();
private:
	TIM_HandleTypeDef htim;
	uint32_t prevCounter;
};

#endif /* SPEEDMEASUREMENT_H_ */
