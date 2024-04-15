/*
 * Buzzer.h
 *
 *  Created on: Apr 11, 2024
 *      Author: Stefan.Milojevic
 */

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include "main.h"

//Structure for holding pinout configuration
typedef struct
{
	GPIO_TypeDef *gpioPort; //GPIO port for Buzzer
	uint16_t gpioPin; //Buzzer analog pin
} Buzzer_t;

//@brief Funtion to initialize Buzzer
//@param BuzzerStruct Structure holding the configuration
//@param gpioPort Buzzer port
//@param gpioPin Buzzer pin
void Buzzer_init(Buzzer_t* BuzzerStruct, GPIO_TypeDef* gpioPort, uint16_t dataPin);

void BuzzerWritePin(Buzzer_t* BuzzerStruct, GPIO_PinState toWrite);



#endif /* INC_BUZZER_H_ */
