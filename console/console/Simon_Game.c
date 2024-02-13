#define F_CPU 8000000U
#include "Simon_Game.h"
#include "STD_TYPES.h"
#include "DIO_INTERFACE.h"
#include "keys.h"
#include "Leds_Interface.h"
#include "CLCD_Interface.h"
#include "TIMER_Interface.h"
#include "SevenSegments_Interface.h"
#include "Buzzer_Interface.h"
#include <util/delay.h>
#include <avr/interrupt.h>
int num=0;

u8 right=0,left=0;
s8 Tick=0;
void Level_1()
{
	for (u8 i=0;i<2;i++)//0
	{
       Flashing_Led(RED_LED);
	}
	
     Flashing_Led(YELLOW_LED);
	   
	
	for (u8 i=0;i<3;i++)//3
	{
      Flashing_Led(BLUE_LED);
	   
	}
	Tick=30;
	Stop_SimonTimer();
	Simon_Timer();
} 

void Level_2()
{
	for (u8 i=0;i<1;i++)
	{
      Flashing_Led(RED_LED);
	   
	}
	
	for (u8 i=0;i<3;i++)
	{
      Flashing_Led(YELLOW_LED);
	}
	for (u8 i=0;i<2;i++)
	{
      Flashing_Led(GREEN_LED);
	   
	}
		Tick=30;
		Simon_Timer();

}

void Level_3()
{
	for (u8 i=0;i<3;i++)
	{
      Flashing_Led(RED_LED);
	   
	}
	for (u8 i=0;i<5;i++)
	{
      Flashing_Led(GREEN_LED);
	   
	}
	Tick=30;
	Simon_Timer();	

}

void Level_4()
{
	for (u8 i=0;i<1;i++)
	{
      Flashing_Led(YELLOW_LED);
	}
	
	for (u8 i=0;i<1;i++)
	{
      Flashing_Led(RED_LED);
	   
	}
	
	for (u8 i=0;i<2;i++)
	{
      Flashing_Led(GREEN_LED);
	   
	}
	
	for (u8 i=0;i<1;i++)
	{
      Flashing_Led(BLUE_LED);
	}
		Tick=30;
		Simon_Timer();	

}

void Level_5()
{
	Flashing_Led(GREEN_LED);
	Flashing_Led(YELLOW_LED);
	Flashing_Led(GREEN_LED);
	Flashing_Led(YELLOW_LED);
	Flashing_Led(BLUE_LED);
		Tick=30;
		Simon_Timer();	

}

void Level_6()
{
	for (u8 i=0;i<3;i++)
	{
      Flashing_Led(RED_LED);
	}
	
    Flashing_Led(BLUE_LED);
	
    Flashing_Led(GREEN_LED);
	
    Flashing_Led(YELLOW_LED);
		Tick=30;
		Simon_Timer();	

}

void Level_7()
{	
	
	for (u8 i=0;i<2;i++)
	{
      Flashing_Led(YELLOW_LED);
	}
	
    Flashing_Led(GREEN_LED);
	
    Flashing_Led(BLUE_LED);
	
    Flashing_Led(RED_LED);
		Tick=30;
		Simon_Timer();	

}

void Level_8()
{
    Flashing_Led(RED_LED);
	
    Flashing_Led(GREEN_LED);
      
    Flashing_Led(BLUE_LED);
	  
    Flashing_Led(RED_LED);
	
    Flashing_Led(BLUE_LED);
	
    Flashing_Led(GREEN_LED);
		Tick=30;
		Simon_Timer();	

}

void Level_9()
{
	
	Flashing_Led(GREEN_LED);
	
	for (u8 i=0;i<1;i++)
	{
      Flashing_Led(BLUE_LED);
	}
	
	for (u8 i=0;i<3;i++)
	{
		Flashing_Led(YELLOW_LED);
	}
		Tick=30;
		Simon_Timer();	


}

void Level_10()
{
    Flashing_Led(BLUE_LED);

    Flashing_Led(YELLOW_LED);
		
    Flashing_Led(GREEN_LED);

    Flashing_Led(BLUE_LED);
	
    Flashing_Led(RED_LED);
	
    Flashing_Led(YELLOW_LED);
	Tick=30;
	Simon_Timer();	

}

void Simon_Say(u8 level_num)
{
	switch(level_num)
	{
		case 1:Level_1();break;
		case 2:Level_2();break;
		case 3:Level_3();break;
		case 4:Level_4();break;
		case 5:Level_6();break;
		case 7:Level_7();break;
		case 8:Level_8();break;
		case 9:Level_9();break;
		case 10:Level_10();break;
		default:break;
	}
}

