/*
 * MotorSetting.h
 *
 *  Created on: 2020年7月9日
 *      Author: 59488
 */

#ifndef MOTORSETTING_H_
#define MOTORSETTING_H_

#include "ClassUartTest.h"
#include "PWM.h"
#include "string.h"
#include "main.h"

class MotorSetting {
	public:
		MotorSetting();
		bool detectMove(int x);
		bool detectStop();
		bool detectTurn();
		bool isRun=false;
		uint8_t myTxData[15]="Hello World\r\n";
		uint8_t myTxData_OK[5]= "OK\r\n";
		uint8_t myTxData_Battery[6]= "50\r\n"; //initial battery life is 50%
		uint8_t myTxData_Distance[6]= "50\r\n"; //initial distance is 50mm
		uint8_t myRxData[1];

	private:
		UART_HandleTypeDef huart2;
		TIM_HandleTypeDef htim2;


};

#endif /* MOTORSETTING_H_ */
