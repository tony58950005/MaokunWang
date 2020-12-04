/*
 * HighLevelComm.cpp
 *
 *  Created on: 2020年7月14日
 *      Author: 59488
 */

#include "HighLevelComm.h"
#include "ClassUartTest.h"
#include "ADCClass.h"
#include "PIDController.h"
#include "SpeedMeasurement.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f407xx.h"
#include "PWM.h"
#include "string.h"
#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>

HighLevelComm::HighLevelComm(UART_HandleTypeDef& uart, PWM servoPWM, PWM motorPWM1, PWM motorPWM2):
	myTxData_OK("OK\r\n"),
	myTxData_Battery("-1"),
	myTxData_Distance("-1"),
	uart(uart),
	servoPWM(servoPWM),
	motor(1.0, 0.0, 0.0, motorPWM1, motorPWM2)
{
}

bool HighLevelComm::ParseMessage()
{
	uint8_t myRxData_1byte;
	int32_t receivedNumber;
	memset(receivedCommand,0,100);

	if (!uart.receiveMessage(&myRxData_1byte, sizeof(myRxData_1byte), 100)){
		return false;
	}

	if (myRxData_1byte != '\n')	//Store character, if it is not '\n'
	{
		if (myRxData_1byte != '\r')
			receivedQueue.Buffer_Write(myRxData_1byte);
		return false;
	}

	//receivedQueue.Buffer_Write('\0');
	//Parse received line
	size_t j=0;
	while (receivedQueue.Buffer_Read((uint8_t*)(receivedCommand + j)) && j < sizeof(receivedCommand)) {
		j++;
	}

	if (j == sizeof(receivedCommand))	//Check receivedCommand length
		return false;

	if (strstr(receivedCommand, "Stop") != NULL){
		Stop();
	}else if (strstr(receivedCommand, "Battery") != NULL){
		showBattery();
	}else if (strstr(receivedCommand, "Distance") != NULL){
		showDistance();
	}else if (sscanf(receivedCommand,"Move,%ld", &receivedNumber) == 1){
		Move(receivedNumber);
	}else if (sscanf(receivedCommand,"Turn,%ld", &receivedNumber) == 1){
		Turn(receivedNumber);
	}else if (sscanf(receivedCommand,"Delay,%ld", &receivedNumber) == 1){//Delay unit:milliseconds
		Delay(receivedNumber);
	}else{
		return false;
	}

	return true;
}
bool HighLevelComm::Move(int x)  //x means moving at x millimeter/second.
{
	if(!getMotorSpeed()){
		Error_Handler(GetMotorSpeedError);
		uart.sendMessage(ErrorInfo,sizeof(ErrorInfo),100);
	}
	if (controlSpeed(motor, x, realSpeed)) {
		isRun = true;
		if (uart.sendMessage(myTxData_OK, sizeof(myTxData_OK), 100) == true) {
			return true;
		} else {
			Error_Handler(UartError);
			uart.sendMessage(ErrorInfo,sizeof(ErrorInfo),100);
			return false;
		}
	} else{
		//TODO: put the sendMessage fcn in the Error_Handler
		//TODO: send back some error message over uart
		Error_Handler(ControlSpeedError);
		uart.sendMessage(ErrorInfo,sizeof(ErrorInfo),100);
		return false;
	}
}

bool HighLevelComm::Stop()
{
	if (uart.sendMessage(myTxData_OK, sizeof(myTxData_OK), 100) == true) {
		if (isRun == true) {	//"Stop\n"
			motor.PIDController_Stop();
			return true;
		} else {
			return false;
		}
	} else {
		Error_Handler(UartError);
		uart.sendMessage(ErrorInfo,sizeof(ErrorInfo),100);
		return false;
	}
}

bool HighLevelComm::Turn(int x) //'x' means the angle of the steering system from -45 degrees to 45 degrees
{
	//TODO: Call this init function in the ctor once
	//servoPWM.steeringServoInit();
	if (setSteering(servoPWM, x)) {	//finish the turning
		if (uart.sendMessage(myTxData_OK, sizeof(myTxData_OK), 100) == true) {
			return true;
		} else {
			Error_Handler(UartError);
			uart.sendMessage(ErrorInfo,sizeof(ErrorInfo),100);
			return false;
		}
	} else{
		//TODO: send back some error message over uart
		Error_Handler(SteeringError);
		uart.sendMessage(ErrorInfo,sizeof(ErrorInfo),100);
		return false;
	}

}

