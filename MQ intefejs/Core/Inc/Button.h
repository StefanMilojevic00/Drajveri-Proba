/*
 * Button.h
 *
 *  Created on: Apr 10, 2024
 *      Author: Marko.Manic
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"



//FSM used for debouncing the button
typedef enum {B_IDLE, B_DEBOUNCE, B_DETECT, B_DETECT_IDLE} ButtonDebounceFSM;

//Structure holding the pin configuration of the button and flags used in debouncing
typedef struct
{
	volatile bool btn_press_flag;
	volatile bool btn_cnt_reset;
	volatile bool read_button_flag;
	volatile bool btn_press_detect_flag;

	GPIO_PinState btn_last_state;
	GPIO_PinState active_state;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;

	ButtonDebounceFSM button_state;
}Button_t;


//@brief Function to initialize the button
//@param button_instance Structure holding the button configuration
//@param GPIOx GPIO port of the button
//@param GPIO_Pin pin of the button
void CreateNewButton(Button_t* button_instance, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

//@brief Function to read the button state if it recives a flag to do so
//@param button_instance Structure holding the button configuration
//@param readEnable Flag that indicates is the time for reading has come
//@retval Value indicating if the button is pressed or not
bool ReadButton(Button_t* button_instance, bool* readEnable);

#endif /* INC_BUTTON_H_ */



