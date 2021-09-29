[bits 16]
[ORG 0x0000]                                ; ORG = 0 | S = 0x07e0, Off = 0x0 = PA = 0x7e00 

jmp x_16

%include "x16/lib/stdio.inc"

welcome_x16 db "Welcome to x16 mode!", 0xA, 0xD, 0
welcome_x16_len equ $ - welcome_x16

x_16:                                       ; x16 entry point

mov ax, cs
mov ds, ax									; Set DS = CS

push es
mov ax, 0xA000
mov es, ax
xor ax, ax
mov al, 0x13
int 0x10
pop es

mov cx, 0x00
mov al, 'H'
call putc_16

mov ah, 0x0C
mov al, 0xA5
mov bh, 0x00
mov cx, 0x50
mov dx, 0x50
int 0x10

cli
hlt
