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
		bool ParseMessage();
		bool Move(int x);
		bool Stop();
		bool Turn(int x);
		bool showBattery();
		bool showDistance();
		bool isRun=false;
	private:
		int x=50;
		char s2[10]="Move";
		char s3[10]="Turn";
		char s4[10]="Stop";
		char s5[10]="Battery";
		char s6[10]="Distance";
		uint8_t myRxData_9bits[8];
		//uint8_t *myRxData_9bits = new uint8_t[10];
		uint8_t myTxData_OK[5];
		uint8_t myTxData_Battery[6];
		uint8_t myTxData_Distance[6];
		uint8_t itemread;
		Queue receivedQueue;
		char receivedCommand[100];
		ClassUartTest uart;
		PWM pwm;
		int number;
		std::string str;
		std::string str_num;

};

#endif /* HIGHLEVELCOMM_H_ */
