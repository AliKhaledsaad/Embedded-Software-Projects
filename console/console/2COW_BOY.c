#include "2COW_BOY.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "KEYBAD_Interface.h"
#include "CLCD_Interface.h"
#include "cowboyTIMER_Interface.h"
#include <util/delay.h>
#include "INTERRUPT_Interface.h"
u8 min3=0xff;
#include "keys.h"
u8 game_End3=0;
extern  volatile u32 game_time_seconds;
u8 max3=0;
 u8 game_over_flag3 = 0;u8 out_flag3=0;
int i;
 // KET_VALYE--->TO GET KEYPAD VALYE ,x--->ROWS  & Y-----> COULMNS
u8 KEY_VALUE,x3=0,y3=15,x23=0,y23=0;

/*---------------------DRAWING THE CAHRACTERS---------------------*/
u8 customChar13[] = {
  0b10100,
  0b10100,
  0b11110,
  0b10101,
  0b00100,
  0b01010,
  0b10001,
  0b00000
};
u8 customChar23[] = {
	0b00100,
	0b11110,
	0b00101,
	0b01111,
	0b10100,
	0b01010,
	0b10001,
	0b00000
};
u8 customChar33[]=
{
	0b10001,
	0b01010,
	0b00100,
	0b10101,
	0b01110,
	0b00100,
	0b00100,
	0b00000
	
};
u8 shot3[] = {
	0b00000,
	0b00000,
	0b00100,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000
};

/*----------------------THE INITIAL POSITION OF CHARACTERS ------------*/
void INIT_POSITION3()
{
	  CLCD_voidSendSpecialChar(customChar13,0,0,15);
	  CLCD_voidSendSpecialChar(customChar23,1,0,0);
}

/*----------------------CONTROL MOVEMENT OF X IN RAWS ------------*/
void move_xchar13(u8 delay)
{
	move_ychar13( KEY_VALUE);
	//GOING DOWN
	if (KEY_VALUE==2)
	{
		x3++ ;
		
		if(x3>3)
		{
			CLCD_voidGoTOxy(3,y3);
			CLCD_voidSendData(' ');
			x3=0;
		
		}
		else {
			
			CLCD_voidGoTOxy(x3-1,y3);
			CLCD_voidSendData(' ');

		}
		CLCD_voidSendSpecialChar(customChar13,0,x3,y3);
	}
	
	//GOING UP
	
	else if (KEY_VALUE == 1)
	{
		CLCD_voidGoTOxy(x3, y3);
		CLCD_voidSendData(' ');
		if (x3 == 0)
		{
			x3 = 3;
		}
		else
		{
			x3--;
		}
		
		CLCD_voidGoTOxy(x3, y3);
		CLCD_voidSendSpecialChar(customChar13, 0, x3, y3);
	}
	u8 delay_temp =delay+30;
	TIMER_Delay_ms(delay_temp);
	//char2 movement 
	// GOING DOWN 
	if (KEY_VALUE == 2)
	{
		x23++;

		if (x23 > 3)
		{
			CLCD_voidGoTOxy(3, y23);
			CLCD_voidSendData(' ');
			x23 = 0;
		}
		else
		{
			CLCD_voidGoTOxy(x23 - 1, y23);
			CLCD_voidSendData(' ');
		}
		CLCD_voidSendSpecialChar(customChar23, 1, x23, y23);
	}

	// GOING UP
	else if (KEY_VALUE == 1)
	{
		CLCD_voidGoTOxy(x23, y23);
		CLCD_voidSendData(' ');
		if (x23 == 0)
		{
			x23 = 3;
		}
		else
		{
			x23--;
		}

		CLCD_voidGoTOxy(x23, y23);
		CLCD_voidSendSpecialChar(customChar23, 1, x23, y23);
	}
	KEY_VALUE = 0;
}

u8 point3(u8 copy_x2,u8 delay)
{
	BUZZ3();
	for ( i = 1; i < 16; i++)
	{
				if(	x23==x3&& y3==y23 )
				{BUZZ23();
					move_xchar13(delay);
					CLCD_voidGoTOxy(x23,y23);
					CLCD_voidSendSpecialChar(customChar33,3,x23,y23);
					game_over_flag3 = 1;
					_delay_ms(3000);
					won3();
					break;
				}
			if (copy_x2 == x3 && i == y3 )
			{BUZZ23();
				move_xchar13(delay);
				CLCD_voidSendSpecialChar(customChar33,3,x3,y3);
				game_over_flag3 = 1;
				_delay_ms(3000);
				GAME_OVER3();
			}
			
	
		
		if (i != 1)
		{
			CLCD_voidGoTOxy(copy_x2, i - 1);
			CLCD_voidSendData(' ');
			CLCD_voidSendSpecialChar(shot3, 2, copy_x2, i);
		
			// Check for key press and break the loop if a key is pressed
			KEY_VALUE = key();
        	if (KEY_VALUE != 0xff){BUZZ3();move_xchar13(delay); }
			TIMER_Delay_ms(delay);
		}
		if (i==15)
		{
			CLCD_voidGoTOxy(copy_x2,i);
			CLCD_voidSendData(' ');
		}
		
	}
}

