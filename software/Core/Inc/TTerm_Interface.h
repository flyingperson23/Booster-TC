/*
 * TTerm_Interface.h
 *
 *  Created on: Jul 2, 2024
 *      Author: flyin
 */

#ifndef INC_TTERM_INTERFACE_H_
#define INC_TTERM_INTERFACE_H_

#include "TTerm.h"
#include "cmds.h"
#include "vars.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin);
void printer(char * format, ...);
void TTerm_Interface_Init(UART_HandleTypeDef * uartHandle);

#endif /* INC_TTERM_INTERFACE_H_ */
