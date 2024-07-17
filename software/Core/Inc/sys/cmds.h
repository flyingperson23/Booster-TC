/*
 * cmds.h
 *
 *  Created on: May 11, 2024
 *      Author: flyin
 */

#ifndef INC_CMDS_H_
#define INC_CMDS_H_

#include <power/boost.h>
#include "sys/tterm/TTerm.h"
#include "main.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sys/vars.h"
#include "status/fault.h"
#include "booster_tc.h"

void CmdsInit();

uint8_t CMD_get(TERMINAL_HANDLE * handle, uint8_t argCount, char ** args);
uint8_t CMD_set(TERMINAL_HANDLE * handle, uint8_t argCount, char ** args);
uint8_t CMD_fault(TERMINAL_HANDLE * handle, uint8_t argCount, char ** args);

#endif /* INC_CMDS_H_ */
