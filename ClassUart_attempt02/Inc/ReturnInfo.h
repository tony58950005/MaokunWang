/*
 * ReturnInfo.h
 *
 *  Created on: 2020年7月9日
 *      Author: 59488
 */

#ifndef RETURNINFO_H_
#define RETURNINFO_H_

#include "ClassUartTest.h"
#include "string.h"
#include "main.h"

class ReturnInfo {
	public:
		bool showBattery();
		bool showDistance();
		uint8_t myTxData[15]="Hello World\r\n";
		uint8_t myTxData_OK[5]= "OK\r\n";
		uint8_t myTxData_Battery[6]= "50\r\n"; //initial battery life is 50%
		uint8_t myTxData_Distance[6]= "50\r\n"; //initial distance is 50mm
		uint8_t myRxData[1];

	private:
		UART_HandleTypeDef huart2;
		TIM_HandleTypeDef htim2;
};

#endif /* RETURNINFO_H_ */
