/*
 * PIDController.cpp
 *
 *  Created on: 2020年10月2日
 *      Author: 59488
 */

#include <PIDController.h>
#include "main.h"
PID_Controller::PID_Controller(float Kp, float Ki, float Kd, PWM motorPWM1, PWM motorPWM2) :
	Kp(Kp),
	Ki(Ki),
	Kd(Kd),
	limit(100),
	motorPWM1(motorPWM1),
	motorPWM2(motorPWM2)
{
	integrator = 0.0f;
	prevError = 0.0f;

	setSpeed(0.0f);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
}

/*
 * Speed: -limit < speed < limit
 */
void PID_Controller::setSpeed(float speed)
{
	if (speed > limit)
		speed = limit;
	else if (speed < -limit)
		speed = -limit;

	motorPWM1.setPWM(50.0f + speed * 0.5f * 100.0f / limit);
	motorPWM1.setPWM(50.0f - speed * 0.5f * 100.0f / limit);
}


void PID_Controller::PIDController_Update(float setpoint, float measurement){
	//error signal
	float error = setpoint - measurement;

	//proportional
	float proportional = Kp * error;

	//derivative
	float differentiator = Kd * (error - prevError);

	//integral
	integrator += Ki * error;

	//compute output and apply limits
	float out = proportional + integrator + differentiator;
	float outLimited = out;
	if(out > limit)
		outLimited = limit;
	else if(out < -limit)
		outLimited = -limit;

	//anti-windup
	integrator += (outLimited - out);

	//store error and measurement for later use
	prevError = error;

	//return controller output
	setSpeed(out);
}
 void PID_Controller::PIDController_Stop(){
	 Kp=0;
	 Ki=0;
	 setSpeed(0);
 }


