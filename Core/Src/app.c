/*
 * app.c
 *
 *  Created on: Jan 18, 2025
 *      Author: steve
 */

#include "app.h"

extern UART_HandleTypeDef	huart2;
extern TIM_HandleTypeDef	htim1;
extern TIM_HandleTypeDef	htim11;

extern int countChangeAngle;

void delayUs(int t) {
	htim11.Instance->CNT = 0;
	while(htim11.Instance->CNT < t);
}

void app() {
	// uart 초기화
	initUart(&huart2);
	// bldc 초기화
	initBldc(&htim1);
	setVoltage(30);	// 10 ~
	HAL_TIM_Base_Start(&htim11);
	while(1) {
		// 초기 회전을 원하는 각도 입력
  	static float angle = 360;
  	float resultValue = updateBldc(angle);
  	delayUs(1);
  	if(resultValue == 360) {
  		angle = 0;
  	}
  	if(resultValue == 0) {
  		angle = 360;
  	}
//  	if(countChangeAngle == 0) {
//  		countChangeAngle = -1;//2400;
//  		/*static int step = 0;
//  		const float stepAngle = (M_PI * 2) / 7;
//  		angle = stepAngle * step;
//  		step++;
//  		step %= 7;//*/
//  		/*static bool flag = false;
//  		angle = flag ? 0 : 2*M_PI;
//  		flag ^= 1;//*/
//  		resetBldc();
//  		angle = 360;
//  	}
	}
}
