#ifndef _SHARE_GAME_
#define _SHARE_GAME_
int _GAME_SNAKE_STG = 0;
int _GAME_SNAKE_DIFFICULT = 0;
int _GAME_SNAKE_LEVEL = 1;
int _GAME_SNAKE_HIGHSCORE = 0;
int _GAME_DIFF_EASY = 0;
int _GAME_DIFF_MEDIUM = 1;
int _GAME_DIFF_HARD = 2;
int _GAME_DIFF_ADIN = 3;
//ESCRIBIMOS LAS FUNCIONES COMPARTIDAS
void write_diff(){
	char *difficult;
	if(_GAME_SNAKE_DIFFICULT == 0){
		difficult = "Easy";
	}
	else if(_GAME_SNAKE_DIFFICULT == 1){
		difficult = "Medium";
	}
	else if(_GAME_SNAKE_DIFFICULT == 2){
		difficult = "Hard";
	}
	else if(_GAME_SNAKE_DIFFICULT == 3){
		difficult = "Adin";
	}
	setcursor(1,23,1);
	printg("Difficult: ",0,_C_WHITE);
	printg(difficult,0,_C_WHITE);
}
void write_highscore(){
	setcursor(1,22,1);
	printg("Highscore: ",0,_C_WHITE);
	printg(itoa(_GAME_SNAKE_HIGHSCORE,"",10),0,_C_WHITE);
}
void set_diff(int diff){
	_GAME_SNAKE_DIFFICULT = diff;
}
char* get_diff_str(){
	char *difficult;
	if(_GAME_SNAKE_DIFFICULT == 0){
		difficult = "Easy";
	}
	else if(_GAME_SNAKE_DIFFICULT == 1){
		difficult = "Medium";
	}
	else if(_GAME_SNAKE_DIFFICULT == 2){
		difficult = "Hard";
	}
	else if(_GAME_SNAKE_DIFFICULT == 3){
		difficult = "Adin";
	}
	return difficult;
}
#endif