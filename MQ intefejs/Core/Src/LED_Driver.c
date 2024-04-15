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
    single_led_instance->cnt_led_correct_on = 0;
    single_led_instance->cnt_led_incorrect_on = 0;
    single_led_instance->cnt_led_off = 0;

    single_led_instance->time_led_correct_on = 1000;    // 1 sec
    single_led_instance->time_led_incorrect_on = 500;   // 0.5 sec
    single_led_instance->time_led_off = 3000;           // 3 sec

    single_led_instance->led_overflow_flag = true;

    single_led_instance->led_state = true;
    single_led_instance->correct_led = false;

    single_led_instance->ledStatus = LED_OFF;

    single_led_instance->GPIOx = GPIOx;
    single_led_instance->GPIO_Pin = GPIO_Pin;
}


void UpdateSingleLED(SingleLed* single_led_instance, bool* system_state)
{

	single_led_instance->correct_led = *system_state;
	TimerLED(&single_led_instance);
}

void DriveSignleLED(SingleLed* single_led_instance)
{

	//TimerLED(single_led_instance);

	if((single_led_instance->led_state) == true)
	{
		HAL_GPIO_WritePin(Led_out_GPIO_Port, Led_out_Pin, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(Led_out_GPIO_Port, Led_out_Pin, GPIO_PIN_RESET);
	}
}



// This function set initial state on pins
/*
static void InitSegmentLED()
{
	HAL_GPIO_WritePin(low_green_led_GPIO_Port, low_green_led_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(mid_yellow_led1_GPIO_Port, mid_yellow_led1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(mid_yellow_led2_GPIO_Port, mid_yellow_led2_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(high_blue_led1_GPIO_Port, high_blue_led1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(high_blue_led2_GPIO_Port, high_blue_led2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(high_blue_led3_GPIO_Port, high_blue_led3_Pin, GPIO_PIN_RESET);
}
*/

// This function set properly state on pins

static void TimerLED(SingleLed* timer)
{
// Timer Emulation with Counters
	if(timer->led_overflow_flag == true)
	{
		timer->led_state = !(timer->led_state);
		DriveSignleLED(&timer);
	}

	switch(timer->ledStatus)
	{
		case LED_OFF:
			timer->cnt_led_off++;
			if((timer->cnt_led_off) >= (timer->time_led_off))
			{
				timer->led_overflow_flag = true;
				if(timer->correct_led)
				{
					timer->ledStatus = LED_ON_CORECT;
				}else
				{
					timer->ledStatus = LED_ON_INCORECT;
				}
				timer->cnt_led_off = 0;
				timer->led_overflow_flag = true;
			}

			break;

		case LED_ON_CORECT:
			timer->cnt_led_correct_on++;
			if((timer->cnt_led_correct_on) >= (timer->time_led_correct_on))
			{
				timer->cnt_led_correct_on = 0;
				timer->led_overflow_flag = true;
				timer->ledStatus = LED_OFF;
				timer->led_state = false;
			}
			break;

		case LED_ON_INCORECT:
			timer->cnt_led_incorrect_on++;
			if((timer->cnt_led_incorrect_on) >= (timer->time_led_incorrect_on))
			{
				timer->cnt_led_incorrect_on = 0;
				timer->led_overflow_flag = true;
				timer->ledStatus = LED_OFF;
				timer->led_state = false;
			}

			break;
	}
}


/*
void HandlerSingleLED(struct LED_Timer_Emulator* timer)
{
/////////////  System Indicator //////////////

    if((timer->led_start_flag) == true)
    {
        if((timer->led_overflow_flag) == true)
        {
            if((timer->led_state) == true)
            {
                DriveSignleLED(true);
            }
            else if((timer->led_state) == false)
            {
                DriveSignleLED(false);
            }
        }
    } else if((timer->led_start_flag) == false)
    {
        timer->led_state = false;
        timer->correct_led = false;
        timer->led_overflow_flag = false;

        timer->cnt_led_correct_on = 0;
        timer->cnt_led_incorrect_on = 0;
        timer->cnt_led_off = 0;
        if((timer->led_state) == true)
		{
        	timer->LED_ON_CORECT;
		}
		else if((timer->led_state) == false)
		{
			timer->LED_ON_INCORECT;
		}
    }
}

*/
