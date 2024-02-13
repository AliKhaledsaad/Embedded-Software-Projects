#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_INTERFACE.h"
#include "CLCD_interface.h"
#include "IR_Sensor.h"
#include "TIMER_TEST_interface.h"
#include <avr/io.h>
#include <util/delay.h>
void checkroams(u8 roams[])
{
	CLCD_voidSendCommand(1);
	
	if(roams[0]==0)
	{
		CLCD_voidGoToXY(0,0);
		CLCD_voidSendString("R1:EMP");
	}
	else if(roams[0]==1)
	{
		
		CLCD_voidGoToXY(0,0);
		CLCD_voidSendString("R1:Full");
	}
	//////////////////////////
	if(roams[1]==0)
	{
		CLCD_voidGoToXY(0,7);
		CLCD_voidSendString("R2:EMP");
	}
	else if(roams[1]==1)
	{
		CLCD_voidGoToXY(0,7);
		CLCD_voidSendString("R2:Full");
	}
	////////////////////////
	if(roams[2]==0)
	{
		CLCD_voidGoToXY(1,0);
		CLCD_voidSendString("R3:EMP");
	}
	else if(roams[2]==1)
	{
		CLCD_voidGoToXY(1,0);
		CLCD_voidSendString("R3:Full");
	}
	////////////////////////
	if(roams[3]==0)
	{
		CLCD_voidGoToXY(1,7);
		CLCD_voidSendString("R4:EMP");
	}
	else if(roams[3]==1)
	{
		CLCD_voidGoToXY(1,7);
		CLCD_voidSendString("R4:Full");
	}
	_delay_ms(3000);
}
int main(void)
{
	 u8 static roams[4]={0,0,0,0};
	u8 userchoose=0xff;
	u8 curroam;
		DIO_u8SetPinDir(PORTA,DIO_PIN0,DIO_HIGH);
		DIO_u8SetPinDir(PORTA,DIO_PIN1,DIO_HIGH);
		DIO_u8SetPinDir(PORTA,DIO_PIN2,DIO_HIGH);
		DIO_u8SetPinDir(PORTA,DIO_PIN3,DIO_HIGH);
	DIO_u8SetPortDir(PORTC,0xff);
	DIO_u8SetPinDir(PORTD,DIO_PIN0,DIO_HIGH);
	DIO_u8SetPinDir(PORTD,DIO_PIN1,DIO_HIGH);
	DIO_u8SetPinDir(PORTD,DIO_PIN2,DIO_HIGH);
      DIO_u8SetPortDir(DIO_PORTD,0xff);
      TIMER1_voidInit();
      TIMER1_voidSetICR(20000);
	  CLCD_voidInit();
	  IR_INIT();
	  CLCD_voidSendString("WELCOME TO YOUR GARAGE");
	  _delay_ms(3000);
    while (1) 
    {
		
		userchoose=IR_READ();
		if(userchoose!=0xff)
		{	
			 if(roams[userchoose]==1)
			 {
				 CLCD_voidSendCommand(1);
				 CLCD_voidSendString("Its FUll choose another");
				 _delay_ms(3000);
				 checkroams(roams);
				   userchoose=0xff;
			 }
			 else if(roams[userchoose]==0)
			 {
				  
				 
				 CLCD_voidSendCommand(1);
				 CLCD_voidSendString("OPENING...");
				 TIMER1_voidSetOCR(2000);
				 _delay_ms(10000);
				   roams[userchoose]=1;
				    userchoose=0xff;
					 CLCD_voidSendCommand(1);
					CLCD_voidSendString("CLOSING...");
					 TIMER1_voidSetOCR(1000);
					  _delay_ms(4000);
			 }
			  userchoose=0xff;
		}
			  
	checkroams(roams);
	}
}

