/*
 * LED_Driver.c
 *
 *  Created on: Apr 9, 2024
 *      Author: Marko.Manic
 */

#include "main.h"
#include "LED_Driver.h"


void CreateNewSingleLED(SingleLed* single_led_instance, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    single_led_instance->GPIOx = GPIOx;
    single_led_instance->GPIO_Pin = GPIO_Pin;
}

void UpdateSingleLED(SingleLed* single_led_instance, bool state)
{
	if(state == true)
	{
		HAL_GPIO_WritePin(single_led_instance->GPIOx, single_led_instance->GPIO_Pin, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(single_led_instance->GPIOx, single_led_instance->GPIO_Pin, GPIO_PIN_RESET);
	}
}


