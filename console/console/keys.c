#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_INTERFACE.h"
#include "keys.h"
u8 key()
{
	u8 state;
	u8 value_pressed=0xff;
	 DIO_u8SetPortDir(DIO_PORTC,0xf0);
	 DIO_u8SetPinValue(DIO_PORTC,DIO_PIN0,DIO_HIGH);
	 DIO_u8SetPinValue(DIO_PORTC,DIO_PIN1,DIO_HIGH);
	 DIO_u8SetPinValue(DIO_PORTC,DIO_PIN2,DIO_HIGH);
	 DIO_u8SetPinValue(DIO_PORTC,DIO_PIN3,DIO_HIGH);
	  DIO_u8SetPinValue(DIO_PORTC,DIO_PIN4,DIO_HIGH);
	for (int i=0;i<5;i++)
	{
		DIO_u8GetPinValue(DIO_PORTC,i,&state);
		if (DIO_LOW==state)
		{
			value_pressed=i;
			
			while(DIO_LOW==state)
			{
				DIO_u8GetPinValue(DIO_PORTC,i,&state);
			}
			return value_pressed;
		}
	}
	return 0xff;
}