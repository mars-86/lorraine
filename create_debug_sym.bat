@echo off
nasm -f elf -g -o bootloader.elf bootloader.asm
nasm -f elf -g -o stage2.elf stage2.asm
rmdir /q /s ../cdisogdb
md ../cdisogdb
mv bootloader.elf stage2.elf ../cdisogdb
cd ../cdisogdb
ld -Ttext=0x7c00 bootloader.elf --oformat binary -o bootloader.bin
ld -Ttext=0x07e0 stage2.elf --oformat binary -o stage2.bin
dd if=/dev/zero of=disk.img bs=1024 count=720
dd if=bootloader.bin of=disk.img conv=notrunc
dd if=stage2.bin of=disk.img bs=512 seek=1 conv=notrunc
rm bootloader.elf stage2.elf bootloader.bin stage2.bin
echo SUCCESS
exit
