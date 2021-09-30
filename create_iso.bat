@echo off
nasm -f bin -o bootloader.bin bootloader.asm
nasm -f bin -o stage2.bin stage2.asm
nasm -f bin -o x16.bin x16/x16.asm
rmdir /q /s ../cdiso
md ../cdiso
mv bootloader.bin stage2.bin x16.bin ../cdiso
cd ../cdiso
dd if=/dev/zero of=disk.img bs=1024 count=720
dd if=bootloader.bin of=disk.img conv=notrunc
dd if=stage2.bin of=disk.img bs=512 seek=1 conv=notrunc
dd if=x16.bin of=disk.img bs=512 seek=3 conv=notrunc
rm bootloader.bin stage2.bin x16.bin
echo SUCCESS
exit

