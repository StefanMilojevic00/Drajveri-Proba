/*
 * LED.h
 *
 *  Created on: Apr 15, 2024
 *      Author: Marko.Manic
 */

#ifndef INC_LED_HANDLER_H_
#define INC_LED_HANDLER_H_

#include "main.h"
#include "LED_Driver.h"





void LED_init();
void LED_Drive(bool state);

//void LED_init(struct SingleLed* led_instance);

#endif /* INC_LED_HANDLER_H_ */
//struct Button btn_1;
//CreateNewButton(&btn_1, Btn_pin_GPIO_Port, Btn_pin_Pin);
