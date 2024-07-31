/*
 * pwm.h
 *
 *  Created on: Jul 15, 2024
 *      Author: flyin
 */

#ifndef INC_POWER_PWM_H_
#define INC_POWER_PWM_H_

#include "main.h"
#include "stdint.h"
#include "booster_tc.h"
#include "sys/util.h"

extern uint8_t switching;
void PWMInit();
void PWMStop();
void PWMStart();

#endif /* INC_POWER_PWM_H_ */
