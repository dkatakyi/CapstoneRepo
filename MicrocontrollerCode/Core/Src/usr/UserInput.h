/*
 * UserInput.h
 *
 *  Created on: Jan 5, 2021
 *      Author: danieltakyi
 * Description: This file contains all functions needed to
 * 				interface to the sensor module
 *
 */

#ifndef SRC_USR_USERINPUT_H_
#define SRC_USR_USERINPUT_H_

#include <stdint.h>
#include "main.h"

/**
 * Function name:	roomSelect
 * Preconditions:	System is initialized
 * Postconditiions:	n/a
 * Return type:		Character pointer
 * Purpose:			Returns a room name depending on the ADC value coming in
 */
char * roomSelect(uint16_t);

#endif /* SRC_USR_USERINPUT_H_ */
