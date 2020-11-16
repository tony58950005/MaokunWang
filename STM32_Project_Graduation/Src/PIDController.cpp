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

bool PID_Controller::motorControlInit()
{
	TIM_Base_InitTypeDef servoInit;
	servoInit.Prescaler = 1;
	servoInit.CounterMode = TIM_COUNTERMODE_CENTERALIGNED3;
	servoInit.Period = 2100;
	servoInit.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	servoInit.RepetitionCounter = 0;

	TIM_OC_InitTypeDef sConfigOC = {0};
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = servoInit.Period/2;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_SET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
//	PWM motorPWM1(TIM8, servoInit, sConfigOC, TIM_CHANNEL_1);
//	PWM motorPWM2(TIM8, servoInit, sConfigOC, TIM_CHANNEL_2);
//	PID_Controller motorController(1.0, 0.0, 0.0, motorPWM1, motorPWM2);

	//return motorController;
}

