/*
 * LED.c
 *
 *  Created on: Apr 15, 2024
 *      Author: Marko.Manic
 */

#include "LED_Handler.h"

void LED_init()
{
	CreateNewSingleLED(&new_led, Led_out_GPIO_Port, Led_out_Pin);
}
void LED_Drive(bool* system_state)
{
	UpdateSingleLED(&new_led, &system_state);
}