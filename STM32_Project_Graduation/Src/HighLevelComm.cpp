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

		uint8_t myTxData_Battery[6]= "50\r\n"; //initial battery life is 50%
		uint8_t myTxData_Distance[6]= "50\r\n"; //initial distance is 50mm

HighLevelComm::HighLevelComm(UART_HandleTypeDef& uart,TIM_HandleTypeDef& pwm) :
	myTxData_OK("OK\r\n"),
	myTxData_Battery("50\r\n"), //initial battery life is 50%
	myTxData_Distance("50\r\n"), //initial distance is 50mm
	uart(uart),
	pwm(pwm)
{
}

bool HighLevelComm::Move(int x)  //x means moving at x millimeter/second.
{
	if (uart.receiveMessage(myRxData_4bits, sizeof(myRxData_4bits), 100) == true) {
		if (strcmp((const char*)myRxData_4bits, "Move\n")) {	//"Move\n" means move forward
			if (pwm.setPWM(x/MaxSpeed)) {
				isRun = true;
				if (uart.sendMessage(myTxData_OK, sizeof(myTxData_OK), 100)== true) {
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

	if (uart.receiveMessage(myRxData_4bits, sizeof(myRxData_4bits), 100) == true) {
		if (strcmp((const char*)myRxData_4bits, "Stop\n") && isRun==true) {	//"Stop\n"
			if (pwm.setPWM(0)) {
				isRun=false;
				if (uart.sendMessage(myTxData_OK, sizeof(myTxData_OK), 100)== true) {
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
	if (uart.receiveMessage(myRxData_4bits, sizeof(myRxData_4bits), 100) == true) {
		if (strcmp((const char*)myRxData_4bits, "Turn\n") && isRun ==true) {	//"Turn\n"
			//if (setSteering(x)) {//finish the turning
				if (uart.sendMessage(myTxData_OK, sizeof(myTxData_OK), 100)== true) {
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
	if (uart.receiveMessage(myRxData_8bits, sizeof(myRxData_8bits), 100) == true) {
		if (strcmp((const char*)(myRxData_8bits), "Battery\n")) { //"Battery\n" means getting the battery life information
			if (uart.sendMessage(myTxData_Battery, sizeof(myTxData_Battery), 100) == true) {
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
	if (uart.receiveMessage(myRxData_9bits, sizeof(myRxData_9bits), 100) == true) {
		if (strcmp((const char*)myRxData_9bits, "Distance\n")) {//"Distance\n" means getting the distance of the nearest obstacle information
			if (uart.sendMessage(myTxData_Distance, sizeof(myTxData_Distance), 100) == true) {
				//myTxData_Distance saves the data from the distance sensor.
				return true;
			}else
				return false;

		}else
			return false;

	}else
		return false;
}

