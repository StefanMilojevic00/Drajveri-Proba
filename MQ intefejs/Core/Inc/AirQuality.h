/*
 * AirQuality.h
 *
 *  Created on: Apr 9, 2024
 *      Author: Marko.Manic
 */

#ifndef INC_AIRQUALITY_H_
#define INC_AIRQUALITY_H_

#include "main.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define ERROR_CONDITION_1 (index < 0)
#define ERROR_CONDITION_2 (index > 0 && index < MINIMAL_VALUE_AQ)

typedef enum {Z0, Z1, Z2, Z3, Z4, Z5, Z6} AirQualityZoneFSM;
static const uint16_t AirQualityMaxIndexMap[] = {0, 600, 1200, 1800, 2400, 3000};
static const uint8_t MINIMAL_VALUE_AQ = 10;
static char* ErrorMessages[] = {
	    "Error Code: [0] < System work well :D >",
	    "Error Code: [1] < Error Message: Data is negative! >",
	    "Error Code: [2] < Error Message: Data is too low! >"
	};
struct AirQuality{
	char* error_message;
	bool error_flag;
	uint8_t error_code;
	AirQualityZoneFSM AirQualityZone;
};

static void ChooseAirQualityZone(struct AirQuality* air_quality_instance, uint16_t* index_value);

char* GetAirQualityError(struct AirQuality* air_quality_instance);
void CreateNewAirQuality(struct AirQuality* air_quality_instance);
bool GetAirQuality(struct AirQuality* air_quality_instance, uint16_t* input_param ,uint8_t* return_value);
char* GetErrorCode(struct AirQuality* air_quality_instance);

#endif /* INC_AIRQUALITY_H_ */