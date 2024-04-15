/*
 * AirQuality.c
 *
 *  Created on: Apr 9, 2024
 *      Author: Marko.Manic
 */



// This method set polution zone in function of polution index
#include "AirQuality.h"

extern char* ErrorMessages[];

static void ChooseAirQualityZone(struct AirQuality* air_quality_instance, uint16_t* index_value)
{
	uint16_t index = *index_value;
	uint8_t i;
	uint8_t max_index = (sizeof(AirQualityMaxIndexMap)/2);
	for(i = 0; i < max_index; i++)
	{
		uint16_t temp = AirQualityMaxIndexMap[i];

		if(index > temp)
		{
			continue;
		}
		else if(index <= temp)
		{
			air_quality_instance->AirQualityZone = i;
			break;
		}
	}
	if ERROR_CONDITION_1
	{
		air_quality_instance->error_flag = true;
		air_quality_instance->error_code = 1;
	}
	else if ERROR_CONDITION_2
	{
		air_quality_instance->error_flag = true;
		air_quality_instance->error_code = 2;
		//	strcpy(air_quality_instance->error_message, "Error Code: [2] < Error Message: Data is to low! > ");
	}
	else
	{
		air_quality_instance->error_flag = false;
		air_quality_instance->error_code = 0;
	}
}

// Function to get air quality
bool GetAirQuality(struct AirQuality* air_quality_instance, uint16_t* input_param ,uint8_t* return_value) {

	ChooseAirQualityZone(air_quality_instance, input_param);

    *return_value = air_quality_instance->AirQualityZone;

    return  air_quality_instance->error_flag;
}

//////////////////  Doesn't work /////////////////////
char* GetAirQualityError(struct AirQuality* air_quality_instance) {

   // strcpy(air_quality_instance->error_message, Error_messages[air_quality_instance->error_code]);
	char* mess = air_quality_instance->error_message = ErrorMessages[air_quality_instance->error_code];

    //return "Error Code: [0] < System work well :D > \r\n";

	//strcpy(mess, ErrorMessages[air_quality_instance->error_code]);
	return  mess;
}

void CreateNewAirQuality(struct AirQuality* air_quality_instance)
{
	air_quality_instance->error_message = ErrorMessages[air_quality_instance->error_code];
	air_quality_instance->error_flag = false;
	air_quality_instance->AirQualityZone = Z0;
	air_quality_instance->error_code = 0;
}
//////////////////  Doesn't work /////////////////////
char* GetErrorCode(struct AirQuality* air_quality_instance)
{
	char* mess;
	uint8_t code_n = air_quality_instance->error_code;
	strcpy(mess, ErrorMessages[code_n]);
	return mess;
}