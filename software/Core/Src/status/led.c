/*
 * led.c
 *
 *  Created on: Jul 15, 2024
 *      Author: flyin
 */

#include "status/led.h"

uint8_t blinking = 0;

void LEDInit() {
	TIM3->CR1 |= TIM_CR1_CEN;
	TIM7->CR1 |= TIM_CR1_CEN;
}

void LEDSetValue(uint8_t LED, uint8_t value) {
	if (LED == LED_VBUS) {
		TIM3->CCR1 = (uint32_t) value;
	}
	if (LED == LED_TEMP) {
		TIM3->CCR3 = (uint32_t) value;
	}
	if (LED == LED_I_IN) {
		TIM3->CCR4 = (uint32_t) value;
	}
	LEDSetBlinking(LED, 0);
}

void LEDSetBlinking(uint8_t LED, uint8_t on) {
	if ((blinking & (1 << LED)) != on) blinking ^= (1 << LED);
}

uint8_t blink_state = 0;

void TIM7_DAC_IRQHandler(void) {
	TIM7->SR = ~TIM_FLAG_UPDATE;
	blink_state ^= 0xFF;
	if (blinking & (1 << LED_VBUS)) {
		TIM3->CCR1 = blink_state;
	}
	if (blinking & (1 << LED_TEMP)) {
		TIM3->CCR3 = blink_state;
	}
	if (blinking & (1 << LED_I_IN)) {
		TIM3->CCR4 = blink_state;
	}
}
