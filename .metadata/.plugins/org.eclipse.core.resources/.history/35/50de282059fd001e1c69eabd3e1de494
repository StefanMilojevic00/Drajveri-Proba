/*
 * Buzzer.c
 *
 *  Created on: Apr 11, 2024
 *      Author: Stefan.Milojevic
 */

#include "Buzzer.h"

void Buzzer_init(Buzzer_t* BuzzerStruct, GPIO_TypeDef* gpioPort, uint16_t gpioPin)
{
	BuzzerStruct->gpioPort = gpioPort;
	BuzzerStruct->gpioPin = gpioPin;
}

void BuzzerWritePin(Buzzer_t* BuzzerStruct, GPIO_PinState toWrite)
{
	HAL_GPIO_WritePin(BuzzerStruct->gpioPort, BuzzerStruct->gpioPin, toWrite);
}
