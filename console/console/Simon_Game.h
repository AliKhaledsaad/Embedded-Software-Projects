#ifndef SIMON_GAME_H_
#define SIMON_GAME_H_

#include "STD_TYPES.h"

#define flag 1
#define new_time 2



u8 Level_Validity(u8 LED_List[],u8 User_Ticks[],u8 lenght);

void Game();

void Get_UserResponse(u8 *LED_List,u8  length);

void Level_Init(u8 level_num,u8*LED_List,u8*length);

void Simon_Say(u8 level_num);

void Simon_Timer();

void Stop_SimonTimer();

void Level_1();

void Level_2();

void Level_3();

void Level_4();

void Level_5();

void Level_6();

void Level_7();

void Level_8();

void Level_9();

void Level_10();


#endif /* SIMON GAME_H_ */