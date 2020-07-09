/*
 * MotorSetting.cpp
 *
 *  Created on: 2020年7月9日
 *      Author: 59488
 */

#include <MotorSetting.h>
#include "ClassUartTest.h"
#include "PWM.h"
#include "string.h"
#include "main.h"

MotorSetting::MotorSetting()
{
	//int MaxSpeed=50;
}

bool MotorSetting::detectMove(int x)  //x means moving at x millimeter/second.
{
	ClassUartTest uartTest(huart2);
	PWM pwmTest(htim2);
	if (uartTest.receiveMessage(myRxData, sizeof(myRxData), 100) == true) {
		if (myRxData[0] == 'm') {	//'m' means "Move"
			HAL_Delay(100);
			if (pwmTest.setPWM(x / MaxSpeed)) {
				isRun = true;
				if (uartTest.sendMessage(myTxData_OK, sizeof(myTxData_OK), 100)== true) {
					return true;
				}else
					return false;
			}else
				return false;
		}else
			return false;

	}else
		return false;
}

bool MotorSetting::detectStop()
{
	ClassUartTest uartTest(huart2);
	PWM pwmTest(htim2);
	if (uartTest.receiveMessage(myRxData, sizeof(myRxData), 100) == true) {
		if (myRxData[0] == 's' && isRun==true) {	//'s' means "Stop"
			HAL_Delay(100);
			if (pwmTest.setPWM(0)) {
				isRun=false;
				if (uartTest.sendMessage(myTxData_OK, sizeof(myTxData_OK), 100)== true) {
					return true;

				}else
					return false;

			}else
				return false;
		}else
			return false;

	}else
		return false;
}

bool MotorSetting::detectTurn()
{
	ClassUartTest uartTest(huart2);
	if (uartTest.receiveMessage(myRxData, sizeof(myRxData), 100) == true) {
		if ((myRxData[0] == 't') && isRun ==true) {	//'s' means "Turn"
			HAL_Delay(100);
			if (setSteering(int x)) { //'x' means the angle of the steering system from -180 degrees to 180 degrees
				HAL_Delay(1000);
				if (uartTest.sendMessage(myTxData_OK, sizeof(myTxData_OK), 100)== true) {
					return true;
				}else
					return false;
			}else
				return false;
		}else
			return false;

	}else
		return false;
}

