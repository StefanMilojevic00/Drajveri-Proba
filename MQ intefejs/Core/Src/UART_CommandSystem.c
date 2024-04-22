/*
 * UART_CommandSystem.c
 *
 *  Created on: Apr 22, 2024
 *      Author: Stefan.Milojevic
 */


#include "UART_CommandSystem.h"
#include "UART.h"

extern UART_HandleTypeDef huart1;

static uint8_t RxIndex;
static uint8_t RxData[1];
static uint8_t RxBuffer[200];
static bool transferCompleteFlag = false;
static uint8_t* toSend;
static char msg[] = "\r\n"; // Just for testing

void TerminalHandler(UART_HandleTypeDef *huart)
{
	uint8_t newLine[] = "\n\r";
	uint8_t backspace[] = "\b  \b";

	if(huart->Instance == USART1)
	{
		if(RxIndex == 0)
		{
			ClearRxBuffer();
		}
		if(RxData[0] != 13) //if it is not carrige return
		{
			if(RxData[0] == 8 && RxIndex > 0) //If user presses backspace
			{
				RxBuffer[RxIndex] = '\0';
				RxIndex--;
				HAL_UART_Transmit(huart, backspace, sizeof(backspace), TIMEOUT_UART);
			}
			else
			{
				RxBuffer[RxIndex] = RxData[0];
				RxIndex++;
			}
			HAL_UART_Transmit(huart, RxData, sizeof(RxData), TIMEOUT_UART);
		}
		else
		{
			RxBuffer[RxIndex] = RxData[0];
			RxIndex = 0; // This will clear the buffer
			transferCompleteFlag = true;
			HAL_UART_Transmit(huart, newLine, sizeof(newLine), TIMEOUT_UART);
		}
	}
	HAL_UART_Receive_IT(huart, RxData, sizeof(RxData)); //Start again so it will read it always
}

void TerminalInit(UART_HandleTypeDef *huart) //Function reads 1 data byte
{
	HAL_UART_Receive_IT(huart, RxData, sizeof(RxData));
}

void ClearRxBuffer()
{
	for(int counter = 0; counter < 200; counter++)
	{
		RxBuffer[counter] = 0;
	}
	transferCompleteFlag = false;
}

bool IsTransferComplete()
{
	return transferCompleteFlag;
}

uint8_t* GetRxBuffer()
{
	return RxBuffer;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) //Interrupt function defined by Cube
{
	TerminalHandler(huart); //TerminalHandler becomes a callback function
	if(IsTransferComplete())
	{
		toSend = GetRxBuffer();
		HAL_UART_Transmit(&huart1, toSend, strlen((char*)toSend), HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	}
}

bool StringCompareFromUART(char* cmp_cmd, char** cmdStrings, const uint8_t array_element, uint8_t* ret_val)
{
  bool find = false;
  bool stop_flag = false;
  uint8_t iterator = 0;
  do
	{
	  if (((strcmp(cmp_cmd, cmdStrings[iterator])) == 0) && (find == false))
		{
		  if(iterator == 0)
		  {
			  find = true;
			  stop_flag = true;
			  *ret_val = iterator;

			 // return find;
		  }
		  *ret_val = iterator;

		//  printf("Uslo\n");
		  UART_TransmitString("Uslo\n");
		//  printf(cmp_cmd);
		  UART_TransmitFloat((float)iterator);
	//	  printf("\n");
		  UART_TransmitString("\n");
		  find = true;
		  stop_flag = true;
		}
        else
        {
            iterator++;
      //      printf("Nije: %d\n", iterator);


        }

	}while ((stop_flag == false) || (iterator < array_element));

    return find;
}
