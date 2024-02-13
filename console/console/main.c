#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_INTERFACE.h"
#include "CLCD_Interface.h"
#include "TIMER_Interface.h"
#include "SevenSegments_Interface.h"
#include "keys.h"
#include "Leds_Interface.h"
#include "Buzzer_Interface.h"
#include "Simon_Game.h"
#include "cowboyTIMER_Interface.h"
#include "COW_BOY.h"
#include "2COW_BOY.h"
#include "ping_game.h"
#include "specialcahrs.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void menu_sound() 
{
	
	DDRB |= (1 << PB3);
	TCCR0 |= (1 << COM00) | (1 << WGM01);
	TCCR0 |= (1 << CS01);
	OCR0 = 0x7F;
	_delay_ms(50);
	TCCR0 &= ~(1 << COM00);
	_delay_ms(50);
}
void game_select()
{
   extern game_End;
   extern game_End3;
   extern game_End2;
   game_End=0;
   game_End2=0;
   game_End3=0;
	CLCD_PowerON();
	CLCD_voidGoTOxy(0,0);
	CLCD_voidPrintString("1 : Smoin Say");
	CLCD_voidGoTOxy(1,0);
	CLCD_voidPrintString("2 : Ping Pong");
	CLCD_voidGoTOxy(2,0);
	CLCD_voidPrintString("3 : Catch");
	CLCD_voidGoTOxy(3,0);
	CLCD_voidPrintString("4 : CowBoy");
	u8 static value=0;
	u8 cursor_x=0;
	u8 cursor_y=0;
	u8 cursor[8]={0x18,0x1C,0x1E,0x1F,0x1F,0x1E,0x1C,0x18};
	CLCD_voidSendSpecialChar(cursor,0,0,0);
	while(value!=shot)
	{
		value=key();
		switch(value)
		{
			case up:
			if(cursor_x>=1)
			{ 
				
				CLCD_voidGoTOxy(0,0);
				CLCD_voidPrintString("1 : Smoin Say");
				CLCD_voidGoTOxy(1,0);
				CLCD_voidPrintString("2 : Ping Pong");
				CLCD_voidGoTOxy(2,0);
				CLCD_voidPrintString("3 : Catch");
				CLCD_voidGoTOxy(3,0);
				CLCD_voidPrintString("4 : CowBoy");
				menu_sound();
				cursor_x--;
				CLCD_voidSendSpecialChar(cursor,0,cursor_x,cursor_y);
			}
			else
			{
				CLCD_voidGoTOxy(0,0);
				CLCD_voidPrintString("1 : Smoin Say");
				CLCD_voidGoTOxy(1,0);
				CLCD_voidPrintString("2 : Ping Pong");
				CLCD_voidGoTOxy(2,0);
				CLCD_voidPrintString("3 : Catch");
				CLCD_voidGoTOxy(3,0);
				CLCD_voidPrintString("4 : CowBoy");
				menu_sound();
				CLCD_voidSendSpecialChar(cursor,0,cursor_x,cursor_y);
			}
			break;
			case down:
			if(cursor_x<=2)
			{
				CLCD_voidGoTOxy(0,0);
				CLCD_voidPrintString("1 : Smoin Say");
				CLCD_voidGoTOxy(1,0);
				CLCD_voidPrintString("2 : Ping Pong");
				CLCD_voidGoTOxy(2,0);
				CLCD_voidPrintString("3 : Catch");
				CLCD_voidGoTOxy(3,0);
				CLCD_voidPrintString("4 : CowBoy");
				 menu_sound();
				cursor_x++;
				CLCD_voidSendSpecialChar(cursor,0,cursor_x,cursor_y);
			}
			else
			{
				CLCD_voidSendCommand(1);
				cursor_x++;
				CLCD_voidGoTOxy(0,0);
		     	CLCD_voidPrintString("2 : Ping Pong");
				CLCD_voidGoTOxy(1,0);
				CLCD_voidPrintString("3 : Catch");
				CLCD_voidGoTOxy(2,0);
				CLCD_voidPrintString("4 : CowBoy");
				CLCD_voidGoTOxy(3,0);
				CLCD_voidPrintString("5 : Snake");
				menu_sound();
				CLCD_voidSendSpecialChar(cursor,0,3,0);
			}
			break;
			
		}
		
	}
	value=0;
	switch(cursor_x)
	{
		case 0:
		menu_sound(); 
		CLCD_voidSendCommand(1);
	    LEDS_PowerON(0xff);
		SevenSegments_PowerON();
		Game();
		break;
		case 1:
		menu_sound(); 
		CLCD_voidSendCommand(1);
		ping_pong();
		break;
		case 2:
		menu_sound(); 
		CLCD_voidSendCommand(1);
		COW_BOY2();
		
		break;
		case 3:
		menu_sound();
		CLCD_voidSendCommand(1);
		COW_BOY();
		
		break;
		default:
		if(cursor_x>=4)
		{
			menu_sound();
			CLCD_voidSendCommand(1);
			snake();
		}
		
	}
	
}
int main(void)
{  
	
	while(1)
	{
      game_select();
	}
		
	
	
	return 0;
}

