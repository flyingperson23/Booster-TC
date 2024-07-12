/*
 * booster_tc.h
 *
 *  Created on: Jul 9, 2024
 *      Author: flyin
 */

#ifndef INC_BOOSTER_TC_H_
#define INC_BOOSTER_TC_H_

#include <stdint.h>
#include "boost_compensators.h"
#include "stm32g474xx.h"
#include "vars.h"
#include "cmds.h"
#include "uart.h"

void booster_init();
void booster_loop();
void background_loop();

// power input
extern int scr_delay;
extern int vref;
extern uint8_t power_state;
#define STATE_OFF 0
#define STATE_SCR 1
#define STATE_BOOST 2

extern uint8_t mode;
#define MODE_AUTO 0
#define MODE_MANUAL 1

extern uint8_t fault;
#define NOFAULT 0
#define FAULT_OC 1
#define FAULT_OV 2
#define FAULT_TEMP 3

#endif /* INC_BOOSTER_TC_H_ */
