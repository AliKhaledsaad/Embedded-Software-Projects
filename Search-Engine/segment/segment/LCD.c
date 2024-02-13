/*
 * LCD.c
 *
 * Created: 27/03/2023 01:58:37 
 *  Author: DON
 */ 
#include "LCD.h"

void lcdInit(void){
	SET_BIT(lcdCommandDDR,RS);
	SET_BIT(lcdCommandDDR,EN);
	
	SET_BIT(lcdDataDDR,PIN0);
	SET_BIT(lcdDataDDR,PIN1);
	SET_BIT(lcdDataDDR,PIN2);
	SET_BIT(lcdDataDDR,PIN4);
	
	_delay_ms(15); 
	//for 4-BIT Mode
	lcdCommand(0x02);
	lcdCommand(0x28);
	
	lcdCommand(0x0C);
	lcdCommand(0x06);
	lcdCommand(0x01);
	
	lcdCommand(0x80);
	
}
void lcdCommand(uint8 cmd){
	CLR_BIT(lcdCommandPort,3);				//RS = 0 commands
	//left part
	lcdDataPort&= 0b11101000;				//work only on B0,1,2,4
	
	uint8 high = ((cmd&0xf0)>>4);	//get the left 4-bits to right 
	
	uint8 temp = (((high&0b00001000) << 1) | (high&0b00000111));
	
	lcdDataPort|=temp;
	
	//latch 
	
	SET_BIT(lcdCommandPort,EN);
	_delay_us(1);
	CLR_BIT(lcdCommandPort,EN);
	_delay_ms(2);
	
	//right part
	lcdDataPort&=0b11101000;				//work only on B0,1,2,4
	
	uint8 low = (cmd&0x0f);	//get the left 4-bits to right
	
	uint8 temp2 = (((low&0b00001000) << 1) | (low&0b00000111));
	
	lcdDataPort|=temp2;
	//latch
	SET_BIT(lcdCommandPort,EN);
	_delay_us(1);
	CLR_BIT(lcdCommandPort,EN);
	_delay_ms(2);
	
	_delay_ms(5);
	
}
void lcdWriteChar(uint8 chr){
	SET_BIT(lcdCommandPort,3);				//RS = 1 commands
 	//left part
 	lcdDataPort &= 0b11101000;				//work only on B0,1,2,4
	
 	uint8 high = ((chr&0xf0)>>4);	//get the left 4-bits to right
	
 	uint8 temp = (((high&0b00001000) << 1) | (high&0b00000111));
	
	lcdDataPort|=temp;
	
	//latch
	SET_BIT(lcdCommandPort,EN);//PORTA PIN2
	_delay_us(1);
	CLR_BIT(lcdCommandPort,EN);
	_delay_us(100);
	SET_BIT(lcdCommandPort,EN);//Disable 7Seg
	//right part
	lcdDataPort&=0b11101000;				//work only on B0,1,2,4
	
	uint8 low = (chr&0x0f);	//get the left 4-bits to right
	
	uint8 temp2 = (((low&0b00001000) << 1) | (low&0b00000111));
	
	lcdDataPort|=temp2;
	//latch
	SET_BIT(lcdCommandPort,EN);
	_delay_us(1);
	CLR_BIT(lcdCommandPort,EN);
	_delay_us(100);
	SET_BIT(lcdCommandPort,EN);//Disable 7Seg
	_delay_ms(5);
}


void lcdString(char *str){
	for(int i=0;str[i]!='\0';i++)
		lcdWriteChar(str[i]);
}
void lcdGoTo(uint8 row,uint8 col){
	uint8 address=0;
	switch(row){
		case 0:
		address = col;
		break;
		case 1:
		address = col+0x40;
		break;
		case 2:
		address = col+0x14;
		break;
		case 3:
		address = col+0x54;
		break;
	}
	lcdCommand(address | 0x80);
}
void lcdClear(void){
	lcdCommand(0x01);
}

