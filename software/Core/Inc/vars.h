/*
 * vars.h
 *
 *  Created on: May 11, 2024
 *      Author: flyin
 */

#ifndef INC_VARS_H_
#define INC_VARS_H_

#include <stdint.h>

typedef struct {
	uint32_t value;
	uint32_t default_value;
	char * name;
	char suffix;
	uint8_t save_status;
	int16_t min;
	int16_t max;
} Var;

void Flash_Write_Data (uint32_t StartPageAddress, uint32_t *Data, uint16_t numberofwords);
void Flash_Read_Data (uint32_t StartPageAddress, uint32_t *RxBuf, uint16_t numberofwords);
uint8_t fillVars();
void writeVars();
void addVars();
void addVar(char* name, uint32_t default_value, char suffix, uint8_t index, int16_t min, int16_t max);
Var * getVar(uint8_t index);
int8_t getIndex(char* name);

#define MEMORY_START 0x08040000
#define OK 0
#define ERR_A_NEQ 1
#define ERR_B_NEQ 2
#define ERR_C_NEQ 3
#define ERR_NONE_EQ 4

#define NUM_VARS 4

#define MAX_PRI_I 0
#define MAX_AC_I 1
#define MAX_OUT_V 2
#define MAX_TEMP 3


#endif /* INC_VARS_H_ */