bool HighLevelComm::showBattery()
{
	//"Battery\n" means getting the battery life information
	//myTxData_Battery saves the data from the battery sensor about its battery life.
	if (uart.sendMessage(myTxData_Battery, sizeof(myTxData_Battery), 100)== true) {
		return true;
	} else
	{
		//TODO: send back some error message over uart
		Error_Handler(UartError);
		uart.sendMessage(ErrorInfo,sizeof(ErrorInfo),100);
		return false;
	}
}

bool HighLevelComm::showDistance()
{
	//"Distance\n" means getting the distance of the nearest obstacle information
	//myTxData_Distance saves the data from the distance sensor.
	if(!measureDistance()){
//
	}
	snprintf(myTxData_Distance, sizeof(myTxData_Distance),"%f:%f:%f\r\n", distanceL, distanceM, distanceR);

	if (uart.sendMessage((uint8_t*)myTxData_Distance, sizeof(myTxData_Distance), 100)== true) {
		return true;
	} else
	{
		//TODO: send back some error message over uart
		Error_Handler(UartError);
		uart.sendMessage(ErrorInfo,sizeof(ErrorInfo),100);
		return false;
	}
}

bool HighLevelComm::Delay(int x) //Delay unit: milliseconds
{
	HAL_Delay(x);

	if (uart.sendMessage(myTxData_OK, sizeof(myTxData_OK), 100) == true) {
		return true;
	} else {
		Error_Handler(UartError);
		uart.sendMessage(ErrorInfo,sizeof(ErrorInfo),100);
		return false;
	}
}

bool HighLevelComm::setSteering(PWM& servoPWM, float steeringAngle)
{
	//presuming the do-able steeringAngle ranges from -45 (PWM->5%) to 45(PWM->10%) degrees.
	//the characteristic line (saturated steeringAgnle, PWM high level line[1.5ms, 2.5ms])
	//goes through point (45, 10[%]),(-45, 5[%])
	float percent=1.0f/18.0f*steeringAngle + 135.0f/18.0f;
	if(servoPWM.setPWM(percent)==false){
		Error_Handler(PWMError);
		uart.sendMessage(ErrorInfo,sizeof(ErrorInfo),100);
		return false;
	}
	return true;
}

bool HighLevelComm::controlSpeed(PID_Controller& motor, float referenceSpeed, float actualSpeed)
{
	//PID for speed control
	motor.PIDController_Update(referenceSpeed, actualSpeed);
	return true;
}

bool HighLevelComm::getMotorSpeed()
{
	//TODO: we have only one speed measurement for the whole car, we don't have the speed of the wheels

	//5ms speed measurement, one time unit is 5ms
	WheelEncoderNow = motorSpeed.getDiffCount();
	//rightWheelEncoderNow+= motorSpeed.getTIMx_DeltaCnt(0);//(TIM2->CCR2);

	 //speed measurement for every 5ms
	realSpeed   = (WheelEncoderNow - WheelEncoderLast)*1000*200*2*3.14*0.003/1000;//modify the last number "1000"->"xxxx"
	//realRightSpeed  = (rightWheelEncoderNow - rightWheelEncoderLast)*1000*200*2*3.14*0.003/1000;

	//record the last time encoder value
	WheelEncoderLast  = WheelEncoderNow;
	//rightWheelEncoderLast = rightWheelEncoderNow;
	return true;
}

bool HighLevelComm::measureDistance()
{
	//Measure the signals of the Sharp sensors
	float sensorsVoltage[3];
	for (int i = 0; i < 3; i++) {
		sensorsVoltage[i] = adc.getAnalogValue(i) / 1000.0f;
	}

	//Convert the voltage[V] to distance[cm] using the characteristics of the sensor
	//Sensor measuring distance (4cm-30cm)
	//the slope1[4cm-6cm] has little difference with the slope2[6cm-30cm]
	float distance[3];
	for (int i = 0; i < 3; i++) {
		if (sensorsVoltage[i] >= 2.0 && sensorsVoltage[i] <= 3.0) {
			distance[i] = 8.55 / (sensorsVoltage[i] - 0.5925); //distance->[4cm,6cm]
		} else if (sensorsVoltage[i] >= 0.41) {
			distance[i] = 13.156 / (sensorsVoltage[i] + 0.0289); //distance->[6cm,30cm]
		} else {
			distance[i] = infinityf(); //the distance here does not make sense.
		}
	}

	distanceL = distance[0];
	distanceM = distance[1];
	distanceR = distance[2];
	return true;
}

