/*
 * lcd.h
 *
 *  Created on: Jan 5, 2021
 *      Author: danieltakyi
 */

#ifndef SRC_USR_LCD_H_
#define SRC_USR_LCD_H_

#include <stdint.h>

#define LCD_CM_ENA 0x00210002 //
#define LCD_CM_DIS 0x00230000 //
#define LCD_DM_ENA 0x00200003 //
#define LCD_DM_DIS 0x00220001 //


void lcd_IO_init (void);

void CMD2LCD(uint8_t);

void DAT2LCD(uint8_t);

void lcd_init(void);

void print2LCD(uint64_t);

void dipSW2LCD(uint8_t);

#endif /* SRC_USR_LCD_H_ */
