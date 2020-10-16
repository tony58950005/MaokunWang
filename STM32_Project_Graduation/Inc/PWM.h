/*
 * PWM.h
 *
 *  Created on: 2020年4月17日
 *      Author: 59488
 */

#ifndef PWM_H_
#define PWM_H_
#include "string.h"
#include <ErrorState.h>
#include "main.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"

#ifdef __cplusplus
class PWM {
public:
	PWM();
	bool setPWM(float percent);
private:
	TIM_HandleTypeDef htim;

};
#endif
#endif /* PWM_H_ */
