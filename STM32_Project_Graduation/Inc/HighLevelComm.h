/*
 * HighLevelComm.h
 *
 *  Created on: 2020年7月14日
 *      Author: 59488
 */

#ifndef HIGHLEVELCOMM_H_
#define HIGHLEVELCOMM_H_

#include "ClassUartTest.h"
#include "PWM.h"
#include "main.h"
#define MaxSpeed	(100)

class HighLevelComm {
public:
		HighLevelComm(UART_HandleTypeDef& uart, TIM_HandleTypeDef& pwm);
		bool Move(int x);
		bool Stop();
		bool Turn(int x);
		bool showBattery();
		bool showDistance();
		bool isRun=false;
	private:
		uint8_t myRxData_4bits[5];
		uint8_t myRxData_8bits[8];
		uint8_t myRxData_9bits[10];
		uint8_t myTxData_OK[5];
		uint8_t myTxData_Battery[10];
		uint8_t myTxData_Distance[10];
		ClassUartTest uart;
		PWM pwm;
};

#endif /* HIGHLEVELCOMM_H_ */


