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
	HAL_Delay(5);
	//delay(8000);

	GPIOB->BSRR = LCD_DM_DIS;
	HAL_Delay(20);
	//delay(80000);

}

void dipSW2LCD(uint8_t val)
{
	switch(val){
	case 0x00:
		DAT2LCD(0x30);
		break;

	case 0x01:
		DAT2LCD(0x31);
		break;

	case 0x02:
		DAT2LCD(0x32);
		break;

	case 0x03:
		DAT2LCD(0x33);
		break;

	case 0x04:
		DAT2LCD(0x34);
		break;

	case 0x05:
		DAT2LCD(0x35);
		break;

	case 0x06:
		DAT2LCD(0x36);
		break;

	case 0x07:
		DAT2LCD(0x37);
		break;

	case 0x08:
		DAT2LCD(0x38);
		break;

	case 0x09:
		DAT2LCD(0x39);
		break;

	case 0x0A:
		DAT2LCD(0x41);
		break;

	case 0x0B:
		DAT2LCD(0x42);
		break;

	case 0x0C:
		DAT2LCD(0x43);
		break;

	case 0x0D:
		DAT2LCD(0x44);
		break;

	case 0x0E:
		DAT2LCD(0x45);
		break;

	case 0x0F:
		DAT2LCD(0x46);
		break;

	default:
		break;
	}
}

void char2LCD(char * val)
{
	//toLower()

	int i = 0;
	while(val[i] != NULL)
	{
		switch(val[i]){
		case '0':
			DAT2LCD(0x30);
			break;

		case '1':
			DAT2LCD(0x31);
			break;

		case '2':
			DAT2LCD(0x32);
			break;

		case '3':
			DAT2LCD(0x33);
			break;

		case '4':
			DAT2LCD(0x34);
			break;

		case '5':
			DAT2LCD(0x35);
			break;

		case '6':
			DAT2LCD(0x36);
			break;

		case '7':
			DAT2LCD(0x37);
			break;

		case '8':
			DAT2LCD(0x38);
			break;

		case '9':
			DAT2LCD(0x39);
			break;

		case 'a':
			DAT2LCD(0x41);
			break;

		case 'b':
			DAT2LCD(0x42);
			break;

		case 'c':
			DAT2LCD(0x43);
			break;

		case 'd':
			DAT2LCD(0x44);
			break;

		case 'e':
			DAT2LCD(0x45);
			break;

		case 'f':
			DAT2LCD(0x46);
			break;

		case 'g':
			DAT2LCD(0x47);
			break;

		case 'h':
			DAT2LCD(0x48);
			break;

		case 'i':
			DAT2LCD(0x49);
			break;

		case 'j':
			DAT2LCD(0x4A);
			break;

		case 'k':
			DAT2LCD(0x4B);
			break;

		case 'l':
			DAT2LCD(0x4C);
			break;

		case 'm':
			DAT2LCD(0x4D);
			break;

		case 'n':
			DAT2LCD(0x4E);
			break;

		case 'o':
			DAT2LCD(0x4F);
			break;

		case 'p':
			DAT2LCD(0x50);
			break;

		case 'q':
			DAT2LCD(0x51);
			break;

		case 'r':
			DAT2LCD(0x52);
			break;

		case 's':
			DAT2LCD(0x53);
			break;

		case 't':
			DAT2LCD(0x54);
			break;

		case 'u':
			DAT2LCD(0x55);
			break;

		case 'v':
			DAT2LCD(0x56);
			break;

		case 'w':
			DAT2LCD(0x57);
			break;

		case 'x':
			DAT2LCD(0x58);
			break;

		case 'y':
			DAT2LCD(0x59);
			break;

		case 'z':
			DAT2LCD(0x5A);
			break;

		case ' ':
			DAT2LCD(0x20);
			break;
			/*
	case '.':
		DAT2LCD();
		break;

	case ':':
		DAT2LCD();
		break;
			 */

		default:
			break;
		}
		i++;
	}
}
