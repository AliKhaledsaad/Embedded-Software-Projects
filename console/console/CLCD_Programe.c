#include "DIO_INTERFACE.h"
#include "CLCD_Interface.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include <util/delay.h>

void CLCD_voidSendCommand(u8 Copy_u8Command){
	//Setting RS to low command
	DIO_u8SetPinValue(CLCD_PORT_CONTROL,CONTROL_RS,DIO_LOW);
	//Setting Rw to low for write	
	DIO_u8SetPinValue(CLCD_PORT_CONTROL,CONTROL_RW,DIO_LOW);
	//Setting Data
	DIO_u8SetPortValue(CLCD_PORT_DATA,Copy_u8Command);
	//Enable and disable pulse
	DIO_u8SetPinValue(CLCD_PORT_CONTROL,CONTROL_E,DIO_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_PORT_CONTROL,CONTROL_E,DIO_LOW);
  
}

void CLCD_voidSendData(u8 Copy_u8Data){
	
	//Setting RS to low High Data
	DIO_u8SetPinValue(CLCD_PORT_CONTROL,CONTROL_RS,DIO_HIGH);
	//Setting Rw to low for write
	DIO_u8SetPinValue(CLCD_PORT_CONTROL,CONTROL_RW,DIO_LOW);
	//Setting Data
	DIO_u8SetPortValue(CLCD_PORT_DATA,Copy_u8Data);
	//Enable and disable pulse
	DIO_u8SetPinValue(CLCD_PORT_CONTROL,CONTROL_E,DIO_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_PORT_CONTROL,CONTROL_E,DIO_LOW);
	
}

void CLCD_voidInit(void){
	//power on
	_delay_ms(45);
	//Funcation set
	CLCD_voidSendCommand(0b00111000);
	//Display ON/OFF control
	CLCD_voidSendCommand(0b00001100);
	//Display Clear
	CLCD_voidSendCommand(1);
}

void CLCD_voidPrintString(u8 Copy_u8String[])
{
	u8*i=Copy_u8String;
	while(*i!='\0'){
		CLCD_voidSendData(*i);
		i++;
	}
}

void CLCD_voidGoTOxy(u8 x,u8 y)
{
	u8 address;
	if (x==0)
	{
		  address=y;
	}
	else if (x==1)
	{
		address=y+0x40;
	}
	else if (x==2)
	{
		address=y+0x10;
	}
	else if (x==3)
	{
		address=y+0x50;
	}
	CLCD_voidSendCommand(address|128);
}

void CLCD_voidSendNumber(s32 number) {
	{
		u8 list[10];
		
		if (number<0)
		{
			CLCD_voidSendData('-');
			number=-number;
		}
		
		if (number==0)
		{
			CLCD_voidSendData('0');
		}
		u8 i=0;
		while(number>0)
		{
			list[i++]=(number%10)+'0';
			number/=10;
		}
		
		for (u8 k=i;k>0;k--)
		{
			CLCD_voidSendData(list[k-1]);
		}
	}
}

void CLCD_ClearDisplay(){
	CLCD_voidSendCommand(0x01);
}
void CLCD_PowerON()
{
	/*SET PORT DATA*/
	DIO_u8SetPortDir(CLCD_PORT_DATA,DIO_PORT_OUT);
	/*SET CONTROL PINS*/
	DIO_u8SetPinDir(CLCD_PORT_CONTROL,CONTROL_RS,DIO_PIN_OUT);
	DIO_u8SetPinDir(CLCD_PORT_CONTROL,CONTROL_RW,DIO_PIN_OUT);
	DIO_u8SetPinDir(CLCD_PORT_CONTROL,CONTROL_E,DIO_PIN_OUT);
    /*Initialize LCD*/	
	CLCD_voidInit();
}
void CLCD_voidSendSpecialChar(u8 *copy_u8pattern, u8 copy_u8pattern_num, u8 x, u8 y)
{
	u8 address = 0, temp;
	address = copy_u8pattern_num * 8;
	CLCD_voidSendCommand(address + 64);
	for (temp = 0; temp < 8; temp++)
	{
		CLCD_voidSendData(copy_u8pattern[temp]);
	}
	CLCD_voidGoTOxy(x, y);
	CLCD_voidSendData(copy_u8pattern_num);
	
}