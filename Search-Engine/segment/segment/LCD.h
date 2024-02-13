/*
 * LCD.h
 *

 *  Author: Mhmd
 */ 


#ifndef LCD_H_
#define LCD_H_


#include "BIT_MATH.h"
#include "reg.h"
#define F_CPU (16000000UL)
#include "util/delay.h"

typedef unsigned char uint8;

#define  lcdDataDDR		DDRB
#define  lcdCommandDDR	DDRA
#define  lcdDataPort	PORTB
#define  lcdCommandPort	PORTA
#define  RS 			PIN3
#define  EN				PIN2

void lcdInit(void);
void lcdCommand(uint8 cmd);
void lcdWriteChar(uint8 chr);
void lcdString(char *str);
void lcdWriteNum(int num);
void lcdClear(void);
void lcdGoTo(uint8,uint8);



#endif /* LCD_H_ */