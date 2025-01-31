/*
 * timer.c
 *
 *  Created on: Aug 8, 2024
 *      Author: coffe
 */

#include "timer.h"

int countChangeAngle;

void SystickCallback() {
	if(countChangeAngle > 0) countChangeAngle--;
}
