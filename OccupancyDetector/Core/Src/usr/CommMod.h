/*
 * CommMod.h
 *
 *  Created on: Jan 5, 2021
 *      Author: danieltakyi
 */

#ifndef SRC_USR_COMMMOD_H_
#define SRC_USR_COMMMOD_H_

#include "main.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern UART_HandleTypeDef huart2;

/**
 Function name: printString
 Preconditions: n/a
 Postconditiions: character array transmitted
 Return type: n/a
 Purpose: Print out a message to terminal via USART transmit
 */
void printString(const char* mess);


#endif /* SRC_USR_COMMMOD_H_ */
