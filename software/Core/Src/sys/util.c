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
	return (bank->IDR & pin) != 0;
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

void InitAvg(StructAvg *avg) {
	for (int i = 0; i < AVG_LEN; i++) {
		avg->values[i] = 0;
	}
	avg->counter = 0;
	avg->out = 0;
	avg->first_value = 1;
}

void AvgInput(StructAvg *avg, float value) {
	avg->counter = (avg->counter + 1) % AVG_LEN;
	if (avg->first_value == 1) {
		for (int i = 0; i < AVG_LEN; i++) {
			avg->values[i] = value;
		}
		avg->first_value = 0;
	} else {
		avg->values[avg->counter] = value;
	}
}

float AvgCalculate(StructAvg *avg) {
	float sum = 0;
	for (int i = 0; i < AVG_LEN; i++) {
		sum += avg->values[i];
	}
	sum /= AVG_LEN;
	avg->out = sum;
	return sum;
}
