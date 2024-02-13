#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include <avr/interrupt.h>
#include "INTERRUPT_Interface.h"


u8 EXIT_u8IntSetsenseControl(u8 copy_Intnum, u8 copy_sense)
{
	u8 LOCAL_ERROR=0;
	if (copy_Intnum==INT0)
	{
		switch (copy_sense)
		{
			case LOW_LEVEL    : CLEAR_BIT(MCUCR,ISC00);CLEAR_BIT(MCUCR,ISC01);break;
			case ANY_CHANGE   : SET_BIT(MCUCR,ISC00);CLEAR_BIT(MCUCR,ISC01);break;
			case FALLING_EDGE : CLEAR_BIT(MCUCR,ISC00);SET_BIT(MCUCR,ISC01);break;
			case RISSING_EDGE :	SET_BIT(MCUCR,ISC00); SET_BIT(MCUCR,ISC01);break;
			default:LOCAL_ERROR=1;break;
		}
	}
	else if (copy_Intnum==INT1)
	{
		switch (copy_sense)
		{
			case LOW_LEVEL    : CLEAR_BIT(MCUCR,ISC10);CLEAR_BIT(MCUCR,ISC11);break;
			case ANY_CHANGE   : SET_BIT(MCUCR,ISC10);CLEAR_BIT(MCUCR,ISC11);break;
			case FALLING_EDGE : CLEAR_BIT(MCUCR,ISC10);SET_BIT(MCUCR,ISC11);break;
			case RISSING_EDGE :	SET_BIT(MCUCR,ISC10); SET_BIT(MCUCR,ISC11);break;
		}
	}
	else if (copy_Intnum==INT2)
	{
		switch (copy_sense)
		{
			case RISSING_EDGE: SET_BIT(MCUCSR, ISC2); break;
			case FALLING_EDGE: CLEAR_BIT(MCUCSR, ISC2); break;
			default: LOCAL_ERROR = 1;break;
		}
	}
	else
	LOCAL_ERROR=1;
	
	return LOCAL_ERROR;
}

u8 EXIT_u8IntEnable(u8 copy_Intnum)
{
	u8 LOCAL_ERROR = 0 ; 
	switch(copy_Intnum)
	{
		case INT0 :SET_BIT(GICR,6);break;
		case INT1 :SET_BIT(GICR,7);break;
		case INT2 :SET_BIT(GICR,5);break;
		default:LOCAL_ERROR=1;
	}
	return LOCAL_ERROR ;
}

u8 EXIT_u8IntDisable(u8 copy_Intnum)
{
	u8 LOCAL_ERROR = 0 ;
	switch(copy_Intnum)
	{
		case INT0 :CLEAR_BIT(GICR,INTF0);break;
		case INT1 :CLEAR_BIT(GICR,INTF1);break;
		case INT2 :CLEAR_BIT(GICR,INTF2);break;
		default:LOCAL_ERROR=1;
	}
	return LOCAL_ERROR ;
}



