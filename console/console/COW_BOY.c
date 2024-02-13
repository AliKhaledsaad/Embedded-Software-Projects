#include "COW_BOY.h"
#include <avr/io.h>
#include "SevenSegments_Interface.h"
#include <avr/interrupt.h>
#include "keys.h"
#include "CLCD_Interface.h"
#include "cowboyTIMER_Interface.h"
#include <util/delay.h>
#include "INTERRUPT_Interface.h"
u8 game_End=0;
volatile uint32_t game_time_seconds;
uint8_t min = 255; // Initialize min to a large value
uint8_t game_over_flag = 0;
uint8_t out_flag = 0;
int i, j;
u8 KEY_VALUE, x = 0, y = 15, x2 = 0, y2 = 0;


/* Custom character bitmaps */
u8 customChar1[] = {
	0b00100,
	0b00100,
	0b01110,
	0b10101,
	0b00100,
	0b01010,
	0b10001,
	0b00000
};

u8 customChar2[] = {
	0b00100,
	0b11110,
	0b00101,
	0b01111,
	0b10100,
	0b01010,
	0b10001,
	0b00000
};

u8 customChar3[] = {
	0b10001,
	0b01010,
	0b00100,
	0b10101,
	0b01110,
	0b00100,
	0b00100,
	0b00000
};

u8 shot[] = {
	0b00000,
	0b00000,
	0b00100,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000
};

u8 shot2[] = {
	0b00000,
	0b00000,
	0b00100,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000
};

void INIT_POSITION() {
	CLCD_voidSendSpecialChar(customChar1, 0, 0, 15);
	CLCD_voidSendSpecialChar(customChar2, 1, 0, 0);
}

void move_xchar1(uint8_t delay) {
	move_ychar1(KEY_VALUE);

	// GOING DOWN
	if (KEY_VALUE == 2) {
		x++;

		if (x > 3) {
			CLCD_voidGoTOxy(3, y);
			CLCD_voidSendData(' ');
			x = 0;
			} else {
			CLCD_voidGoTOxy(x - 1, y);
			CLCD_voidSendData(' ');
		}
		CLCD_voidSendSpecialChar(customChar1, 0, x, y);
	}

	// GOING UP
	else if (KEY_VALUE == 1) {
		CLCD_voidGoTOxy(x, y);
		CLCD_voidSendData(' ');
		if (x == 0) {
			x = 3;
			} else {
			x--;
		}

		CLCD_voidGoTOxy(x, y);
		CLCD_voidSendSpecialChar(customChar1, 0, x, y);
	}

	uint8_t delay_temp = delay + 30;
	TIMER_Delay_ms(delay_temp);

	// char2 movement
	// GOING DOWN
	if (KEY_VALUE == 2) {
		x2++;

		if (x2 > 3) {
			CLCD_voidGoTOxy(3, y2);
			CLCD_voidSendData(' ');
			x2 = 0;
			} else {
			CLCD_voidGoTOxy(x2 - 1, y2);
			CLCD_voidSendData(' ');
		}
		CLCD_voidSendSpecialChar(customChar2, 1, x2, y2);
	}

	// GOING UP
	else if (KEY_VALUE == 1) {
		CLCD_voidGoTOxy(x2, y2);
		CLCD_voidSendData(' ');
		if (x2 == 0) {
			x2 = 3;
			} else {
			x2--;
		}

		CLCD_voidGoTOxy(x2, y2);
		CLCD_voidSendSpecialChar(customChar2, 1, x2, y2);
	}

	KEY_VALUE = 0;
}

