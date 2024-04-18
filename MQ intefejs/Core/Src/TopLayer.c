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

bool SysTickFlag = false;
volatile bool readFlag = true;

//Messages for sending
static char IdleMSG[] = "System waits for configuration";
static char PPM_MSG[] = "PPM = ";
static char AlertMSG[] = "Dangerous leves of PPM in the room";
static char RoomClearedMSG[] = "Room cleared, it is now safe to return";

LED_Counter led_cnt = {
	    .cnt_led_correct_on = 0,
	    .cnt_led_incorrect_on = 0,
	    .cnt_led_off = 0,

	    .time_led_correct_on = 100,
	    .time_led_incorrect_on = 50,
	    .time_led_off = 300,

	    .led_overflow_flag = true,
	    .correct_led = false,
};

ProgramCounters prog_cnt = {
	    .time_button = 300,
	    .cnt_button = 0,
	    .prog_cnt_press = 0,
	    .prog_cnt_reset = false,
	    .read_button_flag = false,
	    .finish_counting = true,
	    .ref_rate = 0,
	    .update_ref_rate_flag = false,
	    .cnt_ref_rate = 0,
	    .update_param_flag = false,
	    .cnt_clear_room = 0,
	    .time_clear_room = 200,
	    .room_not_safe_flag = false
};

ProgramStateFSM progState = P_IDLE_START;
CountingTasterFSM countState = C_IDLE;
LED_StatusFSM ledState = LED_OFF;


void AppInit()
{
	AlarmInit();
	SignalSystemInit();
	AirQualityIncicatorInit();
	LED_init();
}

void AppStart()
{
	while(1)
	{
			switch(progState)
			{
				case P_IDLE_START:

					UART_TransmitString(IdleMSG);
					progState = P_IDLE;
					break;

				case P_IDLE:

					//Does nothing

					break;

				case P_WORK:

					float PPM = ReadGasSensor();
					bool LED_correct;

					if(PPM < 400)
					{
						LED_correct = false;
					}
					else
					{
						LED_correct = true;
					}

					if(led_cnt.led_overflow_flag == true)
					{
						switch(ledState)
						{
							case LED_OFF:

								LED_Drive(LED_correct);

								break;

							case LED_ON_CORECT:

								LED_Drive(LED_correct);

								break;

							case LED_ON_INCORECT:

								LED_Drive(LED_correct);

								break;
						}
						led_cnt.led_overflow_flag = false;
					}

					if(prog_cnt.update_param_flag == true)
					{
						UART_TransmitString(PPM_MSG);
						UART_TransmitFloat(PPM);
						SetIndicatorLEDs(PPM);

						if(PPM > DangerousPPM)
						{
							UART_TransmitString(AlertMSG);
							AlarmON();
						}
						prog_cnt.update_param_flag = false;
					}
					break;
				}
		}
}


//@brief Timer interrupt service routine, happens every 10ms
//@param htim Pointer to timer handler given by cube mx
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	if(htim == &htim11)
	{
		SysTickFlag = true;

		//Controling room clearing mechanism
		if((prog_cnt.cnt_clear_room >= prog_cnt.time_clear_room) && (prog_cnt.room_not_safe_flag))
		{
			AlarmOFF();
			UART_TransmitString(RoomClearedMSG);
			prog_cnt.cnt_clear_room = 0;
			prog_cnt.room_not_safe_flag = false;
		}

		//Controling single LED:////////////////////////////////////////
		switch(ledState)
		{
			case LED_OFF:

				led_cnt.cnt_led_off++;
				if((led_cnt.cnt_led_off) >= (led_cnt.time_led_off))
				{

					led_cnt.led_overflow_flag = true;
					if(led_cnt.correct_led)
					{
						ledState =  LED_ON_CORECT;
					}else
					{
						ledState = LED_ON_INCORECT;
					}
					led_cnt.cnt_led_off = 0;
					led_cnt.led_overflow_flag = true;
				}

				break;

			case LED_ON_CORECT:

				led_cnt.cnt_led_correct_on++;
				if((led_cnt.cnt_led_correct_on) >= (led_cnt.time_led_correct_on))
				{
					led_cnt.cnt_led_correct_on = 0;
					led_cnt.led_overflow_flag = true;
					ledState = LED_OFF;
				}
				break;

			case LED_ON_INCORECT:

				led_cnt.cnt_led_incorrect_on++;
				if((led_cnt.cnt_led_incorrect_on) >= (led_cnt.time_led_incorrect_on))
				{
					led_cnt.cnt_led_incorrect_on = 0;
					led_cnt.led_overflow_flag = true;
					ledState = LED_OFF;
				}
				break;
		}

		//Controling UART refresh rate://////////////////////////////////////////////
		if(((prog_cnt.ref_rate) != 0))
		{
			prog_cnt.cnt_ref_rate++;
			if((prog_cnt.cnt_ref_rate) >= (prog_cnt.ref_rate))
			{
				prog_cnt.update_param_flag = true;
				prog_cnt.cnt_ref_rate = 0;
			}
		}

		//Controling the signal reading system
		prog_cnt.read_button_flag = ReadSignal(&SysTickFlag);
		switch(countState)
		{
			case C_IDLE:

				if(((prog_cnt.read_button_flag) == true) && (prog_cnt.finish_counting) == true)
				{
					prog_cnt.cnt_button = 0;
					prog_cnt.prog_cnt_press = 1;
					prog_cnt.finish_counting = false;

					countState = C_START;
				}
				break;

			case C_START:

				prog_cnt.cnt_button++;
				UART_TransmitFloat((float)prog_cnt.cnt_button);
				if((prog_cnt.cnt_button) >= (prog_cnt.time_button))
				{
					countState = C_END;

				}
				else
				{
					if(((prog_cnt.read_button_flag) == true))
					{
						prog_cnt.cnt_button = 0;
						prog_cnt.prog_cnt_press++;

						countState = C_START;
					}

				}
				break;

			case C_END:
				prog_cnt.cnt_button = 0;

				switch(prog_cnt.prog_cnt_press)
				{
					case 0:

						break;

					case 1:

						progState = P_WORK;
						prog_cnt.ref_rate = 100;
						break;

					case 2:

						progState = P_WORK;
						prog_cnt.ref_rate = 300;
						break;

					case 3:

						progState = P_WORK;
						prog_cnt.ref_rate = 500;
						break;

					case 4:

						// does nothing because it is so in ability!!
						break;

					case 5:

						progState = P_IDLE_START;
						prog_cnt.ref_rate = 0;
						break;

				}

				prog_cnt.prog_cnt_press = 0;
				prog_cnt.finish_counting = true;
				countState = C_IDLE;
				break;

		}
		prog_cnt.read_button_flag = false;
	}
	SysTickFlag = false;
}












