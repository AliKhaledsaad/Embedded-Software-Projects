#ifndef LEDS_INTERFACE_H_
#define LEDS_INTERFACE_H_

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>
#include <avr/io.h>

#define LEDS_PORT DIO_PORTB
#define RED_LED    4
#define YELLOW_LED 5
#define GREEN_LED  6
#define BLUE_LED   7

void LEDS_PowerON(u8 pins);

void Toogle_LED(u8 led_num);

void Flashing_Led(u8 led_num);

void Flashing_LedGroup();
#endif /* LEDS_INTERFACE_H_ */