#include "7seg_driver.h"


void Seven_seg_voidinit(void)
{
	SET_BIT(DDRA,PIN3);
	SET_BIT(DDRA,PIN2);
	DDRB |= 0b01110111;
	//stop all 7seg before start
	SET_BIT(PORTB,PIN6);
	SET_BIT(PORTB,PIN5);
	SET_BIT(PORTA,PIN2);
	SET_BIT(PORTA,PIN3);
	
}
void Seven_seg_voidDisplay(int num)
{
	PORTB &=0b11101000;
	PORTB |=(((num%10 & 0b00001000)<<1)|(num%10 & 0b00000111));
	
}

void idx_7seg(uint8 num){
	Seven_seg_voidDisplay(num / 10);
	_delay_ms(2);
	TOGGLE_BIT(PORTB,PIN6);
	// Display the units digit
	Seven_seg_voidDisplay(num % 10);
	_delay_ms(2);
	TOGGLE_BIT(PORTB,PIN5);
}
