#ifndef _CLOCK_DRIVER_
#define _CLOCK_DRIVER_
#include "../lib/types.c"
int _CLOCK_HOUR;
int _CLOCK_MINUTES;
int _CLOCK_SEC;
int _CLOCK_MSEC;
int _CLOCK_COUNTER;
void get_time(){
	int c,d;
	__asm__(
	    "int $0x1A" :"=c"(c),"=d"(d) : "a"(0x0200)
	);
	_CLOCK_HOUR = (c>>8) & 0xff;
	_CLOCK_MINUTES = c & 0xff;
	_CLOCK_SEC = (d>>8) & 0xff;
}
void get_counter(){
	int c,d;
	__asm__(
	    "int $0x1A" :"=c"(c),"=d"(d) : "a"(0x0000)
	);
	_CLOCK_COUNTER = (c<<16)|d;
}
void get_clock(){
	get_counter();
	_CLOCK_HOUR = _CLOCK_COUNTER / 65543;
    int Remainder = _CLOCK_COUNTER % 65543;
  	_CLOCK_MINUTES   = Remainder / 1092;
    Remainder = Remainder % 1092;
 	_CLOCK_SEC = (Remainder*100) / 1821;
  	_CLOCK_MSEC = ((Remainder*100) % 1821)*10;
}
void sleep(int sec){
	int enlapsed = 0;
	get_clock();
	int last_sec = _CLOCK_SEC;
	do{
		get_clock();
		if(_CLOCK_SEC != last_sec){
			enlapsed++;
			last_sec = _CLOCK_SEC;
		}
	}while(enlapsed <= sec);
}
void timer(int msec){
	get_clock();
	int acumulado = 0;
	int last_counter = _CLOCK_COUNTER;
	do{
		get_clock();
		if(_CLOCK_COUNTER != last_counter){
			acumulado += 5400;
			last_counter = _CLOCK_COUNTER;
		}

	}while(acumulado <= (msec*1000));
}
#endif