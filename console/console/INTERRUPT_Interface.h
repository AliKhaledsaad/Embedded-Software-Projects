/*
 * INTERRUPT.h
 *
 * Created: 8/16/2023 12:18:46 PM
 *  Author: Mohamed
 */ 
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#ifndef INTERRUPT_Interface_H_
#define INTERRUPT_Interface_H_
/*---------------CONTROLSENSE------------------------*/
#define LOW_LEVEL 1
#define ANY_CHANGE 2
#define FALLING_EDGE 3
#define RISSING_EDGE 4
/*---------------INTTURPT NUM------------------------*/
#define INT0 1
#define INT1 2
#define INT2 3

/*------------------------------------------FUNCTIOS--------------------------------------*/

u8 EXIT_u8IntSetsenseControl(u8 copy_Intnum, u8 copy_sense);
u8 EXIT_u8IntEnable(u8 copy_Intnum);
u8 EXIT_u8IntDisable(u8 copy_Intnum);

//void INT_Inturr()
void __vector_1(void) __attribute__((signal));
void __vector_2(void) __attribute__((signal));
void __vector_3(void) __attribute__((signal));


#endif /* INTERRUPT_H_ */