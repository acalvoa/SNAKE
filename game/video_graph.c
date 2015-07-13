#ifndef _VIDEO_GAME_
#define _VIDEO_GAME_
#include "../drivers/video.c"
#define PIXEL_X (_W_VIDEO/2)
#define PIXEL_Y (_H_VIDEO/2)
void draw_game_pixel(int x, int y, int color, int page){
	x = x*2;
	y = y*2;
	draw_pixel(x, y, color, page);
	draw_pixel((x+1), y, color, page);
	draw_pixel(x, (y+1), color, page);
	draw_pixel((x+1), (y+1), color, page);
}
int draw_game_line(int x1,int y1, int x2, int y2, int color, int page){
	x1 *= 2;
	y1 *= 2;
	x2 *= 2;
	y2 *= 2;
	if(_GMODE_ == 1){
		for(int i=x1;i<=x2;i++){
			for(int j=y1;j<=y2;j++){
				draw_pixel(i,j,color,1);
			}	
		}
		return 1;
	}
	else
	{
		return 0;
	}
}
int read_game_pixel(int x, int y){
	x = x*2;
	y = y*2;
	return read_pixel(x,y, 1);
}
void set_border(){
	//	PRIMER BORDE
	for(int i=0;i<PIXEL_X;i++){
		draw_game_pixel(i,0,_C_WHITE,1);
		draw_game_pixel(i,(PIXEL_Y-1),_C_WHITE,1);
	}
	for(int i=0;i<PIXEL_Y;i++){
		draw_game_pixel(0,i,_C_YELLOW,1);
		draw_game_pixel((PIXEL_X-1),i,_C_YELLOW,1);
	}
	// SEGUNDO BORDE
	for(int i=2;i<PIXEL_X-2;i++){
		draw_game_pixel(i,2,_C_YELLOW,1);
		draw_game_pixel(i,(PIXEL_Y-3),_C_YELLOW,1);
	}
	for(int i=2;i<PIXEL_Y-2;i++){
		draw_game_pixel(2,i,_C_WHITE,1);
		draw_game_pixel((PIXEL_X-3),i,_C_WHITE,1);
	}
}
#endif