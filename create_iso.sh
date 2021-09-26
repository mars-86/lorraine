#!/bin/bash
nasm -f bin bootloader.asm -o bootloader.bin
nasm -f bin stage2.asm -o stage2.bin
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
