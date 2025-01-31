/*
 * bldc.c
 *
 *  Created on: Jan 31, 2025
 *      Author: steve
 */

#include "bldc.h"

TIM_HandleTypeDef *timMotor;

float currentDegree = 0;
int voltage = 85;//85;//500
const float incAngle = 0.5;
float dU = 0;
float dV = 120;
float dW = 240;

float roundToDecimal(float value, int decimalPlaces) {
	float scale = pow(10, decimalPlaces);
	return round(value * scale) / scale;
}

void initBldc(TIM_HandleTypeDef *tim) {
	timMotor = tim;
  HAL_TIM_PWM_Start(timMotor, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(timMotor, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(timMotor, TIM_CHANNEL_3);
  HAL_GPIO_WritePin(MotorEnable_GPIO_Port, MotorEnable_Pin, 1);
  resetBldc();
}

void setVoltage(uint8_t inVoltage) {
	voltage = (inVoltage * 5) - 1;
}

float updateBldc(float inDegree) {
	const int polePair = 11; // pole pair 7
	inDegree *= polePair;
	if(fabs(inDegree - currentDegree) < 0.1f) return currentDegree / polePair;
	else if(inDegree > currentDegree) {
		dU += incAngle;
		dV += incAngle;
		dW += incAngle;
		currentDegree += incAngle;
	}
	else if(inDegree < currentDegree) {
		dU -= incAngle;
		dV -= incAngle;
		dW -= incAngle;
		currentDegree -= incAngle;
	}

	dU = roundToDecimal(dU, 1);
	dV = roundToDecimal(dV, 1);
	dW = roundToDecimal(dW, 1);
	currentDegree = roundToDecimal(currentDegree, 1);
	int pwmValueU = sin(dU * M_PI / 180) * voltage + 499;
	int pwmValueV = sin(dV * M_PI / 180) * voltage + 499;
	int pwmValueW = sin(dW * M_PI / 180) * voltage + 499;
	timMotor->Instance->CCR1 = pwmValueU;
	timMotor->Instance->CCR2 = pwmValueV;
	timMotor->Instance->CCR3 = pwmValueW;
	return currentDegree / polePair;
}

void resetBldc() {
	dU = 0;
	dV = 120;
	dW = 240;
	currentDegree = 0;
}
