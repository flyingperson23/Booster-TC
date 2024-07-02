#include "vars.h"
#include "cmds.h"
#include "TTerm.h"
#include "main.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Var * tempVar;
int tempInt;

char* getSaveStatus(uint8_t code) {
	if (code == OK) return "OK";
	if (code == ERR_A_NEQ) return "A NEQ";
	if (code == ERR_B_NEQ) return "B NEQ";
	if (code == ERR_C_NEQ) return "C NEQ";
	if (code == ERR_NONE_EQ) return "NONE EQ";
	return "";
}
volatile int incCounter = 0;
void inc() {
	incCounter++;
}
uint8_t CMD_get(TERMINAL_HANDLE * handle, uint8_t argCount, char ** args) {
	if (argCount == 0) {
		for (int i = 0; i < NUM_VARS; i++) {
			ttprintf("%s: %i%c status: %s\r\n", getVar(i)->name, getVar(i)->value, getVar(i)->suffix, getSaveStatus(getVar(i)->save_status));
		}
	}
	if (argCount != 1) {
		ttprintf("Usage: get [name]");
		return TERM_CMD_EXIT_SUCCESS;
	}
	if (!strcmp(args[0], "inc")) {
		ttprintf("%i", incCounter);
		return TERM_CMD_EXIT_SUCCESS;
	}
	if (getIndex(args[0]) == -1) {
		ttprintf("Var not found: %s", args[0]);
		return TERM_CMD_EXIT_SUCCESS;
	}
	tempVar = getVar(getIndex(args[0]));
	ttprintf("%s: %i%c\r\n", args[0], tempVar->value, tempVar->suffix);
	return TERM_CMD_EXIT_SUCCESS;
}

uint8_t CMD_set(TERMINAL_HANDLE * handle, uint8_t argCount, char ** args) {
	if (argCount == 1 && !strcmp(args[0], "default")) {
		ttprintf("Set all to default");
		for (int i = 0; i < NUM_VARS; i++) {
			getVar(i)->value = getVar(i)->default_value;
		}
		writeVars();
		fillVars();
		return TERM_CMD_EXIT_SUCCESS;
	}
	if (argCount != 2) {
		ttprintf("Usage: set [name] [value]");
		return TERM_CMD_EXIT_SUCCESS;
	}
	if (getIndex(args[0]) == -1) {
		ttprintf("Var not found: %s", args[0]);
		return TERM_CMD_EXIT_SUCCESS;
	}
	tempVar = getVar(getIndex(args[0]));
	tempInt = atoi(args[1]);
	if (tempInt < tempVar->min || tempInt > tempVar->max) {
		ttprintf("Valid range: %i-%i", tempVar->min, tempVar->max);
		return TERM_CMD_EXIT_SUCCESS;
	}
	tempVar->value = tempInt;
	ttprintf("Set %s to %i%c", tempVar->name, tempInt, tempVar->suffix);
	writeVars();
	fillVars();
	return TERM_CMD_EXIT_SUCCESS;

}

void cmds_init(){
    TERM_addCommand(CMD_get, "get", "Gets a variable", 0, &TERM_defaultList);
    TERM_addCommand(CMD_set, "set", "Sets a variable", 0, &TERM_defaultList);
}
