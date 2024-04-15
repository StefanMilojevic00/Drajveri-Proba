/*
 * Button.h
 *
 *  Created on: Apr 10, 2024
 *      Author: Marko.Manic
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


typedef enum {B_IDLE, B_DEBOUNCE, B_DETECT, B_DETECT_IDLE} ButtonDebounceFSM;
//static ButtonDebounceFSM btnDeb = B_IDLE;

/*
static struct Counters{
	volatile bool btn_press_flag;
	volatile bool btn_cnt_reset;
	volatile bool btn_polling_flag;
	volatile bool read_button_flag;
	volatile bool btn_press_detect_flag;
}cnt_1;

static struct GPIO_info{
	GPIO_PinState btn_last_state;
	GPIO_PinState active_state;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
}GPIO_info_1;
*/
/*
static struct Counters cnt_1 = {
	.btn_press_flag = false,
	.btn_polling_flag = false,
	.read_button_flag = false,
	.btn_press_detect_flag = false,
	.btn_last_state = GPIO_PIN_RESET,
	.active_state = GPIO_PIN_SET,
};
*/
static struct Button{

	volatile bool btn_press_flag;
	volatile bool btn_cnt_reset;
	volatile bool btn_polling_flag;
	volatile bool read_button_flag;
	volatile bool btn_press_detect_flag;

	GPIO_PinState btn_last_state;
	GPIO_PinState active_state;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;

	ButtonDebounceFSM button_state;
};

void CreateNewButton(struct Button* button_instance, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
//void ButtonInit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
bool ReadButton(struct Button* button_instance, bool* readEnable);

#endif /* INC_BUTTON_H_ */



