/*
 * lcd.h
 *
 *  Created on: Jan 5, 2021
 *      Author: danieltakyi
 * Description: This file contains all functions needed to
 * 				interface to the Liquid Crystal Display
 *
 */

#ifndef SRC_USR_LCD_H_
#define SRC_USR_LCD_H_

#include <stdint.h>
#include <ctype.h>

#define LCD_CM_ENA 0x00210002 //
#define LCD_CM_DIS 0x00230000 //
#define LCD_DM_ENA 0x00200003 //
#define LCD_DM_DIS 0x00220001 //

/**
 * Function name:	lcd_IO_init
 * Preconditions:	n/a
 * Postconditiions:	Port B and port C enabled. Pins set as outputs.
 * Return type:		n/a
 * Purpose:			Initialize the GPIO pins that connect to the LCD as outputs
 */
void lcd_IO_init (void);

/**
 * Function name:	CMD2LCD
 * Preconditions:	n/a
 * Postconditiions:	LCD affected
 * Return type:		n/a
 * Purpose:			Send commands to LCD
 */
void CMD2LCD(uint8_t);

/**
 * Function name:	DAT2LCD
 * Preconditions:	n/a
 * Postconditiions:	LCD affected
 * Return type:		n/a
 * Purpose:			Send commands to LCD
 */
void DAT2LCD(uint8_t);

/**
 * Function name:	lcd_init
 * Preconditions:	lcd_IO_init has already been run
 * Postconditiions:	DAT2LCD runs to configure LCD
 * Return type:		n/a
 * Purpose:			Initialize the LCD so that it becomes able to receive and print data
 */
void lcd_init(void);

/**
 * Function name:	char2LCD
 * Preconditions:	n/a
 * Postconditiions:	Characters are printed onto the LCD
 * Return type:		n/a
 * Purpose:			Print the string in the argument out onto the LCD screen
 */
void char2LCD(char *);

#endif /* SRC_USR_LCD_H_ */
