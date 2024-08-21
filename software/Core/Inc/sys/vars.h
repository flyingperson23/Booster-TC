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
	int64_t value;
	int64_t default_value;
	char * name;
	char * suffix;
	int64_t min;
	int64_t max;
} Var;

void Flash_Write_Data (uint32_t StartPageAddress, int64_t *Data, uint16_t numberofwords);
void Flash_Read_Data (uint32_t StartPageAddress, int64_t *RxBuf, uint16_t numberofwords);
void FillVars();
void WriteVars();
void AddVars();
void AddVar(char* name, int64_t default_value, char * suffix, uint8_t index, int64_t min, int64_t max);
Var * GetVar(uint8_t index);
int8_t GetIndex(char* name);
int64_t GetValue(uint8_t index);

#define MEMORY_START 0x08000000

#define NUM_VARS 11

#define MAX_PRI_I 0
#define MAX_AC_I 1
#define MAX_OUT_V 2
#define MAX_TEMP 3
#define MAX_I_L 4
#define CT_FACTOR 5
#define VDRIVE 6
#define RAMP_START 7
#define RAMP_END 8
#define AUTORESET_TIME 9
#define UVLO 10


#endif /* INC_VARS_H_ */
