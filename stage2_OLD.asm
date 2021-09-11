BITS 16
ORG 0x0000

main:
	mov ax, cs
	mov ds, ax

	mov ah, 0x00
	int 0x1A

	mov ah, 0x06
	xor al, al
	mov bh, 0x05
	int 0x10
	
	xor ah, ah
	mov al, 0x13
	int 0x10
	
	mov ax, 0xA000
	mov es, ax
	
	mov ax, 320
	mov di, ax

	push 10				; x0 -> ebp + 10
	push 100			; y0 -> ebp + 08
	push 200			; x1 -> ebp + 06
	push 50				; y1 -> ebp + 04
	mov dl, 0xAA
	
	call plotline
	add sp, 8
	
	push 50				; x0 -> ebp + 10
	push 150			; y0 -> ebp + 08
	push 200			; width -> ebp + 06
	push 30				; height -> ebp + 04
	mov dl, 0x09
	
	call plotrect
	add sp, 8

	push 88				; x0 -> ebp + 08
	push 100			; y0 -> ebp + 06
	push 30				; width -> ebp + 04
	mov dl, 0xCC
	
	call plotsquare
	add sp, 6

	cli
	endloop:
		hlt
	jmp endloop
	; mov si, message
	; call printmsg

	jmp $

	; args [regs]
	; ax -> num

	; ret

%include "string.asm"
%include "plot.asm"

message db "Hello, world!", 0x0A, 0x0D, 0
