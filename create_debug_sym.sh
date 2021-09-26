#!/bin/bash
nasm -f bin -o bootloader.bin bootloader.asm
nasm -f elf32 -o stage2.o stage2.asm
ld -melf_i386 -Ttext=0x7e00 -nostdlib -o stage2.elf stage2.o
objcopy -O binary stage2.elf stage2.bin
rm stage2.o stage2.elf
rm -r ../cdiso
mkdir ../cdiso
mv bootloader.bin stage2.bin ../cdiso
cd ../cdiso
dd if=/dev/zero of=disk.img bs=1024 count=720
dd if=bootloader.bin of=disk.img conv=notrunc
dd if=stage2.bin of=disk.img bs=512 seek=1 conv=notrunc
rm bootloader.bin stage2.bin
echo SUCCESS
exit
