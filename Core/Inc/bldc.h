/*
 * bldc.h
 *
 *  Created on: Jan 31, 2025
 *      Author: steve
 */

#ifndef INC_BLDC_H_
#define INC_BLDC_H_

#include "main.h"

void initBldc(TIM_HandleTypeDef *tim);
void setVoltage(uint8_t inVoltage);
float updateBldc(float inDegree);
void resetBldc();

#endif /* INC_BLDC_H_ */
