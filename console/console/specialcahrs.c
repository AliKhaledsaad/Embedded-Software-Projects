/*
 * specialcahrs.c
 *
 * Created: 9/6/2023 9:09:35 AM
 *  Author: 2020
 */ 
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "BIT_MATH.h"
#include "CLCD_Interface.h"
#include "DIO_INTERFACE.h"
#include "STD_TYPES.h"
#include "specialcahrs.h"
u8 customCharurr[] = {
	0x00,
	0x00,
	0x00,
	0x1F,
	0x1F,
	0x00,
	0x00,
	0x00
};
void BUZZ11(void)
{
	SET_BIT(DDRC, 6);
	SET_BIT(PORTC,6);
	_delay_ms(50);
	CLEAR_BIT(PORTC, 6);
}
u8 customChardrr[] = {
	0x00,
	0x00,
	0x00,
	0x1F,
	0x1F,
	0x00,
	0x00,
	0x00
};
void random_pair(u8 c, u8 *x, u8 *y) {
	// Calculate x and y based on the seed
	*x = (c * 15245 + 12345) % 4;
	*y = (c * 5431+ 5432) % 16;
}
u8  customCharull[] = {
	0x04,
	0x04,
	0x04,
	0x04,
	0x00,
	0x00,
	0x00,
	0x00
};
u8 customChardll[] = {
	0x00,
	0x00,
	0x00,
	0x00,
	0x04,
	0x04,
	0x04,
	0x04
};
u8 customCharfll[] = {
	0x00,
	0x00,
	0x06,
	0x06,
	0x06,
	0x06,
	0x00,
	0x00
};
u8 customCharfood[] = {
	 0x00,
	 0x00,
	 0x0E,
	 0x1F,
	 0x1F,
	 0x0E,
	 0x00,
	 0x00
};
u8 customCharspace[] = {
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00
};
 void snake(){
	
 u8 tail_positions[4][16];
 for (u8 i = 0; i < 4; i++) {
	 for (u8 j = 0; j < 16; j++)
	 {tail_positions[i][j]=48;}}
	 
	 tail_positions[0][0]=0;
	 tail_positions[0][1]=1;
	 u8 snake_positions[4][16];
	 for (u8 i = 0; i < 4; i++)
	 for (u8 j = 0; j < 16; j++)
	 snake_positions[i][j]=0;
	 
	 snake_positions[0][0]=2;
	 snake_positions[0][1]=2;
	 CLCD_voidSendSpecialChar(customCharurr,2,0,0);
	 CLCD_voidSendSpecialChar(customCharurr,2,0,1);
	 CLCD_voidGoTOxy(0,5);
	 CLCD_voidSendData('*');
	 //CLCD_voidSendSpecialChar(customCharfood,7,0,5);
	 snake_positions[0][5]=9;

	 u8 k=0,curr_k=right,nx=0,ny=1,pm='u',c=1,ty=7,tx=0,minValue=48,sf=0,rx=0,ry=5;
	 
	 _delay_ms(1000);
	 /* Replace with your application code */
	 while (1)
	 {
		 k=key();
		 if (k!=0xff)
		 curr_k=k;
		 
		 switch (curr_k)
		 {
			 case right:
			 if (pm=='d')
			 ny++;//-1
			 else if (pm=='u')
			 ny++;
			 else
			 ny++;
			 CLCD_voidSendSpecialChar(customCharurr,2,nx,ny);
			  _delay_ms(300);
			 snake_positions[nx][ny]=2;
			 break;
			 case left:
			 if (pm=='d')
			 ny--;//-1
			 else if (pm=='u')
			 ny--;
			 else
			 ny--;
			 CLCD_voidSendSpecialChar(customCharurr,2,nx,ny);
			  _delay_ms(300);
			 snake_positions[nx][ny]=2;
			 break;
			 case up:
			 	
			 if (pm=='d')
			 nx--;//-1
			 else if (pm=='u')
			 nx--;
			 else
			 nx--;
			 
			 CLCD_voidSendSpecialChar(customCharfll,1,nx,ny);
			 _delay_ms(800);
			 snake_positions[nx][ny]=1;
			 break;
			 case down:
			 	
			 if (pm=='d')
			 nx++;
			 else if (pm=='u')
			 nx++;
			 else
			 nx++;
			 
			 CLCD_voidSendSpecialChar(customCharfll,1,nx,ny);
			 _delay_ms(800);
			 snake_positions[nx][ny]=1;
			 break;
		 }
		 u8 go=0;
		 go--;
		 if (nx==4|| ny==16||ny==go||nx==go)
		 break;
		 
		 
		 if(nx==rx & ny==ry)
		 {
			 while(snake_positions[rx][ry]!=0)
			 {random_pair(c, &rx, &ry);c++;}
			 CLCD_voidGoTOxy(rx,ry);
			 CLCD_voidSendData('*');
			 //CLCD_voidSendSpecialChar(customCharfood,7,rx,ry);
			 snake_positions[rx][ry]=9;
			 //	TIM=TIM-50;
			 
		 }
		 else
		 {
			 
			 
			 minValue=48;
			 for (int i = 0; i <3 ; i++) {
				 for (int j = 0; j < 15; j++) {
					 if (tail_positions[i][j] < minValue)
					 {
						 minValue = tail_positions[i][j];
						 tx = i;
						 ty = j;
					 }
				 }
			 }

			 tail_positions[tx][ty]=48;
			 c++;
			 CLCD_voidSendSpecialChar(customCharspace,5,tx,ty);
		 }
		 
		 tail_positions[nx][ny]=c;
		 
		 
	 }
	
	 CLCD_voidSendCommand(1);
	  CLCD_voidGoTOxy(1,5);
	   BUZZ11();
	 CLCD_voidPrintString("Game Over");
	 _delay_ms(2000);
	 
	 
 }
