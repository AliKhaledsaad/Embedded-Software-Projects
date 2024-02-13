#define F_CPU 8000000
#include "SevenSegments_Interface.h"
#include "DIO_INTERFACE.h"
#include "STD_TYPES.h"
#include <util/delay.h>
void SevenSegments_Init()
{
	DIO_u8SetPortDir(SS_PORT,0x7f);
	DIO_u8SetPortValue(SS_PORT,0x7f);
	
}

void SevenSegments_Enable(u8 num)
{
	switch(num)
	{
		case 1:DIO_u8SetPinValue(SS_PORT,E1,DIO_HIGH);break;
		case 2:DIO_u8SetPinValue(SS_PORT,E2,DIO_HIGH);break;
		default:break;
	}
}

void SevenSegments_Disable(u8 num)
{
	switch(num)
	{
		case 1:DIO_u8SetPinValue(SS_PORT,E1,DIO_LOW);break;
		case 2:DIO_u8SetPinValue(SS_PORT,E2,DIO_LOW);break;
		default:break;
	}
}

void SevenSegments_PowerON()
{
	SevenSegments_Init();
	SevenSegments_Disable(1);
	SevenSegments_Disable(2);
}

void SevenSegments_DisplayDigit(u8 Digit)
{
	DIO_u8SetPortValue(SS_PORT,Digit);
}

void SvenSegments_SendNumber(u8 num )
{	
	if (num>=0&&num<100)
	{
		u8 temp=num%10;
		num/=10;
		for(u8 i=0;i<50;i++)
		{
		  SevenSegments_Enable(1);
		  SevenSegments_DisplayDigit(temp);
		  _delay_ms(10);
		  SevenSegments_Disable(1);
		  
		SevenSegments_Enable(2);
		SevenSegments_DisplayDigit(num);
		_delay_ms(10);
		SevenSegments_Disable(2);
		}
	}
}
