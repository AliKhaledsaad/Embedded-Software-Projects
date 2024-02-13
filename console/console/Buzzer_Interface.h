#ifndef BUZZER_INTERFACE_H_
#define BUZZER_INTERFACE_H_

#include "DIO_INTERFACE.h"

#define Buzzer_Pin DIO_PIN3
#define Buzzer_Port DIO_PORTB

#define RED_Tone    0
#define Yellow_Tone 1
#define Green_Tone  2
#define Blue_Tone   3
#define Winer       4
#define Loser       5

void Buzzer_PowerON();

void Buzzer_Enable(u8 Tone_Type);

void Toogle_Buzzer();

#endif /* BUZZER_INTERFACE_H_ */