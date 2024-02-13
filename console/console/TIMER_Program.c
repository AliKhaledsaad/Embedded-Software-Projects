#include "BIT_MATH.h"
#include "DIO_INTERFACE.h"
#include "TIMER_Interface.h"
#include "STD_TYPES.h"
#include "INTERRUPT_Interface.h"
#include <avr/interrupt.h>
#include <avr/io.h>
u8 t=0;
void SET_PRESCALER(u8 Timer_Kind,u8 BIT1,u8 BIT2,u8 BIT3){
	
	if (Timer_Kind==TIMER0||Timer_Kind==TIMER2)
	{
		(BIT1==0)?CLEAR_BIT(TCCR0,CS00):SET_BIT(TCCR0,CS00);
		(BIT2==0)?CLEAR_BIT(TCCR0,CS01):SET_BIT(TCCR0,CS01);
		(BIT3==0)?CLEAR_BIT(TCCR0,CS02):SET_BIT(TCCR0,CS02);
	}
	else if (Timer_Kind==TIMER1)
	{
		(BIT1==0)?CLEAR_BIT(TCCR1B,CS10):SET_BIT(TCCR1B,CS10);
		(BIT2==0)?CLEAR_BIT(TCCR1B,CS11):SET_BIT(TCCR1B,CS11);
		(BIT3==0)?CLEAR_BIT(TCCR1B,CS12):SET_BIT(TCCR1B,CS12);
	}
}

void SET_ValueForTimer(u8 kind_mode, u16 value) {
	switch (kind_mode)
	 {
		case TCNTime0:TCNT0 = value;t=TCNT0;break;
		case OCR:OCR0 = value;break;
		case ICR:ICR1 = value;break;
		case OCR1a:OCR1A = value;break;
		case OCR1b:OCR1B = value;break;
		case TCNTime1:TCNT1 = value;break;
	}
}

u16 Read_Timer(u8 kind_mode) {
	u16 timerValue = 0;

	switch (kind_mode) {
		case TCNTime0:timerValue = TCNT0;break;
		case OCR:timerValue = OCR0;break;
		case ICR:timerValue = ICR1;break;
		case OCR1a:timerValue = OCR1A;break;
		case OCR1b:timerValue = OCR1B;break;
        case TCNTime1:timerValue = TCNT1;break;
	}

	return timerValue;
}

void Timer0_NormalMode_Init(){
	
	/*SET TIMER IN NORMAL MODE*/
	CLEAR_BIT(TCCR0,WGM00);
	CLEAR_BIT(TCCR0,WGM01);
	/*SET PRESCALER AS DEFAULT*/
	SET_PRESCALER(TIMER0,LOW,HIGH,LOW);
	/*ENABLE INTRRUPT FLAG*/
	SET_BIT(TIMSK,TOIE0);
}

void Timer2_CTCMode_Init(){
	
	/*SET TIMER IN NORMAL MODE*/
	CLEAR_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
	/*SET PRESCALER AS DEFAULT*/
	SET_PRESCALER(TIMER0,LOW,HIGH,LOW);
	/*ENABLE INTRRUPT FLAG*/
	SET_BIT(TIMSK,OCIE0);
}

void Timer1_NormalMode_Init(){
	/* Fast PWM Timer1 */
	CLEAR_BIT(TCCR1A,WGM10);
	CLEAR_BIT(TCCR1A,WGM11);
	CLEAR_BIT(TCCR1B,WGM12);
	CLEAR_BIT(TCCR1B,WGM13);
	/*SET PRESCALER 8BIT MODE AS DEFAULT*/
	SET_PRESCALER(TIMER1,LOW,HIGH,LOW);
}

void Timer0_PWMMode_Init(u8 Type){
	/*SET TIMER IN FAST PMW  MODE*/
	SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
	/*SET PRESCALER IN 8BIT MODE AS DEFAULT*/
	SET_PRESCALER(TIMER0,LOW,HIGH,LOW);	
	if (Type==inverted)
	{
		/*SET TIMER IN INVERTED */
		SET_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
	}
	else if (Type==non_inverted)
	{
		/*SET TIMER IN NIN_INVERTED */
		CLEAR_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
	}
}

void Timer1_PWMMode_Init(u8 Type){
	
/*PWM WITH ICR1 as top*/
	SET_BIT(TCCR1B,WGM13);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1A,WGM11);
	CLEAR_BIT(TCCR1A,WGM10);
/*SET PRESCALER IN 8BIT MODE AS DEFAULT*/
	SET_PRESCALER(TIMER1,LOW,HIGH,LOW);
/*SET FAST PWM MODE*/
	if (Type==inverted)
	{
	  /*NON INVERTED PWM*/
	   SET_BIT(TCCR1A,COM1A0);
	   SET_BIT(TCCR1A,COM1A1);
	}
	else if (Type==non_inverted)
	{
	 /*SET TIMER IN NIN_INVERTED */
		CLEAR_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
	}
}




/*void __vector_11(void){
	
	static u16 counter=0;
	counter++;
	if (counter==3907)
	{
		CLCD_ClearDisplay();
		CLCD_voidPrintString("Normal ON");
		TOGGLE_BIT(PORTA,0);
		counter=0;
		TCNT0=t;
	}
}


void __vector_10(void)
{

	static	u16 Local_u16Counter=0;

	Local_u16Counter++;
	if (Local_u16Counter==4000)
	{
		CLCD_ClearDisplay();
		CLCD_voidPrintString("CTC ON");
		TOGGLE_BIT(PORTA,0);
		//TOGGLE_BIT(PORTA,1);
		TCNT0=t;
		Local_u16Counter=0;
	}*/

	//if(Local_u16Counter==5)
	//{
//
		//CLEAR_BIT(PORTB,0);
		//CLEAR_BIT(PORTB,1);
	//}
	//else if (Local_u16Counter==20)
	//{
		//Local_u16Counter=0;
		//SET_BIT(PORTB,0);
		//SET_BIT(PORTB,1);
		//
	//}
//}

//void Timer_CTC_Init(){
///*SET TIMER IN NORMAL MODE*/
//SET_BIT(TCCR0,WGM00);
//SET_BIT(TCCR0,WGM01);
///*SET PWM MODE */
//SET_BIT(TCCR0,COM01);
//CLR_BIT(TCCR0,COM00);
///*SET PRELOAD VALUE*/
//TCNT0=0;
///*SET OCR0*/
//OCR0=10;
///*SET Pre_Scaler in 8Bit MODE*/
//CLR_BIT(TCCR0,CS00);
//SET_BIT(TCCR0,CS01);
//CLR_BIT(TCCR0,CS02);
/////*Enable Global Interrupt*/
////SET_BIT(SREG,7);
/////*ENABLE OVER_FLOW INTRUPT*/
////SET_BIT(TIMSK,OCIE0);
//




//void Timer1_INIT(){
///*NON INVERTED PWM*/
//SET_BIT(TCCR1A,COM1A1);
//CLEAR_BIT(TCCR1A,COM1A0);
///*PWM WITH ICR1*/
//
//SET_BIT(TCCR1B,WGM13);
//SET_BIT(TCCR1B,WGM12);
//SET_BIT(TCCR1A,WGM11);
//CLEAR_BIT(TCCR1A,WGM10);
//
///*PRESCALLER BY 8*/
//CLEAR_BIT(TCCR1B,CS10);
//SET_BIT(TCCR1B,CS11);
//CLEAR_BIT(TCCR1B,CS12);
//}
