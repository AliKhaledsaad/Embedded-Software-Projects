#include "DIO_INTERFACE.h"
#include "STD_TYPES.h"
#include "KEYBAD_Interface.h"
#include "BIT_MATH.h"
void KPD_PowerON()
{
	DIO_u8SetPortDir(KPD_PORT,0x0f);
	DIO_u8SetPortValue(KPD_PORT,0xff);
}
u8 KPD_u8GetPressedKey(void){
	u8 stat;
	u8 value_pressed=0xff, col_index,row_index;
	
	static u8 Local_u8KPDARR[ROW_NUMBER][COLUMN_NUMBER]=KPD_ARR;
	static u8 KPDRowArr[ROW_NUMBER]={KPD_ROW0_PIN,KPD_ROW1_PIN,KPD_ROW2_PIN,KPD_ROW3_PIN};
	static u8 KPDColumnArr[COLUMN_NUMBER]={KPD_COLUMN0_PIN,KPD_COLUMN1_PIN,KPD_COLUMN2_PIN,KPD_COLUMN3_PIN};
		
	for (col_index=0;col_index<COLUMN_NUMBER;col_index++)
	{
		DIO_u8SetPinValue(KPD_PORT,KPDColumnArr[col_index],DIO_LOW);
		for (row_index=0;row_index<ROW_NUMBER;row_index++)
		{
			DIO_u8GetPinValue(KPD_PORT,KPDRowArr[row_index],&stat);
			if (DIO_LOW==stat)
			{
				value_pressed=Local_u8KPDARR[row_index][col_index];
			
				while(DIO_LOW==stat)
				{
					DIO_u8GetPinValue(KPD_PORT,KPDRowArr[row_index],&stat);
				}
				return value_pressed;
		  }
		}
		DIO_u8SetPinValue(KPD_PORT,KPDColumnArr[col_index],DIO_HIGH);
	}
	return 0xff;
}