/*
 * CommMod.c
 *
 *  Created on: Jan 5, 2021
 *      Author: danieltakyi
 */

#include "CommMod.h"

void printString(const char* mess)
{
	int i = 0;
	HAL_StatusTypeDef st;
	uint8_t cliBufferTX[100];

	while(huart2.gState == HAL_UART_STATE_BUSY_TX){}

	for(const char* p = mess; *p; ++p)
	{
		cliBufferTX[i] = *p;
		i++;
	}

	st = HAL_UART_Transmit(&huart2, cliBufferTX, i, 1000);
	if(st != HAL_OK)
	{
		Error_Handler();
	}

}
