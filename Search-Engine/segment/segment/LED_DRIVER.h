/*
 * LED_DRIVER.h
 *
 * Created: 15/04/2023 05:40:26 م
 *  Author: Mohamed Ali Mohamed Hassanein G5
 */ 


#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_


#include "BIT_MATH.h"
#include "reg.h"
#include "std_types.h"


//RED MACROS
#define  LED_DDR_RED DDRB
#define  LED_PORT_RED PORTB
#define  LED_PIN_NUM_RED PIN7
//GREEN MACROS
#define  LED_DDR_GREEN DDRA
#define  LED_PORT_GREEN PORTA
#define  LED_PIN_NUM_GREEN PIN4
//BLUE MACROS
#define  LED_DDR_BLUE DDRA
#define  LED_PORT_BLUE PORTA
#define  LED_PIN_NUM_BLUE PIN5
//YELLOW MACROS
#define  LED_DDR_YELLOW DDRA
#define  LED_PORT_YELLOW PORTA
#define  LED_PIN_NUM_YELLOW PIN6


typedef struct LED_CONF
{
	volatile uint8 *DDR;
	volatile uint8 *PORT;
	uint8 PIN;
}LED_CONF;

void LED_INIT(LED_CONF* led);
void LED_ON(LED_CONF* led);
void LED_OFF(LED_CONF* led);
void LED_TOGGLE(LED_CONF* led);


#endif /* LED_DRIVER_H_ */