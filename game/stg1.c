#ifndef _STG1_GAME_
#define _STG1_GAME_
#include "video_graph.c"
#include "../drivers/clock.c"
#include "../drivers/keyboard.c"
#include "share.c"
#include "stg2.c"
int BACK_TO_FLAG = 0;
void get_difficult(){
	while(1){
		int key = read_key();
		if(key == 49){
			set_diff(0);
			break;
		}
		else if(key == 50){
			set_diff(1);
			break;
		}
		else if(key == 51){
			set_diff(2);
			break;
		}
		else if(key == 52){
			set_diff(3);
			break;
		}	
	}
}
void select_diff(){
	clear_screen();
	set_border();
	setcursor(8,5,1);
	printg("SNAKE: SELECT DIFFICULT",0,_C_YELLOW);
	draw_game_line(23,25,133,25,_C_YELLOW,1);
	setcursor(8,8,1);
	printg("1.- Easy",0,_C_YELLOW);
	setcursor(8,9,1);
	printg("2.- Medium",0,_C_YELLOW);
	setcursor(8,10,1);
	printg("3.- Hard",0,_C_YELLOW);
	setcursor(8,11,1);
	printg("4.- Adin",0,_C_YELLOW);
	get_difficult();
	write_diff();
}
void select_menu(){
	while(1){
		int key = read_key();
		if(key == 49){
			stg2();
			break;
		}
		else if(key == 50){
			select_diff();
			break;
		}
		else if(key == 51){
			BACK_TO_FLAG = 1;
			break;
		}
	}
}
void stg1(){
	while(1){
		BACK_TO_FLAG = 0;
		clear_screen();
		setcursor(8,5,1);
		printg("SNAKE: ADIN EDITION MENU\n\r\0",0,_C_YELLOW);
		set_border();
		draw_game_line(23,25,133,25,_C_YELLOW,1);
		setcursor(8,8,1);
		printg("1.- Start Game",0,_C_YELLOW);
		setcursor(8,9,1);
		printg("2.- Select Difficult",0,_C_YELLOW);
		setcursor(8,10,1);
		printg("3.- Back to screen",0,_C_YELLOW);
		write_diff();
		write_highscore();
		select_menu();
		if(BACK_TO_FLAG == 1) break;
	}
}
#endif
