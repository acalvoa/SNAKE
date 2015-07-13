ENTRY(main);
SECTIONS
{
    . = 0x7E00;
    .text : AT(0x7E00)
    {
        *(.text);
    }
} 

