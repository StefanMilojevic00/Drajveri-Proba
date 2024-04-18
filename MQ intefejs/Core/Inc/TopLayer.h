/*
 * TopLayer.h
 *
 *  Created on: Apr 12, 2024
 *      Author: Stefan.Milojevic
 */

#ifndef INC_TOPLAYER_H_
#define INC_TOPLAYER_H_

#include <stdbool.h>
#include "LED_Handler.h"
#include "main.h"
#include "GasSensor.h"
#include "AlarmSystem.h"
#include "UART.h"
#include "SignalSystem.h"
#include "AirQualityIndicator.h"



typedef enum {P_IDLE, P_IDLE_START, P_WORK} ProgramStateFSM;
//typedef enum {R_IDLE, R_S1, R_S3, R_S5, R_PRESS_4, R_PRESS_5} RefreshRateFSM;
typedef enum {C_IDLE, C_START, C_END} CountingTasterFSM;

typedef enum {LED_OFF, LED_ON_CORECT, LED_ON_INCORECT} LED_StatusFSM;
//@brief Function to initialize all of the systems peripherals


void AppInit();

//@brief Function to act as a main function, calling all drivers and systems
void AppStart();



#endif /* INC_TOPLAYER_H_ */
