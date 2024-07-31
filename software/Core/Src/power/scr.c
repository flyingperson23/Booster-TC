/*
 * scr.c
 *
 *  Created on: Jul 13, 2024
 *      Author: flyin
 */

#include "power/scr.h"

void SCRInit() {
	HAL_TIM_PWM_Start(&htim20, TIM_CHANNEL_1);
	SCRBlock();
}

void SCRBlock() {
	TIM20->CCR1 = SCR_MAX_DELAY;
	TIM20->ARR = SCR_MAX_DELAY;
	TIM20->CR1 &= ~(TIM_CR1_CEN);
}

void SCRIncrement() {
	if (TIM20->CCR1 > (SCR_MIN_DELAY + SCR_STEP)) {
		TIM20->CCR1 = TIM20->CCR1 - SCR_STEP;
		TIM20->ARR = TIM20->CCR1 + SCR_PULSE_LENGTH;
		TIM20->CR1 |= TIM_CR1_CEN;
	} else {
		SCRBypass();
	}
}

void SCRBypass() {
	TIM20->CCR1 = SCR_MIN_DELAY;
	TIM20->ARR = SCR_MIN_DELAY + SCR_PULSE_LENGTH;
	TIM20->CR1 |= TIM_CR1_CEN;
}

uint8_t SCRBypassStatus() {
	return TIM20->CCR1 > (SCR_MIN_DELAY + SCR_STEP);
}
