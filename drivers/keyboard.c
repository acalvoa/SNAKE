#ifndef _KEYBOARD_DRIVER_
#define _KEYBOARD_DRIVER_
int *KEYBOARD_STATE_FLAG = (int *)0x0417;
int *KEYBOARD_BUFFER_START = (int *)0x0480;
int *KEYBOARD_BUFFER_END = (int *)0x0482;
int read_key_block(){
	int key;
	__asm__ (
	    "int $0x16" :"=a"(key):"a"(0x0000)
	);
	int ascii = key & 0xff;
	return ascii;
}
int read_key_scancode_block(){
	int key;
	__asm__ (
	    "int $0x16" :"=a"(key):"a"(0x0000)
	);
	int scan = (key>>8) & 0xff;
	return scan;
}
int read_key_scancode_status(){
	int key;
	__asm__ (
	    "int $0x16" :"=a"(key):"a"(0x0100)
	);
	int scan = (key>>8) & 0xff;
	return scan;
}
int read_key_status(){
	int key;
	__asm__ (
	    "int $0x16" :"=a"(key):"a"(0x0100)
	);
	int ascii = key & 0xff;
	return ascii;
}
int read_key(){
	int k = read_key_status();
	if(k != 0){
		int k = read_key_block();
		return k;	
	}
	else
	{
		return 0;
	}
}
int read_key_scancode(){
	int k = read_key_scancode_status();
	if(k != 1){
		int k = read_key_scancode_block();
		return k;	
	}
	else
	{
		return k;
	}
}
void put_in_buffer(int key, int key_scan){
	__asm__ (
	    "int $0x16" ::"a"(0x0500),"c"((key_scan<<8)|key)
	);
	int ascii = key & 0xff;
}
#endif