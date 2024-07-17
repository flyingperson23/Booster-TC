/*
 * util.c
 *
 *  Created on: Jul 13, 2024
 *      Author: flyin
 */

#include "sys/util.h"

void fconstrain(float * var, float min, float max) {
	if (*var < min) *var = min;
	if (*var > max) *var = max;
}

void uconstrain(uint32_t * var, uint32_t min, uint32_t max) {
	if (*var < min) *var = min;
	if (*var > max) *var = max;
}

void iconstrain(int * var, int min, int max) {
	if (*var < min) *var = min;
	if (*var > max) *var = max;
}

uint8_t GPIORead(GPIO_TypeDef * bank, uint16_t pin) {
	return bank->IDR & pin;
}

int AmpsToCounts(float amps) { // amps * 0.04 v/a * 4095 counts / 3.3v -> 0.04*4095/3.3=49.6363636364 counts/amp
	return (int) (amps * 49.6363636364f);
}

float CountsToAmps(int counts) {// 1 / 49.6363636364 = 0.02014652014 amps / count
	return ((float) counts) * 0.02014652014f;
}

float CountsToVolts(int counts) {
	return ((float) counts) * 3.3f / 4095.0f;
}

int VoltsToCounts(float volts) {
	return (int) (volts * 4095.0f / 3.3f);
}
