/*
 * boost_compensators.h
 *
 *  Created on: Jul 13, 2024
 *      Author: flyin
 */

#ifndef INC_SCR_H_
#define INC_SCR_H_

// controls SCRs for bus voltage

#include <stdint.h>
#include "main.h"
#include "sys/util.h"

#define SCR_PULSE_LENGTH 50 // TIM20 prescaler = 170 -> values in us
#define SCR_MAX_DELAY 8333
#define SCR_MIN_DELAY 10
#define SCR_STEP (SCR_MAX_DELAY - SCR_MIN_DELAY) / 100

void SCRInit();
void SCRBlock(); // lets no current through
void SCRIncrement(); // steps forward pulse timing to let more power through
void SCRBypass(); // lets full power through
uint8_t SCRBypassStatus(); // 1 if letting full power through, 0 otherwise

#endif /* INC_SCR_H_ */
