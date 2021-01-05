/*
 * lcd.c
 *
 *  Created on: Jan 5, 2021
 *      Author: danieltakyi
 */

 #include "stm32f1xx.h"
 #include "lcd.h"


void lcd_IO_init (void)
{

	//Enable peripheral clocks for ports B and C

	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN;

	//Set the config and mode bits for Port B bit 0, 1, and 5 so they will
	// be push-pull outputs (up to 50 MHz)
	GPIOB->CRL = 0x44344433;

	//Set the config and mode bits for Port C bits 7 down to 0 so they will
	// be push-pull outputs (up to 50 MHz)
	GPIOC->CRL = 0x33333333;

}

void CMD2LCD(uint8_t data)
{

	GPIOB->BSRR = LCD_CM_ENA;
	GPIOC->ODR &= 0xFF00;
	GPIOC->ODR |= data;

	HAL_Delay(50);
	//delay(8000);

	GPIOB->BSRR = LCD_CM_DIS;

	HAL_Delay(180);
	//delay(80000);

}

void lcd_init(void)
{
	for(int j = 0; j < 3; j++)
	{
		CMD2LCD(0X38);
		HAL_Delay(80);
		//delay(24600);
	}

	CMD2LCD(0X38);
	HAL_Delay(80);
	//delay(24600);

	CMD2LCD(0X0F);
	HAL_Delay(80);
	//delay(24600);

	CMD2LCD(0X01);
	HAL_Delay(80);
	//delay(24600);

	CMD2LCD(0X06);
	HAL_Delay(80);
	//delay(24600);

}

void DAT2LCD(uint8_t data)
{
	GPIOB->BSRR = LCD_DM_ENA;
	GPIOC->ODR &= 0xFF00;
	GPIOC->ODR |= data;
	HAL_Delay(50);
	//delay(8000);

	GPIOB->BSRR = LCD_DM_DIS;
	HAL_Delay(180);
	//delay(80000);

}

void print2LCD(uint64_t word)
{
	//assumes that word is presented the function backwards;
	//if you want to present a word to the function in its order of characters, then a mirror function is needed
	//
	//to mirror, you need to shift and copy adeptly. use multiples of 8

	while(word != 0)
	{
		DAT2LCD(word);
		word >>= 0x08;
	}
}

void dipSW2LCD(uint8_t val)
{
	switch(val){
	case 0x00:
		print2LCD(0x30);
		break;

	case 0x01:
		print2LCD(0x31);
		break;

	case 0x02:
		print2LCD(0x32);
		break;

	case 0x03:
		print2LCD(0x33);
		break;

	case 0x04:
		print2LCD(0x34);
		break;

	case 0x05:
		print2LCD(0x35);
		break;

	case 0x06:
		print2LCD(0x36);
		break;

	case 0x07:
		print2LCD(0x37);
		break;

	case 0x08:
		print2LCD(0x38);
		break;

	case 0x09:
		print2LCD(0x39);
		break;

	case 0x0A:
		print2LCD(0x41);
		break;

	case 0x0B:
		print2LCD(0x42);
		break;

	case 0x0C:
		print2LCD(0x43);
		break;

	case 0x0D:
		print2LCD(0x44);
		break;

	case 0x0E:
		print2LCD(0x45);
		break;

	case 0x0F:
		print2LCD(0x46);
		break;

	default:
		break;
	}

}
