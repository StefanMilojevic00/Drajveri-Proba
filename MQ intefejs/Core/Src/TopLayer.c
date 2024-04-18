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

bool SysTickFlag;

volatile bool readFlag = true;
//Messages for sending
static char IdleMSG[] = "System waits for configuration";
static char PPM_MSG[] = "PPM = ";
static char AlertMSG[] = "Dangerous leves of PPM in the room";
static char RoomClearedMSG[] = "Room cleared, it is now safe to return";




typedef struct
{
    volatile uint16_t cnt_led_correct_on;
    volatile uint16_t cnt_led_incorrect_on;
    volatile uint16_t cnt_led_off;

    uint16_t time_led_correct_on;    // 1 sec
    uint16_t time_led_incorrect_on;  // 0.5 sec
    uint16_t time_led_off;           // 3 sec

    volatile bool led_overflow_flag;

 //   volatile bool led_state;   //  true . Led ON
    volatile bool correct_led; //  true . Systme work well

}LED_Counter;

LED_Counter led_cnt = {
	    .cnt_led_correct_on = 0,
	    .cnt_led_incorrect_on = 0,
	    .cnt_led_off = 0,

	    .time_led_correct_on = 100,   // 1 sec
	    .time_led_incorrect_on = 50,  // 0.5 sec
	    .time_led_off = 300,           // 3 sec

	    .led_overflow_flag = true,

	  //  .led_state = true,   //  true . Led ON
	    .correct_led = false, //  true . Systme work well
};


// Struct for counting button press
typedef struct{
	const uint16_t time_button; 	//  Timer overflow time
	volatile uint16_t cnt_button; 	//  Timer emulator
	volatile uint8_t prog_cnt_press; //	Counting number of press button for choosing refresh rate
	volatile bool prog_cnt_reset;	//  It should be set after 3 sec
	volatile bool read_button_flag; //  Purpose of this is for moving througt refresh rate FSM
	volatile bool finish_counting;
	volatile uint16_t ref_rate;
	volatile bool update_ref_rate_flag;  //  Pusrpose of this is to indicate when refresh rate FSM should choose Mode
	// refresh rate //
	volatile uint16_t cnt_ref_rate;
	volatile bool update_param_flag;
	// Buzzer counters:
	volatile uint8_t cnt_clear_room; // Counting the safeguard time when clearing a room of gas
	const uint8_t time_clear_room; // 2 sec - prototype
	volatile bool room_not_safe_flag;
}ProgramCounters;

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
//RefreshRateFSM refRate = R_IDLE;
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

					char msg4[] = "P_IDLE_Start";
					UART_TransmitString(msg4);
					UART_TransmitString(IdleMSG);
					progState = P_IDLE;

					break;

				case P_IDLE:

					char msg5[] = "P_IDLE";
					//UART_TransmitString(msg5);


					break;

				case P_WORK:

					char msg6[] = "P_WORK";
					//UART_TransmitString(msg6);
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
							LED_Drive(false);
							break;

						case LED_ON_CORECT:
							LED_Drive(true);
							break;

						case LED_ON_INCORECT:
							LED_Drive(true);
							break;
						}

						led_cnt.led_overflow_flag = false;
					}

						if(prog_cnt.update_param_flag == true)
						{
							char msg10[] = "+++++++++++++++";
							UART_TransmitString(msg10);
							//float PPM = ReadGasSensor();
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
		//char msg[] = "Prekid se desio";
		//UART_TransmitString(msg);

		/////////////////////////////////////////////////////////

		switch(ledState)
		{
			case LED_OFF:
				led_cnt.cnt_led_off++;
			//	HAL_GPIO_WritePin(Led_out_GPIO_Port, Led_out_Pin, GPIO_PIN_RESET);
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
				//	led_cnt.led_state = true;
				}

				break;

			case LED_ON_CORECT:
				led_cnt.cnt_led_correct_on++;
		//		HAL_GPIO_WritePin(Led_out_GPIO_Port, Led_out_Pin, GPIO_PIN_SET);
				if((led_cnt.cnt_led_correct_on) >= (led_cnt.time_led_correct_on))
				{
					led_cnt.cnt_led_correct_on = 0;
					led_cnt.led_overflow_flag = true;
					ledState = LED_OFF;
				//	led_cnt.led_state = false;

				}
				break;

			case LED_ON_INCORECT:
				led_cnt.cnt_led_incorrect_on++;
			//	HAL_GPIO_WritePin(Led_out_GPIO_Port, Led_out_Pin, GPIO_PIN_SET);
				if((led_cnt.cnt_led_incorrect_on) >= (led_cnt.time_led_incorrect_on))
				{
					led_cnt.cnt_led_incorrect_on = 0;
					led_cnt.led_overflow_flag = true;
					ledState = LED_OFF;
				//	led_cnt.ledStatus = LED_OFF;
				//	led_cnt.led_state = false;
				//	HAL_GPIO_WritePin(Led_out_GPIO_Port, Led_out_Pin, GPIO_PIN_RESET);
				}


		}
		//////////////////////////////////////////////////////////
		if(((prog_cnt.ref_rate) != 0))
		{
			prog_cnt.cnt_ref_rate++;
			if((prog_cnt.cnt_ref_rate) >= (prog_cnt.ref_rate))
			{
				prog_cnt.update_param_flag = true;
				prog_cnt.cnt_ref_rate = 0;
			}
		}
		//////////////////////////////////////////
		SysTickFlag = true;
		//prog_cnt.update_ref_rate_flag = true;
		if((prog_cnt.cnt_clear_room >= prog_cnt.time_clear_room) && (prog_cnt.room_not_safe_flag))
		{
			AlarmOFF();
			UART_TransmitString(RoomClearedMSG);
			prog_cnt.cnt_clear_room = 0;
			prog_cnt.room_not_safe_flag = false;
		}
		char msg11[] = "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT";
		prog_cnt.read_button_flag = ReadSignal(&SysTickFlag);

		switch(countState)
		{
			case C_IDLE:

			//	char msg1[] = "C_IDLE";
			//	UART_TransmitString(msg1);
				if(((prog_cnt.read_button_flag) == true) && (prog_cnt.finish_counting) == true)
				{
					prog_cnt.cnt_button = 0;
					prog_cnt.prog_cnt_press = 1;
					prog_cnt.finish_counting = false;

					countState = C_START;
				}

				break;

			case C_START:

				char msg2[] = "C_START";
			//	UART_TransmitString(msg2);

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
				char msg3[] = "C_END";
				//UART_TransmitString(msg3);
				prog_cnt.cnt_button = 0;

				switch(prog_cnt.prog_cnt_press)
				{
					case 0:

						break;

					case 1:

						progState = P_WORK;
						prog_cnt.ref_rate = 100;
						//prog_cnt.update_ref_rate_flag = true; //added
						break;

					case 2:

						progState = P_WORK;
						prog_cnt.ref_rate = 300;
						//prog_cnt.update_ref_rate_flag = true; //added
						break;

					case 3:

						progState = P_WORK;
						prog_cnt.ref_rate = 500;
						//prog_cnt.update_ref_rate_flag = true; //added
						break;

					case 4:
						// does nothing because it is so in ability

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

//		if((prog_cnt.ref_rate) != 0)
//		{
//			prog_cnt.cnt_ref_rate++;
//			if((prog_cnt.cnt_ref_rate) >= (prog_cnt.ref_rate))
//			{
//				prog_cnt.update_param_flag = true;
//				prog_cnt.cnt_ref_rate = 0;
//			}
//		}
		SysTickFlag = false;
	}
}












