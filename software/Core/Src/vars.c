/*
 * vars.c
 *
 *  Created on: Jul 11, 2024
 *      Author: flyin
 */

#include "vars.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stm32g4xx_hal.h"
#include "stm32_hal_legacy.h"

Var * vars[NUM_VARS];
int64_t vars_buffer[NUM_VARS];

void AddVars() {
	AddVar("max_pri_i", 300, 'A', MAX_PRI_I, 0, 5000);
	AddVar("max_ac_i", 15, 'A', MAX_AC_I, 0, 1000);
	AddVar("max_out_v", 400, 'V', MAX_OUT_V, 0, 400);
	AddVar("max_temp", 60, 'C', MAX_TEMP, 0, 200);
}

void AddVar(char * name, int64_t default_value, char suffix, uint8_t index, int64_t min, int64_t max) {
	Var * newVar = malloc(sizeof(Var));
	memset(newVar, 0, sizeof(Var));
	newVar->default_value = default_value;
	newVar->name = name;
	newVar->suffix = suffix;
	newVar->min = min;
	newVar->max = max;
	vars[index] = newVar;
}

Var * GetVar(uint8_t index) {
	return vars[index];
}

int64_t GetValue(uint8_t index) {
	return GetVar(index)->value;
}

int8_t GetIndex(char* name) {
	for (int i = 0; i < NUM_VARS; i++) {
		if (!strcmp(name, vars[i]->name)) {
			return i;
		}
	}
	return -1;
}

void FillVars() {
	Flash_Read_Data(MEMORY_START, vars_buffer, NUM_VARS);
	for (int i = 0; i < NUM_VARS; i++) {
		vars[i]->value = vars_buffer[i];
	}
}

void WriteVars() {
	for (int i = 0; i < NUM_VARS; i++) {
		vars_buffer[i] = vars[i]->value;
	}
	Flash_Write_Data(MEMORY_START, vars_buffer, NUM_VARS);
}

void Flash_Read_Data(uint32_t StartPageAddress, int64_t *RxBuf, uint16_t numberofwords) {
	while (1){
		*RxBuf = *(int64_t *)StartPageAddress;
		StartPageAddress += 8;
		RxBuf++;
		if (!(numberofwords--)) break;
	}
}


static FLASH_EraseInitTypeDef EraseInitStruct;
uint32_t PAGEError = 0;

void Flash_Write_Data (uint32_t StartPageAddress, int64_t *Data, uint16_t numberofwords) {

    HAL_FLASH_Unlock();
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);

    EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.Banks     = FLASH_BANK_1;
    EraseInitStruct.Page	  = 0;
    EraseInitStruct.NbPages	  = 1;
    HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError);
    for (int i = 0; i < numberofwords && i < 256; i++) {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, MEMORY_START + 8 * i, Data[i]);
    }
    HAL_FLASH_Lock();
}

