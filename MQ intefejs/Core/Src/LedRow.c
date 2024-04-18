/*
 * LedRow.c
 *
 *  Created on: Apr 15, 2024
 *      Author: Stefan.Milojevic
 */

#include "LedRow.h"



void LedRowInit(ledRow_t* ledRow,
				GPIO_TypeDef *gpioPortGreen, uint16_t gpioPinGreen,
				GPIO_TypeDef *gpioPortYellow1, uint16_t gpioPinYellow1,
				GPIO_TypeDef *gpioPortYellow2, uint16_t gpioPinYellow2,
				GPIO_TypeDef *gpioPortBlue1, uint16_t gpioPinBlue1,
				GPIO_TypeDef *gpioPortBlue2, uint16_t gpioPinBlue2,
				GPIO_TypeDef *gpioPortBlue3, uint16_t gpioPinBlue3)
{
	ledRow->gpioPortGreen = gpioPortGreen;
	ledRow->gpioPinGreen = gpioPinGreen;

	ledRow->gpioPortYellow1 = gpioPortYellow1;
	ledRow->gpioPinYellow1 = gpioPinYellow1;

	ledRow->gpioPortYellow2 = gpioPortYellow2;
	ledRow->gpioPinYellow2 = gpioPinYellow2;

	ledRow->gpioPortBlue1 = gpioPortBlue1;
	ledRow->gpioPinBlue1 = gpioPinBlue1;

	ledRow->gpioPortBlue2 = gpioPortBlue2;
	ledRow->gpioPinBlue2 = gpioPinBlue2;

	ledRow->gpioPortBlue3 = gpioPortBlue3;
	ledRow->gpioPinBlue3 = gpioPinBlue3;
}

void LedRowWrite(ledRow_t* ledRow, float PPM_Value)
{
	if(PPM_Value > 400)
	{
		HAL_GPIO_WritePin(ledRow->gpioPortGreen, ledRow->gpioPinGreen, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(ledRow->gpioPortGreen, ledRow->gpioPinGreen, GPIO_PIN_RESET);
	}

	if(PPM_Value > 600)
	{
		HAL_GPIO_WritePin(ledRow->gpioPortYellow1, ledRow->gpioPinYellow1, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(ledRow->gpioPortYellow1, ledRow->gpioPinYellow1, GPIO_PIN_RESET);
	}

	if(PPM_Value > 1200)
	{
		HAL_GPIO_WritePin(ledRow->gpioPortYellow2, ledRow->gpioPinYellow2, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(ledRow->gpioPortYellow2, ledRow->gpioPinYellow2, GPIO_PIN_RESET);
	}

	if(PPM_Value > 1800)
	{
		HAL_GPIO_WritePin(ledRow->gpioPortBlue1, ledRow->gpioPinBlue1, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(ledRow->gpioPortBlue1, ledRow->gpioPinBlue1, GPIO_PIN_RESET);
	}

	if(PPM_Value > 2400)
	{
		HAL_GPIO_WritePin(ledRow->gpioPortBlue2, ledRow->gpioPinBlue2, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(ledRow->gpioPortBlue2, ledRow->gpioPinBlue2, GPIO_PIN_RESET);
	}

	if(PPM_Value > 3000)
	{
		HAL_GPIO_WritePin(ledRow->gpioPortBlue3, ledRow->gpioPinBlue3, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(ledRow->gpioPortBlue3, ledRow->gpioPinBlue3, GPIO_PIN_RESET);
	}
}
