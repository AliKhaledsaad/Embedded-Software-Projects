#ifndef CLCD_Interface_H_
#define CLCD_Interface_H_
#include "STD_TYPES.h"
/*Configration*/
#define CLCD_PORT_DATA DIO_PORTA
#define CLCD_PORT_CONTROL DIO_PORTB
#define CONTROL_RS DIO_PIN0
#define CONTROL_RW DIO_PIN1
#define CONTROL_E  DIO_PIN2
/*********************************************************/
void CLCD_voidInit(void);
void CLCD_voidSendCommand(u8 Copy_u8Command);
void CLCD_voidSendData(u8 Copy_u8Data);
void CLCD_voidPrintString(u8 Copy_u8String[]);
void CLCD_voidGoTOxy(u8 x,u8 y);
void CLCD_voidSendNumber(s32 number);
void CLCD_ClearDisplay();
void CLCD_PowerON();
void CLCD_voidSendSpecialChar(u8 *copy_u8pattern, u8 copy_u8pattern_num, u8 x, u8 y);
#endif /* CLCD_H_ */