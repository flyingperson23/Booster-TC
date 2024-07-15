/*
 * booster_tc.h
 *
 *  Created on: Jul 9, 2024
 *      Author: flyin
 */

#ifndef INC_BOOSTER_TC_H_
#define INC_BOOSTER_TC_H_

#include <stdint.h>
#include "stm32g474xx.h"
#include "power/boost_compensators.h"
#include "power/scr.h"
#include "sys/vars.h"
#include "sys/cmds.h"
#include "sys/uart.h"
#include "sys/util.h"
#include "status/fault.h"

void booster_init();
void booster_loop();
void background_loop();

void stop();

// power input
extern int vref;
extern uint8_t power_state;
#define STATE_OFF 0
#define STATE_SCR 1
#define STATE_BOOST 2

extern uint8_t mode;
#define MODE_AUTO 0
#define MODE_MANUAL 1

#endif /* INC_BOOSTER_TC_H_ */
