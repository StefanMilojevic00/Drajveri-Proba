/*
 * LED_Driver.h
 *
 *  Created on: Apr 9, 2024
 *      Author: Marko.Manic
 */



#ifndef INC_LED_DRIVER_H_
#define INC_LED_DRIVER_H_

#include "main.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>



typedef struct{
//    volatile uint16_t cnt_led_correct_on;
//    volatile uint16_t cnt_led_incorrect_on;
//    volatile uint16_t cnt_led_off;
//
//    uint16_t time_led_correct_on;    // 1 sec
//    uint16_t time_led_incorrect_on;  // 0.5 sec
//    uint16_t time_led_off;           // 3 sec
//
//    volatile bool led_overflow_flag;
//
//    volatile bool led_state;   //  true -> Led ON
//    volatile bool correct_led; //  true -> Systme work well
//
//    // LED status state machine
//    LED_StatusFSM ledStatus;

    // GPIO configuration
    GPIO_TypeDef* GPIOx;
    uint16_t GPIO_Pin;
}SingleLed;

//static void DriveSegmentLED(uint8_t LED_status); // izdvojiti

//void TimerLED(SingleLed* single_led_instance);
void UpdateSingleLED(SingleLed* single_led_instance, bool state);




//void HandlerSingleLED(struct LED_Timer_Emulator* timer);


void CreateNewSingleLED(SingleLed* single_led_instance, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void DriveSignleLED(bool state);

//void CreateNewSegmentLED(struct SegmentLED* segment_led_instance);
//void DriveSegmentLED(bool* setState);

//bool ReadButton(struct Button* button_instance, bool readEnable);


#endif /* INC_LED_DRIVER_H_ */
