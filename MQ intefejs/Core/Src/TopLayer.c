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
volatile float PPM;

//Messages for sending
static char IdleMSG[] = "System waits for configuration";
static char PPM_MSG[] = "PPM = ";
static char AlertMSG[] = "Dangerous leves of PPM in the room";
static char RoomClearedMSG[] = "Room cleared, it is now safe to return";
static char S1WorkStateMSG[] = "S1 work regime selected";
static char S3WorkStateMSG[] = "S3 work regime selected";
static char S5WorkStateMSG[] = "S5 work regime selected";
static char FAN_ON[] = "FAN started";
static char FAN_OFF[] = "FAN stoped";


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

const char* cmdStrings[] = {

	//	"INVALID_COMMAND", // cmd_0

		"IDLE",			 // cmd_0
		"WORK_S1",	 	 // cmd_1
		"WORK_S3",		 // cmd_2
		"WORK_S5",		 // cmd_3

		"READ_MQ_SENSOR",// cmd_4

		"SEND_MQ_DATA",	 // cmd_5

		"FAN_ON",		 // cmd_6
		"FAN_OFF",		 // cmd_7

		"ALARM_ON",	   	 // cmd_8
		"ALARM_OFF",  	 // cmd_9

		"LED_ON",		 // cmd_10
		"LED_OFF",		 // cmd_11

		"SEGMENT_0",	 // cmd_12
		"SEGMENT_1",	 // cmd_13
		"SEGMENT_2",	 // cmd_14
		"SEGMENT_3",	 // cmd_15
		"SEGMENT_4",	 // cmd_16
		"SEGMENT_5",	 // cmd_17
		"SEGMENT_6", 	 // cmd_18

};

ProgramStateFSM progState = P_IDLE_START;
CountingTasterFSM countState = C_IDLE;
LED_StatusFSM ledState = LED_OFF;
UART_commandsFSM uartCmdState;

void AppInit()
{
	AlarmInit();
	SignalSystemInit();
	AirQualityIncicatorInit();
	LED_init();
}



uint8_t cmd_code;
char* readFromSerial;

char* cmd_test = "WORK_S1";
uint8_t num_of_codes = 4;


char* readFromSerial;
uint8_t cmd_find = 0;
bool result = false;
const uint8_t len_of_array = 4;
bool first_time = false;

void AppStart()
{
	while(1)
	{
		if(first_time == false)
		{
			result = StringCompareFromUART(cmd_test, &cmdStrings, len_of_array, &cmd_find);
			UART_TransmitString("Proslo\n");
			if(result == true)
			{
				uartCmdState = cmd_find;
				UART_TransmitString("ACK\n");
				SendACK();

			}
			first_time = true;
		}



			       //       (char* cmp_cmd, char* cmdStrings[], bool* ret_val)


			switch(progState)
			{
				case P_IDLE_START:

					UART_TransmitString(IdleMSG);
					SetIndicatorLEDs(0); //resets the indicator
					progState = P_IDLE;
					break;

				case P_IDLE:

					//Does nothing, holds the program here until it is configured

					break;

				case P_WORK:

					PPM = ReadGasSensor();

					if(PPM < 400)
					{
						led_cnt.correct_led = false;
					}
					else
					{
						led_cnt.correct_led  = true;
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

		//Controling room clearing mechanism////////////////////////////////
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
					}
					else
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
						UART_TransmitString(S1WorkStateMSG);
						prog_cnt.ref_rate = 100;

						break;

					case 2:

						progState = P_WORK;
						UART_TransmitString(S3WorkStateMSG);
						prog_cnt.ref_rate = 300;

						break;

					case 3:

						progState = P_WORK;
						UART_TransmitString(S5WorkStateMSG);
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




bool StringCompareFromUART(char* cmp_cmd, char** cmdStrings, const uint8_t array_element, uint8_t* ret_val)
{
  bool find = false;
  bool stop_flag = false;
  uint8_t iterator = 0;
  do
	{
	  if (((strcmp(cmp_cmd, cmdStrings[iterator])) == 0) && (find == false))
		{
		  if(iterator == 0)
		  {
			  find = true;
			  stop_flag = true;
			  *ret_val = iterator;

			 // return find;
		  }
		  *ret_val = iterator;

		//  printf("Uslo\n");
		  UART_TransmitString("Uslo\n");
		//  printf(cmp_cmd);
		  UART_TransmitFloat((float)iterator);
	//	  printf("\n");
		  UART_TransmitString("\n");
		  find = true;
		  stop_flag = true;
		}
        else
        {
            iterator++;
      //      printf("Nije: %d\n", iterator);


        }

	}while ((stop_flag == false) || (iterator < array_element));

    return find;
}


void SendACK()
{
	switch(uartCmdState)
	{
		case cmd_0:

			progState = P_IDLE_START;

			break;

		case cmd_1:

			progState = P_WORK;
			prog_cnt.ref_rate = 100;

			break;

		case cmd_2:

			progState = P_WORK;
			prog_cnt.ref_rate = 300;


			break;

		case cmd_3:

			progState = P_WORK;
			prog_cnt.ref_rate = 500;

			break;

		case cmd_4:

			PPM = ReadGasSensor();

			break;

		case cmd_5:

			UART_TransmitFloat(PPM);

			break;


		case cmd_6:

			UART_TransmitString(FAN_ON);

			break;

		case cmd_7:

			UART_TransmitString(FAN_OFF);

			break;


		case cmd_8:

			AlarmON();

			break;

		case cmd_9:

			AlarmOFF();

			break;

		case cmd_10:

			LED_Drive(true);

			break;

		case cmd_11:

			LED_Drive(false);

			break;


		case cmd_12:

			SetIndicatorLEDsNum(0);

			break;

		case cmd_13:

			SetIndicatorLEDsNum(1);

			break;

		case cmd_14:

			SetIndicatorLEDsNum(2);

			break;

		case cmd_15:

			SetIndicatorLEDsNum(3);

			break;


		case cmd_16:

			SetIndicatorLEDsNum(4);

			break;

		case cmd_17:

			SetIndicatorLEDsNum(5);

			break;


		case cmd_18:

			SetIndicatorLEDsNum(6);

			break;

		case cmd_19:
			// reserved

			break;

		case cmd_20:

			// reserved

			break;
	}
}


/*
int main ()
{
    int cmd_find = 0;
    int result = StringCompareFromUART(cmd_0, &cmdStrings, num_of_codes, &cmd_find);

    if(result != 0)
    {
            printf("Nadjeno: %d\n", cmd_find);
    }
    return 0;
}

	//	StringCompareFromUART(cmd_0, cmdStrings[4], &cmd_find);
		       //       (char* cmp_cmd, char* cmdStrings[], bool* ret_val)
		//UART_TransmitString("Proslo\n");


*/

