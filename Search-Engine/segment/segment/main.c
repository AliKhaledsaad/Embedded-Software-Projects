/*
 * Searching Project
 *
 * Created: 18/05/2023 07:49:02 ã
 *  Author: JUST Submit Team.
 */ 

#include "7seg_driver.h"
#include "LCD.h"
#include "keyPad.h"
#include "LED_DRIVER.h"
#include "std_types.h"
#include "timer0.h"

//declare leds
LED_CONF GREEN =	{&LED_DDR_GREEN,&LED_PORT_GREEN,LED_PIN_NUM_GREEN};
LED_CONF BLUE =		{&LED_DDR_BLUE,&LED_PORT_BLUE,LED_PIN_NUM_BLUE};
LED_CONF YELLOW =	{&LED_DDR_YELLOW,&LED_PORT_YELLOW,LED_PIN_NUM_YELLOW};
LED_CONF RED =		{&LED_DDR_RED,&LED_PORT_RED,LED_PIN_NUM_RED};
	
char binaryStr[4];
void to_binary(uint8);		//num2binary
void binary_leds(void);		

int main(void)
{
	LED_INIT(&GREEN);
	LED_INIT(&BLUE);
	LED_INIT(&YELLOW);
	LED_INIT(&RED);
	lcdInit();
	Seven_seg_voidinit();
	keyPadInit();
	timer0_init();
	
	int count = -1,key=-1,sz,operator=0;
	int list[16] = {[0 ... 15]=-1}; 
	long value=0;
	
	lcdString("List: ");
	while (1)
	{
		key = keyPadGetValue();
		if (key != INVALID_KEYPAD_PRESS)
		{
			switch (key)
			{
				case 13:				// (+) key print comma to separate numbers
					count++;
					if(count != 15){	//list not end
						lcdWriteChar(',');
						list[count] = value;
						value=0;
					}
					break;
				case 14:				// (ON/C) key entering the number to search for
					lcdClear();
					lcdString("Search Number: ");
					operator=1;
					count++;				//append last number
					list[count] = value;
					value=0;
					break;
				case 15:				// (=) key start searching 
					sz = sizeof(list) / sizeof(list[0]);
					int lastVAl=-1;
					for (int i=0;i<=sz;i++)
						{
							if(list[i]==value)
							{
								to_binary(i);	//index2binary for leds
								binary_leds();
								timer0_delay(idx_7seg,i);  //delay 1sec
								lastVAl=i;
							}
						}
						while(1) idx_7seg(lastVAl); // continue showing last index
					break;
				default:				// default wait for entering numbers
					if(key>=0 && key<=9)
					{
						if (count!=16 && operator==0)			//List
						{
							value = value * 10 + key;
							lcdWriteChar(key+'0');
						}
						else							// Search number
						{
							value = value * 10 + key;
							lcdWriteChar(key+'0');
						}
					}
					break;
			}
		}
	}
}
void to_binary(uint8 num) {
	//static char* str;
	
	int idx = 0;
	while (idx <= 3) {
		binaryStr[idx] = (num % 2 ? '1' : '0');//0100
		num /= 2;
		idx++;
	}
	
}
void binary_leds(){
	if(binaryStr[0]=='1')
	LED_ON(&GREEN);
	else
	LED_OFF(&GREEN);
	if(binaryStr[1]=='1')
	LED_ON(&BLUE);
	else
	LED_OFF(&BLUE);
	if(binaryStr[2]=='1')
	LED_ON(&YELLOW);
	else
	LED_OFF(&YELLOW);
	if(binaryStr[3]=='1')
	LED_ON(&RED);
	else
	LED_OFF(&RED);
}
