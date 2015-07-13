#ifndef _VIDEO_DRIVER_
#define _VIDEO_DRIVER_
//DEFINIMOS CONSTANTES DE ANCHO DEL MODO GRAFICO
#define _W_VIDEO 320
#define _H_VIDEO 200
//DEFINIMOS LA PALETA DE COLORES
#define _C_BLACK 0x00
#define _C_BLUE 0x01
#define _C_GREEN 0x02
#define _C_CYAN 0x03
#define _C_RED 0x04
#define _C_MAGENTA 0x05
#define _C_BROWN 0x06
#define _C_LIGHT_GRAY 0x07
#define _C_DARK_GRAY 0x08
#define _C_LIGHT_BLUE 0x09
#define _C_LIGHT_GREEN 0x0A
#define _C_LIGHT_CYAN 0x0B
#define _C_LIGHT_RED 0x0C
#define _C_LIGHT_MAGENTA 0x0D
#define _C_YELLOW 0xE
#define _C_WHITE 0x0F
//VARIABLES DE VIDEO CONTROL
int _GMODE_ = 0;
//DECLARAMOS LAS FUNCIONES DEL DRIVER
void set_graphicmode(){
	__asm__(
	    "int $0x10" : : "a"(0x0000|0x0013)
	);
	_GMODE_ = 1;
}
void set_textmode(){
	__asm__(
	    "int $0x10" : : "a"(0x0000|0x0000)
	);
	_GMODE_ = 0;
}
//ESCRITURA DE PIXELES
int draw_pixel(int x, int y, int color, int page){
	if(_GMODE_ == 1){
		if((x<_W_VIDEO && x >=0) && (y<_H_VIDEO && y >=0))
		{
			__asm__(
				"int $0x10" : : "a"(0x0C00|color), "b"((page<<8)), "c"(x), "d"(y)
			);
			return 1;
		}
		else
		{
			return 2;
		}
	}
	else
	{
		return 0;
	}
}
int read_pixel(int x, int y, int page){
	if(_GMODE_ == 1){
		if((x<_W_VIDEO && x >=0) && (y<_H_VIDEO && y >=0))
		{
			int color;
			__asm__(
				"int $0x10" :"=a"(color) : "a"(0x0D00), "b"((page<<8)), "c"(x), "d"(y)
			);
			return (color & 0xff);
		}
	}
	else
	{
		return -1;
	}
}
int set_blackground(int color, int page){
	if(_GMODE_ == 1){
		for(int i=0;i<_W_VIDEO;i+=2){
			for(int j=0;j<_H_VIDEO;j+=2){
				draw_pixel(i,j,color,1);
				draw_pixel(i,j+1,color,1);
				draw_pixel((i+1),(j),color,1);
				draw_pixel((i+1),(j+1),color,1);
			}	
		}
		return 1;
	}
	else
	{
		return 0;
	}
}
//FUNCION PARA ESCRIBIR EN MODO TEXTO
int strleng(const char *str){
	const char *s;
	for(s=str; *s; ++s);
	return(s - str);
}
void printcharg(const char pStr,int page, int color) {
	__asm__ (
	    "int $0x10" : : "a"(0x0e00|pStr), "b" ((page<<8)|color)
	);
}
void print_charg_ascii(int pStr,int page, int color) {
	__asm__ (
	    "int $0x10" : : "a"(0x0e00|pStr), "b" ((page<<8)|color)
	);
}
void printg(const char* txt,int page, int color){
	for(int i=0; i<strleng(txt); i++){
		printcharg(txt[i],page,color);
	}
}
//FUNCIONES DE SETEO DE FUNCIONM
void setcursor(int x, int y, int page){
	__asm__ (""
	    "int $0x10" : : "a"(0x0200), "b" (page), "d"((y<<8)|x)
	);
}
//FUNCION PARA LIMPIEZA DE PANTALL
void clear_screen(){
	if(_GMODE_ == 1){
		__asm__(
		    "int $0x10" : : "a"(0x0000|0x0013)
		);
	}
}
#endif
