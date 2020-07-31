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
std::string s1;


HighLevelComm::HighLevelComm(UART_HandleTypeDef& uart,TIM_HandleTypeDef& pwm) :
	myTxData_OK("OK\r\n"),
	myTxData_Battery("50\r\n"), //initial battery life is 50%
	myTxData_Distance("50\r\n"), //initial distance is 50mm
	uart(uart),
	pwm(pwm)
{
}
bool HighLevelComm::ParseMessage()	//TODO-Akos: Rename this function to ParseMessage. Create a private class member variable from myRxData_9bits, and also check its type (currently it is one byte).
{
	if (uart.receiveMessage(myRxData_9bits, sizeof(myRxData_9bits), 100) == true){
	 for(int i=0; i<sizeof(myRxData_9bits); i++)
	 {
		 if(myRxData_9bits[i]!='\0')
			 QueueTest.Buffer_Write(myRxData_9bits[i]);
		 else
			 break;
	 }
	 while(QueueTest.Buffer_Read(&itemread))
	 {

	 		s1=s1+(char)itemread;
	 }
	 return true;
	}

	if (s2.compare(s1)==0) {Move(x);s1={'\0'};}
	if (s3.compare(s1)==0) {Stop();s1={'\0'};}
	if (s4.compare(s1)==0) {Turn(x);s1={'\0'};}
	if (s5.compare(s1)==0) {showBattery();s1={'\0'};}
	if (s6.compare(s1)==0) {showDistance();s1={'\0'};}

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
	if (isRun == true) {//"Distance\n" means getting the distance of the nearest obstacle information
		if (uart.sendMessage(myTxData_Distance, sizeof(myTxData_Distance), 100)== true) {
			//myTxData_Distance saves the data from the distance sensor.
			return true;
		} else
			return false;

	} else
		return false;
}


