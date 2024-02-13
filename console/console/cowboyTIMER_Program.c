#include "BIT_MATH.h"
#include "DIO_INTERFACE.h"
#include "cowboyTIMER_Interface.h"
#include "STD_TYPES.h"
#include "INTERRUPT_Interface.h"S
#include <avr/interrupt.h>
#include <avr/io.h>
int seg[100] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
	20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
	38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55,
	56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73,
	74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91,
	92, 93, 94, 95, 96, 97, 98, 99
};
 volatile u32 game_time = 0;
extern u8  game_over_flag ;
 volatile u32 game_time_seconds = 0;
//--------------------------------------------------------------------
volatile u8 timer_flag = 0;

void TIMER1_Init()
{
	// Configure Timer1 with 1ms interrupt interval
	TCCR1B |= (1 << WGM12);              // CTC mode
	OCR1A = 125;                         // Compare value for 1ms at 8MHz clock
	TIMSK |= (1 << OCIE1A);              // Enable compare A interrupt
	sei();                               // Enable global interrupts
	TCCR1B |= ((1 << CS10) | (1 << CS11)); // Start the timer with prescaler 64
}

void TIMER_Delay_ms(u16 milliseconds)
{
	timer_flag = 0;                      // Clear the timer flag
	while (milliseconds > 0)
	{
		if (timer_flag)
		{
			milliseconds--;               // Decrease the remaining milliseconds
			timer_flag = 0;               // Reset the timer flag
		}
	}
}

ISR(TIMER1_COMPA_vect)
{
	timer_flag = 1;                       // Set the timer flag
}

/********************************	TIMER0	 *********************************/
void TIMER0_Init(void)
{
	//1- Set the Wave Generation mode as normal
	CLEAR_BIT(TCCR0, WGM00);
	CLEAR_BIT(TCCR0, WGM01);

	//2- Enable Overflow Interrupt
	SET_BIT(TIMSK, TOIE0);

	//3- Set the prescaler 8Mhz / 8 = 1Mhz --> Timer Freq
	CLEAR_BIT(TCCR0, CS00);
	SET_BIT(TCCR0, CS01);
	CLEAR_BIT(TCCR0, CS02);
TCNT0 = 192;
}
void __vector_11(void)
{
	static u16 counter = 0;
	static u8 time=0, i=0;
	counter++;

	// Ovf Mode First App : 3906.25 --> Ticks_count
	if (counter == 390)
	{
		game_time++;
		counter = 0;
		TCNT0 = 192;

		// Increment seconds count
		if (game_time % 10 == 0) {
			time++;
			game_time_seconds++;
		
		}
	}
}


