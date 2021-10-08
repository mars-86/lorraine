%ifndef __X16_STRING_INC_INCLUDED__
%define __X16_STRING_INC_INCLUDED__

[bits 16]

; args:
; STACK = string
;
; return
; AX = length

string_length_16:
	push si
	push bp
	mov bp, sp
	mov si, [bp + 6]
	xor ax, ax
	.repeat:
		cmp BYTE [si], 0
		je .done
		inc ax
		inc si
 		jmp .repeat
	.done:
	pop bp
	pop si
	ret


; args:
; STACK = dest
; STACK = src
; STACK = length
;
; return
; AX = copied string address

string_concat_16:
	push si
	push di
	push bp
	mov bp, sp
	cld									; clear direction flag
	mov cx, [bp + 08]					; length
	mov si, [bp + 10]					; src
	mov di, [bp + 12]					; dest
	push di								; save dest's address
	.repeat:
		mov al, [di]
		xor al, al
		jz .done
		inc di
		jmp .repeat
	.done:
	rep movsb
	pop ax								; dest start address
	pop bp
	pop di
	pop si
	ret


; args:
; STACK = dest
; STACK = src
; STACK = length
;
; return
; AX = copied string address

string_copy_16:
	push si
	push di
	push bp
	mov bp, sp
	cld									; clear direction flag
	mov cx, [bp + 08]					; length
	mov si, [bp + 10]					; src
	mov di, [bp + 12]					; dest
	mov ax, di							; save dest's address
	rep movsb
	pop bp
	pop di
	pop si
	ret


%endif									; __X16_STRING_INC_INCLUDED__
