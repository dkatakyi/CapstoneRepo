/*
 * sensors.h
 *
 *  Created on: Jan 5, 2021
 *      Author: danieltakyi
 * Description: This file contains all functions needed to
 * 				interface to the sensor module
 *
 */

#ifndef SRC_USR_SENSORS_H_
#define SRC_USR_SENSORS_H_


#include <stdint.h>
#include "main.h"

extern ADC_HandleTypeDef hadc1;

uint16_t CO2Conversion(uint32_t input);

uint16_t TempConversion(uint32_t input);

uint16_t NoiseConversion(uint32_t input);

void CO2_Select(void);

void TEMP_Select(void);

void NOISE_Select(void);

void POT_Select(void);

uint32_t ADC_Read(void);

#endif /* SRC_USR_SENSORS_H_ */
