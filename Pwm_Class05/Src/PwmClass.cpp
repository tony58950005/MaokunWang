/*
 * PwmTestClass.cpp
 *
 *  Created on: Mar. 22, 2020
 *      Author: 59488
 */
#include <PwmClass.h>
#include "main.h"
#include "stm32f4xx.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "cstdint"


PwmClass::PwmClass() {

	uint16_t ledpwmval=0;
	void setLedpwmval(uint16_t ledpwmval);


};

void PwmClass::setLedpwmval(uint16_t ledpwmval){
				TIM2->CCR1 = ledpwmval;
}

PwmClass::~PwmClass() {
	// TODO Auto-generated destructor stub
}



