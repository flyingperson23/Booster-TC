#include "vars.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stm32f4xx_hal.h"

Var * vars[NUM_VARS];
uint32_t vars_buffer[NUM_VARS * 3];

uint32_t a, b, c;

void addVars() {
	addVar("max_pri_i", 300, 'A', MAX_PRI_I, 0, 5000);
	addVar("max_ac_i", 15, 'A', MAX_AC_I, 0, 1000);
	addVar("max_out_v", 400, 'V', MAX_OUT_V, 0, 400);
	addVar("max_temp", 60, 'C', MAX_TEMP, 0, 200);
}

void addVar(char * name, uint32_t default_value, char suffix, uint8_t index, int16_t min, int16_t max) {
	Var * newVar = malloc(sizeof(Var));
	memset(newVar, 0, sizeof(Var));
	newVar->default_value = default_value;
	newVar->name = name;
	newVar->suffix = suffix;
	newVar->min = min;
	newVar->max = max;
	vars[index] = newVar;
}

Var * getVar(uint8_t index) {
	return vars[index];
}

int8_t getIndex(char* name) {
	for (int i = 0; i < NUM_VARS; i++) {
		if (!strcmp(name, vars[i]->name)) {
			return i;
		}
	}
	return -1;
}

uint8_t fillVars() {
	uint8_t ret = 0;
	Flash_Read_Data(MEMORY_START, vars_buffer, 3*NUM_VARS);
	for (int i = 0; i < NUM_VARS; i++) {
		a = vars_buffer[3*i];
		b = vars_buffer[3*i + 1];
		c = vars_buffer[3*i + 2];
		if (a == b && b == c) {
			vars[i]->save_status = OK;
			vars[i]->value = a;
		} else if (a == b && a != c) {
			vars[i]->save_status = ERR_C_NEQ;
			vars[i]->value = a;
			ret = 1;
		} else if (b == c && c != a) {
			vars[i]->save_status = ERR_A_NEQ;
			vars[i]->value = b;
			ret = 1;
		} else if (a == c && a != b) {
			vars[i]->save_status = ERR_B_NEQ;
			vars[i]->value = c;
			ret = 1;
		} else if (a != b && b != c) {
			vars[i]->save_status = ERR_NONE_EQ;
			vars[i]->value = vars[i]->default_value;
			ret = 1;
		}
	}
	return ret;
}

void writeVars() {
	for (int i = 0; i < NUM_VARS; i++) {
		vars_buffer[3*i] = vars[i]->value;
		vars_buffer[3*i + 1] = vars[i]->value;
		vars_buffer[3*i + 2] = vars[i]->value;
	}
	Flash_Write_Data(MEMORY_START, vars_buffer, NUM_VARS*3);
}

void Flash_Read_Data (uint32_t StartPageAddress, uint32_t *RxBuf, uint16_t numberofwords) {
	while (1){

		*RxBuf = *(uint32_t *)StartPageAddress;
		StartPageAddress += 4;
		RxBuf++;
		if (!(numberofwords--)) break;
	}}

void Flash_Write_Data (uint32_t StartPageAddress, uint32_t *Data, uint16_t numberofwords) {

    HAL_FLASH_Unlock();
    FLASH_Erase_Sector(FLASH_SECTOR_6,VOLTAGE_RANGE_3);
    while(1) {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,StartPageAddress,*Data);
        Data++;
        StartPageAddress += 4;
        if (!(numberofwords--)) break;
    }
    HAL_FLASH_Lock();
}

