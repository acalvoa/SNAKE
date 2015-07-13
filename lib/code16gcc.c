#ifndef _CODE16GCC_H_
#define _CODE16GCC_H_
__asm__(".code16gcc\n");
__asm__("jmpl $0x0000, $boot\n");
#endif
