/*
 * timer0.h
 *
 * Created: 25/05/2023 03:33:54 ص
 *  Author: DON
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_


#include "reg.h"
#include "BIT_MATH.h"
#include "std_types.h"
#define I_BIT 7
#define	NUMBER_OF_OVERFLOW 62
typedef void(*g_callBackPtr)(uint8);


void timer0_init(void);
void timer0_delay(g_callBackPtr ,uint8 );
//void timer2_delay_1ms(uint8);





#endif /* TIMER0_H_ */