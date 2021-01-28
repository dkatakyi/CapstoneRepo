/*
 * sensors.h
 *
 *  Created on: Jan 5, 2021
 *      Author: danieltakyi
 */

#ifndef SRC_USR_SENSORS_H_
#define SRC_USR_SENSORS_H_

float CO2Conversion(uint32_t input);
float TempConversion(uint32_t input);
float NoiseConversion(uint32_t input);

#endif /* SRC_USR_SENSORS_H_ */
