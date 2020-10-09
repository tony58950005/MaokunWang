/*
 * PIDController.h
 *
 *  Created on: 2020年10月2日
 *      Author: 59488
 */

#ifndef PIDCONTROLLER_H_
#define PIDCONTROLLER_H_
#include "main.h"

class PID_Controller {
public:
	PID_Controller(float Kp, float Ki, float Kd, float limMin, float limMax);
	float PIDController_Update(float setpoint, float measurement);
private:
	float Kp;//controller gains
	float Ki;
	float Kd;

	float limMin;//output limits
	float limMax;

	float integrator;// controller memory
	float prevError;//required for integrator
};

#endif /* PIDCONTROLLER_H_ */
