#ifndef _STG2_GAME_
#define _STG2_GAME_
#include "video_graph.c"
#include "../drivers/clock.c"
#include "../drivers/keyboard.c"
#include "../lib/math.c"
#include "share.c"
#include <stdlib.h>
int _GAME_SCORE_SNAKE = 0;
int _GAME_TABLE_MIN_Y = 4;
int _GAME_TABLE_MAX_Y = PIXEL_Y-5;
int _GAME_TABLE_MIN_X = 46;
int _GAME_TABLE_MAX_X = (PIXEL_X-5);
int _GAME_TABLE_SNAKE_Y = 4;
int _GAME_TABLE_SNAKE_X = 4;
int _GAME_TABLE_SNAKE_DIRECTION = 2; //1:UP,2:DOWN,3:LEFT,4:RIGHT
int _GAME_TABLE_SNAKE_LENGTH = 1;
int _GAME_TABLE_SNAKE_FETCH = 1;
int _GAME_TABLE_SNAKE_DELAY_MAX;
int _GAME_TABLE_SNAKE_DELAY;
int _GAME_TABLE_SNAKE_LEVELS;
int _GAME_TABLE_SNAKE_DELAY_GAME = 500;
int _GAME_SNAKE_SCORE_LVL;
//ESTRTCUTRA DE DATOS PARA LA SNAKE
short snake[3000][2];
//DEFINIMOS EL PROGRAMA
char* get_direction(){
	char* aux;
	if(_GAME_TABLE_SNAKE_DIRECTION == 1){
		aux = "UP";
	}
	else if(_GAME_TABLE_SNAKE_DIRECTION == 2){
		aux = "DOWN";
	}
	else if(_GAME_TABLE_SNAKE_DIRECTION == 3){
		aux = "LEFT";
	}
	else if(_GAME_TABLE_SNAKE_DIRECTION == 4){
		aux = "RIGHT";
	}
	return aux;
}
void make_cuad_score(){
	for(int i=4;i<45;i++){
		draw_game_pixel(i,4,_C_BLUE,1);
		draw_game_pixel(i,(PIXEL_Y-5),_C_BLUE,1);
	}
	for(int i=4;i<(PIXEL_Y-5);i++){
		draw_game_pixel(4,i,_C_BLUE,1);
		draw_game_pixel(44,i,_C_BLUE,1);
	}
}
void make_cuad_game(){
	for(int i=46;i<(PIXEL_X-5);i++){
		draw_game_pixel(i,4,_C_RED,1);
		draw_game_pixel(i,(PIXEL_Y-5),_C_RED,1);
	}
	for(int i=4;i<(PIXEL_Y-4);i++){
		draw_game_pixel(46,i,_C_RED,1);
		draw_game_pixel((PIXEL_X-5),i,_C_RED,1);
	}
}
void load_score_board(int mov){
	setcursor(2,3,1);
	printg("SNAKE",0,_C_CYAN);
	setcursor(2,5,1);
	printg("SCORE:",0,_C_YELLOW);
	setcursor(2,7,1);
	printg(itoa(_GAME_SCORE_SNAKE,"",10),0	,_C_WHITE);
	setcursor(2,9,1);
	printg("DIFFIC:",0,_C_YELLOW);
	setcursor(2,11,1);
	printg(get_diff_str(),0,_C_WHITE);
	setcursor(2,13,1);
	printg("LEVEL:",0,_C_YELLOW);
	setcursor(2,15,1);
	printg(itoa(_GAME_SNAKE_LEVEL,"",10),0,_C_WHITE);
	if(mov == 1){
		setcursor(2,17,1);
		printg("NEXT MOV:",0,_C_YELLOW);
		setcursor(2,19,1);
		printg("     ",0,_C_YELLOW);
		setcursor(2,19,1);
		printg(get_direction(),0,_C_WHITE);
	}
}
int hashj(int x,int seed){
    get_counter();
    int aleatorio = ((x*_CLOCK_COUNTER*seed)*23209)%seed;
    return aleatorio;
}
void put_fetch(){
	short limite_x = (PIXEL_X-6)-47;
	short limite_y = (PIXEL_Y-6)-5;
	while(1){
		int randx = hashj(snake[0][0],limite_x);
		while(1){
			randx = hashj(snake[0][0],limite_x);
			if(randx >= 0 && randx <=limite_x){
				break;
			}
		}
		int randy = hashj(snake[0][1],limite_y);
		while(1){
			randy = hashj(snake[0][1],limite_y);
			if(randy >= 0 && randy <=limite_y){
				break;
			}
		}
		int color = read_game_pixel(randx,randy);
		if(color == _C_BLACK){
			draw_game_pixel((randx+47),(randy+5),_C_CYAN,1);
			_GAME_TABLE_SNAKE_FETCH = 1;
			break;
		}
	}
}
void make_maze(int lvl){
	for(short m=0;m<lvl;m++){
		short limite_x = (PIXEL_X-6)-47;
		short limite_y = (PIXEL_Y-6)-5;
		int randx = hashj(m,limite_x);
		int randy = hashj((m*randx),limite_y);
		if((randy >= 0 && randy <=limite_y) &&(randx >= 0 && randx <=limite_x)){
			draw_game_pixel((randx+47),(randy+5),_C_WHITE,1);
		}
	}
}
void init_game(){
	put_in_buffer(72,80);
	if(_GAME_SNAKE_DIFFICULT == 0){
		_GAME_TABLE_SNAKE_DELAY_GAME = 500;
		_GAME_TABLE_SNAKE_LEVELS = 20;
		_GAME_SNAKE_SCORE_LVL = 200;
	}
	else if(_GAME_SNAKE_DIFFICULT == 1){
		_GAME_TABLE_SNAKE_DELAY_GAME = 300;
		_GAME_TABLE_SNAKE_LEVELS = 20;
		_GAME_SNAKE_SCORE_LVL = 200;
		make_maze(100);
	}
	else if(_GAME_SNAKE_DIFFICULT == 2){
		_GAME_TABLE_SNAKE_DELAY_GAME = 200;
		_GAME_TABLE_SNAKE_LEVELS = 60;
		_GAME_SNAKE_SCORE_LVL = 100;
		make_maze(500);
	}
	else if(_GAME_SNAKE_DIFFICULT == 3){
		_GAME_TABLE_SNAKE_DELAY_MAX = 100;
		_GAME_TABLE_SNAKE_LEVELS = 60;
		_GAME_SNAKE_SCORE_LVL = 100;
		make_maze(1000);
	}
	_GAME_TABLE_SNAKE_DELAY = _GAME_TABLE_SNAKE_DELAY_MAX;
	_GAME_TABLE_SNAKE_DIRECTION = 2;
	_GAME_SCORE_SNAKE = 0;
	_GAME_TABLE_SNAKE_LENGTH = 1;
	_GAME_SNAKE_LEVEL = 1;
	snake[0][0] = 55;
	snake[0][1] = 10;
	_GAME_TABLE_SNAKE_LENGTH++;
	snake[1][0] = 55;
	snake[1][1] = 9;
	draw_game_pixel(70,50,_C_CYAN,1);
	_GAME_TABLE_SNAKE_FETCH = 1;
}
short analize_mov(short x, short y){
	int color = read_game_pixel(x,y);
	if(color == _C_BLACK){
		return 0;
	}
	else if(color == _C_CYAN){
		_GAME_SCORE_SNAKE+=10;
		_GAME_TABLE_SNAKE_LENGTH++;
		_GAME_TABLE_SNAKE_FETCH = 0;
		_GAME_SNAKE_LEVEL = (_GAME_SCORE_SNAKE/_GAME_SNAKE_SCORE_LVL)+1;
		if(_GAME_SNAKE_LEVEL>_GAME_TABLE_SNAKE_LEVELS){
			_GAME_SNAKE_LEVEL = _GAME_TABLE_SNAKE_LEVELS;
		}
		_GAME_TABLE_SNAKE_DELAY = (_GAME_TABLE_SNAKE_DELAY_MAX/_GAME_TABLE_SNAKE_LEVELS)*(_GAME_TABLE_SNAKE_LEVELS-_GAME_SNAKE_LEVEL+1);

		return 1;
	}
	else if(color == _C_RED || color == _C_YELLOW || color == _C_WHITE){
		return 2;
	}
}
short generate_mov(){
	if(_GAME_TABLE_SNAKE_DIRECTION == 1){
		short x_aux = snake[0][0];
		short y_aux = snake[0][1];
		snake[0][1]--;
		short mov = analize_mov(snake[0][0],snake[0][1]);
		if(mov == 1 || mov == 0){
			draw_game_pixel(snake[0][0],snake[0][1],_C_YELLOW,1);
			for(short i=1;i<_GAME_TABLE_SNAKE_LENGTH;i++){
				short x_node = snake[i][0];
				short y_node = snake[i][1];
				snake[i][0] = x_aux;
				snake[i][1] = y_aux;
				x_aux = x_node;
				y_aux = y_node;
			}
			if(mov == 0){
				draw_game_pixel(x_aux,y_aux,_C_BLACK,1);
			}
		}
		else
		{
			return 0;
		}
	}
	else if(_GAME_TABLE_SNAKE_DIRECTION == 2){
		short x_aux = snake[0][0];
		short y_aux = snake[0][1];
		snake[0][1]++;
		short mov = analize_mov(snake[0][0],snake[0][1]);
		if(mov == 1 || mov == 0){
			draw_game_pixel(snake[0][0],snake[0][1],_C_YELLOW,1);
			for(short i=1;i<_GAME_TABLE_SNAKE_LENGTH;i++){
				short x_node = snake[i][0];
				short y_node = snake[i][1];
				snake[i][0] = x_aux;
				snake[i][1] = y_aux;
				x_aux = x_node;
				y_aux = y_node;
			}
			if(mov == 0){
				draw_game_pixel(x_aux,y_aux,_C_BLACK,1);
			}
		}
		else
		{
			return 0;
		}
	}
	else if(_GAME_TABLE_SNAKE_DIRECTION == 3){
		short x_aux = snake[0][0];
		short y_aux = snake[0][1];
		snake[0][0]--;
		short mov = analize_mov(snake[0][0],snake[0][1]);
		if(mov == 1 || mov == 0){
			draw_game_pixel(snake[0][0],snake[0][1],_C_YELLOW,1);
			for(short i=1;i<_GAME_TABLE_SNAKE_LENGTH;i++){
				short x_node = snake[i][0];
				short y_node = snake[i][1];
				snake[i][0] = x_aux;
				snake[i][1] = y_aux;
				x_aux = x_node;
				y_aux = y_node;
			}
			if(mov == 0){
				draw_game_pixel(x_aux,y_aux,_C_BLACK,1);
			}
		}
		else
		{
			return 0;
		}
	}
	else if(_GAME_TABLE_SNAKE_DIRECTION == 4){
		short x_aux = snake[0][0];
		short y_aux = snake[0][1];
		snake[0][0]++;
		short mov = analize_mov(snake[0][0],snake[0][1]);
		if(mov == 1 || mov == 0){
			draw_game_pixel(snake[0][0],snake[0][1],_C_YELLOW,1);
			for(short i=1;i<_GAME_TABLE_SNAKE_LENGTH;i++){
				short x_node = snake[i][0];
				short y_node = snake[i][1];
				snake[i][0] = x_aux;
				snake[i][1] = y_aux;
				x_aux = x_node;
				y_aux = y_node;
			}
			if(mov == 0){
				draw_game_pixel(x_aux,y_aux,_C_BLACK,1);
			}
		}
		else
		{
			return 0;
		}
	}
	return 1;	
}
void draw(){
	for(short i=0;i<_GAME_TABLE_SNAKE_LENGTH;i++)
	{
		draw_game_pixel(snake[i][0],snake[i][1],_C_YELLOW,1);
	}
}
int get_next_mov(){
	int key = read_key_scancode();
	int retorno = 1;
	if(key == 72 || key == 12){
		if(_GAME_TABLE_SNAKE_DIRECTION == 1){
			retorno = 0;
		} 
		else if(_GAME_TABLE_SNAKE_DIRECTION == 2){
			retorno = 0;
			return retorno;
		} 
		_GAME_TABLE_SNAKE_DIRECTION = 1;
	}
	else if(key == 80 || key == 10){
		if(_GAME_TABLE_SNAKE_DIRECTION == 2){
			retorno = 0;
		} 
		else if(_GAME_TABLE_SNAKE_DIRECTION == 1){
			retorno = 0;
			return retorno;
		} 
		_GAME_TABLE_SNAKE_DIRECTION = 2;
	}
	else if(key == 77 || key == 17){
		if(_GAME_TABLE_SNAKE_DIRECTION == 4){
			retorno = 0;
		} 
		else if(_GAME_TABLE_SNAKE_DIRECTION == 3){
			retorno = 0;
			return retorno;
		} 
		_GAME_TABLE_SNAKE_DIRECTION = 4;
	}
	else if(key == 75 || key == 15){
		if(_GAME_TABLE_SNAKE_DIRECTION == 3){
			retorno = 0;
		} 
		else if(_GAME_TABLE_SNAKE_DIRECTION == 4){
			retorno = 0;
			return retorno;
		} 
		_GAME_TABLE_SNAKE_DIRECTION = 3;
	}
	return retorno;
}
void game_over(){
	for(int i=35;i<135;i++){
		draw_game_pixel(i,30,_C_BLUE,1);
		draw_game_pixel(i,70,_C_BLUE,1);
	}
	for(int i=34;i<136;i++){
		draw_game_pixel(i,29,_C_WHITE,1);
		draw_game_pixel(i,71,_C_WHITE,1);
	}
	for(int i=30;i<70;i++){
		draw_game_pixel(35,i,_C_BLUE,1);
		draw_game_pixel(134,i,_C_BLUE,1);
	}
	for(int i=29;i<71;i++){
		draw_game_pixel(34,i,_C_WHITE,1);
		draw_game_pixel(135,i,_C_WHITE,1);
	}
	for(int i=36;i<134;i++){
		for(int j=31;j<70;j++){
			draw_game_pixel(i,j,_C_BLACK,1);
		}
	}
	setcursor(16,10,1);
	printg("GAME OVER!!",0,_C_YELLOW);
	setcursor(17,12,1);
	printg("SCORE:",0,_C_YELLOW);
	printg(itoa(_GAME_SCORE_SNAKE,"",10),0,_C_YELLOW);
	setcursor(12,14,1);
	printg("PRESS START TO BACK",0,_C_YELLOW);
	if(_GAME_SNAKE_HIGHSCORE < _GAME_SCORE_SNAKE){
		_GAME_SNAKE_HIGHSCORE = _GAME_SCORE_SNAKE;
	}
	while(1){
		int key = read_key();
		if(key == 13){
			break;
		}
	}
}
void stg2(){
	clear_screen();
	init_game();
	draw();
	while(1){
		if(_GAME_TABLE_SNAKE_FETCH == 0){
			put_fetch();
		}
		set_border();
		int mov = get_next_mov();
		short move = generate_mov();
		if(move == 0){
			game_over();
			break;
		}
		else
		{
			make_cuad_score();
			make_cuad_game();
			load_score_board(mov);
		}
		timer(_GAME_TABLE_SNAKE_DELAY);
	}
}
#endif
