/*
 * booster_tc.c
 *
 *  Created on: Jul 9, 2024
 *      Author: flyin
 */

#include "booster_tc.h"

uint8_t power_state = STATE_OFF;
uint8_t mode = MODE_AUTO;
uint8_t fault = NOFAULT;
int vref = 0;
uint16_t temps[2];

void stop() {

}

void booster_init() {
	AddVars();
	FillVars();
	CmdsInit();
	UartInit();
	BoostInit();
}

void booster_loop() {

}

uint32_t scr_counter = 0;
void background_loop() {
	mode = GPIORead(MODE_IN_GPIO_Port, MODE_IN_Pin);
	if (fault == NOFAULT) {
		// check thermistors
		if (mode == MODE_AUTO) {
			vref = 400;
			if (power_state == STATE_OFF) {
				power_state = STATE_SCR;
				SCRBlock();

			}
			if (power_state == STATE_SCR) {
				// enable scr timer, disable boost timer
				scr_counter = (scr_counter + 1) % 100;
				if (scr_counter == 0) {
					SCRIncrement();
				}
				if (SCRBypassStatus()) {
					SCRBypass();
					power_state = STATE_BOOST;
				}
			}
			if (power_state == STATE_BOOST) {
				SCRBypass();
			}
		} else if (mode == MODE_MANUAL) {

		}
	} else {
		FaultHandle();
	}
}
