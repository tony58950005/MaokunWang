/*
 * PIDController.cpp
 *
 *  Created on: 2020年10月2日
 *      Author: 59488
 */

#include <PIDController.h>
#include "main.h"
PID_Controller::PID_Controller(){
	integrator = 0.0f;
	prevError = 0.0f;

	differentiator = 0.0f;
	prevMeasurement = 0.0f;

	out = 0.0f;
}


float PID_Controller::PIDController_Update(float setpoint, float measurement){
	//error signal
	float error =setpoint- measurement;


	//proportional
	float proportional =Kp * error;

	//integral
	integrator = integrator + 0.5f * Ki * T * (error+ prevError);

	//anti-windup via dynamic integrator clamping
	float limMinInt, limMaxInt;

	//compare integrator limits,set up limits we need to set on the integrator
	if(limMax > proportional){
		limMaxInt=limMax-proportional;
	}else{
		limMaxInt=0.0f;
	}

	if(limMin < proportional){
		limMinInt=limMin-proportional;
	}else{
		limMinInt=0.0f;
	}

	//clamp integrator
	if(integrator > limMaxInt){
		integrator = limMaxInt;
	}else if(integrator < limMinInt){
		integrator = limMinInt;
	}

	//derivative band-limited differentiator
	differentiator= (2.0f* Kd * (measurement -prevMeasurement)
			+(2.0f * tau-T)* differentiator)
					/(2.0f * tau + T);

	//compute output and apply limits
	out=proportional + integrator +differentiator;
	if(out > limMax){
		out = limMax;
	}else if(out < limMax){
		out=limMin;
	}
	//store error and measurement for later use
	prevError = error;
	prevMeasurement = measurement;

	//return controller output
	return out;

}

