/*
 * HighLevelComm.h
 *
 *  Created on: 2020年7月14日
 *      Author: 59488
 */

#ifndef HIGHLEVELCOMM_H_
#define HIGHLEVELCOMM_H_

#include "ClassUartTest.h"
#include "Queue.h"
#include "string.h"
#include "PWM.h"
#include "main.h"
#include <iostream>
#define MaxSpeed	(100)


class HighLevelComm {
public:
		HighLevelComm(UART_HandleTypeDef& uart, TIM_HandleTypeDef& pwm);
		bool ParseMessage(uint8_t message[]);
		bool Move(int x);
		bool Stop();
		bool Turn(int x);
		bool showBattery();
		bool showDistance();
		bool isRun=false;
	private:
		//uint8_t myRxData_4bits[4];
		//uint8_t myRxData_8bits[8];
		int x;
		std::string s2="Move";
		std::string s3="Turn";
		std::string s4="Stop";
		std::string s5="Battery";
		std::string s6="Distance";
		uint8_t myRxData_9bits[9];
		uint8_t myTxData_OK[5];
		uint8_t myTxData_Battery[6];
		uint8_t myTxData_Distance[6];
		uint8_t itemread;
		ClassUartTest uart;
		PWM pwm;
};

#endif /* HIGHLEVELCOMM_H_ */

