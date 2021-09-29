[bits 16]
[ORG 0x0000]                                ; ORG = 0 | S = 0x07e0, Off = 0x0 = PA = 0x7e00 

jmp x_16

%include "x16/stdio.inc"

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

mov al, 'H'
call putc_16

mov al, 'e'
call putc_16

mov al, 'l'
call putc_16

mov al, 'l'
call putc_16

mov al, 'o'
call putc_16

mov al, ' '
call putc_16

mov al, 'w'
call putc_16

mov al, 'o'
call putc_16

mov al, 'r'
call putc_16

mov al, 'l'
call putc_16

mov al, 'd'
call putc_16

mov al, ' '
call putc_16

mov al, 'x'
call putc_16

mov al, '1'
call putc_16

mov al, '6'
call putc_16

mov al, '!'
call putc_16

; push welcome_x16
; push welcome_x16_len
; call print_string_16
; add sp, 4

; push welcome_x16
; push welcome_x16_len
; call print_string_16
; add sp, 4

mov ah, 0x0C
mov al, 0xA5
mov bh, 0x00
mov cx, 0x50
mov dx, 0x50
int 0x10

cli
hlt
