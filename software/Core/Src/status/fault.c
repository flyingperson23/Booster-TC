/*
 * fault.c
 *
 *  Created on: Jul 15, 2024
 *      Author: flyin
 */

#include "status/fault.h"

uint8_t waiting = 0;
uint8_t active = 1;
uint8_t fault = 0;

void FaultHandle() {
	if (mode == MODE_AUTO) {
		stop();

		LEDSetBlinking(LED_VBUS, 1);
		LEDSetBlinking(LED_TEMP, 1);
		LEDSetBlinking(LED_I_IN, 1);

		if (active) {
			if (GetValue(AUTORESET_TIME) <= -1) {
				while (1) {
					active = 0;
				}
			} else {
				active = 0;
				HAL_Delay(GetValue(AUTORESET_TIME));
				active = 1;
			}
		}
	} else {
		waiting = 1;
		stop();

		LEDSetBlinking(LED_VBUS, 1);
		LEDSetBlinking(LED_TEMP, 1);
		LEDSetBlinking(LED_I_IN, 1);
		while (waiting) {
			HAL_Delay(1);
			stop();
		}
	}

}
