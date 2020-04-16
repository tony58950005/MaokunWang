#ifndef PWM_H_
#define PWM_H_

#include "stm32f4xx_hal.h"

#ifdef __cplusplus
class PWM
{
	public:
				PWM(TIM_HandleTypeDef huart);
		bool 	setPWM(uint8_t percent);
	private:
		TIM_HandleTypeDef htim;
};
#endif
#endif /* PWM_H_ */