void game3()
{ 
	if(game_End3==0)
	{
		
	
	u8 current_score = game_time_seconds;

	if (current_score > max3)
	{
		max3 = current_score;
	}
	if (out_flag3==1)
	{
		CLCD_ClearDisplay();
		game_End3=1;
		return 1;
	}
	if (game_over_flag3 == 1)
	{
		game_over_flag3 = 0;
		i=1,x3=0,y3=15,x23=0,y23=0;
		
		// Game over condition is met, exit the game loop
		//return 1;
	}
	 game_time_seconds=0;
	CLCD_voidGoTOxy(0,0);
	CLCD_voidPrintString("WELCOME,Cow boy");
	CLCD_voidGoTOxy(1,3);
	CLCD_voidPrintString("1 TO START");
	CLCD_voidGoTOxy(2,3);
	CLCD_voidPrintString("5 TO Out");
	u8 KPDVALUE=key();
	 if (KPDVALUE==0)
	{
		CLCD_ClearDisplay();
		INIT_POSITION3();
		u8 level_up=0;
		while (1)
		{
			// Check the game_over_flag
			if (game_over_flag3 == 1)
			{
				// Game over condition is met, exit the game loop
				break;
			}
			point3(x23,100-level_up);
			level_up=level_up+1;
			game_End3==1;
		}
		game_End3==1;	
	}
	 if (KPDVALUE==4)
	 {out_flag3=1;}
	

}
}
void move_ychar13(u8 KEY_VALUE)
{	
	 		 if(KEY_VALUE==3)
	 		 {
		 		 y3++;
		 		 if (y3>15)
		 		 {
			 		 CLCD_voidGoTOxy(x3,15);
			 		 CLCD_voidSendData(' ');
			 		 y3=0;
		 		 }
		 		 else{
			 		 CLCD_voidGoTOxy(x3,y3-1);
		 		 CLCD_voidSendData(' ');}
		 		 CLCD_voidSendSpecialChar(customChar13,0,x3,y3);
		 		 
	 		 }
	 		 else if (KEY_VALUE == 0)
	 		 {
		 		 CLCD_voidGoTOxy(x3, y3);
		 		 CLCD_voidSendData(' ');
		 		 
		 		 if (y3 == 0)
		 		 {
			 		 y3 = 15;
		 		 }
		 		 else
		 		 {
			 		 y3--;
		 		 }
		 		 
		 		 CLCD_voidGoTOxy(x3, y3);
		 		 CLCD_voidSendSpecialChar(customChar13, 0, x3, y3);
	 		 }
}

void GAME_OVER3()
{ 
	CLCD_ClearDisplay();
	TIMER_Delay_ms(10);
	CLCD_voidGoTOxy(0,4);
	CLCD_voidPrintString("GAME OVER");
	CLCD_voidGoTOxy(1,4);
	CLCD_voidPrintString("SCORE: ");
	CLCD_voidSendNumber(game_time_seconds);
	 _delay_ms(7000);
	 	CLCD_ClearDisplay();
	return 1;
}

void COW_BOY2()
{
	
		TIMER1_Init();
		TIMER0_Init();
		sei();
			
		while (game_End3==0)
		{

			game3();
		}
}




void won3()
{
		
		CLCD_ClearDisplay();
		TIMER_Delay_ms(10);
		CLCD_voidGoTOxy(0, 4);
		CLCD_voidPrintString("YOU won!");
		CLCD_voidGoTOxy(1, 4);
		CLCD_voidPrintString("TIME: ");
		CLCD_voidSendNumber(game_time_seconds);
	//	SvenSegments_SendNumber(min);
		CLCD_voidGoTOxy(2, 0);
		if (min3>game_time_seconds)
		{
			min3=game_time_seconds;
		}	

		CLCD_voidPrintString("mini score: ");
		CLCD_voidSendNumber(min3); 
	// Display minimum time
		TIMER_Delay_ms(5000);
		CLCD_ClearDisplay();
}



void BUZZ3() {
	SET_BIT(DDRC, 6);
	SET_BIT(PORTC, 6);
	_delay_ms(50);
	CLEAR_BIT(PORTC, 6);
}

void BUZZ23() {
	SET_BIT(DDRC, 6);
	SET_BIT(PORTC,6);
	_delay_ms(1000);
	CLEAR_BIT(PORTC, 6);
}
