/*
 * util.h
 *
 *  Created on: Jul 13, 2024
 *      Author: flyin
 */

#ifndef INC_SYS_UTIL_H_
#define INC_SYS_UTIL_H_

#include <stdint.h>
#include "stm32g474xx.h"

void fconstrain(float * var, float min, float max);
void uconstrain(uint32_t * var, uint32_t min, uint32_t max);
void iconstrain(int * var, int min, int max);

uint8_t GPIORead(GPIO_TypeDef * bank, uint16_t pin); // pin is bitmask - for pin 3, pin = 0b0000000000001000

int AmpsToCounts(float amps); // for I_L
float CountsToAmps(int counts);

float CountsToVolts(int counts); // for general adc
int VoltsToCounts(float volts);

#endif /* INC_SYS_UTIL_H_ */
