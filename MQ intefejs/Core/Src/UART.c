/*
 * UART.c
 *
 *  Created on: Apr 11, 2024
 *      Author: Stefan.Milojevic
 */

#include <string.h>
#include <stdio.h>
#include "UART.h"



extern UART_HandleTypeDef huart1;

void UART_TransmitString(char* str)
{
	HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
	char newLine[] = "\r\n";
	HAL_UART_Transmit(&huart1, (uint8_t*)newLine, strlen(newLine), HAL_MAX_DELAY);
}

void UART_TransmitStringWithoutNewLine(char* str)
{
	HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
}

void UART_TransmitFloat(float data)
{
	char msg[50];
	sprintf(msg, "%.2f\r\n", data);
	HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
}

