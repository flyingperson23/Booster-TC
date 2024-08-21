/*
 * cmds.c
 *
 *  Created on: Jul 11, 2024
 *      Author: flyin
 */

#include "sys/cmds.h"

Var * tempVar;
int tempInt;

uint8_t CMD_telem(TERMINAL_HANDLE * handle, uint8_t argCount, char ** args) {
	ttprintf("Bus Voltage: %fVdc\r\n", AvgCalculate(&VBUS_avg));
	ttprintf("Line Voltage: %fVac\r\n", AvgCalculate(&VAC_avg));
	ttprintf("Line Current: %fA\r\n", AvgCalculate(&IAC_avg));
	ttprintf("Temps: %fC, %fC, %fC\r\n", temps[0], temps[1], temps[2]);
	ttprintf("Driver Input: %fVdc\r\n", V24_sense);
	return TERM_CMD_EXIT_SUCCESS;
}

uint8_t CMD_get(TERMINAL_HANDLE * handle, uint8_t argCount, char ** args) {
	if (argCount == 0) {
		for (int i = 0; i < NUM_VARS; i++) {
			ttprintf("%s: %i%c\r\n", GetVar(i)->name, GetVar(i)->value, GetVar(i)->suffix);
		}
		return TERM_CMD_EXIT_SUCCESS;
	}
	if (argCount != 1) {
		ttprintf("Usage: get [name]");
		return TERM_CMD_EXIT_SUCCESS;
	}
	if (GetIndex(args[0]) == -1) {
		ttprintf("Var not found: %s", args[0]);
		return TERM_CMD_EXIT_SUCCESS;
	}
	tempVar = GetVar(GetIndex(args[0]));
	ttprintf("%s: %i%s", args[0], tempVar->value, tempVar->suffix);
	return TERM_CMD_EXIT_SUCCESS;
}

uint8_t CMD_set(TERMINAL_HANDLE * handle, uint8_t argCount, char ** args) {
	if (argCount == 1 && !strcmp(args[0], "default")) {
		ttprintf("Set all to default");
		for (int i = 0; i < NUM_VARS; i++) {
			GetVar(i)->value = GetVar(i)->default_value;
		}
		WriteVars();
		FillVars();
		return TERM_CMD_EXIT_SUCCESS;
	}
	if (argCount != 2) {
		ttprintf("Usage: set [name] [value]");
		return TERM_CMD_EXIT_SUCCESS;
	}
	if (GetIndex(args[0]) == -1) {
		ttprintf("Var not found: %s", args[0]);
		return TERM_CMD_EXIT_SUCCESS;
	}
	tempVar = GetVar(GetIndex(args[0]));
	tempInt = atoi(args[1]);
	if (tempInt < tempVar->min || tempInt > tempVar->max) {
		ttprintf("Valid range: %i-%i", tempVar->min, tempVar->max);
		return TERM_CMD_EXIT_SUCCESS;
	}
	tempVar->value = tempInt;
	ttprintf("Set %s to %i%s", tempVar->name, tempInt, tempVar->suffix);
	WriteVars();
	FillVars();
	return TERM_CMD_EXIT_SUCCESS;

}

uint8_t CMD_fault(TERMINAL_HANDLE * handle, uint8_t argCount, char ** args) {
	if (argCount != 1) {
		ttprintf("Usage: fault [get/clear]");
		return TERM_CMD_EXIT_SUCCESS;
	}
	if (!strcmp(args[0], "get")) {
		if (fault == NOFAULT) {
			ttprintf("No faults active");
		} else {
			if (fault & FAULT_OC) {
				ttprintf("Input current of %f above limit of %i\r\n", I_L, GetValue(MAX_I_L));
			}
			if (fault & FAULT_OV) {
				ttprintf("Bus voltage of %f above limit of %i\r\n", vbus, GetValue(MAX_OUT_V));
			}
			if (fault & FAULT_TEMP) {
				ttprintf("One or more of temps (%f, %f, %f) above limit of %i\r\n", temps[0], temps[1], temps[2], GetValue(MAX_TEMP));
			}
			if (fault & FAULT_UVLO) {
				ttprintf("Input voltage %f less than minimum of %i\r\n", V24_sense, GetValue(UVLO));
			}
		}
		return TERM_CMD_EXIT_SUCCESS;
	}
	if (!strcmp(args[0], "clear")) {
		waiting = 0;
		fault = NOFAULT;
		return TERM_CMD_EXIT_SUCCESS;
	}

	ttprintf("Usage: fault [get/clear]");
	return TERM_CMD_EXIT_SUCCESS;
}

uint8_t CMD_vbus(TERMINAL_HANDLE * handle, uint8_t argCount, char ** args) {
	if (argCount != 1) {
		ttprintf("Usage: vbus [voltage]");
		return TERM_CMD_EXIT_SUCCESS;
	}
	int setpoint = atoi(args[0]);
	if (setpoint < 10 || setpoint > GetValue(MAX_OUT_V)) {
		ttprintf("Valid range: %i-%i", 10, GetValue(MAX_OUT_V));
		return TERM_CMD_EXIT_SUCCESS;
	}

	vref = setpoint;
	ttprintf("Usage: fault [get/clear]");
	return TERM_CMD_EXIT_SUCCESS;
}

void addCommand(TermCommandFunction function, const char * command, const char * description){
	TERM_addCommand(function, command, description, 0, &TERM_defaultList);
}

void CmdsInit(){
	addCommand(CMD_get, "get", "Gets a variable");
	addCommand(CMD_set, "set", "Sets a variable");
	addCommand(CMD_fault, "fault", "Views/clears faults");
	addCommand(CMD_telem, "telem", "Gets telemetry");
}
