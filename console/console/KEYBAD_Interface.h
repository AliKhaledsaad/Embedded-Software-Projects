#ifndef KEYBAD_Interface_H_
#define KEYBAD_Interface_H_
#include <avr/io.h>
/****************************************************************
                          User Configuration
****************************************************************/
/****************************************************************/
#define  KPD_ARR   {{10,9,8,7},{6,6,5,4},{3,3,2,1},{'R',0,'=',' '}};
/****************************************************************/
#define KPD_PORT DIO_PORTC

#define KPD_COLUMN0_PIN  DIO_PIN0
#define KPD_COLUMN1_PIN	 DIO_PIN1
#define KPD_COLUMN2_PIN	 DIO_PIN2
#define KPD_COLUMN3_PIN	 DIO_PIN3

#define KPD_ROW0_PIN	DIO_PIN4
#define KPD_ROW1_PIN	DIO_PIN5
#define KPD_ROW2_PIN	DIO_PIN6
#define KPD_ROW3_PIN	DIO_PIN7
/*************************************************************/
#define COLUMN_NUMBER 4
#define ROW_NUMBER 4
/**************************************************************/
void KPD_PowerON();
u8 KPD_u8GetPressedKey(void);

#endif /* KEYBAD_H_ */