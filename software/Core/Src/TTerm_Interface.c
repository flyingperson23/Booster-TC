/*
 * TTerm_Interface.c
 *
 *  Created on: Jul 2, 2024
 *      Author: flyin
 */
#include "TTerm_Interface.h"

uint8_t rx_buff[1];
TERMINAL_HANDLE * terminal;
UART_HandleTypeDef * UART;

void TTerm_Interface_Init(UART_HandleTypeDef * uartHandle) {
	UART = uartHandle;
	HAL_UART_Receive_IT(UART, rx_buff, 1);
	terminal = TERM_createNewHandle(printer, 1, &TERM_defaultList, 0, "root");
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    HAL_UART_Receive_IT(UART, rx_buff, 1);
    TERM_processBuffer(rx_buff, 1, terminal);
}

void printer(char * format, ...) {
	  va_list arg;
	  va_start (arg, format);
	  uint8_t * buff = (uint8_t*) malloc(256);
	  int length = vsprintf((char *)buff, format, arg);

	  if (length > 256) {
	  	length = 256;
	  }
	  HAL_UART_Transmit(UART, buff, length, 1000);
	  free(buff);
	  va_end (arg);
}

