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
Queue QueueTest;

HighLevelComm::HighLevelComm(UART_HandleTypeDef& uart,TIM_HandleTypeDef& pwm) :
	myTxData_OK("OK\r\n"),
	myTxData_Battery("50\r\n"), //initial battery life is 50%
	myTxData_Distance("50\r\n"), //initial distance is 50mm
	uart(uart),
	pwm(pwm)
{
}
bool HighLevelComm::ReceiveMessage(uint8_t myRxData_9bits)
{
	if (uart.receiveMessage(&myRxData_9bits, sizeof(myRxData_9bits), 100) == true)
	{
		QueueTest.Buffer_Write(myRxData_9bits);
		return true;
	}else
		return false;
}
bool HighLevelComm::Move(int x)  //x means moving at x millimeter/second.
{
		if (strcmp((const char*)(QueueTest.Buffer_Read(&itemread)), "Move\n")) {	//"Move\n" means move forward
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

		if (strcmp((const char*)(QueueTest.Buffer_Read(&itemread)), "Stop\n")) {	//"Stop\n"
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
		if (strcmp((const char*)(QueueTest.Buffer_Read(&itemread)), "Distance\n")) {//"Distance\n" means getting the distance of the nearest obstacle information
			if (uart.sendMessage(myTxData_Distance, sizeof(myTxData_Distance), 100) == true) {
				//HAL_Delay(1000);
				//myTxData_Distance saves the data from the distance sensor.
				return true;
			}else
				return false;

		}else
			return false;
}


