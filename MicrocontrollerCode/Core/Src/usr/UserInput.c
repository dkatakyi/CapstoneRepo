/*
 * UserInput.c
 *
 *  Created on: Jan 5, 2021
 *      Author: danieltakyi
 */

#include "UserInput.h"

char * roomSelect(uint16_t pot)
{
	if(pot < 0x555)
	{
		return "ed435";
	}
	else if(pot < 0xAAA)
	{
		return "ed486";
	}
	else if(pot < 0xFFF)
	{
		return "cl110";
	}
	else
	{
		return "err";
	}
}

