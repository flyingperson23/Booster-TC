/*
 * cmds.c
 *
 *  Created on: Jul 11, 2024
 *      Author: flyin
 */

#include "cmds.h"

Var * tempVar;
int tempInt;

uint8_t CMD_get(TERMINAL_HANDLE * handle, uint8_t argCount, char ** args) {
	if (argCount == 0) {
		for (int i = 0; i < NUM_VARS; i++) {
			ttprintf("%s: %i%c\r\n", GetVar(i)->name, GetVar(i)->value, GetVar(i)->suffix);
		}
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
	ttprintf("%s: %i%c\r\n", args[0], tempVar->value, tempVar->suffix);
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
	ttprintf("Set %s to %i%c", tempVar->name, tempInt, tempVar->suffix);
	WriteVars();
	FillVars();
	return TERM_CMD_EXIT_SUCCESS;

}

void CmdsInit(){
    TERM_addCommand(CMD_get, "get", "Gets a variable", 0, &TERM_defaultList);
    TERM_addCommand(CMD_set, "set", "Sets a variable", 0, &TERM_defaultList);
}
