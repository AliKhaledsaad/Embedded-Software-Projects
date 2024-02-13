/*
 * LED_DRIVER.c
 *
 * Created: 15/04/2023 05:40:41 م
 *  Author: Mohamed Ali Mohamed Hassanein G5
 */ 
#include "LED_DRIVER.h"

void LED_INIT(LED_CONF* led){
	SET_BIT(*(led->DDR),led->PIN);
}

void LED_ON(LED_CONF* led){
	SET_BIT(*(led->PORT),led->PIN);
}

void LED_OFF(LED_CONF* led){
	CLR_BIT(*(led->PORT),led->PIN);
}

void LED_TOGGLE(LED_CONF* led){
	TOGGLE_BIT(*(led->PORT),led->PIN);
}

