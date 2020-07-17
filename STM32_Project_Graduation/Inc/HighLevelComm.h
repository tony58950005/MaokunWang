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
		HighLevelComm();
		bool Move(int x);
		bool Stop();
		bool Turn(int x);
		bool showBattery();
		bool showDistance();
		bool isRun=false;
		uint8_t myTxData_OK[5]= "OK\r\n";
		uint8_t myTxData_Battery[6]= "50\r\n"; //initial battery life is 50%
		uint8_t myTxData_Distance[6]= "50\r\n"; //initial distance is 50mm
		uint8_t myRxData_4bits[5];
		uint8_t myRxData_8bits[8];
		uint8_t myRxData_9bits[10];

	private:


};

#endif /* HIGHLEVELCOMM_H_ */


