/*
 * buck.h
 *
 *  Created on: Jul 17, 2024
 *      Author: flyin
 */

// controls buck converters for fan and drive voltage

#ifndef INC_POWER_BUCK_H_
#define INC_POWER_BUCK_H_

#include "main.h"

void SPIInit();
void FanSet(uint8_t setpoint);
void DriveSet(uint8_t setpoint);

#endif /* INC_POWER_BUCK_H_ */
