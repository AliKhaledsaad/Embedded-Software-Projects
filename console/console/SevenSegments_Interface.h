#ifndef SEVENSEGMENTS_INTERFACE_H_
#define SEVENSEGMENTS_INTERFACE_H_
#include "STD_TYPES.h"
#include "DIO_INTERFACE.h"

#define SS_PORT  DIO_PORTD

#define ss_PIN0  DIO_PIN0
#define ss_PIN1  DIO_PIN1
#define ss_PIN2  DIO_PIN2
#define ss_PIN3  DIO_PIN3

#define E1       DIO_PIN4
#define E2       DIO_PIN5

void SevenSegments_Init();
void SevenSegments_PowerON();
void SevenSegments_Enable(u8 num);
void SevenSegments_Disable(u8 num);
void SvenSegments_SendNumber(u8 num );
void SevenSegments_DisplayDigit(u8 Digit);
#endif /* SEVENSEGMENTS_INTERFACE_H_ */