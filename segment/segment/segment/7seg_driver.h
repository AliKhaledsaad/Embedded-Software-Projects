#ifndef seven_seg_driver_H_
#define seven_seg_driver_H_

#define F_CPU (16000000UL)
#include <util/delay.h>
#include "BIT_MATH.h"
#include "reg.h"
#include "std_types.h"

void Seven_seg_voidinit(void);
void Seven_seg_voidDisplay(int num);

void idx_7seg(uint8);



#endif 