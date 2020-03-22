/*
 * PwmTestClass.h
 *
 *  Created on: Mar. 22, 2020
 *      Author: 59488
 */

#ifndef PWMTESTCLASS_H_
#define PWMTESTCLASS_H_
#include "main.h"
#include "tim.h"
#include "gpio.h"
class PwmClass {

public:
	PwmClass();

	void setLedpwmval(uint16_t ledpwmval);
	//int getLedpwmval();
	virtual ~PwmClass();
};

#endif /* PWMTESTCLASS_H_ */
