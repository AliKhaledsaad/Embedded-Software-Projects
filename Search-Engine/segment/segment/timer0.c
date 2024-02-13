/*
 * timer0.c
 *
 * Created: 18/05/2023 07:49:02 م
 *  Author: DON
 */ 
#include "timer0.h"


void timer0_init(void)
{
	TCNT0=0x00;		//load TCNT0 with initial value
	TCCR0=0x05;		//Normal mode,1024 scaler
}
void timer0_delay(g_callBackPtr callBackPtr,uint8 segNum)
{
	int ticks=0;
	notEnd:
	while((TIFR&0x01)==0){
		callBackPtr(segNum);
		}	//loop if bit0 = 0 (TOV0)
	if (ticks == NUMBER_OF_OVERFLOW)
	{
		TIFR=0x01;			//clear TOV0
	}
	else{
		ticks++;
		TIFR=0x01;			//clear TOV0
		goto notEnd;
	}
}
