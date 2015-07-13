__asm__(".code16gcc\n");
__asm__("jmpl $0, $main\n");
#include "drivers/video.c"
#include "lib/string.c"
#include "drivers/clock.c"
#include "drivers/keyboard.c"
#include "game/snake.c"
void main(){
	set_graphicmode();
	load_game();
	while(1){
	}
}