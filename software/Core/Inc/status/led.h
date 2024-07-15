/*
 * led.h
 *
 *  Created on: Jul 15, 2024
 *      Author: flyin
 */

#ifndef INC_STATUS_LED_H_
#define INC_STATUS_LED_H_

#include <stdint.h>
#include "main.h"

extern uint8_t blinking;
#define LED_VBUS 1
#define LED_TEMP 3
#define LED_I_IN 4

void LEDInit();
void LEDSetValue(uint8_t LED, uint8_t value); // value = 0 to 255
void LEDSetBlinking(uint8_t LED, uint8_t on);

void TIM7_DAC_IRQHandler(void);

#endif /* INC_STATUS_LED_H_ */
