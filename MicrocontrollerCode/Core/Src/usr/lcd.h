/*
 * lcd.h
 *
 *  Created on: Jan 5, 2021
 *      Author: danieltakyi
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
 * Function name:
 * Preconditions:
 * Postconditiions:
 * Return type:
 * Purpose:
 */
void lcd_IO_init (void);

/**
 * Function name:
 * Preconditions:
 * Postconditiions:
 * Return type:
 * Purpose:
 */
void CMD2LCD(uint8_t);

/**
 * Function name:
 * Preconditions:
 * Postconditiions:
 * Return type:
 * Purpose:
 */
void DAT2LCD(uint8_t);

/**
 * Function name:
 * Preconditions:
 * Postconditiions:
 * Return type:
 * Purpose:
 */
void lcd_init(void);

/**
 * Function name:
 * Preconditions:
 * Postconditiions:
 * Return type:
 * Purpose:
 */
void dipSW2LCD(uint8_t);

/**
 * Function name:
 * Preconditions:
 * Postconditiions:
 * Return type:
 * Purpose:
 */
void char2LCD(char *);

#endif /* SRC_USR_LCD_H_ */
