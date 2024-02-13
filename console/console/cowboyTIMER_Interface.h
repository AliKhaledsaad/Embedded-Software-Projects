#ifndef TIMER_Interface_H_
#define TIMER_Interface_H_

#define TIMER0 0
#define TIMER1 1
#define TIMER2 2

#define HIGH 1
#define LOW  0

#define TCNTime0   0
#define OCR        1
#define ICR        2
#define OCR1a      3
#define OCR1b      4
#define TCNTime1   5

#define inverted 0
#define non_inverted 1
void TIMER_Init();
void TIMER_Delay_ms(u16 milliseconds);
void TIMER0_Init(void);

void __vector_11(void) __attribute__((signal));
//void __vector_11(void)__attribute__((signal));
//void __vector_10(void)__attribute__((signal));
//void __vector_2(void)__attribute__((signal));
//
//void SET_PRESCALER(u8 Timer_Kind,u8 BIT1,u8 BIT2,u8 BIT3);
//void SET_ValueForTimer(u8 kind_mode,u16 value);
//u16 Read_Timer(u8 kind_mode);
//
//void Timer0_NormalMode_Init();
//void Timer1_NormalMode_Init();
//void Timer0_PWMMode_Init(u8 Type);
//void Timer1_PWMMode_Init(u8 Type);
//void Timer2_CTCMode_Init();
#endif 