/*
 * LedRow.h
 *
 *  Created on: Apr 15, 2024
 *      Author: Stefan.Milojevic
 */

#ifndef INC_LEDROW_H_
#define INC_LEDROW_H_

#include "main.h"

//Structure holding pin configuration for the entire led row used in indication of air quality
typedef struct
{
	GPIO_TypeDef *gpioPortGreen;
	uint16_t gpioPinGreen;

	GPIO_TypeDef *gpioPortYellow1;
	uint16_t gpioPinYellow1;

	GPIO_TypeDef *gpioPortYellow2;
	uint16_t gpioPinYellow2;
	GPIO_TypeDef *gpioPortBlue1;
	uint16_t gpioPinBlue1;

	GPIO_TypeDef *gpioPortBlue2;
	uint16_t gpioPinBlue2;

	GPIO_TypeDef *gpioPortBlue3;
	uint16_t gpioPinBlue3;
} ledRow_t;

//@brief Function to initialize the led row
//param, Gpio ports and pins for all diodes
void LedRowInit(ledRow_t* ledRow,
				GPIO_TypeDef *gpioPortGreen, uint16_t gpioPinGreen,
				GPIO_TypeDef *gpioPortYellow1, uint16_t gpioPinYellow1,
				GPIO_TypeDef *gpioPortYellow2, uint16_t gpioPinYellow2,
				GPIO_TypeDef *gpioPortBlue1, uint16_t gpioPinBlue1,
				GPIO_TypeDef *gpioPortBlue2, uint16_t gpioPinBlue2,
				GPIO_TypeDef *gpioPortBlue3, uint16_t gpioPinBlue3);

//@brief Function to turn on the required number of diodes in a row
//@param ledRow Structure holding the pinout configuration
//@param PPM_Value Value that dictates how many leds will be ON
void LedRowWrite(ledRow_t* ledRow, float PPM_Value);

#endif /* INC_LEDROW_H_ */
