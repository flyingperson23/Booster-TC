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
