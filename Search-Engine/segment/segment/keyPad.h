/*
 * keyPad.h
 *
 
 *  Author: Mhmd
 */ 



#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "BIT_MATH.h"
#include "reg.h"
#define F_CPU (16000000UL)
#include "util/delay.h"
typedef unsigned char uint8;
#define INVALID_KEYPAD_PRESS (0xFF)

void keyPadInit(void);
uint8 keyPadGetValue(void);






#endif /* KEYPAD_H_ */