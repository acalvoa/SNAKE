#ifndef _STG0_GAME_
#define _STG0_GAME_
#include "video_graph.c"
#include "../drivers/clock.c"
#include "../drivers/keyboard.c"
#include "share.c"
void wait_for_start(){
	while(1){
		int key = read_key();
		if(key == 13){
			break;
		}
		setcursor(10,12,0);
		printg("PRESS START TO PLAY...",0,_C_YELLOW);
		timer(600);
		setcursor(10,12,0);
		printg("                      ",0,_C_YELLOW);
		timer(600);
	}
}
void stg0(){
	clear_screen();
	setcursor(11,11,0);
	printg("SNAKE: ADIN EDITION",0,_C_YELLOW);
	set_border();
	wait_for_start();
}
#endif