void point(uint8_t copy_x2, uint8_t delay) {
	BUZZ();

	// shot2
	for (i = 1; i < 16; i++) {
		if (copy_x2 == x && i == y || x2 == x && y == y2) {
			BUZZ2();
			move_xchar1(delay);
			CLCD_voidSendSpecialChar(customChar3, 3, x, y);
			game_over_flag = 1;
			_delay_ms(3000);
			GAME_OVER();
			break;
		}

		if (i != 1) {
			CLCD_voidGoTOxy(copy_x2, i - 1);
			CLCD_voidSendData(' ');
			CLCD_voidSendSpecialChar(shot, 2, copy_x2, i);

			// Check for key press and break the loop if a key is pressed
			KEY_VALUE = key();
			if (KEY_VALUE != 0xff) {
				if (KEY_VALUE != 1 && KEY_VALUE != 3) {
					if (KEY_VALUE == 4) {
						BUZZ();
						for (j = y - 1; j >= 0; j--) {
							if (x == x2 && j == y2) {
								BUZZ2();
								move_xchar1(delay);
								CLCD_voidSendSpecialChar(customChar3, 3, x2, y2);
								game_over_flag = 1;
								_delay_ms(3000);
								won();
							}

							if (j != 14) {
								CLCD_voidGoTOxy(x, j + 1);
								CLCD_voidSendData(' ');
								CLCD_voidSendSpecialChar(shot2, 4, x, j);
								// Check for key press and break the loop if a key is pressed
								KEY_VALUE = key();
								if (KEY_VALUE != 0xff) {
									CLCD_voidGoTOxy(x, j);
									CLCD_voidSendData(' ');
									point(x2, 40);
									break;
								}
								TIMER_Delay_ms(40);
							}
							if (j == 0) {
								CLCD_voidGoTOxy(x, j);
								CLCD_voidSendData(' ');
							}
						}
					} else
					CLCD_voidGoTOxy(copy_x2, i);
					CLCD_voidSendData(' ');
					move_xchar1(40);
					break;
				} else
				move_ychar1(KEY_VALUE);
			}
			TIMER_Delay_ms(70);
		}
		if (i == 15) {
			CLCD_voidGoTOxy(copy_x2, i);
			CLCD_voidSendData(' ');
		}
	}
}
void pointmid(uint8_t copy_x2, uint8_t delay) {
	BUZZ();

	// shot2
	for (i = 1; i < 16; i++) {
		if (copy_x2 == x && i == y || x2 == x && y == y2) {
			BUZZ2();
			move_xchar1(delay);
			CLCD_voidSendSpecialChar(customChar3, 3, x, y);
			game_over_flag = 1;
			_delay_ms(3000);
			GAME_OVER();
			break;
		}

		if (i != 1) {
			CLCD_voidGoTOxy(copy_x2, i - 1);
			CLCD_voidSendData(' ');
			CLCD_voidSendSpecialChar(shot, 2, copy_x2, i);

			// Check for key press and break the loop if a key is pressed
			KEY_VALUE = key();
			if (KEY_VALUE != 0xff) {
				if (KEY_VALUE != 1 && KEY_VALUE != 3) {
					if (KEY_VALUE == 4) {
						BUZZ();
						for (j = y - 1; j >= 0; j--) {
							if (x == x2 && j == y2) {
								BUZZ2();
								move_xchar1(delay);
								CLCD_voidSendSpecialChar(customChar3, 3, x2, y2);
								game_over_flag = 1;
								_delay_ms(3000);
								won();
							}

							if (j != 14) {
								CLCD_voidGoTOxy(x, j + 1);
								CLCD_voidSendData(' ');
								CLCD_voidSendSpecialChar(shot2, 4, x, j);
								// Check for key press and break the loop if a key is pressed
								KEY_VALUE = key();
								if (KEY_VALUE != 0xff) {
									CLCD_voidGoTOxy(x, j);
									CLCD_voidSendData(' ');
									pointmid(x2, 40);
									break;
								}
								TIMER_Delay_ms(50);
							}
							if (j == 0) {
								CLCD_voidGoTOxy(x, j);
								CLCD_voidSendData(' ');
							}
						}
					} else
					CLCD_voidGoTOxy(copy_x2, i);
					CLCD_voidSendData(' ');
					move_xchar1(40);
					break;
				} else
				move_ychar1(KEY_VALUE);
			}
			TIMER_Delay_ms(40);
		}
		if (i == 15) {
			CLCD_voidGoTOxy(copy_x2, i);
			CLCD_voidSendData(' ');
		}
	}
}
void pointhard(uint8_t copy_x2, uint8_t delay) {
	BUZZ();

	// shot2
	for (i = 1; i < 16; i++) {
		if (copy_x2 == x && i == y || x2 == x && y == y2) {
			BUZZ2();
			move_xchar1(delay);
			CLCD_voidSendSpecialChar(customChar3, 3, x, y);
			game_over_flag = 1;
			_delay_ms(3000);
			GAME_OVER();
			break;
		}

		if (i != 1) {
			CLCD_voidGoTOxy(copy_x2, i - 1);
			CLCD_voidSendData(' ');
			CLCD_voidSendSpecialChar(shot, 2, copy_x2, i);

			// Check for key press and break the loop if a key is pressed
			KEY_VALUE = key();
			if (KEY_VALUE != 0xff) {
				if (KEY_VALUE != 1 && KEY_VALUE != 3) {
					if (KEY_VALUE == 4) {
						BUZZ();
						for (j = y - 1; j >= 0; j--) {
							if (x == x2 && j == y2) {
								BUZZ2();
								move_xchar1(delay);
								CLCD_voidSendSpecialChar(customChar3, 3, x2, y2);
								game_over_flag = 1;
								_delay_ms(3000);
								won();
							}

							if (j != 14) {
								CLCD_voidGoTOxy(x, j + 1);
								CLCD_voidSendData(' ');
								CLCD_voidSendSpecialChar(shot2, 4, x, j);

								// Check for key press and break the loop if a key is pressed
								KEY_VALUE = key();
								if (KEY_VALUE != 0xff) {
									CLCD_voidGoTOxy(x, j);
									CLCD_voidSendData(' ');
									point(x2, 40);
									break;
								}
								TIMER_Delay_ms(40);
							}
							if (j == 0) {
								CLCD_voidGoTOxy(x, j);
								CLCD_voidSendData(' ');
							}
						}
					} else
					CLCD_voidGoTOxy(copy_x2, i);
					CLCD_voidSendData(' ');
					move_xchar1(40);
					break;
				} else
				move_ychar1(KEY_VALUE);
			}
			TIMER_Delay_ms(39);
		}
		if (i == 15) {
			CLCD_voidGoTOxy(copy_x2, i);
			CLCD_voidSendData(' ');
		}
	}
}


