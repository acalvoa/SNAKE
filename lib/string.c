#ifndef _STRING_IO_
#define _STRING_IO_
void printchar(const char pStr) {
	__asm__ (
	    "int $0x10" : : "a"(0x0e00|pStr), "b" (0x0000)
	);
}
void print_char_ascii(int pStr) {
	__asm__ (
	    "int $0x10" : : "a"(0x0e00|pStr), "b" (0x0000)
	);
}
int strlen(const char *str){
	const char *s;
	for(s=str; *s; ++s);
	return(s - str);
}
void print(const char* txt){
	for(int i=0; i<strlen(txt); i++){
		printchar(txt[i]);
	}
}
void printc(char* txt){
	for(int i=0; i<strlen(txt); i++){
		printchar(txt[i]);
	}
}
char* itoa( int value, char * str, int base )
{
    char * rc;
    char * ptr;
    char * low;
    // Check for supported base.
    if ( base < 2 || base > 36 )
    {
        *str = '\0';
        return str;
    }
    rc = ptr = str;
    // Set '-' for negative decimals.
    if ( value < 0 && base == 10 )
    {
        *ptr++ = '-';
    }
    // Remember where the numbers start.
    low = ptr;
    // The actual conversion.
    do
    {
        // Modulo is negative for negative value. This trick makes abs() unnecessary.
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % base];
        value /= base;
    } while ( value );
    // Terminating the string.
    *ptr-- = '\0';
    // Invert the numbers.
    while ( low < ptr )
    {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return rc;
}
#endif