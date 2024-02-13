#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_INTERFACE.h"
#include "IR_Sensor.h"
void IR_INIT()
{
	
DIO_u8SetPinDir(DIO_PORTA,DIO_PIN4,DIO_LOW);
DIO_u8SetPinDir(DIO_PORTA,DIO_PIN5,DIO_LOW);
DIO_u8SetPinDir(DIO_PORTA,DIO_PIN6,DIO_LOW);
DIO_u8SetPinDir(DIO_PORTA,DIO_PIN7,DIO_LOW);	
DIO_u8SetPinValue(DIO_PORTA,DIO_PIN4,DIO_HIGH);
DIO_u8SetPinValue(DIO_PORTA,DIO_PIN5,DIO_HIGH);
DIO_u8SetPinValue(DIO_PORTA,DIO_PIN6,DIO_HIGH);
DIO_u8SetPinValue(DIO_PORTA,DIO_PIN7,DIO_HIGH);
}
u8 IR_READ(){
	u8 value;
	for(int i=4;i<8;i++)
	{
		DIO_u8GetPinValue(DIO_PORTA,i,&value);
		if(value==1)
		{
			value=i-4;
          return value;
		}
	}
	return 0xff;
}