void game() 
{
	uint8_t current_score = game_time_seconds;

	if (out_flag == 1) {
		CLCD_ClearDisplay();
		return;
	}

	if (game_over_flag == 1) {
		game_over_flag = 0;
		i = 1, x = 0, y = 15, x2 = 0, y2 = 0;

		// Game over condition is met, exit the game loop
		// return;
	}

	TIMER0_Init();
	SevenSegments_PowerON();
	game_time_seconds = 0;
	CLCD_voidGoTOxy(0, 0);
	CLCD_voidPrintString("WELCOME, Cowboy");
	CLCD_voidGoTOxy(1, 0);
	CLCD_voidPrintString("1-Easy");
	CLCD_voidGoTOxy(2, 0);
	CLCD_voidPrintString("2-Med");
	CLCD_voidGoTOxy(3, 0);
	CLCD_voidPrintString("3-Hard");
	uint8_t KPDVALUE = key();

	if (KPDVALUE == 0) {
		TIMER0_Init();
		CLCD_ClearDisplay();
		INIT_POSITION();
		TIMER0_Init();
		uint8_t level_up = 0;
		while (1) {
			// Check the game_over_flag
			if (game_over_flag == 1) {
				// Game over condition is met, exit the game loop
				break;
			}
			point(x2, 40);
			// level_up=level_up+10;
				game_End=1;
		}
		} else if (KPDVALUE == 1) {
		TIMER0_Init();
		CLCD_ClearDisplay();
		INIT_POSITION();
		uint8_t level_up = 0;
		while (1) {
			// Check the game_over_flag
			if (game_over_flag == 1) {
				// Game over condition is met, exit the game loop
				break;
			}
			pointmid(x2, 40);
			// level_up=level_up+10;
		}
		game_End=1;
		}
			
		 else if (KPDVALUE == 2) 
		 {
		TIMER0_Init();
		CLCD_ClearDisplay();
		INIT_POSITION();
		uint8_t level_up = 0;
		while (1) {
			// Check the game_over_flag
			if (game_over_flag == 1) {
				// Game over condition is met, exit the game loop
				break;
				
			}
			pointhard(x2, 40);
			// level_up=level_up+10;
		}
		game_End=1;
		} 
		
}
		

void move_ychar1(uint8_t KEY_VALUE) {
	if (KEY_VALUE == 3) {
		y++;
		if (y > 15) {
			CLCD_voidGoTOxy(x, 15);
			CLCD_voidSendData(' ');
			y = 0;
			} else {
			CLCD_voidGoTOxy(x, y - 1);
			CLCD_voidSendData(' ');
		}
		CLCD_voidSendSpecialChar(customChar1, 0, x, y);
		} else if (KEY_VALUE == 0) {
		CLCD_voidGoTOxy(x, y);
		CLCD_voidSendData(' ');

		if (y == 0) {
			y = 15;
			} else {
			y--;
		}

		CLCD_voidGoTOxy(x, y);
		CLCD_voidSendSpecialChar(customChar1, 0, x, y);
	}
}

void GAME_OVER() {
	CLCD_ClearDisplay();
	TIMER_Delay_ms(10);
	CLCD_voidGoTOxy(0, 4);
	CLCD_voidPrintString("GAME OVER");
	CLCD_voidGoTOxy(1, 4);
	CLCD_voidPrintString("TRY again");
	TIMER_Delay_ms(2000);
	CLCD_ClearDisplay();
}

void COW_BOY() {
	TIMER1_Init();
	TIMER0_Init();
	sei();
	
	while(game_End==0)
	{
		game();
		
	}
	
}

void won() {
	if (min>game_time_seconds)
	{
		min=game_time_seconds;
	}
	CLCD_ClearDisplay();
	TIMER_Delay_ms(10);
	CLCD_voidGoTOxy(0, 4);
	CLCD_voidPrintString("YOU won!");
	CLCD_voidGoTOxy(1, 4);
	CLCD_voidPrintString("TIME: ");
	CLCD_voidSendNumber(game_time_seconds);
	SvenSegments_SendNumber(game_time_seconds);
	CLCD_voidGoTOxy(2, 0);
	CLCD_voidPrintString("mini score: ");
	CLCD_voidSendNumber(min); // Display minimum time
	TIMER_Delay_ms(5000);
	CLCD_ClearDisplay();
}

void BUZZ() 
{
	SET_BIT(DDRC, 6);
	SET_BIT(PORTC, 6);
	_delay_ms(50);
	CLEAR_BIT(PORTC, 6);
}

void BUZZ2() 
{
	SET_BIT(DDRC, 6);
	SET_BIT(PORTC, 6);
	_delay_ms(1000);
	CLEAR_BIT(PORTC, 6);
}