void Level_Init(u8 level_num,u8*LED_List,u8*length)
{
	switch (level_num)
	{
		case 1:
		// Initialize LED_List for case 1
		LED_List[0] = RED_LED;
		LED_List[1] = RED_LED;
		LED_List[2] = YELLOW_LED;
		LED_List[3] = BLUE_LED;
		LED_List[4] = BLUE_LED;
		LED_List[5] = BLUE_LED;
		*length = 6;
		break;

		case 2:
		// Initialize LED_List for case 2
		LED_List[0] = RED_LED;
		LED_List[1] = YELLOW_LED;
		LED_List[2] = YELLOW_LED;
		LED_List[3] = YELLOW_LED;
		LED_List[4] = GREEN_LED;
		LED_List[5] = GREEN_LED;
		*length = 6;
		break;

		case 3:
		// Initialize LED_List for case 3
		LED_List[0] = RED_LED;
		LED_List[1] = RED_LED;
		LED_List[2] = RED_LED;
		LED_List[3] = GREEN_LED;
		LED_List[4] = GREEN_LED;
		LED_List[5] = GREEN_LED;
		LED_List[6] = GREEN_LED;
		LED_List[7] = GREEN_LED;
		*length = 8;
		break;

		case 4:
		// Initialize LED_List for case 4
		LED_List[0] = YELLOW_LED;
		LED_List[1] = RED_LED;
		LED_List[2] = GREEN_LED;
		LED_List[3] = GREEN_LED;
		LED_List[4] = BLUE_LED;
		*length = 5;
		break;

		case 5:
		// Initialize LED_List for case 5
		LED_List[0] = GREEN_LED;
		LED_List[1] = YELLOW_LED;
		LED_List[2] = GREEN_LED;
		LED_List[3] = YELLOW_LED;
		LED_List[4] = BLUE_LED;
		*length = 5;
		break;

		case 6:
		// Initialize LED_List for case 6
		LED_List[0] = RED_LED;
		LED_List[1] = RED_LED;
		LED_List[2] = RED_LED;
		LED_List[3] = BLUE_LED;
		LED_List[4] = GREEN_LED;
		LED_List[5] = YELLOW_LED;
		*length = 6;
		break;

		case 7:
		// Initialize LED_List for case 7
		LED_List[0] = YELLOW_LED;
		LED_List[1] = YELLOW_LED;
		LED_List[2] = GREEN_LED;
		LED_List[3] = BLUE_LED;
		LED_List[4] = RED_LED;
		*length =5;
		break;

		case 8:
		// Initialize LED_List for case 8
		LED_List[0] = RED_LED;
		LED_List[1] = GREEN_LED;
		LED_List[2] = BLUE_LED;
		LED_List[3] = RED_LED;
		LED_List[4] = BLUE_LED;
		LED_List[5] = GREEN_LED;
		*length = 6;
		break;

		case 9:
		// Initialize LED_List for case 9
		LED_List[0] = GREEN_LED;
		LED_List[1] = BLUE_LED;
		LED_List[2] = YELLOW_LED;
		LED_List[3] = YELLOW_LED;
		LED_List[4] = YELLOW_LED;
		*length = 5;
		break;

		case 10:
		// Initialize LED_List for case 10
		LED_List[0] = BLUE_LED;
		LED_List[1] = YELLOW_LED;
		LED_List[2] = GREEN_LED;
		LED_List[3] = BLUE_LED;
		LED_List[4] = RED_LED;
		LED_List[5] = YELLOW_LED;
		*length = 6;
		break;

		default:
		break;
	}
}

void Get_UserResponse(u8 *User_Ticks,u8 length)
{
	u8 counter=0;
	Simon_Timer();
	while(counter<length&&Tick!=-1)
	{
		u8 x=key()+4;
		switch (x) {
			case RED_LED:
			User_Ticks[counter] = RED_LED;
			Flashing_Led(RED_LED);
			counter++;
			break;
			case YELLOW_LED:
			User_Ticks[counter] = YELLOW_LED;
			Flashing_Led(YELLOW_LED);
			counter++;
			break;
			case GREEN_LED:
			User_Ticks[counter] = GREEN_LED;
			Flashing_Led(GREEN_LED);
			counter++;
			break;
			case BLUE_LED:
			User_Ticks[counter] = BLUE_LED;
			Flashing_Led(BLUE_LED);
			counter++;
			break;
			default:
			// Handle the case where x is not one of the expected values.
			break;
		}
	}
}

