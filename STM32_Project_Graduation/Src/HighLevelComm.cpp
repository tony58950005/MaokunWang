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



Queue QueueTest;

HighLevelComm::HighLevelComm(UART_HandleTypeDef& uart,TIM_HandleTypeDef& pwm) :
	myTxData_OK("OK\r\n"),
	myTxData_Battery("50\r\n"), //initial battery life is 50%
	myTxData_Distance("50\r\n"), //initial distance is 50mm
	uart(uart),
	pwm(pwm)
{
}
bool HighLevelComm::ReceiveMessage(uint8_t myRxData_9bits)	//TODO-Akos: Rename this function to ParseMessage. Create a private class member variable from myRxData_9bits, and also check its type (currently it is one byte).
{
	if (uart.receiveMessage(&myRxData_9bits, sizeof(myRxData_9bits), 100) == true)
	{
		HAL_Delay(100);	//TODO-Akos: Why are you waiting 100 ms here?
		QueueTest.Buffer_Write(myRxData_9bits);
		//TODO-Akos: Call the other class functions (Move, Stop, etc.) from here
		return true;
	}else
		return false;
}
bool HighLevelComm::Move(int x)  //x means moving at x millimeter/second.
{		//TODO-Akos: In this format, your code is not ok. Buffer read only reads one character, it will never gives you a complete string. And you should push it back (or don't remove from the queue), when it is not "Move\n".
		if (strcmp((const char*)(QueueTest.Buffer_Read(&itemread)), "Move\n")) {	//"Move\n" means move forward
			HAL_Delay(1000);
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
}

bool HighLevelComm::Stop()
{

		if (strcmp((const char*)(QueueTest.Buffer_Read(&itemread)), "Stop\n") && isRun==true) {	//"Stop\n"
			HAL_Delay(1000);
			if (pwm.setPWM(0)) {
				isRun=false;
				//HAL_Delay(1000);
				if (uart.sendMessage(myTxData_OK, sizeof(myTxData_OK), 100)== true) {

					return true;

				}else
					return false;

			}else
				return false;
		}else
			return false;

}

bool HighLevelComm::Turn(int x) //'x' means the angle of the steering system from -180 degrees to 180 degrees
{
		if (strcmp((const char*)(QueueTest.Buffer_Read(&itemread)), "Turn\n") && isRun ==true) {	//"Turn\n"
			HAL_Delay(1000);
			//if (setSteering(x)) {//finish the turning
				if (uart.sendMessage(myTxData_OK, sizeof(myTxData_OK), 100)== true) {
					return true;
				}else
					return false;
			//}else
				//return false;
		}else
			return false;

}

bool HighLevelComm::showBattery()
{
		if (strcmp((const char*)(QueueTest.Buffer_Read(&itemread)), "Battery\n")) { //"Battery\n" means getting the battery life information
			HAL_Delay(1000);
			if (uart.sendMessage(myTxData_Battery, sizeof(myTxData_Battery), 100) == true) {
				//myTxData_Battery saves the data from the battery sensor about its battery life.
				return true;
			}else
				return false;

		}else
			return false;

}

bool HighLevelComm::showDistance()
{
		if (strcmp((const char*)(QueueTest.Buffer_Read(&itemread)), "Distance\n") && isRun==true) {//"Distance\n" means getting the distance of the nearest obstacle information
			HAL_Delay(1000);
			if (uart.sendMessage(myTxData_Distance, sizeof(myTxData_Distance), 100) == true) {
				//HAL_Delay(1000);
				//myTxData_Distance saves the data from the distance sensor.
				return true;
			}else
				return false;

		}else
			return false;
}


