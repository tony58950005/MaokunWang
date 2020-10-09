/*
 * PIDController.cpp
 *
 *  Created on: 2020年10月2日
 *      Author: 59488
 */

#include <PIDController.h>
#include "main.h"
PID_Controller::PID_Controller(float Kp, float Ki, float Kd, float limMin, float limMax) :
	Kp(Kp),
	Ki(Ki),
	Kd(Kd),
	limMin(limMin),
	limMax(limMax)

{
	integrator = 0.0f;
	prevError = 0.0f;
}


float PID_Controller::PIDController_Update(float setpoint, float measurement){
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
	if(out > limMax)
		outLimited = limMax;
	else if(out < limMin)
		outLimited = limMin;

	//anti-windup
	integrator += (outLimited - out);

	//store error and measurement for later use
	prevError = error;

	//return controller output
	return out;
}

