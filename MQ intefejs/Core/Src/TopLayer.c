/*
 * TopLayer.c
 *
 *  Created on: Apr 12, 2024
 *      Author: Stefan.Milojevic
 */
#include <stdbool.h>
#include <stdint.h>
#include "TopLayer.h"

#define DangerousPPM 2200

extern TIM_HandleTypeDef htim11;

volatile bool readFlag = true;
//Messages for sending
char IdleMSG[] = "Sistem ceka na konfiguraciju:";
char PPM_MSG[] = "PPM = ";

void AppInit()
{
	AlarmInit();
	SignalSystemInit();
	AirQualityIncicatorInit();
}

void AppStart()
{
	while(1)
	{

	}
}

//@brief Timer interrupt service routine, happens every 10ms
//@param htim Pointer to timer handler given by cube mx
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//	if(htim == &htim11)
//	{
//		char msg[] = "Prekid se desio";
//		UART_TransmitString(msg);
//	}
//}












