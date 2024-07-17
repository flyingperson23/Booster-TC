/*
 * buck.c
 *
 *  Created on: Jul 17, 2024
 *      Author: flyin
 */

#include "power/buck.h"

void SPIInit() {
	HAL_GPIO_WritePin(CS_FAN_GPIO_Port, CS_FAN_Pin, SET);
	HAL_GPIO_WritePin(CS_DRIVE_GPIO_Port, CS_DRIVE_Pin, SET);
}

void FanSet(uint8_t setpoint) {
	HAL_GPIO_WritePin(CS_FAN_GPIO_Port, CS_FAN_Pin, RESET);
	HAL_SPI_Transmit(&hspi2, &setpoint, 1, 100);
	HAL_GPIO_WritePin(CS_FAN_GPIO_Port, CS_DRIVE_Pin, SET);
}

void DriveSet(uint8_t setpoint) {
	HAL_GPIO_WritePin(CS_DRIVE_GPIO_Port, CS_DRIVE_Pin, RESET);
	HAL_SPI_Transmit(&hspi2, &setpoint, 1, 100);
	HAL_GPIO_WritePin(CS_DRIVE_GPIO_Port, CS_DRIVE_Pin, SET);
}