void Time_Out()
{
	CLCD_ClearDisplay();
	CLCD_voidGoTOxy(1,3);
	CLCD_voidPrintString("Time Out!!");
	_delay_ms(1000);
}
u8 Level_Validity(u8 LED_List[],u8 User_Ticks[],u8 lenght)
{
	u8 state=1;
	
	if (Tick<=0)
	{
		state=0;
		Stop_SimonTimer();
		Time_Out();
		return state;
	}
	else
	{
		Stop_SimonTimer();
	}
	
	for (u8 i=0;i<lenght;i++)
	{
		if (LED_List[i]!=User_Ticks[i])
		{
			state=0;
			return state;
		}
	}
	return state;
}

void Simon_Timer()
{
	Timer2_CTCMode_Init();
	SET_ValueForTimer(OCR,250);
	sei();
}

void Stop_SimonTimer()
{
	TCCR0 = 0; 
	TIMSK &= ~(1 << OCIE0);
}

void Simon_win()
{
	u8 f=1;
	for (u8 i=0;i<5;i++)
	{
		if (f)
		{
			CLCD_ClearDisplay();
			CLCD_voidGoTOxy(0,4);
			CLCD_voidPrintString("You Win");
			f=0;
		}
		Flashing_LedGroup();
	}
}

void Simon_Loss()
{
	CLCD_ClearDisplay();
	CLCD_voidGoTOxy(0,4);
	CLCD_voidPrintString("Game Over");
	Buzzer_Enable(Loser);
}

u8 Restart_OR_Exit()
{
	u8 g=0,z=0;
	CLCD_ClearDisplay();
	while(!g)
	{
		CLCD_voidGoTOxy(1,0);
		CLCD_voidPrintString("1-Start");
		CLCD_voidGoTOxy(2,0);
		CLCD_voidPrintString("2-Exit");
		z=key();
		(z!=0xff)?g++:g;
	}
	if (z==1)
	{
		right=0;
		left=0;
		Tick=0;
	}
	else
	{
		CLCD_ClearDisplay();
	}
	return z;
}

void Show_LevelANDScore(u8 level,u8 score)
{
	CLCD_ClearDisplay();
	CLCD_voidGoTOxy(2,0);
	CLCD_voidPrintString("Your Level: ");
	CLCD_voidSendNumber(level);
	
	CLCD_voidGoTOxy(3,0);
	CLCD_voidPrintString("Your Score: ");
	CLCD_voidSendNumber(score);
}

void Simon_TimerInterfacing()
{
	static u8 b=1;//boolean value
	static u16 counter1=0;
	static u16 counter2=0;
	counter1++;
	counter2++;

	if (counter2==40)
	{

		if (b)
		{
			SevenSegments_Disable(2);
			SevenSegments_Enable(1);
			SevenSegments_DisplayDigit(right);
			b=0;
			counter2=0;
		}
		else
		{
			SevenSegments_Disable(1);
			SevenSegments_Enable(2);
			SevenSegments_DisplayDigit(left);
			b=1;
			counter2=0;
		}
	}
	if (counter1==4000&&Tick>-1)
	{
		right=Tick%10;
		left=Tick/10;
		counter1=0;
		Tick--;
	}
}

void Game()
{
	u8 Counter_Level = 1;
	u8 Score= 0;
	u8 Level=Counter_Level;
	u8 LCD_Show=1;
  while (1)
  {
	  u8 LED_List[20]={0};
	  u8 User_Ticks[20]={0};
	  u8 lenght=0;
	  if (LCD_Show)
	  {
		  CLCD_ClearDisplay();
         Show_LevelANDScore(Level,Score);
		 LCD_Show=0;
		 _delay_ms(2000);
	  }
	  Level_Init(Counter_Level,&LED_List,&lenght);
	  Simon_Say(Counter_Level);
	  Get_UserResponse(&User_Ticks,lenght);
	  u8 result=Level_Validity(LED_List,User_Ticks,lenght);
	  if (result)
	  {
		  Counter_Level++;
		  LCD_Show=1;
		  Level=Counter_Level;
		  Score+=lenght;
		  u8 f=1;
		  Simon_win();
	  }
	  else 
	  {
	     Simon_Loss();
		 Show_LevelANDScore(Level,Score);
		 _delay_ms(3000);
	     Counter_Level=1;
		 LCD_Show=1;
		 Level=Counter_Level;
		 Score=0;
		 if (Restart_OR_Exit())
		 {
			 continue;
		 }
		 else
		    break;
	  }
  }
}

ISR(TIMER0_COMP_vect)
{
  Simon_TimerInterfacing();
}

