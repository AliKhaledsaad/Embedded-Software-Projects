/*
 * kayPad.c
 *
 * Created: 30/03/2023 09:46:34 ص
 *  Author: DON
 */ 
#include "keyPad.h"

const uint8 arr[4][4] = {{7 ,8 , 9, 10},
						 {4 ,5 , 6,11 },
						 {1 ,2 , 3,12 },
						 {14,0,15,13 }
						 };
						 
void keyPadInit(){
		CLR_BIT(DDRD,PIN7);
		CLR_BIT(DDRD,PIN6);
		CLR_BIT(DDRD,PIN5);
		CLR_BIT(DDRD,PIN3);
		
		SET_BIT(DDRC,PIN5);
		SET_BIT(DDRC,PIN4);
		SET_BIT(DDRC,PIN3);
		SET_BIT(DDRC,PIN2);
		
		SET_BIT(PORTD,PIN7);
		SET_BIT(PORTD,PIN6);
		SET_BIT(PORTD,PIN5);
		SET_BIT(PORTD,PIN3);
}

uint8 keyPadGetValue(void){
	uint8 col, row, ans = INVALID_KEYPAD_PRESS;
	for(row=5; row>=2; row--){
		PORTC|=0b00111100;
		CLR_BIT(PORTC,row);
		for(col=7;col>=3;col--){
			if(col==4) col--;
			if(GET_BIT(PIND,col)==0){
				_delay_ms(150);
				if (GET_BIT(PIND,col)==0)
				{
					if (col==3)
					{
						ans=arr[5-row][7-col-1];
						break;
					}
					else
					{
						ans=arr[5-row][7-col];
						break;
					}
				}
			}
		}
	}
	return ans;
}