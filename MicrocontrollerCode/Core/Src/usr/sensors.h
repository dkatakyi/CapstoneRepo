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

/**
 * Function name:	CO2Conversion
 * Preconditions:	n/a
 * Postconditiions:	n/a
 * Return type:		n/a
 * Purpose:			n/a
 */
uint16_t CO2Conversion(uint32_t input);

/**
 * Function name:	TempConversion
 * Preconditions:	n/a
 * Postconditiions:	n/a
 * Return type:		n/a
 * Purpose:			n/a
 */
uint16_t TempConversion(uint32_t input);

/**
 * Function name:	CMD2LCD
 * Preconditions:	n/a
 * Postconditiions:	LCD affected
 * Return type:		n/a
 * Purpose:			Send commands to LCD
 */
uint16_t NoiseConversion(uint32_t input);

/**
 * Function name:	CO2_Select
 * Preconditions:	n/a
 * Postconditiions:	LCD affected
 * Return type:		n/a
 * Purpose:			Send commands to LCD
 */
void CO2_Select(void);

/**
 * Function name:	TEMP_Select
 * Preconditions:	n/a
 * Postconditiions:	LCD affected
 * Return type:		n/a
 * Purpose:			Send commands to LCD
 */
void TEMP_Select(void);

/**
 * Function name:	NOISE_Select
 * Preconditions:	n/a
 * Postconditiions:	LCD affected
 * Return type:		n/a
 * Purpose:			Send commands to LCD
 */
void NOISE_Select(void);

/**
 * Function name:	POT_Select
 * Preconditions:	n/a
 * Postconditiions:	LCD affected
 * Return type:		n/a
 * Purpose:			Send commands to LCD
 */
void POT_Select(void);

/**
 * Function name:	ADC_Select
 * Preconditions:	n/a
 * Postconditiions:	LCD affected
 * Return type:		n/a
 * Purpose:			Send commands to LCD
 */
uint32_t ADC_Read(void);

#endif /* SRC_USR_SENSORS_H_ */
