#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_INTERFACE.h"
#include "CLCD_Interface.h"
#include "GLOBAL_INT1.h"
#include "TIMER_Interface.h"
#include "keys.h"
#include "ping_game.h"
#include <util/delay.h>
#include <avr/io.h>
u8 static x1=1,x2=1,y1=0,y2=15;
u8 Ball[8] = {0x00,0x04,0x0E,0x1F,0x1F,0x0E,0x04,0x00};
u8 static result1=0;
u8 static result2=0;
u8 static ball_posit[2]={-1,1};
u8 static press_key;
u8 status=10;
u8 game_End2=0;
u8 player1[8]={0x01,0x03,0x17,0x1F,0x1F,0x17,0x03,0x01};
u8 erase[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
u8 player2[8]={0x10,0x18,0x1D,0x1F,0x1F,0x1D,0x18,0x10};
u8 static temp=-1 ;

void BUZZ1() {
	SET_BIT(DDRC, 6);
	SET_BIT(PORTC,6);
	_delay_ms(50);
	CLEAR_BIT(PORTC, 6);
}
void BUZZ21() 
{
	SET_BIT(DDRC, 6);
	SET_BIT(PORTC,6);
	_delay_ms(1000);
	CLEAR_BIT(PORTC, 6);
}
void player2_move()
{
	if(game_End2==0)
	{
		
	
	switch(press_key)
	{
		case left:
		
		if(y2>=15)
		{
			CLCD_voidSendSpecialChar(player2,1,x2,15);
		}
		
		else
		{
			CLCD_voidSendSpecialChar(erase,3,x2,y2);
			y2=y2+1;
			CLCD_voidSendSpecialChar(player2,1,x2,y2);
			
		}
		
		break;
		case up:
		if(x2<=2)
		{
			CLCD_voidSendSpecialChar(erase,3,x2,y2);
			x2=x2+1;
			CLCD_voidSendSpecialChar(player2,1,x2,y2);
		}
		else
		{
			
		}
		break;
		case down:
		if(x2>=1)
		{
			CLCD_voidSendSpecialChar(erase,3,x2,y2);
			x2=x2-1;
			CLCD_voidSendSpecialChar(player2,1,x2,y2);
		}
		else
		{
			
		}
		break;
		case right:
		if(y2<9)
		{
			CLCD_voidSendSpecialChar(erase,3,x2,y2);
			CLCD_voidSendSpecialChar(player2,1,1,15);
			y2=15;
		}
		
		else
		{
			CLCD_voidSendSpecialChar(erase,3,x2,y2);
			y2=y2-1;
			CLCD_voidSendSpecialChar(player2,1,x2,y2);
		}
		
		break;
	}
}
}
/*unsigned int random_x_y(unsigned int min, unsigned int max)
{
    int r;
    const unsigned int range = 1 + max - min;
    const unsigned int buckets = RAND_MAX / range;
    const unsigned int limit = buckets * range;

    
    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}
*/
void player2_movecc()
{
	if (game_End2==0)
	{
	
	CLCD_voidSendSpecialChar(erase,3,x2,y2);
	/*
       x2=random_x_y(0, 3);
	   y2=random_x_y(15, 15);
*/
	if(x2<=2)
	{
		x2=x2+1;
		y2=15;
	}
	else
	{
		y2=15;
		x2=0;	
	}
	CLCD_voidSendSpecialChar(player2,1,x2,y2);
}
}
void player1_move()
{
	if (game_End2==0)
	{
	
	 press_key=key();
	 switch(press_key)
	 {
		 case left:
		 player2_movecc();
		
		 if(y1<1)
		 {
			 CLCD_voidSendSpecialChar(player1,0,1,0);
			 
		 }
		 
		 else
		 {
			 CLCD_voidSendSpecialChar(erase,3,x1,y1);
			 y1=y1-1;
			 CLCD_voidSendSpecialChar(player1,0,x1,y1);
		 }
		 
		 break;
		 case up:
		 player2_movecc();
		 
		 if(x1>=1)
		 {
			 CLCD_voidSendSpecialChar(erase,3,x1,y1);
			 x1=x1-1;
			 CLCD_voidSendSpecialChar(player1,0,x1,y1);
		 }
		 else
		 {
			 
		 }
		 
		 break;
		 case down:
		 player2_movecc();
		
		 if(x1<3)
		 {
			 CLCD_voidSendSpecialChar(erase,3,x1,y1);
			 x1=x1+1;
			 CLCD_voidSendSpecialChar(player1,0,x1,y1);
		 }
		 else
		 {
			 
		 }
		 break;
		 case right:
		 player2_movecc();
		
		 if(y1>=7)
		 {
			 CLCD_voidSendSpecialChar(erase,3,x1,y1);
			 CLCD_voidSendSpecialChar(player1,0,1,0);
			 y1=0;
		 }
		
		 else
		 {
			 CLCD_voidSendSpecialChar(erase,3,x1,y1);
			 y1=y1+1;
			 CLCD_voidSendSpecialChar(player1,0,x1,y1);
		 }
		 
		 break;
		 case shot:
		 
		 break;
	 }
	  return 0;
 }
 }
void ping_pong()
{
	if (game_End2==0)
	{
	
		CLCD_voidSendSpecialChar(player1,0,x1,y1);
		CLCD_voidSendSpecialChar(player2,1,x2,y2);
		ball();
		_delay_ms(5000);
		while(game_End2==0)
		{
			 player1_move();
			 ball_move_player1();
			 ball_move_player2();
		}
	}
		
}

void check_goal()
{
	
	
	if(game_End2==0)
	{
		
	
	if(ball_posit[1]>=15)
	{
		result1++;
		CLCD_voidSendCommand(1);
		 CLCD_voidGoTOxy(1,6);
		CLCD_voidPrintString("GOAL!!");
		 BUZZ21();
		_delay_ms(5000);
		CLCD_voidSendCommand(1);
		 CLCD_voidGoTOxy(1,6);
		CLCD_voidPrintString("GOAL!!");
		
		_delay_ms(5000);
		CLCD_voidSendCommand(1);
		
		 if(result1==3)
		 {
			 CLCD_voidSendCommand(1);
			 CLCD_voidGoTOxy(1,6);
			 CLCD_voidPrintString("P1 WIN!!");
			 BUZZ21();
			 _delay_ms(5000);
			 CLCD_voidSendCommand(1);
			 CLCD_voidGoTOxy(1,6);
			 CLCD_voidPrintString("P1 WIN!!");
			  BUZZ21();
			 _delay_ms(5000);
			 CLCD_voidSendCommand(1);
			  result2=result1=0;
			  game_End2=1;
	       }
	  	if (game_End2==0)
	  	{
		  	ping_pong();
	  	}
	}
 if(ball_posit[1]<=0)
	{
		result2++;
		CLCD_voidSendCommand(1);
	 CLCD_voidGoTOxy(1,6);
		CLCD_voidPrintString("GOAL!!");
		 BUZZ21();
		_delay_ms(5000);
		CLCD_voidSendCommand(1);
		 CLCD_voidGoTOxy(1,6);
		CLCD_voidPrintString("GOAL!!");
		
		_delay_ms(5000);
		CLCD_voidSendCommand(1);
		if(result2==3)
		{
			
			CLCD_voidSendCommand(1);
			 CLCD_voidGoTOxy(1,6);
			CLCD_voidPrintString("P2 WIN!!");
			 BUZZ2();
			_delay_ms(5000);
			CLCD_voidSendCommand(1);
			 CLCD_voidGoTOxy(1,6);
			CLCD_voidPrintString("P2 WIN!!");
			 BUZZ21();
			_delay_ms(5000);
			CLCD_voidSendCommand(1);
			 result2=result1=0;
			 game_End2=1;
		}
		if (game_End2==0)
		{
			ping_pong();
		}
		
		
	}
	
	}
}
void ball_move_player1()
{
	if (game_End2==0)
	{
	
	check_goal();
	if(ball_posit[1]==y1+1&&ball_posit[0]==x1)
	{
		BUZZ1();
		switch(x1)
		{
			case 0:
			player2_movecc();
			while(ball_posit[1]!=y2-1&&game_End2==0)
			{
				player2_movecc();
			while(ball_posit[0]<=2&&ball_posit[1]<=14)
			{
				player2_movecc();
				check_goal();
				CLCD_voidSendSpecialChar(erase,3,ball_posit[0],ball_posit[1]);
				ball_posit[1]=ball_posit[1]+1;
				ball_posit[0]=ball_posit[0]+1;
				CLCD_voidSendSpecialChar(Ball,4,ball_posit[0],ball_posit[1]);
				_delay_ms(1000);
				 player1_move();
				
				 ball_move_player2();
				check_goal();
				
			}
			
			if(ball_posit[0]>=3)
			{
				player2_movecc();
				while(ball_posit[0]>=1&&game_End2==0)
				{
					player2_movecc();
					check_goal();
					CLCD_voidSendSpecialChar(erase,3,ball_posit[0],ball_posit[1]);
					ball_posit[0]=ball_posit[0]-1;
					ball_posit[1]=ball_posit[1]+1;
					CLCD_voidSendSpecialChar(Ball,4,ball_posit[0],ball_posit[1]);
					_delay_ms(1000);
					player1_move();
					
					ball_move_player2();
					check_goal();
					
				}
				
			}
			}	
			break;
			case 1:
			player2_movecc();
			check_goal();
			while(ball_posit[1]<=y2-1&&game_End2==0)
			{
				player2_movecc();
				while(ball_posit[0]<=2&&ball_posit[1]<=y2-1)
				{
					player2_movecc();
					check_goal();
					CLCD_voidSendSpecialChar(erase,3,ball_posit[0],ball_posit[1]);
					ball_posit[1]=ball_posit[1]+1;
					ball_posit[0]=ball_posit[0]+1;
					CLCD_voidSendSpecialChar(Ball,4,ball_posit[0],ball_posit[1]);
					_delay_ms(1000);
					player1_move();
					
					ball_move_player2();
					check_goal();
					
				}
				
				if(ball_posit[0]>=3)
				{
					player2_movecc();
					while(ball_posit[0]>=1&&game_End2==0)
					{
						player2_movecc();
						check_goal();
						CLCD_voidSendSpecialChar(erase,3,ball_posit[0],ball_posit[1]);
						ball_posit[0]=ball_posit[0]-1;
						ball_posit[1]=ball_posit[1]+1;
						CLCD_voidSendSpecialChar(Ball,4,ball_posit[0],ball_posit[1]);
						_delay_ms(1000);	
					player1_move();
				
					ball_move_player2();
						check_goal();
						
					}
					
				}
			}
			
			break;
			case 2:
			player2_movecc();
			check_goal();
			while(ball_posit[1]<=15&&game_End2==0)
			{
				player2_movecc();
				check_goal();
			CLCD_voidSendSpecialChar(erase,3,ball_posit[0],ball_posit[1]);
			ball_posit[1]=ball_posit[1]+1;
			CLCD_voidSendSpecialChar(Ball,4,ball_posit[0],ball_posit[1]);
			_delay_ms(1000);
			ball_move_player2();
			player1_move();
			 check_goal();
			}
			break;
			case 3:
			player2_movecc();
			while(ball_posit[1]!=y2-1&&game_End2==0)
			{
				player2_movecc();
				while(ball_posit[0]<=2&&ball_posit[1]!=y2-1)
				{
					player2_movecc();
					check_goal();
					CLCD_voidSendSpecialChar(erase,3,ball_posit[0],ball_posit[1]);
					ball_posit[1]=ball_posit[1]+1;
					ball_posit[0]=ball_posit[0]+1;
					CLCD_voidSendSpecialChar(Ball,4,ball_posit[0],ball_posit[1]);
					_delay_ms(1000);
					player1_move();
					ball_move_player2();
					check_goal();
					
				}
				
				if(ball_posit[0]>=3)
				{
				player2_movecc();
					while(ball_posit[0]>=1&&game_End2==0)
					{
						player2_movecc();
						check_goal();
						CLCD_voidSendSpecialChar(erase,3,ball_posit[0],ball_posit[1]);
						ball_posit[0]=ball_posit[0]-1;
						ball_posit[1]=ball_posit[1]+1;
						CLCD_voidSendSpecialChar(Ball,4,ball_posit[0],ball_posit[1]);
						_delay_ms(1000);
						player1_move();
						ball_move_player2();
						check_goal();
						player2_movecc();
					}
					
				}
			}
			break;
		
	}
   }
}
}
void ball_move_player2()
{
	if (game_End2==0)
	{
	
	check_goal();
	if(ball_posit[1]==y2-1&&ball_posit[0]==x2)
	{
		BUZZ1();
		switch(x2)
		{
		case 0:
		player2_movecc();
			while(ball_posit[1]!=y1+1&&game_End2==0)
			{
				while(ball_posit[0]<=2&&ball_posit[1]!=y1+1)
				{
				    player1_move();
					check_goal();
				CLCD_voidSendSpecialChar(erase,3,ball_posit[0],ball_posit[1]);
				ball_posit[1]=ball_posit[1]-1;
				ball_posit[0]=ball_posit[0]+1;
				CLCD_voidSendSpecialChar(Ball,4,ball_posit[0],ball_posit[1]);
				_delay_ms(1000);
				 ball_move_player1();
				 check_goal();
			     }
				
			if(ball_posit[0]>=3&&ball_posit[1]<=y2-1)
			{
				while(ball_posit[0]>=1&&game_End2==0)
				{
						player1_move();
						check_goal();
					CLCD_voidSendSpecialChar(erase,3,ball_posit[0],ball_posit[1]);
					ball_posit[0]=ball_posit[0]-1;
					ball_posit[1]=ball_posit[1]-1;
					CLCD_voidSendSpecialChar(Ball,4,ball_posit[0],ball_posit[1]);
					_delay_ms(1000);
					ball_move_player1();
					check_goal();
					
				}
				
			}
		}
		
		break;
		case 1:
		player1_move();
		while(ball_posit[1]>=1&&game_End2==0)
		{
			player1_move();
			check_goal();
			CLCD_voidSendSpecialChar(erase,3,ball_posit[0],ball_posit[1]);
			ball_posit[1]=ball_posit[1]-1;
			CLCD_voidSendSpecialChar(Ball,4,ball_posit[0],ball_posit[1]);
			 player1_move();
			_delay_ms(1000);
			ball_move_player1();
			check_goal();
			player1_move();
		}
		
		break;
		case 2:
		player2_movecc();
		while(ball_posit[1]!=y1+1&&game_End2==0)
		{
			player1_move();
			check_goal();
			while(ball_posit[0]<=2&&ball_posit[1]!=y1+1)
			{
				player2_movecc();
			CLCD_voidSendSpecialChar(erase,3,ball_posit[0],ball_posit[1]);
			ball_posit[1]=ball_posit[1]-1;
			ball_posit[0]=ball_posit[0]+1;
			CLCD_voidSendSpecialChar(Ball,4,ball_posit[0],ball_posit[1]);
			_delay_ms(1000);
			
			ball_move_player1();
			check_goal();
			
		    }
			
		if(ball_posit[0]>=3)
		{
			player2_movecc();
				while(ball_posit[0]>=1&&game_End2==0)
			{
				player1_move();
				check_goal();
				CLCD_voidSendSpecialChar(erase,3,ball_posit[0],ball_posit[1]);
				ball_posit[0]=ball_posit[0]-1;
				ball_posit[1]=ball_posit[1]-1;
				CLCD_voidSendSpecialChar(Ball,4,ball_posit[0],ball_posit[1]);
				_delay_ms(1000);
				ball_move_player1();
				check_goal();
			}
			
		}
	}
	
		break;
		case 3:
		player2_movecc();
		check_goal();
		while(ball_posit[1]!=y1+1&&game_End2==0)
		{
			while(ball_posit[0]<=3&&ball_posit[1]!=y1+1)
			{
				player1_move();
				check_goal();
				CLCD_voidSendSpecialChar(erase,3,ball_posit[0],ball_posit[1]);
				ball_posit[1]=ball_posit[1]-1;
				ball_posit[0]=ball_posit[0]-1;
				CLCD_voidSendSpecialChar(Ball,4,ball_posit[0],ball_posit[1]);
				_delay_ms(1000);
				ball_move_player1();
				check_goal();
				
			}
			
			if(ball_posit[0]>=0&&ball_posit[0]<=2)
			{
				player2_movecc();
				while(ball_posit[0]>=0&&game_End2==0)
				{
					player1_move();
					check_goal();
					CLCD_voidSendSpecialChar(erase,3,ball_posit[0],ball_posit[1]);
					ball_posit[0]=ball_posit[0]+1;
					ball_posit[1]=ball_posit[1]-1;
					CLCD_voidSendSpecialChar(Ball,4,ball_posit[0],ball_posit[1]);
					_delay_ms(1000);
					ball_move_player1();
					check_goal();
					
				}
				
			}
		}
		
		break;	
       }
	}
}
}
void ball()
{
	
	if(game_End2==0)
	{
			if(temp<=2)
			{
				ball_posit[0]=temp+1;
				ball_posit[1]=1;
				temp =ball_posit[0];
			}
			else
			{
				ball_posit[1]=1;
				ball_posit[0]=0;
				temp =ball_posit[0];
			}
				CLCD_voidSendSpecialChar(Ball,4,ball_posit[0],ball_posit[1]);
			
	}
}
