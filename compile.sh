#!/bin/bash
dd if=/dev/zero of=os-img.img bs=512 count=2880
# COMPILAMOS EL BOOT
rm -f os-img os-img.bin 
gcc -ffreestanding -std=c99 -c kernel.c -o kernel.o -m32 
ld -o kernel.bin -T ./linker/kernel.ld kernel.o -m elf_i386 --oformat binary 
nasm boot.asm -f bin -o boot.bin 
# cat boot.bin kernel.bin > os-img.bin 
# truncate os-img.bin -s 5120 
dd if=boot.bin of=os-img.img
dd if=kernel.bin of=os-img.img ibs=512 conv=sync seek=1
# qemu-system-i386 os-img.img
# bochs
# nasm -f bin kernel.asm -o kernel.bin
# dd if=kernel.bin of=floppy.img ibs=512 conv=sync seek=1
# BORRAMOS LOS ARCHIVOS INNECESARIOS
rm boot.bin
rm kernel.o
rm kernel.bin
rm os-img.bin
#CARGMOS LA IMAGEN
