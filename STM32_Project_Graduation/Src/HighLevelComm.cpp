/*
 * HighLevelComm.cpp
 *
 *  Created on: 2020年7月14日
 *      Author: 59488
 */

#include <HighLevelComm.h>


#include "ClassUartTest.h"
#include "PWM.h"
#include "string.h"
#include "main.h"

HighLevelComm::HighLevelComm() {
//nothing
}
TIM_HandleTypeDef htim2;
ClassUartTest uartTest(huart2);
PWM pwmTest(htim2);

bool HighLevelComm::Move(int x)  //x means moving at x millimeter/second.
{
	if (uartTest.receiveMessage(myRxData_4bits, sizeof(myRxData_4bits), 100) == true) {
		if ((const char*)myRxData_4bits == "Move\n") {	//"Move\n" means move forward
			HAL_Delay(100);
			if (pwmTest.setPWM(x/MaxSpeed)) {
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

bool HighLevelComm::Stop()
{

	PWM pwmTest(htim2);
	if (uartTest.receiveMessage(myRxData_4bits, sizeof(myRxData_4bits), 100) == true) {
		if ((const char*)myRxData_4bits == "Stop\n" && isRun==true) {	//"Stop\n"
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

bool HighLevelComm::Turn(int x) //'x' means the angle of the steering system from -180 degrees to 180 degrees
{
	if (uartTest.receiveMessage(myRxData_4bits, sizeof(myRxData_4bits), 100) == true) {
		if (((const char*)myRxData_4bits == "Turn\n") && isRun ==true) {	//"Turn\n"
			HAL_Delay(100);
			//if (setSteering(x)) {//finish the turning
				if (uartTest.sendMessage(myTxData_OK, sizeof(myTxData_OK), 100)== true) {
					return true;
				}else
					return false;
			//}else
				//return false;
		}else
			return false;

	}else
		return false;
}

bool HighLevelComm::showBattery()
{
	if (uartTest.receiveMessage(myRxData_8bits, sizeof(myRxData_8bits), 100) == true) {
		if ((const char*)(myRxData_8bits) == "Battery\n") { //"Battery\n" means getting the battery life information
			HAL_Delay(100);
			if (uartTest.sendMessage(myTxData_Battery, sizeof(myTxData_Battery), 100) == true) {
				//myTxData_Battery saves the data from the battery sensor about its battery life.
				return true;
			}else
				return false;

		}else
			return false;

	}else
		return false;
}

bool HighLevelComm::showDistance()
{
	if (uartTest.receiveMessage(myRxData_9bits, sizeof(myRxData_9bits), 100) == true) {
		if ((const char*)myRxData_9bits == "Distance\n") {//"Distance\n" means getting the distance of the nearest obstacle information
			HAL_Delay(100);
			if (uartTest.sendMessage(myTxData_Distance, sizeof(myTxData_Distance), 100) == true) {
				//myTxData_Distance saves the data from the distance sensor.
				return true;
			}else
				return false;

		}else
			return false;

	}else
		return false;
}

