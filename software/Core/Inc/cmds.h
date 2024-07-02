/*
 * cmds.h
 *
 *  Created on: May 11, 2024
 *      Author: flyin
 */

#ifndef INC_CMDS_H_
#define INC_CMDS_H_

#include <stdint.h>
#include "TTerm.h"

void cmds_init();
void inc();
uint8_t CMD_get(TERMINAL_HANDLE * handle, uint8_t argCount, char ** args);
uint8_t CMD_set(TERMINAL_HANDLE * handle, uint8_t argCount, char ** args);

#endif /* INC_CMDS_H_ */
