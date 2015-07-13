#ifndef _SNAKE_GAME_
#define _SNAKE_GAME_
#include "share.c"
#include "stg0.c"
#include "stg1.c"
#include <stdlib.h>
void load_stg1(){
	_GAME_SNAKE_STG = 1;
	stg1();
}
void load_game(){
	while(1)
	{
		_GAME_SNAKE_STG = 0;
		stg0();
		load_stg1();
	}
}
#endif