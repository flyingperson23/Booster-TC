/*
 * fault.h
 *
 *  Created on: Jul 15, 2024
 *      Author: flyin
 */

#ifndef INC_SYS_FAULT_H_
#define INC_SYS_FAULT_H_

#include <stdint.h>
#include "booster_tc.h"
#include "sys/vars.h"
#include "status/led.h"

void FaultHandle();

extern uint8_t fault;
extern uint8_t waiting;
#define NOFAULT 0
#define FAULT_OC 1
#define FAULT_OV 2
#define FAULT_TEMP 4
#define FAULT_UVLO 5

#endif /* INC_SYS_FAULT_H_ */
