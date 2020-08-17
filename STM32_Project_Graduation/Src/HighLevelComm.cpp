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
#include <stdlib.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <iostream>



HighLevelComm::HighLevelComm(UART_HandleTypeDef& uart,TIM_HandleTypeDef& pwm) :
	myTxData_OK("OK\r\n"),
	myTxData_Battery("50\r\n"), //initial battery life is 50%
	myTxData_Distance("30\r\n"), //initial distance is 50mm
	uart(uart),
	pwm(pwm)
{
}
bool HighLevelComm::ParseMessage()
{

	uint8_t myRxData_1byte=0;
	char receivedNumber[1];
	if (!uart.receiveMessage(&myRxData_1byte, sizeof(myRxData_1byte), 100))
		return false;

	if (myRxData_1byte != '\n')	//Store character, if it is not '\n'
	{
		receivedQueue.Buffer_Write(myRxData_1byte);
		return false;
	}

	//Parse received line
	size_t j=0;
	while (receivedQueue.Buffer_Read((uint8_t*)(receivedCommand + j)) && j < sizeof(receivedCommand)) {
		j++;
	}

	if (j == sizeof(receivedCommand))	//Check receivedCommand length
		return false;

	//TODO-Akos: You get the received line in receivedCommand, parse the line using strstr and sscanf. I give you an example:
	if (strstr(receivedCommand, "Stop") != NULL){
		Stop();
	}else if (strstr(receivedCommand, "Battery") != NULL){
		showBattery();
	}else if (strstr(receivedCommand, "Distance") != NULL){
		showDistance();
	}else if (strstr(receivedCommand, "Move") != NULL){
		sscanf(receivedCommand,"%*4s%*c%d", &receivedNumber);
		//sscanf(receivedCommand,"%*[A-Z]%*[a-z]%*1c%d", &receivedNumber);
	    //sscanf(receivedCommand,"%*4s%*[,]%d",&receivedNumber);
	    /*for(int i=sizeof(receivedNumber);i>0;i--){
	    	realNumber=realNumber+((int)receivedNumber[i-1]-48)*pow(10,(sizeof(receivedNumber)-i));
	    }*/
		//realNumber=((int)(receivedNumber[0])-48)*10+((int)(receivedNumber[1]-48));
		Move(receivedNumber[0]);
	}else if (strstr(receivedCommand, "Turn") != NULL){
		sscanf(receivedCommand,"%*4s%*1c%d",&receivedNumber);
		Turn(receivedNumber[0]);
	}else{
		return false;
	}

	return true;
}
bool HighLevelComm::Move(int x)  //x means moving at x millimeter/second.
{
	if (pwm.setPWM(x / MaxSpeed)) {
		isRun = true;
		if(x==100){
			if (uart.sendMessage(myTxData_OK, sizeof(myTxData_OK), 100) == true) {
				return true;
			} else
				return false;
		}
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
