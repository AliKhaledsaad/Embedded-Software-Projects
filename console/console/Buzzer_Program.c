#define F_CPU 8000000U

#include "DIO_INTERFACE.h"
#include <avr/io.h>
#include "BIT_MATH.h"
#include "Buzzer_Interface.h"
#include <util/delay.h>
void Buzzer_PowerON()
{
	DIO_u8SetPinDir(Buzzer_Port,Buzzer_Pin,DIO_PIN_OUT);
}

void Buzzer_Enable(u8 Tone_Type)
{
	switch(Tone_Type)
	{
		case 0:
				for(u8 i=0;i<250;i++)
				{
					TOGGLE_BIT(PORTB,PB3);
					_delay_ms(0.5);
				}
				for(u8 i=0;i<250;i++)
				{
					TOGGLE_BIT(PORTB,PB3);
					_delay_ms(0.4);
				}
		break;
		
		case 1:
		for(u8 i=0;i<250;i++)
		{
			TOGGLE_BIT(PORTB,PB3);
			_delay_ms(0.5);
		}
		for(u8 i=0;i<250;i++)
		{
			TOGGLE_BIT(PORTB,PB3);
			_delay_ms(0.3);
		}
		break;
		
		case 2:
		for(u8 i=0;i<250;i++)
		{
			TOGGLE_BIT(PORTB,PB3);
			_delay_ms(0.5);
		}
		for(u8 i=0;i<250;i++)
		{
			TOGGLE_BIT(PORTB,PB3);
			_delay_ms(0.2);
		}
		break;
		
		case 3:
		for(u8 i=0;i<250;i++)
		{
			TOGGLE_BIT(PORTB,PB3);
			_delay_ms(0.5);
		}
		for(u8 i=0;i<250;i++)
		{
			TOGGLE_BIT(PORTB,PB3);
			_delay_ms(0.1);
		}
		break;
				
		case 4:
			for(u8 i=0;i<250;i++)
			{
				TOGGLE_BIT(PORTB,PB3);
				_delay_ms(0.5);
			}
			for(u8 i=0;i<250;i++)
			{
				TOGGLE_BIT(PORTB,PB3);
				_delay_ms(0.4);
			}
			
			
			for(u8 i=0;i<250;i++)
			{
				TOGGLE_BIT(PORTB,PB3);
				_delay_ms(0.5);
			}
			for(u8 i=0;i<250;i++)
			{
				TOGGLE_BIT(PORTB,PB3);
				_delay_ms(0.3);
			}
		break;
		
		case 5:
			for (int i=0;i<10;i++)// Loser
			{
				for(u8 i=0;i<250;i++)
				{
					TOGGLE_BIT(PORTB,PB3);
					_delay_ms(0.4);
				}
				for(u8 i=0;i<250;i++)
				{
					TOGGLE_BIT(PORTB,PB3);
					_delay_ms(0.1);
				}
				for(u8 i=0;i<250;i++)
				{
					TOGGLE_BIT(PORTB,PB3);
					_delay_ms(0.4);
				}
				_delay_ms(50);
			}
		break;
	}
}
	
	

	

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	