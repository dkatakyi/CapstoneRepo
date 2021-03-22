/*
 * sensors.c
 *
 *  Created on: Jan 5, 2021
 *      Author: danieltakyi
 */

#include "sensors.h"


uint16_t CO2Conversion(uint32_t input)
{
 if(input == 0)
 {
  return 0; /*this should print fault*/
 }
 else if((input) < 400)  /*preheating voltage is from 0.2 to 0.4 */
 {
  return -1; /* this should print "preheating CO2"*/
 }
 else 
 {
  uint16_t voltagedif = (input - 400) * 40 / 16; /*this is for voltage to PPM conversion*/
  return voltagedif - 1000;
  }
 /*CO2 has a 100ms delay before looping*/
}

uint16_t TempConversion(uint32_t input)
{
  return input / 10;   /* voltage to degree celsius conversion*/
  /* has an 500ms delay before looping*/
 }

uint16_t NoiseConversion(uint32_t input)
{
 uint16_t PinVoltage;
//  PinVoltage = (input) / 1024.0 * 5.0;   /* 5.0 is voltage that is powering sensor */
//  return PinVoltage * 50.0; /* 50.0 is voltage to dB conversion value */
 /* has an 125ms delay before looping*/

//input = input * 50 / 1000;

 input = input - 600;
 input /= 20;
 input += 30;
 input -= 8;
 return input;

}

void CO2_Select(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_1;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
}

void TEMP_Select(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_4;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
}

void NOISE_Select(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_6;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
}

void POT_Select(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_7;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
}

uint32_t ADC_Read(void)
{
	uint32_t temp;
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion (&hadc1, 1000);
	temp = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);
	return temp;
}

