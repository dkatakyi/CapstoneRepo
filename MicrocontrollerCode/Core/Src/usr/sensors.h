/*
 * sensors.h
 *
 *  Created on: Jan 5, 2021
 *      Author: danieltakyi
 */

#ifndef SRC_USR_SENSORS_H_
#define SRC_USR_SENSORS_H_

#include <stdint.h>
#include "main.h"


extern ADC_HandleTypeDef hadc1;



void CO2_Select(void);

void TEMP_Select(void);

void NOISE_Select(void);

void POT_Select(void);

uint32_t ADC_Read(void);

#endif /* SRC_USR_SENSORS_H_ */
