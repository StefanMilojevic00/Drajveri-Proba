/*
 * TopLayer.h
 *
 *  Created on: Apr 12, 2024
 *      Author: Stefan.Milojevic
 */

#ifndef INC_TOPLAYER_H_
#define INC_TOPLAYER_H_

#include <stdbool.h>

#include "main.h"
#include "GasSensor.h"
#include "AlarmSystem.h"
#include "UART.h"
#include "SignalSystem.h"
#include "AirQualityIndicator.h"

//@brief Function to initialize all of the systems peripherals
void AppInit();

//@brief Function to act as a main function, calling all drivers and systems
void AppStart();



#endif /* INC_TOPLAYER_H_ */
