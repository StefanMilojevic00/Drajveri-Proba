/*
 * LED_Driver.h
 *
 *  Created on: Apr 9, 2024
 *      Author: Marko.Manic
 */



#ifndef INC_LED_DRIVER_H_
#define INC_LED_DRIVER_H_

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "main.h"


//Structure for holding the pin configuration
typedef struct{
    GPIO_TypeDef* GPIOx;
    uint16_t GPIO_Pin;
}SingleLed;

//@brief Function to initialize the pin configuration for the LED used to signify if the system works well or not
//@param single_led_instance Structure that will hold the pin configuration
//@param GPIOx LED port
//@param GPIO_Pin LED pin
void CreateNewSingleLED(SingleLed* single_led_instance, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

//@brief Function to write 1 or zero on LED pin based on the status of the whole system
//@param single_led_instance Structure holding the pin configuration
//@param state The state of the system - true if it works as intended, false if it encounters an error
void UpdateSingleLED(SingleLed* single_led_instance, bool state);



#endif /* INC_LED_DRIVER_H_ */
