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
#include <iostream>




Queue QueueTest;
char s1[10];


HighLevelComm::HighLevelComm(UART_HandleTypeDef& uart,TIM_HandleTypeDef& pwm) :
	myTxData_OK("OK\r\n"),
	myTxData_Battery("50\r\n"), //initial battery life is 50%
	myTxData_Distance("50\r\n"), //initial distance is 50mm
	uart(uart),
	pwm(pwm)
{
}
bool HighLevelComm::ParseMessage()	//TODO-Akos: Rename this function to ParseMessage.
//Create a private class member variable from myRxData_9bits, and also check its type (currently it is one byte).
{
	bool arraysEqual1 = true;
	bool arraysEqual2 = true;
	bool arraysEqual3 = true;
	bool arraysEqual4 = true;
	bool arraysEqual5 = true;
	int count=0;
	if (uart.receiveMessage(myRxData_9bits, sizeof(myRxData_9bits), 1000) == true){
		HAL_Delay(500);
			for (int i = 0; i < sizeof(myRxData_9bits); i++) {
				if (myRxData_9bits[i] != '\\')
					QueueTest.Buffer_Write(myRxData_9bits[i]);
			}
			int i = 0;
			while (QueueTest.Buffer_Read(&itemread)) {
				s1[i] = itemread;
				i++;
			}
			//memcpy(s1[i], itemread,1);
	}


	while (count < sizeof(myRxData_9bits))
	{
		if (s2[count] != s1[count]){
	        arraysEqual1 = false;
		}
		if (s3[count] != s1[count]){
			arraysEqual2 = false;
		}
		if (s4[count] != s1[count]){
			arraysEqual3 = false;
		}
		if (s5[count] != s1[count]){
			arraysEqual4 = false;
		}
		if (s6[count] != s1[count]){
			arraysEqual5 = false;
		}
		count++;
	}
	if (arraysEqual1) {
		if(Move(x)){
			memset(s1,0,10);
		}
	}else if (arraysEqual2) {
		if(Turn(x)){
			memset(s1,0,10);
		}
	}else if (arraysEqual3) {
		if(Stop()){
			memset(s1,0,10);
		}
	}else if (arraysEqual4) {
		if(showBattery()){
			memset(s1,0,10);
		}
	}else if (arraysEqual5) {
		if(showDistance()){
			memset(s1,0,10);
		}
	}else
	{
		memset(s1,0,10);
	}

}
bool HighLevelComm::Move(int x)  //x means moving at x millimeter/second.
{		//TODO-Akos: In this format, your code is not ok. Buffer read only reads one character,
	//it will never gives you a complete string. And you should push it back (or don't remove from the queue), when it is not "Move\n".
		//"Move\n" means move forward
	if (pwm.setPWM(x / MaxSpeed)) {
		isRun = true;
		if (uart.sendMessage(myTxData_OK, sizeof(myTxData_OK), 100) == true) {
			return true;
		} else
			return false;
	} else
		return false;
}

bool HighLevelComm::Stop()
{
	if (isRun == true) {	//"Stop\n"
		if (pwm.setPWM(0)) {
			isRun = false;
			if (uart.sendMessage(myTxData_OK, sizeof(myTxData_OK), 100)
					== true) {
				return true;
			} else
				return false;
		} else
			return false;
	} else
		return false;

}

bool HighLevelComm::Turn(int x) //'x' means the angle of the steering system from -180 degrees to 180 degrees
{
	if (isRun == true) {	//"Turn\n"
		//if (setSteering(x)) {//finish the turning
		if (uart.sendMessage(myTxData_OK, sizeof(myTxData_OK), 100) == true) {
			return true;
		} else
			return false;
		//}else
		//return false;
	} else
		return false;

}

bool HighLevelComm::showBattery()
{
	//"Battery\n" means getting the battery life information
	if (uart.sendMessage(myTxData_Battery, sizeof(myTxData_Battery), 100)== true) {
		//myTxData_Battery saves the data from the battery sensor about its battery life.
		return true;
	} else
		return false;
}

bool HighLevelComm::showDistance()
 {
	//if (isRun == true) {//"Distance\n" means getting the distance of the nearest obstacle information
		if (uart.sendMessage(myTxData_Distance, sizeof(myTxData_Distance), 100)== true) {
			//myTxData_Distance saves the data from the distance sensor.
			return true;
		} else
			return false;
	//} else
		//return false;
}


