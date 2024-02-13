


#ifndef REG_H_
#define REG_H_

#define DDRA *(volatile unsigned char*)(0x3A)
#define PINA *(volatile unsigned char*)(0x39)
#define PORTA *(volatile unsigned char*)(0x3B)

#define DDRB *(volatile unsigned char*)(0x37)
#define PINB *(volatile unsigned char*)(0x36)
#define PORTB *(volatile unsigned char*)(0x38)

#define DDRC *(volatile unsigned char*)(0x34)
#define PINC *(volatile unsigned char*)(0x33)
#define PORTC *(volatile unsigned char*)(0x35)

#define DDRD *(volatile unsigned char*)(0x31)
#define PIND *(volatile unsigned char*)(0x30)
#define PORTD *(volatile unsigned char*)(0x32)
//TIMERS
#define TCNT0 *(volatile unsigned char*)(0x52)
#define TCCR0 *(volatile unsigned char*)(0x53)
#define TIFR  *(volatile unsigned char*)(0x58)

#define PIN0 (0)
#define PIN1 (1)
#define PIN2 (2)
#define PIN3 (3)
#define PIN4 (4)
#define PIN5 (5)
#define PIN6 (6)
#define PIN7 (7)




#endif