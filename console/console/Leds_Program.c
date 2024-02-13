#define F_CPU 8000000U
#include "Leds_Interface.h"
#include "STD_TYPES.h"
#include "DIO_INTERFACE.h"
#include "BIT_MATH.h"
#include "Buzzer_Interface.h"

void LEDS_PowerON(u8 pins)
{
	DIO_u8SetPortDir(LEDS_PORT,pins);
}

void Toogle_LED(u8 led_num)
{
	switch(LEDS_PORT)
	{
		case 0: TOGGLE_BIT(PORTA,led_num);break;
		case 1: TOGGLE_BIT(PORTB,led_num);break;
		case 2: TOGGLE_BIT(PORTC,led_num);break;
		case 3: TOGGLE_BIT(PORTD,led_num);break;
	}
}

void Flashing_Led(u8 led_num)
{
    switch(led_num)
	{
		case 4:Buzzer_Enable(RED_Tone);break;
		case 5:Buzzer_Enable(Yellow_Tone);break;
		case 6:Buzzer_Enable(Green_Tone);break;
		case 7:Buzzer_Enable(Blue_Tone);break;
		default:break;
	}
	Toogle_LED(led_num);
	_delay_ms(500);
	Toogle_LED(led_num);
	_delay_ms(500);
}

void Flashing_LedGroup()
{
	switch(LEDS_PORT)
	{
		case 0:
		       Buzzer_Enable(Winer);
			   
		       TOGGLE_BIT(PORTA,4);TOGGLE_BIT(PORTA,5);TOGGLE_BIT(PORTA,6);TOGGLE_BIT(PORTA,7);
			   _delay_ms(200);
		       TOGGLE_BIT(PORTA,4);TOGGLE_BIT(PORTA,5);TOGGLE_BIT(PORTA,6);TOGGLE_BIT(PORTA,7);
			   _delay_ms(200);
               break;
		case 1: 
		      Buzzer_Enable(Winer);
			  TOGGLE_BIT(PORTB,4);TOGGLE_BIT(PORTB,5);TOGGLE_BIT(PORTB,6);TOGGLE_BIT(PORTB,7);
			  _delay_ms(200);
			  TOGGLE_BIT(PORTB,4);TOGGLE_BIT(PORTB,5);TOGGLE_BIT(PORTB,6);TOGGLE_BIT(PORTB,7);
			  _delay_ms(200);
			 break;
		case 2:
		      Buzzer_Enable(Winer);
			  TOGGLE_BIT(PORTC,4);TOGGLE_BIT(PORTC,5);TOGGLE_BIT(PORTC,6);TOGGLE_BIT(PORTC,7);
			  _delay_ms(200);
			  TOGGLE_BIT(PORTC,4);TOGGLE_BIT(PORTC,5);TOGGLE_BIT(PORTC,6);TOGGLE_BIT(PORTC,7);
			  _delay_ms(200);
			  break;
			  		    
		case 3: 
			  TOGGLE_BIT(PORTD,4);TOGGLE_BIT(PORTD,5);TOGGLE_BIT(PORTD,6);TOGGLE_BIT(PORTD,7);
			  _delay_ms(200);
			  TOGGLE_BIT(PORTD,4);TOGGLE_BIT(PORTD,5);TOGGLE_BIT(PORTD,6);TOGGLE_BIT(PORTD,7);
			  _delay_ms(200);
			  break;
	}
}