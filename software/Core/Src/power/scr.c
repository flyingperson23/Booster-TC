/*
 * scr.c
 *
 *  Created on: Jul 13, 2024
 *      Author: flyin
 */

#include "power/scr.h"

void SCRBlock() {
	SCR_TIM->CCR1 = SCR_MAX_DELAY;
	SCR_TIM->ARR = SCR_MAX_DELAY;
	SCR_TIM->CR1 ^= ~(TIM_CR1_CEN);
}

void SCRIncrement() {
	if (SCR_TIM->CCR1 > (SCR_MIN_DELAY + SCR_STEP)) {
		SCR_TIM->CCR1 = SCR_TIM->CCR1 - SCR_STEP;
		SCR_TIM->ARR = SCR_TIM->CCR1 + SCR_PULSE_LENGTH;
		SCR_TIM->CR1 |= TIM_CR1_CEN;
	} else {
		SCRBypass();
	}
}

void SCRBypass() {
	SCR_TIM->CCR1 = SCR_MIN_DELAY;
	SCR_TIM->ARR = SCR_MIN_DELAY + SCR_PULSE_LENGTH;
	SCR_TIM->CR1 |= TIM_CR1_CEN;
}

uint8_t SCRBypassStatus() {
	return SCR_TIM->CCR1 > (SCR_MIN_DELAY + SCR_STEP);
}
